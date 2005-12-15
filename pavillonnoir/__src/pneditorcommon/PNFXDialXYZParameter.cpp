/*
 * PNFXDialXYZParameter.cpp
 * 
 * Description :
 * PNFXDialXYZParameter definition
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
#include <sstream>

#include "pneditorcommon.hpp"
#include "pnproperties.h"

#include "PN3DObject.hpp"
#include "PNFXDialXYZParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

/*// Map
FXDEFMAP(PNFXDialXYZParameter) PNFXDialXYZParameterMap[]=
{
  FXMAPFUNC(SEL_UPDATE, 0, PNFXDialXYZParameter::onUpdate)
};*/

//////////////////////////////////////////////////////////////////////////
//FXIMPLEMENT(PNFXDialXYZParameter, FXHorizontalFrame, PNFXDialXYZParameterMap, ARRAYNUMBER(PNFXDialXYZParameterMap))
FXIMPLEMENT(PNFXDialXYZParameter, FXHorizontalFrame, NULL, 0)

PNFXDialXYZParameter::PNFXDialXYZParameter(FXComposite* p, PNConfigurableParameter* param)
: FXHorizontalFrame(p), PNPropertiesGridParameter(param)
{
  PN3DObject* o = (PN3DObject*)_param->getElem();
  _dial = new FXDial(this, NULL, 0, FRAME_SUNKEN  |  FRAME_THICK  |  DIAL_CYCLIC  |  
	DIAL_HORIZONTAL  |  LAYOUT_FIX_WIDTH  |  LAYOUT_FIX_HEIGHT  |  
	LAYOUT_CENTER_Y, 0, 0, 160, 14, 0, 0, 0, 0);
  _field = new FXTextField(this, 6, NULL, 0, TEXTFIELD_READONLY|FRAME_SUNKEN|FRAME_THICK|LAYOUT_SIDE_TOP);
  _oldValue = _dial->getValue();

  ostringstream oss;

  pnfloat x, y, z;
  o->getOrient().getDegrees(x, y, z);
  switch (_param->getType())
  {
  case PN_PARAMTYPE_DIALX:
	oss << x;
	break;
  case PN_PARAMTYPE_DIALY:
	oss << y;
	break;
  case PN_PARAMTYPE_DIALZ:
	oss << z;
	break;
  default:
	break;
  }

  _field->setText(oss.str().c_str());
}

PNFXDialXYZParameter::~PNFXDialXYZParameter()
{
  delete _dial;
  delete _field;
}


void	PNFXDialXYZParameter::create()
{
  FXHorizontalFrame::create();

  update();
}

void	PNFXDialXYZParameter::update()
{
  FXHorizontalFrame::update();

  pnfloat pos = (pnfloat)_dial->getValue();

  if (pos != _oldValue)
  {
	PN3DObject* o = (PN3DObject*)_param->getElem();

	ostringstream oss;

	pnfloat	  x, y, z;
	o->getOrient().getDegrees(x, y, z);
	switch (_param->getType())
	{
	case PN_PARAMTYPE_DIALX:
	  o->rotatePitchRadians(DEGREE_TO_RADIAN_F(pos - _oldValue));
	  oss << x;
	  break;
	case PN_PARAMTYPE_DIALY:
	  o->rotateYawRadians(DEGREE_TO_RADIAN_F(pos - _oldValue));
	  oss << y;
	  break;
	case PN_PARAMTYPE_DIALZ:
	  o->rotateRollRadians(DEGREE_TO_RADIAN_F(pos - _oldValue));
	  oss << z;
	  break;
	default:
	  break;
	}

	_oldValue = (pnint)pos;
	_field->setText(oss.str().c_str());
	_param->getConfigurableObject()->update(_param);
  }
}

//////////////////////////////////////////////////////////////////////////
};
