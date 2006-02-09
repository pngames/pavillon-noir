/*
 * PNBoundingSphere.cpp
 * 
 * Description :
 * PNBoundingSphere definition
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

#include "PNBoundingSphere.hpp"
#include <iostream>
using namespace std;

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////


PNBoundingSphere::PNBoundingSphere(void)
{
  PNPoint3f	position(0, 0, 0);
  PNPoint3f	radius(1, 1, 1);

  setPosition(position);
  setRadius(radius);

  return;
}

PNBoundingSphere::~PNBoundingSphere(void)
{
  return;
}

PNBoundingSphere::PNBoundingSphere(const PNPoint3f& radius, const PNPoint3f& position)
{
  setPosition(position);
  setRadius(radius);

  return;
}

PNBoundingSphere::PNBoundingSphere(const PNBoundingSphere & source)
{
  setPosition(source.getPosition(_position));
  setRadius(source.getRadius(_radius));

  return;
}

//////////////////////////////////////////////////////////////////////////

/**
 * \brief Call this method to check or compute a potentialy collision with the current BoundingSphere and the specified triangle. 
 * In the case where a collision is detected a correction vector to apply to the sphere is computed to prevent it to collide.
 * 
 * \param	triangle		triangle for which a collision needs to be tested
 * \param	correction		location where to store the new coordinates of the correction in case of collision
 * 
 * \return	true in case of collision, if this so, the caller can use the values stored into correction.
 * 			false otherwise.
 */
bool
PNBoundingSphere::testCollisionWithTriangle(const PNTriangle & triangle, PNVector3f & correction) const
{
	static PNVector3f	v;
	static pnfloat		k;
	static PNPoint3f		impactTriangle;
	static PNPoint3f		impactBBox;
	static PNPoint3f		projectedCenter;
	static PNVector3f	eep;
	pnfloat				eqtResult;
		
	projectedCenter = triangle.projectionOnPlane(_position, projectedCenter);
	impactTriangle = triangle.getClosestPoint(_position, impactTriangle);	
	
	v.setFromSegment(_position, impactTriangle);
	
	eqtResult = (v.x * v.x) / _sqrRadius.x + (v.y * v.y) / _sqrRadius.y + (v.z * v.z) / _sqrRadius.z;
		
	if (eqtResult < 1)
	{
		eep.setFromSegment(_position, projectedCenter);
		if (eep.getNorm() <= PN_EPSILON)
			{
				eep.set(triangle.getOrientationX(), triangle.getOrientationY(), triangle.getOrientationZ());
				eep.multiply(-1);
			}
		k = sqrtf(1.0f / ((eep.x * eep.x)/_sqrRadius.x +
						  (eep.y * eep.y)/_sqrRadius.y +
						  (eep.z * eep.z)/_sqrRadius.z));
						  							  
		impactBBox.set( _position.x + k * eep.x,
						   _position.y + k * eep.y,
						   _position.z + k * eep.z);
							   
		correction.setFromSegment(impactBBox, projectedCenter);
				
		return (correction.getNorm() >= PN_EPSILON);
	}
		
	return (false);
}

/**
 * \return Computes the distance from the center to the surface along the given direction.
 */
pnfloat
PNBoundingSphere::computeDistanceFromCenterToSurface (PNPoint3f& direction)
{
	return (sqrtf(1.0f / (((direction.x*direction.x) / _sqrRadius.x) + 
				((direction.y*direction.y) / _sqrRadius.y) + 
				((direction.z*direction.z) / _sqrRadius.z))));
}

//////////////////////////////////////////////////////////////////////////
};

