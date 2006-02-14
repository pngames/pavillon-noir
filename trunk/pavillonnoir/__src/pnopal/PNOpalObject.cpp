/*
 * PNOpalObject.cpp
 * 
 * Description :
 * PNOpalObject definition
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
#include "pnplugins.h"
#include "pnimport.h"
#include "pnp_format.h"

#include "PNPhysicsInterface.hpp"
#include "PNPhysicalObject.hpp"
#include "PNGameInterface.hpp"
#include "PNGameMap.hpp"
#include "PNConsole.hpp"

#include "PNOpal.hpp"
#include "PNOpalObject.hpp"
#include "PNOpalEvents.hpp"
#include "PNOpalMeshImporter.hpp"

#include "PNVector3f.hpp"
#include "PNMatrixTR4f.hpp"

namespace fs = boost::filesystem;

#define DEFAULT_PLAYER_ID "Player"

namespace PN {

/** PNOpalObject constructor
*
* \param  sim  a pointer on the opal simulation
*/ 

PNOpalObject::PNOpalObject(opal::Simulator* sim) : _blueprint(), _blueprintInstance()
{
  _sim = sim;
  _player = false;
}

/** PNOpalObject destructor
*/
PNOpalObject::~PNOpalObject()
{
}

//////////////////////////////////////////////////////////////////////////

void 
PNOpalObject::update()
{
}

/** Display the Axis Aligned Bounding Boxes of the solid (physical object)
*/
void 
PNOpalObject::render()
{
  pnfloat color[4] = {1.0f, 1.0f, 1.0f, 0.3f};

  opal::ShapeData* shapeData = _solid->getData().getShapeData(0);

  switch(shapeData->getType())
  {
  case opal::BOX_SHAPE:
	{
	  opal::BoxShapeData* boxData = (opal::BoxShapeData*)shapeData;
	  PNRendererInterface::getInstance()->renderBox(_aabb[1] - _aabb[0], _aabb[3] - _aabb[2], _aabb[5] - _aabb[4], color, _offset);
	  break;
	}
  case opal::SPHERE_SHAPE:
	{
	  opal::SphereShapeData* sphereData = (opal::SphereShapeData*)shapeData;
	  PNRendererInterface::getInstance()->renderSphere(_radius, 20, 20, color, _offset);
	  break;
	}
  case opal::CAPSULE_SHAPE:
	{
	  opal::CapsuleShapeData* capsuleData = (opal::CapsuleShapeData*)shapeData;
	  PNRendererInterface::getInstance()->renderBox((pnfloat)_radius, _height, (pnfloat)_radius, color, _offset);
	  break;
	}
  case opal::PLANE_SHAPE:
	break;
  case opal::MESH_SHAPE:
	break;
  default:
	assert(false);
  }
}

//////////////////////////////////////////////////////////////////////////

/** Return the coordinates of the physical object
* 
* \return point coordinates
*/
const PNPoint3f&	
PNOpalObject::getCoord()
{
  opal::Point3r pos = _solid->getPosition();
  _coord.x = pos[0];
  _coord.y = pos[1];
  _coord.z = pos[2];

  return _coord;
}

/** Return the orientation of the physical object
* 
* \return orientation quaternion
*/ 
const PNQuatf&	
PNOpalObject::getOrient()
{
  opal::Quaternion quat = _solid->getQuaternion();

  _orient.x = quat[1];
  _orient.y = quat[2];
  _orient.z = quat[3];
  _orient.w = quat[0];
  
  return _orient;
}

/** Return the physical object's offset (scaled) between its rendering center and its center of mass
*
* \return offset
*/ 

const PNPoint3f&	
PNOpalObject::getOffset()
{
  return _offset;
}

/** Return the physical object's offset between its rendering center and its center of mass
*
* \return offset
*/ 
const PNPoint3f&	
PNOpalObject::getRenderOffset()
{
  return _renderOffset;
}

/** 
** \return opal physical object (opal::Solid)
*/ 
opal::Solid* 
PNOpalObject::getOpalSolid()
{
  return _solid;
}

