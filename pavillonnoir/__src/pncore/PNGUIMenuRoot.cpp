/*
 * PNGUIMenuRoot.cpp
 * 
 * Description :
 * PNGUIMenuRoot definition
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

#include <iostream>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////

#include "pndefs.h"
#include "pnresources.h"
#include "pnevent.h"

//////////////////////////////////////////////////////////////////////////

#include "PNGUIMenuRoot.hpp"
#include "PNGUIGame.hpp"
#include "PNGUIEscMenu.hpp"
#include "PNGUIMsgBox.hpp"

//////////////////////////////////////////////////////////////////////////

#include "PNVideoEventData.hpp"
#include "PNGameEventData.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PN3DCamera.hpp"
#include "PN3DGround.hpp"
#include "PNGameMap.hpp"
#include "PNPhysicsInterface.hpp"
#include "PNConsole.hpp"

////Changes music volume (specific for the demo, please delete later)
#include "PNSoundInterface.hpp"

//////////////////////////////////////////////////////////////////////////

using namespace PN;
namespace fs = boost::filesystem;

namespace PN
{
  PNGUIMenuRoot::PNGUIMenuRoot()
  {
	CEGUI::Imageset* windowsImages = CEGUI::ImagesetManager::getSingleton().createImageset("./datafiles/imagesets/MenuRoot.imageset");

	_mainSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"./datafiles/layouts/MenuRoot.layout"); 
	//	CEGUI::StaticImage* backGround = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().getWindow("MenuRoot/Background");
	//	backGround->disable();
	CEGUI::WindowManager::getSingleton().getWindow("MenuRoot/Load")->disable();
#ifndef WIN32
	CEGUI::WindowManager::getSingleton().getWindow("MenuRoot/Credits")->disable();
#endif
	//CEGUI::WindowManager::getSingleton().getWindow("MenuRoot/Options")->disable();
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_mainSheet);

	PNConsole::addFonction("loadlevel", &PNGUIMenuRoot::loadLevel, "loadlevel [level]");

	setupEventHandlers();	
  }

  PNGUIMenuRoot::~PNGUIMenuRoot()
  {

  }

  void PNGUIMenuRoot::setupEventHandlers()
  {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Exit")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMenuRoot::handleQuit, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/New")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMenuRoot::handleNew, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Load")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMenuRoot::handleLoad, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Credits")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMenuRoot::handleCredits, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Options")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMenuRoot::handleOptions, this));
	
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Credits")->subscribeEvent(CEGUI::ButtonBase::EventMouseEnters, CEGUI::Event::Subscriber(&PNGUIMenuRoot::overButton, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Exit")->subscribeEvent(CEGUI::ButtonBase::EventMouseEnters, CEGUI::Event::Subscriber(&PNGUIMenuRoot::overButton, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/New")->subscribeEvent(CEGUI::ButtonBase::EventMouseEnters, CEGUI::Event::Subscriber(&PNGUIMenuRoot::overButton, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Load")->subscribeEvent(CEGUI::ButtonBase::EventMouseEnters, CEGUI::Event::Subscriber(&PNGUIMenuRoot::overButton, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuRoot/Options")->subscribeEvent(CEGUI::ButtonBase::EventMouseEnters, CEGUI::Event::Subscriber(&PNGUIMenuRoot::overButton, this));
  }

  void  PNGUIMenuRoot::loadLevel(const std::string&, std::istream& i)
  {
	std::string level;
	i >> level;
  }

   bool PNGUIMenuRoot::overButton(const CEGUI::EventArgs& e)
   {
	 PNSoundInterface::getInstance()->playSound("click");
	 return true;
   }

  /*!
  \brief
  Called when the "New Game" button is pressed in CEGUI menu root
  */
  bool PNGUIMenuRoot::handleNew(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	hideMenuRoot();

	//////////////////////////////////////////////////////////////////////////
	// loading

	pnerror(PN_LOGLVL_INFO, "Loading game...");

	// show loading page

	// start loading
	// FIXME -> PNGameMap cr�� par le script
	// FIXME -> lancer l'evenement START

	FILE* file = fopen("config.cfg", "r");
	char  buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	fread(buffer, 1, 1023, file);
	fclose(file);

	////Changes Background music volume (specific for the demo, please delete later)
	//////////////////////////////////////////////////////////////////////////
	PNSoundInterface*	si = PNSoundInterface::getInstance();
	si->changeSoundVolume("theme", 0.0);
	//////////////////////////////////////////////////////////////////////////

    PNGameLoadMapEventData* data = new PNGameLoadMapEventData();
    data->mapName =  DEF::mapsFilePath + buffer;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_START, 0, data);
    //
    //PNGameMap*  map = new PNGameMap();

	//pnint err = map->unserialize(fs::path(DEF::mapsFilePath + "entities-1.0.xml", fs::native));
	//pnint err = map->unserialize(fs::path(DEF::mapsFilePath + "test_model.xml", fs::native));
  
	//if (err != PNEC_SUCCES)
	//  pnerror(PN_LOGLVL_ERROR, "%s : %s", "Error loading level", pnGetErrorString(err));

	//State::gStateMgr->changeState(LOADING);

	//////////////////////////////////////////////////////////////////////////
	// game

	PNGUIGame*		guigame = new PNGUIGame();
	//State::gStateMgr->changeState(GAME);

	return true;
  }

  /*!
  \brief
  Called when the "Quit" button is pressed in CEGUI menu root
  */
  bool PNGUIMenuRoot::handleQuit(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;

	PNRendererInterface::getInstance()->endRendering();
	return true;
  }
 
  bool PNGUIMenuRoot::handleLoad(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;

	//Transition to the load state
	//State::gStateMgr->changeState(LOAD);

	return true;
  }

  /*!
  \brief
  Called when the "Credits" button is pressed in CEGUI menu root
  */
  bool PNGUIMenuRoot::handleCredits(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;

	/*hideMenuRoot();

	if (PN3DGround::getInstance()->unserialize(fs::path(DEF::objectFilePath + "groundLevel3.pno", fs::native)) != PNEC_SUCCES)
	  return false;

	PNGUIGame*		guigame = new PNGUIGame();*/

	if (PNSoundInterface::getInstance() != NULL)
	  PNSoundInterface::getInstance()->changeSoundVolume("theme", 0.0);

	PNVideoEventData* videoEventData = new PNVideoEventData(DEF::videosFilePath + "scene1.avi");
	PNEventManager::getInstance()->addEvent(PN_EVENT_VIDEO_START, NULL, videoEventData);

	return true;
  }

  /*!
  \brief
  Called when the "Options" button is pressed in CEGUI menu root
  */
  bool PNGUIMenuRoot::handleOptions(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;

	PNGUIMsgBox* tmp = new PNGUIMsgBox("test", "test", PNGUIMsgBox::OK_CANCEL, _mainSheet);


	//PNGUIEscMenu* toto =  new PNGUIEscMenu();
	//toto->showEscMenu();
	//PNGUIEscMenu::getInstance()->showEscMenu();
	//hideMenuRoot();
	//CEGUI::System::getSingleton().getGUISheet()->addChildWindow(CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/myschemas/demolayout.xml"));
	//Transition to the Credits state
	//State::gStateMgr->changeState(OPTIONS);
	return true;
  }

  /*!
  \brief
  To hide the CEGUI root menu
  */
  void	PNGUIMenuRoot::hideMenuRoot()
  {
	CEGUI::MouseCursor::getSingleton().hide();
	//CEGUI::Window* win= CEGUI::WindowManager::getSingleton().getWindow("MenuRoot");
	//win->hide();
	_mainSheet->hide();
  }

  /*!
  \brief
  To show the CEGUI root menu
  */
  void	PNGUIMenuRoot::showMenuRoot()
  {
	CEGUI::MouseCursor::getSingleton().show();
	//CEGUI::Window* win= CEGUI::WindowManager::getSingleton().getWindow("MenuRoot");
	//win->show();
	_mainSheet->show();
  }

};
