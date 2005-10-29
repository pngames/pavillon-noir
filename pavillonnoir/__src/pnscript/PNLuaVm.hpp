/*
* PNLuaVm.hpp
* 
* Description : Lua Virtual Machine class
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


#ifndef _PNLUAVM_HPP
#define _PNLUAVM_HPP

#include <boost/thread/recursive_mutex.hpp>
#include "PNObject.hpp"

typedef int (*lua_library_register)(lua_State *lvm);

namespace PN
{
    class PNObject;
    class PNLuaVm: public PNObject
    {
    protected:
        lua_State*				  _luaVm;
        FILE*					  _debug_log;
        bool					  _debug;
    public:
        boost::recursive_mutex	  _mutex;

    //----------------------------CONSTRUCTORS/DESTRUCTOR----------------------
    public:
        PNLuaVm();
        ~PNLuaVm();
    //-------------------------------------------------------------------------
    public:
	//----------------------------DEBUG RELATED METHODS------------------------
		//Returns file handle to debug log file
		//FILE*	getDebugLogHandle(){ return this->_debug_log;}
		//Sets debug logging (true or false)
		void	setDebug(bool b);
		bool	getLuaDebugLogging();
		/* Debug Hooks */
		static void	luaDebugLineHook(lua_State *S, lua_Debug *ar);
		
    //-------------------------------MANIPULATION METHODS---------------------------------
        int    execFile(const boost::filesystem::path &path);
        int    execString(const std::string &orders);
        int    registerLuaLibrary(lua_library_register);
        void		   setDebugLogPath(boost::filesystem::path path);
		void   reset();
    };
}
#endif

