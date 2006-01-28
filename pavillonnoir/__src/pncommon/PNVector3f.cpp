/*
 * PNVector3f.cpp
 * 
 * Description :
 * 3D-Vector definition
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
using namespace std;

/////////////////////////////////////

#include "pndefs.h"
#include "PNVector3f.hpp"

/////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

/**
 * \brief default constructor for PNVector3f.
 * Assigns 0 value for the three components.
 */
PNVector3f::PNVector3f()
{
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

/**
 * \brief constructor for PNVector3f. Assigns the specified values
 * for each of the component.
 */
PNVector3f::PNVector3f(pnfloat vX, pnfloat vY, pnfloat vZ)
{
  x = vX;
  y = vY;
  z = vZ;
}

/**
 * \brief copy constructor. Assigns the specified value to the current instance.
 */
PNVector3f::PNVector3f(const PNPoint3f& source)
{
  x = source.x;
  y = source.y;
  z = source.z;
}

/**
 * \brief Constructs the specified segment.
 *
 * \param	source		origin of the segment
 * \param	destination	destination of the segment.
 */
PNVector3f::PNVector3f(const PNPoint3f& origin, const PNPoint3f& destination)
{
  setFromSegment(origin, destination);
}

/////////////////////////////////////

/**
 * \brief destructor.
 */
PNVector3f::~PNVector3f()
{
}

/////////////////////////////////////

void
PNVector3f::get(pnfloat & vX, pnfloat & vY, pnfloat & vZ)
{
  vX = x;
  vY = y;
  vZ = z;
}

void
PNVector3f::get(pnfloat * array)
{
  assert(array != NULL);

  array[0] = x;
  array[1] = y;
  array[2] = z;
}

/**
 * \brief Creates the current instance from the specified segment.
 *
 * \param	origin		origin of the specified segment
 * \param	extremity	extremity of the specified segment
 *
 * \return void
 */
void
PNVector3f::setFromSegment(const PNPoint3f& origin, const PNPoint3f& extremity)
{
  x = extremity.x - origin.x;
  y = extremity.y - origin.y;
  z = extremity.z - origin.z;
}

/**
 * \brief Returns true if the current instance is colinear with v, ie: if both vectors are parallel and have the same direction.
 * Note: it is an error to call this method whereas one of the vector is null. In DEBUG version
 * an assertion will be broken. In RELEASE version this may lead to an undefined behavior.
 *
 * \param	v	the vector we want to test.
 *
 * \return	true if they are colinear, false otherwise.
 */
bool
PNVector3f::isColinear(const PNVector3f & v)
{
  PNVector3f	a(*this);
  PNVector3f	b(v);
  pnfloat		ps;

  a.setNorm(1.0f);
  b.setNorm(1.0f); 

  ps = a.scalarProduct(b);

  return (ps > 1.0f - PN_EPSILON);
}

/**
 * \brief Returns true if the current instance is collinear with v, ie: if both vectors are parallel and have the same direction.
 * Note: it is an error to call this method whereas one of the vector is null. In DEBUG version
 * an assertion will be broken. In RELEASE version this may lead to an undefined behavior.
 *
 * \param	vX	x-coordinate of the specified vector
 * \param	vY	y-coordinate of the specified vector
 * \param	vZ	z-coordinate of the specified vector
 *
 * \return	true if they are collinear, false otherwise.
 */
bool
PNVector3f::isColinear(pnfloat vX, pnfloat vY, pnfloat vZ)
{
  PNVector3f	u(vX, vY, vZ);

  return isColinear(u);
}

/**
 * \brief Returns true if both the current instance and the specified vector are orthogonal. False
 * Otherwise.
 *
 * \param	v	the specified vector we want to test the orthogonality
 * \return	true	if they are orthogonal, false otherwise.
 */
bool
PNVector3f::isOrthogonal(const PNVector3f & v)
{
  pnfloat	ps;

  ps = this->scalarProduct(v);
  if (ps < 0)
    ps *= -1;

  return (ps <= PN_EPSILON);
}

/**
 * \brief Returns true if both the current instance and the specified vector are orthogonal. False
 * Otherwise.
 *
 * \param	vX	x-coordinate of the specified vector
 * \param	vY	y-coordinate of the specified vector
 * \param	vZ	z-coordinate of the specified vector
 *
 * \return	true	if they are orthogonal, false otherwise.
 */
bool
PNVector3f::isOrthogonal(pnfloat vX, pnfloat vY, pnfloat vZ)
{
  PNVector3f	a(vX, vY, vZ);

  return isOrthogonal(a);
}

/**
 * \brief Substracts v's coordinates from the current instance.
 * \return void
 */
void
PNVector3f::substract(const PNPoint3f& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

/**
 * \brief Substracts specified coordinates from current coordinates.
 *
 * \param	vX	x-value to substract from the current x-coordinate
 * \param	vY	y-value to substract from the current y-coordinate
 * \param	vZ	z-value to substract from the current z-coordinate
 *
 * \return	void
 */
void
PNVector3f::substract(pnfloat vX, pnfloat vY, pnfloat vZ)
{
  x -= vX;
  y -= vY;
  z -= vZ;
}

/**
 * \brief Substracts the point u from the point v and stores the corresponding result
 * into the current instance.
 *
 * \param	v	first vector for substraction
 * \param	u       second vector for substraction
 *
 * \return	void
 */
void
PNVector3f::substract(const PNPoint3f& v, const PNPoint3f& u)
{
  x = v.x - u.x;
  y = v.y - u.y;
  z = v.z - u.z;
}

/**
 * \brief Adds the specified point to the current instance.
 *
 * \param	v	vector to add
 * \return		void
 */
void
PNVector3f::add(const PNPoint3f& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
}

/**
 * \brief Add the specified coordinates to the current instance
 */
void
PNVector3f::add(pnfloat vX, pnfloat vY, pnfloat vZ)
{
  x += vX;
  y += vY;
  z += vZ;
}

/**
 * \brief Adds both point and stores the corresponding result into the current instance.
 */
void
PNVector3f::add(const PNPoint3f& u, const PNPoint3f& v)
{
  x = u.x + v.x;
  y = u.y + v.y;
  z = u.z + v.z;
}

/**
 * \brief Multiplies the current vector by the specified constant.
 *
 * \param	constant	multiplicator
 * \return	void
 */
void
PNVector3f::multiply(pnfloat constant)
{
  x *= constant;
  y *= constant;
  z *= constant;
}

/**
 * \return the scalar product with the specified vector
 */
pnfloat
PNVector3f::scalarProduct(const PNVector3f & v) const
{
  return (x * v.x + y * v.y + z * v.z);
}

/**
 * \return the scalar product with the specified coordinates
 */
pnfloat
PNVector3f::scalarProduct(pnfloat vX, pnfloat vY, pnfloat vZ) const
{
  return (x * vX + y * vY + z * vZ);
}

/**
 * \brief Computes the cross product between the vector u and v and stores the result in the current instance.
 *
 * \param	u	first vector for the cross product
 * \param	v	second vector for the cross product
 *
 * \return	void
 */
void
PNVector3f::crossProduct(const PNVector3f &u, const PNVector3f &v)
{
  register pnfloat	r_x;
  register pnfloat	r_y;
  register pnfloat	r_z;
	
  r_x = u.y * v.z - u.z * v.y;
  r_y = u.z * v.x - u.x * v.z;
  r_z = u.x * v.y - u.y * v.x;
	
  x = r_x;
  y = r_y;
  z = r_z;
}

/**
 * \brief Return true if the current vector belongs to the specified segment, false otherwise.
 *
 * \param	origin		origin of the specified segment
 * \param	extremity	extremity of the specified segment
 *
 * \return	true if the current vector belongs to the specified segment, false otherwise.
 */
bool
PNVector3f::isBelongToSegment(const PNPoint3f& origin, const PNPoint3f& extremity)
{
  PNVector3f	u;
  PNVector3f	v;
  pnfloat		res;

  if (this->isEquals(origin) || this->isEquals(extremity))
    return (true);
  
  u.substract(origin, *this);
  v.substract(extremity, *this);
  u.setNorm(1.0f);
  v.setNorm(1.0f);

  res = u.scalarProduct(v);

  return (res > - 1 - PN_EPSILON && res < - 1 + PN_EPSILON);
}

/**
 * \brief Computes the intersection between the two specified segments, returns true if an intersection has been found. If this so,
 * the current instance stores computed coordinates of the intersection. Otherwise returns false.
 * Note: It is an error to call this method with one or two segments of size null. In DEBUG mode, an assertion will be broken.
 * int RELEASE mode this may lead to an undefined behavior.
 *
 * \param	originOne	origin of the first segment
 * \param	extremityOne	extremity of the first segment
 * \param	originTwo	origin of the second segment
 * \param	extremityTwo	extremity of the second segment
 *
 * \return	true if an intersection has been found, false otherwise.
 */
bool
PNVector3f::intersection(const PNPoint3f& originOne, const PNPoint3f& extremityOne, const PNPoint3f& originTwo, const PNPoint3f& extremityTwo)
{
  PNVector3f	u1;
  PNVector3f	u2;
  PNVector3f	tmp;
  pnfloat	u1_ps_a;
  pnfloat	u1_ps_u;
  pnfloat	u1_ps_u2;
  pnfloat	u2_ps_a;
  pnfloat	u2_ps_u;
  pnfloat	det;
  pnfloat	det_inv;
  pnfloat	phi;

  u1.setFromSegment(originOne, extremityOne);
  u1.setNorm(1.0f);

  u2.setFromSegment(originTwo, extremityTwo);
  u2.setNorm(1.0f);

  if ((det = u1.scalarProduct(u2)) >=1)
    return (false);
  
  det *= det;  
  det_inv = 1 / (1 - det);
  
  u1_ps_a = u1.scalarProduct(originOne.x, originOne.y, originOne.z);
  u1_ps_u = u1.scalarProduct(originTwo.x, originTwo.y, originTwo.z);
  u1_ps_u2 = u1.scalarProduct(u2);
  u2_ps_a = u2.scalarProduct(originOne.x, originOne.y, originOne.z);
  u2_ps_u = u2.scalarProduct(originTwo.x, originTwo.y, originTwo.z);
  
  phi = det_inv * ((u1_ps_u - u1_ps_a) + u1_ps_u2 * (u2_ps_a - u2_ps_u));

  u1.multiply(phi);
  tmp.add(originOne, u1);

  if (tmp.isBelongToSegment(originOne, extremityOne) && tmp.isBelongToSegment(originTwo, extremityTwo))
    {
      *this = tmp;
      return (true);
    }  
  
  return (false);
}

//////////////////////////////////////////////////////////////////////////

const PNVector3f PNVector3f::ZERO( 0, 0, 0 );
const PNVector3f PNVector3f::UNIT_X( 1, 0, 0 );
const PNVector3f PNVector3f::UNIT_Y( 0, 1, 0 );
const PNVector3f PNVector3f::UNIT_Z( 0, 0, 1 );
const PNVector3f PNVector3f::NEGATIVE_UNIT_X( -1,  0,  0 );
const PNVector3f PNVector3f::NEGATIVE_UNIT_Y(  0, -1,  0 );
const PNVector3f PNVector3f::NEGATIVE_UNIT_Z(  0,  0, -1 );
const PNVector3f PNVector3f::UNIT_SCALE(1, 1, 1);

/////////////////////////////////////

} /* end of namespace */

/////////////////////////////////////

