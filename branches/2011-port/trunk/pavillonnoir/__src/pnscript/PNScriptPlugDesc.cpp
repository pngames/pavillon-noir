/*
 * PNScriptPlugDesc.cpp
 * 
 * Description :
 * 
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
#include "pnplugins.h"
#include "pnevent.h"

#include "PNScriptPlugDesc.hpp"
#include "PNLuaGame.hpp"

using namespace PN;

PNInterface*	PNScriptPlugDesc::getInterface(pnuint id)
{
  if (_gameInterface == NULL)
	_gameInterface = new PNLuaGame();

  return ((PNInterface*)_gameInterface); 
}

pnuint			PNScriptPlugDesc::getNbInterface()
{
  return 1;
}

void			init()
{
}

//////////////////////////////////////////////////////////////////////////

const pnchar*	PNScriptPlugDesc::getName()
{
  return "script";
}

pnuint			PNScriptPlugDesc::getVersion()
{
  return 001;
}

PNScriptPlugDesc::PNScriptPlugDesc()
{
  this->_gameInterface = NULL;
}

PNScriptPlugDesc::~PNScriptPlugDesc()
{
}
