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

//////////////////////////////////////////////////////////////////////////

namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

//////////////////////////////////////////////////////////////////////////

#define _SEND_LOADING_STEP(d_event, d_cmd, d_eventData, d_name, d_step)	\
  (d_eventData).cmd = (d_cmd);			\
  (d_eventData).item = (d_name);		\
  (d_eventData).progressVal = (d_step);	\
  PNEventManager::getInstance()->sendEvent(d_event, this, &(d_eventData));	\

#define SEND_LOAD_STEP(d_eventData, d_name, d_step)	\
  _SEND_LOADING_STEP(PN_EVENT_ML_STEP, PNGameLoadStepsMapEventData::LSTATE_CMD_NONE, d_eventData, d_name, d_step)
#define SEND_LOAD_STEP_POP(d_eventData, d_name, d_step)	\
  _SEND_LOADING_STEP(PN_EVENT_ML_STEP, PNGameLoadStepsMapEventData::LSTATE_CMD_POP, d_eventData, d_name, d_step)
#define SEND_LOAD_STEP_PUSH(d_eventData, d_name, d_step)	\
  _SEND_LOADING_STEP(PN_EVENT_ML_STEP, PNGameLoadStepsMapEventData::LSTATE_CMD_PUSH, d_eventData, d_name, d_step)

#define SEND_UNLOAD_STEP(d_eventData, d_name, d_step)	\
  _SEND_LOADING_STEP(PN_EVENT_MU_STEP, PNGameLoadStepsMapEventData::LSTATE_CMD_NONE, d_eventData, d_name, d_step)
#define SEND_UNLOAD_STEP_POP(d_eventData, d_name, d_step)	\
  _SEND_LOADING_STEP(PN_EVENT_MU_STEP, PNGameLoadStepsMapEventData::LSTATE_CMD_POP, d_eventData, d_name, d_step)
#define SEND_UNLOAD_STEP_PUSH(d_eventData, d_name, d_step)	\
  _SEND_LOADING_STEP(PN_EVENT_MU_STEP, PNGameLoadStepsMapEventData::LSTATE_CMD_PUSH, d_eventData, d_name, d_step)

//////////////////////////////////////////////////////////////////////////

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

pnfloat
PNGameMap::getMpp()
{
  return _mpp;
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
  PNGameLoadStepsMapEventData	eaLoadStep;
  pnfloat						nbSteps = 5.0f;

  //////////////////////////////////////////////////////////////////////////

  std::string id = (char *)xmlGetProp(node, PNXML_ID_ATTR);
  std::string className = (char *)xmlGetProp(node, PNXML_CLASS_ATTR);

  SEND_LOAD_STEP(eaLoadStep, className + " " + id, 0.0f)

  //////////////////////////////////////////////////////////////////////////

  if (_entityList.find(id) != _entityList.end())
  {
	pnerror(PN_LOGLVL_ERROR, "An object with id: [%s] already exists", id.c_str());

	return PNEC_ERROR;
  }

  //////////////////////////////////////////////////////////////////////////

  SEND_LOAD_STEP(eaLoadStep, className + " " + id + ": constructing", 1.0f / nbSteps)

  addToMap(className, id);

  PN3DObject*  object = _entityList[id];

  if (object == NULL)
	return PNEC_ERROR;

  //////////////////////////////////////////////////////////////////////////

  SEND_LOAD_STEP(eaLoadStep, className + " " + id + ": parsing", 2.0f / nbSteps)

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

  SEND_LOAD_STEP(eaLoadStep, className + " " + id + ": initialising", 3.0f / nbSteps)

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
	SEND_LOAD_STEP(eaLoadStep, className + " " + id + ": initialising physics", 4.0f / nbSteps)

	// set the object status (static/dynamic)
	bool isStatic = (!strcmp((const char*)xmlGetProp(node, PNXML_ENVTYPE_ATTR), "dynamic")) ? false : true;
	object->getPhysicalObject()->setStatic(isStatic);
  }

  SEND_LOAD_STEP(eaLoadStep, className + " " + id + ": ending", 5.0f / nbSteps)

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

