/*
 * PNLuaGameMap.hpp
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

#ifndef _PN_LUA_GAME_MAP_HPP
#define _PN_LUA_GAME_MAP_HPP


#include "PNLuaVm.hpp" 
#include "PNGameMap.hpp"

//typedef struct s_scripts_infos
//{
//	std::string file;
//	std::string events;
//} t_scripts_infos;

namespace PN
{
	/*typedef std::map<std::string , t_scripts_infos *>  scriptInfosMap;*/
	class PN3DSkeletonObject;
    class PNLuaGameMap : public PNGameMap
    {
    protected:
        PNLuaVm&		_LVM;
		/*scriptInfosMap	_entitiesActions;*/
    public:
        PNLuaGameMap(PNLuaVm &lvm);
        ~PNLuaGameMap(void);
        void addToMap(const std::string& entityName,const std::string& id);
        void addToMap2(PNObject& entity, char* id);
		//execute mapScript
		void executeScript(const std::string& ScriptName);
        // void addToMap2(PNObject& entity);
        void clear();
		void loadScript(const std::string& file, const std::string& id, const std::string& events);
		void unloadScript(const std::string& file, const std::string& id, const std::string& events);
    };
}
#endif
