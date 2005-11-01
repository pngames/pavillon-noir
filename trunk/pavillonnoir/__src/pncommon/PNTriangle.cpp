/*
 * PNTriangle.cpp
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

#include <iostream>
using namespace std;

///////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

///////////////////////////////////////////////////

#include "pndefs.h"
#include "pnmath.h"
#include "PNTriangle.hpp" 

///////////////////////////////////////////////////

namespace PN {

///////////////////////////////////////////////////

/**
 * private usage, used for clipping
 */
class PtClipper : public PNPoint
{
public:
	PtClipper	()											{ _origin = NULL; _extremity = NULL; x = 0; y = 0; z = 0; return; }
	PtClipper	(PNPoint & pt)								{ _origin = NULL; _extremity = NULL; x = pt.x; y = pt.y; z = pt.z; }	
public:
	void	setSide(PNPoint & origin, PNPoint & extremity)	{ _origin = &origin; _extremity = &extremity; return; }
	pnfloat	getInterpolationValue()							{ assert(isClipped() == true); return (getDistance(*_origin) / _origin->getDistance(*_extremity)); }
	bool	isClipped()										{ return (_origin != NULL && _extremity != NULL); }
	
private:
	PNPoint * _origin;
	PNPoint	* _extremity;
};

///////////////////////////////////////////////////

static void
buildTriangle(vector<PtClipper> & pts, pnuint id0, pnuint id1, pnuint id2, vector<PNTriangle> & triangles)
{
	PNTriangle	triangle;
	
	triangle.setPoints(pts[id0], pts[id1], pts[id2]);
	triangles.push_back(triangle);
	
	return;
}

///////////////////////////////////////////////////

/**
 * \brief Default constructor for triangle.
 * Constructs the triangle with the following default coordinates:
 *   pt 0 : -10, 0, 0
 *   pt 1 : 10, 0, 0
 *   pt 2 : 0, 0, -10
 * The triangle is oriented in counter-clockwise mode.
 */
PNTriangle::PNTriangle()
{
	PNVector3f	a(-10, 0, 0);
	PNVector3f	b(10, 0, 0);
	PNVector3f	c(0, 0, -10);
	
	setPoints(a, b, c);
	
	return;
}

/**
 * \brief copy constructor for triangle.
 * 
 * \param	src		source of the copy
 */
PNTriangle::PNTriangle(const PNTriangle & src)
{
	setPoints(src._pt[0], src._pt[1], src._pt[2]);
	return;
}

/**
 * \brief Constructs a triangle with the specified coordinates.
 * Note: it is an error to try building a flat triangle. In DEBUG version
 * an assertion will be broken. In RELEASE version this may lead to an undefined behavior.
 * The triangle is oriented in counter-clockwise mode.
 * 
 * \param	a	first point
 * \param	b	second point
 * \param	c	third point
 */
PNTriangle::PNTriangle(const PNPoint & a, const PNPoint & b, const PNPoint & c)
{
	setPoints(a, b, c);
	return;
}

/**
 * \brief Constructs a triangle with the specified coordinates.
 * Note: it is an error to try building a flat triangle. In DEBUG version
 * an assertion will be broken. In RELEASE version, this may lead to an undefined behavior.
 * The triangle is oriented in counter-clockwise mode.
 * 
 * \param	array	an array of 3 consecutives PNVector3f object

 */
PNTriangle::PNTriangle(const PNPoint * array)
{
	setPoints(array[0], array[1], array[2]);	
	return;
}

PNTriangle::~PNTriangle()
{
	return;
}

 ///////////////////////////////////////////////////

/**
 * \brief retrieves the point of the current triangle matching the specified identifiant.
 * Note: it is an error to call this method with an identifiant out of the range [0-2].
 * in DEBUG version, an assertion will be broken. In RELEASE version this may lead to
 * an undefined behavior.
 * 
 * \param	id		identifiant of the point to retrieve must fall in the range [0-2]
 * \param	pt		location where to store the point to retrieve
 * 
 * \return	the point to retrieve
 */
PNVector3f &
PNTriangle::getPoint(int id, PNVector3f & pt) const 
{
	assert(id >= 0 && id < 3 && "id out of range [0-2]");
	pt = _pt[id];	
	return (pt);
}

