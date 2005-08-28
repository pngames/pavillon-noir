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

using namespace PN;

namespace PN {
PNGUIEscMenu*				PNGUIEscMenu::_instance = NULL;

  PNGUIEscMenu::PNGUIEscMenu()
  {
	CEGUI::Window* rootSheet = CEGUI::System::getSingleton().getGUISheet();
	CEGUI::Window* win = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/ESCMenu.layout");
	 rootSheet->addChildWindow(win);
	 win->setVisible(false);

	setupEventHandlers();
  }

  PNGUIEscMenu::~PNGUIEscMenu()
  {
	if (_instance != NULL)
	  delete _instance;
  }
 
  PNGUIEscMenu*	PNGUIEscMenu::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIEscMenu();

	return _instance;
  }

  void PNGUIEscMenu::setupEventHandlers()
  {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/resume")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleResume, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/loadGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleLoadGame, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/saveGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleSaveGame, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/options")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleOptions, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/mainMenu")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleMainMenu, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/newGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleNewGame, this));
	wmgr.getWindow((CEGUI::utf8*)"PNESCMenu/quitGame")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIEscMenu::handleQuit, this));
  }

  void PNGUIEscMenu::showEscMenu()
  {
	CEGUI::Window* win= CEGUI::WindowManager::getSingleton().getWindow("PNESCMenu");
	win->setVisible(true);
	//win->setEnabled(true);
	win->activate();
  }

  void PNGUIEscMenu::hideEscMenu()
  {
	CEGUI::Window* win= CEGUI::WindowManager::getSingleton().getWindow("PNESCMenu");
	win->setVisible(false);
	//win->setEnabled(false);
  }

  bool PNGUIEscMenu::handleResume(const CEGUI::EventArgs& e)
  {
	hideEscMenu();
	return true;
  }

  bool PNGUIEscMenu::handleLoadGame(const CEGUI::EventArgs& e)
  {
	hideEscMenu();
	return true;
  }

  bool PNGUIEscMenu::handleSaveGame(const CEGUI::EventArgs& e)
  {
	hideEscMenu();
	return true;
  }

  bool PNGUIEscMenu::handleOptions(const CEGUI::EventArgs& e)
  {
	hideEscMenu();
	return true;
  }

  bool PNGUIEscMenu::handleMainMenu(const CEGUI::EventArgs& e)
  {
	hideEscMenu();
	return true;
  }

  bool PNGUIEscMenu::handleNewGame(const CEGUI::EventArgs& e)
  {
	hideEscMenu();
	return true;
  }

  bool PNGUIEscMenu::handleQuit(const CEGUI::EventArgs& e)
  {
	PNRendererInterface::getInstance()->endRendering();
	return true;
  }
};
