/*
* PNGameMap.cpp
* 
* Description :
* PNGameMap definition
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

#include <boost/filesystem/operations.hpp>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnimport.h"
#include "pnresources.h"

#include "PN3DCamera.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PNPhysicsInterface.hpp"
#include "PNPhysicalObject.hpp"
#include "PN3DCamera.hpp"
#include "PNRendererInterface.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNCharacter.hpp"

#include "pnxml.h"
#include "pno_format.h"

#include "PNGameMap.hpp"

namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

PNGameMap::PNGameMap()
{
}

PNGameMap::~PNGameMap()
{ 
}

const PNGameMap::ObjMap&
PNGameMap::getEntityList() const
{
  return _entityList;
}

pnint
PNGameMap::_unserializeSkybox(xmlNode* root)
{
  PNRendererInterface::getInstance()->setSkyBoxEnabled(XMLUtils::xmlGetProp(root, PNXML_ENABLED_ATT, false));

  //////////////////////////////////////////////////////////////////////////
  
  return PNEC_SUCCESS;
}

pnint
PNGameMap::_unserializeEntity(xmlNode* node)
{
  std::string id = (char *)xmlGetProp(node, PNXML_ID_ATTR);
  std::string className = (char *)xmlGetProp(node, PNXML_CLASS_ATTR);

  //////////////////////////////////////////////////////////////////////////

  if (_entityList.find(id) != _entityList.end())
  {
	pnerror(PN_LOGLVL_ERROR, "An object with id: [%s] already exists", id.c_str());

	return PNEC_ERROR;
  }

  //////////////////////////////////////////////////////////////////////////

  addToMap(className, id);

  PN3DObject*  object = _entityList[id];

  if (object == NULL)
	return PNEC_ERROR;

  //////////////////////////////////////////////////////////////////////////
  
  // create boost path
  //fs::path  file(DEF::objectFilePath + (const char*)xmlGetProp(node, PNXML_MODELREFERENCE_ATTR), fs::native);

  //////////////////////////////////////////////////////////////////////////

  pnint		error = -1;

  for (xmlNodePtr n = node->children; n != NULL; n = n->next)
  {
	if (PNO_XMLNODE_ROOT == (const char*)n->name)
	{
	  error = object->unserializeFromXML(n);
	  break;
	}
  }

  if (error == -1)
	error = object->unserializeFromPath(DEF::objectFilePath + (const char*)xmlGetProp(node, PNXML_MODELREFERENCE_ATTR));

  // check for errors
  if (error != PNEC_SUCCESS)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", (const char*)xmlGetProp(node, PNXML_MODELREFERENCE_ATTR), pnGetErrorString(error));

	return error;
  }

  //////////////////////////////////////////////////////////////////////////

  // set coordinates
  pnfloat x = (pnfloat)(atof((const char *)(xmlGetProp(node, PNXML_COORDX_ATTR))));
  pnfloat y = (pnfloat)(atof((const char *)(xmlGetProp(node, PNXML_COORDY_ATTR))));
  pnfloat z = (pnfloat)(atof((const char *)(xmlGetProp(node, PNXML_COORDZ_ATTR))));
  object->setCoord(x, y, z);

  // set orientation
  pnfloat xx = (pnfloat)(atof((const char *)(xmlGetProp(node, PNXML_ROTX_ATTR))));
  pnfloat yy = (pnfloat)(atof((const char *)(xmlGetProp(node, PNXML_ROTY_ATTR))));
  pnfloat zz = (pnfloat)(atof((const char *)(xmlGetProp(node, PNXML_ROTZ_ATTR))));
  pnfloat ww = (pnfloat)(atof((const char *)(xmlGetProp(node, PNXML_ROTW_ATTR))));
  object->setOrient(xx, yy, zz, ww);

  //////////////////////////////////////////////////////////////////////////

  // physical settings
  if (object->getPhysicalObject() != NULL)
  {
	// set the object status (static/dynamic)
	bool isStatic = (!strcmp((const char*)xmlGetProp(node, PNXML_ENVTYPE_ATTR), "dynamic")) ? false : true;
	object->getPhysicalObject()->setStatic(isStatic);
	// set the physical object coordinates
	object->getPhysicalObject()->setCoord(object->getCoord());
	// set the physical object orientation
	object->getPhysicalObject()->setOrient(object->getOrient());
  }

  return PNEC_SUCCESS;
}

pnint
PNGameMap::_unserializeNode(xmlNode* node)
{
  if (xmlStrEqual(PNXML_ENTITY_MKP, node->name))
	_unserializeEntity(node);
  if (xmlStrEqual(PNXML_SKYBOX_MKP, node->name))
	_unserializeSkybox(node);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

int	PNGameMap::unserializeFromXML(xmlNode* node)
{
  //////////////////////////////////////////////////////////////////////////

  xmlNodePtr root = node;
  xmlNodePtr current;

  pnint	error = PNEC_SUCCESS;

  //////////////////////////////////////////////////////////////////////////
  // LISTENTITIES

  if (xmlStrEqual(root->name, PNXML_LISTENTITIES_MKP) && root->children != NULL)
  {
	for (current = root->children; current != NULL; current = current->next)
	{
	  error = _unserializeNode(current);

	  if (error != PNEC_SUCCESS)
		break ;
	}
  }

  //////////////////////////////////////////////////////////////////////////
  // OTHERS

  return error;
}

pnint PNGameMap::unserializeFromFile(const fs::path& dir)
{
  _wpFile = new fs::path(dir.string() + "/waypoints.xml", fs::native);

  //////////////////////////////////////////////////////////////////////////

  fs::path file(dir.string() + "/entities.xml", fs::native);

  return IPNXMLSerializable::unserializeFromFile(file);
}

void PNGameMap::addToMap(const std::string& entityName,const std::string& id)
{
  _entityList[id] = new PN3DSkeletonObject();
}

void PNGameMap::clear()
{
  _entityList.clear();
  PNImportManager::getInstance()->clean(); //fixeMe
}

const std::string&	PNGameMap::getWpFile()
{
  return _wpFile->string();
}
