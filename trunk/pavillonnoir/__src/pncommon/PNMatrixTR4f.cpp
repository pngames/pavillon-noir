/*
 * PNMatrixTR4f.cpp
 * 
 * Description :
 * PNMatrixTR4f definition
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

#include "PNMatrixTR4f.hpp"
#include "PNQuatf.hpp"
#include "PNPoint3f.hpp"
#include "PNVector3f.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNMatrixTR4f::PNMatrixTR4f()
{}

PNMatrixTR4f::PNMatrixTR4f(const PNMatrix4f& mat) : PNMatrix4f(mat)
{}

PNMatrixTR4f::PNMatrixTR4f(const pnfloat* mat) : PNMatrix4f(mat)
{}

PNMatrixTR4f::PNMatrixTR4f(pnfloat m1, pnfloat m2, pnfloat m3, pnfloat m4,
						   pnfloat m5, pnfloat m6, pnfloat m7, pnfloat m8,
						   pnfloat m9, pnfloat m10, pnfloat m11, pnfloat m12,
						   pnfloat m13, pnfloat m14, pnfloat m15, pnfloat m16) : 
PNMatrix4f(
		   m1, m2, m3, m4,
		   m5, m6, m7, m8,
		   m9, m10, m11, m12,
		   m13, m14, m15, m16)
{}

PNMatrixTR4f::PNMatrixTR4f(const PNQuatf& quat) : PNMatrix4f(quat)
{}

PNMatrixTR4f::~PNMatrixTR4f()
{}

//////////////////////////////////////////////////////////////////////////
  
PNMatrixTR4f&		PNMatrixTR4f::postMultiply(const PNMatrixTR4f& matrix)
{
  pnmatrix4f	newMatrix;
  const pnfloat	*m1 = _matrix;
  const pnfloat	*m2 = matrix._matrix;

  newMatrix[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2];
  newMatrix[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2];
  newMatrix[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2];

  newMatrix[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6];
  newMatrix[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6];
  newMatrix[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6];

  newMatrix[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10];
  newMatrix[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10];
  newMatrix[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10];

  newMatrix[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12];
  newMatrix[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13];
  newMatrix[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14];

  set(newMatrix);

  return *this;
}

PNMatrixTR4f&		PNMatrixTR4f::preMultiply(const PNMatrixTR4f& matrix)
{
  pnmatrix4f	newMatrix;
  const pnfloat	*m1 = matrix._matrix;
  const pnfloat	*m2 = _matrix;

  newMatrix[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2];
  newMatrix[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2];
  newMatrix[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2];

  newMatrix[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6];
  newMatrix[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6];
  newMatrix[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6];

  newMatrix[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10];
  newMatrix[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10];
  newMatrix[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10];

  newMatrix[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12];
  newMatrix[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13];
  newMatrix[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14];

  set(newMatrix);

  return *this;
}

pnfloat*		PNMatrixTR4f::transform(pnfloat* vdest, const pnfloat* vsrc, pnfloat weight) const
{
  pnfloat v1 = weight * (vsrc[0] * _matrix[0] + vsrc[1] * _matrix[4] + vsrc[2] * _matrix[8] + _matrix[12]);
  pnfloat v2 = weight * (vsrc[0] * _matrix[1] + vsrc[1] * _matrix[5] + vsrc[2] * _matrix[9] + _matrix[13]);
  pnfloat v3 = weight * (vsrc[0] * _matrix[2] + vsrc[1] * _matrix[6] + vsrc[2] * _matrix[10] + _matrix[14]);

  vdest[0] = v1;
  vdest[1] = v2;
  vdest[2] = v3;

  return vdest;
}

pnfloat*		PNMatrixTR4f::transform(pnfloat* vec) const
{
  pnfloat v1 = vec[0] * _matrix[0] + vec[1] * _matrix[4] + vec[2] * _matrix[8] + _matrix[12];
  pnfloat v2 = vec[0] * _matrix[1] + vec[1] * _matrix[5] + vec[2] * _matrix[9] + _matrix[13];
  pnfloat v3 = vec[0] * _matrix[2] + vec[1] * _matrix[6] + vec[2] * _matrix[10] + _matrix[14];

  vec[0] = v1;
  vec[1] = v2;
  vec[2] = v3;

  return (vec);
}

pnfloat*		PNMatrixTR4f::transform3(pnfloat* vdest, const pnfloat* vsrc, pnfloat weight) const
{
  pnfloat v1 = weight * (vsrc[0] * _matrix[0] + vsrc[1] * _matrix[4] + vsrc[2] * _matrix[8]);
  pnfloat v2 = weight * (vsrc[0] * _matrix[1] + vsrc[1] * _matrix[5] + vsrc[2] * _matrix[9]);
  pnfloat v3 = weight * (vsrc[0] * _matrix[2] + vsrc[1] * _matrix[6] + vsrc[2] * _matrix[10]);

  vdest[0] = v1;
  vdest[1] = v2;
  vdest[2] = v3;

  return vdest;
}

pnfloat			*PNMatrixTR4f::transform3(pnfloat* vec) const
{
  pnfloat v1 = vec[0] * _matrix[0] + vec[1] * _matrix[4] + vec[2] * _matrix[8];
  pnfloat v2 = vec[0] * _matrix[1] + vec[1] * _matrix[5] + vec[2] * _matrix[9];
  pnfloat v3 = vec[0] * _matrix[2] + vec[1] * _matrix[6] + vec[2] * _matrix[10];

  vec[0] = v1;
  vec[1] = v2;
  vec[2] = v3;

  return (vec);
}

//////////////////////////////////////////////////////////////////////////

PNPoint3f			PNMatrixTR4f::operator*(const PNPoint3f& vec) const
{
  return PNPoint3f(
	vec.x * _matrix[0] + vec.y * _matrix[4] + vec.z * _matrix[8] + _matrix[12],
	vec.x * _matrix[1] + vec.y * _matrix[5] + vec.z * _matrix[9] + _matrix[13],
	vec.x * _matrix[2] + vec.y * _matrix[6] + vec.z * _matrix[10] + _matrix[14]
	);
}

PNVector3f		PNMatrixTR4f::operator*(const PNVector3f& vec) const
{
  return PNVector3f(
	vec.x * _matrix[0] + vec.y * _matrix[4] + vec.z * _matrix[8],
	vec.x * _matrix[1] + vec.y * _matrix[5] + vec.z * _matrix[9],
	vec.x * _matrix[2] + vec.y * _matrix[6] + vec.z * _matrix[10]
	);
}

//////////////////////////////////////////////////////////////////////////
};
