/*
* PNGUIGameManager.hpp
* 
* Description :
* PNGUIGameManager declaration
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

#ifndef _PNGUIGAMEMANAGER_HPP_
# define _PNGUIGAMEMANAGER_HPP_

#include "pndefs.h"
#include "pnevent.h"

#include "PNGUIGame.hpp"
#include "PNGUIEscMenu.hpp"

namespace PN{

  class PNGUIGameManager
  {
	typedef enum
	{
	  INGAME,
	  PAUSE,
	  INVENTORY,
	  DISCUTION,
	  NONE
	} gameStates;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	gameStates					_currentState;
  protected:
  private:
	PNGUIGame*					_guiGame;
	PNGUIEscMenu*				_guiMenuEsc;
	static PNGUIGameManager*	_instance;
	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIGameManager*			getInstance();
  protected:
  private:
	void						deleteAllInstances();
	void						resetAllInstances();
	void						launchInGame(pnEventType type, PNObject* source, PNEventData* data);
	void						escMenu(pnEventType type, PNObject* source, PNEventData* data);
	void						hidePrevious();
	void						callbackQuit(const unsigned int& enu);

	void						onMPStarted(pnEventType type, PNObject* source, PNEventData* data);
	void						onMPEnded(pnEventType type, PNObject* source, PNEventData* data);
	void						onMLStarted(pnEventType type, PNObject* source, PNEventData* data);
	void						onMLEnded(pnEventType type, PNObject* source, PNEventData* data);
	void						onMUStarted(pnEventType type, PNObject* source, PNEventData* data);
	void						onMUEnded(pnEventType type, PNObject* source, PNEventData* data);

	void						onMPPaused(pnEventType type, PNObject* source, PNEventData* data);
	void						onMPUnpauseded(pnEventType type, PNObject* source, PNEventData* data);



	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIGameManager();
  protected:
  private:
	~PNGUIGameManager();
  };
}


#endif /*_PNGUIGAMEMANAGER_HPP_*/
