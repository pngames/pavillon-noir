/*
 * PNI3DSkeleton.cpp
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

#include <iostream>

#include "pndefs.h"
#include "pnmath.h"
#include "pnrender.h"

#include "PNI3DSkeleton.hpp"
#include "PN3DAnimation.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNI3DSkeleton::PNI3DSkeleton()
{
  
}

PNI3DSkeleton::~PNI3DSkeleton()
{
  
}

//////////////////////////////////////////////////////////////////////////

fs::path*
PNI3DSkeleton::getFile()
{
  return &_path;
}

const PNMatrixTR4f&
PNI3DSkeleton::getMatrix(pnuint id) const
{
  return _bones[id].getFinal();
}

//////////////////////////////////////////////////////////////////////////

void
PNI3DSkeleton::render()
{
  _robject->render();
}

pnbool
PNI3DSkeleton::update(pnuint time, PN3DAnimation* anim)
{
  if (anim != NULL && anim->getTotalTime() < time)
	return false;

  for (BoneList::iterator it = _bones.begin(); it != _bones.end(); ++it)
  {
	it->update(time, anim);
	memcpy (_vertBuffer[it->getId()], it->getCourse().getMatrix() + 12, sizeof(pnpoint3f));
  }

  return true;
}

pnbool
PNI3DSkeleton::update(pndouble rtime, PN3DAnimation* anim)
{
  for (BoneList::iterator it = _bones.begin(); it != _bones.end(); ++it)
  {
	it->update(rtime, anim);
	memcpy (_vertBuffer[it->getId()], it->getCourse().getMatrix() + 12, sizeof(pnpoint3f));
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNI3DSkeleton::unserialize(const fs::path& file)
{
  std::cout << "start unserialize " << file.native_file_string() << " : " << std::endl;

  _path = file;

  return PN3DSkeleton::unserialize(file);
}

pnint
PNI3DSkeleton::unserialize(std::istream& istm)
{
  int err = PNEC_SUCCES;

  if ((err = parseHeader(istm)) == 0)
	err = parseBody(istm);

  _vertBuffer = new pnpoint3f[_header.nbBones];
  _idBuffer = new pnpoint2ui[_header.nbBones];

  _robject = PNRendererInterface::getInstance()->newObj(
	(pnfloat*)_vertBuffer, NULL, NULL, NULL, _header.nbBones, (pnuint*)_idBuffer, _header.nbBones * 2, PN_LINES);

  int i = 0;
  for (BoneList::iterator it = _bones.begin(); it != _bones.end(); ++it, ++i)
  {
	memcpy (_vertBuffer[it->getId()], it->getCourse().getMatrix() + 12, sizeof(pnpoint3f));

	_idBuffer[i][0] = it->getId();
	if (it->getParent() != NULL)
	  _idBuffer[i][1] = it->getParent()->getId();
	else
	  _idBuffer[i][1] = it->getId();
  }

  return err;
}

//////////////////////////////////////////////////////////////////////////
};
