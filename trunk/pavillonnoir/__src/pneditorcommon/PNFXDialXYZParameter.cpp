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

// Map
FXDEFMAP(PNFXDialXYZParameter) PNFXDialXYZParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXDialXYZParameter::ID_VALUE_CHANGED, PNFXDialXYZParameter::onValueChanged),
  FXMAPFUNC(SEL_CHANGED, PNFXDialXYZParameter::ID_VALUE_CHANGED, PNFXDialXYZParameter::onValueChanged)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXDialXYZParameter, FXHorizontalFrame, PNFXDialXYZParameterMap, ARRAYNUMBER(PNFXDialXYZParameterMap))
//FXIMPLEMENT(PNFXDialXYZParameter, FXHorizontalFrame, NULL, 0)

PNFXDialXYZParameter::PNFXDialXYZParameter(FXComposite* p, PNConfigurableParameter* param)
: FXHorizontalFrame(p), PNPropertiesGridParameter(param)
{
  _intTarget.connect(_int);
  _intTarget.setTarget(this);
  _intTarget.setSelector(ID_VALUE_CHANGED);
  
  _field = new FXTextField(this, 6, &_intTarget, FXDataTarget::ID_VALUE, TEXTFIELD_REAL|FRAME_SUNKEN|FRAME_THICK|LAYOUT_SIDE_TOP);
  _dial = new FXDial(this, &_intTarget, FXDataTarget::ID_VALUE, LAYOUT_CENTER_Y|LAYOUT_FILL_ROW|LAYOUT_FIX_WIDTH|DIAL_HORIZONTAL|DIAL_HAS_NOTCH, 0, 0, 160, 14, 0, 0, 0, 0);

  _oldValue = _dial->getValue();
}

PNFXDialXYZParameter::~PNFXDialXYZParameter()
{
  delete _dial;
  delete _field;
}

void
PNFXDialXYZParameter::create()
{
  FXHorizontalFrame::create();

  updateParam();
}

void
PNFXDialXYZParameter::updateParam()
{
  PN3DObject* o = (PN3DObject*)_param->getElem();

  pnfloat x, y, z;
  o->getOrient().getDegrees(x, y, z);
  switch (_param->getType())
  {
  case PN_PARAMTYPE_DIALX:
	_int = (int)x;
	break;
  case PN_PARAMTYPE_DIALY:
	_int = (int)y;
	break;
  case PN_PARAMTYPE_DIALZ:
	_int = (int)z;
	break;
  default:
	break;
  }

  _intTarget.onUpdValue(this, 0, NULL);
}

void
PNFXDialXYZParameter::apply()
{
  if (_int != _oldValue)
  {
	PN3DObject* o = (PN3DObject*)_param->getElem();

	switch (_param->getType())
	{
	case PN_PARAMTYPE_DIALX:
	  o->rotatePitchRadians(DEGREE_TO_RADIAN_F(_int - _oldValue));
	  break;
	case PN_PARAMTYPE_DIALY:
	  o->rotateYawRadians(DEGREE_TO_RADIAN_F(_int - _oldValue));
	  break;
	case PN_PARAMTYPE_DIALZ:
	  o->rotateRollRadians(DEGREE_TO_RADIAN_F(_int - _oldValue));
	  break;
	default:
	  break;
	}

	_oldValue = _int;
	sendParamModif();
  }
}

long
PNFXDialXYZParameter::onValueChanged(FXObject*, FXSelector, void*)
{
  apply();

  return 0;
}

//////////////////////////////////////////////////////////////////////////
};
