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

#include <boost/filesystem/path.hpp>

#include "pndefs.h"
#include "pnmath.h"

#include "PNPoint3f.hpp"
#include "PNVector3f.hpp"
#include "PNMatrix4f.hpp"

#include "PNQuatf.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////
  
void
PNQuatf::loadIdentity()
{
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
  w = 1.0f;
}

bool
PNQuatf::isIdentity() const
{
  return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
}

/////////////////////////////////////////////////////////////////////////

void
PNQuatf::set(const PNMatrix4f& mat)
{
  register pnfloat trace = mat[0] + mat[5] + mat[10];
  register pnfloat scale;

  if (trace > 0.0f)
  {
	scale = sqrtf(1.0f + trace);
	w = 0.5f * scale;
	scale = 0.5f / scale;
	x = (mat[6] - mat[9]) * scale;
	y = (mat[8] - mat[2]) * scale;
	z = (mat[1] - mat[4]) * scale;
  }
  else if (mat[0] > mat[5] && mat[0] > mat[10])
  {
	scale = 2.0f * sqrtf(1.0f + mat[0] - mat[5] - mat[10]);
	x = 0.25f * scale;
	y = (mat[1] + mat[4]) / scale;
	z = (mat[2] + mat[8]) / scale;
	w = (mat[6] - mat[9]) / scale;
  }
  else if (mat[5] > mat[10])
  {
	scale = 2.0f * sqrtf(1.0f + mat[5] - mat[0] - mat[10]);
	y = 0.25f * scale;
	x = (mat[1] + mat[4]) / scale;
	z = (mat[6] + mat[9]) / scale;
	w = (mat[2] - mat[8]) / scale;
  }
  else
  {
	scale = 2.0f * sqrtf(1.0f + mat[10] - mat[0] - mat[5]);
	z = 0.25f * scale;
	x = (mat[2] + mat[8]) / scale;
	y = (mat[6] + mat[9]) / scale;
	w = (mat[1] - mat[4]) / scale;
  }
}

/////////////////////////////////////////////////////////////////////////

void
PNQuatf::fromDegrees(const pnfloat* angles)
{
  fromRadians((pnfloat)DEGREE_TO_RADIAN(angles[0]), (pnfloat)DEGREE_TO_RADIAN(angles[1]), (pnfloat)DEGREE_TO_RADIAN(angles[2]));
}

void
PNQuatf::fromDegrees(pnfloat pitch, pnfloat yaw, pnfloat roll)
{
  fromRadians((pnfloat)DEGREE_TO_RADIAN(pitch), (pnfloat)DEGREE_TO_RADIAN(yaw), (pnfloat)DEGREE_TO_RADIAN(roll));
}

void
PNQuatf::fromRadians(const pnfloat* angles)
{
  fromRadians(angles[0], angles[1], angles[2]);
}

