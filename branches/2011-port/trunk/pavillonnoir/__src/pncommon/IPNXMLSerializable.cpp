/*
 * IPNXMLSerializable.cpp
 * 
 * Description :
 * Base interface for serialization support
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
 
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <boost/filesystem/operations.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

//////////////////////////////////////////////////////////////////////////

#include "pndefs.h"
#include "pntypes.h"

#include "PNPoint3f.hpp"

#include "IPNXMLSerializable.hpp"

//////////////////////////////////////////////////////////////////////////

using namespace PN;
using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

const std::string	IPNXMLSerializable::_dtd;
const std::string	IPNXMLSerializable::_dtdName;
const std::string	IPNXMLSerializable::_rootNode = "root";

IPNXMLSerializable::IPNXMLSerializable()
{
  _serializeInXML = true;
}

//////////////////////////////////////////////////////////////////////////

const std::string&
IPNXMLSerializable::getDTD() const
{
  return _dtd;
}

const std::string&
IPNXMLSerializable::getDTDName() const
{
  return _dtdName;
}

const std::string&
IPNXMLSerializable::getRootNodeName() const
{
  return _rootNode;
}

//////////////////////////////////////////////////////////////////////////

pnint
IPNXMLSerializable::_unserializeNode(xmlNode* node)
{
  return PNEC_NOT_IMPLEMENTED;
}

pnint
IPNXMLSerializable::unserializeFromXML(xmlNode* root)
{
  for (root = root->children ; root != NULL; root = root->next)
	if (root->type == XML_ELEMENT_NODE)
	  _unserializeNode(root);

  return PNEC_SUCCESS;
}

/**
 * @brief		Load object from file
 *
 * @param file	File to load
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
 *
 * @see			pnGetErrorString
 */
pnint
IPNXMLSerializable::unserializeFromFile(const boost::filesystem::path& file)
{
  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;

  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  //////////////////////////////////////////////////////////////////////////

  xmlParserCtxtPtr	ctxt;
  xmlDocPtr			doc;

  LIBXML_TEST_VERSION ctxt = xmlNewParserCtxt();	// create a parser context

  if (ctxt == NULL) 
	return PNEC_ALLOC_PARSER_CONTEXT;

  doc = xmlCtxtReadFile(ctxt, file.string().c_str(), NULL, XML_PARSE_DTDVALID); // parse the file, + DTD validation 
  xmlFreeParserCtxt(ctxt);							// free up the parser context

  if (doc == NULL)									// check if parsing succeeded
	return PNEC_FAILED_TO_PARSE;

  xmlNodePtr  node = xmlDocGetRootElement(doc);

  //////////////////////////////////////////////////////////////////////////

  pnint error = unserializeFromXML(node);

  //////////////////////////////////////////////////////////////////////////
  // clean

  xmlFreeDoc(doc);									// free the document

  return error;
}

//////////////////////////////////////////////////////////////////////////

pnint
IPNXMLSerializable::_serializeContent(xmlNode* node)
{
  return PNEC_NOT_IMPLEMENTED;
}

