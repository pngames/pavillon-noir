/*
 * PNPathFinding.cpp
 * 
 * Description :
 * PNPathFinding definition
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
#include "pndefs.h"
#include "pnmath.h"
#include "PNWayPoint.hpp"
#include "PNPathFinding.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

/*  PNPathFinding::PNPathFinding()
{
  _pos = PNPoint3f(0,0,0);
}*/

  PNPathFinding::PNPathFinding(const PNPoint3f&pos) : _pos(pos)
{
//  _pos = pos;
}

PNPathFinding::~PNPathFinding()
{
}

void
PNPathFinding::moveTo(const PNPoint3f&p)
{
  _dest.set(p);
  _goal = closestWP(p);
  _firstcall = true;
  _travellist.clear();
  _travelmap.clear();
}

void
PNPathFinding::moveTo(PNWayPoint *wp)
{
  PNPoint3f				p = wp->getCoord();

  _goal = wp;
  _dest.set(p.x, p.y, p.z);
  _firstcall = true;
  _travellist.clear();
  _travelmap.clear();
}

/*
** TODO: -Test collisions between waypoint and destination point
**			 -Select Waypoint considering direction towards goal
*/

PNWayPoint*
PNPathFinding::closestWP(const PNPoint3f&p)
{
  bool								begin = true;
  pnfloat							distance = 0.0f;
  PNWayPoint						*wp = NULL;
  std::list<PNWayPoint*>			ls;
  std::list<PNWayPoint*>::iterator	i;

  for (ls = getWayPoints(), i = ls.begin(); i != ls.end(); i++)
  {
	PNPoint3f						  coord = (*i)->getCoord();
	pnfloat						  dist = coord.getDistance(p);
	pnfloat						  fdist = _pos.getFlatDistance(coord);

//	if (fdist > 50.0f)
//	{
	  if (begin == true || dist < distance)
	  {
		wp = *i;
		distance = coord.getDistance(p);
	  }
	  begin = false;
//	}
  }
  return (wp);
}

PNPoint3f
PNPathFinding::closestWPCoord(const PNPoint3f&p)
{
  return this->closestWP(p)->getCoord();
}

void
PNPathFinding::moveNext(PN3DObject& o)
{
  bool								begin = true;
  pnfloat 							fulldistance;
  pnfloat							temp;
  PNWayPoint						*wp = NULL;
  std::list<wayLink_t*>				ls;
  std::list<wayLink_t*>::iterator	i;

  //manage first call to moveNext
  if (_travellist.empty() && _firstcall)
  {
	_next = closestWP(_pos);
	_firstcall = false;
	o.setCoord(_next->getCoord());
	_travellist.clear();
	_travelmap.clear();
	return;
  }

  //handle end of travel
  if (_next == _goal || _pos == _dest)
  {
	//pnerror(PN_LOGLVL_DEBUG, "end of travel");
	o.setCoord(_dest);
	if (_pos.getFlatDistance(_dest) < 30.0f)
	{
	  _firstcall = true;
	  _travellist.clear();
	  _travelmap.clear();
	}
	return;
  }

  //select best unused link amongst all available
  for (ls = _next->getLinks(), i = ls.begin(); i != ls.end(); i++)
  {
	//if goal available, get yer ass down there !
	if ((*i)->next == _goal)
	{
	  wp = _goal;
	  break;
	}

	//if the link has not been visited yet, get the closest WP
	if (_travelmap.find((*i)->next) == _travelmap.end())
	{
	  if (begin == true)
	  {
		wp = (*i)->next;
		fulldistance = (*i)->weight * (*i)->coef +
		  _dest.getDistance((PNPoint3f&)wp->getCoord());
		begin = false;
	  }	
	  else
	  {
		temp = (*i)->weight * (*i)->coef +
		  _dest.getDistance((PNPoint3f&)(*i)->next->getCoord());
		if (fulldistance > temp)
		{
		  fulldistance = temp;
		  wp = (*i)->next;
		}
	  }
	}
  }

  //if no link was found, go backward
  if (wp == NULL)
  {
	wp = _travellist.front();
	_travellist.pop_front();
  }
  else
	_travellist.push_front(_next);

  _travelmap[_next] = _next;
  _next = wp;
  o.setCoord(_next->getCoord());
}

void
PNPathFinding::getNext(PN3DObject &o)
{
  o.setCoord(_next->getCoord());
}

//////////////////////////////////////////////////////////////////////////
};

