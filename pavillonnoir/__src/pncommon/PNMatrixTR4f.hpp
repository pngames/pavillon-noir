/*
 * PNMatrixTR4f.hpp
 * 
 * Description :
 * PNMatrixTR4f declaration
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

#ifndef _PNMATRIXTR4F_HPP_
# define _PNMATRIXTR4F_HPP_

#include <string.h>

#include "PNMatrix4f.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNPoint;
class PNVector3f;

/**
 * Partial transformation Matrix with just rotations and translations
 * 
 * @see PNMatrix4f
 */
class PNAPI		PNMatrixTR4f : public PNMatrix4f
{
public:
  PNMatrixTR4f();
  PNMatrixTR4f(const PNMatrix4f& matrix);
  PNMatrixTR4f(const pnfloat* matrix);
  PNMatrixTR4f(
	pnfloat m1, pnfloat m2, pnfloat m3, pnfloat m4,
	pnfloat m5, pnfloat m6, pnfloat m7, pnfloat m8,
	pnfloat m9, pnfloat m10, pnfloat m11, pnfloat m12,
	pnfloat m13, pnfloat m14, pnfloat m15, pnfloat m16);
  explicit PNMatrixTR4f(const PNQuatf& quat);
  ~PNMatrixTR4f();

  PNMatrixTR4f&	postMultiply(const PNMatrixTR4f& matrix);
  PNMatrixTR4f&	preMultiply(const PNMatrixTR4f& matrix);

  pnfloat*		transform(pnfloat* vdest, const pnfloat* vsrc, pnfloat weight) const;
  pnfloat*		transform3(pnfloat* vdest, const pnfloat* vsrc, pnfloat weight) const;

  pnfloat*		transform(pnfloat* vdest, const pnfloat* vsrc) const;
  pnfloat*		transform3(pnfloat* vdest, const pnfloat* vsrc) const;

  pnfloat*		transform(pnfloat* vec) const;
  pnfloat*		transform3(pnfloat* vec) const;

  //////////////////////////////////////////////////////////////////////////
  
  PNPoint		operator*(const PNPoint& vec) const;
  PNVector3f	operator*(const PNVector3f& vec) const;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNMATRIXTR4F_HPP_*/
