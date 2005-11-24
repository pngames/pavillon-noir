/*
 * PNPlane.hpp
 * 
 * Description :
 * 3D-Plane declaration
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

#ifndef PNPLANE_HPP_
#define PNPLANE_HPP_

////////////////////////////////////////

#include "pndefs.h"
#include "IAutoTestable.hpp"

////////////////////////////////////////

namespace PN {

////////////////////////////////////////

typedef enum
  {
    BehindPlane = -1,
    OnPlane = 0,    
    InFrontOfPlane = 1,
    ClippedByPlane = 2
  }
planeSide_t;

////////////////////////////////////////

class PNAPI PNPlane
{
public:
  PNPlane	();
  PNPlane	(pnfloat x, pnfloat y, pnfloat z, pnfloat d);
  PNPlane	(const PNPoint3f& position, const PNNormal3f & orientation);
  PNPlane	(const PNPlane & source);

public:
  virtual ~PNPlane	();

public:
  virtual void		setEquation					(pnfloat x, pnfloat y, pnfloat z, pnfloat d);
  virtual void		setPosition					(const PNPoint3f& position);
  virtual void		setOrientation				(const PNNormal3f & orientation);
  virtual void		setPlane					(const PNPoint3f& position, const PNNormal3f & orientation);

public:
  virtual PNPoint3f&	   getPosition				(PNPoint3f& position)	const;
  virtual PNVector3f & getPosition				(PNVector3f & position) const;
  virtual PNNormal3f & 	getOrientation			(PNNormal3f & orientation) const;
  virtual pnfloat		getOrientationX			() const;
  virtual pnfloat		getOrientationY			() const;
  virtual pnfloat		getOrientationZ			() const;
  virtual pnfloat		getDistanceFromOrigin	() const;
  virtual pnfloat 		getDistanceFromPlane	(const PNPoint3f& position) const;
  
public:
  virtual PNPoint3f&	projectionOnPlane			(const PNPoint3f& point, PNPoint3f& result) const;

public:
  virtual bool isSegmentIntersectPlane			(const PNPoint3f& segOrigin, const PNPoint3f& segDestination, PNPoint3f& intersection);
  virtual bool isRayIntersectPlane				(const PNPoint3f& rayOrigin, const PNNormal3f & rayDirection, PNPoint3f& intersection);
  virtual bool isEquals							(const PNPlane & plane);

public:
  virtual planeSide_t classifyVertex			(const PNPoint3f& position) const;
  virtual planeSide_t classifyTriangle			(const PNPoint3f& a, const PNPoint3f& b, const PNPoint3f& c);  

private:
  pnfloat		_x;
  pnfloat		_y;
  pnfloat		_z;
  pnfloat		_d;
};

////////////////////////////////////////

} /* end of namespace */

////////////////////////////////////////

#endif /* PNPLANE_HPP_ */

////////////////////////////////////////
