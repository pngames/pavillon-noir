/*
 * PNMatrix4f.cpp
 * 
 * Description :
 * PNMatrix4f definition
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

#include <math.h>

#include "pndefs.h"
#include "pnmath.h"

#include "PNMatrix4f.hpp"

#include "PNQuatf.hpp"

#define DET2(a00,a01, \
  a10,a11) ((a00)*(a11)-(a10)*(a01))

#define DET3(a00,a01,a02, \
  a10,a11,a12, \
  a20,a21,a22) ((a00)*DET2(a11,a12,a21,a22) - \
  (a10)*DET2(a01,a02,a21,a22) + \
  (a20)*DET2(a01,a02,a11,a12))

#define DET4(a00,a01,a02,a03, \
  a10,a11,a12,a13, \
  a20,a21,a22,a23, \
  a30,a31,a32,a33) ((a00)*DET3(a11,a12,a13,a21,a22,a23,a31,a32,a33) - \
  (a10)*DET3(a01,a02,a03,a21,a22,a23,a31,a32,a33) + \
  (a20)*DET3(a01,a02,a03,a11,a12,a13,a31,a32,a33) - \
  (a30)*DET3(a01,a02,a03,a11,a12,a13,a21,a22,a23))

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNMatrix4f::PNMatrix4f()
{}

PNMatrix4f::PNMatrix4f(const PNMatrix4f& mat)
{
  set(mat._matrix);
}

PNMatrix4f::PNMatrix4f(const pnfloat* mat)
{
  set(mat);
}

PNMatrix4f::PNMatrix4f(pnfloat m1, pnfloat m2, pnfloat m3, pnfloat m4,
					   pnfloat m5, pnfloat m6, pnfloat m7, pnfloat m8,
					   pnfloat m9, pnfloat m10, pnfloat m11, pnfloat m12,
					   pnfloat m13, pnfloat m14, pnfloat m15, pnfloat m16)
{
  set(&m1);
}

PNMatrix4f::PNMatrix4f(const PNQuatf& quat)
{
  setRotationQuaternion(quat);
}

PNMatrix4f::~PNMatrix4f()
{}

//////////////////////////////////////////////////////////////////////////

pnfloat			PNMatrix4f::det() const
{
  return DET4(
	_matrix[0], _matrix[1], _matrix[2], _matrix[3],
	_matrix[4], _matrix[5], _matrix[6], _matrix[7],
	_matrix[8], _matrix[9], _matrix[10], _matrix[11],
	_matrix[12], _matrix[13], _matrix[14], _matrix[15]);
}

static void		m4_submat(const pnfloat *mr, pnfloat *mb, int i, int j)
{
  int			ti, tj, idst, jdst;

  for (ti = 0; ti < 4; ti++)
  {
	if (ti < i)
	  idst = ti;
	else/* if (ti > i)*/
	  idst = ti - 1;

	for (tj = 0; tj < 4; tj++)
	{
	  if (tj < j)
		jdst = tj;
	  else/* if (tj > j)*/
		jdst = tj - 1;

	  if (ti != i && tj != j)
		mb[idst + (jdst * 3)] = mr[ti + (tj * 4)];
	}
  }
}

static int		m4_inverse(pnfloat *mr, const pnfloat *ma)
{
  float			mdet = DET4(
	ma[0], ma[1], ma[2], ma[3],
	ma[4], ma[5], ma[6], ma[7],
	ma[8], ma[9], ma[10], ma[11],
	ma[12], ma[13], ma[14], ma[15]);

  pnmatrix3f	mtemp;
  int			i, j, sign;

  if (fabs(mdet) < 0.0005)
	return (0);

  for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	{
	  sign = 1 - ((i + j) % 2) * 2;

	  m4_submat(ma, mtemp, i, j);

	  float m3det = DET3(
		mtemp[0], mtemp[1], mtemp[2],
		mtemp[3], mtemp[4], mtemp[5],
		mtemp[6], mtemp[7], mtemp[8]);

	  mr[i * 4 + j] = (m3det * sign) / mdet;
	}

	return (1);
}

