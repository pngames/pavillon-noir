/*
* PNLuaGameMap.cpp
* 
* Description :
* 
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

#include <boost/filesystem/path.hpp>

extern "C"
{
#include <lua.h>
#include <lualib.h>
}
#include "tolua++.h"
#include <string>
#include <sstream>
#include <map>
#include "pndefs.h"
#include "PNObject.hpp"
#include "PN3DObject.hpp"
#include "PN3DCamera.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PNLuaGameMap.hpp"
#include "PNLuaGameUtil.h"
#include "PNLuaGame.hpp"
#include "PNRendererInterface.hpp"
using namespace PN; 


PNLuaGameMap::PNLuaGameMap(PNLuaVm &lvm): _LVM(lvm)
{
  this->_mapStarted = false; 
  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_START,  EventCallback(this, &PNLuaGameMap::onPlayMapStart));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_END,  EventCallback(this, &PNLuaGameMap::onPlayMapEnd));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_INIT, EventCallback(this, &PNLuaGameMap::onInit));
  return;
}

PNLuaGameMap::~PNLuaGameMap(void)
{
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MP_START,  EventCallback(this, &PNLuaGameMap::onPlayMapStart));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MP_END,  EventCallback(this, &PNLuaGameMap::onPlayMapEnd));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_INIT, EventCallback(this, &PNLuaGameMap::onInit));
}


void  PNLuaGameMap::addToMap(const std::string& entityName, const std::string& id)
{
    _playerId.clear();
  std::string luaOrder = "";
  if (entityName.length() == 0)
	luaOrder +=  "entity = PN3DObjectClass(\"" + id + "\")\n gameMap:spawn2(entity, \"" + id + "\")\n";
  else
  {
    if (entityName == "PNPlayer")
        _playerId = id;

	loadLuaScript(std::string(entityName).append(".lua").c_str());
	luaOrder +=  "entity = " + entityName + "Class(\"" + id + "\")\n gameMap:spawn2(entity, \"" + id + "\")\n";
  }
  pnerror(PN_LOGLVL_DEBUG, "%s -> Lua", luaOrder.c_str());
  int err  = this->_LVM.execString(luaOrder);
  return;
}


void        PNLuaGameMap::addToMap2(PNObject& entity, char* id)
{
  //puts("[LUA Teste] addToMap2");
  if (!_playerId.empty())
  {
    _player = (PN3DObject*)&entity;
    _playerId.clear();
  }

 // if (((PN3DObject&)entity).getObjType() == PN_GROUND)
 //   ;
 //   _ground = (PN3DObject*)&entity;
  this->_entityList[id] = (PN3DObject*)&entity;
}


void        PNLuaGameMap::clear()
{
  std::string luaOrder;
  luaOrder += "gameMap:clear()";
  int err = this->_LVM.execString(luaOrder);
  PNGameMap::clear();
  return;
}


//execute mapScript
void PNLuaGameMap::executeScript(const std::string& ScriptName)
{
  ((PNLuaGame*)PNLuaGame::getInstance())->loadLuaScript(ScriptName.c_str());
}

//Set the script to the RUNNING state and runthe script; 
//return true if succeed, else return false
void		PNLuaGameMap::manageLuaError(int errorcode)
{
  if (errorcode != 0)
  {
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_END, NULL, NULL);
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ERROR, NULL, NULL);
	pnerror(PN_LOGLVL_ERROR, "Game Runtime Error");
  }
}

void  PNLuaGameMap::onUpdate(pnEventType evt, PNObject* source, PNEventData* data)
{
  PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_UPDATE_STARTED, 0, NULL);

  float deltaTime = ((PNGameUpdateEventData*)data)->deltaTime;

  if (this->_mapStarted == true)
  {
	std::stringstream luaOrder;
	luaOrder << "gameMap:onUpdate(" << deltaTime << ")";
	manageLuaError(this->_LVM.execString(luaOrder.str()));
  }

  PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_UPDATE_ENDED, 0, NULL);
}
void  PNLuaGameMap::onInit(pnEventType evt, PNObject* source, PNEventData* data)
{
  PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT_STARTED, this, NULL);

  std::string luaOrder;
  luaOrder +=  "gameMap:onInit()";
  manageLuaError(this->_LVM.execString(luaOrder));

  PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT_ENDED, this, NULL);
}



void  PNLuaGameMap::onReset(pnEventType evt, PNObject* source, PNEventData* data)
{
  std::string luaOrder;
  luaOrder +=  "gameMap.onReset()";
  manageLuaError(this->_LVM.execString(luaOrder));
}


void  PNLuaGameMap::onPlayMapStart(pnEventType evt, PNObject* source, PNEventData* data)
{
  this->_mapStarted = true;
  registerInGameCallbacks();
  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_STARTED, this, NULL);
}

void  PNLuaGameMap::onPlayMapPause(pnEventType evt, PNObject* source, PNEventData* data)
{
  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_PAUSED, NULL, NULL);
}

void  PNLuaGameMap::onPlayMapEnd(pnEventType evt, PNObject* source, PNEventData* data)
{
  this->_mapStarted = false;
  unregisterInGameCallbacks();
  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_ENDED, NULL, NULL);
}



void  PNLuaGameMap::onGameAction(pnEventType evt, PNObject* source, PNEventData* data)
{
  std::stringstream luaOrder;

  PNGameActionEventData* actionEvent= (PNGameActionEventData*) data;

  luaOrder << "if (gameMap.on";
  luaOrder << actionEvent->action;
   luaOrder << " ~= nil) then\n";
  luaOrder << "gameMap:on";
  luaOrder << actionEvent->action;
  luaOrder << "(\"" ;
  luaOrder << actionEvent->sourceId;
  luaOrder << "\", \"";
  luaOrder << actionEvent->targetId;
  luaOrder << "\", ";
  luaOrder << (actionEvent->value);
  luaOrder << ")\n end";/* else print(\"[LUA] ";
  luaOrder << "gameMap:on";
  luaOrder << actionEvent->action;
  luaOrder << " is not binded\")\n end";*/
  luaOrder << std::ends;
  manageLuaError(this->_LVM.execString(luaOrder.str().c_str()));
}

