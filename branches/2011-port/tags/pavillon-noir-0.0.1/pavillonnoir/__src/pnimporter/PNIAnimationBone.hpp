/*
 * PNIAnimationBone.hpp
 * 
 * Description :
 * PNIAnimationBone declaration
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

#ifndef _PNI3DANIMATIONBONE_HPP_
# define _PNI3DANIMATIONBONE_HPP_

#include <vector>
#include <iostream>

#include "PNObject.hpp"
#include "PNPoint.hpp"
#include "PNQuatf.hpp"

#include "pna_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef struct		pniRotationKey_s
{
  pnuint			time;
  PNQuatf			rot;
}					pniRotationKey_t;

typedef struct		pniPositionKey_s
{
  pnuint			time;
  PNPoint			pos;
}					pniPositionKey_t;

class PNMatrixTR4f;
class PNQuatf;
class PNPoint;

class				PNIAnimationBone : public PNObject
{
  pnuint			_id;

  typedef std::vector<pniRotationKey_t>	RotationVector;
  RotationVector	_rotations;
  typedef std::vector<pniPositionKey_t>	PositionVector;
  PositionVector	_positions;
public:
  PNIAnimationBone(std::istream& i);

  pnuint			getId();

  //////////////////////////////////////////////////////////////////////////
  
  pnint				unserialize(std::istream& i);

  //////////////////////////////////////////////////////////////////////////
  
  pnuint			setTransformation(pnuint time, PNMatrixTR4f& transform);

  pnbool			setRotation(pnuint time, PNQuatf& rot);
  pnbool			setRotation(pndouble rtime, const PNQuatf& lastRot, PNQuatf& rot);
  pnbool			setPosition(pnuint time, PNPoint& pos);
  pnbool			setPosition(pndouble rtime, const PNPoint& lastPos, PNPoint& pos);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNI3DANIMATIONBONE_HPP_*/
