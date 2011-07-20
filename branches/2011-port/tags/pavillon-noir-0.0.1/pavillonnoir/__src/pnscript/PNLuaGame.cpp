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
#include "PNConsole.hpp"
#include "pnbind.h"
#include "PNGameEventData.hpp"
#include "PN3DCamera.hpp"

// debug printer
#ifdef DEBUG
# define DEBUG_PRINTER printf
#else
# define DEBUG_PRINTER(fmt,arg)
#endif

using namespace PN;
namespace fs = boost::filesystem;
using boost::filesystem::path;

//Set the script to the RUNNING state and runthe script; 
//return true if succeed, else return false
pnerrorcode PNLuaGame::run(void)
{
    DEBUG_PRINTER("Entering PNLuaGame::run()\n");
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
    std::string tempFilePathVar =  initScriptFile.native_file_string();
    const pnchar * tempFilePathVar2 = tempFilePathVar.c_str();
    lua_dofile(this->L, tempFilePathVar2);
    DEBUG_PRINTER("Leaving PNLuaGame::run() -> PNEC_SUCCES\n");
    int i = 1;
    i++;
    return PNEC_SUCCES;

}


//Set the script to the PAUSED state and pause the script
//return true if succeed, else return false
pnerrorcode PNLuaGame::pause(void)
{
    return PNEC_SUCCES;
}

//set the script into STOPED state and jump to the 1st instruction; 
//return true if succeed, else return false
pnerrorcode PNLuaGame::stop(void) 
{
    return PNEC_SUCCES;
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
    return (PNEC_SUCCES);
}


const fs::path& PNLuaGame::getGameRoot()
{
    return (this->_gameRootDirectory);
}


void PNLuaGame::init()
{
  int ret;
    DEBUG_PRINTER("Entering PNLuaGame::init()\n");
    fs::path currentDiectory = fs::current_path();
    std::cout << "currentDiectory : " <<  currentDiectory.native_file_string() <<  std::endl;
    int errorCode = PNEC_SUCCES;  
    ret = lua_baselibopen(this->L);
    ret = lua_iolibopen(this->L);
    ret = lua_strlibopen(this->L); 
    ret = lua_tablibopen(this->L);
    ret = lua_mathlibopen(this->L);
    ret = tolua_pnbind_open (this->L);
    this->_modsDirectory = currentDiectory / fs::path(DEF::gamedefFilePath);
    errorCode =  this->setGameRoot(".");
#ifdef _DEBUG
    if (errorCode != PNEC_SUCCES)
    {
        pnerror(PN_LOGLVL_ERROR, "GameRoot :\n\t%s : %s\n", this->getGameRoot().native_file_string().c_str(), pnGetErrorString(errorCode));
        return;
    }
#endif
    registerCallbacks();
    run();
    DEBUG_PRINTER("Leaving PNLuaGame::init()\n");
    return;
}




PNLuaGame::~PNLuaGame()
{
    if (this->L != 0)
        lua_close(this->L);
    this->L = NULL;
    delete _gameMap;
}

PNLuaGame::PNLuaGame()
{
    this->L = NULL;
    this->L = lua_open();
    this->_gameStarted = false;
}

//load a lua script file 
pnerrorcode PNLuaGame::loadLuaScript(const pnchar* file, int reload/*=0*/)
{
  //DEBUG_PRINTER("Entering PNLuaGame::luoadLuaScript()\n");

  PNLuaGame* lsb = ((PNLuaGame *) PNLuaGame::getInstance());
  lua_State *localL = NULL;
  //si le flag de reload est pas sette et que le fichier est deja loader dans la vm 
  //on relance pas le script;
  if (reload == 0 && lsb->_loadedScripts.find(file) != lsb->_loadedScripts.end())
    return PNEC_SUCCES;
  else
    lsb->_loadedScripts.insert(file);
  // const pnchar* gameroot = lsb->getGameRoot();
  localL = lsb->L; 
  if (localL == NULL) 
  {
    DEBUG_PRINTER("Leaving PNLuaGame::loadLuaScript()\n");
    return PNEC_NOT_INITIALIZED;
  }
  fs::path filePath = lsb->getGameRoot();
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
  lua_dofile(localL, filePath.native_file_string().c_str());
//  DEBUG_PRINTER("Leaving PNLuaGame::luoadLuaScript()\n"); 
  return PNEC_SUCCES;
}

PNGameMap* PNLuaGame::getGameMap()
{
    return _gameMap;
}

void  PNLuaGame::onUpdate(pnuint deltaTime)
{
  if (this->_gameStarted)
  {
    std::stringstream luaOrder;
    luaOrder << "gameMap:onUpdate(" << deltaTime << ")";
    lua_dostring(L, luaOrder.str().c_str());    
  }
}
void  PNLuaGame::onInit(pnEventType evt, PNObject* source, PNEventData* data)
{
    std::string luaOrder;
    luaOrder +=  "gameMap.onInit()";
    lua_dostring(L, luaOrder.c_str());
}

void  PNLuaGame::onReset(pnEventType evt, PNObject* source, PNEventData* data)
{
    std::string luaOrder;
    luaOrder +=  "gameMap.onReset()";
    lua_dostring(L, luaOrder.c_str());
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
void  PNLuaGame::onLoadMap(pnEventType evt, PNObject* source, PNEventData* data)
{
	PN3DCamera* cam = PN3DCamera::getRenderCam();
    PNGameLoadMapEventData* loadMapData = (PNGameLoadMapEventData*)data;
    if (this->_gameStarted == false)
    {
      _gameMap = new PNLuaGameMap(this->L);
      loadLuaScript("gameMap.lua", 1);
    }
    else
    {
      _gameMap->clear();
    }
    PNConsole::writeLine("PNGame::Start of loading map -> %s", loadMapData->mapName.c_str());
    PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_STARTED, 0, data);
    _gameMap->unserialize(loadMapData->mapName.c_str());
    PNConsole::writeLine("PNGame:: End of Loading map -> %s", loadMapData->mapName.c_str());
    PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_ENDED, 0, data);
    this->_gameStarted = true;
}
void  PNLuaGame::onStartGame(pnEventType evt, PNObject* source, PNEventData* data)
{

}
void  PNLuaGame::onPauseGame(pnEventType evt, PNObject* source, PNEventData* data)
{
}
void  PNLuaGame::onLeaveGame(pnEventType evt, PNObject* source, PNEventData* data)
{
}
void  PNLuaGame::onGameAction(pnEventType evt, PNObject* source, PNEventData* data)
{
	std::string luaOrder;
	
	PNGameActionEventData* actionEvent= (PNGameActionEventData*) data;
	luaOrder = "gameMap:OnLuaAction";
	luaOrder += actionEvent->action;
	luaOrder += "(";
	luaOrder += actionEvent->targetId;
	luaOrder += ", ";
	luaOrder += actionEvent->state;
	luaOrder += ")";
	
	lua_dostring(this->L, luaOrder.c_str());

}
void  PNLuaGame::onColision(pnEventType evt, PNObject* source, PNEventData* data)
{
}

void  PNLuaGame::registerCallbacks()
{
    PNEventManager::getInstance()->addCallback(PN_EVENT_ML_START, EventCallback(this, &PNLuaGame::onLoadMap));
	PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNLuaGame::onLoadMap));
   // PNEventManager::getInstance()->addCallback(PN_EVENT_RU_STARTING, EventCallback(this, &PNLuaGame::update));
}
