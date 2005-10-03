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
#include "PNConsole.hpp"

#include "PNOpal.hpp"
#include "PNOpalObject.hpp"

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
}

/** PNOpal plugin initialization method
*/

void  PNOpal::init()
{
  pnerror(PN_LOGLVL_DEBUG, "%s", "PNOpal (PNPhysicsInterface implementation) initialization");
  PNEventManager::getInstance()->addCallback(PN_EVENT_RU_STARTING, EventCallback(this, &PNOpal::frameStarted));
  
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

void PNOpal::addForceToObj(pnuint nb, pnfloat x, pnfloat y, pnfloat z, pnfloat duration)
{
  /*PN3DObject* currentObject = NULL;
  pnuint i = 0;
  PN3DObjList::iterator it = _list3DObj.begin();
  */
  //for (;it != _list3DObj.end() && i != nb; it++, i++);
  /*
  currentObject = (*it);
  currentObject->setCoord(currentObject->getCoord().x + x, currentObject->getCoord().y + y, currentObject->getCoord().z + z);
  PNOpalObject* opalObject = (PNOpalObject*)currentObject->getPhysicalObject();
  opalObject->getOpalSolid()->setPosition(currentObject->getCoord().x + x, currentObject->getCoord().y + y, currentObject->getCoord().z + z);
  */
  //opalObject->addForce(x, y, z, duration);
}

/** Create the physical simulation (opal::Simulator)
*/

void PNOpal::createSimulation()
{
  _sim = opal::createSimulator();
  pnerror(PN_LOGLVL_DEBUG, "%s", "PNOpal::_sim created");
  _sim->setGravity(opal::Vec3r(0, (opal::real)GRAVITY, 0));
  _sim->setStepSize((opal::real)STEPSIZE);
}

/** Destroy the physical simulation (opal::Simulator)
*/

void PNOpal::destroySimulation()
{
  _sim->destroy();
}

/** Return a pointer to the OPAL simulation (opal::Simulator*)
*/

void* PNOpal::getSimulation()
{
  return _sim;
}

/** Return the elapsed time (in seconds) since the last frame
*/

pnfloat PNOpal::getElapsedTime()
{
  static pnfloat lastTicks = 0;
  pnfloat currentTicks;
  pnfloat elapsedTicks;
  
  currentTicks = (pnfloat)PNRendererInterface::getInstance()->getTicks();
  if (currentTicks < lastTicks)
  	elapsedTicks = 0;
  else
	elapsedTicks = (currentTicks - lastTicks) / 100;
  lastTicks = currentTicks;

  return elapsedTicks;
}

/** Called at the start of each frame : calculate dt since the last frame,
* update physics then update all PN3DObjects coordinates and orientations.
*/

void PNOpal::frameStarted(pnEventType type, PNObject* source, PNEventData* data)
{
  //static pnuint frame = 0;
  
  pnfloat elapsedTime = getElapsedTime();

  if (_sim == NULL)
	return;
  
  if (_paused == true)
	return;

  bool ret = _sim->simulate(elapsedTime);
  if (ret == false)
  	return;

  for (PN3DObjList::iterator it = _list3DObj.begin(); it != _list3DObj.end(); it++)
  {
  //////////////////////////////////////////////////////////////////////////
  // Will be operational when pnscript will instantiate PNGameMap

  /*
  PNGameMap* game_map = PNGameInterface::getInstance()->getGameMap();
  map<std::string, PN3DObject *>& my_list = game_map->getEntityList();
  map<std::string, PN3DObject *>::iterator it = my_list.begin();

  for (;it != my_list.end(); it++)
  {
  */
	//frame++;

	PN3DObject* current_obj = *it;

	PNLOCK_BEGIN(current_obj);
	{
	  const PNPoint& coord = current_obj->getPhysicalObject()->getCoord();
	  const PNPoint& center = current_obj->get3DModel()->getCenter();
	  const PNQuatf& orient = current_obj->getPhysicalObject()->getOrient();

	  current_obj->setCoord(coord.x - center.x, coord.y - center.y, coord.z - center.z);
	  current_obj->setOrient(orient);

	  /*if (frame == 3000)
	  {
	  PNConsole::writeLine("Orient PNPhysicalObject - x : %f, y : %f, z : %f, w : %f", orient.x, orient.y, orient.z, orient.w);
	  PNConsole::writeLine("Orient PN3DObject       - x : %f, y : %f, z : %f, w : %f", current_obj->getOrient().x, current_obj->getOrient().y, current_obj->getOrient().z, current_obj->getOrient().w);
	  frame = 0;
	  }*/
	}
	PNLOCK_END(current_obj);
  }
}

//////////////////////////////////////////////////////////////////////////

/** Create a physical object (PNPhysicalObject)
*
* \param	object		a pointer on the PN3DObject
*
* \return	a pointer on the corresponding, newly created, physical object
*/

PNPhysicalObject* PNOpal::createPhysicalObjectBox(PN3DObject* object, bool isStatic)
{
  PNPhysicalObject* physicalObject = new PNOpalObject(_sim);

  /* FIXME : previously deprecated */
  _list3DObj.push_back(object);
  
  physicalObject->setStatic(isStatic);
  physicalObject->setShape(object->get3DModel()->getMin(), object->get3DModel()->getMax(), PN_PHYS_ROCKLIGHT);

  const PNPoint&  coord = object->getCoord();
  const PNPoint&  center = object->get3DModel()->getCenter();

  physicalObject->setCoord(coord.x + center.x, coord.y + center.y, coord.z + center.z);
  physicalObject->setOrient(object->getOrient());

  return physicalObject;
}

/** Set the status of all the physical objects (static/dynamic)
*
*  \param	state			true to make them static / false to make them dynamic
*/

void PNOpal::setAllPhysicalObjectsStatic(bool state)
{
  PN3DObject* currentObject = NULL;
  /* FIXME : previously deprecated */
  PN3DObjList::iterator it = _list3DObj.begin();

  for (;it != _list3DObj.end(); it++)
  {
	currentObject = (*it);
	currentObject->getPhysicalObject()->setStatic(state);
  }
}

/** Destroy a physical object
*
*  \param	physicalObject	pointer on the physical object to destroy
*/

void PNOpal::destroyPhysicalObject(PNPhysicalObject* physicalObject)
{
  PNOpalObject* opalObject = (PNOpalObject*)physicalObject;

  _sim->destroySolid(opalObject->getOpalSolid());
}

/** Destroy all the physical objects in the simulation
*/

void PNOpal::destroyAllPhysicalObjects()
{
  PN3DObject* currentObject = NULL;
  PNOpalObject* currentOpalObject = NULL;
  /* FIXME : previously deprecated */
  PN3DObjList::iterator it = _list3DObj.begin();

  for (;it != _list3DObj.end(); it++)
  {
	currentObject = (*it);
	currentOpalObject = (PNOpalObject*)currentObject->getPhysicalObject();
	_sim->destroySolid(currentOpalObject->getOpalSolid());
  }
}

}

