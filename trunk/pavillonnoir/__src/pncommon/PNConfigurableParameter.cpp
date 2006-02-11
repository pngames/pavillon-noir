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

#include "pntypes.h"
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

  _serialization = S_VALUE;
}

//////////////////////////////////////////////////////////////////////////

pnparamtype
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

PNObject*
PNConfigurableParameter::getObjectByClass(const std::string& name)
{
  //if (name == )
  return NULL;
}

//////////////////////////////////////////////////////////////////////////

std::string
PNConfigurableParameter::toString(pnbool value)
{
  return PNBool::staticToString(value);
}

std::string
PNConfigurableParameter::toString(pnint value)
{
  return PNInt::staticToString(value);
}

std::string
PNConfigurableParameter::toString(pnuint value)
{
  return PNUInt::staticToString(value);
}

std::string
PNConfigurableParameter::toString(pnfloat value)
{
  return PNFloat::staticToString(value);
}

std::string
PNConfigurableParameter::toString(const std::string& value)
{
  return value;
}

std::string
PNConfigurableParameter::toString(PNObject* value)
{
  return value->toString();
}

std::string
PNConfigurableParameter::toString()
{
  switch (_type)
  {
  case PN_PARAMTYPE_BOOLEAN:
	return toString(*(pnbool*)_elem);

  case PN_PARAMTYPE_INT:
	return toString(*(pnint*)_elem);

  case PN_PARAMTYPE_UINT:
	return toString(*(pnuint*)_elem);

  case PN_PARAMTYPE_REAL:
  case PN_PARAMTYPE_DIALX:
  case PN_PARAMTYPE_DIALY:
  case PN_PARAMTYPE_DIALZ:
	return toString(*(pnfloat*)_elem);

  case PN_PARAMTYPE_STRING:
  case PN_PARAMTYPE_FILE:
  case PN_PARAMTYPE_DIR:
	return toString(*(std::string*)_elem);

  case PN_PARAMTYPE_LINK:
  case PN_PARAMTYPE_EVENTBOX:
  case PN_PARAMTYPE_MATERIAL:
	return toString(*(PNObject**)_elem);

  case PN_PARAMTYPE_SCRIPTLIST:
	/*FIXME*/
  default:
	break;
  }

  return "";
}

//////////////////////////////////////////////////////////////////////////

void
PNConfigurableParameter::fromString(pnbool* value, const std::string& str)
{
  *value = PNBool::staticToValue(str);
}

void
PNConfigurableParameter::fromString(pnint* value, const std::string& str)
{
  *value = PNInt::staticToValue(str);
}

void
PNConfigurableParameter::fromString(pnuint* value, const std::string& str)
{
  *value = PNUInt::staticToValue(str);
}

void
PNConfigurableParameter::fromString(pnfloat* value, const std::string& str)
{
  *value = PNFloat::staticToValue(str);
}

void
PNConfigurableParameter::fromString(std::string* value, const std::string& str)
{
  *value = str;
}

void
PNConfigurableParameter::fromString(PNObject** value, const std::string& str)
{
  (*value)->fromString(str);
}

void
PNConfigurableParameter::fromString(const std::string& str)
{
  switch (_type)
  {
  case PN_PARAMTYPE_BOOLEAN:
	fromString((pnbool*)_elem, str);
	break;

  case PN_PARAMTYPE_INT:
	fromString((pnint*)_elem, str);
	break;

  case PN_PARAMTYPE_UINT:
	fromString((pnuint*)_elem, str);
	break;

  case PN_PARAMTYPE_REAL:
  case PN_PARAMTYPE_DIALX:
  case PN_PARAMTYPE_DIALY:
  case PN_PARAMTYPE_DIALZ:
	fromString((pnfloat*)_elem, str);
	break;

  case PN_PARAMTYPE_STRING:
  case PN_PARAMTYPE_FILE:
  case PN_PARAMTYPE_DIR:
	fromString((std::string*)_elem, str);
	break;

  case PN_PARAMTYPE_LINK:
  case PN_PARAMTYPE_EVENTBOX:
  case PN_PARAMTYPE_MATERIAL:
	fromString((PNObject**)_elem, str);
	break;

  case PN_PARAMTYPE_SCRIPTLIST:
	/*FIXME*/
  default:
	break;
  }
}

//////////////////////////////////////////////////////////////////////////

void
PNConfigurableParameter::setSerializable(serializable option)
{
  _serialization |= option;
}

void
PNConfigurableParameter::unsetSerializable(serializable option)
{
  _serialization &= ~option;
}

///

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
PNConfigurableParameter::_unserializeNode(xmlNode* node)
{
  if (PCF_PARAMV_XMLDTD_NAME == (const char*)node->name)
  {
	xmlChar* attr = xmlGetProp(node, PCF_XMLPROP_DATA);
	if (attr != NULL)
	  fromString((const char*)attr);
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableParameter::_serializeContent(xmlNode* node)
{
  xmlNewProp(node, PCF_XMLPROP_NAME, BAD_CAST getName().c_str());

  if (_serialization & S_VALUE)
  {
	xmlNodePtr valueNode = xmlNewChild(node, NULL, BAD_CAST PCF_PARAMV_XMLDTD_NAME.c_str(), NULL);
	xmlNewProp(valueNode, PCF_XMLPROP_DATA, BAD_CAST toString().c_str());
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};

