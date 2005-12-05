/*
 * PNOpal.cpp
 * 
 * Description :
 * PNOpal definition
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

#include "pndefs.h"
#include "pnplugins.h"
#include "pnrender.h"
#include "pnevent.h"

#include "PNRendererInterface.hpp"
#include "PNGameInterface.hpp"
#include "PNConsole.hpp"
#include "PNGameMap.hpp"
#include "PNGameEventData.hpp"
#include "PNConfPanel.hpp"

#include "PNOpal.hpp"
#include "PNOpalObject.hpp"
#include "PNOpalEvents.hpp"

#include "PN3DModel.hpp"
#include "PN3DObject.hpp"

#define PNOPAL_LABEL "physics"
#define GRAVITY -9.81
#define STEPSIZE 0.02
#define TIME_SCALE 100
#define DEFAULT_FORCE_MAGNITUDE 300000.0f
#define DEFAULT_FORCE_DURATION 0.0f

using namespace std;

namespace PN {

class PNOpalObject;

PNOpal::PNOpal()
{
  _sim = NULL;
}

PNOpal::~PNOpal()
{
  _sim->destroy();
}

/** PNOpal plugin initialization method
*/

void  PNOpal::init()
{
  pnerror(PN_LOGLVL_DEBUG, "%s", "PNOpal (PNPhysicsInterface implementation) initialization");

  PNEventManager::getInstance()->addCallback(PN_EVENT_ML_STARTED, EventCallback(this, &PNOpal::_onMapLoad));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MU_ENDED, EventCallback(this, &PNOpal::_onMapUnload));
  PNEventManager::getInstance()->addCallback(PN_EVENT_PU_START, EventCallback(this, &PNOpal::_onFrame));

  _label = PNOPAL_LABEL;
  addParam(new PNConfigurableParameter(this, PN_PARAMTYPE_BOOLEAN, &_paused, "pause", "pause"));

  setPause(true);
}

/** Play/pause the physical simulation
*
*  \param	state			true to play simulation / false set the pause on
*/

void  PNOpal::setPause(bool state)
{
  _paused = state;

  if (_paused == false)
	pn2opal();
}

/** Create the physical simulation (opal::Simulator)
*/

void PNOpal::createSimulation()
{
  _sim = opal::createSimulator();
  pnerror(PN_LOGLVL_DEBUG, "%s", "PNOpal : physical simulation created");
  _sim->setGravity(opal::Vec3r(0, (opal::real)GRAVITY, 0));
  _sim->setStepSize((opal::real)STEPSIZE);

  _eventHandler = new PNOpalCommonEventHandler();
  _break = false;

  PNConfPanel::getInstance()->addConfigurableObject(this);
}

/** Destroy the physical simulation (opal::Simulator)
*/

void PNOpal::destroySimulation()
{
  _sim->destroyAllMotors();
  _sim->destroyAllJoints();
  _sim->destroyAllSensors();
  _sim->destroyAllSolids();
  _sim->destroy();

  //if (_eventHandler =! NULL)
	//delete _eventHandler;
}

//////////////////////////////////////////////////////////////////////////

/** Simulation getter
* 
*  \return sim			the OPAL simulation instance
*/
void* PNOpal::getSimulation()
{
  return _sim;
}

/** Return a pointer to the PNOPAL event class (PNOpalCommonEventHandler*)
*
*  \return eventHandler	the PNOpalCommonEventHandler instance
*/
void* PNOpal::getEventHandler()
{
  return _eventHandler;
}

//////////////////////////////////////////////////////////////////////////

/** invoked by PN_EVENT_ML_STARTED (level loading start)
*/
void
PNOpal::_onMapLoad(pnEventType type, PNObject* source, PNEventData* data)
{
  this->createSimulation();
}

/** invoked by PN_EVENT_MU_ENDED (end of level unload)
*/
void PNOpal::_onMapUnload(pnEventType type, PNObject* source, PNEventData* data)
{
  _lastTicks = 0;
  _break = true;

  this->destroySimulation();
}

/** Called at the start of each frame : calculate dt since the last frame,
* update physics then update all PN3DObjects coordinates and orientations.
*/

