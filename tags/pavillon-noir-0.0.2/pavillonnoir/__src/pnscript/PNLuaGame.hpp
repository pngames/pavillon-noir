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
    boost::filesystem::path	  _modsDirectory;
    boost::filesystem::path	  _gameRootDirectory;
    PNLuaGameMap*             _gameMap;
    std::set<std::string>     _loadedScripts;
    bool                      _gameStarted;


    /*/////////////////////////////////////////////////////////////////////////////
    /                                    Methods                                  /
    /////////////////////////////////////////////////////////////////////////////*/
	
	// register all the needed callbacks to the event manager.
    void                            registerCallbacks();

  public:

    lua_State* getLuaState(){ return this->L;}
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
    void init(void);
    


    //////////////////////////////////--------  callbacks ---------////////////////////////////////////
	void onUpdate(pnuint deltaTime);
	void onInit(pnEventType evt, PNObject* source, PNEventData* data);
	void onReset(pnEventType evt, PNObject* source, PNEventData* data);
	void onNewGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onSaveGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onLoadGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onLoadMap(pnEventType evt, PNObject* source, PNEventData* data);
	void onStartGame(pnEventType evt, PNObject* source, PNEventData* data);
	void onPauseGame(pnEventType evt, PNObject* source, PNEventData* data);
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