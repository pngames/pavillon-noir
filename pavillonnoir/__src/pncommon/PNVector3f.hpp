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

} /* end of namespace */

/////////////////////////////////////

#endif /* _PNVECTOR3F_HPP_ */
