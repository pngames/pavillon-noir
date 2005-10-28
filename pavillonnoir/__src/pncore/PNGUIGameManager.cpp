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
	_guiMenuEsc = NULL;
	_guiMenuLoad = NULL;

	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_GAME_START, EventCallback(this, &PNGUIGameManager::launchInGame));
	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_NEW_GAME, EventCallback(this, &PNGUIGameManager::launchInGame));

	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_QUIT_MENU_ROOT, EventCallback(this, &PNGUIGameManager::launchMenuRoot));

	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_MENU_LOAD, EventCallback(this, &PNGUIGameManager::launchMenuLoad));

	PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_ESC, EventCallback(this, &PNGUIGameManager::escManager));

	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_MENU_PAUSE, EventCallback(this, &PNGUIGameManager::escMenu));

	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_QUIT, EventCallback(this, &PNGUIGameManager::launchQuit));

	PNEventManager::getInstance()->addCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PNGUIGameManager::onMPStarted));
	PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PNGUIGameManager::onMPEnded));

	PNEventManager::getInstance()->addCallback(PN_EVENT_ML_STARTED, EventCallback(this, &PNGUIGameManager::onMLStarted));
	PNEventManager::getInstance()->addCallback(PN_EVENT_ML_ENDED, EventCallback(this, &PNGUIGameManager::onMLEnded));

	PNEventManager::getInstance()->addCallback(PN_EVENT_MU_STARTED, EventCallback(this, &PNGUIGameManager::onMUStarted));
	PNEventManager::getInstance()->addCallback(PN_EVENT_MU_ENDED, EventCallback(this, &PNGUIGameManager::onMUEnded));

	PNEventManager::getInstance()->addCallback(PN_EVENT_MP_PAUSED, EventCallback(this, &PNGUIGameManager::onMPPaused));
	PNEventManager::getInstance()->addCallback(PN_EVENT_MP_UNPAUSED, EventCallback(this, &PNGUIGameManager::onMPUnpauseded));
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
	if (_guiMenuEsc != NULL) 
	{
	  delete (_guiMenuEsc);
	  _guiMenuEsc = NULL;
	}
  }

  void PNGUIGameManager::resetAllInstances()
  {
	if (_guiGame != NULL)
	 _guiGame->resetGUI();
	
	if (_guiMenuEsc != NULL) 
	 _guiMenuEsc->resetGUI();
	
	if (_guiMenuLoad != NULL) 
	  _guiMenuLoad->resetGUI();
	
  }
 
  void  PNGUIGameManager::escManager(pnEventType type, PNObject* source, PNEventData* data)
  {
	switch (_currentState)
	{
	case INGAME:
	  escMenu(PN_NUMBER_EVENTS,0,NULL);
	  break;
	case PAUSE:
	  escMenu(PN_NUMBER_EVENTS,0,NULL);
	  break;
	case PAUSE_LOAD:
	  launchMenuLoad(PN_NUMBER_EVENTS,0,NULL);
	  break;
	}
  }

  void  PNGUIGameManager::launchInGame(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_guiGame == NULL)
	  _guiGame = new PNGUIGame();

	switch (_currentState)
	{
	case NONE:
	  _currentState = INGAME;
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_START, 0, data);
	  break;
	case PAUSE_LOAD:
	  hidePrevious();
	  _tmpLoadData = data;
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_END, NULL, NULL);
	  break;
	}
  }

  void  PNGUIGameManager::escMenu(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_guiMenuEsc == NULL)
	  _guiMenuEsc = new PNGUIEscMenu();

	switch (_currentState)
	{
	case NONE:
	  break;
	case PAUSE:
	  hidePrevious();
	  _guiGame->startGUI();
	  _currentState = INGAME;
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
	  break;
	case INGAME:
	  hidePrevious();
	  _guiMenuEsc->startGUI();
	  _currentState = PAUSE;
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_PAUSE, NULL, NULL);
	  break;
	}


	//PNGUIMsgBox* tmp = new PNGUIMsgBox("QUITTER ?", "Voulez-vous quitter\nla partie en cours ?", PNGUIMsgBox::YES_NO, PNGUIMsgBox::MsgBoxCallback(this, &PNGUIGameManager::callbackMenu), _guiGame->getWindow());
	// PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
  }


 void  PNGUIGameManager::launchMenuLoad(pnEventType type, PNObject* source, PNEventData* data)
 {
   if (_guiMenuLoad == NULL)
	 _guiMenuLoad = PNGUIMenuLoad::getInstance();

   switch (_currentState)
   {
   case NONE:
	 break;
   case PAUSE:
	 hidePrevious();
	 _guiMenuLoad->startGUI();
	 _currentState = PAUSE_LOAD;
	 break;
   case PAUSE_LOAD:
	 hidePrevious();
	 _guiMenuEsc->startGUI();
	 _currentState = PAUSE;
	 break;
   }
 }

 void  PNGUIGameManager::launchMenuRoot(pnEventType type, PNObject* source, PNEventData* data)
 {
   if (_currentState == NONE)
	 return;

   if (_currentState == PAUSE)
	 PNGUIMsgBox* tmp = new PNGUIMsgBox("QUITTER ?", "Voulez-vous retourner\nau menu principal ?", PNGUIMsgBox::YES_NO, PNGUIMsgBox::MsgBoxCallback(this, &PNGUIGameManager::callbackMenu), _guiMenuEsc->getWindow());

 }

  void PNGUIGameManager::callbackMenu(const unsigned int& enu)
  {
	if (enu == PNGUIMsgBox::YES)
	{
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_END, NULL, NULL);
	}
  }

  void  PNGUIGameManager::launchQuit(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;

	if (_currentState == PAUSE)
	  PNGUIMsgBox* tmp = new PNGUIMsgBox("QUITTER ?", "Voulez-vous reellement\nquitter ?", PNGUIMsgBox::YES_NO, PNGUIMsgBox::MsgBoxCallback(this, &PNGUIGameManager::callbackQuit), _guiMenuEsc->getWindow());
  }

  void PNGUIGameManager::callbackQuit(const unsigned int& enu)
  {
	if (enu == PNGUIMsgBox::YES)
	{
	  // BOURRIN !!!
	  PNRendererInterface::getInstance()->endRendering();
	}
  }

  void PNGUIGameManager::hidePrevious()
  {
	switch (_currentState) 
	{
	case INGAME:
	  _guiGame->resetGUI();
	break;
	case PAUSE:
	  _guiMenuEsc->resetGUI();
	  break;
	case PAUSE_LOAD:
	  _guiMenuLoad->resetGUI();
	break;
	}
  }

 
  void	PNGUIGameManager::onMLStarted(pnEventType type, PNObject* source, PNEventData* data)
  {

  }

  void	PNGUIGameManager::onMLEnded(pnEventType type, PNObject* source, PNEventData* data)
  {
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_START, 0, NULL);
  }

  void	PNGUIGameManager::onMPStarted(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == INGAME)
	  _guiGame->startGUI();
  }

  void	PNGUIGameManager::onMPEnded(pnEventType type, PNObject* source, PNEventData* data)
  {
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MU_START, 0, NULL);
  }

  void	PNGUIGameManager::onMUStarted(pnEventType type, PNObject* source, PNEventData* data)
  {

  }

  void	PNGUIGameManager::onMUEnded(pnEventType type, PNObject* source, PNEventData* data)
  {
	switch (_currentState)
	{
	case PAUSE:
	  resetAllInstances();
	  _currentState = NONE;
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_MENU_ROOT, NULL, NULL);
	break;
	case PAUSE_LOAD:
	  _currentState = INGAME;
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_START, 0, _tmpLoadData);
	   _tmpLoadData = NULL;
	 break;
	}
  }

  void	PNGUIGameManager::onMPPaused(pnEventType type, PNObject* source, PNEventData* data)
  {

  }

  void	PNGUIGameManager::onMPUnpauseded(pnEventType type, PNObject* source, PNEventData* data)
  {

  }
}