/** Return distance between object's center and the ground
*/ 
pnfloat 
PNOpalObject::getDesiredHeight()
{
  return _desiredHeight;
}

/**
** \return the Opal raycast sensor (opal::RaycastSensor)
*/ 
opal::RaycastSensor* 
PNOpalObject::getPlayerSensor()
{
  return _playerSensor;
}

/**
** \return PNPlayer's ray lenght
*/ 
pnfloat 
PNOpalObject::getRayLenght()
{
  return _rayLenght;
}

pnbool
PNOpalObject::isPlayer()
{
  return _player;
}

//////////////////////////////////////////////////////////////////////////
// Core

/** Set the state of the physical object (static/dynamic)
*
* /param  state  true to make it static / false to make it dynamic
*/ 
void			
PNOpalObject::setStatic(bool state)
{
  _solid->setStatic(state);
}

/** Get the state of the physical object (static/dynamic)
*
* \return true if static, false if dynamic
*/
bool			
PNOpalObject::isStatic()
{
  return _solid->isStatic();
}

/** Set the coordinates and orientation of the physical object
*
* /param  coord  coordinates
* /param  orient  orientation
*/ 
void			
PNOpalObject::setTransform(const PNPoint3f& coord, const PNQuatf& orient, pnfloat scale)
{
  pnfloat			trans[3];
  opal::Matrix44r	transform;
  PNMatrix4f		pntransform;
  const PNPoint3f&	offset = getOffset();

  trans[0] = coord.x * scale + offset.x;
  trans[1] = coord.y * scale + offset.y;
  trans[2] = coord.z * scale + offset.z;

  pntransform.loadIdentity();
  pntransform.setTranslation(trans);
  pntransform.setRotationQuaternion(orient);
  transform.set(pntransform.getMatrix());

  _solid->setTransform(transform);
}


//////////////////////////////////////////////////////////////////////////
// Forces

/** Add a force to the solid
* /param  vec the force vector
* /param  magnitude the force magnitude
* /param  duration Specifies how long to apply the force. (in millisecond)
*/
void		
PNOpalObject::addForce(const PNVector3f& vec, pnfloat magnitude, pnfloat duration, pnbool isLocal)
{
  opal::Force f;
  
  if (isLocal == true)
	f.type = opal::LOCAL_FORCE_AT_LOCAL_POS;
  else
	f.type = opal::GLOBAL_FORCE_AT_LOCAL_POS;
  f.pos.set(PNPoint3f::ZERO.x, PNPoint3f::ZERO.y, PNPoint3f::ZERO.z);
  f.duration = duration;
  if (duration == 0.0f)
	f.singleStep = true;
  else
	 f.singleStep = false;
  opal::Vec3r v(vec.x, vec.y, vec.z);
  v *= magnitude;
  f.vec = v;

  _solid->addForce(f);
}

/** Add a torque to the solid
* /param  axis axis on which the torque will be applied
* /param  magnitude the torque magnitude
* /param  duration Specifies how long to apply the torque. (in millisecond)
*/
void		
PNOpalObject::addTorque(const PNVector3f& axis, pnfloat magnitude, pnfloat duration, pnbool isLocal)
{
  opal::Force f;

  f.type = opal::LOCAL_TORQUE;
  f.pos.set(PNPoint3f::ZERO.x, PNPoint3f::ZERO.y, PNPoint3f::ZERO.z);
  f.duration = duration;
  if (duration == 0.0f)
	f.singleStep = true;
  else
	f.singleStep = false;
  opal::Vec3r opalAxis(axis.x, axis.y, axis.z);
  opalAxis *= magnitude;
  f.vec = opalAxis;

  _solid->addForce(f);
}

//////////////////////////////////////////////////////////////////////////
// Movement motor