void
PNQuatf::fromRadians(pnfloat pitch, pnfloat yaw, pnfloat roll)
{
  register pnfloat	sx, sy, sz, cx, cy, cz;

  register pnfloat	ax = pitch * 0.5f;
  register pnfloat	ay = yaw * 0.5f;
  register pnfloat	az = roll * 0.5f;

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

void
PNQuatf::fromAxisDegrees(const PNVector3f& axis, pnfloat phi)
{
  fromAxisRadians(axis, DEGREE_TO_RADIAN_F(phi));
}

void
PNQuatf::fromAxisRadians(const PNVector3f& axis, pnfloat phi)
{
  register pnfloat a = 0.5f * phi;
  register pnfloat s = sinf(a) / axis.getNorm();

  x = axis.x * s;
  y = axis.y * s;
  z = axis.z * s;
  w = cosf(a);
}

void
PNQuatf::getDegrees(pnfloat* angles) const
{
  getDegrees(angles[0], angles[1], angles[2]);
}

void
PNQuatf::getDegrees(pnfloat& pitch, pnfloat& yaw, pnfloat& roll) const
{
  getRadians(pitch, yaw, roll);

  pitch = RADIAN_TO_DEGREE_F(pitch);
  yaw = RADIAN_TO_DEGREE_F(yaw);
  roll = RADIAN_TO_DEGREE_F(roll);
}

void
PNQuatf::getRadians(pnfloat* angles) const
{
  getRadians(angles[0], angles[1], angles[2]);
}

void
PNQuatf::getRadians(pnfloat& pitch, pnfloat& yaw, pnfloat& roll) const
{
  register pnfloat s = -2.0f * (x * z - w * y);

  if (s < 1.0f)
  {
	if (-1.0f < s)
	{
	  pitch = atan2f(2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	  yaw = asinf(s);
	  roll = atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (y * y + z * z));
	}
	else
	{
	  pitch = 0.0f;
	  yaw = -1.57079632679489661923f;
	  roll = -atan2f(-2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
	}
  }
  else
  {
	pitch = 0.0f;
	yaw = 1.57079632679489661923f;
	roll = atan2f(-2.0f * (x * y - w * z), 2.0f *(x * z + w * y));
  }
}

//////////////////////////////////////////////////////////////////////////

void
PNQuatf::slerp(const PNQuatf& src, const PNQuatf& dest, pnfloat interp)
{
  register pnfloat	a, b;

  a = (src.x - dest.x) * (src.x - dest.x);
  b = (src.x + dest.x) * (src.x + dest.x);

  a += (src.y - dest.y) * (src.y - dest.y);
  b += (src.y + dest.y) * (src.y + dest.y);

  a += (src.z - dest.z) * (src.z - dest.z);
  b += (src.z + dest.z) * (src.z + dest.z);

  a += (src.w - dest.w) * (src.w - dest.w);
  b += (src.w + dest.w) * (src.w + dest.w);

  if (a > b)
  {
	pnfloat	cosom = src.x * -dest.x + src.y * -dest.y + src.z * -dest.z + src.w * -dest.w;
	pndouble  sclsrc, scldest;

	if ((1.0 + cosom) > 0.00000001)
	{
	  if ((1.0 - cosom) > 0.00000001)
	  {
		pndouble  omega = acos(cosom);
		pndouble  sinom = sin(omega);
		sclsrc = sin((1.0 - interp) * omega) / sinom;
		scldest = sin(interp * omega) / sinom;
	  }
	  else
	  {
		sclsrc = 1.0 - interp;
		scldest = interp;
	  }

	  x = (pnfloat) (sclsrc * src.x + scldest * -dest.x);
	  y = (pnfloat) (sclsrc * src.y + scldest * -dest.y);
	  z = (pnfloat) (sclsrc * src.z + scldest * -dest.z);
	  w = (pnfloat) (sclsrc * src.w + scldest * -dest.w);
	}
	else
	{
	  sclsrc = sin((1.0 - interp)* 0.5 * PI);
	  scldest = sin(interp * 0.5 * PI);

	  x = (pnfloat) (sclsrc * src.x + scldest * -src.y);
	  y = (pnfloat) (sclsrc * src.y + scldest * src.x);
	  z = (pnfloat) (sclsrc * src.z + scldest * -src.w);
	  w = (pnfloat) (sclsrc * src.w + scldest * src.z);
	}
  }
  else
  {
	pnfloat	cosom = src.x * dest.x + src.y * dest.y + src.z * dest.z + src.w * dest.w;
	pndouble  sclsrc, scldest;

	if ((1.0 + cosom) > 0.00000001)
	{
	  if ((1.0 - cosom) > 0.00000001)
	  {
		pndouble  omega = acos(cosom);
		pndouble  sinom = sin(omega);
		sclsrc = sin((1.0 - interp) * omega) / sinom;
		scldest = sin(interp * omega) / sinom;
	  }
	  else
	  {
		sclsrc = 1.0 - interp;
		scldest = interp;
	  }

	  x = (pnfloat) (sclsrc * src.x + scldest * dest.x);
	  y = (pnfloat) (sclsrc * src.y + scldest * dest.y);
	  z = (pnfloat) (sclsrc * src.z + scldest * dest.z);
	  w = (pnfloat) (sclsrc * src.w + scldest * dest.w);
	}
	else
	{
	  sclsrc = sin((1.0 - interp)* 0.5 * PI);
	  scldest = sin(interp * 0.5 * PI);

	  x = (pnfloat) (sclsrc * src.x + scldest * -src.y);
	  y = (pnfloat) (sclsrc * src.y + scldest * src.x);
	  z = (pnfloat) (sclsrc * src.z + scldest * -src.w);
	  w = (pnfloat) (sclsrc * src.w + scldest * src.z);
	}
  }
}

void
PNQuatf::slerp(const PNQuatf& dest, pnfloat interp)
{
  slerp(*this, dest, interp);
}

PNQuatf
PNQuatf::getInvert() const
{
  register pnfloat n = x * x + y * y + z * z + w * w;

  return PNQuatf(-x / n, -y / n, -z / n, w / n);
}

//////////////////////////////////////////////////////////////////////////

PNPoint3f
PNQuatf::multiply(const pnfloat *point) const
{
  register pnfloat tx = 2.0f * x;
  register pnfloat ty = 2.0f * y;
  register pnfloat tz = 2.0f * z;
  register pnfloat twx = tx * w;
  register pnfloat twy = ty * w;
  register pnfloat twz = tz * w;
  register pnfloat txx = tx * x;
  register pnfloat txy = ty * x;
  register pnfloat txz = tz * x;
  register pnfloat tyy = ty * y;
  register pnfloat tyz = tz * y;
  register pnfloat tzz = tz * z;

  return PNPoint3f(
	point[0] * (1.0f - tyy - tzz) + point[1] * (txy - twz) + point[2] * (txz + twy),
	point[0] * (txy + twz) + point[1] * (1.0f - txx - tzz) + point[2] * (tyz - twx),
	point[0] * (txz - twy) + point[1] * (tyz + twx) + point[2] * (1.0f - txx - tyy));
}

PNPoint3f
PNQuatf::multiply(const PNPoint3f& point) const
{
  register pnfloat tx = 2.0f * x;
  register pnfloat ty = 2.0f * y;
  register pnfloat tz = 2.0f * z;
  register pnfloat twx = tx * w;
  register pnfloat twy = ty * w;
  register pnfloat twz = tz * w;
  register pnfloat txx = tx * x;
  register pnfloat txy = ty * x;
  register pnfloat txz = tz * x;
  register pnfloat tyy = ty * y;
  register pnfloat tyz = tz * y;
  register pnfloat tzz = tz * z;

  return PNPoint3f(
	point.x * (1.0f - tyy - tzz) + point.y * (txy - twz) + point.z * (txz + twy),
	point.x * (txy + twz) + point.y * (1.0f - txx - tzz) + point.z * (tyz - twx),
	point.x * (txz - twy) + point.y * (tyz + twx) + point.z * (1.0f - txx - tyy));
}

//////////////////////////////////////////////////////////////////////////

PNPoint3f
PNQuatf::operator*(const PNPoint3f& vec) const
{
  register pnfloat tx = 2.0f * x;
  register pnfloat ty = 2.0f * y;
  register pnfloat tz = 2.0f * z;
  register pnfloat twx = tx * w;
  register pnfloat twy = ty * w;
  register pnfloat twz = tz * w;
  register pnfloat txx = tx * x;
  register pnfloat txy = ty * x;
  register pnfloat txz = tz * x;
  register pnfloat tyy = ty * y;
  register pnfloat tyz = tz * y;
  register pnfloat tzz = tz * z;

  return PNPoint3f(
	vec.x * (1.0f - tyy - tzz) + vec.y * (txy - twz) + vec.z * (txz + twy),
	vec.x * (txy + twz) + vec.y * (1.0f - txx - tzz) + vec.z * (tyz - twx),
	vec.x * (txz - twy) + vec.y * (tyz + twx) + vec.z * (1.0f - txx - tyy));
}

PNQuatf
PNQuatf::operator*(const PNQuatf& quat) const
{
  PNQuatf	qr(*this);

  qr *= quat;

  return qr;
}

PNQuatf&
PNQuatf::operator*=(const PNQuatf& quat)
{
  set(
	w * quat.x + x * quat.w + y * quat.z - z * quat.y,
	w * quat.y + y * quat.w + z * quat.x - x * quat.z,
	w * quat.z + z * quat.w + x * quat.y - y * quat.x,
	w * quat.w - x * quat.x - y * quat.y - z * quat.z
	);

  return *this;
}

//////////////////////////////////////////////////////////////////////////

PNQuatf&
PNQuatf::operator=(const pnfloat* q)
{
  set(q);

  return *this;
}

//////////////////////////////////////////////////////////////////////////

pnbool
PNQuatf::operator==(const PNQuatf& quat) const
{
  return x == quat.x && y == quat.y && z == quat.z && w == quat.w;
}

pnbool
PNQuatf::operator!=(const PNQuatf& quat) const
{
  return !operator==(quat);
}

//////////////////////////////////////////////////////////////////////////

std::ostream&
operator<<(std::ostream& o, const PNQuatf& p)
{
  o << "[x=" << p.x << " y=" << p.y << " z=" << p.z << " w=" << p.w << "]";

  return o;
}

//////////////////////////////////////////////////////////////////////////

const PNQuatf	PNQuatf::IDENTITY(0, 0, 0, 1);

//////////////////////////////////////////////////////////////////////////
};

