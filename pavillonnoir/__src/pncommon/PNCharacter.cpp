/*
 * PNCharacter.cpp
 * 
 * Description :
 * PNCharacter definition
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

#include "pndefs.h"
#include "PNWayPoint.hpp"
#include "PNCharacter.hpp"

namespace fs = boost::filesystem;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNCharacter::PNCharacter() : _pf(_coord)
{
  _state = PN_IA_PASSIVE;
  _hurry = false;
  _objType = OBJTYPE_CHARACTER;
}

PNCharacter::~PNCharacter()
{
}

void
PNCharacter::buildGraph(fs::path& file)
{
  _pf.unserializeFromFile(file);
}

void
PNCharacter::beSmart()
{
  // set hurry or not
  pnerror(PN_LOGLVL_DEBUG, "I'm C++smart !");
  if (_state == PN_IA_TRAVELLING)
  {
	if (_coord == _toReach.getCoord())
	{
	  _pf.moveNext(_toReach);
	  if (_coord == _toReach.getCoord())
	  {
		restoreState();
		return;
	  }
	  //setDirect and rotate
	}
	else
	{
	  //Walk doooooooooown !
	}
  }
}

void
PNCharacter::moveTo(PNPoint &p)
{
  setState(PN_IA_TRAVELLING);
  _pf.moveTo(p);
  _pf.moveNext(_toReach);
  //setDirect and rotate
}

void
PNCharacter::moveTo(PNWayPoint *wp)
{
  setState(PN_IA_TRAVELLING);
  _pf.moveTo(wp);
  _pf.moveNext(_toReach);
  //setDirect and rotate
}

void
PNCharacter::hear()
{
}

void
PNCharacter::see()
{
}

void
PNCharacter::startFight()
{
}

void
PNCharacter::manageFight()
{
}

void
PNCharacter::setState(pnIAState st)
{
  _pastStates.push(_state);
  _state = st;
}

void
PNCharacter::restoreState()
{
  _state = _pastStates.top();
  _pastStates.pop();
}

//////////////////////////////////////////////////////////////////////////
};
