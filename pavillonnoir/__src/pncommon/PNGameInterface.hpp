/*
 * PNGameInterface.hpp
 * 
 * Description :
 * PNGameInterface declaration
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

#ifndef _PNGAMEINTERFACE_HPP_
# define _PNGAMEINTERFACE_HPP_

#include <boost/filesystem/path.hpp>

#include "pnevent.h"

#include "PNInterface.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNGameMap;

class PNAPI PNGameInterface: public PNInterface
{
  static PNGameInterface* _instance; 

public:
  // fonction statique qui renvoye une instance unique de l'objet; 
  static PNGameInterface* getInstance();

  //Set the script to the RUNNING state and runthe script; 
  //return true if succeed, else return false
  virtual pnerrorcode run(void)=0;

  //Set the script to the PAUSED state and pause the script
  //return true if succeed, else return false
  virtual pnerrorcode pause(void) =0;

  //set the script into STOPED state and jump to the 1st instruction; 
  //return true if succeed, else return false
  virtual pnerrorcode stop(void)=0;

  //Return the state of the script. It could be RUNNING | PAUSED | STOPED | OVER 
  virtual void getState(void)=0;

  //Return the Script id
  virtual const pnchar* getId(void)=0;

  //defini le repertoir principal ou se trouve le script
  virtual pnerrorcode setGameRoot(const pnchar *name)=0;

  //recupere le chemin racine du jeu 
  virtual const boost::filesystem::path& getGameRoot()=0;

  //init the plugin
  virtual void init(void)=0;
  
  //return the gameMap
  virtual PNGameMap* getGameMap()=0;

  //Event CallBack
  virtual void onUpdate(pnuint deltaTime){};
  virtual void onInit(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onReset(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onNewGame(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onSaveGame(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onLoadGame(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onLoadMap(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onStartGame(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onPauseGame(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onLeaveGame(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onGameAction(pnEventType evt, PNObject* source, PNEventData* data){};
  virtual void onColision(pnEventType evt, PNObject* source, PNEventData* data){};

  plugintypes	getType() {return PN_PLUGIN_GAME;}

protected:
  PNGameInterface();

public:
  virtual ~PNGameInterface();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNGAMEINTERFACE_HPP_*/
