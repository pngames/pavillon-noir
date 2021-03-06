/*
 * PNWayPoint.cpp
 * 
 * Description :
 * PNWayPoint definition
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

#include <math.h>
#include <iostream>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnxml.h"
#include "PNWPModel.hpp"
#include "PNWayPoint.hpp"

using namespace PN;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNWayPoint::PNWayPoint()
{
  _model = PNWPModel::getInstance();
  _selected = false;
  _serializeInXML = false;

  _objType = OBJTYPE_WAYPOINT;
}

PNWayPoint::PNWayPoint(PNIAGraph* g)
{
  _model = PNWPModel::getInstance();
  _selected = false;
  _objType = OBJTYPE_WAYPOINT;
  _graph = g;
}

PNWayPoint::PNWayPoint(pnint id, PNPoint3f&pos, PNIAGraph* g)
{
  _model = PNWPModel::getInstance();
  _id = id;
  _coord.x = pos.x;
  _coord.y = pos.y;
  _coord.z = pos.z;
  _objType = OBJTYPE_WAYPOINT;
  _selected = false;
  _graph = g;
}

PNWayPoint::PNWayPoint(pnint id, pnfloat x, pnfloat y, pnfloat z, PNIAGraph* g)
{
  _model = PNWPModel::getInstance();
  _id = id;
  _coord.x = x;
  _coord.y = y;
  _coord.z = z;
  _objType = OBJTYPE_WAYPOINT;
  _selected = false;
  _graph = g;
}

PNWayPoint::~PNWayPoint()
{
}

pnbool
PNWayPoint::addLink(PNWayPoint *p, pnfloat coef)
{
  PNLOCK(this);

  wayLink_t	*link = new wayLink_t;

  for (std::list<wayLink_t*>::iterator i = _links.begin(); i != _links.end();
	i++)
  {
	if ((*i)->next->getId() == p->getId())
	  return false;
  }
  link->next = p;
  link->weight = _coord.getDistance((PNPoint3f&)p->getCoord());
  link->coef = coef;
  _links.push_back(link);

  return true;
}

pnbool
PNWayPoint::addLink(wayLink_t &link)
{
  PNLOCK(this);

  for (std::list<wayLink_t*>::iterator i = _links.begin(); i != _links.end(); i++)
  {
	if ((*i)->next->getId() == link.next->getId())
	  return false;
  }
  
  _links.push_back(&link);

  return true;
}

pnbool
PNWayPoint::deleteLink(wayLink_t &link)
{
  PNLOCK(this);

  _links.remove(&link);

  return true;
}

pnbool
PNWayPoint::deleteLink(PNWayPoint *p)
{
  PNLOCK(this);

  for (std::list<wayLink_t*>::iterator i = _links.begin(); i != _links.end(); i++)
  {
	if ((*i)->next->getId() == p->getId())
	{
	  _links.erase(i);

	  return true;
	}
  }

  return false;
}

pnint
PNWayPoint::getId()
{
  return (_id);
}

pnint
PNWayPoint::getNbLinks()
{
  return (pnint)_links.size();
}

LINKLIST&
PNWayPoint::getLinks()
{
  return (_links);
}

PNIAGraph*
PNWayPoint::getGraph()
{
  return (_graph);
}

void
PNWayPoint::print()
{
  std::cout << _id << " (" << _coord.x << " ," << _coord.y << " ," << _coord.z
	<< ")\n" << std::endl;
}

pnint
PNWayPoint::serializeInStream(std::ostream& o)
{
  PNLOCK(this);

  o << "<wp id=\"" << PNXML_IDBASE_VAL << _id << "\" x=\"" << _coord.x << "\" y=\"" << _coord.y << "\" z=\""
	<< _coord.z << "\"/>" << std::endl;

  return PNEC_SUCCESS;
}

int
PNWayPoint::_parseID(std::string id)
{
  std::string idstr((const char *)PNXML_IDBASE_VAL);
  std::string::size_type	  index = id.find(idstr);

  if (index == std::string::npos)
	return atoi(id.c_str());

  return atoi(id.c_str() + index + idstr.size());
}

pnint
PNWayPoint::unserializeFromXML(xmlTextReader* _reader)
{
  PNLOCK(this);

  xmlChar *attr;

  attr = xmlTextReaderGetAttribute(_reader, (const xmlChar *) PNXML_ID_ATTR);
  _id = _parseID((char*)attr);
  attr = xmlTextReaderGetAttribute(_reader, (const xmlChar *) PNXML_COORDX_ATTR);
  _coord.x = (pnfloat)atof((char*)attr);
  attr = xmlTextReaderGetAttribute(_reader, (const xmlChar *) PNXML_COORDY_ATTR);
  _coord.y = (pnfloat)atof((char*)attr);
  attr = xmlTextReaderGetAttribute(_reader, (const xmlChar *) PNXML_COORDZ_ATTR);
  _coord.z = (pnfloat)atof((char*)attr);

  return PNEC_SUCCESS;
}

void
PNWayPoint::render()
{
  PNLOCK(this);

  if (_selected)
  {
	((PNWPModel*)_model)->setSlctColor();
	PN3DObject::render();
	((PNWPModel*)_model)->setDflColor();
  }
  else
	PN3DObject::render();

  renderLinks();
}

void
PNWayPoint::renderLinks()
{
  PNLOCK(this);

  for (LINKLIST::iterator  i = _links.begin(); i != _links.end(); i++)
  {
	PNWPModel*	m = (PNWPModel*)_model;

	static PNPoint3f	p1(0.0f, 0.0f, 0.0f);
	PNPoint3f			p2 = (*i)->next->getCoord();
	pnpoint4f		slctColor = {1.0f, 1.0f, 1.0f, 0.0f};
	pnpoint4f		dflColor = {0.0f, 0.0f, 0.0f, 0.0f};

	p2.x -= _coord.x;
	p2.y -= _coord.y;
	p2.z -= _coord.z;

	if (_selected)
	  m->renderLink(p1, p2, slctColor);
	else
	  m->renderLink(p1, p2, dflColor);
	/*pnerror(PN_LOGLVL_DEBUG, "rendering link from(%f,%f,%f) to (%f,%f,%f)",
	_coord.x, _coord.y, _coord.z, p.x, p.y, p.z);*/
  }
  _selected = false;
}

void
PNWayPoint::setSelected()
{
  PNLOCK(this);

  _selected = true;
}

//////////////////////////////////////////////////////////////////////////
};

