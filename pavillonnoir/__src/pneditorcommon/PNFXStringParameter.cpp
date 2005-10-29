/*
 * PNFXStringParameter.cpp
 * 
 * Description :
 * PNFXStringParameter definition
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

#include "PNFXStringParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXStringParameter) PNFXStringParameterMap[]={
  FXMAPFUNC(SEL_KEYRELEASE,0,PNFXStringParameter::onKeyRelease),
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXStringParameter,FXTextField,PNFXStringParameterMap,ARRAYNUMBER(PNFXStringParameterMap))

PNFXStringParameter::PNFXStringParameter(FXComposite* p, PNConfigurableParameter* param)
: FXTextField(p, 25)
{
  _param = param;
  update();
}


PNFXStringParameter::~PNFXStringParameter()
{
}

void	PNFXStringParameter::create()
{
  FXTextField::create();
}

void PNFXStringParameter::update()
{
  string* str = (string*)_param->getElem();
  setText(str->c_str());
  setEditable(_param->isEditable());

  return;
}

long	PNFXStringParameter::onKeyRelease(FXObject* obj,FXSelector sel, void* ptr)
{
  FXTextField::handle(obj, sel, ptr);
  FXEvent* event=(FXEvent*)ptr;
  switch(event->code)
  {
  case KEY_Return:
  case KEY_KP_Enter:
	{
	  std::string* s = (std::string*)_param->getElem();
	  s->clear();
	  s->append(getText().text());
	  setTextColor(0x000000);
	  return 1;
	}
  case KEY_Right:
  case KEY_KP_Right:
  case KEY_Left:
  case KEY_KP_Left:
  case KEY_Down:
  case KEY_KP_Down:
  case KEY_Up:
  case KEY_KP_Up:
  case KEY_Home:
  case KEY_KP_Home:
  case KEY_End:
  case KEY_KP_End:
  case KEY_Insert:
  case KEY_KP_Insert:
	return 1;
  default:
	{
	  setTextColor(0x0000FF);
	  return 1;
	}
  }
}

//////////////////////////////////////////////////////////////////////////
};