void  PNLuaGameMap::onColision(pnEventType evt, PNObject* source, PNEventData* data)
{
}

void  PNLuaGameMap::onFrustrumIn(pnEventType evt, PNObject* source, PNEventData* data)
{
  PN3DObject*	  viewed = ((PNFrustrumEventData*)data)->obj;
  PN3DCamera*	  viewerCamera = (PN3DCamera*)source;
  PN3DObject*	  viewer = viewerCamera->getPositionTarget();
  std::string	  luaOrder;

  if (viewer != NULL)
  {
	//pnerror(PN_LOGLVL_DEBUG, "frustrum in : %s views %s", viewer->getId().c_str(), viewed->getId().c_str());
	luaOrder = "gameMap:onFrustrumIn(\"";
	luaOrder += viewer->getId().c_str();
	luaOrder += "\",\"";
	luaOrder += viewed->getId().c_str();
	luaOrder += "\")";
	manageLuaError(_LVM.execString(luaOrder));
  }
}

void  PNLuaGameMap::onFrustrumOut(pnEventType evt, PNObject* source, PNEventData* data)
{
  PN3DObject*	  viewed = ((PNFrustrumEventData*)data)->obj;
  PN3DCamera*	  viewerCamera = (PN3DCamera*)source;
  PN3DObject*	  viewer = viewerCamera->getPositionTarget();
  std::string	  luaOrder;

  //pnerror(PN_LOGLVL_DEBUG, "frustrum out : %s doesn't view %s anymore", viewerCamera->getId().c_str(), viewed->getId().c_str());

  if (viewer != NULL)
  {
	luaOrder = "gameMap:onFrustrumOut(\"";
	luaOrder += viewer->getId().c_str();
	luaOrder += "\",\"";
	luaOrder += viewed->getId().c_str();
	luaOrder += "\")";
	manageLuaError(_LVM.execString(luaOrder));
  }
}

