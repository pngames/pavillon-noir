/*
 * s_parseHeader.cpp
 * 
 * Description :
 * PNI3DSkeleton definition
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
#include "pnmath.h"

#include "PNI3DSkeleton.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

int	  PNI3DSkeleton::parseHeader(std::istream& istm)
{
  istm.read((char*)&_header, sizeof(_header));

  if (strncmp(_header.magic, PNS_MAGIC, PNS_MAGIC_SIZE) != 0)
	return PNEC_FILETYPE_INVALID;

  std::cout << "magic : " << _header.magic << std::endl;
  std::cout << "version : " << _header.version << std::endl;

  std::cout << "nbBones : " << _header.nbBones << std::endl;

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
}
