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

#ifndef _PN_CONFIGURABLE_PARAMETER_HPP_
# define _PN_CONFIGURABLE_PARAMETER_HPP_

#include <string>
#include "pndefs.h" // /!\ normalement inutile mais pas de compilation sans

namespace PN
{
//////////////////////////////////////////////////////////////////////////	

typedef enum
{
  PN_PARAMTYPE_INT,
  PN_PARAMTYPE_REAL,
  PN_PARAMTYPE_STRING,
  PN_PARAMTYPE_ACTIVESTRING,
  PN_PARAMTYPE_FILE,
  PN_PARAMTYPE_DIR,
  PN_PARAMTYPE_LINK,
  PN_PARAMTYPE_DIALX,
  PN_PARAMTYPE_DIALY,
  PN_PARAMTYPE_DIALZ,
  PN_PARAMTYPE_CHECKBOX,

  PN_PARAMTYPE_INTLIST,
  PN_PARAMTYPE_REALLIST,
  PN_PARAMTYPE_STRINGLIST,
  PN_PARAMTYPE_FILELIST,
  PN_PARAMTYPE_DIRLIST,
  PN_PARAMTYPE_LINKLIST,
  PN_PARAMTYPE_MATERIALLIST,
  PN_PARAMTYPE_ANIMLIST,
  PN_PARAMTYPE_SCRIPTLIST
} pnparamtype;

//////////////////////////////////////////////////////////////////////////

class PNConfigurableObject;

class PNAPI				PNConfigurableParameter
{
protected:
  PNConfigurableObject*	_p;
  pnparamtype			_type;
  void*					_elem;
  std::string			_label;
  std::string			_altText;
  bool					_editable;

public:
  PNConfigurableParameter(PNConfigurableObject* p, pnparamtype type, void* elem, const std::string& label, const std::string& altText, bool editable = true);
  virtual ~PNConfigurableParameter();

  pnparamtype			getType();
  void*					getElem();
  const std::string&	getLabel();
  const std::string&	getAltText();
  bool					isEditable();
  PNConfigurableObject*	getConfigurableObject();

  // for tests only
  void					dump();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PN_CONFIGURABLE_PARAMETER_HPP_*/