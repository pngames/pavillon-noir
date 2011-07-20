/*
 * PNIAGraph.cpp
 * 
 * Description :
 * PNIAGraph definition
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

#include <boost/filesystem/path.hpp>
#include <stdio.h>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNIAGraph::PNIAGraph()
{
  _idMax = 0;
}

PNIAGraph::~PNIAGraph()
{
}

pnbool
PNIAGraph::addWayPoint(int id, PNPoint3f&pos)
{
  PNWayPoint						*wp = new PNWayPoint(id, pos, this);	
  std::list<PNWayPoint*>::iterator  i;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	PNPoint3f							coord = (*i)->getCoord();

	if (((*i)->getId() == id) || (coord.x == pos.x && coord.y == pos.y && coord.z == pos.z))
	{
	  delete wp;
	  return false;
	}
  }

  _wayPoints.push_back(wp);
  _wpidmap[id] = wp;
  if (id > _idMax)
	_idMax = id;
  return true;
}

pnbool
PNIAGraph::addWayPoint(pnint id, pnfloat x, pnfloat y, pnfloat z)
{
  PNWayPoint						*wp = new PNWayPoint(id, x, y, z, this);	
  std::list<PNWayPoint*>::iterator  i;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	PNPoint3f							coord = (*i)->getCoord();

	if (((*i)->getId() == id) || (coord.x == x && coord.y == y && coord.z == z))
	{
	  delete wp;
	  return false;
	}
  }

  _wayPoints.push_back(wp);
  _wpidmap[id] = wp;
  if (id > _idMax)
	_idMax = id;
  return true;
}

pnbool
PNIAGraph::addWayPoint(PNWayPoint* wp)
{
  std::list<PNWayPoint*>::iterator  i;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	PNPoint3f							coord = (*i)->getCoord();

	if (((*i)->getId() == wp->getId()) || (coord.x == wp->getX() && coord.y == wp->getY() && coord.z == wp->getZ()))
	{
	  delete wp;
	  return false;
	}
  }

  _wayPoints.push_back(wp);
  _wpidmap[wp->getId()] = wp;
  if (wp->getId() > _idMax)
	_idMax = wp->getId();
  return true;
}

pnint
PNIAGraph::addWayPoint(PNPoint3f&pos)
{
  PNWayPoint							*wp = new PNWayPoint(_idMax + 1, pos, this);	
  std::list<PNWayPoint *>::iterator	i;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	PNPoint3f						coord = (*i)->getCoord();

	if (coord.x == pos.x && coord.y == pos.y && coord.z == pos.z)
	  return false;
  }

  _wayPoints.push_back(wp);
  _wpidmap[wp->getId()] = wp;
  _idMax++;
  return _idMax;
}

pnint
PNIAGraph::addWayPoint(pnfloat x, pnfloat y, pnfloat z)
{
  PNWayPoint							*wp = new PNWayPoint(_idMax + 1, x, y, z, this);
  std::list<PNWayPoint *>::iterator	i;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	PNPoint3f						coord = (*i)->getCoord();

	if (coord.x == x && coord.y == y && coord.z == z)
	  return false;
  }

  _wayPoints.push_back(wp);
  _wpidmap[wp->getId()] = wp;
  _idMax++;
  return _idMax;
}

std::list<int>
PNIAGraph::deleteWayPoint(int id)
{
  pnbool							  erase = false;
  PNWayPoint						  *wp;
  std::list<PNWayPoint*>::iterator  i;
  std::list<pnint>					  ls;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	if ((*i)->getId() == id)
	{
	  wp = (*i);
	  _wpidmap.erase(wp->getId());
	  _wayPoints.erase(i);
	  erase = true;
	  break;
	}
  }

  if (erase == true)
	for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
	  if ((*i)->deleteLink(wp) == true)
		ls.push_back((*i)->getId());

  delete wp;
  return ls;
}

std::list<pnint>
PNIAGraph::deleteWayPoint(PNWayPoint *wp)
{
  std::list<PNWayPoint*>::iterator  i;
  std::list<pnint>				  ls;

  _wayPoints.remove(wp);
  _wpidmap.erase(wp->getId());
  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
	if ((*i)->deleteLink(wp) == true)
	  ls.push_back((*i)->getId());

  delete wp;
  return ls;
}

pnbool	
PNIAGraph::makeLink(PNWayPoint &wp1, PNWayPoint &wp2, pnbool type, pnfloat coef)
{
  if (wp1.getId() == wp2.getId())
	return false;

  wp1.addLink(&wp2, coef);
  if (type == DOUBLE)
	wp2.addLink(&wp1, coef);
  return true;
}

pnbool
PNIAGraph::makeLink(PNWayPoint &wp1, pnint id, pnbool type, pnfloat coef)
{
  std::list<PNWayPoint*>::iterator	i;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	if ((*i)->getId() == id)
	{
	  wp1.addLink(*i, coef);
	  if (type == DOUBLE)
		(*i)->addLink(&wp1, coef);
	  return true;
	}
  }
  return false;
}

pnbool
PNIAGraph::makeLink(pnint id1, pnint id2, pnbool type, pnfloat coef)
{
  PNWayPoint							*wp1 = NULL;
  PNWayPoint							*wp2 = NULL;
  std::list<PNWayPoint*>::iterator	i;

  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	if ((*i)->getId() == id1)
	  wp1 = *i;
	if ((*i)->getId() == id2)
	  wp2 = *i;
  }

  if (wp1 == NULL || wp2 == NULL)
	return false;

  wp1->addLink(wp2, coef);
  if (type == DOUBLE)
	wp2->addLink(wp1, coef);
  return true;
}

WPLIST&
PNIAGraph::getWayPoints()
{
  return (_wayPoints);
}

pnint
PNIAGraph::getNbWayPoints()
{
  return ((pnint)_wayPoints.size());
}

PNWayPoint*
PNIAGraph::getWPFromId(int id)
{
  PNWayPoint* wp = _wpidmap.find(id)->second;
  return wp;
}

pnint
PNIAGraph::serializeInStream(std::ostream& o)
{
  WPLIST::iterator	i;

  o << "<?xml version=\"1.0\"?>" << std::endl;
  o << "<!DOCTYPE graph SYSTEM \"../waypoints.dtd\">" << std::endl;
  o << "<graph>" << std::endl;
  o << "<listwp>" << std::endl;
  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
	(*i)->serializeInStream(o);
  o << "</listwp>" << std::endl;
  o << "<listlnk>" << std::endl;
  for (i = _wayPoints.begin(); i != _wayPoints.end(); i++)
  {
	LINKLIST&		l = (*i)->getLinks();

	for (LINKLIST::iterator i2 = l.begin(); i2 != l.end(); i2++)
	  o << "<lnk from=\"" << (*i)->getId() << "\" to=\"" << (*i2)->next->getId()
	  << "\" coef=\"" << (*i2)->coef << "\"/>" << std::endl;
  }
  o << "</listlnk>" << std::endl;
  o << "</graph>" << std::endl;
  return PNEC_SUCCESS;
}

pnint
PNIAGraph::unserializeFromFile(const boost::filesystem::path& file)
{
  int				ret;
  xmlTextReaderPtr	_reader;

  _reader = xmlNewTextReaderFilename(file.string().c_str());
  if (_reader != NULL)
  {
	ret = xmlTextReaderRead(_reader);
	while (ret == 1)
	{
	  processChild(_reader);
	  ret = xmlTextReaderRead(_reader);
	}
	xmlFreeTextReader(_reader);
	if (ret != 0)
	{
	  printf("%s : failed to parse\n", file.string().c_str());
	  return PNEC_FAILED_TO_PARSE;
	}
  }
  else
  {
	printf("Unable to open %s\n", file.string().c_str());
	return PNEC_FILE_NOT_FOUND;
  }
  return PNEC_SUCCESS;
}

int
PNIAGraph::processChild(xmlTextReader* _reader)
{
  xmlChar *name, *value, *attr;

  name = xmlTextReaderName(_reader);
  value = xmlTextReaderValue(_reader);

  if (!xmlStrcmp(name, (const xmlChar *) "wp"))
  {
	PNWayPoint*	wp = new PNWayPoint(this);

	wp->unserializeFromXML(_reader);
	addWayPoint(wp);
  }

  else if (!xmlStrcmp(name, (const xmlChar *) "lnk"))
  {
	int	  from, to;
	float coef;

	attr = xmlTextReaderGetAttribute(_reader, (const xmlChar *) LNK_FROM_MKP);
	from = atoi((char*)attr);
	attr = xmlTextReaderGetAttribute(_reader, (const xmlChar *) LNK_TO_MKP);
	to = atoi((char*)attr);
	attr = xmlTextReaderGetAttribute(_reader, (const xmlChar *) LNK_COEF_MKP);
	coef = (float)atof((char*)attr);
	makeLink(from, to, SINGLE, coef);
  }

  if (name != NULL)
	xmlFree(name);
  if (value != NULL)
	xmlFree(value);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};

