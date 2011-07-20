/*
 * PNFXVPPNObjectParameter.cpp
 * 
 * Description :
 * PNFXVPPNObjectParameter definition
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

#include "PNPropertiesGrid.hpp"

#include "PNFXVPPNObjectParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

/*// Map
FXDEFMAP(PNFXVPPNObjectParameter) PNFXVPPNObjectParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXVPPNObjectParameter::ID_LISTBOX_SEL, PNFXVPPNObjectParameter::onCmdListBox)
};*/

//////////////////////////////////////////////////////////////////////////
//FXIMPLEMENT(PNFXVPPNObjectParameter, PNFXListParameter, PNFXVPPNObjectParameterMap, ARRAYNUMBER(PNFXVPPNObjectParameterMap))
FXIMPLEMENT(PNFXVPPNObjectParameter, PNFXListParameter, NULL, 0)

PNFXVPPNObjectParameter::PNFXVPPNObjectParameter(FXComposite* p, PNConfigurableParameterList* param)
: PNFXListParameter(p, param)
{
}

PNFXVPPNObjectParameter::~PNFXVPPNObjectParameter()
{
  
}
//////////////////////////////////////////////////////////////////////////

void
PNFXVPPNObjectParameter::create()
{
  PNFXListParameter::create();
}

/*
*	Updates StringList
*/
void
PNFXVPPNObjectParameter::_update(void)
{
  PNVPPNObjectParameter*  list = (PNVPPNObjectParameter*)_param->getElem();

  _listBox->clearItems();

  for (PNVPPNObjectParameter::iterator it = list->begin(); it != list->end(); ++it)
  {
	PNObject*	object = *it;

	_listBox->appendItem(object->toString().c_str());
  }
}

bool
PNFXVPPNObjectParameter::_deleteObject(FXint index)
{
  PNVPPNObjectParameter*  list = (PNVPPNObjectParameter*)_param->getElem();

  list->erase(list->begin() + index);

  return true;
}

bool
PNFXVPPNObjectParameter::_addNewObject(FXint index)
{
  return false;
}

//////////////////////////////////////////////////////////////////////////
};
