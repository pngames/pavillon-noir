/*
 * PNFXDirParameter.cpp
 * 
 * Description :
 * PNFXDirParameter definition
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

#include "PNFXDirParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXDirParameter) PNFXDirParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND,PNFXDirParameter::ID_BROWSE,PNFXDirParameter::onBrowse),
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXDirParameter,FXHorizontalFrame,PNFXDirParameterMap,ARRAYNUMBER(PNFXDirParameterMap))

PNFXDirParameter::PNFXDirParameter(FXComposite* p, PNConfigurableParameter* param)
: FXHorizontalFrame(p), PNPropertiesGridParameter(param)
{
  _field = new FXTextField(this, 24, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN|FRAME_THICK|LAYOUT_SIDE_TOP);
  _button = new FXButton(this, "Browse", NULL, this, 0,FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X|LAYOUT_CENTER_Y);
}

PNFXDirParameter::~PNFXDirParameter()
{
}

void
PNFXDirParameter::create()
{
  FXHorizontalFrame::create();

  _field->create();
  _button->create();

  update();
}

void 
PNFXDirParameter::update()
{
  string* str = (string*)_param->getElem();
  _field->setText(str->c_str());
  _field->setEditable(_param->isEditable());
}

long	
PNFXDirParameter::onBrowse(FXObject* obj,FXSelector sel, void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXDirParameter::onBrowse");
  FXDirDialog open(this, "Choose level directory to edit");

  if (open.execute())
  {
	_field->setText(open.getDirectory().text());
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
};
