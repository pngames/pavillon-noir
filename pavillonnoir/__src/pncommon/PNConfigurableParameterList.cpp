/*
 * PNConfigurableParameterList.cpp
 * 
 * Description :
 * PNConfigurableParameterList definition
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

#include <list>

//////////////////////////////////////////////////////////////////////////

#include "pndefs.h"
#include "pnobject_base_types.h"

//////////////////////////////////////////////////////////////////////////

#include "PNConfigurableParameterList.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNConfigurableParameterList::PNConfigurableParameterList(PNConfigurableObject* p, 
														 pnlistparamtype type, 
														 void* elem, 
														 const string& label, 
														 const string& altText,
														 pnbool choosable/* = true*/,
														 pnbool editable,
														 void* max,
														 void* min) :
PNConfigurableParameter(p, (pnparamtype)type, elem, label, altText, editable, max, min),
_choosable(choosable), _choise(0)
{
  _serialization |= S_CHOISE;
}

PNConfigurableParameterList::~PNConfigurableParameterList()
{
}

//////////////////////////////////////////////////////////////////////////

pnbool
PNConfigurableParameterList::isChoosable()
{
  return _choosable;
}

void
PNConfigurableParameterList::setChoosable(pnbool choosable)
{
  _choosable = choosable;
}

void
PNConfigurableParameterList::setChoise(pnuint choise)
{
  _choise = choise;
}

pnuint
PNConfigurableParameterList::getChoise()
{
  return _choise;
}

//////////////////////////////////////////////////////////////////////////

pnint		
PNConfigurableParameterList::getElementList(pnint def)
{
  std::list<pnint>*	lst = (std::list<pnint>*)_elem;
  std::list<pnint>::iterator	it = lst->begin();
  for (int i = 0; it != lst->end(); ++i, ++it)
  {
	if  (i == _choise)
	{
	  return *it;
	}
  }

  return def;
}

pnuint	
PNConfigurableParameterList::getElementList(pnuint def)
{
  std::list<pnuint>*	lst = (std::list<pnuint>*)_elem;
  std::list<pnuint>::iterator	it = lst->begin();
  for (int i = 0; it != lst->end(); ++i, ++it)
  {
	if  (i == _choise)
	{
	  return *it;
	}
  }

  return def;
}

