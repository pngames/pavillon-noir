/*
* PNGUILoadingScreen.cpp
* 
* Description :
* PNGUILoadingScreen declaration
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

//#include <stdlib.h>
#include <time.h>

#include "pndefs.h"
#include "pnrender.h"
#include "PNGameEventData.hpp"
#include "PNGUILoadingScreen.hpp"

using namespace PN;

#define RGBA(R,G,B,A) (B+(G<<8)+(R<<16)+(A<<24))

namespace PN{
//////////////////////////////////////////////////////////////////////////

PNGUILoadingScreen*	PNGUILoadingScreen::_instance = NULL;

PNGUILoadingScreen::PNGUILoadingScreen()
{
  srand((pnuint)time(0));

  CEGUI::Imageset* imgSet = CEGUI::ImagesetManager::getSingleton().getImageset("LoadingScreenImages");
  CEGUI::Imageset::ImageIterator imgSetIte = imgSet->getIterator();

  while (!imgSetIte.isAtEnd())
  {
	std::string tmp = (*imgSetIte).getName().c_str();
	if (tmp != "LoadingScreenImages/chargement")
	  _listImagesetAll.push_back(tmp);
	imgSetIte++;
  }

  _mainSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNLoadingScreen.layout");
  _backGround = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadingScreen/Background");
  _progBar = (CEGUI::ProgressBar*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadingScreen/ProgressBar");
  _staticText = (CEGUI::StaticText*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadingScreen/StaticText");
  

  _statImg = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"TaharezLook/StaticImage", "LoadingScreenImages/randomBack");
  _mainSheet->addChildWindow(_statImg);

  CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_mainSheet);
  hide();

  PNEventManager::getInstance()->addCallback(PN_EVENT_ML_STARTED, EventCallback(this, &PNGUILoadingScreen::startGUI));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MU_STARTED, EventCallback(this, &PNGUILoadingScreen::startGUI));

  PNEventManager::getInstance()->addCallback(PN_EVENT_ML_ENDED, EventCallback(this, &PNGUILoadingScreen::resetGUI));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MU_ENDED, EventCallback(this, &PNGUILoadingScreen::resetGUI));

  addCallback(PN_EVENT_ML_STEP);
  addCallback(PN_EVENT_MU_STEP);
}

PNGUILoadingScreen::~PNGUILoadingScreen()
{
  _mainSheet->destroy();
}

PNGUILoadingScreen* PNGUILoadingScreen::getInstance()
{
  if (_instance == NULL)
	_instance = new PNGUILoadingScreen();

  return _instance;
}

//////////////////////////////////////////////////////////////////////////

void 
PNGUILoadingScreen::setRandomBackground()
{
  int i = 0;
  listImagesetAll::iterator ite = _listImagesetAll.begin();

  int val = (rand() % (_listImagesetAll.size()-1));

  while (i != val) 
  {
	ite++;
	i++;
  }

  CEGUI::Image img = (CEGUI::Image)CEGUI::ImagesetManager::getSingleton().getImageset("LoadingScreenImages")->getImage((*ite).c_str());

  float imgWidth = img.getWidth();
  float imgHeight = img.getHeight();
  float screenHeight = CEGUI::System::getSingleton().getRenderer()->getHeight();
  float screenWidth = CEGUI::System::getSingleton().getRenderer()->getWidth();

  float sizeWidth = 0.0f;
  float sizeHeight = 0.0f;
  float posX = 0.0;
  float posY = 0.0;

  if (imgHeight >= imgWidth) 
  {
	sizeHeight = 0.63;
	sizeWidth = imgWidth * sizeHeight / imgHeight / 1.33;
	posX = (1 - sizeWidth) /2;
	posY = 0.0f;

  }
  else if (imgHeight < imgWidth)
  {
	sizeWidth = 1;
	sizeHeight = imgHeight * sizeWidth / imgWidth * 1.33; 
	if (sizeHeight > 0.63)
	{
	  sizeHeight = 0.63;
	  sizeWidth = imgWidth * sizeHeight / imgHeight / 1.33;
	  posX = (1 - sizeWidth) /2;
	  posY = 0.0f;
	}
	else
	{
	  posX = 0.0;
	  posY = (0.63 - sizeHeight) /2;
	}
  }

  _statImg->setImage("LoadingScreenImages", (*ite).c_str());
  _statImg->setSize(CEGUI::Size(sizeWidth, sizeHeight));
  _statImg->setPosition(CEGUI::Point(posX, posY));
  _statImg->setFrameEnabled(false);
  _statImg->setBackgroundEnabled(false);
  _statImg->disable();
  _statImg->show();
}

void 
PNGUILoadingScreen::resetScreen()
{
  reinit();

  _progBar->setProgress(_step);
  _statImg->hide();
  _staticText->setText("");
}

void	
PNGUILoadingScreen::show()
{
  _mainSheet->show();
}

void	
PNGUILoadingScreen::hide()
{
  _mainSheet->hide();
}

//////////////////////////////////////////////////////////////////////////

void	
PNGUILoadingScreen::startGUI(pnEventType type, PNObject* source, PNEventData* data)
{
  CEGUI::MouseCursor::getSingleton().hide();
  resetScreen();
  setRandomBackground();
  show();

  PNEventManager::getInstance()->sendEvent(PN_EVENT_RU_END, 0, NULL);
}

void
PNGUILoadingScreen::resetGUI(pnEventType type, PNObject* source, PNEventData* data)
{
  PNRendererInterface::getInstance()->flushSDLEvents();
  hide();
}

//////////////////////////////////////////////////////////////////////////

void
PNGUILoadingScreen::refresh()
{
  _progBar->setProgress(_step);
  _staticText->setText(_label.c_str());

  PNEventManager::getInstance()->sendEvent(PN_EVENT_RU_END, 0, NULL);
}

//////////////////////////////////////////////////////////////////////////
};
