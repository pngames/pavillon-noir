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

#include "PN3DObject.hpp"
#include "PNMatrixTR4f.hpp"

#define PNOPAL_LABEL "physics"
#define STEPSIZE 0.02
#define GRAVITY -9.81
#define TIME_SCALE 1000
#define DEFAULT_FORCE_MAGNITUDE 10.0f
#define DEFAULT_FORCE_DURATION 0.0f
#define DEFAULT_TORQUE_MAGNITUDE 6.0f
#define DEFAULT_ANTIGRAVITY 500.0f
#define DEFAULT_ANTIGRAVITY_CONSTANT 0.5f

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
  PNEventManager::getInstance()->addCallback(PN_EVENT_ML_ENDED, EventCallback(this, &PNOpal::_onMapLoaded));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MU_ENDED, EventCallback(this, &PNOpal::_onMapUnload));
  PNEventManager::getInstance()->addCallback(PN_EVENT_PU_START, EventCallback(this, &PNOpal::_onFrame));

  _label = PNOPAL_LABEL;
  addParam(new PNConfigurableParameter(this, PN_PARAMTYPE_BOOLEAN, &_paused, "pause", "pause"));

  //setPause(false);
}

/** Play/pause the physical simulation
*
*  \param	state			true to play simulation / false set the pause on
*/
void  PNOpal::setPause(bool state)
{
  _paused = state;
  if (state == false)
	pn2opal();
}

/** Create the physical simulation (opal::Simulator)
*/
void PNOpal::createSimulation()
{
  _sim = opal::createSimulator();
  _sim->setGravity(opal::Vec3r(0, (opal::real)GRAVITY, 0));
  _sim->setStepSize((opal::real)STEPSIZE);
  pnerror(PN_LOGLVL_DEBUG, "%s", "PNOpal : physical simulation created");

  _eventHandler = new PNOpalCommonEventHandler();
  _break = false;

  setPause(true);

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
  createSimulation();
}

/** invoked by PN_EVENT_ML_ENDED (level loading end)
*/
void
PNOpal::_onMapLoaded(pnEventType type, PNObject* source, PNEventData* data)
{
  pn2opal();
}

/** invoked by PN_EVENT_MU_ENDED (end of level unload)
*/
void PNOpal::_onMapUnload(pnEventType type, PNObject* source, PNEventData* data)
{
  _lastTicks = 0;
  _break = true;

  destroySimulation();
}

//////////////////////////////////////////////////////////////////////////

