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

PNOpalObject::PNOpalObject(opal::Simulator* sim) : _blueprint(), _blueprintInstance()
{
  _sim = sim;
  //PNOpalCommonEventHandler* handler = new PNOpalCommonEventHandler();
  //_solid->setCollisionEventHandler(handler);
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
  pnfloat					  color[4] = {1.0f, 1.0f, 1.0f, 0.3f};

  opal::Point3r point = _solid->getTransform().getPosition();
  PNRendererInterface::getInstance()->renderBox(_aabb[1] - _aabb[0], _aabb[3] - _aabb[2], _aabb[5] - _aabb[4], color, _offset);	
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

/** Return a pointer on the Opal physical object (opal::Solid)
*/ 

opal::Solid* PNOpalObject::getOpalSolid()
{
  return _solid;
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
  PNMatrixTR4f	  pntransform;

  pntransform.loadIdentity();
  pntransform.setTranslation(_solid->getPosition().getData());
  pntransform.setRotationQuaternion(orient);

  opal::Matrix44r transform(pntransform.getMatrix());
  this->_solid->setTransform(transform);
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
  // FIXME

  //opal::Matrix44r transform;
  //transform.rotate((opal::real)w, (opal::real)x, (opal::real)y, (opal::real)z);
  //this->_solid->setTransform(transform);
}

//////////////////////////////////////////////////////////////////////////

void		PNOpalObject::addForce(pnfloat x, pnfloat y, pnfloat z, pnfloat duration)
{
  /*opal::Force f;
  f.type = opal::GLOBAL_FORCE;
  f.vec = opal::Vec3r(x, y, z);
  f.duration = duration;
  //PNConsole::writeLine("Adding force - x : %f, y : %f, z : %f, duration : %f", x, y, z, duration);
  _solid->addForce(f);*/
}

//////////////////////////////////////////////////////////////////////////

pnint		PNOpalObject::unserializeFromFile(const boost::filesystem::path& file)
{
  int err = PNEC_SUCCESS;

  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;

  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  _file = file.string();
  opal::loadFile(_blueprint, _file);
  _sim->instantiateBlueprint(_blueprintInstance, _blueprint);

  // FIXME : get the first shape (supposed to be Boite01)
  if (_solid = _blueprintInstance.getSolid("Boite01"))
	;
  else 
	_solid = _blueprintInstance.getSolid("Sphere01");

  if (!_solid)
	return PNEC_NOT_INITIALIZED;

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

  // get the solid translation (will allow the renderer to represent the AABB at the good coords)
  opal::real* translation = _solid->getTransform().getTranslation().getData();
  _offset.set(translation[0] * -1, translation[1] * -1, translation[2] * -1);

  return err;
}

}
