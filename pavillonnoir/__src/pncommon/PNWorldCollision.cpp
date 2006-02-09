/*
 * PNWorldCollision.cpp
 * 
 * Description :
 * PNWorldCollision definition
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
#include <list>
using namespace std;

/////////////////////////////////////////////

#include "PNWorldCollision.hpp"

/////////////////////////////////////////////

namespace PN {

/////////////////////////////////////////////

PNWorldCollision::PNWorldCollision()
{
	_nbTriangle = 0;
	_triangles = NULL;
	_accuracy = PN_ACCURACY_DEFAULT;
	
	return;
}

PNWorldCollision::~PNWorldCollision()
{
	if (_nbTriangle > 0)
		delete[] _triangles;
		
	return;
}

void
PNWorldCollision::setAccuracy(pnfloat biggestStep)
{
	assert(biggestStep > PN_EPSILON && "biggestStep parameter is out of range!");
	_accuracy = biggestStep;
	
	return;
}

pnfloat
PNWorldCollision::getAccuracy(void)
{
	return (_accuracy);
}


/**
 * \brief create the physic-static-world from mesh data
 * 
 * \param	vertices	list of vertex in the form (x, y, z)(x, y, z)...(x, y, z)
 * \param	nbVertex	number of vertex in this list
 * \param	triangles	list of triangles in the form (i0, i1, i2)(i0, i1, i2)...
 * \param	nbTriangle	number of triangle in this list
 * 
 * \return	void
 */	
void
PNWorldCollision::loadWorld(pnfloat * vertices, pnuint nbVertex, pnuint * triangles, pnuint nbTriangle)
{
	unsigned int		i;
	
	_nbTriangle = nbTriangle;
	_triangles = new PNTriangle[nbTriangle];
	
	for (i = 0; i < nbTriangle; i++)
	{
		PNPoint3f	vertex[3];
			
		vertex[0].set(vertices[triangles[i * 3] * 3], vertices[triangles[i * 3] * 3 + 1], vertices[triangles[i * 3] * 3 + 2]);
		vertex[1].set(vertices[triangles[i * 3 + 1] * 3], vertices[triangles[i * 3 + 1] * 3 + 1], vertices[triangles[i * 3 + 1] * 3 + 2]);
		vertex[2].set(vertices[triangles[i * 3 + 2] * 3], vertices[triangles[i * 3 + 2] * 3 + 1], vertices[triangles[i * 3 + 2] * 3 + 2]);
				
		_triangles[i].setPoints(vertex[0], vertex[1], vertex[2]);		
	}
	
	return;
}

/**
 * \brief creates the physic-static-world from an array of PNTriangle
 * 
 * \param	triangles	array of initialized triangles
 * \param	nbTriangle	size of the array
 * 
 * \return	void
 */
void
PNWorldCollision::loadWorld(PNTriangle * triangles, pnuint nbTriangle)
{
	unsigned int		i;
	
	assert(triangles != NULL);
	assert(nbTriangle > 0 && "nbTriangle is invalid");
	
	_nbTriangle = nbTriangle;
	_triangles = new PNTriangle[_nbTriangle];
	for (i = 0; i < nbTriangle; i++)
		_triangles[i] = triangles[i];
	
	return;
}

/**
 * \brief Sorts the internal array of triangles according the specified direction. This may be useful
 * if some colliders oriented in a certain way should be tested before other possible colliders during
 * the collision detection step. Typically, for climbing a step, horizontal colliders should be tested
 * BEFORE vertical colliders since temporaries corrections adjustements may occur during the collision
 * correction phase...
 *  
 * \param	normal				direction for sorting the triangles according their normals in the internal array.
 * 								The internal array will be sort from best-match to worse-match.
 * \param	testSens			if true direction and sens are tested for sorting otherwise only direction is checked.
 * 
 * \return	void
 */
