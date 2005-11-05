/*
* PNLuaGame.cpp
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


#include <boost/filesystem/operations.hpp>

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <tolua++.h>

#include "pndefs.h"
#include "pnerror.h"
#include "pnresources.h"
#include "pnevent.h"

#include "PNGameEventData.hpp"
#include "PNLuaGameMap.hpp"
#include "PNLuaGame.hpp"
#include "PNLuaGameUtil.h"
#include "PNConsole.hpp"
#include "pnbind.h"
#include "PNGameEventData.hpp"
#include "PN3DCamera.hpp"
#include "PNWayPoint.hpp"
#include "PNCharacter.hpp"

// debug printer
#ifdef DEBUG
# define DEBUG_PRINTER printf
#else
# define DEBUG_PRINTER //
#endif

using namespace PN;
namespace fs = boost::filesystem;
using boost::filesystem::path;

//Set the script to the RUNNING state and runthe script; 
//return true if succeed, else return false
void		PNLuaGame::manageLuaError(int errorcode)
{
	if (errorcode != 0)
		PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ERROR, NULL, NULL);
}

pnerrorcode PNLuaGame::run(void)
{
    DEBUG_PRINTER("Entering PNLuaGame::run()\n");	
    this->_LVM.registerLuaLibrary(&lua_baselibopen);
    this->_LVM.registerLuaLibrary(&lua_iolibopen);
    this->_LVM.registerLuaLibrary(&lua_strlibopen); 
    this->_LVM.registerLuaLibrary(&lua_tablibopen);
    this->_LVM.registerLuaLibrary(&lua_mathlibopen);
    this->_LVM.registerLuaLibrary(&tolua_pnbind_open);
    fs::path initScriptFile = this->_gameRootDirectory / fs::path("init.lua");
    if (!fs::exists(initScriptFile))
    {
        DEBUG_PRINTER("Leaving PNLuaGame::run() -> PNEC_FILE_NOT_FOUND\n");
        return PNEC_FILE_NOT_FOUND;
    }
    if (fs::is_directory(initScriptFile))
    {
        DEBUG_PRINTER("Leaving PNLuaGame::run() -> PNEC_NOT_A_FILE\n");
        return PNEC_NOT_A_FILE;
    }
    manageLuaError(this->_LVM.execFile(initScriptFile));

	DEBUG_PRINTER("Leaving PNLuaGame::run() -> PNEC_SUCCESS\n");
    return PNEC_SUCCESS;

}


//Set the script to the PAUSED state and pause the script
//return true if succeed, else return false
pnerrorcode PNLuaGame::pause(void)
{
    return PNEC_SUCCESS;
}

//set the script into STOPED state and jump to the 1st instruction; 
//return true if succeed, else return false
pnerrorcode PNLuaGame::stop(void) 
{
    return PNEC_SUCCESS;
}

//Return the state of the script. It could be RUNNING | PAUSED | STOPED | OVER 
void PNLuaGame::getState(void)
{
}

const pnchar* PNLuaGame::getId(void)
{
    return "pnscript";
}

//defini le repertoir principal ou se trouve le script
pnerrorcode PNLuaGame::setGameRoot(const pnchar *name)
{
    DEBUG_PRINTER("Entering PNLuaGame::setGameRoot()\n");
    this->_gameRootDirectory = this->_modsDirectory / fs::path(name);
    if (!fs::exists(this->_gameRootDirectory))
    {
        return PNEC_DIRECTORY_NOT_FOUND;
    }
    if (!fs::is_directory(this->_gameRootDirectory))
    {
        return PNEC_NOT_A_DIRECTORY;
    }
    DEBUG_PRINTER("GameRootPath : %s\n", this->_gameRootDirectory.native_file_string().c_str());
    DEBUG_PRINTER("Leaving PNLuaGame::setGameRoot()\n");
    return (PNEC_SUCCESS);
}


const fs::path& PNLuaGame::getGameRoot()
{
    return (this->_gameRootDirectory);
}


void PNLuaGame::init()
{
    DEBUG_PRINTER("Entering PNLuaGame::init()\n");
    fs::path currentDiectory = fs::current_path();
    std::cout << "currentDiectory : " <<  currentDiectory.native_file_string() <<  std::endl;
    int errorCode = PNEC_SUCCESS;

    ////////////////////////////////
    this->_modsDirectory = currentDiectory / fs::path(DEF::gamedefFilePath);
    errorCode =  this->setGameRoot(".");
#ifdef _DEBUG
    if (errorCode != PNEC_SUCCESS)
    {
        pnerror(PN_LOGLVL_ERROR, "GameRoot :\n\t%s : %s\n", this->getGameRoot().native_file_string().c_str(),
				pnGetErrorString(errorCode));
        return;
    }
#endif
    registerCallbacks();
    DEBUG_PRINTER("Leaving PNLuaGame::init()\n");
    return;
}

PNLuaGame::~PNLuaGame()
{
    delete _gameMap;
}

PNLuaGame::PNLuaGame()
{
    //   this->L = NULL;
    //    this->L = lua_open();
    this->_mapStarted = false;
    this->_mapLoaded = false;
    this->_isLoadingMap = false;
    this->_isUnloadingMap = false;

    //this->debug = false;
    this->_LVM.setDebugLogPath(DEF_LUA_LOG_FILE);
    _gameMap = NULL;
}

/* ------------------------------ load a lua script file --------------------*/


