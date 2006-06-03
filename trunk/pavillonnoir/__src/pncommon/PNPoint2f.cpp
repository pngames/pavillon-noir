/*
* PNPoint2f.cpp
* 
* Description :
* PNPoint2fdefinition
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

#include "pndefs.h"
#include "pnmath.h"
#include "PNPoint2f.hpp"

#define	DIST_EPSILON	10E-5

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNPoint2f::PNPoint2f(void)
{
  setNull();
}

PNPoint2f::PNPoint2f(const pnfloat& px, const pnfloat& py)
{
  x = px;
  y = py;
}

PNPoint2f::PNPoint2f(const pnfloat* coord)
{
  x = coord[0];
  y = coord[1];
}

PNPoint2f::PNPoint2f(const PNPoint2f& p)
{
  x = p.x;
  y = p.y;
}

PNPoint2f::~PNPoint2f(void)
{
}

//////////////////////////////////////////////////////////////////////////

void
PNPoint2f::setNull()
{
  x = 0.0f;
  y = 0.0f;
}

bool
PNPoint2f::isNull() const
{
  return ABS(x) < PN_EPSILON && ABS(y) < PN_EPSILON;
}

void
PNPoint2f::set(const pnfloat& px, const pnfloat& py)
{
  x = px;
  y = py;
}

void
PNPoint2f::set(const pnfloat* coord)
{
  x = coord[0];
  y = coord[1];
}

void
PNPoint2f::set(const PNPoint2f& p)
{
  x = p.x;
  y = p.y;
}

//////////////////////////////////////////////////////////////////////////

pnfloat
PNPoint2f::getDistance(const PNPoint2f& p) const
{
  return sqrtf(((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y)));
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
PNPoint2f::isEquals(const PNPoint2f& point)
{
  return (getDistance(point) <= PN_EPSILON);
}

bool
PNPoint2f::isEquals(pnfloat x, pnfloat y)
{
  PNPoint2f	u(x, y);

  return isEquals(u);
}

//////////////////////////////////////////////////////////////////////////

std::string
PNPoint2f::toString() const
{
  std::ostringstream os;
  os << x << " " << y;

  return os.str();
}

void
PNPoint2f::fromString(const std::string& str)
{
  std::istringstream	is(str);

  is >> x >> y;
}

//////////////////////////////////////////////////////////////////////////


PNPoint2f::operator const pnfloat*() const
{
  return &x;
}

PNPoint2f&
PNPoint2f::operator=(const pnfloat* p)
{
  set(p);

  return *this;
}

//////////////////////////////////////////////////////////////////////////

// Operators

PNPoint2f&
PNPoint2f::operator+=(const PNPoint2f& p)
{
  x += p.x;
  y += p.y;

  return *this;
}

PNPoint2f&
PNPoint2f::operator+=(const pnfloat k)
{
  x += k;
  y += k;

  return *this;
}

PNPoint2f&
PNPoint2f::operator-=(const PNPoint2f& p)
{
  x -= p.x;
  y -= p.y;

  return *this;
}

PNPoint2f&
PNPoint2f::operator-=(const pnfloat k)
{
  x -= k;
  y -= k;

  return *this;
}

PNPoint2f&
PNPoint2f::operator*=(const PNPoint2f& p)
{
  x *= p.x;
  y *= p.y;

  return *this;
}

PNPoint2f&
PNPoint2f::operator*=(const pnfloat k)
{
  x *= k;
  y *= k;

  return *this;
}

PNPoint2f&
PNPoint2f::operator/=(const PNPoint2f& p)
{
  x /= p.x;
  y /= p.y;

  return *this;
}

PNPoint2f&
PNPoint2f::operator/=(const pnfloat k)
{
  x /= k;
  y /= k;

  return *this;
}

//////////////////////////////////////////////////////////////////////////

PNPoint2f
PNPoint2f::operator-()
{
  return PNPoint2f(-x, -y);
}

//////////////////////////////////////////////////////////////////////////

PNAPI PNPoint2f
operator+(const PNPoint2f& p1, const PNPoint2f& p2)
{
  PNPoint2f	res(p1);

  return (res += p2);
}

PNAPI PNPoint2f
operator-(const PNPoint2f& p1, const PNPoint2f& p2)
{
  PNPoint2f	res(p1);

  return (res -= p2);
}

PNAPI PNPoint2f
operator*(const PNPoint2f& p1, const PNPoint2f& p2)
{
  PNPoint2f	res(p1);

  return (res *= p2);
}

PNAPI PNPoint2f
operator/(const PNPoint2f& p1, const PNPoint2f& p2)
{
  PNPoint2f	res(p1);

  return (res /= p2);
}

PNAPI pnbool
operator==(const PNPoint2f& p1, const PNPoint2f& p2)
{
  if ((fabs(p1.x - p2.x) < DIST_EPSILON)
	&& (fabs(p1.y - p2.y) < DIST_EPSILON))
	return true;

  return false;
}

PNAPI pnbool
operator!=(const PNPoint2f& p1, const PNPoint2f& p2)
{
  if ((fabs(p1.x - p2.x) < DIST_EPSILON)
	&& (fabs(p1.y - p2.y) < DIST_EPSILON))
	return false;

  return true;
}

//////////////////////////////////////////////////////////////////////////

PNAPI std::ostream&
operator<<(std::ostream& o, const PNPoint2f& p)
{
  o << "x=" << p.x << " y=" << p.y;

  return o;
}

//////////////////////////////////////////////////////////////////////////

const PNPoint2f	PNPoint2f::ZERO(0, 0);

//////////////////////////////////////////////////////////////////////////
};

