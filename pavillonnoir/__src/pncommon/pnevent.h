/*
 * pnevent.h
 * 
 * Description :
 * Meta-include for events management
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

#ifndef _PNEVENT_H_
# define _PNEVENT_H_

#include <list>
#include <map>
#include <fastdelegate/FastDelegate.h>

namespace boost{namespace filesystem{class path;};};

namespace PN {
//////////////////////////////////////////////////////////////////////////

/*
 * \brief Event list
 *
 *	!! IMPORTANT !!
 *	If you ever add an event, don't forget to add it to the eventNames map
 *	of the PNEventManager (it's a map containing the char* name and the enum value)
 */
typedef enum
{
  PN_EVENT_GAME_INIT = 1,		/// Initialize all entities in the game, Start from 1
  PN_EVENT_GAME_INIT_STARTED,	/// Say the game init has started
  PN_EVENT_GAME_INIT_ENDED,	    /// Say the game init has finished
  PN_EVENT_GAME_NEW,			/// Set game state to new
  PN_EVENT_GAME_UPDATE,			/// Update all entities status
  PN_EVENT_GAME_UPDATE_STARTED, /// Say the game update has started
  PN_EVENT_GAME_UPDATE_ENDED,   /// Say the game update has finished
  PN_EVENT_GAME_START,			/// start the game
  PN_EVENT_GAME_SAVE,			/// save game
  PN_EVENT_GAME_LOAD,			/// Load saved game
  PN_EVENT_GAME_PAUSE,			/// pause game
  PN_EVENT_GAME_ACTION,			/// lunch a game action event	
  PN_EVENT_GAME_QUIT,			/// quit game
  PN_EVENT_GAME_QUIT_STARTED,
  PN_EVENT_GAME_QUIT_ENDED,				

  PN_EVENT_GUI_MENU_ROOT,
  PN_EVENT_GUI_MENU_LOAD,
  PN_EVENT_GUI_MENU_OPTIONS,
  PN_EVENT_GUI_MENU_CREDITS,
  PN_EVENT_GUI_MENU_PAUSE,
  PN_EVENT_GUI_NEW_GAME,
  PN_EVENT_GUI_GAME_START,
  PN_EVENT_GUI_QUIT,
  PN_EVENT_GUI_QUIT_MENU_ROOT,

  PN_EVENT_CONSOLE,

  PN_EVENT_SDL_GRAB_OFF,		/// When SDL mouse is visible
  PN_EVENT_SDL_GRAB_ON,			/// When SDL mouse is not visible
  PN_EVENT_SDL_ESC,

  PN_EVENT_MOUSE_MOVE,

  PN_EVENT_INFO_PANEL,
  PN_EVENT_UPDATE_GUI,

  //////////////////////////////////////////////////////////////////////////
  // MAPS LOADING

  PN_EVENT_ML_START,			/// start loading map
  PN_EVENT_ML_STARTED,			/// loading the map
  PN_EVENT_ML_END,				/// end loading map
  PN_EVENT_ML_ENDED,			/// loading map ended
  
  PN_EVENT_MU_START,			/// start unloading map
  PN_EVENT_MU_STARTED,			/// unloading map
  PN_EVENT_MU_END,				/// end unloading map
  PN_EVENT_MU_ENDED,			/// unloading map ended

  PN_EVENT_MP_START,			/// start play map
  PN_EVENT_MP_STARTED,          /// say the map has started
  PN_EVENT_MP_END,				/// stop the map
  PN_EVENT_MP_ENDED,            /// say the map has stoped
  PN_EVENT_MP_PAUSE,            /// pause the map
  PN_EVENT_MP_PAUSED,           /// say the map is paused
  PN_EVENT_MP_UNPAUSE,          /// pause the map
  PN_EVENT_MP_UNPAUSED,         /// say the map is paused
  //////////////////////////////////////////////////////////////////////////
  // OBJECTS DISPLACEMENT

  PN_EVENT_OM_START,			/// start moving object
  PN_EVENT_OM_STARTED,			/// object started moving
  PN_EVENT_OM_END,				/// end moving object
  PN_EVENT_OM_ENDED,			/// object ended moving
  PN_EVENT_OM,					/// object moved

  //////////////////////////////////////////////////////////////////////////
  // OBJECTS LOCAL ANIMATIONS

  PN_EVENT_OA_STARTED,			/// object animation started
  PN_EVENT_OA_LOOPED,			/// object animation looped
  PN_EVENT_OA_PAUSED,			/// object animation paused
  PN_EVENT_OA_ENDED,			/// object animation ended

  //////////////////////////////////////////////////////////////////////////
  // PHYSIC

  PN_EVENT_COLLISION,			/// collision occurred
  PN_EVENT_COLLISION_C,			/// collision occurred on character
  PN_EVENT_COLLISION_2C,		/// collision occurred between 2 characters

  //////////////////////////////////////////////////////////////////////////
  // FIGHT

  PN_EVENT_CH_ATTACK,			/// character attack
  PN_EVENT_CH_DEFEND_START,		/// character starting defend mode
  PN_EVENT_CH_DEFEND_END,		/// character ending defend mode

  PN_EVENT_CHL_TARGET,			/// character change target in lock mode fight
  PN_EVENT_CHL_START,			/// character start lock mode fight
  PN_EVENT_CHL_END,				/// character end lock mode fight

  PN_EVENT_CH_DIES,				/// character dies

  //////////////////////////////////////////////////////////////////////////
  // FRUSTRUM

  PN_EVENT_F_IN,				/// new object in camera frustum
  PN_EVENT_F_OUT,				/// object quit camera frustum
  PN_EVENT_FCH_IN,				/// new character in camera frustum
  PN_EVENT_FCH_OUT,				/// character quit camera frustum

  //////////////////////////////////////////////////////////////////////////
  // UPDATE

  PN_EVENT_RU_STARTING,			/// event occurred when render engine starting frame
  PN_EVENT_RU_ENDING,			/// event occurred when render engine ending frame
  PN_EVENT_PU_STARTING,			/// event occurred when physic engine starting frame
  PN_EVENT_PU_ENDING,			/// event occurred when render engine ending frame

  //////////////////////////////////////////////////////////////////////////
  // SCRIPTING

  PN_EVENT_SCR_START,			/// start running script
  PN_EVENT_SCR_STARTED,			/// script started
  PN_EVENT_SCR_END,				/// end running script
  PN_EVENT_SCR_ENDED,			/// script ended

  //////////////////////////////////////////////////////////////////////////
  // VIDEO

  PN_EVENT_VIDEO_CMD,			/// control video
  PN_EVENT_VIDEO_START,			/// start playing video
  PN_EVENT_VIDEO_STARTED,		/// video starting playing
  PN_EVENT_VIDEO_END,			/// end playing video
  PN_EVENT_VIDEO_ENDED,			/// video ending playing
  PN_EVENT_VIDEO_RESTART,		/// restart video
  PN_EVENT_VIDEO_RESTARTED,		/// video restarting

  //////////////////////////////////////////////////////////////////////////
  // SOUND

  PN_EVENT_SOUND_PLAY,			/// play a sound
  PN_EVENT_SOUND_STOP,			/// stop a sound
  PN_EVENT_SOUND_PAUSE,			/// pause volume
  PN_EVENT_SOUND_CREATE,		/// create a sound
  PN_EVENT_SOUND_VOLUME,		/// sound volume
  PN_EVENT_SOUND_ENABLE,		/// Enable sound
  PN_EVENT_SOUND_DISABLE,		/// Disable sound

  //////////////////////////////////////////////////////////////////////////

  // ...

  //////////////////////////////////////////////////////////////////////////
  PN_NUMBER_EVENTS
} pnEventType;

class PNObject;
class PNEventData;

/// Callback type
typedef fastdelegate::FastDelegate3<pnEventType, PNObject*, PNEventData*> EventCallback;

/// Script list type
typedef std::list<boost::filesystem::path*> scriptList;
/// Script map type
typedef std::map<pnEventType, scriptList*> scriptMap;

//////////////////////////////////////////////////////////////////////////
}

#include "PNEventManager.hpp"

#endif /*_PNEVENT_H_*/
