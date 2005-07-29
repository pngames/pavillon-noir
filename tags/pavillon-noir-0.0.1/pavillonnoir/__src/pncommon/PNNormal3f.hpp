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
#include "IAutoTestable.hpp"
#include "PNVector3f.hpp"

/////////////////////////////////////

namespace PN {

/////////////////////////////////////

class PNAPI							PNNormal3f : private PNVector3f, public IAutoTestable
{
public:
  PNNormal3f();
  PNNormal3f(pnfloat nX, pnfloat nY, pnfloat nZ);
  PNNormal3f(const PNNormal3f & source);

public:
  virtual ~PNNormal3f();

public:
  virtual inline void				setCrd(pnfloat nX, pnfloat nY, pnfloat nZ)	{ PNVector3f::setCrd(nX, nY, nZ); setNorm(1.0f); return; }
  virtual inline void				setArray(const pnfloat * array)				{ PNVector3f::setArray(array); setNorm(1.0f);}
   
public:
  virtual inline pnfloat			getX()	const											{ return (x); }
  virtual inline pnfloat			getY()	const											{ return (y); }
  virtual inline pnfloat			getZ()	const 											{ return (z); }  
  virtual inline void				get(pnfloat & nX, pnfloat & nY, pnfloat & nZ)	 const	{ nX = x; nY = y; nZ = z; return; }
  virtual inline void				get(pnfloat * array)							 const 	{ assert(array!=NULL); array[0]=x;array[1]=y;array[2]=z;}
public:
  virtual inline const PNVector3f&	getVector() const {return *this;};

public:
  virtual void						setFromSegment(const PNPoint & origin, const PNPoint & extremity);
  
public:
  virtual bool						isColinear(PNNormal3f & v);
  virtual bool						isColinear(pnfloat nX, pnfloat nY, pnfloat nZ);
  virtual bool						isOrthogonal(PNNormal3f & v);
  virtual bool						isOrthogonal(pnfloat nX, pnfloat nY, pnfloat nZ);
  virtual bool						isNull();
  
public:
  virtual pnfloat					radianRangePi(PNNormal3f & n);
  virtual pnfloat					radianRange2Pi(PNNormal3f & cosinusReferentiel, PNNormal3f & sinusReferentiel);
  virtual pnfloat					degreeRangePi(PNNormal3f & n);
  virtual pnfloat					degreeRange2Pi(PNNormal3f & cosinusReferentiel, PNNormal3f & sinusReferentiel);
  
public:
  virtual void						crossProduct(PNPoint & u, PNPoint & v);
  virtual void						crossProduct(PNNormal3f & u, PNNormal3f & v);
  
public:  
  virtual pnfloat					scalarProduct(const PNNormal3f & n) const;
  virtual pnfloat					scalarProduct(const PNPoint & u) const;
  virtual pnfloat					scalarProduct(pnfloat nX, pnfloat nY, pnfloat nZ) const;
  
public:
  virtual pnfloat getNorm			();

public:
  virtual std::string toString	(std::string title) const;

public: /* XXX: unit test interface, Don't TOUCH! */
  bool	___IsEqualsTo		(IAutoTestable * testable, std::string & bugReport);
  bool	___IsNotEqualsTo	(IAutoTestable * testable, std::string & bugReport);
};

/////////////////////////////////////

} /* end of namespace */

/////////////////////////////////////

#endif /* PN_NORMAL_3F_HPP_ */

/////////////////////////////////////