void			PNMatrix4f::invert()
{
  pnmatrix4f	tmp;

  m4_inverse(tmp, _matrix);
  set(tmp);
}

//////////////////////////////////////////////////////////////////////////

void			PNMatrix4f::set(const pnfloat* matrix)
{
  memcpy(_matrix, matrix, sizeof(_matrix));
}

inline void		PNMatrix4f::set(pnfloat m1, pnfloat m2, pnfloat m3, pnfloat m4,
								pnfloat m5, pnfloat m6, pnfloat m7, pnfloat m8,
								pnfloat m9, pnfloat m10, pnfloat m11, pnfloat m12,
								pnfloat m13, pnfloat m14, pnfloat m15, pnfloat m16)
{
  set(&m1);
}

void			PNMatrix4f::loadIdentity()
{
  memset(_matrix, 0, sizeof(_matrix));
  _matrix[0] = _matrix[5] = _matrix[10] = _matrix[15] = 1.0f;
}

//////////////////////////////////////////////////////////////////////////

PNMatrix4f&		PNMatrix4f::postMultiply(const PNMatrix4f& matrix)
{
  pnmatrix4f	newMatrix;
  const pnfloat	*m1 = _matrix, *m2 = matrix._matrix;

  newMatrix[0]	= m1[0] * m2[0]  + m1[4] * m2[1]  + m1[8]  * m2[2];
  newMatrix[1]	= m1[1] * m2[0]  + m1[5] * m2[1]  + m1[9]  * m2[2];
  newMatrix[2]	= m1[2] * m2[0]  + m1[6] * m2[1]  + m1[10] * m2[2];
  newMatrix[3]	= m1[3] * m2[0]  + m1[7] * m2[1]  + m1[11] * m2[2];

  newMatrix[4]	= m1[0] * m2[4]  + m1[4] * m2[5]  + m1[8]  * m2[6];
  newMatrix[5]	= m1[1] * m2[4]  + m1[5] * m2[5]  + m1[9]  * m2[6];
  newMatrix[6]	= m1[2] * m2[4]  + m1[6] * m2[5]  + m1[10] * m2[6];
  newMatrix[7]	= m1[3] * m2[4]  + m1[7] * m2[5]  + m1[11] * m2[6];

  newMatrix[8]	= m1[0] * m2[8]  + m1[4] * m2[9]  + m1[8]  * m2[10];
  newMatrix[9]	= m1[1] * m2[8]  + m1[5] * m2[9]  + m1[9]  * m2[10];
  newMatrix[10]	= m1[2] * m2[8]  + m1[6] * m2[9]  + m1[10] * m2[10];
  newMatrix[11]	= m1[3] * m2[8]	 + m1[7] * m2[9]  + m1[11] * m2[10];

  newMatrix[12]	= m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12];
  newMatrix[13]	= m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13];
  newMatrix[14]	= m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14];
  newMatrix[15]	= m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15];

  set(newMatrix);

  return *this;
}

PNMatrix4f&		PNMatrix4f::preMultiply(const PNMatrix4f& matrix)
{
  pnmatrix4f	newMatrix;
  const pnfloat	*m1 = matrix._matrix;
  const pnfloat	*m2 = _matrix;

  newMatrix[0]	= m1[0] * m2[0]  + m1[4] * m2[1]  + m1[8]  * m2[2];
  newMatrix[1]	= m1[1] * m2[0]  + m1[5] * m2[1]  + m1[9]  * m2[2];
  newMatrix[2]	= m1[2] * m2[0]  + m1[6] * m2[1]  + m1[10] * m2[2];
  newMatrix[3]	= m1[3] * m2[0]  + m1[7] * m2[1]  + m1[11] * m2[2];

  newMatrix[4]	= m1[0] * m2[4]  + m1[4] * m2[5]  + m1[8]  * m2[6];
  newMatrix[5]	= m1[1] * m2[4]  + m1[5] * m2[5]  + m1[9]  * m2[6];
  newMatrix[6]	= m1[2] * m2[4]  + m1[6] * m2[5]  + m1[10] * m2[6];
  newMatrix[7]	= m1[3] * m2[4]  + m1[7] * m2[5]  + m1[11] * m2[6];

  newMatrix[8]	= m1[0] * m2[8]  + m1[4] * m2[9]  + m1[8]  * m2[10];
  newMatrix[9]	= m1[1] * m2[8]  + m1[5] * m2[9]  + m1[9]  * m2[10];
  newMatrix[10]	= m1[2] * m2[8]  + m1[6] * m2[9]  + m1[10] * m2[10];
  newMatrix[11]	= m1[3] * m2[8]	 + m1[7] * m2[9]  + m1[11] * m2[10];

  newMatrix[12]	= m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12];
  newMatrix[13]	= m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13];
  newMatrix[14]	= m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14];
  newMatrix[15]	= m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15];

  set(newMatrix);

  return *this;
}

