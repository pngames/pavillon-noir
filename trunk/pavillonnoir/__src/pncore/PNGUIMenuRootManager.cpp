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
#include "PNGUIGame.hpp"

using namespace PN;

namespace PN
{
	PNGUIMenuRootManager*				PNGUIMenuRootManager::_instance = NULL;

	PNGUIMenuRootManager::PNGUIMenuRootManager()
	{
		_guiMenuRoot = NULL;
		//_guiLoadGame = NULL;
		//_guiOptions = NULL;
		//_guiCredits = NULL;
		PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_MENUROOT, EventCallback(this, &PNGUIMenuRootManager::launchMenuRoot));
		//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_LOAD, EventCallback(this, &PNGUIMenuRootManager::launchMenuLoad));
		//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_OPTIONS, EventCallback(this, &PNGUIMenuRootManager::launchMenuOptions));
		//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_CREDITS, EventCallback(this, &PNGUIMenuRootManager::launchMenuCredits));
		PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_NEWGAME, EventCallback(this, &PNGUIMenuRootManager::launchNewGame));
		//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_LOADGAME, EventCallback(this, &PNGUIMenuRootManager::launchLoadGame));
		//PNEventManager::getInstance()->addCallback(PN_EVENT_GUI_QUIT, EventCallback(this, &PNGUIMenuRootManager::launchQuit));
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
			delete _guiMenuRoot;
		/*if (_guiMenuLoad != NULL)
		delete _guiMenuLoad;
		if (_guiMenuOptions != NULL)
		delete _guiMenuOptions;
		if (_guiMenuCredits != NULL)
		delete _guiMenuCredits;*/
	}

	void	PNGUIMenuRootManager::launchNewGame(pnEventType type, PNObject* source, PNEventData* data)
	{
		deleteAllInstances();
		PNGUIGame*		guigame = new PNGUIGame();
		//TODO : send event start game
	}

	void	PNGUIMenuRootManager::launchLoadGame(pnEventType type, PNObject* source, PNEventData* data)
	{
		deleteAllInstances();
		//TODO : send event load game
	}

	void	PNGUIMenuRootManager::launchQuit(pnEventType type, PNObject* source, PNEventData* data)
	{
	
		//TODO : popup QUIT, if yes send event quit
		// if yes : deleteAllInstances();
	}

	

	void	PNGUIMenuRootManager::launchMenuRoot(pnEventType type, PNObject* source, PNEventData* data)
	{
		_currentState = MENUROOT;
		if (_guiMenuRoot == NULL)
			_guiMenuRoot = new PNGUIMenuRoot();
		else
			hidePrevious();
		_guiMenuRoot->show();
	}

	void	PNGUIMenuRootManager::launchMenuLoad(pnEventType type, PNObject* source, PNEventData* data)
	{
		_currentState = LOAD;

		/*if (_guiMenuLoad == NULL)
			_guiMenuLoad = new PNGUIMenuLoad();
		hidePrevious();
		_guiMenuLoad->show();
		*/
	}

	void	PNGUIMenuRootManager::launchMenuOptions(pnEventType type, PNObject* source, PNEventData* data)
	{
		_currentState = OPTIONS;

		/*if (_guiMenuOptions == NULL)
			_guiMenuOptions = new PNGUIMenuOptions();
		hidePrevious();
		_guiMenuOptions->show();
		*/
	}

	void	PNGUIMenuRootManager::launchMenuCredits(pnEventType type, PNObject* source, PNEventData* data)
	{
		_currentState = CREDITS;

		/*if (_guiMenuCredits == NULL)
			_guiMenuCredits = new PNGUIMenuCredits();
		hideMenuPrevious();
		_guiMenuCredits->show();
		*/
	}

	void	PNGUIMenuRootManager::hidePrevious()
	{
		switch (_currentState)
		{
		case MENUROOT:
			_guiMenuRoot->hide();
			break;
		case LOAD:
			//_guiMenuLoad->hide();
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