void PNOpal::preComputeCharactersForces(PN3DObject* pnObject, PNOpalObject* physicalObject)
{
  pnfloat			mpp = PNGameInterface::getInstance()->getGameMap()->getMpp();
  const PNPoint3f&	coord = pnObject->getCoord();
  const PNQuatf&	orient = pnObject->getOrient();
  pnbool			mustMove = true;

  // avoid translation inertia (except gravity)
  opal::Vec3r gravity = physicalObject->getOpalSolid()->getGlobalLinearVel();
  physicalObject->getOpalSolid()->setGlobalLinearVel(opal::Vec3r(0, gravity.getData()[1], 0));
  // avoid rotation inertia
  physicalObject->getOpalSolid()->setGlobalAngularVel(opal::Vec3r(0, 0, 0));

  if (physicalObject->isNPC())
  {
	opal::RaycastResult result = physicalObject->getPlayerSensor()->fireRay(physicalObject->getRayLenght());
	// avoid air control
	if (result.distance == 0.0f)
	  mustMove = false;
  }

  if (mustMove == true)
  {
	//////////////////////////////////////////////////////////////////////////
	// translation

	if (!pnObject->getUpdateTranslation().isNull())
	{
	  const PNVector3f& dir = pnObject->getUpdateTranslation();

	  //////////////////////////////////////////////////////////////////////////
	  // obstacle detectors

	  if (physicalObject->isNPC())
	  {
		PNVector3f		  dirTmp = orient.getInvert() * dir;
		dirTmp.y = 0;
		opal::Point3r	  ori;
		opal::Vec3r		  vecDir;
		PNNormal3f		  dirNorm(dirTmp);
		vecDir.set(dirNorm.getX(), dirNorm.getY(), dirNorm.getZ());

		ori.set(0, -physicalObject->getRayLenght()*0.49f, 0);
		opal::Rayr obstacle1(ori, vecDir);
		ori.set(0, -physicalObject->getRayLenght()/6.0f, 0);
		opal::Rayr obstacle2(ori, vecDir);

		// fire'em
		physicalObject->getPlayerSensor()->setRay(obstacle1);
		opal::RaycastResult resultObstacle1 = physicalObject->getPlayerSensor()->fireRay(physicalObject->getRayLenght());
		physicalObject->getPlayerSensor()->setRay(obstacle2);
		opal::RaycastResult resultObstacle2 = physicalObject->getPlayerSensor()->fireRay(physicalObject->getRayLenght());

		// reinit RaySensor (which is also used to detect ground)
		/*ori.set(0, 0, 0);
		vecDir.set(0, -1, 0);
		opal::Rayr ground(ori, vecDir);
		physicalObject->getPlayerSensor()->setRay(ground);*/

		// apply obstacle workaround force
		if (resultObstacle1.distance > 0.0f && resultObstacle1.distance < physicalObject->getRadius() * 1.2f)
		  if (resultObstacle2.distance == 0.0f || resultObstacle2.distance > resultObstacle1.distance * 1.5f)
		  {
			physicalObject->addForce(PNVector3f::UNIT_Y, (physicalObject->getRayLenght()/mpp)/3.0f, 0.0f, true);
			//pnerror(PN_LOGLVL_INFO, "Obstacle sensor 1, height: %f, distance : %f, point : %f:%f:%f", -physicalObject->getRayLenght()*0.49, resultObstacle1.distance, 
			//resultObstacle1.intersection[0], resultObstacle1.intersection[1], resultObstacle1.intersection[2]);
			//pnerror(PN_LOGLVL_INFO, "Obstacle sensor 2, height: %f, distance : %f, point : %f:%f:%f", -physicalObject->getRayLenght()/3, resultObstacle2.distance, 
			  //resultObstacle2.intersection[0], resultObstacle2.intersection[1], resultObstacle2.intersection[2]);
			  //pnerror(PN_LOGLVL_INFO, "Obstacle workaround force added : %f - %f, %f, %f", (physicalObject->getRayLenght()/mpp)/3.0f, dirNorm.getX(), dirNorm.getY(), dirNorm.getZ());
		  }
	  }

	  //////////////////////////////////////////////////////////////////////////
	  // apply translation
	  physicalObject->addForce(pnObject->getUpdateTranslation(), DEFAULT_FORCE_MAGNITUDE, DEFAULT_FORCE_DURATION, false);
	}

  }

  //////////////////////////////////////////////////////////////////////////
  // rotation

  if (physicalObject->isNPC())
  {
	if (orient != pnObject->getPhysicalObject()->getOrient())
	{
	  PNNormal3f	vecOri = physicalObject->getOrient() * PNVector3f::NEGATIVE_UNIT_Z;
	  PNNormal3f	vecEnd = orient * PNVector3f::NEGATIVE_UNIT_Z;
	  pnfloat		angleOri = vecOri.radianRange2Pi(PNVector3f::UNIT_X, PNVector3f::NEGATIVE_UNIT_Z);
	  pnfloat		angleEnd = vecEnd.radianRange2Pi(PNVector3f::UNIT_X, PNVector3f::NEGATIVE_UNIT_Z);
	  pnfloat		angle = angleOri - angleEnd;

	  if (angle > PI)
		angle -= (pnfloat)PI * 2.0f;
	  else if (angle < -PI)
		angle += (pnfloat)PI * 2.0f;

	  physicalObject->addTorque(PNVector3f::UNIT_Y, -angle * DEFAULT_TORQUE_MAGNITUDE, 0.0f, true);
	}
  }
}

