/*
* PNFXCheckButtonParameter.cpp
* 
* Description :
* PNFXCheckButtonParameter definition
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

#include "pneditorcommon.h"
#include "pnproperties.h"

#include "PNFXCheckButtonParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXCheckButtonParameter) PNFXCheckButtonParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXCheckButtonParameter::ID_VALUE_CHANGED, PNFXCheckButtonParameter::onValueChanged)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXCheckButtonParameter, FXCheckButton, PNFXCheckButtonParameterMap, ARRAYNUMBER(PNFXCheckButtonParameterMap))

// Fixme : change text parameter
PNFXCheckButtonParameter::PNFXCheckButtonParameter(FXComposite* p, PNConfigurableParameter* param) 
: FXCheckButton(p, ""), PNPropertiesGridParameter(param)
{
  target = this;
  message = ID_VALUE_CHANGED;
}

PNFXCheckButtonParameter::~PNFXCheckButtonParameter()
{
}

void
PNFXCheckButtonParameter::create()
{
  FXCheckButton::create();

  updateParam();
}

void
PNFXCheckButtonParameter::updateParam()
{
  bool*	p = (bool*)_param->getElem();

  setCheck(*p);
}

void
PNFXCheckButtonParameter::apply()
{
  bool*	p = (bool*)_param->getElem();

  *p = getCheck() == TRUE;
  sendParamModif();
}

//////////////////////////////////////////////////////////////////////////

long
PNFXCheckButtonParameter::onValueChanged(FXObject* obj, FXSelector sel, void* data)
{
  apply();

  return 1;
}

//////////////////////////////////////////////////////////////////////////
};
