/*
 * PNNormal3f.cpp
 * 
 * Description :
 * 3D-Normal definition
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
#include <assert.h>
#include <string>
using namespace std;

/////////////////////////////////////

#include "pndefs.h"
#include "IAutoTestable.hpp"
#include "PNNormal3f.hpp"

/////////////////////////////////////

namespace PN {

/////////////////////////////////////

/**
 * \brief default constructor for PNVector3f.
 * Assigns 0 value for the three components.
 */
PNNormal3f::PNNormal3f()
{
  x = 0;
  y = 0;
  z = 0;
}

/**
* \brief constructor for PNVector3f. Assigns the specified values
* for each of the component. The resulting vector is normalized automatically.
*/
PNNormal3f::PNNormal3f(pnfloat nX, pnfloat nY, pnfloat nZ)
{
  setCrd(nX, nY, nZ);
}

/**
* \brief copy constructor. Assigns the specified normalized vector to the current instance.
*/
PNNormal3f::PNNormal3f(const PNPoint3f& source)
{
  setCrd(source.x, source.y, source.z);
}

/**
* \brief destructor
*/
PNNormal3f::~PNNormal3f()
{
}

/**
* \brief Creates the current instance from the specified segment.
*
* The resulting vector is normalized automatically.
*
* \param	origin		origin of the specified segment
* \param	extremity	extremity of the specified segment
*
* \return void
*/
void
PNNormal3f::setFromSegment(const PNPoint3f& origin, const PNPoint3f& extremity)
{
  PNVector3f::setFromSegment(origin, extremity);
  setNorm(1.0f);
}

/**
* \brief Returns true if current vector and the one specified are colinear, ie: if both vectors are parallel
* and have the same direction.
*
* \param v	normal we want to test
* \return true	if colinear, false otherwise.
*/
bool
PNNormal3f::isColinear(const PNNormal3f & v)
{
  pnfloat	ps = x * v.x + y * v.y + z * v.z;

  return (ps >= 1 - PN_EPSILON);
}

/**
* \brief Returns true if current vector and the one specified are collinear, ie: if both vectors are parallel
* and have the same direction.
*
* Note: it is an error to call this method in passing a null vector as parameter. In DEBUG version an assertion
* will be broken, In RELEASE version this may lead to an undefined behavior.
*
* \param v	normal we want to test
* \return true	if collinear, false otherwise.
*/
bool
PNNormal3f::isColinear(pnfloat nX, pnfloat nY, pnfloat nZ)
{
  PNNormal3f	n(nX, nY, nZ);

  return isColinear(n);
}

/**
* \brief Returns true if both the current instance and the specified normal are orthogonal. False
* Otherwise.
*
* \param	v	the specified normal we want to test the orthogonality
* \return	true	if they are orthogonal, false otherwise.
*/
bool
PNNormal3f::isOrthogonal(const PNNormal3f& v)
{
  pnfloat	ps = x * v.x + y * v.y + z * v.z;

  return (ABS(ps) < PN_EPSILON);
}

/**
* \brief Returns true if both the current instance and the specified normal are orthogonal. False
* Otherwise.
*
* Note: it is an error to call this method in passing a null vector as parameter. In DEBUG version an assertion
* will be broken, In RELEASE version this may lead to an undefined behavior.
*
* \param	v	the specified normal we want to test the orthogonality
* \return	true	if they are orthogonal, false otherwhise.
*/
bool
PNNormal3f::isOrthogonal(pnfloat nX, pnfloat nY, pnfloat nZ)
{
  PNNormal3f	n(nX, nY, nZ);

  return isOrthogonal(n);
}

/**
* \return true if the normal is null or lesser than EPSILON false otherwise
*/
bool
PNNormal3f::isNull()
{
  return (x * x + y * y + z * z < PN_EPSILON);
}

/**
* \brief Returns the measure in radian of the angle specified by the current instance
* and the one specified in parameter. 
* The resulting angle (in radian) always belongs to the range [0 - PI].
* 
* \param	n	the normal specifying the other side for the angle computation.
* \return	an angle in radian belonging to the range [0 - PI]
*/
pnfloat
PNNormal3f::radianRangePi(const PNNormal3f& n)
{
  pnfloat	ps;

  ps = x * n.x + y * n.y + z * n.z;

  if (ps > 1 - PN_EPSILON)
	return (0);
  if (ps < -1 + PN_EPSILON)
	return (pnfloat)PI;

  return (acosf(ps));
}

