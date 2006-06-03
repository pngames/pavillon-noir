/*
 * PNFXTextFieldParameter.cpp
 * 
 * Description :
 * PNFXTextFieldParameter definition
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


#include <iostream>

#include <fxkeys.h>

#include "pneditorcommon.h"
#include "pnproperties.h"

#include "PNFXTextFieldParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXTextFieldParameter) PNFXTextFieldParameterMap[]=
{
  FXMAPFUNC(SEL_CHANGED, PNFXTextFieldParameter::ID_VALUE_CHANGED, PNFXTextFieldParameter::onValueChanged),
  FXMAPFUNC(SEL_COMMAND, PNFXTextFieldParameter::ID_VALUE_CHANGED, PNFXTextFieldParameter::onValueValidated)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT_ABSTRACT(PNFXTextFieldParameter, FXTextField, PNFXTextFieldParameterMap, ARRAYNUMBER(PNFXTextFieldParameterMap))

PNFXTextFieldParameter::PNFXTextFieldParameter(FXComposite* p, PNConfigurableParameter* param, FXint ncols, FXObject* tgt/*= NULL*/, FXSelector sel/*= 0*/, FXuint opts/*= TEXTFIELD_NORMAL*/)
: FXTextField(p, ncols, tgt, sel, opts),
PNPropertiesGridParameter(param)
{
  target = this;
  message = ID_VALUE_CHANGED;

  switch (_param->getType())
  {
  case PN_PARAMTYPE_INT:
  case PN_PARAMTYPE_UINT:
	options |= TEXTFIELD_INTEGER;
	break;
  case PN_PARAMTYPE_REAL:
	options |= TEXTFIELD_REAL;
	break;
  default:
	break;
  }
}

PNFXTextFieldParameter::~PNFXTextFieldParameter()
{
}

void
PNFXTextFieldParameter::create()
{
  FXTextField::create();

  updateParam();
}

void
PNFXTextFieldParameter::updateParam()
{
  setText(toString().c_str());
  setEditable(_param->isEditable());
}

void
PNFXTextFieldParameter::apply()
{
  _apply();
  sendParamModif();

  setTextColor(0x000000);
}

void
PNFXTextFieldParameter::_apply()
{
  fromString(getText().text());
}

//////////////////////////////////////////////////////////////////////////

long
PNFXTextFieldParameter::onValueValidated(FXObject*, FXSelector, void* ptr)
{
  apply();

  return 1;
}

long
PNFXTextFieldParameter::onValueChanged(FXObject*, FXSelector, void* ptr)
{
  setTextColor(0x0000FF);

  return 1;
}

//////////////////////////////////////////////////////////////////////////
};
