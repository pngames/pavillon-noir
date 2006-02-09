/*
 * PNIAGraph.hpp
 * 
 * Description :
 * PNIAGraph declaration
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

#ifndef _PNIAGRAPH_HPP_
# define _PNIAGRAPH_HPP_

#include <list>
#include <map>

#include "PNObject.hpp"
#include "IPNSerializable.hpp"

#define LNK_FROM_MKP	"from"
#define	LNK_TO_MKP		"to"
#define	LNK_COEF_MKP	"coef"

typedef struct _xmlTextReader	xmlTextReader;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNWayPoint;

typedef std::list<PNWayPoint*>	WPLIST;
typedef std::map<int,PNWayPoint*> WPIDMAP;

class PNAPI					PNIAGraph : public PNObject, public IPNSerializable
{
private:
  WPLIST					_wayPoints;
  WPIDMAP					_wpidmap;
  pnint						_idMax;

  pnbool					addWayPoint(pnint id, PNPoint3f&pos);			
  pnbool					addWayPoint(pnint id, pnfloat x, pnfloat y, pnfloat z);
  pnbool					addWayPoint(PNWayPoint* wp);
public:
  PNIAGraph();
  virtual ~PNIAGraph();

  /* adds a WP at specified position and gives it an id number */
  pnint						addWayPoint(PNPoint3f&pos);
  pnint						addWayPoint(pnfloat x, pnfloat y, pnfloat z);

  /* functions to delete WP by id or ptr. delete links to it too */
  std::list<pnint>			deleteWayPoint(PNWayPoint *wp);
  std::list<pnint>			deleteWayPoint(pnint id);

  /*
  ** functions that create links from 1 WP to another
  ** if type is DOUBLE, links wp1 with w2 and also wp2 with wp1
  ** if type is SINGLE, only links wp1 with wp2
  */
  pnbool					makeLink(PNWayPoint &wp1, PNWayPoint &wp2, pnbool type = true, pnfloat coef = 1.0);
  pnbool					makeLink(PNWayPoint &wp1, pnint id, pnbool type = true, pnfloat coef = 1.0);
  pnbool					makeLink(pnint id1, pnint id2, pnbool type = true, pnfloat coef = 1.0);
  pnint						getNbWayPoints();

  /* returns a reference on _wayPoints */
  WPLIST&					getWayPoints();

  /* return pointer to the WP corresponding to the given id */
  PNWayPoint*				getWPFromId(int id);

  /* save/load a graph to/from a file/stream */
  pnint						serializeInStream(std::ostream& o);
  pnint						unserializeFromFile(const boost::filesystem::path& file);
  int						processChild(xmlTextReader* _reader);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* !_PNIAGRAPH_HPP_ */

