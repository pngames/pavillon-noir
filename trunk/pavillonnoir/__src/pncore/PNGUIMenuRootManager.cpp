/*
* PNGUIMenuRootManager.cpp
* 
* Description :
* PNGUIMenuRootManager definition
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

#include "PNGUIMenuRootManager.hpp"

using namespace PN;

namespace PN
{
  PNGUIMenuRootManager*				PNGUIMenuRootManager::_instance = NULL;

  PNGUIMenuRootManager::PNGUIMenuRootManager()
  {
	_currentState = NONE;
	_guiMenuRoot = NULL;
	_guiMenuLoad = NULL;
	//_guiOptions = NULL;
	//_guiCredits = NULL;
	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_MENU_ROOT, EventCallback(this, &PNGUIMenuRootManager::launchMenuRoot));
	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_MENU_LOAD, EventCallback(this, &PNGUIMenuRootManager::launchMenuLoad));
	//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_OPTIONS, EventCallback(this, &PNGUIMenuRootManager::launchMenuOptions));
	//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_CREDITS, EventCallback(this, &PNGUIMenuRootManager::launchMenuCredits));
	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_NEW_GAME, EventCallback(this, &PNGUIMenuRootManager::launchNewGame));
	//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_LOADGAME, EventCallback(this, &PNGUIMenuRootManager::launchLoadGame));
	PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_ESC, EventCallback(this, &PNGUIMenuRootManager::launchQuit));
	PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_QUIT, EventCallback(this, &PNGUIMenuRootManager::launchQuit));
  }

  PNGUIMenuRootManager::~PNGUIMenuRootManager()
  {
	deleteAllInstances();
	if (_instance != NULL)
	  delete _instance;
  }

  PNGUIMenuRootManager*	PNGUIMenuRootManager::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIMenuRootManager();

	return _instance;
  }

  void	PNGUIMenuRootManager::deleteAllInstances()
  {
	if (_guiMenuRoot != NULL)
	{
	  delete (_guiMenuRoot);
	  _guiMenuRoot = NULL;
	}
	/*if (_guiMenuLoad != NULL)
	{
	  delete _guiMenuLoad;
	  _guiMenuLoad = NULL;
	}*/
/*	if (_guiMenuOptions != NULL)
	delete _guiMenuOptions;
	if (_guiMenuCredits != NULL)
	delete _guiMenuCredits;*/
  }

  void	PNGUIMenuRootManager::resetAllInstances()
  {
	if (_guiMenuRoot != NULL)
	{
	  _guiMenuRoot->resetGUI();
	}
	if (_guiMenuLoad != NULL)
	{
	   _guiMenuLoad->resetGUI();
	}
	/*	if (_guiMenuOptions != NULL)
	 _guiMenuOptions->resetGUI();
	if (_guiMenuCredits != NULL)
	 _guiMenuCredits->resetGUI();*/
  }

  void	PNGUIMenuRootManager::launchNewGame(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;

	resetAllInstances();

	PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_GAME_START, NULL, data);
	_currentState = NONE;
	//TODO : send event start game
  }

  void	PNGUIMenuRootManager::launchLoadGame(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;

	//deleteAllInstances();
	_currentState = NONE;
	//TODO : send event load game
  }

  void	PNGUIMenuRootManager::launchQuit(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;
	if (_currentState == MENUROOT)
	  PNGUIMsgBox* tmp = new PNGUIMsgBox("QUITTER ?", "Voulez-vous reellement\nquitter ?", PNGUIMsgBox::YES_NO, PNGUIMsgBox::MsgBoxCallback(this, &PNGUIMenuRootManager::callbackQuit), _guiMenuRoot->getWindow());
	//TODO : popup QUIT, if yes send event quit
	// if yes : deleteAllInstances();
  }

  void PNGUIMenuRootManager::callbackQuit(const unsigned int& enu)
  {
	if (enu == PNGUIMsgBox::YES)
	{
	  //deleteAllInstances();
	  PNRendererInterface::getInstance()->endRendering();
	}
  }


  void	PNGUIMenuRootManager::launchMenuRoot(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_guiMenuRoot == NULL)
	  _guiMenuRoot = new PNGUIMenuRoot();

	if (_currentState == NONE) 
	{
	  _guiMenuRoot->startGUI();
	  _currentState = MENUROOT;
	}
  }

  void	PNGUIMenuRootManager::launchMenuLoad(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;
	if (_guiMenuLoad == NULL)
	  _guiMenuLoad = PNGUIMenuLoad::getInstance();

	if (_currentState == LOAD) 
	{
	  hidePrevious();
	  _currentState = MENUROOT;
	  _guiMenuRoot->startGUI();
	}
	else if (_currentState == MENUROOT)
	{
	
	  hidePrevious();
	  _guiMenuLoad->startGUI();
	  _currentState = LOAD;
	}
  }

  void	PNGUIMenuRootManager::launchMenuOptions(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;
	/*if (_guiMenuOptions == NULL)
	_guiMenuOptions = new PNGUIMenuOptions();
	hidePrevious();
	_guiMenuOptions->show();
	*/
	_currentState = OPTIONS;
  }

  void	PNGUIMenuRootManager::launchMenuCredits(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentState == NONE)
	  return;
	/*if (_guiMenuCredits == NULL)
	_guiMenuCredits = new PNGUIMenuCredits();
	hideMenuPrevious();
	_guiMenuCredits->show();
	*/
	_currentState = CREDITS;
  }

  void	PNGUIMenuRootManager::hidePrevious()
  {
	switch (_currentState)
	{
	case MENUROOT:
	  _guiMenuRoot->resetGUI();
	  break;
	case LOAD:
	  _guiMenuLoad->resetGUI();
	  break;
	case OPTIONS:
	  //_guiMenuOptions->hide();
	  break;
	case CREDITS:
	  //_guiMenuCredits->hide();
	  break;
	}
  }

}