pnerrorcode PNLuaGame::loadLuaScript(const pnchar* file, bool reload/*=0*/)
{

    //si le flag de reload est pas sette et que le fichier est deja loader dans la vm 
    //on relance pas le script;
    if (reload == false && (this->_loadedScripts.find(file) != this->_loadedScripts.end()))
        return PNEC_SUCCESS;
    else 
        this->_loadedScripts.insert(file); // it could be only one instance of an item in a set
    fs::path filePath = this->getGameRoot();
    filePath /= fs::path(file, fs::native);
    if (!fs::exists(filePath))
    {
        DEBUG_PRINTER("Leaving PNLuaGame::loadLuaScript()\n");
        return PNEC_FILE_NOT_FOUND;
    }
    if (fs::is_directory(filePath))
    {
        DEBUG_PRINTER("Leaving PNLuaGame::loadLuaScript()\n");
        return PNEC_NOT_A_FILE;
    }
     manageLuaError(this->_LVM.execFile(filePath));
    return PNEC_SUCCESS;
}

PNGameMap* PNLuaGame::getGameMap()
{
    return _gameMap;
}

void  PNLuaGame::onUpdate(pnEventType evt, PNObject* source, PNEventData* data)
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
void  PNLuaGame::onInit(pnEventType evt, PNObject* source, PNEventData* data)
{
    PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT_STARTED, 0, NULL);

    std::string luaOrder;
    luaOrder +=  "gameMap.onInit()";
     manageLuaError(this->_LVM.execString(luaOrder));

    PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT_ENDED, 0, NULL);
}

void  PNLuaGame::onInitEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
    PNEventManager::getInstance()->addEvent(PN_EVENT_MP_START, 0, NULL); 
}

void  PNLuaGame::onReset(pnEventType evt, PNObject* source, PNEventData* data)
{
    std::string luaOrder;
    luaOrder +=  "gameMap.onReset()";
     manageLuaError(this->_LVM.execString(luaOrder));
}

void  PNLuaGame::onNewGame(pnEventType evt, PNObject* source, PNEventData* data)
{
}

void  PNLuaGame::onSaveGame(pnEventType evt, PNObject* source, PNEventData* data)
{
}
void  PNLuaGame::onLoadGame(pnEventType evt, PNObject* source, PNEventData* data)
{
}

