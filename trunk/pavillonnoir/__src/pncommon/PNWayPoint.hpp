/*
 * PNWayPoint.hpp
 * 
 * Description :
 * PNWayPoint declaration
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

#ifndef _PNWAYPOINT_HPP_
# define _PNWAYPOINT_HPP_

#include <list>

#include "PN3DObject.hpp"

#define	DOUBLE	true
#define SINGLE	false

typedef struct _xmlTextReader	xmlTextReader;

namespace PN
{	
//////////////////////////////////////////////////////////////////////////

class PNIAGraph;
class PNWayPoint;

typedef struct	PNAPI	wayLink_s
{
  PNWayPoint*			next;
  pnfloat				weight;
  pnfloat				coef;
}						wayLink_t;

typedef	std::list<wayLink_t*> LINKLIST;

class PNAPI PNWayPoint : public PN3DObject
{
  bool					_selected;
  pnint					_id;
  LINKLIST				_links;
  PNIAGraph*			_graph;

public:
  PNWayPoint();
  PNWayPoint(PNIAGraph* g);
  PNWayPoint(pnint id, PNPoint &pos, PNIAGraph* g);
  PNWayPoint(pnint id, pnfloat x, pnfloat y, pnfloat z, PNIAGraph* g);
  virtual ~PNWayPoint();

  /* extracts int # from "id_#" */
  int	  _parseID(std::string id);

  /* functions to add a link to the WP preventing double entries */
  pnbool					addLink(PNWayPoint *p, pnfloat coef);
  pnbool					addLink(wayLink_t &link);

  /* functions to delete a link from the list */
  pnbool					deleteLink(PNWayPoint *p);
  pnbool					deleteLink(wayLink_t &link);

  /* returns _id */
  pnint 					getId();

  /* returns _nbLinks */
  pnint 					getNbLinks();

  /* return _graph */
  PNIAGraph*				getGraph();

  /* prints id and coords of the WP to std::cout */
  void					print();

  /* returns a reference to _links */
  LINKLIST&				getLinks();

  /* render each links */
  void					render();
  void					renderLinks();

  /* Change model color wether the wp is selected or not */
  void					setSelected();

  //////////////////////////////////////////////////////////////////////////

  pnint serializeInStream(std::ostream& o);
  pnint unserializeFromXML(xmlTextReader* _reader);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* !_PNWAYPOINT_HPP_ */