pnint
PNGameMap::unserializeFromXML(xmlNode* root)
{
  PNGameLoadStepsMapEventData	eaLoadStep;

  SEND_LOAD_STEP(eaLoadStep, _path, 0.0f)

  //////////////////////////////////////////////////////////////////////////

  _mpp = XMLUtils::xmlGetProp(root, PNXML_MPP_ATTR, 1.0f);

  //////////////////////////////////////////////////////////////////////////
  
  pnint	error = PNEC_SUCCESS;

  //////////////////////////////////////////////////////////////////////////
  // ENTITIES

  if (xmlStrEqual(root->name, PNXML_LISTENTITIES_MKP) && root->children != NULL)
  {
	pnuint	nbNodes = XMLUtils::xmlGetNbChilds(root);
	pnuint	stepSize = XMLUtils::xmlGetNbChilds(root);

	pnfloat	nb = 0.0f;

	for (xmlNodePtr current = root->children; current != NULL; current = current->next)
	{
	  SEND_LOAD_STEP_PUSH(eaLoadStep, _path, 1.0 / nbNodes)
	  error = _unserializeNode(current);
	  SEND_LOAD_STEP_POP(eaLoadStep, _path, 1.0 / nbNodes)

	  SEND_LOAD_STEP(eaLoadStep, _path, ++nb / nbNodes)

	  if (error != PNEC_SUCCESS)
		break ;
	}
  }

  //////////////////////////////////////////////////////////////////////////

  return error;
}

pnint
PNGameMap::unserializeFromFile(const fs::path& dir)
{
  _wpFile = dir.string() + "/waypoints.xml";

  //////////////////////////////////////////////////////////////////////////
  
  fs::path file(dir.string() + "/entities.xml", fs::native);

  return IPNXMLSerializable::unserializeFromFile(file);
}

//////////////////////////////////////////////////////////////////////////

pnint
PNGameMap::_serializeSkybox(xmlNode* node)
{
  return PNEC_NOT_IMPLEMENTED;
}

pnint
PNGameMap::_serializeEntity(xmlNode* node, PN3DObject* object)
{
  xmlNewProp(node, PNXML_ID_ATTR, BAD_CAST object->getId().c_str());
  xmlNewProp(node, PNXML_MODELREFERENCE_ATTR, BAD_CAST object->getPath()->c_str());

  /*
	<!ATTLIST entity class CDATA #REQUIRED>
	<!ATTLIST entity envtype (dynamic|static|ground) "dynamic">
	<!ATTLIST entity objtype (object|dynamic|character) "object">*/

  const PNPoint3f&	position = object->getCoord();

  XMLUtils::xmlNewProp(node, PNXML_COORDX_ATTR, position.x);
  XMLUtils::xmlNewProp(node, PNXML_COORDY_ATTR, position.y);
  XMLUtils::xmlNewProp(node, PNXML_COORDZ_ATTR, position.z);

  const PNQuatf&	orient = object->getOrient();

  XMLUtils::xmlNewProp(node, PNXML_ROTX_ATTR, orient.x);
  XMLUtils::xmlNewProp(node, PNXML_ROTY_ATTR, orient.y);
  XMLUtils::xmlNewProp(node, PNXML_ROTZ_ATTR, orient.z);
  XMLUtils::xmlNewProp(node, PNXML_ROTW_ATTR, orient.w);

  //////////////////////////////////////////////////////////////////////////
  
  object->serializeInXML(node);

  return PNEC_SUCCESS;
}

/// Save object into XML file
pnint
PNGameMap::serializeInXML(xmlNode* root, pnbool isroot/* = false*/)
{
  if (isroot == false)
	root = xmlNewChild(root, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  //////////////////////////////////////////////////////////////////////////

  _serializeSkybox(root);

  for (ObjMap::iterator	it = _entityList.begin(); it != _entityList.end(); ++it)
	_serializeEntity(root, it->second);

  return PNEC_SUCCESS;
}

/// Save object to file
pnint
PNGameMap::serializeInFile(const boost::filesystem::path& dir)
{
  //////////////////////////////////////////////////////////////////////////
  // Entities

  fs::path file(dir.string() + "/entities.xml", fs::native);

  IPNXMLSerializable::serializeInFile(file);

  //////////////////////////////////////////////////////////////////////////
  // Waypoints

  //_graph->serializeInPath(dir.string() + "waypoints.xml");

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

void PNGameMap::addToMap(const std::string& entityName,const std::string& id)
{
  _entityList[id] = new PN3DSkeletonObject();
}

void PNGameMap::clear()
{
  PNGameLoadStepsMapEventData	eaLoadStep;

  SEND_UNLOAD_STEP(eaLoadStep, _path, 0.0f)

  _entityList.clear();

  SEND_UNLOAD_STEP(eaLoadStep, _path, 0.5f)

  SEND_UNLOAD_STEP_PUSH(eaLoadStep, _path, 0.5f)
  PNImportManager::getInstance()->clean(); //fixeMe
  SEND_UNLOAD_STEP_POP(eaLoadStep, _path, 0.5f)

  SEND_UNLOAD_STEP(eaLoadStep, _path, 1.0f)
}

const std::string&	PNGameMap::getWpFile()
{
  return _wpFile;
}