/**
* \brief Returns the measure in radian of the angle specified by the current instance
* and the axis orientation specified.
* The resulting angle (in radian) always belongs to the range [0 - 2*PI].
* 
* \param	cosinusReferentiel	orientation of X-axis (cosinus axis)
* \param	sinusReferentiel	orientation of Y-axis (sinus axis)
* \return	an angle in radian belonging to the range [0 - 2*PI]
*/
pnfloat
PNNormal3f::radianRange2Pi(const PNNormal3f& cosinusReferentiel, const PNNormal3f& sinusReferentiel)
{
  pnfloat	ps_cs;
  pnfloat	ps_sn;

  if (isColinear(cosinusReferentiel))
	return (0);

  if (isColinear(sinusReferentiel))
	return (pnfloat)(PI/2);

  ps_cs = scalarProduct(cosinusReferentiel);
  ps_sn = scalarProduct(sinusReferentiel);

  if (ps_sn >= 0)
	return (acosf(ps_cs));

  if (ps_cs >= 0 && ps_sn < 0)
	return (pnfloat)(2 * PI - acos(ps_cs));

  return (pnfloat)(acos(ps_cs) + PI/2);
}

/**
* \brief Returns the measure in degree of the angle specified by the current instance
* and the one specified in parameter. 
* The resulting angle (in degree) always belongs to the range [0 - 180].
* 
* \param	n	the normal specifying the other side for the angle computation.
* \return	an angle in degree belonging to the range [0 - 180]
*/
pnfloat
PNNormal3f::degreeRangePi(const PNNormal3f& n)
{
  return (pnfloat)RADIAN_TO_DEGREE(radianRangePi(n));
}

/**
* \brief Returns the measure in degree of the angle specified by the current instance
* and the axis orientation specified.
* The resulting angle (in degree) always belongs to the range [0 - 360].
* 
* \param	cosinusReferentiel	orientation of X-axis (cosinus axis)
* \param	sinusReferentiel	orientation of Y-axis (sinus axis)
* \return	an angle in degree belonging to the range [0 - 360]
*/
pnfloat
PNNormal3f::degreeRange2Pi(const PNNormal3f& cosinusReferentiel, const PNNormal3f& sinusReferentiel)
{
  return (pnfloat)RADIAN_TO_DEGREE(radianRange2Pi(cosinusReferentiel, sinusReferentiel));
}

/**
* \return the norms of the current normal
*/
pnfloat
PNNormal3f::getNorm() const
{
  return PNVector3f::getNorm();
}

/**
* \brief computes the cross product of vectors u and v and normalizes the resulting normal.
* Note: it is an error to call this method with a null vector. In DEBUG version an assertion
* will be broken. In RELEASE version this may lead to a division by zero.
* 
* \param	u	first vector for the cross product
* \param	v	second vector for the cross product
* 
* \return	void
*/
void
PNNormal3f::crossProduct(const PNPoint3f& u, const PNPoint3f& v)
{
  PNNormal3f	normalizedU(u.x, u.y, u.z);
  PNNormal3f	normalizedV(v.x, v.y, v.z);

  assert(normalizedU.isColinear(normalizedV) == false);

  PNVector3f::crossProduct(normalizedU, normalizedV);		
  setNorm(1.0f);

  return;
}

void
PNNormal3f::crossProduct(const PNNormal3f& u, const PNNormal3f& v)
{
  PNVector3f::crossProduct((const PNVector3f &) u, (const PNVector3f &) v);
  setNorm(1.0f);

  return;
}

pnfloat
PNNormal3f::scalarProduct(const PNNormal3f & n) const
{
  return (PNVector3f::scalarProduct((PNVector3f &) n));
}

pnfloat
PNNormal3f::scalarProduct(const PNPoint3f& u) const
{
  PNNormal3f	uNormalized(u.x, u.y, u.z);
  return (PNVector3f::scalarProduct(uNormalized)); 
}

pnfloat
PNNormal3f::scalarProduct(pnfloat nX, pnfloat nY, pnfloat nZ) const
{
  PNNormal3f	uNormalized(nX, nY, nZ);
  return (this->PNVector3f::scalarProduct(uNormalized));
}

//////////////////////////////////////////////////////////////////////////

PNNormal3f&
PNNormal3f::operator=(const PNPoint3f& p)
{
  setArray(p);

  return *this;
}

//////////////////////////////////////////////////////////////////////////
};
