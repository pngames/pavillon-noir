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
  _eventEnums["PN_EVENT_GAME_INIT_STARTED"] = PN_EVENT_GAME_INIT_STARTED;
  _eventNames[PN_EVENT_GAME_INIT_STARTED] = "PN_EVENT_GAME_INIT_STARTED";
  _eventEnums["PN_EVENT_GAME_INIT_ENDED"] = PN_EVENT_GAME_INIT_ENDED;
  _eventNames[PN_EVENT_GAME_INIT_ENDED] = "PN_EVENT_GAME_INIT_ENDED";
  _eventEnums["PN_EVENT_GAME_UPDATE"] = PN_EVENT_GAME_UPDATE;
  _eventNames[PN_EVENT_GAME_UPDATE] = "PN_EVENT_GAME_UPDATE";
  _eventEnums["PN_EVENT_GAME_UPDATE_STARTED"] = PN_EVENT_GAME_UPDATE_STARTED;
  _eventNames[PN_EVENT_GAME_UPDATE_STARTED] = "PN_EVENT_GAME_UPDATE_STARTED";  
  _eventEnums["PN_EVENT_GAME_UPDATE_ENDED"] = PN_EVENT_GAME_UPDATE_ENDED;
  _eventNames[PN_EVENT_GAME_UPDATE_ENDED] = "PN_EVENT_GAME_UPDATE_ENDED";
  _eventEnums["PN_EVENT_GAME_PAUSE"] = PN_EVENT_GAME_PAUSE;
  _eventNames[PN_EVENT_GAME_PAUSE] = "PN_EVENT_GAME_PAUSE";
  _eventEnums["PN_EVENT_GAME_ACTION"] = PN_EVENT_GAME_ACTION;
  _eventNames[PN_EVENT_GAME_ACTION] = "PN_EVENT_GAME_ACTION";
  _eventEnums["PN_EVENT_GAME_QUIT"] = PN_EVENT_GAME_QUIT;
  _eventNames[PN_EVENT_GAME_QUIT] = "PN_EVENT_GAME_QUIT";
  _eventEnums["PN_EVENT_GAME_QUIT_STARTED"] = PN_EVENT_GAME_QUIT_STARTED;
  _eventNames[PN_EVENT_GAME_QUIT_STARTED] = "PN_EVENT_GAME_QUIT_STARTED";
  _eventEnums["PN_EVENT_GAME_QUIT_ENDED"] = PN_EVENT_GAME_QUIT_ENDED;
  _eventNames[PN_EVENT_GAME_ERROR] = "PN_EVENT_GAME_ERROR";
  _eventEnums["PN_EVENT_GAME_ERROR"] = PN_EVENT_GAME_ERROR;
  
  _eventNames[PN_EVENT_GAME_QUIT_ENDED] = "PN_EVENT_GAME_QUIT_ENDED";
  _eventEnums["PN_EVENT_MOUSE_MOVE"] = PN_EVENT_MOUSE_MOVE;
  _eventNames[PN_EVENT_MOUSE_MOVE] = "PN_EVENT_MOUSE_MOVE";

  // GUI
  _eventEnums["PN_EVENT_GUI_MENU_ROOT"] = PN_EVENT_GUI_MENU_ROOT;
  _eventNames[PN_EVENT_GUI_MENU_ROOT] = "PN_EVENT_GUI_MENU_ROOT";
  _eventEnums["PN_EVENT_GUI_MENU_LOAD"] = PN_EVENT_GUI_MENU_LOAD;
  _eventNames[PN_EVENT_GUI_MENU_LOAD] = "PN_EVENT_GUI_MENU_LOAD";
  _eventEnums["PN_EVENT_GUI_MENU_OPTIONS"] = PN_EVENT_GUI_MENU_OPTIONS;
  _eventNames[PN_EVENT_GUI_MENU_OPTIONS] = "PN_EVENT_GUI_MENU_OPTIONS";
  _eventEnums["PN_EVENT_GUI_MENU_CREDITS"] = PN_EVENT_GUI_MENU_CREDITS;
  _eventNames[PN_EVENT_GUI_MENU_CREDITS] = "PN_EVENT_GUI_MENU_CREDITS";
  _eventEnums["PN_EVENT_GUI_NEW_GAME"] = PN_EVENT_GUI_NEW_GAME;
  _eventNames[PN_EVENT_GUI_NEW_GAME] = "PN_EVENT_GUI_NEWG_AME";
  _eventEnums["PN_EVENT_GUI_GAME_START"] = PN_EVENT_GUI_GAME_START;
  _eventNames[PN_EVENT_GUI_GAME_START] = "PN_EVENT_GUI_GAME_START";
  _eventEnums["PN_EVENT_GUI_QUIT"] = PN_EVENT_GUI_QUIT;
  _eventNames[PN_EVENT_GUI_QUIT] = "PN_EVENT_GUI_QUIT";
  _eventEnums["PN_EVENT_GUI_QUIT_MENU_ROOT"] = PN_EVENT_GUI_QUIT_MENU_ROOT;
  _eventNames[PN_EVENT_GUI_QUIT_MENU_ROOT] = "PN_EVENT_GUI_QUIT_MENU_ROOT";

  

	_eventEnums["PN_EVENT_CONFPANEL"] = PN_EVENT_CONFPANEL;
  _eventNames[PN_EVENT_CONFPANEL] = "PN_EVENT_CONFPANEL";

  _eventEnums["PN_EVENT_CONSOLE"] = PN_EVENT_CONSOLE;
  _eventNames[PN_EVENT_CONSOLE] = "PN_EVENT_CONSOLE";
  _eventEnums["PN_EVENT_SDL_GRAB_OFF"] = PN_EVENT_SDL_GRAB_OFF;	
  _eventNames[PN_EVENT_SDL_GRAB_OFF] = "PN_EVENT_SDL_GRAB_OFF";	
  _eventEnums["PN_EVENT_SDL_GRAB_ON"] = PN_EVENT_SDL_GRAB_ON;
  _eventNames[PN_EVENT_SDL_GRAB_ON] = "PN_EVENT_SDL_GRAB_ON";
  _eventEnums["PN_EVENT_SDL_ESC"] = PN_EVENT_SDL_ESC;
  _eventNames[PN_EVENT_SDL_ESC] = "PN_EVENT_SDL_ESC";
  _eventEnums["PN_EVENT_INFO_PANEL"] = PN_EVENT_INFO_PANEL;
  _eventNames[PN_EVENT_INFO_PANEL] = "PN_EVENT_INFO_PANEL";

  _eventEnums["PN_EVENT_UPDATE_GUI"] = PN_EVENT_UPDATE_GUI;
  _eventNames[PN_EVENT_UPDATE_GUI] = "PN_EVENT_UPDATE_GUI";

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

  _eventEnums["PN_EVENT_MP_START"] = PN_EVENT_MP_START;
  _eventNames[PN_EVENT_MP_START] = "PN_EVENT_MP_START";
  _eventEnums["PN_EVENT_MP_END"] = PN_EVENT_MP_END;
  _eventNames[PN_EVENT_MP_END] = "PN_EVENT_MP_END";
  _eventEnums["PN_EVENT_MP_STARTED"] = PN_EVENT_MP_STARTED;
  _eventNames[PN_EVENT_MP_STARTED] = "PN_EVENT_MP_STARTED";
  _eventEnums["PN_EVENT_MP_ENDED"] = PN_EVENT_MP_ENDED;
  _eventNames[PN_EVENT_MP_ENDED] = "PN_EVENT_MP_ENDED";
  _eventEnums["PN_EVENT_MP_PAUSE"] = PN_EVENT_MP_PAUSE;
  _eventNames[PN_EVENT_MP_PAUSE] = "PN_EVENT_MP_PAUSE";
  _eventEnums["PN_EVENT_MP_PAUSED"] = PN_EVENT_MP_PAUSED;
  _eventNames[PN_EVENT_MP_PAUSED] = "PN_EVENT_MP_PAUSED";

  _eventEnums["PN_EVENT_MP_UNPAUSE"] = PN_EVENT_MP_UNPAUSE;
  _eventNames[PN_EVENT_MP_UNPAUSE] = "PN_EVENT_MP_UNPAUSE";
  _eventEnums["PN_EVENT_MP_UNPAUSED"] = PN_EVENT_MP_UNPAUSED;
  _eventNames[PN_EVENT_MP_UNPAUSED] = "PN_EVENT_MP_UNPAUSED";

  //////////////////////////////////////////////////////////////////////////
  // OBJECTS DISPLACEMENT

  _eventEnums["PN_EVENT_OM_STARTED"] = PN_EVENT_OM_STARTED;
  _eventNames[PN_EVENT_OM_STARTED] = "PN_EVENT_OM_STARTED";
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
  
  //////////////////////////////////////////////////////////////////////////
  // SOUND
  _eventEnums["PN_EVENT_SOUND_PLAY"] = PN_EVENT_SOUND_PLAY;
  _eventNames[PN_EVENT_SOUND_PLAY] = "PN_EVENT_SOUND_PLAY";
  _eventEnums["PN_EVENT_SOUND_STOP"] = PN_EVENT_SOUND_STOP;
  _eventNames[PN_EVENT_SOUND_STOP] = "PN_EVENT_SOUND_STOP";
  _eventEnums["PN_EVENT_SOUND_CREATE"] = PN_EVENT_SOUND_CREATE;
  _eventNames[PN_EVENT_SOUND_CREATE] = "PN_EVENT_SOUND_CREATE";
  _eventEnums["PN_EVENT_SOUND_PAUSE"] = PN_EVENT_SOUND_PAUSE;
  _eventNames[PN_EVENT_SOUND_PAUSE] = "PN_EVENT_SOUND_PAUSE";
  _eventEnums["PN_EVENT_SOUND_VOLUME"] = PN_EVENT_SOUND_VOLUME;
  _eventNames[PN_EVENT_SOUND_VOLUME] = "PN_EVENT_SOUND_VOLUME";
  _eventEnums["PN_EVENT_SOUND_ENABLE"] = PN_EVENT_SOUND_ENABLE;
  _eventNames[PN_EVENT_SOUND_ENABLE] = "PN_EVENT_SOUND_ENABLE";
  _eventEnums["PN_EVENT_SOUND_DISABLE"] = PN_EVENT_SOUND_DISABLE;
  _eventNames[PN_EVENT_SOUND_DISABLE] = "PN_EVENT_SOUND_DISABLE";
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
      boost::mutex::scoped_lock lk(_waitMutex);
      _cond.wait(lk);
    }

	pnEventType type;
	PNObject* source;
	PNEventData* data;

	PNLOCK_BEGIN(this);
	{
	  pnevent& event = _events.front();

	  type = event.type;
	  source = event.source;
	  data = event.data;
	}
	PNLOCK_END(this);

	sendEvent(type, source, data);

	PNLOCK(this);

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
  if (data != NULL)
	data->destructData = destruct;

  pnevent eventParams(type, source, data);

  PNLOCK(this);

  _events.push(eventParams);

  eventParams.data = NULL;

  if (_events.size() == 1)
  {
	//pnerror(PN_LOGLVL_INFO, "stack was empty");
    _cond.notify_all();
  }
}

void	PNEventManager::sendEvent(pnEventType type, PNObject* source, PNEventData* data)
{
  _callbackList[type].sendEvent(type, source, data);
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
  _callbackList[type].addCallback(callback);
}

void	PNEventManager::deleteCallback(pnEventType type, const EventCallback& callback)
{
  _callbackList[type].deleteCallback(callback);
}

//////////////////////////////////////////////////////////////////////////

void		PNEventManager::stop()
{
  _run = false;
}

//////////////////////////////////////////////////////////////////////////
}
