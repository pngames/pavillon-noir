/*
* PNGUIStateManager.cpp
* 
* Description :
* PNGUIStateManager declaration
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

#include "PNGUIStateManager.hpp"
#include "pnevent.h"
#include "pnrender.h"

#include "PNGUIMenuRoot.hpp"
#include "PNGUIGame.hpp"

using namespace PN;

namespace PN
{
  PNGUIStateManager* PNGUIStateManager::_instance = NULL;

  PNGUIStateManager::PNGUIStateManager()
  {
	_currentSubState = NONE;
	_currentMainState = NONE;	
	_nextStep = NONE;
	
	PNEventManager::getInstance()->addCallback(PN_EVENT_ML_STARTED, EventCallback(this, &PNGUIStateManager::LoadManagerHandler));
	PNEventManager::getInstance()->addCallback(PN_EVENT_ML_ENDED, EventCallback(this, &PNGUIStateManager::LoadManagerHandler));

	PNEventManager::getInstance()->addCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PNGUIStateManager::LoadManagerHandler));
	PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PNGUIStateManager::LoadManagerHandler));

	PNEventManager::getInstance()->addCallback(PN_EVENT_MU_STARTED, EventCallback(this, &PNGUIStateManager::LoadManagerHandler));
	PNEventManager::getInstance()->addCallback(PN_EVENT_MU_ENDED, EventCallback(this, &PNGUIStateManager::LoadManagerHandler));
  }

  PNGUIStateManager::~PNGUIStateManager()
  {
  }

  PNGUIStateManager*  PNGUIStateManager::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIStateManager();
	return _instance;
  }

  void	PNGUIStateManager::setMainState(guiStates state)
  {
	_currentMainState = state;
  }

  void	PNGUIStateManager::setSubState(guiStates state)
  {
	_currentSubState = state;
  }

  PNGUIStateManager::guiStates  PNGUIStateManager::getMainState()
  {
	return _currentMainState;
  }

  PNGUIStateManager::guiStates	PNGUIStateManager::getSubState()
  {
	return _currentSubState;
  }

  void		PNGUIStateManager::LoadManager(PNGameLoadMapEventData* data, guiStates nextStep)
  {
	_nextStep = nextStep;
	_nextData = data;
	
	if (_currentMainState == MENUROOT && (_currentSubState == MENULOAD || _currentSubState == NONE))
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_START, 0, data);

	if (_currentMainState == INGAME && (_currentSubState == MENUPAUSE || _currentSubState == PAUSE_MENULOAD))
	   PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_END, 0, NULL);
  }

  void	  PNGUIStateManager::LoadManagerHandler(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_currentMainState == MENUROOT && (_currentSubState == MENULOAD || _currentSubState == NONE))
	{
	  if (type == PN_EVENT_ML_ENDED)
		PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_START, 0, NULL);

	  if (type == PN_EVENT_MP_STARTED)
		PNGUIGame::getInstance()->startGUI();
	}

	if (_currentMainState == INGAME && (_currentSubState == MENUPAUSE || _currentSubState == PAUSE_MENULOAD))
	{
	  if (type == PN_EVENT_MP_ENDED)
		PNEventManager::getInstance()->sendEvent(PN_EVENT_MU_START, 0, NULL);
	  if (type == PN_EVENT_MU_ENDED)
	  {
		if (_nextStep == INGAME)
		  PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_START, 0, _nextData);
		if (_nextStep == MENUROOT)
		  PNGUIMenuRoot::getInstance()->startGUI();
		if (_nextStep == NONE)
		  PNRendererInterface::getInstance()->endRendering();
	  }
	}
  }
}
