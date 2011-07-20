/*
 * PNNormal3f.hpp
 * 
 * Description :
 * 3D-Normal declaration
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

#ifndef PN_NORMAL_3F_HPP_
#define PN_NORMAL_3F_HPP_

/////////////////////////////////////

#include <assert.h>

/////////////////////////////////////

#include "pndefs.h"
#include "pnmath.h"
#include "PNVector3f.hpp"

/////////////////////////////////////

namespace PN {

/////////////////////////////////////

class PNAPI							PNNormal3f : private PNVector3f
{
  PNDECLARE(PNNormal3f)

public:
  PNNormal3f();
  PNNormal3f(pnfloat nX, pnfloat nY, pnfloat nZ);
  PNNormal3f(const PNPoint3f& source);

public:
  virtual ~PNNormal3f();

public:
  virtual inline void				setCrd(pnfloat nX, pnfloat nY, pnfloat nZ) { PNVector3f::setCrd(nX, nY, nZ); setNorm(1.0f); }
  virtual inline void				setArray(const pnfloat * array) { PNVector3f::setArray(array); setNorm(1.0f); }
   
public:
  virtual inline pnfloat			getX() const { return (x); }
  virtual inline pnfloat			getY() const { return (y); }
  virtual inline pnfloat			getZ() const { return (z); }  
  virtual inline void				get(pnfloat & nX, pnfloat & nY, pnfloat & nZ)	 const	{ nX = x; nY = y; nZ = z; return; }
  virtual inline void				get(pnfloat* array) const { assert(array!=NULL); array[0]=x; array[1]=y; array[2]=z;}
public:
  virtual inline const PNVector3f&	getVector() const {return *this;}

public:
  virtual void						setFromSegment(const PNPoint3f& origin, const PNPoint3f& extremity);
  
public:
  virtual bool						isColinear(const PNNormal3f& v);
  virtual bool						isColinear(pnfloat nX, pnfloat nY, pnfloat nZ);
  virtual bool						isOrthogonal(const PNNormal3f& v);
  virtual bool						isOrthogonal(pnfloat nX, pnfloat nY, pnfloat nZ);
  virtual bool						isNull();
  
public:
  virtual pnfloat					radianRangePi(const PNNormal3f& n);
  virtual pnfloat					radianRange2Pi(const PNNormal3f& cosinusReferentiel, const PNNormal3f& sinusReferentiel);
  virtual pnfloat					degreeRangePi(const PNNormal3f& n);
  virtual pnfloat					degreeRange2Pi(const PNNormal3f& cosinusReferentiel, const PNNormal3f& sinusReferentiel);
  
public:
  virtual void						crossProduct(const PNPoint3f& u, const PNPoint3f& v);
  virtual void						crossProduct(const PNNormal3f& u, const PNNormal3f& v);
  
public:  
  virtual pnfloat					scalarProduct(const PNNormal3f & n) const;
  virtual pnfloat					scalarProduct(const PNPoint3f& u) const;
  virtual pnfloat					scalarProduct(pnfloat nX, pnfloat nY, pnfloat nZ) const;
  
public:
  virtual pnfloat					getNorm() const;

  //////////////////////////////////////////////////////////////////////////
  
public:
  PNNormal3f&						operator=(const PNPoint3f& p);
};

/////////////////////////////////////

} /* end of namespace */

/////////////////////////////////////

#endif /* PN_NORMAL_3F_HPP_ */

/////////////////////////////////////

