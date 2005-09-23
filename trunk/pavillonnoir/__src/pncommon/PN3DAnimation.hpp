/*
 * PN3DAnimation.hpp
 * 
 * Description :
 * PN3DAnimation declaration
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

#ifndef _PN3DANIMATION_HPP_
# define _PN3DANIMATION_HPP_

#include "PNObject.hpp"
#include "IPNSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNMatrixTR4f;
class PNQuatf;
class PNPoint;

/// Animation
class /*PNAPI*/		PN3DAnimation : public PNObject, public IPNSerializable
{
public:
  /// Destructor for PN3DAnimation.
  virtual ~PN3DAnimation() {}

  //////////////////////////////////////////////////////////////////////////
  
  /// Get animation duration
  virtual pnuint	getTotalTime()=0;

  //////////////////////////////////////////////////////////////////////////
  
  /// Calculate matrix transformation for bone \c id and at time \c time
  virtual pnuint	setTransformation(pnint id, pnuint time, PNMatrixTR4f& transform)=0;

  /// Calculate quaternion (rotation) for bone \c id and at time \c time
  virtual pnbool	setRotation(pnint id, pnuint time, PNQuatf& rot)=0;
  /// Calculate interpolation quaternion (rotation) between \c lastrot and \c rot for bone \c id and at relative time \c rtime
  virtual pnbool	setRotation(pnint id, pndouble rtime, const PNQuatf& lastRot, PNQuatf& rot)=0;
  /// Calculate position for bone \c id and at time \c time
  virtual pnbool	setPosition(pnint id, pnuint time, PNPoint& pos)=0;
  /// Calculate interpolation position between \c lastrot and \c rot for bone \c id and at relative time \c rtime
  virtual pnbool	setPosition(pnint id, pndouble rtime, const PNPoint& lastPos, PNPoint& pos)=0;
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PN3DANIMATION_HPP_*/