/** Called at the start of each frame : calculate dt since the last frame,
* update physics then update all PN3DObjects coordinates and orientations.
*/
void PNOpal::_onFrame(pnEventType type, PNObject* source, PNEventData* data)
{
  pnfloat elapsedTime = ((PNGameUpdateEventData*)data)->deltaTime / TIME_SCALE;
  static PNMatrix4f	playertranslation;

  if (_sim == NULL)
	return;
  if (_break == true)
	return;
  if (_paused == true)
	return;

  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	if (_break == true)
	  return;
	PN3DObject*	current_obj = it->second;
	PNOpalObject* physicalObject = (PNOpalObject*)current_obj->getPhysicalObject();
	if (physicalObject != NULL)
	{
	  PNLOCK_BEGIN(current_obj);
	  {
		if (physicalObject->isPlayer() || physicalObject->isNPC())
		  preComputeCharactersForces(current_obj, physicalObject);
	  }
	  PNLOCK_END(current_obj);
	}
  }

  //run simulation
  if ((_sim->simulate(elapsedTime)) != true)
	return;

  // apply simulation into rendering
  opal2pn();

  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	PN3DObject* object = it->second;

	PNLOCK_BEGIN(object);
	if (object->getPhysicalObject() == NULL && (object->getPositionTarget() != NULL || object->getViewTarget() != NULL))
	{
	  object->prepareUpdate();
	  object->update((pnuint)((PNGameUpdateEventData*)data)->deltaTime);
	}
	PNLOCK_END(object);
  }
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
		current_obj->getPhysicalObject()->setTransform(coord, orient, mpp);
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
	PN3DObject* object = it->second;
	PNOpalObject* physicalObject = (PNOpalObject*)object->getPhysicalObject();
	if (physicalObject != NULL)
	{
	  PNLOCK_BEGIN(object);
	  {
		const PNPoint3f& coord = physicalObject->getCoord();
		const PNPoint3f& offset = physicalObject->getOffset();
		const PNQuatf& orient = physicalObject->getOrient();

		//////////////////////////////////////////////////////////////////////////
		// Player objects

		//doesn't seems to work well for me, even if it is a method used by others with ODE
		if (physicalObject->isPlayer())
		  physicalObject->resetAngularRotation();

		// avoid translation inertia (except gravity)
		opal::Vec3r gravity = physicalObject->getOpalSolid()->getGlobalLinearVel();
		physicalObject->getOpalSolid()->setGlobalLinearVel(opal::Vec3r(0, gravity.getData()[1], 0));

		//////////////////////////////////////////////////////////////////////////
		// elevates PNPlayer' from the ground (a little bit)

		/*opal::RaycastResult result = physicalObject->getPlayerSensor()->fireRay(physicalObject->getRayLenght());
		opal::Point3r hitPoint = result.intersection;
		opal::Solid* hitSolid = result.solid;

		if (result.distance != 0.0 && result.distance < physicalObject->getDesiredHeight() + DEFAULT_ANTIGRAVITY_CONSTANT)
		{
		physicalObject->addForce(PNVector3f::UNIT_Y, (physicalObject->getDesiredHeight() - (pnfloat)result.distance) * DEFAULT_ANTIGRAVITY, 0.0f, true);
		pnerror(PN_LOGLVL_INFO, "Player sensor, Y: %f", result.distance);
		}*/

		//////////////////////////////////////////////////////////////////////////
		// avoid falls of PNPlayers (the "culbuto" effect)

		/*PNVector3f	vecCurrent = orient * PNVector3f::UNIT_Y;
		if (vecCurrent.y < 1.0f && vecCurrent.y > 0.8f)
		{
		PNVector3f	oriY(vecCurrent.x, 1.0f, vecCurrent.z);
		PNVector3f	vecAxis;
		pnfloat		correctiveForce = (1.0f - vecCurrent.y) * 100000.0f;

		if (correctiveForce > 10000.0f * physicalObject->getOpalSolid()->getMass())
		correctiveForce = 10000.0f * physicalObject->getOpalSolid()->getMass();

		vecAxis.crossProduct(oriY, vecCurrent);
		physicalObject->addTorque(vecAxis, correctiveForce, 0.0f, true);
		pnerror(PN_LOGLVL_INFO, "Player anti-fall force : %f - %f:%f:%f", correctiveForce, vecCurrent.x, vecCurrent.y, vecCurrent.z);
		}*/

		//////////////////////////////////////////////////////////////////////////
		// set obj's rendering matrix according to physics 
		// (considering map's scale [meters per pixel])

		object->setCoord((coord.x - offset.x) / mpp,
		  (coord.y - offset.y) / mpp,
		  (coord.z - offset.z) / mpp);
		if (!physicalObject->isPlayer())
		  object->setOrient(orient);
	  }
	  PNLOCK_END(object);
	}
  }
}

};
