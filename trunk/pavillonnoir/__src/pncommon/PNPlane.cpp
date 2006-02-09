/*
 * PNPlane.cpp
 * 
 * Description :
 * 3D-Plane definition
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
using namespace std;

////////////////////////////////////////

#include "pndefs.h"
#include "pnmath.h"
#include "PNVector3f.hpp"
#include "PNNormal3f.hpp"
#include "PNPlane.hpp"

////////////////////////////////////////

namespace PN {

////////////////////////////////////////

/**
 * \brief Initializes a plane with default value. The created plane
 * is equals to the XZ plane and passes through the origin.
 */
PNPlane::PNPlane()
{
  this->setEquation(0, 1, 0, 0);
  return;
}

/**
 * \brief Initializes the plane according the specified equation.
 * This has the same effect than to call the setEquation() method.
 */
PNPlane::PNPlane(pnfloat x, pnfloat y, pnfloat z, pnfloat d)
{
  this->setEquation(x, y, z, d);
  return;
}

/**
 * \brief Initialized the current instance with the specified position and orientation.
 * For further details please read the documentation corresponding to the setPlane() method.
 */
PNPlane::PNPlane(const PNPoint3f& position, const PNNormal3f & normal)
{
  this->setPlane(position, normal);
  return;
}

/**
 * \brief Copy constructor. Initializes the current instance with the
 * same data provided in the specified plane.
 */
PNPlane::PNPlane(const PNPlane & source)
{
  *this = source;
  return;
}

/**
 * \brief Plane destructor.
 */
PNPlane::~PNPlane()
{
  return;
}

////////////////////////////////////////

/**
 * \brief Set a new equation for the current plane.
 * Note: it is an error to call setEquation with a null orientation (ie: x=0 y=0 and z=0).
 * In DEBUG mode, an assertion will be broken. In RELEASE mode, this may lead to and undefined
 * behavior. (division by zero).
 *
 * \param x	x value corresponding to the x parameter of the normal of the plane
 * \param y	y value corresponding to the y parameter of the normal of the plane
 * \param z	z value corresponding to the z parameter of the normal of the plane
 * \param d	d value corresponding to the distance of the plane from the origin.
 *
 * \return	void
 */
void
PNPlane::setEquation(pnfloat x, pnfloat y, pnfloat z, pnfloat d)
{
  PNNormal3f	normal(x, y, z);

  _x = normal.getX();
  _y = normal.getY();
  _z = normal.getZ();
  _d = d / sqrtf(x * x + y * y + z * z);

  return;
}

/**
 * \brief Sets a new position for the current plane.
 *
 * \param	position	the new position
 * \return	void
 */
void
PNPlane::setPosition(const PNPoint3f& position)
{
	PNVector3f	pos(position);		
  	_d = pos.scalarProduct(_x, _y, _z);
  	return;
}

/**
 * \brief Sets a new orientation for the current plane.
 *
 * \param	orientation	the new orientation.
 * \return	void
 */
void
PNPlane::setOrientation(const PNNormal3f & orientation)
{
  _x = orientation.getX();
  _y = orientation.getY();
  _z = orientation.getZ();  

  return;
}

/**
 * \brief Initializes the plane with the specified position and orientation.
 * Note: It is an error to call this method with a null orientation (ie: x=0 y=0 z=0).
 * In DEBUG mode an assertion will be broken. In RELEASE mode this may lead to an
 * undefined behavior. (probably division by zero).
 *
 * \param	position	the position of the plane from the origin.
 * \param	orientation	the orientation of the plane.
 *
 * \return	void
 */
void
PNPlane::setPlane(const PNPoint3f& position, const PNNormal3f & orientation)
{
  this->setOrientation(orientation);
  this->setPosition(position);

  return;
}

////////////////////////////////////////

/**
 * \brief fill the specified point with the current position of the plane.
 * Note: the filled position may not exactly corresponds to the one specified
 * during creation/initialization process, because it results from the computation
 * of the intersection of the plane with a ray launched from the origin.
 *
 * \param	position	the location where to store the position of the current plane.
 * \return	position
 */
PNPoint3f&
PNPlane::getPosition(PNPoint3f& position) const
{
  PNVector3f	result;
  
  getPosition(result);  
  position.x = result.x;
  position.y = result.y;
  position.z = result.z;

  return (position);
}

