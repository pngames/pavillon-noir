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

PNPathFinding::PNPathFinding()
{
}

PNPathFinding::PNPathFinding(PNPoint *pos)
{
  _pos = pos;
}

PNPathFinding::~PNPathFinding()
{
}

void
PNPathFinding::moveTo(PNPoint &p)
{

  _dest.set(p);
  _goal = closestWP(p);
  _firstcall = true;
}

void
PNPathFinding::moveTo(PNWayPoint *wp)
{
  PNPoint				p = wp->getCoord();

  _goal = wp;
  _dest.set(p.x, p.y, p.z);
  _firstcall = true;
}

/*
** TODO: -Test collisions between waypoint and destination point
**			 -Select Waypoint considering direction towards goal
*/

PNWayPoint*
PNPathFinding::closestWP(PNPoint &p)
{
  bool							  begin = true;
  pnfloat							  distance;
  PNWayPoint						  *wp;
  std::list<PNWayPoint*>			  ls;
  std::list<PNWayPoint*>::iterator  i;

  for (ls = getWayPoints(), i = ls.begin(); i != ls.end(); i++)
  {
	PNPoint						  coord = (*i)->getCoord();

	if (begin == true || coord.getDistance(p) < distance)
	{
	  wp = *i;
	  distance = coord.getDistance(p);
	}
	begin = false;
  }
  return (wp);
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
	_next = closestWP(*_pos);
	_firstcall = false;
	o.setCoord(_next->getCoord());
	return;
  }

  //handle end of travel
  if (_next == _goal || *_pos == _dest)
  {
	o.setCoord(_dest);
	if (*_pos == _dest)
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
		  _dest.getDistance((PNPoint &)wp->getCoord());
		begin = false;
	  }	
	  else
	  {
		temp = (*i)->weight * (*i)->coef +
		  _dest.getDistance((PNPoint &)(*i)->next->getCoord());
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