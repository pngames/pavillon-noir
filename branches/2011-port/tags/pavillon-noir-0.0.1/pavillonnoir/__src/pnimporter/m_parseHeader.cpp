/*
 * m_parseHeader.cpp
 * 
 * Description :
 * PNI3DModel definition
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

#include "PNI3DModel.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

pnint	  PNI3DModel::parseHeader()
{
  _istream->read((char*)&_header, sizeof(_header));
  
  if (strncmp(_header.magic, PNM_MAGIC, PNM_MAGIC_SIZE) != 0)
  	return PNEC_FILETYPE_INVALID;

  std::cout << "magic : " << _header.magic << std::endl;
  std::cout << "version : " << _header.version << std::endl;

  std::cout << "SupportedBones : " << _header.nbSupportedBones << std::endl;
  std::cout << "SupportedMaterials : " << _header.nbSupportedMaterials << std::endl;

  std::cout << "nbVerts : " << _header.nbVerts << std::endl;

  std::cout << "nbMeshes : " << _header.nbMeshes << std::endl;

  return PNEC_SUCCES;
}

//////////////////////////////////////////////////////////////////////////
}