void PNOpal::_onFrame(pnEventType type, PNObject* source, PNEventData* data)
{
  static int i = 0;

  pnfloat elapsedTime = ((PNGameUpdateEventData*)data)->deltaTime / TIME_SCALE;

  if (_sim == NULL)
	return;
  if (_break == true)
	return;
  if (_paused == true)
	return;
  
  i++;

  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	if (_break == true)
	  return;
	PN3DObject*	current_obj = it->second;
	if (current_obj->getPhysicalObject() != NULL)
	{
	  PNLOCK_BEGIN(current_obj);
	  {
		const PNPoint3f& coord = current_obj->getCoord();
		const PNQuatf& orient = current_obj->getOrient();
		
		if (!current_obj->getUpdateTranslation().isNull() || (orient != current_obj->getPhysicalObject()->getOrient()))
		{
		  //const PNPoint3f& offset = current_obj->getPhysicalObject()->getOffset();
		  //((PNOpalObject*)current_obj->getPhysicalObject())->setMovementMotor(coord.x + offset.x, coord.y + offset.y, coord.z + offset.z, orient);
		  ((PNOpalObject*)current_obj->getPhysicalObject())->addForce(current_obj->getUpdateTranslation(), DEFAULT_FORCE_MAGNITUDE, DEFAULT_FORCE_DURATION);
		  //PNVector3f axis(6.0f, 8.0f, 2.0f);
		  //((PNOpalObject*)current_obj->getPhysicalObject())->addTorque(axis, DEFAULT_FORCE_MAGNITUDE, DEFAULT_FORCE_DURATION);
		  //opal::Vec3r vec;
		  //vec.set(current_obj, 20.0, 0.0);
		  //((PNOpalObject*)current_obj->getPhysicalObject())->getOpalSolid()->setLocalLinearVel(vec);
		}
	  }
	  PNLOCK_END(current_obj);
	}
  }

  // run simulation
  if ((_sim->simulate(elapsedTime)) != true)
	return;

  // apply simulation into rendering
  opal2pn();
}



//////////////////////////////////////////////////////////////////////////

/** Set the status of all the physical objects (static/dynamic)
*
*  \param	state			true to make them static / false to make them dynamic
*/

void	PNOpal::setAllPhysicalObjectsStatic(bool state)
{
  PN3DObject* currentObject = NULL;

  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	if (_break == true)
	  return;

	currentObject = it->second;
	if (currentObject->getPhysicalObject())
	  currentObject->getPhysicalObject()->setStatic(state);
  }
}

//////////////////////////////////////////////////////////////////////////

/** Set opal objects coordinates and orientation from PN3DObjects's data
*/

void	PNOpal::pn2opal()
{
  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	if (_break == true)
	  return;

	pnfloat mpp = PNGameInterface::getInstance()->getGameMap()->getMpp();

	PN3DObject*	current_obj = it->second;
	if (current_obj->getPhysicalObject() != NULL)
	{
	  PNLOCK_BEGIN(current_obj);
	  {
		const PNPoint3f& coord = current_obj->getCoord();
		const PNQuatf& orient = current_obj->getOrient();
		const PNPoint3f& offset = current_obj->getPhysicalObject()->getOffset();
		current_obj->getPhysicalObject()->setCoord((coord.x + offset.x) * mpp, 
												  (coord.y + offset.y) * mpp,
												  (coord.z + offset.z) * mpp);
		current_obj->getPhysicalObject()->setOrient(orient);
	  }
	  PNLOCK_END(current_obj);
	}
  }
}

/** Set PN3DObjects coordinates and orientation from opal simulation's data
*/

void	PNOpal::opal2pn()
{
  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	if (_break == true)
	  return;

	pnfloat mpp = PNGameInterface::getInstance()->getGameMap()->getMpp();

	PN3DObject*	current_obj = it->second;
	if (current_obj->getPhysicalObject())
	{
	  PNLOCK_BEGIN(current_obj);
	  {
		const PNPoint3f& coord = current_obj->getPhysicalObject()->getCoord();
		const PNPoint3f& offset = current_obj->getPhysicalObject()->getOffset();
		const PNQuatf& orient = current_obj->getPhysicalObject()->getOrient();

		current_obj->setCoord((coord.x - offset.x) / mpp, 
							  (coord.y - offset.y) / mpp,
							  (coord.z - offset.z) / mpp);
		current_obj->setOrient(orient);
	  }
	  PNLOCK_END(current_obj);
	}
  }
}

};
