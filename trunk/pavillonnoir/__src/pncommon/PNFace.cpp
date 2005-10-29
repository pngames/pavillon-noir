/*
 * PNFace.cpp
 * 
 * Description :
 * PNFace definition
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

#include <string.h>

#include "pndefs.h"
#include "pnmath.h"

#include "PNFace.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNFace::PNFace(void)
{
}

PNFace::~PNFace(void)
{
}

//////////////////////////////////////////////////////////////////////////

void	PNFace::set(pnuint id0, pnuint id1, pnuint id2)
{
  memcpy(&v0, &id0, sizeof(pnpoint3ui));
}

void	PNFace::setMaterial(PN3DMaterial* mat)
{
  _mat = mat;
}

PN3DMaterial*
PNFace::getMaterial()
{
  return _mat;
}

//////////////////////////////////////////////////////////////////////////
}