/**
 * \brief fill the specified vector with the current position of the plane.
 * Note: the filled position may not exactly corresponds to the one specified
 * during creation/initialization process, because it results from the computation
 * of the intersection of the plane with a ray launched from the origin.
 *
 * \param	position	the location where to store the position of the current plane.
 * \return	position
 */
PNVector3f &
PNPlane::getPosition(PNVector3f & position) const
{
  position.setCrd(_x, _y, _z);
  position.multiply(_d);
  
  return (position);	
}

/**
 * \brief fill the specified normal with the current normalized orientation of the plane.
 *
 * \param	normal	location where to store the normalized orientation of the plane.
 * \return	void.
 */
PNNormal3f &
PNPlane::getOrientation(PNNormal3f & orientation) const
{
  orientation.setCrd(_x, _y, _z);
  return (orientation);
}

/**
 * \brief Returns the x normalized value of the orientation of the current plane.
 */
pnfloat
PNPlane::getOrientationX() const
{
  return (_x);
}

/**
 * \brief Returns the y normalized value of the orientation of the current plane.
 */
pnfloat
PNPlane::getOrientationY() const
{
  return (_y);
}

/**
 * \brief Returns the z normalized value of the orientation of the current plane.
 */
pnfloat
PNPlane::getOrientationZ() const
{
  return (_z);
}

/**
 * \brief Returns the distance of the plane from the origin.
 */
pnfloat
PNPlane::getDistanceFromOrigin() const
{
  return (_d);
}

////////////////////////////////////////

/**
 * \brief projects the specified point on the current plane and store the resulting
 * point into the parameter 'result'.
 * 
 * \param 	point	the point to project on the plane
 * \param	result	location where to store the resulting projection
 * 
 * \return	the resulting projection
 */
PNPoint3f&
PNPlane::projectionOnPlane(const PNPoint3f& point, PNPoint3f& result) const
{
	pnfloat		dist;	
	PNVector3f	orientation;
	
	dist = getDistanceFromPlane(point);
	orientation.setCrd(getOrientationX(), getOrientationY(), getOrientationZ());
	orientation.multiply(-dist);
	
	result.x = point.x + orientation.x;
	result.y = point.y + orientation.y;
	result.z = point.z + orientation.z;
		
	return (result);
}

////////////////////////////////////////

/**
 * \brief Computes the potential intersection between the specified segment and the current plane.
 *
 * \param	segOrigin	origin of the segment
 * \param	segDestination	destination of the segment
 * \param	intersection	location where to store the intersection coordinates.
 *
 * \return	true if an intersection has been found, in this case intersection parameter is filled
 *              with the computed coordinates. Returns false otherwise.
 */
bool
PNPlane::isSegmentIntersectPlane(const PNPoint3f& segOrigin, const PNPoint3f& segDestination, PNPoint3f& intersection)
{
  planeSide_t	side[2];

  if ((side[0] = classifyVertex(segOrigin)) * (side[1] = classifyVertex(segDestination)) <= 0)
    {
      	PNVector3f	currentPosition;
      	PNVector3f	inter;
      	PNVector3f	segmentOriginToPlane(segOrigin, this->getPosition(currentPosition));
      	PNVector3f	segment(segOrigin, segDestination);
      	pnfloat		ps_segmentOriginToPlane_normalPlane;
      	pnfloat		ps_segment_normalPlane;
      	pnfloat		k;

  		if (side[0] == OnPlane)
		{
	  		intersection = segOrigin;
	  		return (true);
		}
	
		  if (side[1] == OnPlane)
		  	{
			  intersection = segDestination;
			  return (true);
			}

		  ps_segment_normalPlane = segment.scalarProduct(_x, _y, _z);

		  if (ABS(ps_segment_normalPlane) < PN_EPSILON)
			return (false);    

		  ps_segmentOriginToPlane_normalPlane = segmentOriginToPlane.scalarProduct(_x, _y, _z);
		     
		  k = ps_segmentOriginToPlane_normalPlane / ps_segment_normalPlane;
      
		  if (k < 0 || k > 1)
			return (false);
      
		  segment.multiply(k);
		  inter.add(segOrigin, segment);
		  
		  intersection.x = inter.x;
		  intersection.y = inter.y;
		  intersection.z = inter.z;

		  return (true);
		 }

  return (false);
}

/**
 * \brief Computes the potential intersection of the specified ray with the current plane.
 *
 * \param	rayOrigin		origin of the ray.
 * \param	rayDirection	direction of the ray.
 * \param	intersection	location where to store the intersection coordinates.
 *
 * \return	true if the ray intersects the plane, in this case, the 'intersection' parameter is filled
 *              with the computed coordinates. Otherwise the method returns false and intersection is left untouched.
 */
