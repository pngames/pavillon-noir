/*
* PNFXEventBoxParameter.cpp
* 
* Description :
* PNFXEventBoxParameter definition
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

#include "PNFXEventBoxParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXEventBoxParameter) PNFXEventBoxParameterMap[]={
  FXMAPFUNC(SEL_KEYRELEASE,0,PNFXEventBoxParameter::onKeyRelease),
  FXMAPFUNC(SEL_KEYPRESS,0,PNFXEventBoxParameter::onKeyPress),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,0,PNFXEventBoxParameter::onLeftBtnPress)
  //FXMAPFUNC(ID_,0,PNFXEventBoxParameter::onKeyPress)
  // changer le texte/la couleur lorsque l'on clique (LEFT_BTN)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXEventBoxParameter,FXTextField,PNFXEventBoxParameterMap,ARRAYNUMBER(PNFXEventBoxParameterMap))

PNFXEventBoxParameter::PNFXEventBoxParameter(FXComposite* p, PNConfigurableParameter* param)
: FXTextField(p, 5),
PNPropertiesGridParameter(param)
{
  _current_text = (string*)_param->getElem();
  setText(_current_text->c_str());
  this->setEditable(false);
  update();
}


PNFXEventBoxParameter::~PNFXEventBoxParameter()
{
}

void	PNFXEventBoxParameter::create()
{
  FXTextField::create();
}

void PNFXEventBoxParameter::update()
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXEventBoxParameter::onupdate()");
  string* str = (string*)_param->getElem();
  setText(str->c_str());
  return;
}

/*! \brief Called on left button press event
* Sets the text of the widget to "???" and sets the widget in "capture mode" 
* waiting for a keypress
*/
long	PNFXEventBoxParameter::onLeftBtnPress(FXObject* obj,FXSelector sel, void* ptr)
{
  FXTextField::handle(obj, sel, ptr);
  pnerror(PN_LOGLVL_DEBUG, "PNFXEventBoxParameter::onLeftBtnPress");
  setText("???");
  setTextColor(0x0000FF);
  _capture=true;
  return 1;
}

/*! \brief Called on key release event
* Sets the text of the widget to "???" and sets the widget in "capture mode" 
* waiting for a keypress
*/
long	PNFXEventBoxParameter::onKeyRelease(FXObject* obj,FXSelector sel, void* ptr)
{
  FXEvent* event=(FXEvent*)ptr;
  pnerror(PN_LOGLVL_DEBUG, "PNFXEventBoxParameter::onKeyRelease event->code=%i", event->code);

  string* elem = (std::string*)_param->getElem();
  switch(event->code)
  {
  case KEY_Escape:
	setText(_current_text->c_str());
	break;
  default:
	{
	  if (_capture==true)
	  {
		// on enregistre l'evenement (map toussa)
		FXString  fxstr;
		fxstr.format("%i", event->code);
		elem->clear();
		elem->append(fxstr.text());
		_current_text = elem;
	  }
	  break;
	}
  }
  setTextColor(0x000000);
  _capture=false;
  update();

  return 1;
}

//////////////////////////////////////////////////////////////////////////
};