pnint
IPNXMLSerializable::serializeInXML(xmlNode* root, pnbool isroot /*=false*/)
{
  if (!isroot)
	root = xmlNewChild(root, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  return _serializeContent(root);
}

pnint
IPNXMLSerializable::serializeInFile(const boost::filesystem::path& file)
{
  if (!_serializeInXML)
	return IPNXMLSerializable::serializeInFile(file);

  xmlDocPtr doc = NULL;       /* document pointer */
  xmlNodePtr root_node = NULL;/* node pointers */

  LIBXML_TEST_VERSION;

  /* 
  * Creates a new document, a node and set it as a root node
  */
  doc = xmlNewDoc(BAD_CAST "1.0");
  root_node = xmlNewNode(NULL, BAD_CAST getRootNodeName().c_str());
  xmlDocSetRootElement(doc, root_node);

  /*
  * Creates a DTD declaration. Isn't mandatory. 
  */
  if (!getDTD().empty())
	xmlCreateIntSubset(doc, BAD_CAST getDTDName().c_str(), NULL, BAD_CAST getDTD().c_str());

  //////////////////////////////////////////////////////////////////////////

  serializeInXML(root_node, true);

  //////////////////////////////////////////////////////////////////////////

  /* 
  * Dumping document to stdio or file
  */
  xmlSaveFormatFile(file.string().c_str(), doc, 1);

  /*free the document */
  xmlFreeDoc(doc);

  /*
  *Free the global variables that may
  *have been allocated by the parser.
  */
  xmlCleanupParser();

  /*
  * this is to debug memory for regression tests
  */
  xmlMemoryDump();

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

namespace XMLUtils {
//////////////////////////////////////////////////////////////////////////

PNAPI pnuint
xmlGetNbChilds(xmlNode* node)
{
  int nb = 0;

  for (xmlNodePtr current = node->children; current != NULL; current = current->next)
	++nb;

  return nb;
}

//////////////////////////////////////////////////////////////////////////

#define XML_TRUE_VAL	(const xmlChar *)"true"
#define XML_FALSE_VAL	(const xmlChar *)"false"

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const xmlChar *name, pnbool value)
{
  return xmlNewProp(node, name, value ? XML_TRUE_VAL : XML_FALSE_VAL);
}

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const char *name, pnbool value)
{
  return xmlNewProp(node, BAD_CAST name, value);
}

PNAPI pnbool
xmlGetProp(xmlNode* node, const pnuchar* name, pnbool def)
{
  xmlChar*	att = xmlGetProp(node, name);

  if (att == NULL)
	return def;

  return PNBool::staticToValue((const char*)att, def);
}

PNAPI pnbool
xmlGetProp(xmlNode* node, const char* name, pnbool def)
{
  return xmlGetProp(node, BAD_CAST name, def);
}

//////////////////////////////////////////////////////////////////////////

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const xmlChar *name, pnint value)
{  
  std::ostringstream os;
  os << value;

  return xmlNewProp(node, name, BAD_CAST os.str().c_str());
}

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const char *name, pnint value)
{
  return xmlNewProp(node, BAD_CAST name, value);
}

PNAPI pnint
xmlGetProp(xmlNode* node, const pnuchar* name, pnint def)
{
  xmlChar*	att = xmlGetProp(node, name);

  if (att == NULL)
	return def;

  return PNInt::staticToValue((const char*)att, def);
}

PNAPI pnint
xmlGetProp(xmlNode* node, const char* name, pnint def)
{
  return xmlGetProp(node, BAD_CAST name, def);
}

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const pnuchar *name, pnuint value)
{
  return xmlNewProp(node, BAD_CAST name, (pnint)value);
}

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const char *name, pnuint value)
{
  return xmlNewProp(node, BAD_CAST name, value);
}

PNAPI pnuint
xmlGetProp(xmlNode* node, const pnuchar* name, pnuint def)
{
  return xmlGetProp(node, BAD_CAST name, (pnint)def);
}

PNAPI pnuint
xmlGetProp(xmlNode* node, const char* name, pnuint def)
{
  return xmlGetProp(node, BAD_CAST name, def);
}

//////////////////////////////////////////////////////////////////////////

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const pnuchar *name, pnfloat value)
{
  std::ostringstream os;
  os << value;

  return xmlNewProp(node, name, BAD_CAST os.str().c_str());
}

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const char *name, pnfloat value)
{
  return xmlNewProp(node, BAD_CAST name, value);
}

PNAPI pnfloat
xmlGetProp(xmlNode* node, const pnuchar* name, pnfloat def)
{
  xmlChar*	att = xmlGetProp(node, name);

  if (att == NULL)
	return def;

  return PNFloat::staticToValue((const char*)att, def);
}

PNAPI pnfloat
xmlGetProp(xmlNode* node, const char* name, pnfloat def)
{
  return xmlGetProp(node, BAD_CAST name, def);
}

//////////////////////////////////////////////////////////////////////////

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const pnuchar *name, const PNPoint3f& value)
{
  return xmlNewProp(node, name, BAD_CAST value.toString().c_str());
}

PNAPI xmlAttr*
xmlNewProp(xmlNode* node, const char *name, const PNPoint3f& value)
{
  return xmlNewProp(node, BAD_CAST name, value);
}

PNAPI PNPoint3f
xmlGetProp(xmlNode* node, const pnuchar* name, const PNPoint3f& def)
{
  xmlChar*	att = xmlGetProp(node, name);

  if (att == NULL)
	return def;

  return PNPoint3f((const char*)att);
}

PNAPI PNPoint3f
xmlGetProp(xmlNode* node, const char* name, const PNPoint3f& def)
{
  return xmlGetProp(node, BAD_CAST name, def);
}

//////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
}

