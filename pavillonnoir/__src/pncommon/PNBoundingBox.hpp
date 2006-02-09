/*
 * PNBoundingBox.hpp
 * 
 * Description :
 * PNBoundingBox declaration
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

#ifndef _PNBOUNDINGBOX_H_
# define _PNBOUNDINGBOX_H_

#include "PNObject.hpp"
#include "PNPoint3f.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

  /** A 3D box aligned with the x/y/z axes.
  @remarks
  This class represents a simple box which is aligned with the
  axes. Internally it only stores 2 points as the extremeties of
  the box, one which is the minima of all 3 axes, and the other
  which is the maxima of all 3 axes. This class is typically used
  for an axis-aligned bounding box (AABB) for collision and
  visibility determination.
  */

class PNAPI			PNBoundingBox : public PNObject
{
protected:
  PNPoint3f			mMinimum;
  PNPoint3f			mMaximum;
  bool				mNull;

  PNPoint3f			mCorners[8];

  void				_updateCorners(void);
public:
  PNBoundingBox(void);
  PNBoundingBox(const PNPoint3f& min, const PNPoint3f& max);
  PNBoundingBox(pnfloat mx, pnfloat my, pnfloat mz, pnfloat Mx, pnfloat My, pnfloat Mz);
  ~PNBoundingBox(void);

  const	PNPoint3f&	getMinimum(void) const;
  const	PNPoint3f&	getMaximum(void) const;
  void				setMinimum(const PNPoint3f& vec);
  void				setMinimum(pnfloat x, pnfloat y, pnfloat z);
  void				setMaximum(const PNPoint3f& vec);
  void				setMaximum(pnfloat x, pnfloat y, pnfloat z);
  void				setExtents(const PNPoint3f& min, const PNPoint3f& max);
  void				setExtents(pnfloat mx, pnfloat my, pnfloat mz, pnfloat Mx, pnfloat My, pnfloat Mz);
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNBOUNDINGBOX_H_*/

