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

#include "PNOpal.hpp"
#include "PNOpalObject.hpp"
#include "PNOpalEvents.hpp"

#include "PN3DModel.hpp"
#include "PN3DObject.hpp"

#define GRAVITY -9.81
#define STEPSIZE 0.02

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

  PNEventManager::getInstance()->addCallback(PN_EVENT_PU_START, EventCallback(this, &PNOpal::frameStarted));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PNOpal::mapEnded));
  
  setPause(true);
}

/** Play/pause the physical simulation
*
*  \param	state			true to play simulation / false set the pause on
*/

void  PNOpal::setPause(bool state)
{
  _paused = state;
}

/** Create the physical simulation (opal::Simulator)
*/

void PNOpal::createSimulation()
{
  _sim = opal::createSimulator();
  pnerror(PN_LOGLVL_DEBUG, "%s", "PNOpal::_sim created");
  _sim->setGravity(opal::Vec3r(0, (opal::real)GRAVITY, 0));
  _sim->setStepSize((opal::real)STEPSIZE);

  _eventHandler = new PNOpalCommonEventHandler();
  _break = false;
}

/** Destroy the physical simulation (opal::Simulator)
*/

void PNOpal::destroySimulation()
{
  _sim->destroyAllSolids();
  // if (_eventHandler)
  // delete _eventHandler; // unexpected read/write error !
  // _sim->destroy(); // unexpected read/write error !

}

/** Return a pointer to the OPAL simulation (opal::Simulator*)
*/

void* PNOpal::getSimulation()
{
  return _sim;
}

/** Return a pointer to the PNOPAL event class (PNOpalCommonEventHandler*)
*/

void* PNOpal::getEventHandler()
{
  return _eventHandler;
}

/** invoked by PN_EVENT_MP_ENDED (level destruction)
*/

void PNOpal::mapEnded(pnEventType type, PNObject* source, PNEventData* data)
{
  _lastTicks = 0;
  _break = true; // make the running loops stop
  this->destroySimulation();
}

/** Called at the start of each frame : calculate dt since the last frame,
* update physics then update all PN3DObjects coordinates and orientations.
*/

void PNOpal::frameStarted(pnEventType type, PNObject* source, PNEventData* data)
{
  static int i = 0;

  pnfloat elapsedTime = ((PNGameUpdateEventData*)data)->deltaTime / 100;

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
	if (current_obj->getPhysicalObject())
	{
	  PNLOCK_BEGIN(current_obj);
	  {
		const PNPoint& coord = current_obj->getCoord();
		const PNPoint& offset = current_obj->getPhysicalObject()->getOffset();
		const PNQuatf& orient = current_obj->getOrient();

		current_obj->getPhysicalObject()->setCoord(coord.x + offset.x, coord.y + offset.y, coord.z + offset.z);
		current_obj->getPhysicalObject()->setOrient(orient);
		if (i == 400  && orient.x != 0)
		  pnerror(PN_LOGLVL_DEBUG, "in-orient : %i, %i, %i, %i", orient.x, orient.y, orient.z, orient.w);
	  }
	  PNLOCK_END(current_obj);
	}
  }

  // run simulation
  bool ret = _sim->simulate(elapsedTime);
  if (ret == false)
  	return;

  // apply simulation
  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	if (_break == true)
	  return;
	PN3DObject*	current_obj = it->second;
	if (current_obj->getPhysicalObject())
	{
	  PNLOCK_BEGIN(current_obj);
	  {
		const PNPoint& coord = current_obj->getPhysicalObject()->getCoord();
		const PNPoint& offset = current_obj->getPhysicalObject()->getOffset();
		const PNQuatf& orient = current_obj->getPhysicalObject()->getOrient();

		current_obj->setCoord(coord.x, coord.y, coord.z);
		current_obj->setCoord(coord.x - offset.x, coord.y - offset.y, coord.z - offset.z);
		current_obj->setOrient(orient);
		if (i == 400 && orient.x != 0)
		  pnerror(PN_LOGLVL_DEBUG, "out-orient : %i, %i, %i, %i", orient.x, orient.y, orient.z, orient.w);
	  }
	  PNLOCK_END(current_obj);
	}
  }

  if (i == 400)
	i = 0;

}

//////////////////////////////////////////////////////////////////////////

/** Set the status of all the physical objects (static/dynamic)
*
*  \param	state			true to make them static / false to make them dynamic
*/

void PNOpal::setAllPhysicalObjectsStatic(bool state)
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


}