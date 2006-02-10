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


#include "pndefs.h"
#include "pcf_format.h"
#include "pnxml.h"
#include "PNChatTree.hpp"

using namespace PN;
namespace fs = boost::filesystem;

namespace PN
{

  PNChatTree::PNChatTree()
  {
  }

  PNChatTree::~PNChatTree()
  {
  }

  //////////////////////////////////////////////////////////////////////////

  pnint	PNChatTree::unserializeFromXML(xmlNode* root)
  {
	_id = (const char*)xmlGetProp(root, PNXML_ID_ATTR);
	_name = (const char*)xmlGetProp(root, PNXML_BUDDYNAME_ATTR);
	_currentNode = root;

	return PNEC_SUCCESS;
  }

  xmlNode* PNChatTree::getCurrentNode()
  {
	return _currentNode;
  }

  pnint	PNChatTree::unserializeFromFile(const fs::path& file)
  {
	return IPNXMLSerializable::unserializeFromFile(file);
  }

  //////////////////////////////////////////////////////////////////////////
  
  bool PNChatTree::isAResolvedDep(std::string depID)
  {
	for (std::list<std::string>::iterator it = _resolvedDependencies->begin(); it != _resolvedDependencies->end(); ++it)
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
		if (xmlStrEqual(sub->name, PNXML_DEPENDS_MKP))
		  if (!isAResolvedDep((const char*)xmlGetProp(sub, PNXML_ID_ATTR)))
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
		if (xmlStrEqual(current->name, PNXML_BUDDY_MKP) && buddyIsAvailable(current))
		{
		  return current;
		}
	  }
	}
	return NULL;

  }

  void	PNChatTree::addDependency(std::string dependency)
  {
	_resolvedDependencies->push_back(dependency);
  }
}
