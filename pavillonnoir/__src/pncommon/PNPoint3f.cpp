/*
 * PNPoint3f.cpp
 * 
 * Description :
 * PNPoint3fdefinition
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
#include <sstream>
#include <math.h>

#include "pndefs.h"
#include "pnmath.h"
#include "PNPoint3f.hpp"

#define	DIST_EPSILON	10E-5

using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////
  
PNPoint3f::PNPoint3f(void)
{
  setNull();
}

PNPoint3f::PNPoint3f(const pnfloat& px, const pnfloat& py, const pnfloat& pz)
{
  x = px;
  y = py;
  z = pz;
}

PNPoint3f::PNPoint3f(const pnfloat* coord)
{
  x = coord[0];
  y = coord[1];
  z = coord[2];
}

PNPoint3f::PNPoint3f(const PNPoint3f& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
}

PNPoint3f::PNPoint3f(const std::string& str)
{
  unserialize(str);
}

PNPoint3f::~PNPoint3f(void)
{
}

//////////////////////////////////////////////////////////////////////////

void
PNPoint3f::setNull()
{
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

bool
PNPoint3f::isNull() const
{
  return ABS(x) < PN_EPSILON && ABS(y) < PN_EPSILON && ABS(z) < PN_EPSILON;
}

void
PNPoint3f::set(const pnfloat& px, const pnfloat& py, const pnfloat& pz)
{
  x = px;
  y = py;
  z = pz;
}

void
PNPoint3f::set(const pnfloat* coord)
{
  x = coord[0];
  y = coord[1];
  z = coord[2];
}

void
PNPoint3f::set(const PNPoint3f& p)
{
  x = p.x;
  y = p.y;
  z = p.z;
}

//////////////////////////////////////////////////////////////////////////

pnfloat
PNPoint3f::getDistance(const PNPoint3f& p) const
{
  return sqrtf(((p.x -x)* (p.x -x) + (p.y -y)* (p.y -y)
	+ (p.z -z)* (p.z -z)));
}

pnfloat
PNPoint3f::getFlatDistance(const PNPoint3f& p) const
{
  return sqrtf(((p.x -x)* (p.x -x) + (p.z -z)* (p.z -z)));
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
PNPoint3f::isEquals(const PNPoint3f& point)
{
  return (getDistance(point) <= PN_EPSILON);
}

bool
PNPoint3f::isEquals(pnfloat x, pnfloat y, pnfloat z)
{
  PNPoint3f	u(x, y, z);
  return (isEquals(u));
}

//////////////////////////////////////////////////////////////////////////

std::string
PNPoint3f::serialize() const
{
  std::ostringstream os;
  os << x << " " << y << " " << z;

  return os.str();
}

void
PNPoint3f::unserialize(const std::string& str)
{
  std::istringstream	is(str);
	
  unserialize(is);
}

void
PNPoint3f::unserialize(std::istream& is)
{
  is >> x >> y >> z;
}

//////////////////////////////////////////////////////////////////////////


PNPoint3f::operator const pnfloat*() const
{
  return &x;
}

PNPoint3f&
PNPoint3f::operator=(const pnfloat* p)
{
  set(p);

  return *this;
}

//////////////////////////////////////////////////////////////////////////

// Operators

PNPoint3f&
PNPoint3f::operator+=(const PNPoint3f& p)
{
  x += p.x;
  y += p.y;
  z += p.z;

  return (*this);
}

PNPoint3f&
PNPoint3f::operator+=(const pnfloat k)
{
  x += k;
  y += k;
  z += k;

  return (*this);
}

PNPoint3f&
PNPoint3f::operator-=(const PNPoint3f& p)
{
  x -= p.x;
  y -= p.y;
  z -= p.z;

  return (*this);
}

PNPoint3f&
PNPoint3f::operator-=(const pnfloat k)
{
  x -= k;
  y -= k;
  z -= k;

  return (*this);
}

PNPoint3f&
PNPoint3f::operator*=(const PNPoint3f& p)
{
  x *= p.x;
  y *= p.y;
  z *= p.z;

  return (*this);
}

PNPoint3f&
PNPoint3f::operator*=(const pnfloat k)
{
  x *= k;
  y *= k;
  z *= k;

  return (*this);
}

PNPoint3f&
PNPoint3f::operator/=(const PNPoint3f& p)
{
  x /= p.x;
  y /= p.y;
  z /= p.z;

  return (*this);
}

PNPoint3f&
PNPoint3f::operator/=(const pnfloat k)
{
  x /= k;
  y /= k;
  z /= k;

  return (*this);
}

//////////////////////////////////////////////////////////////////////////

PNPoint3f
PNPoint3f::operator-()
{
  return PNPoint3f(-x, -y, -z);
}

//////////////////////////////////////////////////////////////////////////

PNAPI PNPoint3f
operator+(const PNPoint3f& p1, const PNPoint3f& p2)
{
  PNPoint3f	res(p1);

  return (res += p2);
}

PNAPI PNPoint3f
operator-(const PNPoint3f& p1, const PNPoint3f& p2)
{
  PNPoint3f	res(p1);

  return (res -= p2);
}

PNAPI PNPoint3f
operator*(const PNPoint3f& p1, const PNPoint3f& p2)
{
  PNPoint3f	res(p1);

  return (res *= p2);
}

PNAPI PNPoint3f
operator/(const PNPoint3f& p1, const PNPoint3f& p2)
{
  PNPoint3f	res(p1);

  return (res /= p2);
}

PNAPI pnbool
operator==(const PNPoint3f& p1, const PNPoint3f& p2)
{
  if ((fabs(p1.x - p2.x) < DIST_EPSILON) 
	&& (fabs(p1.y - p2.y) < DIST_EPSILON) 
	&& (fabs(p1.z - p2.z) < DIST_EPSILON))
	return (true);

  return (false);
}

PNAPI pnbool
operator!=(const PNPoint3f& p1, const PNPoint3f& p2)
{
  if ((fabs(p1.x - p2.x) < DIST_EPSILON) 
	&& (fabs(p1.y - p2.y) < DIST_EPSILON) 
	&& (fabs(p1.z - p2.z) < DIST_EPSILON))
	return (false);

  return (true);
}

//////////////////////////////////////////////////////////////////////////

PNAPI std::ostream&
operator<<(std::ostream& o, const PNPoint3f& p)
{
  o << "x=" << p.x << " y=" << p.y << " z=" << p.z;

  return o;
}

//////////////////////////////////////////////////////////////////////////

const PNPoint3f	PNPoint3f::ZERO(0, 0, 0);

//////////////////////////////////////////////////////////////////////////
};
