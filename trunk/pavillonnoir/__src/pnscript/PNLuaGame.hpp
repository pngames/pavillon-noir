/*
 * PNLuaGame.hpp
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

#ifndef _PNLUASANDBOX_HPP
# define  _PNLUASANDBOX_HPP

#include <boost/filesystem/path.hpp>
extern "C"
{
#include <lua.h>
#include <lualib.h>
}
#include "pnevent.h"
#include "PNGameInterface.hpp"
#include "PNLuaGameMap.hpp"
#include <set>
// Default lua debug log file
#define DEF_LUA_LOG_FILE "pnScript.log"

/* mini machine virtuelle lua*/
namespace PN
{
  class PNLuaGame: public PNGameInterface
  {
    /*/////////////////////////////////////////////////////////////////////////////
    /                                   Properties                                /
    /////////////////////////////////////////////////////////////////////////////*/
  public:

  private:
    lua_State*				  L;
    FILE*					  debug_log;  
	bool					  debug;
	boost::filesystem::path	  _modsDirectory;
    boost::filesystem::path	  _gameRootDirectory;
    PNLuaGameMap*             _gameMap;
    std::set<std::string>     _loadedScripts;
    bool                      _mapStarted;
    bool                      _mapLoaded;
    bool                      _isLoadingMap;
    bool                      _isUnloadingMap;
    std::string               _mapToLoad;


    /*/////////////////////////////////////////////////////////////////////////////
    /                                    Methods                                  /
    /////////////////////////////////////////////////////////////////////////////*/
	
	// register all the needed callbacks to the event manager.
    void                            registerCallbacks();

  public:

    lua_State* getLuaState(){ return this->L;}
	//Returns file handle to debug log file
	FILE* getDebugLogHandle(){ return this->debug_log;}
	//Sets debug logging (true or false)
	void  setDebug(bool b);
	bool  getLuaDebugLogging();
    //Set the script to the RUNNING state and runthe script; 
    //return true if succeed, else return false
    pnerrorcode						run(void);

    //Set the script to the PAUSED state and pause the script
    //return true if succeed, else return false
    pnerrorcode						pause(void);

    //set the script into STOPED state and jump to the 1st instruction; 
    //return true if succeed, else return false
    pnerrorcode						stop(void) ;

    //Return the state of the script. It could be RUNNING | PAUSED | STOPED | OVER 
    void							getState(void);

    //Return the Script id
    const pnchar*					getId(void);

    //load a lua script file
    static pnerrorcode				loadLuaScript(const pnchar* file, int reload=0);

    //defini le repertoir principal ou se trouve le script
    pnerrorcode						setGameRoot(const pnchar *name);

    const boost::filesystem::path&  getGameRoot();
    PNGameMap*                      getGameMap();

    //initialize the plugin
    void init(void);
    // load the map
    void loadMap();
    //unloadthe map;
    void unloadMap();



    //////////////////////////////////--------  callbacks ---------////////////////////////////////////
//	void onUpdate(pnuint deltaTime);
   	void onUpdate(pnEventType evt, PNObject* source, PNEventData* data);
	void onInit(pnEventType evt, PNObject* source, PNEventData* data);
    void onInitEnded(pnEventType evt, PNObject* source, PNEventData* data);
	void onReset(pnEventType evt, PNObject* source, PNEventData* data);
	void onNewGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onSaveGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onLoadGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onLoadMapStart(pnEventType evt, PNObject* source, PNEventData* data);
    void onLoadMapEnded(pnEventType evt, PNObject* source, PNEventData* data);
    void onUnloadMapStart(pnEventType evt, PNObject* source, PNEventData* data);
    void onUnloadMapEnded(pnEventType evt, PNObject* source, PNEventData* data);
    void onPlayMapEnd(pnEventType evt, PNObject* source, PNEventData* data);   
    void onPlayMapEnded(pnEventType evt, PNObject* source, PNEventData* data);
	void onPlayMapStart(pnEventType evt, PNObject* source, PNEventData* data);
    void onPlayMapStarted(pnEventType evt, PNObject* source, PNEventData* data);
	void onPlayMapPause(pnEventType evt, PNObject* source, PNEventData* data);
    void onPlayMapPaused(pnEventType evt, PNObject* source, PNEventData* data);
	void onLeaveGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onGameAction(pnEventType evt, PNObject* source, PNEventData* data);
	void onColision(pnEventType evt, PNObject* source, PNEventData* data);
    ////////////////////////////////////////////////////////////////////////////////////////////////////




    /*/////////////////////////////////////////////////////////////////////////////
    /                           Constructors / Destructor                         /
    /////////////////////////////////////////////////////////////////////////////*/
  public:
    ~PNLuaGame();
    PNLuaGame();
  };
}

#endif /*_PNLUASANDBOX_HPP*/
