/*
 * PNPathFinding.hpp
 * 
 * Description :
 * PNPathFinding declaration
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

#ifndef _PNPATHFINDING_HPP_
# define _PNPATHFINDING_HPP_

#include <map>
#include "PNIAGraph.hpp"
#define REACHED			true
#define UNREACHABLE		false

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNWayPoint;

class PNAPI PNPathFinding : public PNIAGraph
{
  bool									_firstcall;
  PNWayPoint							*_next;
  PNWayPoint							*_goal;
  PNPoint3f								_dest;
  const PNPoint3f&						_pos;
  std::list<PNWayPoint*>				_travellist;
  std::map<PNWayPoint*, PNWayPoint *>	_travelmap;

public:
  //PNPathFinding();
  PNPathFinding(const PNPoint3f&pos);
  virtual ~PNPathFinding();

  /* functions that set destination point and first waypoint to use */
  void									moveTo(const PNPoint3f& p);
  void									moveTo(PNWayPoint* wp);

  /*
  ** functions that finds the closest WP to specified point
  ** without heuristics for the moment
  */
  PNWayPoint							*closestWP(const PNPoint3f& p);

  /* fills specified PNPoint3fwith the coords of WP '_next' */
  void									getNext(PN3DObject& o);

  /* 
  ** selects next WP to reach, goes backwards if no solution is found
  ** fills specified PNPoint3fwith the coords of the WP to reach
  */
  void									moveNext(PN3DObject& o);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* !_PNPATHFINDING_HPP_ */

