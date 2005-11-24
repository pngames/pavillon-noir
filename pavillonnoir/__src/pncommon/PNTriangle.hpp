/*
 * PNTriangle.hpp
 * 
 * Description :
 * Triangle for space partitionning
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

#ifndef _PNTRIANGLE_HPP_
# define _PNTRIANGLE_HPP_

///////////////////////////////////////////////////

#include <vector>

#include "PNVector3f.hpp"
#include "PNNormal3f.hpp"
#include "PNPlane.hpp"

///////////////////////////////////////////////////
 
namespace PN { 
///////////////////////////////////////////////////
 
 class PNAPI PNTriangle : public PNPlane
 {
public:
	PNTriangle		();
	PNTriangle		(const PNTriangle & src);
	PNTriangle		(const PNPoint3f& a, const PNPoint3f& b, const PNPoint3f& c);
	PNTriangle		(const PNPoint3f* array);
	~PNTriangle		();
	
public:
	PNPoint3f&		getPoint				(int id, PNPoint3f& pt) const;
	PNVector3f &	getPoint				(int id, PNVector3f & pt) const;
	pnfloat			getArea					() const;
	PNPlane &		getExtrusionPlane		(int id, PNPlane & plane) const;
	PNPoint3f&		getClosestPoint			(const PNPoint3f& from, PNPoint3f& result) const;
	PNPoint3f&		getClosestPointOnSide	(const PNPoint3f& origin, const PNPoint3f& destination, const PNPoint3f& point, PNPoint3f& result) const;
	
public:
	void			setPoints				(const PNPoint3f& a, const PNPoint3f& b, const PNPoint3f& c);
		
public:
	static bool		isFlat					(PNPoint3f& a, PNPoint3f& b, PNPoint3f& c);
	bool			isInsideTriangle		(const PNPoint3f& point) const;
	bool			isInsideBoundTriangle	(const PNPoint3f& point) const;
	bool			isEquals				(const PNTriangle & triangle, bool exactOrdering) const;
	static bool		areEqual				(PNTriangle * arrayOne, PNTriangle * arrayTwo, int sizeOne, int sizeTwo, bool exactOrdering);
	
		
public:
	bool			clipWith				(PNPlane & plane, std::vector<PNTriangle> & triangles);
	bool			substract				(PNTriangle & triangle, std::vector<PNTriangle> & triangles);
  
private:
	

private:
	PNPoint3f		_pt[3];
 };
 
 ///////////////////////////////////////////////////
 
 }; /* end of namespace */
 
 ///////////////////////////////////////////////////
 
 #endif /* _PNTRIANGLE_HPP_ */
 
 ///////////////////////////////////////////////////
