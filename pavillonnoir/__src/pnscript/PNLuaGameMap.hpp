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


#include "pnevent.h"
#include "PNLuaVm.hpp" 
#include "PNGameMap.hpp"
#include "PNGameEventData.hpp"
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
        bool            _mapStarted;
        bool            _mapPaused;
        std::string     _playerId;
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
        bool isStarted(){return _mapStarted;}
        bool isPaused(){return _mapPaused;}
        void loadScript(const std::string& file, const std::string& id, const std::string& events);
        void unloadScript(const std::string& file, const std::string& id, const std::string& events);
		//managed lua error
	    void manageLuaError(int errorcode); 
	    // register all the needed callbacks to the event manager.
        void registerInGameCallbacks();
        void unregisterInGameCallbacks();
        ///////////////////////////////////////////////////////////////////
        //        game maps callbacks
        ///////////////////////////////////////////////////////////////////
        void onUpdate(pnEventType evt, PNObject* source, PNEventData* data);
        void onInit(pnEventType evt, PNObject* source, PNEventData* data);
        void onReset(pnEventType evt, PNObject* source, PNEventData* data);
        void onPlayMapEnd(pnEventType evt, PNObject* source, PNEventData* data);   
        void onPlayMapStart(pnEventType evt, PNObject* source, PNEventData* data);
        void onPlayMapPause(pnEventType evt, PNObject* source, PNEventData* data);
        void onGameAction(pnEventType evt, PNObject* source, PNEventData* data);
        void onColision(pnEventType evt, PNObject* source, PNEventData* data);
        void onFrustrumIn(pnEventType evt, PNObject* source, PNEventData* data);
        void onFrustrumOut(pnEventType evt, PNObject* source, PNEventData* data);
        void onMouseMove(pnEventType evt, PNObject* source, PNEventData* data);
         ////////////////////////////////////////////////////////////////////////
        void sendGameActionEvent(std::string eventName, PNGameActionEventData *eventData);
    };
}
#endif
