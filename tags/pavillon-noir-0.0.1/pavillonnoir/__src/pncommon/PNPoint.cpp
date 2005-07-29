/*
 * PNPoint.cpp
 * 
 * Description :
 * PNPoint definition
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
#include <math.h>

#include "pndefs.h"
#include "pnmath.h"
#include "PNPoint.hpp"

#define	DIST_EPSILON	10E-5

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////
  
PNPoint::PNPoint(void)
{
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;

  return ;
}

PNPoint::PNPoint(const pnfloat& px, const pnfloat& py, const pnfloat& pz)
{
  x = px;
  y = py;
  z = pz;

  return ;
}

PNPoint::PNPoint(const pnfloat* coord)
{
  x = coord[0];
  y = coord[1];
  z = coord[1];
}

PNPoint::PNPoint(const PNPoint& p)
{
  x = p.x;
  y = p.y;
  z = p.z;

  return ;
}

PNPoint::~PNPoint(void)
{
  return ;
}

//////////////////////////////////////////////////////////////////////////

void
PNPoint::setNull()
{
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

void
PNPoint::set(const pnfloat& px, const pnfloat& py, const pnfloat& pz)
{
  x = px;
  y = py;
  z = pz;

  return ;
}

void
PNPoint::set(const pnfloat* coord)
{
  x = coord[0];
  y = coord[1];
  z = coord[2];
}

void
PNPoint::set(const PNPoint& p)
{
  x = p.x;
  y = p.y;
  z = p.z;

  return ;
}

//////////////////////////////////////////////////////////////////////////

pnfloat
PNPoint::getDistance(const PNPoint& p) const
{
  return sqrtf(((p.x -x)* (p.x -x) + (p.y -y)* (p.y -y)
	+ (p.z -z)* (p.z -z)));
}

//////////////////////////////////////////////////////////////////////////

/**
 * \brief returns true if the specified point is equals to the current instance
 * in taking into account an EPSILON error. Returns false otherwise.
 * 
 * \param	point	the point used to do the comparison
 * \return	true	if both instance are equal, false otherwise.
 */
bool
PNPoint::isEquals(const PNPoint& point)
{
	return (getDistance(point) <= PN_EPSILON);
}

bool
PNPoint::isEquals(pnfloat x, pnfloat y, pnfloat z)
{
	PNPoint	u(x, y, z);
	return (isEquals(u));
}

//////////////////////////////////////////////////////////////////////////

std::string
PNPoint::toString(const char * title) const
{
	static 	char	buffer[256];
		
	sprintf(buffer, "PNPoint:%s: X=%f Y=%f Z=%f", title, x, y, z);
	return (buffer);
}


PNPoint::operator const pnfloat*() const
{
  return &x;
}

PNPoint&
PNPoint::operator=(const pnfloat* p)
{
  set(p);

  return *this;
}

//////////////////////////////////////////////////////////////////////////

// Operators

/**
 * DEPRECATED use PNVector3f instead
 */
PNPoint&
PNPoint::operator+=(const PNPoint& p)
{
  x += p.x;
  y += p.y;
  z += p.z;

  return (*this);
}

/**
 * DEPRECATED use PNVector3f instead
 */
PNPoint&
PNPoint::operator+=(const pnfloat k)
{
  x += k;
  y += k;
  z += k;

  return (*this);
}

/**
 * DEPRECATED use PNVector3f instead
 */
PNPoint&
PNPoint::operator-=(const PNPoint& p)
{
  x -= p.x;
  y -= p.y;
  z -= p.z;

  return (*this);
}

/**
 * DEPRECATED use PNVector3f instead
 */
PNPoint&
PNPoint::operator-=(const pnfloat k)
{
  x -= k;
  y -= k;
  z -= k;

  return (*this);
}

/**
 * DEPRECATED use PNVector3f instead
 */
PNPoint&
PNPoint::operator*=(const PNPoint& p)
{
  x *= p.x;
  y *= p.y;
  z *= p.z;

  return (*this);
}

/**
 * DEPRECATED use PNVector3f instead
 */
PNPoint&
PNPoint::operator*=(const pnfloat k)
{
  x *= k;
  y *= k;
  z *= k;

  return (*this);
}

PNPoint&
PNPoint::operator/=(const PNPoint& p)
{
  x /= p.x;
  y /= p.y;
  z /= p.z;

  return (*this);
}

PNPoint&
PNPoint::operator/=(const pnfloat k)
{
  x /= k;
  y /= k;
  z /= k;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////

PNAPI PNPoint
operator+(const PNPoint& p1, const PNPoint& p2)
{
  PNPoint	res(0.0, 0.0, 0.0);

  res = p1;

  return (res += p2);
}

PNAPI PNPoint
operator-(const PNPoint& p1, const PNPoint& p2)
{
  PNPoint	res(0.0, 0.0, 0.0);

  res = p1;

  return (res -= p2);
}

PNAPI PNPoint
operator*(const PNPoint& p1, const PNPoint& p2)
{
  PNPoint	res(0.0, 0.0, 0.0);

  res = p1;

  return (res*= p2);
}

PNAPI PNPoint
operator/(const PNPoint& p1, const PNPoint& p2)
{
  PNPoint	res(0.0, 0.0, 0.0);

  res = p1;

  return (res /= p2);
}

PNAPI pnbool
operator==(const PNPoint& p1, const PNPoint& p2)
{
  if ((fabs(p1.x - p2.x) < DIST_EPSILON) 
	&& (fabs(p1.y - p2.y) < DIST_EPSILON) 
	&& (fabs(p1.z - p2.z) < DIST_EPSILON))
	return (true);

  return (false);
}

PNAPI pnbool
operator!=(const PNPoint& p1, const PNPoint& p2)
{
  if ((fabs(p1.x - p2.x) < DIST_EPSILON) 
	&& (fabs(p1.y - p2.y) < DIST_EPSILON) 
	&& (fabs(p1.z - p2.z) < DIST_EPSILON))
	return (false);

  return (true);
}

//////////////////////////////////////////////////////////////////////////

PNAPI std::ostream&
operator<<(std::ostream& o, const PNPoint& p)
{
  o << "x=" << p.x << " y=" << p.y << " z=" << p.z;

  return o;
}

//////////////////////////////////////////////////////////////////////////

const PNPoint PNPoint::ZERO( 0, 0, 0 );

//////////////////////////////////////////////////////////////////////////
};
