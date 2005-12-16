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

  update();
}

void
PNFXTextFieldParameter::update()
{
  FXString  str;

  string*	truc = (string*)_param->getElem();

  switch (_param->getType())
  {
  case PN_PARAMTYPE_STRING:
	str = ((string*)_param->getElem())->c_str();
	break;
  case PN_PARAMTYPE_INT:
	str.format("%i", *(int*)_param->getElem());
	break;
  case PN_PARAMTYPE_REAL:
	str.format("%f", *(pnfloat*)_param->getElem());
	break;
  default:
	break;
  }

  setText(str);
  setEditable(_param->isEditable());
}

void
PNFXTextFieldParameter::updateParam()
{
  switch (_param->getType())
  {
  case PN_PARAMTYPE_STRING:
	*(std::string*)_param->getElem() = getText().text();
	break;
  case PN_PARAMTYPE_INT:
	*(pnint*)_param->getElem() = atoi(getText().text());
	break;
  case PN_PARAMTYPE_REAL:
	*(pnfloat*)_param->getElem() = (pnfloat)atof(getText().text());
	break;
  default:
	break;
  }
}

//////////////////////////////////////////////////////////////////////////

long
PNFXTextFieldParameter::onValueValidated(FXObject*, FXSelector, void* ptr)
{
  updateParam();
  sendParamModif();

  setTextColor(0x000000);

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
