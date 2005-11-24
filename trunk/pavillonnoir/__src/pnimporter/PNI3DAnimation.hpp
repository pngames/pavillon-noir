/*
 * PNI3DAnimation.hpp
 * 
 * Description :
 * PNI3DAnimation declaration
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

#ifndef _PNI3DANIMATION_HPP_
# define _PNI3DANIMATION_HPP_

#include <vector>

#include "PN3DAnimation.hpp"

#include "PNIAnimationBone.hpp"

#include "pna_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNMatrixTR4f;

class						PNI3DAnimation : public PN3DAnimation
{
private:
  typedef std::vector<PNIAnimationBone>	BoneList;
  BoneList					_bones;

  pnaHeader_t				_header;
public:
  PNI3DAnimation();
  ~PNI3DAnimation();

  //////////////////////////////////////////////////////////////////////////
  // PN3DModel
  
  pnuint					getTotalTime();

  //////////////////////////////////////////////////////////////////////////

  pnint						unserializeFromStream(std::istream& i);

  //////////////////////////////////////////////////////////////////////////
  
  pnuint					setTransformation(pnint id, pnuint time, PNMatrixTR4f& transform);

  pnbool					setRotation(pnint id, pnuint time, PNQuatf& rot);
  pnbool					setRotation(pnint id, pndouble rtime, const PNQuatf& lastRot, PNQuatf& rot);
  pnbool					setPosition(pnint id, pnuint time, PNPoint3f& pos);
  pnbool					setPosition(pnint id, pndouble rtime, const PNPoint3f& lastPos, PNPoint3f& pos);

  //////////////////////////////////////////////////////////////////////////

  pnint						parseHeader(std::istream& istm);
  pnint						parseBody(std::istream& istm);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNI3DANIMATION_HPP_*/
