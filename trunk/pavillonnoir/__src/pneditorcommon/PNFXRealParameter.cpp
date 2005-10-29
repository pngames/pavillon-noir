/*
 * PNFXRealParameter.cpp
 * 
 * Description :
 * PNFXRealParameter definition
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

#include "PNFXRealParameter.hpp"

using namespace std;

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  // Map
  FXDEFMAP(PNFXRealParameter) PNFXRealParameterMap[]={
	FXMAPFUNC(SEL_KEYRELEASE,0,PNFXRealParameter::onKeyRelease),
  };

  //////////////////////////////////////////////////////////////////////////
  FXIMPLEMENT(PNFXRealParameter,FXTextField,PNFXRealParameterMap,ARRAYNUMBER(PNFXRealParameterMap))
 // FXIMPLEMENT(PNFXRealParameter,FXTextField,NULL,0)

	PNFXRealParameter::PNFXRealParameter(FXComposite* p, PNConfigurableParameter* param)
	: FXTextField(p, 12, NULL, 0, TEXTFIELD_REAL|FRAME_SUNKEN|FRAME_THICK|LAYOUT_SIDE_TOP)
  {
	_param = param;
	update();
  }

  PNFXRealParameter::~PNFXRealParameter()
  {

  }


  void	PNFXRealParameter::create()
  {
	FXTextField::create();
  }

  void	PNFXRealParameter::update()
  {
	FXString  str;
	str.format("%f", *(pnfloat*)_param->getElem());
	setText(str);
	setEditable(_param->isEditable());
	return;
  }


  long	PNFXRealParameter::onKeyRelease(FXObject* obj,FXSelector sel, void* ptr)
  {
	FXTextField::handle(obj, sel, ptr);
	FXEvent* event=(FXEvent*)ptr;
	switch(event->code)
	{
	  case KEY_Return:
	  case KEY_KP_Enter:
	  {
		pnfloat* f = (pnfloat*)_param->getElem();
		*f = atof(getText().text());
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
