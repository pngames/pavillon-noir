/*
 * PNFXStringListParameter.cpp
 * 
 * Description :
 * PNFXStringListParameter definition
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

#include "PNFXStringListParameter.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

/*// Map
FXDEFMAP(PNFXStringListParameter) PNFXStringListParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXStringListParameter::ID_LISTBOX_SEL, PNFXStringListParameter::onCmdListBox)
};*/

//////////////////////////////////////////////////////////////////////////
//FXIMPLEMENT(PNFXStringListParameter, PNFXListParameter, PNFXStringListParameterMap, ARRAYNUMBER(PNFXStringListParameterMap))
FXIMPLEMENT(PNFXStringListParameter, PNFXListParameter, NULL, 0)

PNFXStringListParameter::PNFXStringListParameter(FXComposite* p, PNConfigurableParameterList* param)
: PNFXListParameter(p, param)
{
  _labelsNumChars = 29;
}

PNFXStringListParameter::~PNFXStringListParameter()
{
  
}
//////////////////////////////////////////////////////////////////////////

void
PNFXStringListParameter::create()
{
  PNFXListParameter::create();
}

/*
*	Updates StringList
*/
void
PNFXStringListParameter::_update(void)
{
  std::list<std::string>* l = (std::list<std::string>*)_param->getElem();

  _listBox->clearItems();

  for (std::list<std::string>::iterator it = l->begin(); it != l->end(); it++)
  {
	std::string s = (*it);
	if (_labelsNumChars != 0 && _labelsNumChars != 0 && s.size() > (pnuint)_labelsNumChars)
	{	
	  int before = (_labelsNumChars-5)/5*2;
	  int after = _labelsNumChars-5-before;
	  s = s.substr(0, before) + "[...]" + s.substr(s.size()-after, s.size());
	}

	_listBox->appendItem(s.c_str(), NULL, NULL);
  }
}

//////////////////////////////////////////////////////////////////////////
};
