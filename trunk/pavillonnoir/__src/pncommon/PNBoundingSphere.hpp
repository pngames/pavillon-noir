/*
 * PNBoundingSphere.hpp
 * 
 * Description :
 * PNBoundingSphere declaration
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

#ifndef _PNBOUNDINGSPHERE_HPP_
# define _PNBOUNDINGSPHERE_HPP_

#include <string>
#include <vector>

#include "PNObject.hpp"
#include "PNPoint.hpp"
#include "PNVector3f.hpp"
#include "PNNormal3f.hpp"
#include "PNPlane.hpp"
#include "PNTriangle.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNAPI PNBoundingSphere : public PNObject
{
public:
  PNBoundingSphere		(void);
  PNBoundingSphere		(const PNPoint & radius, const PNPoint & position);  
  PNBoundingSphere		(const PNBoundingSphere & source);    
  ~PNBoundingSphere		(void);

public:
  void	setRadius	(pnfloat x, pnfloat y, pnfloat z)							{ _radius.setCrd(x, y, z); _sqrRadius.setCrd(x*x, y*y, z*z); }
  void	setRadius	(const PNPoint & radius)									{ setRadius(radius.x, radius.y, radius.z); }
  void	setPosition	(pnfloat x, pnfloat y, pnfloat z)							{ _position.x = x; _position.y = y; _position.z = z; }
  void	setPosition	(const PNPoint & position)									{ _position = position; }
  
public:
  void	translate	(pnfloat x, pnfloat y, pnfloat z)							{ _position.x += x; _position.y += y; _position.z += z; }
  void	translate	(PNVector3f & t)											{ _position.x += t.x; _position.y += t.y; _position.z += t.z; }

public:
  PNPoint & 	getRadius	(PNPoint & result)					const			{ result = _radius; return (result); }
  PNPoint &		getPosition	(PNPoint & result)						const		{ result = _position; return (result); }
  
  const PNPoint &	getPosition	(void) const									{ return (_position); }
  const PNPoint &	getRadius	(void) const									{ return (_radius); }
  
public:
	pnfloat			computeDistanceFromCenterToSurface (PNPoint & direction);

public:  
  bool  	testCollisionWithTriangle	(const PNTriangle & triangle, PNVector3f & correction) const;
 
private:
  PNVector3f	_radius;
  PNVector3f	_sqrRadius;
  PNPoint		_position;	
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNBOUNDINGSPHERE_HPP_*/
