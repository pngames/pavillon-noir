/*
 * PNI3DAnimation.cpp
 * 
 * Description :
 * PNI3DAnimation definition
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

#include "PNI3DAnimation.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNI3DAnimation::PNI3DAnimation()
{

}

PNI3DAnimation::~PNI3DAnimation()
{

}

//////////////////////////////////////////////////////////////////////////

fs::path*
PNI3DAnimation::getFile()
{
  return &_path;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNI3DAnimation::getTotalTime()
{
  return _header.totalTime;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNI3DAnimation::unserialize(const fs::path& file)
{
  std::cout << "start unserialize " << file.native_file_string() << " : " << std::endl;

  _path = file;

  return PN3DAnimation::unserialize(file);
}

pnint
PNI3DAnimation::unserialize(std::istream& istm)
{
  int err = PNEC_SUCCES;

  if ((err = parseHeader(istm)) == 0)
	err = parseBody(istm);

  return err;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNI3DAnimation::setTransformation(pnint id, pnuint time, PNMatrixTR4f& transform)
{
  return _bones[id].setTransformation(time, transform);
}

pnbool
PNI3DAnimation::setRotation(pnint id, pnuint time, PNQuatf& rot)
{
  return _bones[id].setRotation(time, rot);
}

pnbool
PNI3DAnimation::setRotation(pnint id, pndouble rtime, const PNQuatf& lastRot, PNQuatf& rot)
{
  return _bones[id].setRotation(rtime, lastRot, rot);
}

pnbool
PNI3DAnimation::setPosition(pnint id, pnuint time, PNPoint& pos)
{
  return _bones[id].setPosition(time, pos);
}

pnbool
PNI3DAnimation::setPosition(pnint id, pndouble rtime, const PNPoint& lastPos, PNPoint& pos)
{
  return _bones[id].setPosition(rtime, lastPos, pos);
}

//////////////////////////////////////////////////////////////////////////
};