void			PNMatrix4f::setTranslation(const pnfloat* trans)
{
  _matrix[12] = trans[0];
  _matrix[13] = trans[1];
  _matrix[14] = trans[2];
}

void			PNMatrix4f::addTranslation(const pnfloat* trans)
{
  _matrix[12] += trans[0];
  _matrix[13] += trans[1];
  _matrix[14] += trans[2];
}

void			PNMatrix4f::setRotationQuaternion(const PNQuatf& quat)
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

  _matrix[0]  = 1.0f -	tyy - tzz;
  _matrix[1]  = 		txy + twz;
  _matrix[2]  = 		txz - twy;

  _matrix[4]  = 		txy - twz;
  _matrix[5]  = 1.0f -	txx - tzz;
  _matrix[6]  = 		tyz + twx;

  _matrix[8]  = 		txz + twy;
  _matrix[9]  = 		tyz - twx;
  _matrix[10] = 1.0f -	txx - tyy;
}

void			PNMatrix4f::setRotationDegrees(const pnfloat* rot)
{
  pnpoint3f		vec =
  {
	(pnfloat) DEGREE_TO_RADIAN(rot[0]),
	(pnfloat) DEGREE_TO_RADIAN(rot[1]),
	(pnfloat) DEGREE_TO_RADIAN(rot[2])
  };

  setRotationRadians(vec);
}

void			PNMatrix4f::setRotationRadians(const pnfloat* rot)
{
  register pnfloat cx = cos(rot[0]);
  register pnfloat sx = sin(rot[0]);
  register pnfloat cy = cos(rot[1]);
  register pnfloat sy = sin(rot[1]);
  register pnfloat cz = cos(rot[2]);
  register pnfloat sz = sin(rot[2]);

  register pnfloat cxsy = cx * sy;
  register pnfloat sxsy = sx * sy;

  _matrix[0]  = cy * cz;
  _matrix[1]  = cy * sz;
  _matrix[2]  = -sy;

  _matrix[4]  = sxsy * cz - cx * sz;
  _matrix[5]  = sxsy * sz + cx * cz;
  _matrix[6]  = sx * cy;

  _matrix[8]  = cxsy * cz + sy * sz;
  _matrix[9]  = cxsy * sz - sx * cz;
  _matrix[10] = cx * cy;
}

//////////////////////////////////////////////////////////////////////////

std::ostream&	operator<<(std::ostream& o, const PNMatrix4f& mat)
{
  o << "{" << std::endl <<
	mat[0] << "\t" << mat[1] << "\t" << mat[2] << "\t" << mat[3] << std::endl <<
	mat[4] << "\t" << mat[5] << "\t" << mat[6] << "\t" << mat[7] << std::endl <<
	mat[8] << "\t" << mat[9] << "\t" << mat[10] << "\t" << mat[11] << std::endl <<
	mat[12] << "\t" << mat[13] << "\t" << mat[14] << "\t" << mat[15] << std::endl <<
	"}" << std::endl;

  return o;
}

//////////////////////////////////////////////////////////////////////////
};
