/*
 * PNOpalPlugDesc.cpp
 * 
 * Description :
 * PNOpalPlugDesc definition
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

#include "PNOpalPlugDesc.hpp"

namespace PN {

PNInterface*	PNOpalPlugDesc::getInterface(pnuint id)
{
  switch (id)
  {
  case 0:
	  if (_physicsInterface == NULL)
		  _physicsInterface = new PNOpal();
	  return (PNInterface*)_physicsInterface;
  case 1:
	  if (_importerInterface == NULL)
		  _importerInterface = new PNOpalImporter();
	  return (PNInterface*)_importerInterface;
  }

  return NULL;
}

pnuint			PNOpalPlugDesc::getNbInterface()
{
  return 2;
}

//////////////////////////////////////////////////////////////////////////

PNOpalPlugDesc::PNOpalPlugDesc() : _physicsInterface(NULL), _importerInterface(NULL)
{
}

PNOpalPlugDesc::~PNOpalPlugDesc()
{
  if (_physicsInterface != NULL)
	delete _physicsInterface;
  if (_importerInterface != NULL)
	delete _importerInterface;
}

}
