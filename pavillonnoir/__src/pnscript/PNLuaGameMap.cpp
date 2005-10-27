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
#include <map>
#include "pndefs.h"
#include "PNObject.hpp"
#include "PNLuaGameMap.hpp"
#include "PNLuaGameUtil.h"
#include "PNLuaGame.hpp"
using namespace PN; 


PNLuaGameMap::PNLuaGameMap(PNLuaVm &lvm): _LVM(lvm)
{
    //this->_LVM = lvm;
    return;
}



PNLuaGameMap::~PNLuaGameMap(void)
{
}

//void  PNLuaGameMap::loadScript(const std::string& file, const std::string& id, const std::string& events)
//{
//	t_scripts_infos *new_elem = new t_scripts_infos();
//
//	new_elem->events = events;
//	new_elem->file = file;
//
//	_entitiesActions[id] = new_elem;
//}

//void  PNLuaGameMap::unloadScript(const std::string& file, const std::string& id, const std::string& events)
//{
//	
//}

void  PNLuaGameMap::addToMap(const std::string& entityName, const std::string& id)
{
  std::string luaOrder = "";
  if (entityName.length() == 0)
	  luaOrder +=  "entity = PN3DObjectClass(\"" + id + "\")\n gameMap:spawn2(entity, \"" + id + "\")\n";
  else
  {
    loadLuaScript(std::string(entityName).append(".lua").c_str());
		luaOrder +=  "entity = " + entityName + "Class(\"" + id + "\")\n gameMap:spawn2(entity, \"" + id + "\")\n";
  }
  pnerror(PN_LOGLVL_DEBUG, "%s -> Lua", luaOrder.c_str());
  int err  = this->_LVM.execString(luaOrder);
  return;
}


void        PNLuaGameMap::addToMap2(PNObject& entity, char* id)
{
  puts("[LUA Teste] addToMap2");
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