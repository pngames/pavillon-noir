/*
 * PNIBone.hpp
 * 
 * Description :
 * PNIBone declaration
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

#ifndef _PNIBONE_HPP_
# define _PNIBONE_HPP_

#include "PNObject.hpp"

#include "PNMatrixTR4f.hpp"
#include "PNQuatf.hpp"
#include "PNPoint.hpp"

#include "pns_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DAnimation;
class PNQuatf;
class PNPoint;
class PNMatrixTR4f;

class					PNIBone : public PNObject
{
  pnuint				_id;
  std::string			_name;

  PNIBone*				_parent;

  /// Transformation matrix relative to parent bone
  PNMatrixTR4f			_mRelativ;

  /// Course matrix
  PNMatrixTR4f			_mCourse;
  /// Initial inverted course matrix
  PNMatrixTR4f			_mICourse;

  /// Transformation matrix to apply (Course * ICourse)
  PNMatrixTR4f			_mFinal;
public:
  PNIBone(pnsBone_t& bone, PNIBone* parent);

  pnuint				getId();
  const std::string&	getName();
  PNIBone*				getParent();

  const PNMatrixTR4f&	getCourse() const;
  const PNMatrixTR4f&	getFinal() const;

private:
  PNQuatf				_lastRot;
  PNPoint				_lastPos;

  PNQuatf				_totalLastRot;
public:
  const PNQuatf&		getOrientation();
public:
  void					update(pnuint time, PN3DAnimation* anim);
  void					update(pndouble rtime, PN3DAnimation* anim);
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNIBONE_HPP_*/
