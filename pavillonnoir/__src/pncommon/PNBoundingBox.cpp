/*
 * PNBoundingBox.cpp
 * 
 * Description :
 * PNBoundingBox definition
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

#include "PNBoundingBox.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNBoundingBox::PNBoundingBox()
{
  // Default to null box
  setMinimum(-0.5, -0.5, -0.5);
  setMaximum(0.5, 0.5, 0.5);
  mNull = true;
}

PNBoundingBox::~PNBoundingBox(void)
{
}

PNBoundingBox::PNBoundingBox(const PNPoint3f& min, const PNPoint3f& max)
{
  setExtents(min, max);
}

PNBoundingBox::PNBoundingBox(pnfloat mx, pnfloat my, pnfloat mz, pnfloat Mx, pnfloat My, pnfloat Mz)
{
  setExtents(mx, my, mz, Mx, My, Mz);
}

/** Gets the minimum corner of the box.
*/
const PNPoint3f& PNBoundingBox::getMinimum(void) const
{ 
  return mMinimum; 
}

/** Gets the maximum corner of the box.
*/
const	PNPoint3f& PNBoundingBox::getMaximum(void) const
{ 
  return mMaximum;
}

/** Sets the minimum corner of the box.
*/
void	PNBoundingBox::setMinimum(const PNPoint3f& vec)
{
  mNull = false;
  mMinimum = vec;
  _updateCorners();
}

void	PNBoundingBox::setMinimum(pnfloat x, pnfloat y, pnfloat z)
{
  mNull = false;
  mMinimum.x = x;
  mMinimum.y = y;
  mMinimum.z = z;
  _updateCorners();
}

/** Sets the maximum corner of the box.
*/
void	PNBoundingBox::setMaximum(const PNPoint3f& vec)
{
  mNull = false;
  mMaximum = vec;
  _updateCorners();
}

void	PNBoundingBox::setMaximum(pnfloat x, pnfloat y, pnfloat z)
{
  mNull = false;
  mMaximum.x = x;
  mMaximum.y = y;
  mMaximum.z = z;
  _updateCorners();
}

/** Sets both minimum and maximum extents at once.
*/
void	PNBoundingBox::setExtents(const PNPoint3f& min, const PNPoint3f& max)
{
  mNull = false;
  mMinimum = min;
  mMaximum = max;
  _updateCorners();
}

void	PNBoundingBox::setExtents(pnfloat mx, pnfloat my, pnfloat mz, pnfloat Mx, pnfloat My, pnfloat Mz)
{
  mNull = false;

  mMinimum.x = mx;
  mMinimum.y = my;
  mMinimum.z = mz;

  mMaximum.x = Mx;
  mMaximum.y = My;
  mMaximum.z = Mz;

  _updateCorners();
}

//////////////////////////////////////////////////////////////////////////

/** Internal method for updating corner points.
*/
void	PNBoundingBox::_updateCorners(void)
{
  // The order of these items is, using right-handed co-ordinates:
  // Minimum Z face, starting with Min(all), then anticlockwise
  //   around face (looking onto the face)
  // Maximum Z face, starting with Max(all), then anticlockwise
  //   around face (looking onto the face)

  mCorners[0] = mMinimum;
  mCorners[1].set(mMinimum.x, mMaximum.y, mMinimum.z);    
  mCorners[2].set(mMinimum.x, mMaximum.y, mMinimum.z);
  mCorners[3].set(mMinimum.x, mMaximum.y, mMinimum.z);
  mCorners[4] = mMaximum;
  mCorners[5].set(mMinimum.x, mMaximum.y, mMinimum.z);
  mCorners[6].set(mMinimum.x, mMaximum.y, mMinimum.z);
  mCorners[7].set(mMinimum.x, mMaximum.y, mMinimum.z);
}

//////////////////////////////////////////////////////////////////////////
}