void  PNLuaGame::onLoadMapStart(pnEventType evt, PNObject* source, PNEventData* data)
{
    PN3DCamera* cam = PN3DCamera::getRenderCam();
    PNGameLoadMapEventData* loadMapData = (PNGameLoadMapEventData*)data;
    this->_mapToLoad = loadMapData->mapName;
    this->_isLoadingMap = true;
    if (_mapLoaded == false) //if yhere is no map already loaded 
    {
        //boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNLuaGame::loadMap));
        this->loadMap();
    }
    else // if a map is already loaded, unload the map
    {
        PNEventManager::getInstance()->addEvent(PN_EVENT_MU_START, 0,
            NULL);
    }
}
void  PNLuaGame::onLoadMapEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
    PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT, NULL, NULL);
}

void  PNLuaGame::onUnloadMapStart(pnEventType evt, PNObject* source, PNEventData* data)
{
    this->_isUnloadingMap = true;

    if (this->_mapStarted == true)
    {
        PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_END, NULL, NULL);
    }
    else
    {
        this->unloadMap();
    }
}
void  PNLuaGame::onUnloadMapEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
    if (this->_isLoadingMap == true)
    {
        //boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNLuaGame::loadMap));
        this->loadMap();
    }
}
void  PNLuaGame::onPlayMapStart(pnEventType evt, PNObject* source, PNEventData* data)
{
    this->_mapStarted = true;

    PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_STARTED, NULL, NULL);
}
void  PNLuaGame::onPlayMapStarted(pnEventType evt, PNObject* source, PNEventData* data)
{

}
void  PNLuaGame::onPlayMapPause(pnEventType evt, PNObject* source, PNEventData* data)
{
}
void  PNLuaGame::onPlayMapPaused(pnEventType evt, PNObject* source, PNEventData* data)
{
}

void  PNLuaGame::onPlayMapEnd(pnEventType evt, PNObject* source, PNEventData* data)
{
    this->_mapStarted = false;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_ENDED, NULL, NULL);
}

void  PNLuaGame::onPlayMapEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
    if (this->_isUnloadingMap == true)
    {
        //boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNLuaGame::unloadMap));
        this->unloadMap();
    }
}

void  PNLuaGame::onLeaveGame(pnEventType evt, PNObject* source, PNEventData* data)
{
}
void  PNLuaGame::onGameAction(pnEventType evt, PNObject* source, PNEventData* data)
{
    std::stringstream luaOrder;

    PNGameActionEventData* actionEvent= (PNGameActionEventData*) data;
    luaOrder << "gameMap:on";
	luaOrder << actionEvent->action;
	luaOrder << "(\"" ;
	luaOrder << actionEvent->sourceId;
    luaOrder << "\", \"";
    luaOrder << actionEvent->targetId;
    luaOrder << "\", ";
	luaOrder << (actionEvent->value);
	luaOrder << ")";
    luaOrder << std::ends;
	 manageLuaError(this->_LVM.execString(luaOrder.str().c_str()));
}

void  PNLuaGame::onColision(pnEventType evt, PNObject* source, PNEventData* data)
{
}

void  PNLuaGame::onFrustrumIn(pnEventType evt, PNObject* source, PNEventData* data)
{
  PN3DObject*	  viewed = ((PNFrustrumEventData*)data)->obj;
  PN3DObject*	  viewer = ((PN3DCamera*)source)->getPositionTarget();
  std::string	  luaOrder;

  pnerror(PN_LOGLVL_DEBUG, "frustrum in : %s view %s", viewer->getId().c_str(), viewed->getId().c_str());

    if (viewer != NULL)
    {
        luaOrder = "gameMap:onFrustrumIn(\"";
        luaOrder += viewer->getId().c_str();
        luaOrder += "\",\"";
        luaOrder += viewed->getId().c_str();
        luaOrder += "\")";
        manageLuaError(_LVM.execString(luaOrder));
    }
}

