/*
 * PNConfigurableParameterList.cpp
 * 
 * Description :
 * PNConfigurableParameterList definition
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

#include <list>

#include "pndefs.h"

#include "PNConfigurableParameterList.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNConfigurableParameterList::PNConfigurableParameterList(PNConfigurableObject* p, 
														 pnlistparamtype type, 
														 void* elem, 
														 const string& label, 
														 const string& altText,
														 pnbool choosable/* = true*/,
														 pnbool editable,
														 void* max,
														 void* min) :
PNConfigurableParameter(p, (pnparamtype)type, elem, label, altText, editable, max, min),
_choosable(choosable), _choise(0)
{
}

PNConfigurableParameterList::~PNConfigurableParameterList()
{
}

//////////////////////////////////////////////////////////////////////////

pnbool
PNConfigurableParameterList::isChoosable()
{
  return _editable;
}

void
PNConfigurableParameterList::setChoosable(pnbool choosable)
{
  _choosable = choosable;
}

void
PNConfigurableParameterList::setChoise(pnuint choise)
{
  _choise = choise;
}

pnuint
PNConfigurableParameterList::getChoise()
{
  return _choise;
}

//////////////////////////////////////////////////////////////////////////

pnint		
PNConfigurableParameterList::getElementList(pnint def)
{
  std::list<pnint>*	lst = (std::list<pnint>*)_elem;
  std::list<pnint>::iterator	it = lst->begin();
  for (int i = 0; it != lst->end(); ++i, ++it)
  {
	if  (i == _choise)
	{
	  return *it;
	}
  }

  return def;
}

pnuint	
PNConfigurableParameterList::getElementList(pnuint def)
{
  std::list<pnuint>*	lst = (std::list<pnuint>*)_elem;
  std::list<pnuint>::iterator	it = lst->begin();
  for (int i = 0; it != lst->end(); ++i, ++it)
  {
	if  (i == _choise)
	{
	  return *it;
	}
  }

  return def;
}

pnfloat
PNConfigurableParameterList::getElementList(pnfloat def)
{
  std::list<pnfloat>*	lst = (std::list<pnfloat>*)_elem;
  std::list<pnfloat>::iterator	it = lst->begin();
  for (int i = 0; it != lst->end(); ++i, ++it)
  {
	if  (i == _choise)
	{
	  return *it;
	}
  }

  return def;
}

//////////////////////////////////////////////////////////////////////////
};