/** Enable the movementMotor attached to the solid
*
* /param  x desired x coordinate
* /param  y desired y coordinate
* /param  z desired z coordinate
* /param  orient desired orientation quaternion
*/
void		
PNOpalObject::setMovementMotor(pnfloat x, pnfloat y, pnfloat z, PNQuatf orient)
{
  /* motor data */
  _movementMotorData.solid = _solid;
  _movementMotorData.mode = opal::LINEAR_AND_ANGULAR_MODE;

  const PNPoint3f&	offset = getOffset();

  /* coordinates */
  _movementMotorData.desiredPos.set((opal::real)x + offset.x, (opal::real)y + offset.y, (opal::real)z + offset.z);

  /* creation of the orientation matrix */
  opal::Matrix44r transform;
  transform.makeIdentity();
  if (!orient.isIdentity())
  {
	transform.setRotation((opal::real)orient.w, (opal::real)orient.x, (opal::real)orient.y, (opal::real)orient.z);
	_movementMotorData.desiredUp.set(transform.getUp().getData());
	_movementMotorData.desiredRight.set(transform.getRight().getData());
	_movementMotorData.desiredForward.set(transform.getForward().getData());
  }

  /* optional motor data */
  _movementMotorData.linearKd = (opal::real)0.1;
  _movementMotorData.linearKs = (opal::real)100.0;
  _movementMotorData.angularKd = (opal::real)0.1;
  _movementMotorData.angularKs = (opal::real)200.0;

  /* motor init */
  _movementMotor->init(_movementMotorData);
}

/** Disable the movementMotor attached to the solid
*/

void		
PNOpalObject::destroyMovementMotor()
{
  _movementMotorData.solid = NULL;
  _movementMotor->init(_movementMotorData);
}

pnfloat
PNOpalObject::getRadius()
{
  return (pnfloat)_radius;
}

//////////////////////////////////////////////////////////////////////////
// IPNXMLSerializable

pnint		  
PNOpalObject::_parseTypePnm(const std::string& path)
{
  fs::path	  file(path, fs::no_check);

  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;
  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  //////////////////////////////////////////////////////////////////////////
  
  PNOpalMeshImporter* mesh = new PNOpalMeshImporter();
  opal::MeshShapeData meshData;
  
  mesh->unserializeFromPath(path);

  meshData.numVertices = mesh->getNbVertices();
  meshData.numTriangles = mesh->getNbFaces();

  meshData.vertexArray = mesh->getVertices();
  meshData.triangleArray = mesh->getFaces();

  //////////////////////////////////////////////////////////////////////////

  // create a solid
  _solid = _sim->createSolid();
  _solid->setStatic(true);

  // Add the mesh Shape to the Solid.
  _solid->addShape(meshData);
  
  return PNEC_SUCCESS;
}