void  PNLuaGame::onFrustrumOut(pnEventType evt, PNObject* source, PNEventData* data)
{
  PN3DObject*	  viewed = ((PNFrustrumEventData*)data)->obj;
  PN3DObject*	  viewer = ((PN3DCamera*)source)->getPositionTarget();
  std::string	  luaOrder;

    pnerror(PN_LOGLVL_DEBUG, "frustrum out : %s doesn't view %s anymore", viewer->getId().c_str(), viewed->getId().c_str());

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


void  PNLuaGame::onMouseMove(pnEventType evt, PNObject* source, PNEventData* data)
{
	PNGameMouseMoveEventData* mouseData = (PNGameMouseMoveEventData*) data;

	std::stringstream luaOrder;
	luaOrder << "gameMap:onMouseMove(" << mouseData->coords.x << " ," << mouseData->coords.y << ")" << std::endl;
     manageLuaError(this->_LVM.execString(luaOrder.str().c_str()));
}
void  PNLuaGame::registerCallbacks()
{
    PNEventManager::getInstance()->addCallback(PN_EVENT_ML_START, EventCallback(this, &PNLuaGame::onLoadMapStart));
    //PNEventManager::getInstance()->addCallback(PN_EVENT_ML_ENDED, EventCallback(this, &PNLuaGame::onLoadMapEnded));
    PNEventManager::getInstance()->addCallback(PN_EVENT_MP_START,  EventCallback(this, &PNLuaGame::onPlayMapStart));
    PNEventManager::getInstance()->addCallback(PN_EVENT_MU_START, EventCallback(this, &PNLuaGame::onUnloadMapStart));
    //PNEventManager::getInstance()->addCallback(PN_EVENT_MU_ENDED, EventCallback(this, &PNLuaGame::onUnloadMapEnded));
    PNEventManager::getInstance()->addCallback(PN_EVENT_MP_END,  EventCallback(this, &PNLuaGame::onPlayMapEnd));
    //PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED,  EventCallback(this, &PNLuaGame::onPlayMapEnded));
    PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNLuaGame::onGameAction));
    PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_UPDATE, EventCallback(this, &PNLuaGame::onUpdate));
    PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_INIT, EventCallback(this, &PNLuaGame::onInit));
    //PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_INIT_ENDED, EventCallback(this, &PNLuaGame::onInitEnded));
    PNEventManager::getInstance()->addCallback(PN_EVENT_F_IN, EventCallback(this, &PNLuaGame::onFrustrumIn));
    PNEventManager::getInstance()->addCallback(PN_EVENT_F_OUT, EventCallback(this, &PNLuaGame::onFrustrumOut));
    PNEventManager::getInstance()->addCallback(PN_EVENT_MOUSE_MOVE, EventCallback(this, &PNLuaGame::onMouseMove));
    PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNLuaGame::onGameAction));
    pnerror(PN_LOGLVL_DEBUG, "callbacks registered");
}

///////////////////////////////////////////////////////////////////////////////

//function which really load the map
void  PNLuaGame::loadMap()
{
    pnint error;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_STARTED, NULL, NULL);
    //TODO : capturer cet event pour debug
    if (this->_gameMap)
    {
        delete this->_gameMap;
        this->_gameMap = NULL;
    }

    _gameMap = new PNLuaGameMap(this->_LVM);
    run();
    loadLuaScript("gameMap.lua", true);
    
	error = _gameMap->unserializeFromFile(fs::path(_mapToLoad.c_str(), fs::native));
    _isLoadingMap = false;
    
	if (error != PNEC_SUCCESS)
    {
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MU_START, NULL, NULL);

      return;
    }
    
	_mapLoaded = true;
    
	PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_ENDED, NULL, NULL);
    //TODO : capturer cet event pout debug
    
	return;
}

void  PNLuaGame::unloadMap()
{
    PNEventManager::getInstance()->sendEvent(PN_EVENT_MU_STARTED, NULL, NULL);
    //TODO : capturer cet event pour debug
    this->_gameMap->clear();
    this->_mapLoaded = false;
    this->_isUnloadingMap = false;    
    if (this->_gameMap)
    {
        delete this->_gameMap;
        this->_gameMap = NULL;
		this->_LVM.reset();
    }
    PNEventManager::getInstance()->sendEvent(PN_EVENT_MU_ENDED, NULL, NULL);
    //TODO : capturer cet event pout debug
}

void	PNLuaGame::sendGameActionEvent(std::string eventName, PN::PNGameActionEventData *eventData)
{
  eventData->action = eventName; 
  PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, eventData);

}