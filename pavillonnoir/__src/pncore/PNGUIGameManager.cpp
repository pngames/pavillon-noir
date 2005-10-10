/*
* PNGUIGameManager.cpp
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

#include "PNGUIGameManager.hpp"
#include "PNGUIMsgBox.hpp"
#include "pnrender.h"

using namespace PN;

namespace PN
{
  PNGUIGameManager*				PNGUIGameManager::_instance = NULL;

  PNGUIGameManager::PNGUIGameManager()
  {
	_currentState = NONE;
	_guiGame = NULL;

	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_GAME_START, EventCallback(this, &PNGUIGameManager::launchInGame));
	PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_ESC, EventCallback(this, &PNGUIGameManager::quitGame));
	
  }

  PNGUIGameManager::~PNGUIGameManager()
  {
	deleteAllInstances();
	if (_instance != NULL)
	  delete _instance;
  }

  PNGUIGameManager*	PNGUIGameManager::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIGameManager();

	return _instance;
  }

  void PNGUIGameManager::deleteAllInstances()
  {
	if (_guiGame != NULL)
	{
	  delete (_guiGame);
	  _guiGame = NULL;
	}
  }

  void  PNGUIGameManager::launchInGame(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_guiGame == NULL)
	  _guiGame = new PNGUIGame();


	_guiGame->show();
	_currentState = INGAME;
  }

  void  PNGUIGameManager::quitGame(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;

	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_PAUSE, NULL, NULL);
	PNGUIMsgBox* tmp = new PNGUIMsgBox("QUITTER ?", "Voulez-vous quitter\nla partie en cours ?", PNGUIMsgBox::YES_NO, PNGUIMsgBox::MsgBoxCallback(this, &PNGUIGameManager::callbackQuit), _guiGame->getWindow());
  }

  void PNGUIGameManager::callbackQuit(const unsigned int& enu)
  {
	if (enu == PNGUIMsgBox::YES)
	{
	  deleteAllInstances();
	  _currentState = NONE;
	 // PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_QUIT, NULL, NULL);
	 // PNEventManager::getInstance()->addEvent(PN_EVENT_GUI_MENUROOT, NULL, NULL);
	   PNRendererInterface::getInstance()->endRendering();
	}
  }

  void PNGUIGameManager::hidePrevious()
  {
	switch (_currentState) 
	{
	case INGAME:
	  _guiGame->hide();
		break;
	}
  }

}