pnint		  
PNOpalObject::_parseTypeOpal(const std::string& path)
{
  fs::path	  file(path, fs::no_check);

  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;
  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  //////////////////////////////////////////////////////////////////////////

  PNGameMap*  gm = PNGameInterface::getInstance()->getGameMap();
  pnfloat mpp = gm->getMpp();

  // create and instantiate the opal blueprint
  opal::loadFile(_blueprint, path);

  // object's coord offset
  opal::Matrix44r offset;
  offset.makeIdentity();

  /* Could be used if the PN3DObject was reachable here, in this case opal2pn would be deprecated */
  /*
  offset.scale( mpp );
  offset.makeTranslation( position[ 0 ], position[ 1 ], position[ 2 ] );
  offset.rotate( orientation[ 0 ], 1, 0, 0 );
  offset.rotate( orientation[ 1 ], 0, 1, 0 );
  offset.rotate( orientation[ 2 ], 0, 0, 1 );
  */

  _sim->instantiateBlueprint(_blueprintInstance, _blueprint, offset, mpp);
  _solid = _blueprintInstance.getSolid(0);

  //////////////////////////////////////////////////////////////////////////

  if (_solid != NULL)
  {
	_solid->getData().getShapeData(0)->getLocalAABB(_aabb);
	_desiredHeight = abs(_aabb[2]);
	_rayLenght = _desiredHeight * 2.0f;
	opal::ShapeData* shapeData = _solid->getData().getShapeData(0);

	// enlarge the local AABB (make the AABB rendering a little bigger)
	switch(shapeData->getType())
	{
	case opal::BOX_SHAPE:
	  {
		for (int i = 0; i < 6; i++)
		{
		  if (_aabb[i] < 0)
			_aabb[i] -= 0.1f;
		  else
			_aabb[i] += 0.1f;
		}
		_radius = _aabb[5] - _aabb[4]; // ugly hack (see obstacle detection)
		break;
	  }
	case opal::SPHERE_SHAPE:
	  {
		_radius = ((opal::SphereShapeData*)shapeData)->radius + 0.1;
		break;
	  }
	case opal::CAPSULE_SHAPE:
	  {
		_radius = ((opal::CapsuleShapeData*)shapeData)->radius + 0.1;
		_height = ((opal::CapsuleShapeData*)shapeData)->length + 0.1f;
		break;
	  }
	case opal::PLANE_SHAPE:
	  break;
	default:
	  assert(false);
	}
  }

  // check for loading errors
  if (!_solid)
	return PNEC_NOT_INITIALIZED;

  // set Collision handling function
  PNOpal* pnopalInstance = (PNOpal*)PNOpal::getInstance();
  _solid->setCollisionEventHandler((opal::CollisionEventHandler*)pnopalInstance->getEventHandler());

  // set the offsets (physically scaled & rendering)
  opal::real* translation = _solid->getTransform().getTranslation().getData();
  _offset.set(translation[0], translation[1], translation[2]);
  _renderOffset.set(translation[0] / mpp, translation[1] / mpp, translation[2] / mpp);

  // object spring motor
  _movementMotor = _sim->createSpringMotor();

  // create ground/obstacle detectors for PNPlayers
  if (_solid->getName() == DEFAULT_PLAYER_ID)
  {
	_player = true;

	opal::RaycastSensorData data;
	data.solid = _solid;
	data.ray.setOrigin(opal::Point3r(0, 0, 0));
	data.ray.setDir(opal::Vec3r(0, -1, 0));
	_playerSensor = _sim->createRaycastSensor();
	_playerSensor->init(data);

	_playerJoint = _sim->createJoint();
  }

  // enable the object
  _solid->setEnabled(true);

  return PNEC_SUCCESS;
}

pnint		  
PNOpalObject::_parsePhysics(xmlNode* node)
{
  xmlChar*	  attr = NULL;

  if ((attr = xmlGetProp(node, (const xmlChar *)PNP_XMLPROP_TYPE)) != NULL)
  {
	if (PNP_XMLATTR_TYPEOPAL == (const char*)attr)
	{
	  if ((attr = xmlGetProp(node, (const xmlChar *)PNP_XMLPROP_PATH)) != NULL)
		_parseTypeOpal(PNOPAL_XML_DEF::opalFilePath + (const char*)attr);
	}
	else if (PNP_XMLATTR_TYPEPNM == (const char *)attr)
	{
	  if ((attr = xmlGetProp(node, (const xmlChar *)PNP_XMLPROP_PATH)) != NULL)
		_parseTypePnm(PNOPAL_XML_DEF::modelFilePath + (const char*)attr);
	}
	else
	  return PNEC_FAILED_TO_PARSE;
  }

  return PNEC_SUCCESS;
}

pnint
PNOpalObject::_unserializeNode(xmlNode* node)
{
  if (PNP_XMLNODE_MODEL == (const char*)node->name)
	_parsePhysics(node);
 
  return PNEC_SUCCESS;
}

pnint
PNOpalObject::unserializeFromXML(xmlNode* root)
{
  for (root = root->children ; root != NULL; root = root->next)
  {
	 _unserializeNode(root);
  }

  return PNEC_SUCCESS;
}

std::string*
PNOpalObject::getFile()
{
  return IPNXMLSerializable::getPath();
}

//////////////////////////////////////////////////////////////////////////
};
