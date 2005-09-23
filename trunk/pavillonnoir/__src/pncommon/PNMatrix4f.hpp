/*
 * PNMatrix4f.hpp
 * 
 * Description :
 * PNMatrix4f declaration
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

#ifndef _PNMATRIX4F_HPP_
# define _PNMATRIX4F_HPP_

#include <string.h>
#include <iostream>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNQuatf;

/**
 * Complete transformation Matrix
 * 
 * \see PNMatrixTR4f
 */
class PNAPI		PNMatrix4f : public PNObject
{
  friend PNAPI std::ostream&	operator<<(std::ostream& o, const PNMatrix4f& mat);

  //////////////////////////////////////////////////////////////////////////
protected:
  pnmatrix4f	_matrix;
public:
  PNMatrix4f();
  PNMatrix4f(const PNMatrix4f& matrix);
  PNMatrix4f(const pnfloat* matrix);
  PNMatrix4f(
	pnfloat m1, pnfloat m2, pnfloat m3, pnfloat m4,
	pnfloat m5, pnfloat m6, pnfloat m7, pnfloat m8,
	pnfloat m9, pnfloat m10, pnfloat m11, pnfloat m12,
	pnfloat m13, pnfloat m14, pnfloat m15, pnfloat m16);
  explicit PNMatrix4f(const PNQuatf& quat);
  ~PNMatrix4f();

  void			loadIdentity();

  void			set(const pnfloat* matrix);
  void			set(
	pnfloat m1, pnfloat m2, pnfloat m3, pnfloat m4,
	pnfloat m5, pnfloat m6, pnfloat m7, pnfloat m8,
	pnfloat m9, pnfloat m10, pnfloat m11, pnfloat m12,
	pnfloat m13, pnfloat m14, pnfloat m15, pnfloat m16);

  pnfloat		det() const;
  void			invert();

  PNMatrix4f&	postMultiply(const PNMatrix4f& matrix);
  PNMatrix4f&	preMultiply(const PNMatrix4f& matrix);

  void			setTranslation(const pnfloat* trans);
  void			addTranslation(const pnfloat* trans);
  void			setRotationQuaternion(const PNQuatf& quat);
  void			setRotationDegrees(const pnfloat* rot);
  void			setRotationRadians(const pnfloat* rot);

  pnfloat&		operator[](pnint index) {return (_matrix[index]);}
  const pnfloat	*getMatrix() const {return (_matrix);}
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNMATRIX4F_HPP_*/