/**
 * \brief retrieves the point of the current triangle matching the specified identifiant.
 * Note: it is an error to call this method with an identifiant out of the range [0-2].
 * in DEBUG version, an assertion will be broken. In RELEASE version this may lead to
 * an undefined behavior.
 * 
 * \param	id		identifiant of the point to retrieve must fall in the range [0-2]
 * \param	pt		location where to store the point to retrieve
 * 
 * \return	the point to retrieve
 */
PNPoint &
PNTriangle::getPoint(int id, PNPoint & pt) const
{
	PNVector3f	v;
	
	v = getPoint(id, v);
	pt.x = v.x;
	pt.y = v.y;
	pt.z = v.z;
	
	return (pt);	
}

/**
 * \brief compute the area of the current triangle.
 * \return	the area of the current triangle
 */
pnfloat
PNTriangle::getArea() const
{
  pnfloat	s;
  pnfloat	norm_ab;
  pnfloat	norm_bc;
  pnfloat	norm_ca;

  norm_ab = _pt[0].getDistance(_pt[1]);
  norm_bc = _pt[1].getDistance(_pt[2]);
  norm_ca = _pt[2].getDistance(_pt[0]);

  s = (norm_ab + norm_bc + norm_ca) / 2;

  return (sqrt(s * (s - norm_ab) * (s - norm_bc) * (s - norm_ca)));
}

/**
 * \brief retrieves the specified extruded plane.
 * Note: the orientation of the extruded plane is always facing in the opposite direction of the triangle.
 * 
 * \param	id		identifiant of the plane to retrieve, must fall in the range [0-2]
 * \param	plane	location where to store the plane to retrieve
 * 
 * \return	the plane to retrieve
 */
PNPlane &
PNTriangle::getExtrusionPlane(pnint id, PNPlane & plane) const
{
	PNVector3f	side;
	PNVector3f	pt;
	PNNormal3f	normal;
	PNNormal3f	currentOrientation;
	
	assert(id >= 0 && id < 3 && "id out of range [0-2]");
	
	switch (id)
	{
	case 0:
 	  	side.setFromSegment(_pt[0], _pt[1]);
	  	pt = _pt[0];	  	
	  	break;
		
	case 1:
		side.setFromSegment(_pt[1], _pt[2]);
		pt = _pt[1];
		break;
		
	case 2:
		side.setFromSegment(_pt[2], _pt[0]);
		pt = _pt[2];
		break;
		
	default:
		assert(0 && "should not reach this code");
		break;
	}
	
	normal.crossProduct(side, (PNVector3f &) getOrientation(currentOrientation));
	plane.setPlane(pt, normal);
	
	return (plane);
}

/**
 * \brief returns the closest coordinates on the side [origin-destination] from the specified point.
 * 
 * \param	origin		origin of the side
 * \param	destination	destination of the side
 * \param	point		point from where we want the closest point to the side
 * \param	result		location where to store the resulting coordinates
 * 
 * \return	the resulting coordinates
 */
PNPoint &
PNTriangle::getClosestPointOnSide(const PNPoint & origin, const PNPoint & destination, const PNPoint & point, PNPoint & result) const
{
	PNVector3f	dir(origin, destination);
	PNVector3f	v(origin, point);
	pnfloat		proj;
	
	dir.setNorm(1.0f);		
	proj = dir.scalarProduct(v);
	
	if (proj <= 0)
		result = origin;
	else if (proj >= origin.getDistance(destination))
		result = destination;
	else
	{
		result = origin;
		result.x += dir.x * proj;
		result.y += dir.y * proj;
		result.z += dir.z * proj;		
	}
	
	return (result);
}

/**
 * \brief returns the coordinates of the point belonging either to a side of the triangle or inside of it and
 * closest to the specified point.
 * 
 * \param	from	the point for which we want the closest point of the triangle
 * \param	result	location where to store the resulting point
 * 
 * \return	the resulting closest coordinates
 */
PNPoint &
PNTriangle::getClosestPoint(const PNPoint & from, PNPoint & result) const
{
	PNPoint	closest;
	PNPoint	projection;
	
	projection = projectionOnPlane(from, projection);	
	if (isInsideBoundTriangle(projection))
	{
		result = projection;
		return (result);
	}
	
	getClosestPointOnSide(_pt[0], _pt[1], projection, result);
	getClosestPointOnSide(_pt[1], _pt[2], projection, closest);
	if (result.getDistance(projection) > closest.getDistance(projection))
		result = closest;
	getClosestPointOnSide(_pt[2], _pt[0], projection, closest);
	if (result.getDistance(projection) > closest.getDistance(projection))
		result = closest;
	
	return (result);
}

