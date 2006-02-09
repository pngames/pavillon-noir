/*
* PNLuaGameUtil.cpp
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

#include "pndefs.h"
#include "pnerror.h"
#include "stdio.h"
#include "pnevent.h"
#include "PNConsole.hpp"
#include "PNLuaGame.hpp"
#include "PNLuaGameUtil.h"
#include "PNGameEventData.hpp"
namespace PN{
  //load a lua script file

  void loadLuaScript(const pnchar* file, bool reload/*=0*/)
  {
    ((PNLuaGame*)PNLuaGame::getInstance())->loadLuaScript(file, reload);
  }

  pnint pnprint(const pnchar* format, int where)
  {
    // writes in the console
    if (where == 0)
      printf("[LUA] %s", format);
    // writes in the GUI console
    if (where == 1)
      PNConsole::writeLine("[LUA] %s", format);
    /// writes in the Lua debug log file
    if (where == 2)
    {
      PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
      //		  fprintf(vm->getDebugLogHandle(), "\n----\n[LUA] %s\n-----\n", format);
    }
    return 0;
  }


  PNLuaGameMap* getGameMap()
  {
    PNLuaGameMap* gm = (PNLuaGameMap*) PNLuaGame::getInstance()->getGameMap();
    return gm;
  }

  void  newGame()
  {
    PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
    //    vm->newGame();
  }

  void  continueGame()
  {
    PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
    //    vm->continueGame();
  }

  void  loadGame(std::string saveName)
  {
    PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
    //    vm->loadGame(saveName);

  }

  void  saveGame(std::string saveName)
  {
    PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
    //    vm->saveGame(saveName);
  }

  void  loadMap(std::string mapName)
  {
    PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
    //  vm->loadMap(mapName);
  }

  void	sendGameActionEvent(std::string eventName, std::string sourceid, std::string targetId, double value)
  {
    PNGameActionEventData *eventData  = new PNGameActionEventData(eventName, targetId, sourceid, value);
    PNLuaGame* game = (PNLuaGame*) PNLuaGame::getInstance();
    ((PNLuaGameMap*)game->getGameMap())->sendGameActionEvent(eventName, eventData);
    delete eventData;
  }

  void GUIChangeLife(int lifeLevel)
  {
    PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_LIFEVAL, NULL, new PNGameLifeValEventData(lifeLevel));

  }
};