/*
 * PNEventManager.cpp
 * 
 * Description :
 * PNEventManager definition
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
#include "pnevent.h"

#include "PNConsole.hpp"

#include "PNEventManager.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNEventManager*	PNEventManager::_instance = NULL;

PNEventManager::PNEventManager()
{
  _run = true;

  // Creation of the maps containing the char* name & the enum of each event

  // GAME EVENTS
  _eventEnums["PN_EVENT_GAME_NEW"] = PN_EVENT_GAME_NEW;
  _eventNames[PN_EVENT_GAME_NEW] = "PN_EVENT_GAME_NEW";
  _eventEnums["PN_EVENT_GAME_START"] = PN_EVENT_GAME_START;
  _eventNames[PN_EVENT_GAME_START] = "PN_EVENT_GAME_START";
  _eventEnums["PN_EVENT_GAME_SAVE"] = PN_EVENT_GAME_SAVE;
  _eventNames[PN_EVENT_GAME_SAVE] = "PN_EVENT_GAME_SAVE";
  _eventEnums["PN_EVENT_GAME_LOAD"] = PN_EVENT_GAME_LOAD;
  _eventNames[PN_EVENT_GAME_LOAD] = "PN_EVENT_GAME_LOAD";
  _eventEnums["PN_EVENT_GAME_INIT"] = PN_EVENT_GAME_INIT;
  _eventNames[PN_EVENT_GAME_INIT] = "PN_EVENT_GAME_INIT";
  _eventEnums["PN_EVENT_GAME_UPDATE"] = PN_EVENT_GAME_UPDATE;
  _eventNames[PN_EVENT_GAME_UPDATE] = "PN_EVENT_GAME_UPDATE";
  _eventEnums["PN_EVENT_GAME_PAUSE"] = PN_EVENT_GAME_PAUSE;
  _eventNames[PN_EVENT_GAME_PAUSE] = "PN_EVENT_GAME_PAUSE";
  _eventEnums["PN_EVENT_GAME_ACTION"] = PN_EVENT_GAME_ACTION;
  _eventNames[PN_EVENT_GAME_ACTION] = "PN_EVENT_GAME_ACTION";

  // GUI
  _eventEnums["PN_EVENT_CONSOLE"] = PN_EVENT_CONSOLE;
  _eventNames[PN_EVENT_CONSOLE] = "PN_EVENT_CONSOLE";
  _eventEnums["PN_EVENT_SDL_GRAB_OFF"] = PN_EVENT_SDL_GRAB_OFF;	
  _eventNames[PN_EVENT_SDL_GRAB_OFF] = "PN_EVENT_SDL_GRAB_OFF";	
  _eventEnums["PN_EVENT_SDL_GRAB_ON"] = PN_EVENT_SDL_GRAB_ON;
  _eventNames[PN_EVENT_SDL_GRAB_ON] = "PN_EVENT_SDL_GRAB_ON";
  _eventEnums["PN_EVENT_INFO_PANEL"] = PN_EVENT_INFO_PANEL;
  _eventNames[PN_EVENT_INFO_PANEL] = "PN_EVENT_INFO_PANEL";

  //////////////////////////////////////////////////////////////////////////
  // MAPS LOADING

  _eventEnums["PN_EVENT_ML_START"] = PN_EVENT_ML_START;
  _eventNames[PN_EVENT_ML_START] = "PN_EVENT_ML_START";
  _eventEnums["PN_EVENT_ML_STARTED"] = PN_EVENT_ML_STARTED;
  _eventNames[PN_EVENT_ML_STARTED] = "PN_EVENT_ML_STARTED";
  _eventEnums["PN_EVENT_ML_END"] = PN_EVENT_ML_END;
  _eventNames[PN_EVENT_ML_END] = "PN_EVENT_ML_END";
  _eventEnums["PN_EVENT_ML_ENDED"] = PN_EVENT_ML_ENDED;
  _eventNames[PN_EVENT_ML_ENDED] = "PN_EVENT_ML_ENDED";

  _eventEnums["PN_EVENT_MU_START"] = PN_EVENT_MU_START;
  _eventNames[PN_EVENT_MU_START] = "PN_EVENT_MU_START";
  _eventEnums["PN_EVENT_MU_STARTED"] = PN_EVENT_MU_STARTED;
  _eventNames[PN_EVENT_MU_STARTED] = "PN_EVENT_MU_STARTED";
  _eventEnums["PN_EVENT_MU_END"] = PN_EVENT_MU_END;
  _eventNames[PN_EVENT_MU_END] = "PN_EVENT_MU_END";
  _eventEnums["PN_EVENT_MU_ENDED"] = PN_EVENT_MU_ENDED;
  _eventNames[PN_EVENT_MU_ENDED] = "PN_EVENT_MU_ENDED";

  _eventEnums["PN_EVENT_M_START"] = PN_EVENT_M_START;
  _eventNames[PN_EVENT_M_START] = "PN_EVENT_M_START";
  _eventEnums["PN_EVENT_M_END"] = PN_EVENT_M_END;
  _eventNames[PN_EVENT_M_END] = "PN_EVENT_M_END";

  //////////////////////////////////////////////////////////////////////////
  // OBJECTS DISPLACEMENT

  _eventEnums["PN_EVENT_OM_START"] = PN_EVENT_OM_START;
  _eventNames[PN_EVENT_OM_START] = "PN_EVENT_OM_START";
  _eventEnums["PN_EVENT_OM_STARTED"] = PN_EVENT_OM_STARTED;
  _eventNames[PN_EVENT_OM_STARTED] = "PN_EVENT_OM_STARTED";
  _eventEnums["PN_EVENT_OM_END"] = PN_EVENT_OM_END;
  _eventNames[PN_EVENT_OM_END] = "PN_EVENT_OM_END";
  _eventEnums["PN_EVENT_OM_ENDED"] = PN_EVENT_OM_ENDED;
  _eventNames[PN_EVENT_OM_ENDED] = "PN_EVENT_OM_ENDED";
  _eventEnums["PN_EVENT_OM"] = PN_EVENT_OM;
  _eventNames[PN_EVENT_OM] = "PN_EVENT_OM";

  //////////////////////////////////////////////////////////////////////////
  // OBJECTS LOCAL ANIMATIONS

  _eventEnums["PN_EVENT_OA_STARTED"] = PN_EVENT_OA_STARTED;
  _eventNames[PN_EVENT_OA_STARTED] = "PN_EVENT_OA_STARTED";
  _eventEnums["PN_EVENT_OA_LOOPED"] = PN_EVENT_OA_LOOPED;
  _eventNames[PN_EVENT_OA_LOOPED] = "PN_EVENT_OA_LOOPED";
  _eventEnums["PN_EVENT_OA_PAUSED"] = PN_EVENT_OA_PAUSED;
  _eventNames[PN_EVENT_OA_PAUSED] = "PN_EVENT_OA_PAUSED";
  _eventEnums["PN_EVENT_OA_ENDED"] = PN_EVENT_OA_ENDED;
  _eventNames[PN_EVENT_OA_ENDED] = "PN_EVENT_OA_ENDED";

  //////////////////////////////////////////////////////////////////////////
  // PHYSIC

  _eventEnums["PN_EVENT_COLLISION"] = PN_EVENT_COLLISION;
  _eventNames[PN_EVENT_COLLISION] = "PN_EVENT_COLLISION";
  _eventEnums["PN_EVENT_COLLISION_C"] = PN_EVENT_COLLISION_C;
  _eventNames[PN_EVENT_COLLISION_C] = "PN_EVENT_COLLISION_C";
  _eventEnums["PN_EVENT_COLLISION_2C"] = PN_EVENT_COLLISION_2C;
  _eventNames[PN_EVENT_COLLISION_2C] = "PN_EVENT_COLLISION_2C";

  //////////////////////////////////////////////////////////////////////////
  // FIGHT

  _eventEnums["PN_EVENT_CH_ATTACK"] = PN_EVENT_CH_ATTACK;
  _eventNames[PN_EVENT_CH_ATTACK] = "PN_EVENT_CH_ATTACK";
  _eventEnums["PN_EVENT_CH_DEFEND_START"] = PN_EVENT_CH_DEFEND_START;
  _eventNames[PN_EVENT_CH_DEFEND_START] = "PN_EVENT_CH_DEFEND_START";
  _eventEnums["PN_EVENT_CH_DEFEND_END"] = PN_EVENT_CH_DEFEND_END;
  _eventNames[PN_EVENT_CH_DEFEND_END] = "PN_EVENT_CH_DEFEND_END";

  _eventEnums["PN_EVENT_CHL_TARGET"] = PN_EVENT_CHL_TARGET;
  _eventNames[PN_EVENT_CHL_TARGET] = "PN_EVENT_CHL_TARGET";
  _eventEnums["PN_EVENT_CHL_START"] = PN_EVENT_CHL_START;
  _eventNames[PN_EVENT_CHL_START] = "PN_EVENT_CHL_START";
  _eventEnums["PN_EVENT_CHL_END"] = PN_EVENT_CHL_END;
  _eventNames[PN_EVENT_CHL_END] = "PN_EVENT_CHL_END";

  _eventEnums["PN_EVENT_CH_DIES"] = PN_EVENT_CH_DIES;
  _eventNames[PN_EVENT_CH_DIES] = "PN_EVENT_CH_DIES";

  //////////////////////////////////////////////////////////////////////////
  // FRUSTRUM

  _eventEnums["PN_EVENT_F_IN"] = PN_EVENT_F_IN;
  _eventNames[PN_EVENT_F_IN] = "PN_EVENT_F_IN";
  _eventEnums["PN_EVENT_F_OUT"] = PN_EVENT_F_OUT;
  _eventNames[PN_EVENT_F_OUT] = "PN_EVENT_F_OUT";
  _eventEnums["PN_EVENT_FCH_IN"] = PN_EVENT_FCH_IN;
  _eventNames[PN_EVENT_FCH_IN] = "PN_EVENT_FCH_IN";
  _eventEnums["PN_EVENT_FCH_OUT"] = PN_EVENT_FCH_OUT;
  _eventNames[PN_EVENT_FCH_OUT] = "PN_EVENT_FCH_OUT";

  //////////////////////////////////////////////////////////////////////////
  // UPDATE

  _eventEnums["PN_EVENT_RU_STARTING"] = PN_EVENT_RU_STARTING;
  _eventNames[PN_EVENT_RU_STARTING] = "PN_EVENT_RU_STARTING";
  _eventEnums["PN_EVENT_RU_ENDING"] = PN_EVENT_RU_ENDING;
  _eventNames[PN_EVENT_RU_ENDING] = "PN_EVENT_RU_ENDING";
  _eventEnums["PN_EVENT_PU_STARTING"] = PN_EVENT_PU_STARTING;
  _eventNames[PN_EVENT_PU_STARTING] = "PN_EVENT_PU_STARTING";
  _eventEnums["PN_EVENT_PU_ENDING"] = PN_EVENT_PU_ENDING;
  _eventNames[PN_EVENT_PU_ENDING] = "PN_EVENT_PU_ENDING";

  //////////////////////////////////////////////////////////////////////////
  // SCRIPTING

  _eventEnums["PN_EVENT_SCR_START"] = PN_EVENT_SCR_START;
  _eventNames[PN_EVENT_SCR_START] = "PN_EVENT_SCR_START";
  _eventEnums["PN_EVENT_SCR_STARTED"] = PN_EVENT_SCR_STARTED;
  _eventNames[PN_EVENT_SCR_STARTED] = "PN_EVENT_SCR_STARTED";
  _eventEnums["PN_EVENT_SCR_END"] = PN_EVENT_SCR_END;
  _eventNames[PN_EVENT_SCR_END] = "PN_EVENT_SCR_END";
  _eventEnums["PN_EVENT_SCR_ENDED"] = PN_EVENT_SCR_ENDED;
  _eventNames[PN_EVENT_SCR_ENDED] = "PN_EVENT_SCR_ENDED";

  //////////////////////////////////////////////////////////////////////////
  // VIDEO

  _eventEnums["PN_EVENT_VIDEO_CMD"] = PN_EVENT_VIDEO_CMD;
  _eventNames[PN_EVENT_VIDEO_CMD] = "PN_EVENT_VIDEO_CMD";
  _eventEnums["PN_EVENT_VIDEO_START"] = PN_EVENT_VIDEO_START;
  _eventNames[PN_EVENT_VIDEO_START] = "PN_EVENT_VIDEO_START";
  _eventEnums["PN_EVENT_VIDEO_STARTED"] = PN_EVENT_VIDEO_STARTED;
  _eventNames[PN_EVENT_VIDEO_STARTED] = "PN_EVENT_VIDEO_STARTED";
  _eventEnums["PN_EVENT_VIDEO_END"] = PN_EVENT_VIDEO_END;
  _eventNames[PN_EVENT_VIDEO_END] = "PN_EVENT_VIDEO_END";
  _eventEnums["PN_EVENT_VIDEO_ENDED"] = PN_EVENT_VIDEO_ENDED;
  _eventNames[PN_EVENT_VIDEO_ENDED] = "PN_EVENT_VIDEO_ENDED";
  _eventEnums["PN_EVENT_VIDEO_RESTART"] = PN_EVENT_VIDEO_RESTART;
  _eventNames[PN_EVENT_VIDEO_RESTART] = "PN_EVENT_VIDEO_RESTART";
  _eventEnums["PN_EVENT_VIDEO_RESTARTED"] = PN_EVENT_VIDEO_RESTARTED;
  _eventNames[PN_EVENT_VIDEO_RESTARTED] = "PN_EVENT_VIDEO_RESTARTED";
}

PNEventManager::~PNEventManager()
{

}

PNEventManager*	PNEventManager::getInstance()
{
  if (_instance == NULL)
	_instance = new PNEventManager();

  return _instance;
}

//////////////////////////////////////////////////////////////////////////

void
PNEventManager::run()
{
  while (_run)
  {
    if (_events.empty())
    {
      boost::mutex::scoped_lock lk(_mutex);
      _cond.wait(lk);
    }

    pnevent& event = _events.front();

	sendEvent(event.type, event.source, event.data);

    _events.pop();
  }
}

void
PNEventManager::init()
{
  boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNEventManager::run));
}

//////////////////////////////////////////////////////////////////////////

void	PNEventManager::addEvent(pnEventType type, PNObject* source, PNEventData* data, bool destruct/* = true*/)
{
  pnevent eventParams(type, source, data, destruct);

  _events.push(eventParams);

  eventParams.data = NULL;

  if (_events.size() == 1)
  {
	pnerror(PN_LOGLVL_INFO, "stack was empty");

    _cond.notify_all();
  }
}

void	PNEventManager::sendEvent(pnEventType type, PNObject* source, PNEventData* data)
{
  _callbacktList[type].sendEvent(type, source, data);
}

const std::string&	PNEventManager::getNameByType(pnEventType type)
{
  return _eventNames[type];
}

pnEventType			PNEventManager::getTypeByName(const std::string& name)
{
  return _eventEnums[name];
}

//////////////////////////////////////////////////////////////////////////

void	PNEventManager::addCallback(pnEventType type, const EventCallback& callback)
{
  _callbacktList[type].addCallback(callback);
}

void	PNEventManager::deleteCallback(pnEventType type, const EventCallback& callback)
{
  _callbacktList[type].deleteCallback(callback);
}

//////////////////////////////////////////////////////////////////////////

pnint		PNEventManager::unserialize(const fs::path& file)
{
  return PNEC_NOT_IMPLEMENTED;
}

pnint		PNEventManager::serialize(const fs::path& file)
{
  return PNEC_NOT_IMPLEMENTED;
}

void		PNEventManager::stop()
{
  _run = false;
}

//////////////////////////////////////////////////////////////////////////
}
