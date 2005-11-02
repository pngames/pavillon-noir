/*
 * PNGUIEscMenu.cpp
 * 
 * Description :
 * PNGUIEscMenu definition
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

#include "PNGUIEscMenu.hpp"
#include "pnrender.h"
#include "PNGUIMenuLoad.hpp"
#include "PNGUIGame.hpp"
#include "PNGUIStateManager.hpp"

using namespace PN;

namespace PN {
  PNGUIEscMenu* PNGUIEscMenu::_instance = NULL;

  PNGUIEscMenu::PNGUIEscMenu()
  {
	_mainSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/ESCMenu.layout");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_mainSheet);
	
	setupEventHandlers();
	hide();
  }

  PNGUIEscMenu::~PNGUIEscMenu()
  {
	_mainSheet->destroy();
  }

  PNGUIEscMenu* PNGUIEscMenu::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIEscMenu();
	return _instance;
  }

  void PNGUIEscMenu::startGUI()
  {
	if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::INGAME && 
	  PNGUIStateManager::getInstance()->getSubState() == PNGUIStateManager::NONE)
	{
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_PAUSE, NULL, NULL);
	 
	}
	if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::INGAME )
	  PNGUIStateManager::getInstance()->setSubState(PNGUIStateManager::MENUPAUSE);
	show();

	
  }

  void PNGUIEscMenu::resetGUI()
  {
	hide();
	
  }
  
  CEGUI::Window* PNGUIEscMenu::getWindow()
  {
	return (_mainSheet);
  }

  void PNGUIEscMenu::setupEventHandlers()
  {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/resume")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleResume, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/loadGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleLoadGame, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/mainMenu")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleMainMenu, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/newGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleNewGame, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/quitGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleQuit, this));
  }

  void PNGUIEscMenu::show()
  {
	_mainSheet->show();
	//win->setEnabled(true);
	
	//_mainSheet->setAlwaysOnTop(true);
	_mainSheet->setMutedState(false);
	CEGUI::MouseCursor::getSingleton().show();
  }

  void PNGUIEscMenu::hide()
  {
	_mainSheet->hide();
	_mainSheet->setAlwaysOnTop(false);
	_mainSheet->setMutedState(true);
  }

  bool PNGUIEscMenu::handleResume(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	resetGUI();
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
	PNGUIGame::getInstance()->startGUI();
	//PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_MENU_PAUSE, NULL, NULL);
	return true;
  }

  bool PNGUIEscMenu::handleLoadGame(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	resetGUI();
	PNGUIMenuLoad::getInstance()->startGUI();
	//PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_MENU_LOAD, NULL, NULL);
	//hide();
	return true;
  }

  bool PNGUIEscMenu::handleSaveGame(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	//hide();
	return true;
  }

  bool PNGUIEscMenu::handleOptions(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	//hide();
	return true;
  }

  bool PNGUIEscMenu::handleMainMenu(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	resetGUI();
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
	PNGUIStateManager::getInstance()->LoadManager(NULL, PNGUIStateManager::MENUROOT);
	//PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_QUIT_MENU_ROOT, NULL, NULL);
	return true;
  }

  bool PNGUIEscMenu::handleNewGame(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	//hide();
	return true;
  }

  bool PNGUIEscMenu::handleQuit(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
	PNGUIStateManager::getInstance()->LoadManager(NULL, PNGUIStateManager::NONE);
	//PNRendererInterface::getInstance()->endRendering();
	//PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_QUIT, NULL, NULL);
	
	return true;
  }
};
