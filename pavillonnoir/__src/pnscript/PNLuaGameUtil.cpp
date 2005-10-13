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
#include "PNConsole.hpp"
#include "PNLuaGame.hpp"
#include "PNLuaGameUtil.h"

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

	void	sendGameActionEvent(std::string id, std::string action, ...)
	{
		int count = 0;
		va_list marker;

		va_start( marker, action );     /* Initialize variable arguments. */
		//while( i != -1 )
		//{
		//	sum += i;
		//	count++;
		//	i = va_arg( marker, int);
		//}
		//va_end( marker );              /* Reset variable arguments.      */
		//return( sum ? (sum / count) : 0 );
	}

//	void	luaDebugLineHook(lua_State *S, lua_Debug *ar)
	//{
	  //printf("\n----\nEntered Lua Line Hook\n");
	  //char* buf = (char*) malloc(512 * sizeof(char));
	//  PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();

	 // lua_getinfo(vm->getLuaState(), "Snl", ar);
	  //sprintf(buf, "##Line: File \"%s\" -- function \"%s\" -- line : \"%d\"\n", ar->source, ar->name, ar->currentline);
	//  fprintf(vm->getDebugLogHandle(), "##Line: File \"%s\" -- function \"%s\" -- line : \"%d\"\n", ar->source, ar->name, ar->currentline);
	  //fwrite(buf, strlen(buf), sizeof(char), vm->getDebugLogHandle());
	  //free(buf);
//	}

	//void	activateDebug(bool b)
	//{
	//  PNLuaGame::getInstance()->setDebug(b);
	//}



	/*  void  onUpdate(float deltaTime)
	{
	PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
	vm->onUpdate(deltaTime);
	}
	void  onInit()
	{
	PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
	vm->onInit();
	}
	void  onReset()
	{
	PNLuaGame* vm = (PNLuaGame*) PNLuaGame::getInstance();
	vm->onReset();
	}
	*/
}