/**
 * \brief sets new points for the current instance of triangle.
 * Note: The triangle is counter-clockwise oriented.
 * 
 * \param	a	first point
 * \param	b	second point
 * \param	c	third point
 * 
 * \return	void
 */
void
PNTriangle::setPoints(const PNPoint & a, const PNPoint & b, const PNPoint & c)
{
	PNVector3f	ab(a, b);
	PNVector3f	ac(a, c);
	PNNormal3f	n;
		
	n.crossProduct(ab, ac);		
	setPlane(a, n);
	
	_pt[0] = a;
	_pt[1] = b;
	_pt[2] = c;
	
	return;
}

/**
 * \brief Returns true if the specifed points are defining a flat triangle. Returns false otherwise.
 */
bool
PNTriangle::isFlat(PNPoint & a, PNPoint & b, PNPoint & c)
{
	PNVector3f	ab(a, b);
	PNVector3f	ac(a, c);
	PNVector3f	bc(b, c);
	PNVector3f	n;

  	if (ab.getNorm() < PN_EPSILON ||
        ac.getNorm() < PN_EPSILON ||
        bc.getNorm() < PN_EPSILON)
    	return (true);

	ab.setNorm(1.0f);
	ac.setNorm(1.0f);
	bc.setNorm(1.0f);

	if (ABS(ab.scalarProduct(ac)) > 1 - PN_EPSILON)
		return (true);
	
	
	if (ABS(bc.scalarProduct(ac)) > 1 - PN_EPSILON)
    	return (true);

	n.setCrd(ab.y * ac.z - ab.z * ac.y,
			 ab.z * ac.x - ab.x * ac.z,
			 ab.x * ac.y - ab.y * ac.x);
 
  	if (n.getNorm() < PN_EPSILON)
    	return (true);  

  return (false);
}

/**
 * \brief Returns true if the specified point is inside the bounds of the current triangle
 * i.e : if the point is infront of the 3 planes extruded from the 3 sides of this triangle.
 * The specified point doesn't require to be directly placed on the plane of this triangle.
 * 
 * \param	point	the point to check wether it is inside the bounds of the current triangle
 * \return	true	if the point is inside and false otherwise.
 */
bool
PNTriangle::isInsideBoundTriangle(const PNPoint & point) const
{
	PNPlane	plane;
	
	if (getExtrusionPlane(0, plane).classifyVertex(point) == InFrontOfPlane ||
	 	getExtrusionPlane(1, plane).classifyVertex(point) == InFrontOfPlane ||
	 	getExtrusionPlane(2, plane).classifyVertex(point) == InFrontOfPlane)
	 	return (false);
	
	return (true);
}


/**
 * \brief Returns true if the specified point is inside the bounds of the current triangle
 * and if it is on its plane. Returns false otherwise.
 * 
 * \param	point	the point to check wether it is inside the current triangle or not
 * \return	true if it is inside, false otherwise.
 */
bool
PNTriangle::isInsideTriangle(const PNPoint & point) const
{
	PNPlane	plane;
	
	if (classifyVertex(point) != OnPlane ||
		getExtrusionPlane(0, plane).classifyVertex(point) == InFrontOfPlane ||
	 	getExtrusionPlane(1, plane).classifyVertex(point) == InFrontOfPlane ||
	 	getExtrusionPlane(2, plane).classifyVertex(point) == InFrontOfPlane)
	 	return (false);
	
	return (true);
}
	
/**
 * \brief compares the specifed triangle with the current one and returns true in case of matching
 * false otherwise.
 * 
 * \param 	triangle		the triangle to be tested with the current instance
 * \param	exactOrdering	if false, vertex ordering is not take into account for the comparison test. (ie: a-b-c = b-c-a)
 * 
 * \return	true	if the specified triangle matches with the current one, false otherwise
 */
bool
PNTriangle::isEquals(const PNTriangle & triangle, bool exactOrdering) const
{
	PNPoint	v;
	int		i;
	
	for (i = 0; i < 3; i++)
	{
		if (_pt[0].getDistance(triangle.getPoint(i % 3, v)) == 0 &&
			_pt[1].getDistance(triangle.getPoint((i+1)%3, v)) == 0 &&
			_pt[2].getDistance(triangle.getPoint((i+2)%3, v)) == 0)
			return (true);
		
		if (exactOrdering == true)
			break;
	}
		
	return (false);			
}

