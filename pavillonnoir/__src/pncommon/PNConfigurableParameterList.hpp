/*
 * PNConfigurableParameterList.hpp
 * 
 * Description :
 * PNConfigurableParameterList declaration
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

#ifndef _PNCONFIGURABLEPARAMETERLIST_HPP_
# define _PNCONFIGURABLEPARAMETERLIST_HPP_

#include <list>

//////////////////////////////////////////////////////////////////////////

#include "PNConfigurableParameter.hpp"
#include "pcf_format.h"
#include "libxml/xmlreader.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef enum
{
  PN_LISTPARAMTYPE_BOOL = PN_NB_PARAMTYPE,	// based on std:list<pnbool>
  PN_LISTPARAMTYPE_INT,						// based on std:list<pnint>
  PN_LISTPARAMTYPE_UINT,					// based on std:list<pnuint>
  PN_LISTPARAMTYPE_REAL,					// based on std:list<pnfloat>
  PN_LISTPARAMTYPE_STRING,					// based on std:list<std::string>
  PN_LISTPARAMTYPE_FILE,					// based on std:list<std::string>
  PN_LISTPARAMTYPE_DIR,						// based on std:list<std::string>

  PN_LISTPARAMTYPE_LPPNOBJECT,				// based on std:list<PNObject*>
  PN_LISTPARAMTYPE_VPPNOBJECT,			  	// based on std:vector<PNObject*>

  PN_LISTPARAMTYPE_LINK,
  PN_LISTPARAMTYPE_MATERIAL,				// based on PN3DObject:VectorMaterial
  PN_LISTPARAMTYPE_ANIM,					// based on PN3DSkeletonObject:AnimationVector

  PN_NB_LISTPARAMTYPE						// number of parameters
} pnlistparamtype;

//////////////////////////////////////////////////////////////////////////

class PNAPI				PNConfigurableParameterList : public PNConfigurableParameter
{
public:
  typedef enum
  {
	S_CHOISE = PNConfigurableParameter::LAST_S,
	LAST_S = S_CHOISE << 1
  } serializable;
protected:
  pnbool				_choosable;
  pnuint				_choise;

public:
  PNConfigurableParameterList(PNConfigurableObject* p, pnlistparamtype type, void* elem, const std::string& label, const std::string& altText, pnbool choosable = true, pnbool editable = true, void* max = NULL, void* min = NULL);
  virtual ~PNConfigurableParameterList();

  pnbool				isChoosable();
  void					setChoosable(pnbool choosable);

  void					setChoise(pnuint choise);
  pnuint				getChoise();

  pnint					getElementList(pnint def);
  pnuint				getElementList(pnuint def);
  pnfloat				getElementList(pnfloat def);

  //////////////////////////////////////////////////////////////////////////
  
  virtual pnint			_unserializeNode(xmlNode* node);
  virtual pnint			_serializeContent(xmlNode* node);

  virtual pnint			unserializeFromXML(xmlNode* node);

  //////////////////////////////////////////////////////////////////////////
  
  template<class _ListType>
  static pnint			findChoiseIndex(_ListType* list, const std::string& choise);
  pnint					findChoiseIndex(const std::string& choise);

  template<class _ListType>
  static std::string	findChoiseValue(_ListType* list, pnuint choise);
  std::string			findChoiseValue(pnuint choise);

  void				  	addToList(const std::string& value);

  //////////////////////////////////////////////////////////////////////////

  template<class _ListType>
  void					serializeList(_ListType* list, xmlNode* node);
  void					serializeList(xmlNode* node);
};

template<class _ListType>
inline pnint
PNConfigurableParameterList::findChoiseIndex(_ListType* list, const std::string& value)
{
  pnint choise = 0;

  for (typename _ListType::iterator it = list->begin(); it != list->end(); ++it, ++choise)
	if (value == toString(*it))
	  return choise;

  return -1;
}

template<class _ListType>
inline std::string
PNConfigurableParameterList::findChoiseValue(_ListType* list, pnuint index)
{
  for (typename _ListType::iterator it = list->begin(); it != list->end(); ++it, --index)
	if (index == 0)
	  return toString(*it);

  return "";
}

template<class _ListType>
inline void
PNConfigurableParameterList::serializeList(_ListType* list, xmlNode* node)
{
  for (typename _ListType::iterator it = list->begin(); it != list->end(); ++it)
  {
	xmlNodePtr valueNode = xmlNewChild(node, NULL, BAD_CAST PCF_PARAMV_XMLDTD_NAME.c_str(), NULL);

	if (PNObject::getClass(*it).size() >0)
	  xmlNewProp(valueNode, PCF_XMLPROP_CLASS, BAD_CAST PNObject::getClass(*it).c_str());

	xmlNewProp(valueNode, PCF_XMLPROP_DATA, BAD_CAST toString(*it).c_str());
  }
}

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNCONFIGURABLEPARAMETERLIST_HPP_*/
