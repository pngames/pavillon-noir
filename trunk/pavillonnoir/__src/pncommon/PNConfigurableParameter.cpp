/*
 * PNConfigurableParameter.cpp
 * 
 * Description :
 * PNConfigurableParameter definition
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

#include <libxml/xmlreader.h>

#include "pndefs.h"

#include "pnobject_base_types.h"
#include "pcf_format.h"

#include "PNConfigurableParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNConfigurableParameter::PNConfigurableParameter(PNConfigurableObject* p,
												 pnparamtype type,
												 const std::string& label,
												 const std::string& altText,
												 pnbool editable,
												 void* max,
												 void* min)
{
  _init(p, type, NULL, label, altText, editable, max, min);
}

PNConfigurableParameter::PNConfigurableParameter(PNConfigurableObject* p, 
												 pnparamtype type, 
                                                 void* elem, 
                                                 const string& label, 
                                                 const string& altText,
												 pnbool editable,
												 void* max,
												 void* min)
{
  _init(p, type, elem, label, altText, editable, max, min);
}

PNConfigurableParameter::~PNConfigurableParameter()
{
}

//////////////////////////////////////////////////////////////////////////

void
PNConfigurableParameter::_init(PNConfigurableObject* p, 
							   pnparamtype type, 
							   void* elem, 
							   const std::string& label, 
							   const std::string& altText,
							   pnbool editable, 
							   void* max, 
							   void* min)
{
  _p = p;

  _name = label;

  _elem = elem;
  _max = max;
  _min = min;

  _label = label;
  _altText = altText;
  _type = type;
  _editable = editable;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNConfigurableParameter::getType()
{
  return _type;
}

void*
PNConfigurableParameter::getElem()
{
  return _elem;
}

void*
PNConfigurableParameter::getMax()
{
  return _max;
}

void*
PNConfigurableParameter::getMin()
{
  return _min;
}

const string&
PNConfigurableParameter::getName()
{
  return _name;
}

const string&
PNConfigurableParameter::getLabel()
{
  return _label;
}

const string&
PNConfigurableParameter::getAltText()
{
  return _altText;
}

pnbool
PNConfigurableParameter::isEditable()
{
  return _editable;
}

PNConfigurableObject*
PNConfigurableParameter::getConfigurableObject()
{
  return _p;
}

void
PNConfigurableParameter::setConfigurableObject(PNConfigurableObject* object)
{
  _p = object;
}

//////////////////////////////////////////////////////////////////////////

std::string
PNConfigurableParameter::toString()
{
  switch (_type)
  {
  case PN_PARAMTYPE_BOOLEAN:
	return *((PNBool*)_elem);
  case PN_PARAMTYPE_INT:
  	return *((PNInt*)_elem);
  case PN_PARAMTYPE_UINT:
	return *((PNUInt*)_elem);
  case PN_PARAMTYPE_REAL:
  case PN_PARAMTYPE_DIALX:
  case PN_PARAMTYPE_DIALY:
  case PN_PARAMTYPE_DIALZ:
	return *((PNFloat*)_elem);
  case PN_PARAMTYPE_STRING:
  case PN_PARAMTYPE_FILE:
  case PN_PARAMTYPE_DIR:
	return *((std::string*)_elem);
  case PN_PARAMTYPE_LINK:
	break;
  case PN_PARAMTYPE_EVENTBOX:
	break;
  case PN_PARAMTYPE_MATERIAL:
	break;
  case PN_PARAMTYPE_SCRIPTLIST:
	break;
  default:
	break;
  }

  return "";
}

void
PNConfigurableParameter::fromString(const std::string& str)
{
  switch (_type)
  {
  case PN_PARAMTYPE_BOOLEAN:
	*((PNBool*)_elem) = str;
	break;
  case PN_PARAMTYPE_INT:
	*((PNInt*)_elem) = str;
	break;
  case PN_PARAMTYPE_UINT:
	*((PNUInt*)_elem) = str;
	break;
  case PN_PARAMTYPE_REAL:
  case PN_PARAMTYPE_DIALX:
  case PN_PARAMTYPE_DIALY:
  case PN_PARAMTYPE_DIALZ:
	*((PNFloat*)_elem) = str;
	break;
  case PN_PARAMTYPE_STRING:
  case PN_PARAMTYPE_FILE:
  case PN_PARAMTYPE_DIR:
	*((std::string*)_elem) = str;
	break;
  case PN_PARAMTYPE_LINK:
	break;
  case PN_PARAMTYPE_EVENTBOX:
	break;
  case PN_PARAMTYPE_MATERIAL:
	break;
  case PN_PARAMTYPE_SCRIPTLIST:
	break;
  default:
	break;
  }
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNConfigurableParameter::getDTDName() const
{
  return PCF_PARAM_XMLDTD_NAME;
}

const std::string&
PNConfigurableParameter::getRootNodeName() const
{
  return PCF_PARAM_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableParameter::unserializeFromXML(xmlNode* node)
{
  for (xmlNodePtr child = node->children ; child != NULL; child = child->next)
	if (PCF_PARAMV_XMLDTD_NAME == (const char*)child->name)
	{
	  xmlChar* attr = xmlGetProp(node, PCF_XMLPROP_DATA);
	  if (attr != NULL)
		fromString((const char*)attr);
	  break;
	}

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableParameter::_serializeContent(xmlNode* node)
{
  xmlNewProp(node, PCF_XMLPROP_NAME, BAD_CAST getName().c_str());

  xmlNodePtr valueNode = xmlNewChild(node, NULL, BAD_CAST PCF_PARAMV_XMLDTD_NAME.c_str(), NULL);
  xmlNewProp(valueNode, PCF_XMLPROP_DATA, BAD_CAST toString().c_str());

  return PNEC_SUCCESS;
}

pnint
PNConfigurableParameter::serializeInXML(xmlNode* root, pnbool isroot/* = false*/)
{
  if (!isroot)
	root = xmlNewChild(root, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  return _serializeContent(root);
}

//////////////////////////////////////////////////////////////////////////
};