/**
 * \brief compares the given array of triangles and returns true in case of matching, false otherwise.
 * 
 * \param	arrayOne		first array of triangles
 * \param	arrayTwo		second array of triangles
 * \param	sizeOne			number of triangle in the first array
 * \param	sizeTwo			number of triangle in the second array
 * \param	exactOrdering	see isEquals() method
 * 
 * \return	true if the given arrays are of the same size and the inner triangle matche
 */
bool
PNTriangle::areEqual(PNTriangle * arrayOne, PNTriangle * arrayTwo, int sizeOne, int sizeTwo, bool exactOrdering)
{
	int		i;
		
	if (sizeOne != sizeTwo)
		return (false);
		
	if (sizeOne == 0)
		return (true);
		
	if (arrayOne == NULL || arrayTwo == NULL)
		return (false);		
		
	for (i = 0; i < sizeOne; i++)
		if (arrayOne[i].isEquals(arrayTwo[i], exactOrdering) == false)
			return (false);

	return (true);
}

		
bool
PNTriangle::clipWith(PNPlane & plane, std::vector<PNTriangle> & triangles)
{
	PtClipper			ptIntersection[2];
	pnint				idOfIntersection[2];
	pnint				nbIntersection;
	vector<PtClipper> 	points;
	pnint				idCurrent;
	pnint				idNext;
	
	triangles.clear();
		
	if (plane.classifyTriangle(_pt[0], _pt[1], _pt[2]) != ClippedByPlane)
		return (false);
	
	idOfIntersection[0] = idOfIntersection[1] = -1;
	nbIntersection = 0;

	idCurrent = 0;
	idNext = 1;
		
	while (idCurrent != 3)
	{		
  	  points.push_back(_pt[idCurrent]);  	  	
  	  if (plane.classifyVertex(_pt[idCurrent]) * plane.classifyVertex(_pt[idNext]) < 0)
		{
			plane.isSegmentIntersectPlane(_pt[idCurrent], _pt[idNext], ptIntersection[nbIntersection]);			
			ptIntersection[nbIntersection].setSide(_pt[idCurrent], _pt[idNext]);
	    	idOfIntersection[nbIntersection] = (pnint)points.size();
	    	points.push_back(ptIntersection[nbIntersection]);
	    	nbIntersection++;
		}
					
		idCurrent++;
		idNext = (idCurrent + 1) % 3;
	}
		
	if (nbIntersection == 2)
	{
		assert(points.size() == 5);
		if (idOfIntersection[0] == 2)
		{
			buildTriangle(points, 0, 1, 2, triangles);
			buildTriangle(points, 2, 4, 0, triangles);
			buildTriangle(points, 2, 3, 4, triangles);
		}
		else if (idOfIntersection[0] == 1 && idOfIntersection[1] == 4)
		{
			buildTriangle(points, 0, 1, 4, triangles);
			buildTriangle(points, 1, 2, 3, triangles);
			buildTriangle(points, 1, 3, 4, triangles);
		}
		else
		{
			buildTriangle(points, 0, 1, 4, triangles);
			buildTriangle(points, 1, 3, 4, triangles);
			buildTriangle(points, 1, 2, 3, triangles);
		}
	}
	else if (nbIntersection == 1)
	{
		assert(idOfIntersection[0] >= 1 && idOfIntersection[0] <= 3);
		switch (idOfIntersection[0])
		{
			case 1:
			buildTriangle(points, 3, 0, 1, triangles);
			buildTriangle(points, 1, 2, 3, triangles);
		    break;
			
			case 2:
			buildTriangle(points, 0, 1, 2, triangles);
			buildTriangle(points, 2, 3, 0, triangles);
		    break;
		    
		    case 3:
		    buildTriangle(points, 1, 2, 3, triangles);
		    buildTriangle(points, 3, 0, 1, triangles);
		    break;		    
		}
	}
			
	return (true);
}

bool
PNTriangle::substract(PNTriangle & triangle, std::vector<PNTriangle> & triangles)
{
	return (false);
}
 
///////////////////////////////////////////////////
 
}	/* end of namespace */
