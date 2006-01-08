/*
 * PNVector3f.hpp
 * 
 * Description :
 * 3D-Vector declaration
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

#ifndef _PNVECTOR3F_HPP_
# define _PNVECTOR3F_HPP_

/////////////////////////////////////

#include <assert.h>

/////////////////////////////////////

#include "pndefs.h"
#include "pnmath.h"
#include "IAutoTestable.hpp"
#include "PNPoint3f.hpp"

/////////////////////////////////////

namespace PN {

/////////////////////////////////////

class PNAPI							PNVector3f : public PNPoint3f
{
public:
  PNVector3f();
  PNVector3f(pnfloat x, pnfloat y, pnfloat z);
  PNVector3f(const PNPoint3f& source);
  PNVector3f(const PNPoint3f& origin, const PNPoint3f& destination);

public:
  virtual ~PNVector3f();

public:
  virtual inline void				setCrd(pnfloat vX, pnfloat vY, pnfloat vZ) { x = vX; y = vY; z = vZ; }
  virtual inline void				setArray(const pnfloat * array) { assert(array != NULL); x=array[0]; y=array[1]; z=array[2]; }

public:  
  virtual void						get(pnfloat& destX, pnfloat& destY, pnfloat& destZ); 
  virtual void						get(pnfloat* array);

public:
  virtual void						setFromSegment(const PNPoint3f& origin, const PNPoint3f& extremity);
  
public:
  virtual bool						isColinear(const PNVector3f& v);
  virtual bool						isColinear(pnfloat vX, pnfloat vY, pnfloat vZ);
  virtual bool						isOrthogonal(const PNVector3f& v);
  virtual bool						isOrthogonal(pnfloat vX, pnfloat vY, pnfloat vZ);

public:
  virtual void						substract(const PNPoint3f& v);
  virtual void						substract(pnfloat vX, pnfloat vY, pnfloat vZ);
  virtual void						substract(const PNPoint3f& v, const PNPoint3f& u);
  virtual void						add(const PNPoint3f& v);
  virtual void						add(const PNPoint3f& u, const PNPoint3f& v);  
  virtual void						add(pnfloat vX, pnfloat vY, pnfloat vZ);
  virtual void						multiply(pnfloat constant);
  
public:
  virtual void						setNorm(pnfloat newNorm);
  static  void						setNorm(pnfloat* v, pnfloat newNorm);
  virtual pnfloat					getNorm() const;
  static pnfloat					getNorm(pnfloat* v);

public:
  virtual pnfloat					scalarProduct(const PNVector3f& v) const;
  virtual pnfloat					scalarProduct(pnfloat vX, pnfloat vY, pnfloat vZ) const;
  virtual void						crossProduct(const PNVector3f& u, const PNVector3f& v);

public:
  virtual bool						isBelongToSegment(const PNPoint3f& origin, const PNPoint3f& extremity);
  virtual bool						intersection(const PNPoint3f& originOne, const PNPoint3f& extremityOne, const PNPoint3f& originTwo, const PNPoint3f& extremityTwo);

public: /* special points */
  static const PNVector3f			ZERO;
  static const PNVector3f			UNIT_X;
  static const PNVector3f			UNIT_Y;
  static const PNVector3f			UNIT_Z;
  static const PNVector3f			NEGATIVE_UNIT_X;
  static const PNVector3f			NEGATIVE_UNIT_Y;
  static const PNVector3f			NEGATIVE_UNIT_Z;
  static const PNVector3f			UNIT_SCALE;
};

/////////////////////////////////////

/**
* \return	the norm of the vector
*/
inline pnfloat
PNVector3f::getNorm() const
{
  return (sqrtf(x * x + y * y + z * z));
}

inline pnfloat
PNVector3f::getNorm(pnfloat* v)
{
  return (sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

/**
* \brief Scales the vector to fit the specified new norm. 
* Note: It is an error to call this method on a vector whoose norm is lesser than
* EPSILON. An assertion will be broken in DEBUG mode, but in release mode, calling
* this method on a null vector may result in an undefined behavior.
* 
* \param	newNorm		the new norm of the vector
* \return	void
*/
inline void
PNVector3f::setNorm(pnfloat newNorm)
{
  register pnfloat	factor;

  assert(!this->isNull() && "FATAL-ERROR: You try to normalize a null vector... bug ?");

  factor = newNorm / this->getNorm();

  x *= factor;
  y *= factor;
  z *= factor;
}

inline void
PNVector3f::setNorm(pnfloat* v, pnfloat newNorm)
{
  register pnfloat	factor;

  factor = newNorm / getNorm(v);

  v[0] *= factor;
  v[1] *= factor;
  v[2] *= factor;
}

};

/////////////////////////////////////

#endif /* _PNVECTOR3F_HPP_ */
