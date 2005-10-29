/*
* PNLuaVm.cpp
* 
* Description : Lua Virtual Machine class implementation
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
#include <boost/thread/recursive_mutex.hpp>

#include "pndefs.h"
#include "pnerror.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
}
#include "tolua++.h"

#include "PNLuaVm.hpp"

using namespace PN;
namespace fs = boost::filesystem;

//----------------------------CONSTRUCTORS/DESTRUCTOR----------------------
PNLuaVm::PNLuaVm()
{
    this->_luaVm = lua_open();
    this->_debug = false;
    this->_debug_log = NULL;//fopen(debugLogPath.native_file_string().c_str(), "w+");
	//setDebug(true);
}

PNLuaVm::~PNLuaVm()
{
	lua_close(this->_luaVm);
}
//-------------------------------------------------------------------------

//-------------------------------MANIPULATION METHODS----------------------
pnerrorcode    PNLuaVm::execFile(const boost::filesystem::path &path)
{
    PNLOCK(this);

    pnerrorcode myret;
    int lret = lua_dofile(this->_luaVm, path.native_file_string().c_str());
    switch (lret)
    {
    case LUA_ERRSYNTAX:
        myret = PNEC_FAILED_TO_PARSE;
        break;
    case LUA_ERRMEM:
        myret = PNEC_ERROR;
        break;
    case LUA_ERRRUN:
        myret = PNEC_ERROR;
        break;
    case LUA_ERRFILE:
        myret = PNEC_ERROR;
        break;
    case 0:
        myret = PNEC_SUCCESS;
        break;
    default:
        myret = PNEC_ERROR;
    }
    assert(myret == PNEC_SUCCESS);
    return myret;
}

pnerrorcode    PNLuaVm::execString(const std::string &orders)
{   
    PNLOCK(this);

    pnerrorcode myret;
    int lret = lua_dostring(this->_luaVm, orders.c_str());
    switch (lret)
    {
    case LUA_ERRSYNTAX:
        myret = PNEC_FAILED_TO_PARSE;
        break;
    case LUA_ERRMEM:
        myret = PNEC_ERROR;
        break;
    case LUA_ERRRUN:
        myret = PNEC_ERROR;
        break;
    case 0:
        myret = PNEC_SUCCESS;
        break;
    default:
        myret = PNEC_ERROR;
    }
    assert(myret == PNEC_SUCCESS);
    return myret;
}

pnerrorcode    PNLuaVm::registerLuaLibrary(lua_library_register f)
{
    PNLOCK(this);

    f(this->_luaVm);
    return PNEC_ERROR;
}

void       PNLuaVm::setDebugLogPath(boost::filesystem::path path)
{
    PNLOCK(this);
    this->_debug_log = fopen(path.native_file_string().c_str(), "w+");
}

void	PNLuaVm::luaDebugLineHook(lua_State *S, lua_Debug *ar)
{
	static FILE* _lua_debug_file = fopen("./pnScript.log", "w+");

	lua_getinfo(S, "Snl", ar);
	fprintf(_lua_debug_file, "##Line: File \"%s\" -- function \"%s\" -- line : \"%d\"\n", ar->source, ar->name, ar->currentline);
}


void PNLuaVm::setDebug(bool b)
{
	this->_debug = b;

	if (b == true)
	{
		// Line hook activated - function called every time a line is interpreted
	   lua_sethook(this->_luaVm, (lua_Hook) luaDebugLineHook, LUA_MASKLINE, 0);
	}
	else
	{
		// Line hook deactivated
	   lua_sethook(this->_luaVm, (lua_Hook) luaDebugLineHook, 0, 0);
	}
}

bool	PNLuaVm::getLuaDebugLogging()
{
	return(this->_debug);
}
