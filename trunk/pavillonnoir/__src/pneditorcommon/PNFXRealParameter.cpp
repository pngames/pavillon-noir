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

/*// Map
FXDEFMAP(PNFXRealParameter) PNFXRealParameterMap[]={
  FXMAPFUNC(SEL_KEYRELEASE,0,PNFXRealParameter::onKeyRelease),
};*/

//////////////////////////////////////////////////////////////////////////
//FXIMPLEMENT(PNFXRealParameter, PNFXTextFieldParameter, PNFXRealParameterMap, ARRAYNUMBER(PNFXRealParameterMap))
FXIMPLEMENT(PNFXRealParameter, PNFXTextFieldParameter, NULL, 0)

PNFXRealParameter::PNFXRealParameter(FXComposite* p, PNConfigurableParameter* param)
: PNFXTextFieldParameter(p, param, 12)
{ 
}

PNFXRealParameter::~PNFXRealParameter()
{
}


void	PNFXRealParameter::create()
{
  PNFXTextFieldParameter::create();
}

//////////////////////////////////////////////////////////////////////////
};
