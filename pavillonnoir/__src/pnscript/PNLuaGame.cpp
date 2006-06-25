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
  {
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_END, NULL, NULL);
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ERROR, NULL, NULL);
	pnerror(PN_LOGLVL_ERROR, "Game Runtime Error");
  }
}

pnerrorcode PNLuaGame::run(void)
{
  DEBUG_PRINTER("Entering PNLuaGame::run()\n");	
  _LVM.registerLuaLibrary(&lua_baselibopen);
  _LVM.registerLuaLibrary(&lua_iolibopen);
  _LVM.registerLuaLibrary(&lua_strlibopen); 
  _LVM.registerLuaLibrary(&lua_tablibopen);
  _LVM.registerLuaLibrary(&lua_mathlibopen);
  _LVM.registerLuaLibrary(&tolua_pnbind_open);

  manageLuaError(_LVM.execFile(PNResourcesManager::getInstance()->findPath(PNRT_gamedef, "init.lua")));

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
/*pnerrorcode PNLuaGame::setGameRoot(const pnchar *name)
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
}*/


/*const fs::path& PNLuaGame::getGameRoot()
{
  return (this->_gameRootDirectory);
}*/


void PNLuaGame::init()
{
  DEBUG_PRINTER("Entering PNLuaGame::init()\n");
  fs::path currentDiectory = fs::current_path();
  std::cout << "currentDiectory : " <<  currentDiectory.native_file_string() <<  std::endl;
  int errorCode = PNEC_SUCCESS;

  ////////////////////////////////
  /*this->_modsDirectory = currentDiectory / fs::path(PNResourcesManager::getInstance()->getDefault(PNRT_gamedef), fs::no_check);
  errorCode =  this->setGameRoot(".");
#ifdef _DEBUG
  if (errorCode != PNEC_SUCCESS)
  {
	pnerror(PN_LOGLVL_ERROR, "GameRoot :\n\t%s : %s\n", this->getGameRoot().native_file_string().c_str(),
	  pnGetErrorString(errorCode));
	return;
  }
#endif*/

  registerCallbacks();

  DEBUG_PRINTER("Leaving PNLuaGame::init()\n");
}

PNLuaGame::~PNLuaGame()
{
  delete _gameMap;
}

PNLuaGame::PNLuaGame()
{
  this->_mapLoaded = false;
  this->_isLoadingMap = false;
  this->_isUnloadingMap = false;

  //this->debug = false;
  _gameMap = NULL;
}

/* ------------------------------ load a lua script file --------------------*/


pnerrorcode PNLuaGame::loadLuaScript(const pnchar* file, bool reload/*=0*/)
{
  //si le flag de reload est pas sette et que le fichier est deja loader dans la vm 
  //on relance pas le script;
  if (reload == false && (_loadedScripts.find(file) != _loadedScripts.end()))
	return PNEC_SUCCESS;
  else 
	_loadedScripts.insert(file); // it could be only one instance of an item in a set
  
  manageLuaError(_LVM.execFile(PNResourcesManager::getInstance()->findPath(PNRT_gamedef, file)));

  return PNEC_SUCCESS;
}

PNGameMap* PNLuaGame::getGameMap()
{
  return _gameMap;
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
  _mapToLoad = loadMapData->mapName;
  _isLoadingMap = true;
  if (_mapLoaded == false) //if yhere is no map already loaded 
  {
	//boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNLuaGame::loadMap));
	loadMap();
  }
  else // if a map is already loaded, unload the map
  {
	PNEventManager::getInstance()->addEvent(PN_EVENT_MU_START, 0,NULL);
  }
}
void  PNLuaGame::onLoadMapEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
  PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_INIT, NULL, NULL);
}

void  PNLuaGame::onPlayMapStarted(pnEventType evt, PNObject* source, PNEventData* data)
{

}

void  PNLuaGame::onPlayMapEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
  if (this->_isUnloadingMap == true)
  {
	//boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNLuaGame::unloadMap));
	this->unloadMap();
  }
}

void  PNLuaGame::onInitEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
  PNEventManager::getInstance()->addEvent(PN_EVENT_MP_START, 0, NULL); 
}

void  PNLuaGame::onUnloadMapStart(pnEventType evt, PNObject* source, PNEventData* data)
{
  _isUnloadingMap = true;

  if (_gameMap->isStarted() == true)
  {
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_END, NULL, NULL);
  }
  else
  {
	unloadMap();
  }
}
void  PNLuaGame::onUnloadMapEnded(pnEventType evt, PNObject* source, PNEventData* data)
{
  if (_isLoadingMap == true)
  {
	//boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNLuaGame::loadMap));
	loadMap();
  }
}

void  PNLuaGame::onLeaveGame(pnEventType evt, PNObject* source, PNEventData* data)
{
}


void  PNLuaGame::registerCallbacks()
{
  PNEventManager::getInstance()->addCallback(PN_EVENT_ML_START, EventCallback(this, &PNLuaGame::onLoadMapStart));
  //PNEventManager::getInstance()->addCallback(PN_EVENT_ML_ENDED, EventCallback(this, &PNLuaGame::onLoadMapEnded));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MU_START, EventCallback(this, &PNLuaGame::onUnloadMapStart));
  //PNEventManager::getInstance()->addCallback(PN_EVENT_MU_ENDED, EventCallback(this, &PNLuaGame::onUnloadMapEnded));
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

  error = _gameMap->unserializeFromPath(_mapToLoad);
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
