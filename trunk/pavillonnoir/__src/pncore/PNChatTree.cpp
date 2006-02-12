/*
* PNChatTree.cpp
* 
* Description :
* PNChatTree definition
*
* Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
* This software has been written in EPITECH <http://www.epitech.net>
* EPITECH is computer science school in Paris - FRANCE -
* under the direction of flav <http://www.epita.fr/~flav>.
* and Jerome Landrieu.
*
* This file is part of Pavillon Noir.
*
* Pavillon Noir is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* Pavillon Noir is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU General Public License along with
* Pavillon Noir; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
*/

#include <boost/filesystem/operations.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "pndefs.h"
#include "pcf_format.h"
#include "pnchatxml.h"
#include "PNChatTree.hpp"

using namespace PN;
namespace fs = boost::filesystem;

namespace PN
{

  PNChatTree::PNChatTree()
  {
	_doc = NULL;
  }

  PNChatTree::~PNChatTree()
  {
	if (_doc != NULL)
	  xmlFreeDoc(_doc);
  }

  //////////////////////////////////////////////////////////////////////////

  pnint	PNChatTree::unserializeFromXML(xmlNode* root)
  {
	_id = (const char*)xmlGetProp(root, PNCHATXML_ID_ATTR);
	_name = (const char*)xmlGetProp(root, PNCHATXML_BUDDYNAME_ATTR);
	_currentNode = new xmlNode();
	*_currentNode = *root;

	return PNEC_SUCCESS;
  }

  xmlNode* PNChatTree::getCurrentNode()
  {
	return _currentNode;
  }

  pnint	PNChatTree::unserializeFromFile(const fs::path& file)
  {
	pnerror(PN_LOGLVL_INFO, "Loading XMLObject: %s ...", file.native_file_string().c_str());

	if (!fs::exists(file))
	  return PNEC_FILE_NOT_FOUND;

	if (fs::is_directory(file))
	  return PNEC_NOT_A_FILE;

	//////////////////////////////////////////////////////////////////////////

	xmlParserCtxtPtr	ctxt;
	

	LIBXML_TEST_VERSION ctxt = xmlNewParserCtxt();	// create a parser context

	if (ctxt == NULL) 
	  return PNEC_ALLOC_PARSER_CONTEXT;

	_doc = xmlCtxtReadFile(ctxt, file.string().c_str(), NULL, XML_PARSE_DTDVALID); // parse the file, + DTD validation 
	xmlFreeParserCtxt(ctxt);							// free up the parser context

	if (_doc == NULL)									// check if parsing succeeded
	  return PNEC_FAILED_TO_PARSE;

	xmlNodePtr  node = xmlDocGetRootElement(_doc);

	//////////////////////////////////////////////////////////////////////////

	pnint error = unserializeFromXML(node);

	//////////////////////////////////////////////////////////////////////////
	// clean

	//xmlFreeDoc(doc);									// free the document

	return error;
  }

  //////////////////////////////////////////////////////////////////////////
  
  bool PNChatTree::isAResolvedDep(std::string depID)
  {
	ListResolvedDependencies::iterator it;

	for ( it = _resolvedDependencies.begin(); it != _resolvedDependencies.end(); ++it)
	{
	  if (depID == *it)
		return true;
	}
	return false;
  }

  bool	PNChatTree::buddyIsAvailable(xmlNode* node)
  {
	if (node->children != NULL)
	{
	  for (xmlNodePtr sub = node->children; sub != NULL; sub = sub->next)
	  {
		if (xmlStrEqual(sub->name, PNCHATXML_DEPENDS_MKP))
		  if (!isAResolvedDep((const char*)xmlGetProp(sub, PNCHATXML_ID_ATTR)))
			return false;
	  }
	}
	return true;
  }

  xmlNodePtr PNChatTree::getBuddyNode(xmlNode* currentNode)
  {
	if (currentNode->children != NULL)
	{
	  for (xmlNodePtr current = currentNode->children; current != NULL; current = current->next)
	  {
		if (xmlStrEqual(current->name, PNCHATXML_BUDDY_MKP) && buddyIsAvailable(current))
		{
		  return current;
		}
	  }
	}
	return NULL;
  }

  void	PNChatTree::setListDependencies(ListResolvedDependencies& deps)
  {
	_resolvedDependencies = deps;
  }

  xmlNode* PNChatTree::getNodeFromId(xmlNode* root, std::string NodeId)
  {
	for (xmlNodePtr current = root->children; current != NULL; current = current->next)
	{
	  xmlChar* id = xmlGetProp(current, PNCHATXML_ID_ATTR);
	  if (id != NULL && strcmp((const char*)id, NodeId.c_str()) == 0)
		return current;
	}
	return NULL;
  }
}