pnfloat
PNConfigurableParameterList::getElementList(pnfloat def)
{
  std::list<pnfloat>*	lst = (std::list<pnfloat>*)_elem;
  std::list<pnfloat>::iterator	it = lst->begin();
  for (int i = 0; it != lst->end(); ++i, ++it)
  {
	if  (i == _choise)
	{
	  return *it;
	}
  }

  return def;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableParameterList::findChoiseIndex(const std::string& value)
{
  switch (_type)
  {
  case PN_LISTPARAMTYPE_BOOL:
	return findChoiseIndex((std::list<pnbool>*)_elem, value);
  case PN_LISTPARAMTYPE_INT:
	return findChoiseIndex((std::list<pnint>*)_elem, value);
  case PN_LISTPARAMTYPE_UINT:
	return findChoiseIndex((std::list<pnuint>*)_elem, value);
  case PN_LISTPARAMTYPE_REAL:
	return findChoiseIndex((std::list<pnfloat>*)_elem, value);
  case PN_LISTPARAMTYPE_STRING:
  case PN_LISTPARAMTYPE_FILE:
  case PN_LISTPARAMTYPE_DIR:
	return findChoiseIndex((std::list<std::string>*)_elem, value);

  case PN_LISTPARAMTYPE_LPPNOBJECT:
	return findChoiseIndex((std::list<PNObject*>*)_elem, value);

  case PN_LISTPARAMTYPE_VPPNOBJECT:
  case PN_LISTPARAMTYPE_MATERIAL:
  case PN_LISTPARAMTYPE_ANIM:
	return findChoiseIndex((std::vector<PNObject*>*)_elem, value);

  case PN_LISTPARAMTYPE_LINK:
	/*FIXME*/
  default:
	break;
  }

  return -1;
}

std::string
PNConfigurableParameterList::findChoiseValue(pnuint index)
{
  switch (_type)
  {
  case PN_LISTPARAMTYPE_BOOL:
	return findChoiseValue((std::list<pnbool>*)_elem, index);
  case PN_LISTPARAMTYPE_INT:
	return findChoiseValue((std::list<pnint>*)_elem, index);
  case PN_LISTPARAMTYPE_UINT:
	return findChoiseValue((std::list<pnuint>*)_elem, index);
  case PN_LISTPARAMTYPE_REAL:
	return findChoiseValue((std::list<pnfloat>*)_elem, index);
  case PN_LISTPARAMTYPE_STRING:
  case PN_LISTPARAMTYPE_FILE:
  case PN_LISTPARAMTYPE_DIR:
	return findChoiseValue((std::list<std::string>*)_elem, index);

  case PN_LISTPARAMTYPE_LPPNOBJECT:
	return findChoiseValue((std::list<PNObject*>*)_elem, index);

  case PN_LISTPARAMTYPE_VPPNOBJECT:
  case PN_LISTPARAMTYPE_MATERIAL:
  case PN_LISTPARAMTYPE_ANIM:
	return findChoiseValue((std::vector<PNObject*>*)_elem, index);

  case PN_LISTPARAMTYPE_LINK:
	/*FIXME*/
  default:
	break;
  }

  return "";
}

void
PNConfigurableParameterList::addToList(const std::string& value)
{
  switch (_type)
  {
  case PN_LISTPARAMTYPE_BOOL:
	((std::list<pnbool>*)_elem)->push_back(PNBool::staticToValue(value));
  case PN_LISTPARAMTYPE_INT:
	((std::list<pnint>*)_elem)->push_back(PNInt::staticToValue(value));
  case PN_LISTPARAMTYPE_UINT:
	((std::list<pnuint>*)_elem)->push_back(PNUInt::staticToValue(value));
  case PN_LISTPARAMTYPE_REAL:
	((std::list<pnfloat>*)_elem)->push_back(PNFloat::staticToValue(value));
  case PN_LISTPARAMTYPE_STRING:
  case PN_LISTPARAMTYPE_FILE:
  case PN_LISTPARAMTYPE_DIR:
	((std::list<std::string>*)_elem)->push_back(value);

  case PN_LISTPARAMTYPE_LPPNOBJECT:
	/*FIXME*/

  case PN_LISTPARAMTYPE_VPPNOBJECT:
  case PN_LISTPARAMTYPE_MATERIAL:
  case PN_LISTPARAMTYPE_ANIM:
	/*FIXME*/

  case PN_LISTPARAMTYPE_LINK:
	/*FIXME*/
  default:
	break;
  }
}

void
PNConfigurableParameterList::serializeList(xmlNode* node)
{
  switch (_type)
  {
  case PN_LISTPARAMTYPE_BOOL:
	return serializeList((std::list<pnbool>*)_elem, node);
  case PN_LISTPARAMTYPE_INT:
	return serializeList((std::list<pnint>*)_elem, node);
  case PN_LISTPARAMTYPE_UINT:
	return serializeList((std::list<pnuint>*)_elem, node);
  case PN_LISTPARAMTYPE_REAL:
	return serializeList((std::list<pnfloat>*)_elem, node);
  case PN_LISTPARAMTYPE_STRING:
  case PN_LISTPARAMTYPE_FILE:
  case PN_LISTPARAMTYPE_DIR:
	return serializeList((std::list<std::string>*)_elem, node);

  case PN_LISTPARAMTYPE_LPPNOBJECT:
	return serializeList((std::list<PNObject*>*)_elem, node);

  case PN_LISTPARAMTYPE_VPPNOBJECT:
  case PN_LISTPARAMTYPE_MATERIAL:
  case PN_LISTPARAMTYPE_ANIM:
	return serializeList((std::vector<PNObject*>*)_elem, node);

  case PN_LISTPARAMTYPE_LINK:
	/*FIXME*/
  default:
	break;
  }
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableParameterList::_unserializeNode(xmlNode* node)
{
  if (PCF_PARAMV_XMLDTD_NAME == (const char*)node->name)
  {
	xmlChar* attr = xmlGetProp(node, PCF_XMLPROP_DATA);
	
	addToList((const char*)attr);
  }

  return PNEC_SUCCESS;
}

pnint
PNConfigurableParameterList::unserializeFromXML(xmlNode* node)
{
  if (_serialization & S_CHOISE)
  {
	xmlChar* attr = xmlGetProp(node, PCF_XMLPROP_CHOISE);

	if (attr)
	  setChoise(findChoiseIndex((const char*) attr));
  }

  return _serialization & S_VALUE ? PNConfigurableParameter::unserializeFromXML(node) : PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableParameterList::_serializeContent(xmlNode* node)
{
  xmlNewProp(node, PCF_XMLPROP_NAME, BAD_CAST getName().c_str());

  if (_serialization & S_CHOISE)
	xmlNewProp(node, PCF_XMLPROP_CHOISE, BAD_CAST findChoiseValue(_choise).c_str());

  if (_serialization & S_VALUE)
  {
	serializeList(node);
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};

