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

namespace PN {

/** PNOpalObject constructor
*
* \param  sim  a pointer on the opal simulation
*/ 

PNOpalObject::PNOpalObject(opal::Simulator* sim)
{
  _sim = sim;
  _solid = _sim->createSolid();
  PNOpalCommonEventHandler* handler = new PNOpalCommonEventHandler();
  _solid->setCollisionEventHandler(handler);
  _solid->setLinearDamping(0.2f);
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

void PNOpalObject::render()
{
  /*pnuint i = _solid->getData().getNumShapes();
  opal::BoxShapeData* sd = (opal::BoxShapeData*)_solid->getData().getShapeData(i);
  */
  
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

/** Set the dimensions of the physical object
*
* /param  min  the minimum point of the AABB (axis aligned bounding box)
* /param  max  the maximum point of the AABB (axis aligned bounding box)
*/ 

void			PNOpalObject::setShape(const PNPoint& min, const PNPoint& max, physicalmaterial material)
{
  opal::BoxShapeData boxData;
  PNVector3f dim = PNVector3f(min, max);

  // PNConsole::writeLine("Object dimensions - x : %f, y : %f, z : %f", dim.x, dim.y, dim.z);
  boxData.dimensions.set(dim.x, dim.y, dim.z);

  switch(material)
  {
  case PN_PHYS_ICE:
	boxData.material.hardness = opal::globals::iceHardness;
	boxData.material.bounciness = opal::globals::iceBounciness;
	boxData.material.friction = opal::globals::iceFriction;
	boxData.material.density = opal::globals::iceDensity;
	break;
  case PN_PHYS_METAL:
	boxData.material.hardness = opal::globals::metalHardness;
	boxData.material.bounciness = opal::globals::metalBounciness;
	boxData.material.friction = opal::globals::metalFriction;
	boxData.material.density = opal::globals::metalDensity;
	break;
  case PN_PHYS_RUBBER:
	boxData.material.hardness = opal::globals::rubberHardness;
	boxData.material.bounciness = opal::globals::rubberBounciness;
	boxData.material.friction = opal::globals::rubberFriction;
	boxData.material.density = opal::globals::rubberDensity;
	break;
  case PN_PHYS_WOOD:
	boxData.material.hardness = opal::globals::woodHardness;
	boxData.material.bounciness = opal::globals::woodBounciness;
	boxData.material.friction = opal::globals::woodFriction;
	boxData.material.density = opal::globals::woodDensity;
	break;
  case PN_PHYS_ROCKLIGHT:
	boxData.material.hardness = (opal::real)1.0;
	boxData.material.bounciness = (opal::real)0.1;
	boxData.material.friction = (opal::real)1.0;
	boxData.material.density = (opal::real)0.5;
	break;
  default:
	boxData.material.hardness = opal::globals::woodHardness;
	boxData.material.bounciness = opal::globals::woodBounciness;
	boxData.material.friction = opal::globals::woodFriction;
	boxData.material.density = opal::globals::woodDensity;
	break;
  }

  _solid->addShape(boxData);
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

pnint		PNOpalObject::unserializeFromXML(xmlNode* node)
{
  /*
  opal::Simulator* sim = opal::createSimulator();
  opal::Blueprint sailboatBP;

  // Load the Blueprint from a file.
  opal::loadFile(sailboatBP, �sailboat.xml�);
  
  // Instantiate the Blueprint.
  opal::BlueprintInstance instance;
  sim->instantiateBlueprint(instance, sailboatBP);
  */

  return PNEC_SUCCES;
}

}