void
PNWorldCollision::sortByNormals (PNNormal3f & normal, bool testSens)
{
	vector<PNTriangle>	listTmp;
	vector<PNTriangle>	list_sorted;
	PNNormal3f			orientation;
	pnfloat				cs_current;
	pnfloat				cs_best;
	vector<PNTriangle>::iterator	it;
	vector<PNTriangle>::iterator	best_it;
	unsigned int		i;
	
	assert(_nbTriangle > 0 && _triangles != NULL && "a world must be loaded before calling this method !!");
	
	for (i = 0; i < (unsigned int) _nbTriangle; i++)
		listTmp.push_back(_triangles[i]);
		
	while (listTmp.size() > 0)
	{
	    best_it = listTmp.begin();
	    cs_best = best_it->getOrientation(orientation).scalarProduct(normal);
	    cs_best = ((testSens == false) ? ABS(cs_best) : cs_best);
    		    	
		for (it = listTmp.begin(); it != listTmp.end(); it++)
		{			
			cs_current = it->getOrientation(orientation).scalarProduct(normal);
			cs_current = ((testSens == false) ? ABS(cs_current) : cs_current);
			if (cs_current > cs_best)
			{
				best_it = it;
				cs_best = cs_current;
			}
		}
	
		list_sorted.push_back(*best_it);
		listTmp.erase(best_it);
	}
	
	assert(list_sorted.size() == (unsigned int) _nbTriangle && "le nombre de triangle ne devrait pas avoir change apres le tri");
	
	for (i = 0; i < (unsigned int) _nbTriangle; i++)
		_triangles[i] = list_sorted[i];
		
	return;
}


/**
 * \brief check wether the specified sphere collides with a list of triangles in the world,
 * returns true if a collision is detected and false otherwise.
 * 
 * \param	sphere	the bounding volume to test the collision with the world
 * \return	true if a collision is detected and false otherwise.
 */			
bool
PNWorldCollision::checkCollision(const PNBoundingSphere & sphere) const
{
	PNVector3f	correction;
	int			i;
	
	for (i = 0; i < _nbTriangle; i++)
		if (sphere.testCollisionWithTriangle(_triangles[i], correction))
			return (true);
	return (false);
}

/**
 * \brief	handle potential static collisions which may occurs during the the translation step of the specified boundingSphere.
 * It is the responsibility of the caller to give a sphere which is not already in collision with the static world. Otherwise
 * this may lead to an undefined behavior.
 * 
 * \param	sphere			the sphere to test during the displacement in the static world. The initial position of the sphere should
 *                  		not collide with static world.
 * \param	translation		the translation to apply to the sphere during the checking processus
 * \param	resultingPos	location where to store the resulting position of the sphere once the translation vector has been applied
 * 							and all collisions tests with static world are done.
 * 
 * \return	a boolean indicating wether a collision occured during the checking processus.
 */
bool
PNWorldCollision::translateSphere(const PNBoundingSphere & sphere, const PNVector3f & translation, PNVector3f & resultingPos) const
{
	PNVector3f			step;
	PNVector3f			trRemaining;
	PNBoundingSphere	sph(sphere);
	PNVector3f			correction;
	PNNormal3f			force;
	
	if (translation.getNorm() * 100 <= PN_EPSILON)
		{
			resultingPos = sphere.getPosition();
			return (true);
		}
		
	force.setCrd(translation.x * 1000, translation.y * 1000, translation.z * 1000);
	
	trRemaining = translation;
	step = translation;	
	if (step.getNorm() > _accuracy)
		step.setNorm(_accuracy);
	resultingPos = sph.getPosition(resultingPos);
	
	while (trRemaining.getNorm() > _accuracy)
	{
		trRemaining.x -= step.x;
		trRemaining.y -= step.y;
		trRemaining.z -= step.z;
		
		resultingPos.add(sph.getPosition(), step);
		sph.setPosition(resultingPos);
		
		if (_computeStepCollision(sph, force, sphere.getPosition(), correction))
		{
			resultingPos.add(resultingPos, correction);
			return (true);
		}		
	}

	resultingPos.add(sph.getPosition(), trRemaining);
	sph.setPosition(resultingPos);
		
	if (_computeStepCollision(sph, force, sphere.getPosition(), correction))
	{
		resultingPos.add(resultingPos, correction);
		return (true);
	}		
		
	return (false);
}

