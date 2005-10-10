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
}

PNLuaVm::~PNLuaVm()
{
    lua_close(this->_luaVm);
    fclose(this->_debug_log);
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
    case 0:
        myret = PNEC_SUCCES;
    }
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
    case 0:
        myret = PNEC_SUCCES;
        break;
    default:
        myret = PNEC_ERROR;
    }
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