void  PNLuaGameMap::onAnimEnd(pnEventType evt, PNObject* source, PNEventData* data)
{
  PNObjectAnimationEventData* animData = (PNObjectAnimationEventData*)data;
  PN3DSkeletonObject*		  obj = (PN3DSkeletonObject*)source;
  std::ostringstream 		  luaOrder;

  luaOrder << "gameMap.entities.all[\"";
  luaOrder << obj->getId();
  luaOrder << "\"]:checkAnimEnd(";
  luaOrder << animData->playId;
  luaOrder << ")";
  pnerror(PN_LOGLVL_DEBUG, "%s", luaOrder.str().c_str());
  manageLuaError(_LVM.execString(luaOrder.str()));
}

void  PNLuaGameMap::onMouseMove(pnEventType evt, PNObject* source, PNEventData* data)
{
  PNGameMouseMoveEventData* mouseData = (PNGameMouseMoveEventData*) data;

  std::stringstream luaOrder;
  luaOrder << "gameMap:onMouseMove(" << mouseData->coords.x << " ," << mouseData->coords.y << ")" << std::endl;
  manageLuaError(this->_LVM.execString(luaOrder.str().c_str()));
}

void  PNLuaGameMap::onDeath(pnEventType evt, PNObject* source, PNEventData* data)
{
  std::ostringstream 		  luaOrder;

  luaOrder << "gameMap:onDeath(\"";
  luaOrder << ((PN3DObject*)source)->getId();
  luaOrder << "\")";
  pnerror(PN_LOGLVL_DEBUG, "%s", luaOrder.str().c_str());
  manageLuaError(_LVM.execString(luaOrder.str()));
  //delete the object from the rendered objects list
  //PNRendererInterface::getInstance()->deleteObj(source);
  //delete source;
}

void  PNLuaGameMap::sendGameActionEvent(std::string eventName, PN::PNGameActionEventData *eventData)
{
  eventData->action = eventName; 
  PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, eventData);
}

void  PNLuaGameMap::registerInGameCallbacks()
{
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNLuaGameMap::onGameAction));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_UPDATE, EventCallback(this, &PNLuaGameMap::onUpdate));
  PNEventManager::getInstance()->addCallback(PN_EVENT_F_IN, EventCallback(this, &PNLuaGameMap::onFrustrumIn));
  PNEventManager::getInstance()->addCallback(PN_EVENT_F_OUT, EventCallback(this, &PNLuaGameMap::onFrustrumOut));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MOUSE_MOVE, EventCallback(this, &PNLuaGameMap::onMouseMove));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNLuaGameMap::onGameAction)); 
  PNEventManager::getInstance()->addCallback(PN_EVENT_COLLISION, EventCallback(this, &PNLuaGameMap::onColision));
  PNEventManager::getInstance()->addCallback(PN_EVENT_OA_ENDED, EventCallback(this, &PNLuaGameMap::onAnimEnd));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_DEATH, EventCallback(this, &PNLuaGameMap::onDeath));
  pnerror(PN_LOGLVL_DEBUG, "in game callbacks registered");
}

void  PNLuaGameMap::unregisterInGameCallbacks()
{
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNLuaGameMap::onGameAction));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_UPDATE, EventCallback(this, &PNLuaGameMap::onUpdate));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_F_IN, EventCallback(this, &PNLuaGameMap::onFrustrumIn));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_F_OUT, EventCallback(this, &PNLuaGameMap::onFrustrumOut));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MOUSE_MOVE, EventCallback(this, &PNLuaGameMap::onMouseMove));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNLuaGameMap::onGameAction)); 
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_COLLISION, EventCallback(this, &PNLuaGameMap::onColision));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_OA_ENDED, EventCallback(this, &PNLuaGameMap::onAnimEnd));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_DEATH, EventCallback(this, &PNLuaGameMap::onDeath));
  pnerror(PN_LOGLVL_DEBUG, "in game callbacks unregistered");
}

void  PNLuaGameMap::sendEventFromLua(PNObject* source, pnint eventId)
{
  PNEventManager::getInstance()->addEvent((pnEventType)eventId, source, NULL);
}