/////////////////////////////////////////////

/**
 * \brief Fills the list 'colliders' with all the triangles which are in collision with the current bounding sphere.
 * The method doesn't take into account the triangles of the world which were not visible for the sphere at its initial position
 * (to prevent undesirable correction) and all triangles which are not colliding with the current position of the specified sphere. 
 * 
 * \param	sphere				the current sphere to test the collision with the static world
 * \param	startPosition		the initial position of the sphere before any translation vector has been applied to it.
 * \param	colliders			location where to store the result
 * 
 * \return	void
 */
void
PNWorldCollision::_fillCollidersList(const PNBoundingSphere & sphere, const PNPoint3f& startPosition, std::list<int> & colliders) const
{
	int			i;
	PNVector3f	correction;
	
	colliders.clear();

	for (i = 0; i < _nbTriangle; i++)
	{
		if (_triangles[i].classifyVertex(startPosition) == BehindPlane ||
			!sphere.testCollisionWithTriangle(_triangles[i], correction))
			continue;
		colliders.push_back(i);
	}

	return;
}

/**
 * \brief returns the index of the triangle array of the best remaining triangle of the list. The best triangle is the one
 * whoose orientation is orthonormal with the specified force which is the unit-length vector of its translation. A side
 * effect of this method is to automatically delete the item of the list before returning. If this method is called with
 * an empty list it returns -1 to indicate the caller that no choice was possible.
 * 
 * \param	sphere		the current sphere to test the collision
 * \param	force		the unit-lenght vector of its translation
 * \param	colliders	a list of index of triangle which collides with the specified sphere
 * 
 * \return	an index of the triangle array of the world or -1 if empty
 */
int
PNWorldCollision::_getBestColliderOfList(const PNBoundingSphere & sphere, const PNNormal3f & force, std::list<int> & colliders) const
{
	std::list<int>::iterator	it;
	std::list<int>::iterator	itemToErase;
	pnfloat				ps_current;
	pnfloat				ps_best;
	int					best_collider;
	PNNormal3f			triangleOrientation;
	
	if (colliders.size() == 0)
		return (-1);
	
	best_collider = -1;
	ps_best = 2.0f;
		
	for (it = colliders.begin(); it != colliders.end(); it++)
	{
		_triangles[*it].getOrientation(triangleOrientation);		
		ps_current = ABS(force.scalarProduct(triangleOrientation));		
		
		if (ps_best > ps_current)
		{
			ps_best = ps_current;
			best_collider = *it;
			itemToErase = it;
		}		
	}
	
	colliders.erase(itemToErase);
	
	return (best_collider);	
}

/**
 * \brief Computes a potential correction to apply to the sphere at its current position in the static world. Returns true if at least one collision
 * has been detected, false otherwise.
 * 
 * \param	sphere			the sphere to test in the static world
 * \param	force			the unit-length vector of its translation
 * \param	startPosition	the initial position of the sphere before any translation vector has been applied to it
 * \param	correction		location where to store an eventual correction to apply to the current position of the sphere to prevent a collision.
 * 
 * \return	true if a collision has been detected. If this so, the caller may consult the value of the correction parameter. If no collision
 * has been detected the method returns false.
 */
bool
PNWorldCollision::_computeStepCollision(const PNBoundingSphere & sphere, const PNNormal3f & force, const PNPoint3f& startPosition, PNVector3f & correction) const
{
	PNVector3f			correctionLocal;
	PNBoundingSphere	sph(sphere);
	int					collider;
	std::list<int>			colliders;
	
	correction.set(0, 0, 0);
	
	_fillCollidersList(sph, startPosition, colliders);
	while (!colliders.empty())
	{
		collider = _getBestColliderOfList(sph, force, colliders);
		assert(collider != -1);
		if (sph.testCollisionWithTriangle(_triangles[collider], correctionLocal) == true)
		{
			correction.add(correction, correctionLocal);
			sph.translate(correctionLocal);
		}
	}

	return ((correction.getNorm() > PN_EPSILON)	? true : false);
}

/////////////////////////////////////////////
} /* end of namespace */

