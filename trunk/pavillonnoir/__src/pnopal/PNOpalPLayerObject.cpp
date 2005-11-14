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

#include "PNOpalPlayerObject.hpp"

namespace PN {

/** PNOpalPlayerObject constructor
*
* \param  sim  the opal simulation
*/ 

/*
PNOpalPlayerObject::PNOpalPlayerObject(opal::Simulator* sim)
{
  _sim = sim;
  _graspingMotor = _sim->createSpringMotor();
}
*/

/** PNOpalPlayerObject destructor
*/

/*
PNOpalPlayerObject::~PNOpalPlayerObject()
{
}
*/

/** Enable the springMotor attached to the solid
*
* /param  x desired x coordinate
* /param  y desired y coordinate
* /param  z desired z coordinate
* /param  orient desired orientation quaternion
*/

void		PNOpalPlayerObject::setSpringMotor(pnfloat x, pnfloat y, pnfloat z, PNQuatf orient)
{
  /* motor data */
  //_springMotorData.solid = _solid;
  //_springMotorData.mode = opal::LINEAR_AND_ANGULAR_MODE;

  /* coordinates */
  //_springMotorData.desiredPos = opal::Point3r((opal::real)x, (opal::real)y, (opal::real)z);
  
  /* orientation */
  /*
  opal::Matrix44r transform;
  transform.makeIdentity();
  if (!orient.isIdentity())
	transform.setRotation((opal::real)orient.w, (opal::real)orient.x, (opal::real)orient.y, (opal::real)orient.z);
  _springMotorData.desiredForward = transform.getForward();
  _springMotorData.desiredUp = transform.getUp();
  _springMotorData.desiredRight = transform.getRight();
  */

  /* optional motor data */
  /*
  _springMotorData.linearKd = 2.0;
  _springMotorData.linearKs = 20.0;
  _springMotorData.angularKd = 0.2;
  _springMotorData.angularKs = 0.6;
  */

  /* motor init */
  //_graspingMotor->init(_springMotorData);
}

/** Disable the springMotor attached to the solid
*/

void		PNOpalPlayerObject::destroySpringMotor()
{
  //_springMotorData.solid = NULL;
  //_graspingMotor->init(_springMotorData);
}

}
