/*
 * PNWorldCollision.hpp
 * 
 * Description :
 * PNWorldCollision declaration
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

#ifndef _PNWORLDCOLLISON_H_
# define _PNWORLDCOLLISON_H_

/////////////////////////////////////////////

#include <assert.h>

/////////////////////////////////////////////

#include "pndefs.h"
#include "pnmath.h"
#include "PNVector3f.hpp"
#include "PNBoundingSphere.hpp"

/////////////////////////////////////////////

namespace PN {

/////////////////////////////////////////////

#define PN_ACCURACY_DEFAULT			5.0f

/////////////////////////////////////////////

class PNAPI	PNWorldCollision
{
public:
	PNWorldCollision();
	virtual ~PNWorldCollision();
	
public:
	void			loadWorld				(pnfloat * vertices, pnuint nbVertex, pnuint * triangles, pnuint nbTriangle);
	void			loadWorld				(PNTriangle * triangles, pnuint nbTriangle);
	void			sortByNormals			(PNNormal3f & direction, bool testSens);
	
public:	
	void			setAccuracy				(pnfloat biggestStep);
	pnfloat			getAccuracy				(void);
	
public:
	int				getNbTriangle			(void)				{ return (_nbTriangle); }
	PNTriangle *	getTriangleAt			(pnuint index)		{ assert(index < (pnuint)_nbTriangle); return (&_triangles[index]); }
	PNTriangle *	getTriangles			(void)				{ return (_triangles); }
	
public:
	bool			checkCollision			(const PNBoundingSphere & sphere) const;
	bool			translateSphere			(const PNBoundingSphere & sphere, const PNVector3f & translation, PNVector3f & resultingPos) const;
	
private:
	void			_fillCollidersList		(const PNBoundingSphere & sphere, const PNPoint3f& startPosition, std::list<int> & colliders) const;	
	int				_getBestColliderOfList	(const PNBoundingSphere & sphere, const PNNormal3f & force, std::list<int> & colliders) const;	
	bool			_computeStepCollision	(const PNBoundingSphere & sphere, const PNNormal3f & force, const PNPoint3f& posAtPreviousStep, PNVector3f & correction) const;
 	
private:
	PNTriangle *	_triangles;	
	int				_nbTriangle;
	pnfloat			_accuracy;
};

/////////////////////////////////////////////

}	/* end of namespace */

/////////////////////////////////////////////

#endif //_PNWORLDCOLLISON_H_

/////////////////////////////////////////////

