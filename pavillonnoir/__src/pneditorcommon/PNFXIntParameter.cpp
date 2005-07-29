/*
 * PNFXIntParameter.cpp
 * 
 * Description :
 * PNFXIntParameter definition
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

#include "pneditorcommon.hpp"
#include "pnproperties.h"

#include "PNFXIntParameter.hpp"

using namespace std;

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  // Map
  FXDEFMAP(PNFXIntParameter) PNFXIntParameterMap[]={
	FXMAPFUNC(SEL_KEYRELEASE,0,PNFXIntParameter::onKeyRelease),
  };

  //////////////////////////////////////////////////////////////////////////
  //FXIMPLEMENT(PNFXIntParameter,FXTextField,PNFXIntParameterMap,ARRAYNUMBER(PNFXIntParameterMap))
  FXIMPLEMENT(PNFXIntParameter,FXTextField,NULL,0)

	PNFXIntParameter::PNFXIntParameter(FXComposite* p, PNConfigurableParameter* param)
	: FXTextField(p, 12, NULL, 0, TEXTFIELD_INTEGER|TEXTFIELD_ENTER_ONLY)
  {
	_param = param;
	update();
  }

  PNFXIntParameter::~PNFXIntParameter()
  {
  }

  void	PNFXIntParameter::create()
  {
	FXTextField::create();
  }

  void PNFXIntParameter::update()
  {
	FXString  str;
	str.format("%i", *(int*)_param->getElem());
	setText(str);
	setEditable(_param->isEditable());
	return;
  }

  long	PNFXIntParameter::onKeyRelease(FXObject* obj,FXSelector sel, void* ptr)
  {
	FXTextField::handle(obj, sel, ptr);
	FXEvent* event=(FXEvent*)ptr;
	switch(event->code)
	{
	case KEY_Return:
	case KEY_KP_Enter:
	  {
		pnint* i = (pnint*)_param->getElem();
		*i = atoi(getText().text());
		_param->getConfigurableObject()->update(_param);
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
