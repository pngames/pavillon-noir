/*
 * PNConfigurableParameter.hpp
 * 
 * Description :
 * PNConfigurableParameter declaration
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

#ifndef _PNCONFIGURABLEPARAMETER_HPP_
# define _PNCONFIGURABLEPARAMETER_HPP_

#include <string>

//////////////////////////////////////////////////////////////////////////

#include "PNObject.hpp"
#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////	

typedef enum
{
  PN_PARAMTYPE_SEPARATOR = -1,

  PN_PARAMTYPE_INT,			// based on pnint
  PN_PARAMTYPE_UINT,		// based on pnuint
  PN_PARAMTYPE_REAL,		// based on pnfloat
  PN_PARAMTYPE_STRING,		// based on std::string
  PN_PARAMTYPE_FILE,		// based on std::string
  PN_PARAMTYPE_DIR,			// based on std::string
  PN_PARAMTYPE_LINK,
  PN_PARAMTYPE_DIALX,		// based on pnfloat
  PN_PARAMTYPE_DIALY,		// based on pnfloat
  PN_PARAMTYPE_DIALZ,		// based on pnfloat
  PN_PARAMTYPE_BOOLEAN,		// based on pnbool
  PN_PARAMTYPE_EVENTBOX,	// based on std::string
  PN_PARAMTYPE_MATERIAL,	// based on PN3DMaterial*

  PN_PARAMTYPE_SCRIPTLIST,

  PN_NB_PARAMTYPE			// number of parameters
} pnparamtype;

//////////////////////////////////////////////////////////////////////////

class PNConfigurableObject;

class PNAPI						PNConfigurableParameter : public PNObject, public IPNXMLSerializable
{
public:
  typedef enum
  {
	S_VALUE = 0x000001,
	LAST_S = S_VALUE << 1
  } serializable;
protected:
  PNConfigurableObject*			_p;
  pnparamtype					_type;

  std::string					_name;
  void*							_elem;
  void*							_max;
  void*							_min;

  std::string					_label;
  std::string					_altText;
  pnbool						_editable;

  pnbool						_enableSetModified;

  pnuint						_serialization;

protected:
  PNConfigurableParameter(PNConfigurableObject* p, pnparamtype type, const std::string& label, const std::string& altText, pnbool editable = true, void* max = NULL, void* min = NULL, pnbool enableSetModified = false);

  void							_init(PNConfigurableObject* p, pnparamtype type, void* elem, const std::string& label, const std::string& altText, pnbool editable, void* max, void* min, pnbool enableSetModified);
public:
  PNConfigurableParameter(PNConfigurableObject* p, pnparamtype type, void* elem, const std::string& label, const std::string& altText, pnbool editable = true, void* max = NULL, void* min = NULL, pnbool enableSetModified = false);
  virtual ~PNConfigurableParameter();

  pnparamtype					getType();

  void*							getElem();
  void*							getMax();
  void*							getMin();

  const std::string&			getName();
  const std::string&			getLabel();
  const std::string&			getAltText();
  pnbool						isEditable();

  PNConfigurableObject*			getConfigurableObject();
  void							setConfigurableObject(PNConfigurableObject* object);

  void							enableSetModified(pnbool modified);
  void							setModified();

  //////////////////////////////////////////////////////////////////////////
  
  void							setSerializable(serializable option);
  void							unsetSerializable(serializable option);

  //////////////////////////////////////////////////////////////////////////
  
  virtual std::string			toString();
  virtual void					fromString(const std::string& str);

  //////////////////////////////////////////////////////////////////////////
  
  static std::string			toString(pnbool value);
  static std::string			toString(pnint value);
  static std::string			toString(pnuint value);
  static std::string			toString(pnfloat value);
  static std::string			toString(const std::string& value);
  static std::string			toString(PNObject* value);

  static void					fromString(pnbool* value, const std::string& str);
  static void					fromString(pnint* value, const std::string& str);
  static void					fromString(pnuint* value, const std::string& str);
  static void					fromString(pnfloat* value, const std::string& str);
  static void					fromString(std::string* value, const std::string& str);
  static void					fromString(PNObject** value, const std::string& str);

  //////////////////////////////////////////////////////////////////////////
  
public:
  virtual PNObject*				getObjectByClass(const std::string& name);

  //////////////////////////////////////////////////////////////////////////

  virtual const std::string&	getDTDName() const;
  virtual const std::string&	getRootNodeName() const;

protected:
  virtual pnint					_unserializeNode(xmlNode* node);
  virtual pnint					_serializeContent(xmlNode* node);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNCONFIGURABLEPARAMETER_HPP_*/