bool
PNPlane::isRayIntersectPlane(const PNPoint3f& rayOrigin,const PNNormal3f & rayDirection, PNPoint3f& intersection)
{
  PNVector3f	plane_vertex;
  PNVector3f	rayOriginToPlane;
  PNVector3f	direction;
  PNVector3f	intersectionResult;
  pnfloat		ps_rayOriginToPlane_normalPlane;
  pnfloat		ps_rayDirection_normalPlane;
  pnfloat		k;

  this->getPosition(plane_vertex);
  rayOriginToPlane.setFromSegment(rayOrigin, plane_vertex);

  ps_rayDirection_normalPlane = rayDirection.scalarProduct(_x, _y, _z);

  if (ABS(ps_rayDirection_normalPlane) < PN_EPSILON)
    return (false);    

  ps_rayOriginToPlane_normalPlane = rayOriginToPlane.scalarProduct(_x, _y, _z);
  k = ps_rayOriginToPlane_normalPlane / ps_rayDirection_normalPlane;

  if (k < 0)
    return (false);

  direction.setCrd(rayDirection.getX(), rayDirection.getY(), rayDirection.getZ());
  direction.multiply(k);
  intersectionResult.add(rayOrigin, direction);
  
  intersection.x = intersectionResult.x;
  intersection.y = intersectionResult.y;
  intersection.z = intersectionResult.z;
  
  return (true);
}

////////////////////////////////////////

/**
 * \brief Return true if the current plane and the one specified are almost equals (an error of EPSILON is tolerated).
 * Return false otherwise.
 *
 * \param	plane	the plane with which we want to test the colinearity.
 * \return	true if those planes are almost equals (epsilon error) false otherwise.
 */
bool
PNPlane::isEquals(const PNPlane & plane)
{
  PNNormal3f	currentOrientation;
  PNNormal3f	planeOrientation;

  this->getOrientation(currentOrientation);
  plane.getOrientation(planeOrientation);
  
  if (!currentOrientation.isColinear(planeOrientation))
    return (false);

  if (ABS(plane.getDistanceFromOrigin() - _d) > PN_EPSILON)
    return (false);

  return (true);
}

/**
 * \brief Return the relative location of the specified point from the current plane.
 *
 * \param	position	a 3D position
 * \return	One of the following value: BehindPlane, OnPlane, InFrontOfPlane.
 */
planeSide_t
PNPlane::classifyVertex(const PNPoint3f& position) const
{
  pnfloat	distance;

  distance = this->getDistanceFromPlane(position);

  if (distance < - PN_EPSILON)
    return (BehindPlane);

  if (ABS(distance) < PN_EPSILON)
    return (OnPlane);

  return (InFrontOfPlane);
}

/**
 * \brief Return the relative location of the specified triangle from the current plane.
 * 
 * \param	a	first point defining the triangle
 * \param	b	second point defining the triangle
 * \param	c	third point defining the triangle
 * 
 * \return	One of the following value: BehindPlane, ClippedByPlane, InFrontOfPlane, OnPlane
 */
planeSide_t
PNPlane::classifyTriangle(const PNPoint3f& a, const PNPoint3f& b, const PNPoint3f& c)
{
	planeSide_t	sides[3];
	
	sides[0] = classifyVertex(a);
	sides[1] = classifyVertex(b);
	sides[2] = classifyVertex(c);
	
	if (sides[0] * sides[1] < 0 || sides[0] * sides[2] < 0 || sides[1] * sides[2] < 0)
		return (ClippedByPlane);
		
	if (sides[0] == InFrontOfPlane || sides[1] == InFrontOfPlane || sides[2] == InFrontOfPlane)
		return (InFrontOfPlane);
		
	if (sides[0] == BehindPlane || sides[1] == BehindPlane || sides[2] == BehindPlane)
		return (BehindPlane);
		
	return (OnPlane);
}

/**
 * \brief return the smallest distance from the specified position to the plane.
 *
 * \param	position	a 3D position
 * \return	A positive value if the point is in front of the plane, a null value
 *		if the point is on the plane and a negative value if the point is behind the plane.
 */
pnfloat
PNPlane::getDistanceFromPlane(const PNPoint3f& position) const
{  
  return (position.x * _x + position.y * _y + position.z * _z - _d);
}

////////////////////////////////////////

} /* end of namespace */

////////////////////////////////////////

