/*
 * s_parseBody.cpp
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

#include <map>

#include "pndefs.h"
#include "pnmath.h"

#include "PNI3DSkeleton.hpp"

using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

pnint	PNI3DSkeleton::parseBody(std::istream& istm)
{
  pnsBone_t*  tabBones = new pnsBone_t[_header.nbBones];

  istm.read((char*)tabBones, sizeof(*tabBones) * _header.nbBones);

  _bones.reserve(_header.nbBones);

  map<pnint, PNIBone*>  bonesMap;
  bonesMap[-1] = NULL;

  for (pnuint i = 0; i < _header.nbBones; ++i)
  {
	pnsBone_t&	bone = tabBones[i];

	_bones.push_back(PNIBone(bone, bonesMap[bone.parent]));

	bonesMap[bone.id] = &_bones.back();
  }

  delete[]	tabBones;

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
}
