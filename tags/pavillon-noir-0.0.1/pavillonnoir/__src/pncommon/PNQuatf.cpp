/*
 * PNQuatf.cpp
 * 
 * Description :
 * PNQuatf definition
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

#include "PNQuatf.hpp"
#include "PNPoint.hpp"
#include "PNVector3f.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////
  
void		PNQuatf::fromDegrees(const pnfloat* angles)
{
  fromRadians((pnfloat)DEGREE_TO_RADIAN(angles[0]), (pnfloat)DEGREE_TO_RADIAN(angles[1]), (pnfloat)DEGREE_TO_RADIAN(angles[2]));
}

void		PNQuatf::fromDegrees(pnfloat x, pnfloat y, pnfloat z)
{
  fromRadians((pnfloat)DEGREE_TO_RADIAN(x), (pnfloat)DEGREE_TO_RADIAN(y), (pnfloat)DEGREE_TO_RADIAN(z));
}

void		PNQuatf::fromRadians(const pnfloat* angles)
{
  fromRadians(angles[0], angles[1], angles[2]);
}

void		PNQuatf::fromRadians(pnfloat rx, pnfloat ry, pnfloat rz)
{
  register pnfloat	sx, sy, sz, cx, cy, cz;

  register pnfloat	ax = rx * 0.5f;
  register pnfloat	ay = ry * 0.5f;
  register pnfloat	az = rz * 0.5f;

  sx = sinf(ax);
  cx = cosf(ax);

  sy = sinf(ay);
  cy = cosf(ay);

  sz = sinf(az);
  cz = cosf(az);

  x = sx * cy * cz - cx * sy * sz;
  y = cx * sy * cz + sx * cy * sz;
  z = cx * cy * sz - sx * sy * cz;
  w = cx * cy * cz + sx * sy * sz;
}

void		PNQuatf::fromAxisDegrees(const PNVector3f& axis, pnfloat phi)
{
  fromAxisRadians(axis, (pnfloat)DEGREE_TO_RADIAN(phi));
}

void		PNQuatf::fromAxisRadians(const PNVector3f& axis, pnfloat phi)
{
  register pnfloat a = 0.5f * phi;
  register pnfloat s = sinf(a) / axis.getNorm();

  x = axis.x * s;
  y = axis.y * s;
  z = axis.z * s;
  w = cosf(a);
}

void		PNQuatf::getDegrees(pnfloat* angles) const
{
  getDegrees(angles[0], angles[1], angles[2]);
}

void		PNQuatf::getDegrees(pnfloat& x, pnfloat& y, pnfloat& z) const
{
  getRadians(x, y, z);

  x = (pnfloat)RADIAN_TO_DEGREE(x);
  y = (pnfloat)RADIAN_TO_DEGREE(y);
  z = (pnfloat)RADIAN_TO_DEGREE(z);
}

void		PNQuatf::getRadians(pnfloat* angles) const
{
  getRadians(angles[0], angles[1], angles[2]);
}

void		PNQuatf::getRadians(pnfloat& roll, pnfloat& pitch, pnfloat& yaw) const
{
  register pnfloat s = -2.0f * (x * z - w * y);

  if (s < 1.0f)
  {
	if (-1.0f < s)
	{
	  roll = atan2f(2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	  pitch = asinf(s);
	  yaw = atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (y * y + z * z));
	}
	else
	{
	  roll = 0.0f;
	  pitch = -1.57079632679489661923f;
	  yaw = -atan2f(-2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
	}
  }
  else
  {
	roll = 0.0f;
	pitch = 1.57079632679489661923f;
	yaw = atan2f(-2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
  }
}

//////////////////////////////////////////////////////////////////////////

void		PNQuatf::slerp(const PNQuatf& q1, PNQuatf& q2, pnfloat interp)
{
  register pnfloat	a, b;

  a = (q1.x - q2.x) * (q1.x - q2.x);
  b = (q1.x + q2.x) * (q1.x + q2.x);

  a += (q1.y - q2.y) * (q1.y - q2.y);
  b += (q1.y + q2.y) * (q1.y + q2.y);

  a += (q1.z - q2.z) * (q1.z - q2.z);
  b += (q1.z + q2.z) * (q1.z + q2.z);

  a += (q1.w - q2.w) * (q1.w - q2.w);
  b += (q1.w + q2.w) * (q1.w + q2.w);
  
  if (a > b)
	q2.invert();

  pnfloat	cosom = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
  pndouble  sclq1, sclq2;

  if ((1.0 + cosom) > 0.00000001)
  {
	if ((1.0 - cosom) > 0.00000001)
	{
	  pndouble  omega = acos(cosom);
	  pndouble  sinom = sin(omega);
	  sclq1 = sin((1.0 - interp) * omega) / sinom;
	  sclq2 = sin(interp * omega) / sinom;
	}
	else
	{
	  sclq1 = 1.0 - interp;
	  sclq2 = interp;
	}

	x = (pnfloat) (sclq1 * q1.x + sclq2 * q2.x);
	y = (pnfloat) (sclq1 * q1.y + sclq2 * q2.y);
	z = (pnfloat) (sclq1 * q1.z + sclq2 * q2.z);
	w = (pnfloat) (sclq1 * q1.w + sclq2 * q2.w);
  }
  else
  {
	x = -q1.y;
	y = q1.x;
	z = -q1.w;
	w = q1.z;

	sclq1 = sin((1.0 - interp)* 0.5 * PI);
	sclq2 = sin(interp * 0.5 * PI);

	x = (pnfloat) (sclq1 * q1.x + sclq2 * x);
	y = (pnfloat) (sclq1 * q1.y + sclq2 * y);
	z = (pnfloat) (sclq1 * q1.z + sclq2 * z);
	w = (pnfloat) (sclq1 * q1.w + sclq2 * w);
  }
}

PNQuatf			PNQuatf::getInvert()
{
  register pnfloat n = x * x + y * y + z * z + w * w;

  return PNQuatf(-x / n, -y / n, -z / n, w / n);
}

//////////////////////////////////////////////////////////////////////////

PNAPI PNPoint	operator*(const PNQuatf& quat, const PNPoint& vec)
{
  register pnfloat tx = 2.0f * quat.x;
  register pnfloat ty = 2.0f * quat.y;
  register pnfloat tz = 2.0f * quat.z;
  register pnfloat twx = tx * quat.w;
  register pnfloat twy = ty * quat.w;
  register pnfloat twz = tz * quat.w;
  register pnfloat txx = tx * quat.x;
  register pnfloat txy = ty * quat.x;
  register pnfloat txz = tz * quat.x;
  register pnfloat tyy = ty * quat.y;
  register pnfloat tyz = tz * quat.y;
  register pnfloat tzz = tz * quat.z;

  return PNPoint(
	vec.x * (1.0f - tyy - tzz) + vec.y * (txy - twz) + vec.z * (txz + twy),
	vec.x * (txy + twz) + vec.y * (1.0f - txx - tzz) + vec.z * (tyz - twx),
	vec.x * (txz - twy) + vec.y * (tyz + twx) + vec.z * (1.0f - txx - tyy));
}

PNAPI PNQuatf	operator*(const PNQuatf& p, const PNQuatf& quat)
{
  PNQuatf	qr(
	p.w * quat.x + p.x * quat.w + p.y * quat.z - p.z * quat.y,
	p.w * quat.y + p.y * quat.w + p.z * quat.x - p.x * quat.z,
	p.w * quat.z + p.z * quat.w + p.x * quat.y - p.y * quat.x,
	p.w * quat.w - p.x * quat.x - p.y * quat.y - p.z * quat.z);

  return qr;
}

//////////////////////////////////////////////////////////////////////////

PNQuatf&
PNQuatf::operator=(const pnfloat* q)
{
  set(q);

  return *this;
}

//////////////////////////////////////////////////////////////////////////

std::ostream&	operator<<(std::ostream& o, const PNQuatf& p)
{
  o << "[x=" << p.x << " y=" << p.y << " z=" << p.z << " w=" << p.w << "]";

  return o;
}

//////////////////////////////////////////////////////////////////////////
};