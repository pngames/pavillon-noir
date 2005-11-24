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
#include "pnp_format.h"

#include "PNPhysicsInterface.hpp"
#include "PNPhysicalObject.hpp"
#include "PNConsole.hpp"

#include "PNOpal.hpp"
#include "PNOpalObject.hpp"
#include "PNOpalEvents.hpp"

#include "PNVector3f.hpp"
#include "PNMatrixTR4f.hpp"

namespace fs = boost::filesystem;

namespace PN {

/** PNOpalObject constructor
*
* \param  sim  a pointer on the opal simulation
*/ 

PNOpalObject::PNOpalObject(opal::Simulator* sim) : _blueprint(), _blueprintInstance(), _accelSensorData()
{
  _sim = sim;
}

/** PNOpalObject destructor
*/

PNOpalObject::~PNOpalObject()
{
}

//////////////////////////////////////////////////////////////////////////

void PNOpalObject::update(pnuint elapsed_time)
{
  /* deprecated */
}

/** Display the Axis Aligned Bounding Boxes of the solid (physical object)
*/

void PNOpalObject::render()
{
  /*
  pnuint numshapes;
  pnfloat aabb[6];
  pnfloat	color[4] = {0.0f, 1.0f, 0.0f, 1.0f};

  opal::SolidData solidData;
  opal::BoxShapeData* boxShapeData;
  
  solidData = _solid->getData();
  numshapes = solidData.getNumShapes();

  for (int i = 0; i < numshapes; i++)
  {
	boxShapeData = (opal::BoxShapeData*)solidData.getShapeData(i);
	boxShapeData->getLocalAABB(aabb);

	PNRendererInterface::getInstance()->renderBox(aabb[1] - aabb[0], aabb[3] - aabb[2], aabb[5] - aabb[4], color);	
  }
  */
  pnfloat color[4] = {1.0f, 1.0f, 1.0f, 0.3f};

  switch (_type)
  {
  case OPALBOX :
	PNRendererInterface::getInstance()->renderBox(_aabb[1] - _aabb[0], _aabb[3] - _aabb[2], _aabb[5] - _aabb[4], color, _offset);
	break;
  case OPALSPHERE :
	PNRendererInterface::getInstance()->renderSphere(_radius, 20, 20, color, _offset);
	break;
  default:
	break;
  }
}

//////////////////////////////////////////////////////////////////////////

/** Return the coordinates of the physical object
* 
* \return point coordinates
*/ 

const PNPoint&	PNOpalObject::getCoord()
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

const PNQuatf&	PNOpalObject::getOrient()
{
  opal::Quaternion quat = _solid->getQuaternion();

  _orient.x = quat[1];
  _orient.y = quat[2];
  _orient.z = quat[3];
  _orient.w = quat[0];
  
  return _orient;
}

/** Return the physical object's offset between its rendering center and its center of mass
*
* \return offset
*/ 

const PNPoint&	PNOpalObject::getOffset()
{
  return _offset;
}

/** Return the Opal physical object (opal::Solid)
*/ 

opal::Solid* PNOpalObject::getOpalSolid()
{
  return _solid;
}

/** Return the Opal acceleration sensor (opal::AccelerationSensor)
*/ 

opal::AccelerationSensor* PNOpalObject::getAccelSensor()
{
  return _accelSensor;
}

//////////////////////////////////////////////////////////////////////////

/** Set the state of the physical object (static/dynamic)
*
* /param  state  true to make it static / false to make it dynamic
*/ 

void			PNOpalObject::setStatic(bool state)
{
  _solid->setStatic(state);
}

/** Get the state of the physical object (static/dynamic)
*
* \return true if static, false if dynamic
*/

bool			PNOpalObject::isStatic()
{
  return _solid->isStatic();
}

/** Set the coordinates of the physical object
*
* /param  coord  point object
*/ 

void			PNOpalObject::setCoord(const PNPoint& coord)
{
  _solid->setPosition(coord.x, coord.y, coord.z);
}

/** Set the coordinates of the physical object
*
* /param  x  coordinate on the x axis
* /param  y  coordinate on the y axis
* /param  z  coordinate on the z axis
*/ 

void			PNOpalObject::setCoord(pnfloat x, pnfloat y, pnfloat z)
{
  _solid->setPosition(x, y, z);
}

/** Set the orientation of the physical object
*
* /param  orient  quaternion of orientation
*/ 

void			PNOpalObject::setOrient(const PNQuatf& orient)
{
  opal::Matrix44r transform;
  opal::Point3r pos = _solid->getPosition();

  transform.makeIdentity();
  transform.setPosition(pos[0], pos[1], pos[2]);
  if (!orient.isIdentity())
	transform.setRotation((opal::real)orient.w, (opal::real)orient.x, (opal::real)orient.y, (opal::real)orient.z);
  _solid->setTransform(transform);
}

/** Set the orientation of the physical object
*
* /param  x  orientation on the x axis
* /param  y  orientation on the y axis
* /param  z  orientation on the z axis
* /param  w  theta
*/ 

void			PNOpalObject::setOrient(pnfloat x, pnfloat y, pnfloat z, pnfloat w)
{
  opal::Matrix44r transform;
  transform.makeIdentity();
  opal::Point3r pos = _solid->getPosition();
  transform.setPosition(pos[0], pos[1], pos[2]);

  if (!(x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f))
	transform.rotate((opal::real)w, (opal::real)x, (opal::real)y, (opal::real)z);
  _solid->setTransform(transform);
}

/** Set the coordinates and orientation of the physical object
*
* /param  coord  coordinates
* /param  orient  orientation
*/ 

void			PNOpalObject::setTransform(const PNPoint& coord, const PNQuatf& orient)
{
  opal::Matrix44r transform;
  transform.makeIdentity();
  transform.setPosition((opal::real)coord.x, (opal::real)coord.y, (opal::real)coord.z);
  if (!orient.isIdentity())
	transform.setRotation((opal::real)orient.w, (opal::real)orient.x, (opal::real)orient.y, (opal::real)orient.z);
  _solid->setTransform(transform);
}

//////////////////////////////////////////////////////////////////////////

/** Add a force to the solid
*
* /param  x force axis (global x axis)
* /param  y force axis (global y axis)
* /param  z force axis (global z axis)
* /param  duration Specifies how long to apply to force. (in millisecond) 
*/

void		PNOpalObject::addForce(pnfloat x, pnfloat y, pnfloat z, pnfloat duration)
{
  _force.type = opal::LOCAL_FORCE;
  _force.vec = opal::Vec3r((opal::real)x, (opal::real)y, (opal::real)z);
  _force.duration = (opal::real)duration;
  _solid->addForce(_force);

#ifdef DEBUG
  PNConsole::writeLine("Adding force - x : %f, y : %f, z : %f, duration : %f", x, y, z, duration);
#endif
}

/** Enable the movementMotor attached to the solid
*
* /param  x desired x coordinate
* /param  y desired y coordinate
* /param  z desired z coordinate
* /param  orient desired orientation quaternion
*/

void		PNOpalObject::setMovementMotor(pnfloat x, pnfloat y, pnfloat z, PNQuatf orient)
{
  /* motor data */
  _movementMotorData.solid = _solid;
  _movementMotorData.mode = opal::LINEAR_AND_ANGULAR_MODE;

  /* coordinates */
  _movementMotorData.desiredPos = opal::Point3r((opal::real)x, (opal::real)y, (opal::real)z);

  /* orientation */
  opal::Matrix44r transform;
  transform.makeIdentity();
  if (!orient.isIdentity())
	transform.setRotation((opal::real)orient.w, (opal::real)orient.x, (opal::real)orient.y, (opal::real)orient.z);
  _movementMotorData.desiredForward = transform.getForward();
  _movementMotorData.desiredUp = transform.getUp();
  _movementMotorData.desiredRight = transform.getRight();

  /* optional motor data */
  _movementMotorData.linearKd = 2.0;
  _movementMotorData.linearKs = 20.0;
  _movementMotorData.angularKd = 0.2f;
  _movementMotorData.angularKs = 0.6f;

  /* motor init */
  _movementMotor->init(_movementMotorData);
}

/** Disable the movementMotor attached to the solid
*/

void		PNOpalObject::destroyMovementMotor()
{
  _movementMotorData.solid = NULL;
  _movementMotor->init(_movementMotorData);
}

//////////////////////////////////////////////////////////////////////////
// IPNXMLSerializable

pnint		  PNOpalObject::_parseTypePnm(const boost::filesystem::path& file)
{
  // FIXME :
  // must create a solid
  // must use the model file to create the shape
  return PNEC_SUCCESS;
}

pnint		  PNOpalObject::_parseTypeOpal(const boost::filesystem::path& file)
{

  // check for errors
  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;
  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  // create and instantiate the opal blueprint
  _file = file.string();
  opal::loadFile(_blueprint, _file);
  _sim->instantiateBlueprint(_blueprintInstance, _blueprint);

  _solid = _blueprintInstance.getSolid("Boite01");
  if (_solid != NULL)
  {
	// store the shape type
	_type = OPALBOX;

	// get the AABB dimensions
	_solid->getData().getShapeData(0)->getLocalAABB(_aabb);

	// enlarge the local AABB (make the AABB rendering a little bigger)
	for (int i = 0; i < 6; i++)
	{
	  if (_aabb[i] < 0)
		_aabb[i] -= 1.0;
	  else
		_aabb[i] += 1.0;
	}
  }
  else 
  {
	_solid = _blueprintInstance.getSolid("Sphere01");
	_type = OPALSPHERE;
	opal::SphereShapeData* shapeData = (opal::SphereShapeData*)_solid->getData().getShapeData(0);
	_radius = shapeData->radius + 1.0;
  }

  // check for loading errors
  if (!_solid)
	return PNEC_NOT_INITIALIZED;

  // set Collision handling function
  PNOpal* pnopalInstance = (PNOpal*)PNOpal::getInstance();
  _solid->setCollisionEventHandler((opal::CollisionEventHandler*)pnopalInstance->getEventHandler());

  // get the solid translation (will allow the renderer to represent the AABB at the good coords)
  opal::real* translation = _solid->getTransform().getTranslation().getData();
  _offset.set(translation[0], translation[1], translation[2]);

  // create a motor
  _movementMotor = _sim->createSpringMotor();

  // create an acceleration sensor
  _accelSensorData.solid = _solid;
  _accelSensor = _sim->createAccelerationSensor();
  _accelSensor->init(_accelSensorData);

  return PNEC_SUCCESS;
}

pnint		  PNOpalObject::_parseModel(xmlNode* node)
{
  xmlChar*	  attr = NULL;

  if ((attr = xmlGetProp(node, (const xmlChar *)PNP_XMLPROP_TYPE)) != NULL)
  {
	if (PNP_XMLATTR_TYPEOPAL == (const char*)attr)
	{
	  if ((attr = xmlGetProp(node, (const xmlChar *)PNP_XMLPROP_PATH)) != NULL)
	  {
		fs::path p(PNOPAL_XML_DEF::opalFilePath + (const char*)attr, fs::native);
		_parseTypeOpal(p);
	  }
	}
	else if (PNP_XMLATTR_TYPEPNM == (const char *)attr)
	{
	  if ((attr = xmlGetProp(node, (const xmlChar *)PNP_XMLPROP_PATH)) != NULL)
	  {
		fs::path p(PNOPAL_XML_DEF::modelFilePath + (const char*)attr, fs::native);
		_parseTypePnm(p);
	  }
	}
	else
	  return PNEC_FAILED_TO_PARSE;
  }

  return PNEC_SUCCESS;
}

pnint			PNOpalObject::_unserializeNode(xmlNode* node)
{
  if (PNP_XMLNODE_MODEL == (const char*)node->name)
	_parseModel(node);
 
  return PNEC_SUCCESS;
}

pnint			PNOpalObject::unserializeFromXML(xmlNode* root)
{
  for (root = root->children ; root != NULL; root = root->next)
  {
	 _unserializeNode(root);
  }

  return PNEC_SUCCESS;
}

}
