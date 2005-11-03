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

#include "PNGUILoadingScreen.hpp"

using namespace PN;

#define RGBA(R,G,B,A) (B+(G<<8)+(R<<16)+(A<<24))

namespace PN{

  PNGUILoadingScreen*	PNGUILoadingScreen::_instance = NULL;

  PNGUILoadingScreen::PNGUILoadingScreen()
  {
	if (CEGUI::ImagesetManager::getSingleton().isImagesetPresent("LoadingScreenImage") == false)
	  CEGUI::ImagesetManager::getSingleton().createImageset("./datafiles/imagesets/LoadingBackground.imageset");

	_mainSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNLoadingScreen.layout");
	_backGround = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadingScreen/Background");
	_progBar = (CEGUI::ProgressBar*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadingScreen/ProgressBar");
	_listBox = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"LoadingScreen/ListBox");
	_listBox->setShowVertScrollbar(false);

	_mainSheet->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&PNGUILoadingScreen::handleClickTest, this));

	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_mainSheet);
	//resetProgBar();
	hide();
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

  void PNGUILoadingScreen::refreshScreen(float val, std::string update)
  {
	_progBar->setProgress(val);
	CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(update.c_str());
	item->setSelectionBrushImage((CEGUI::utf8*)"Vanilla-Images", (CEGUI::utf8*)"GenericBrush");
	item->setSelectionColours(CEGUI::colour(RGBA(159,159,159,255)));

	_listBox->addItem(item);
	_listBox->setShowVertScrollbar(false);
  }

  void  PNGUILoadingScreen::setRandomBackground()
  {
  }

 // void  PNGUILoadingScreen::resetScreen()
 // {
	//_progBar->setProgress(0.0f;
 // }

 bool PNGUILoadingScreen::handleClickTest(const CEGUI::EventArgs& e)
 {
   static float tmp = 0.0f;
	static int count = 0;
   std::string str = "ca a clique ";
   if (tmp > 1.0f)
	 tmp = 0.0f;

   	tmp += 0.1f;

	refreshScreen(tmp, str );
	

  return true;
 }

  void	PNGUILoadingScreen::startGUI(pnEventType type, PNObject* source, PNEventData* data)
  {
	//CEGUI::MouseCursor::getSingleton().hide();
	//setRandomBackground();
	show();
	// TODO : voir les conflis avec la console

	//CEGUI::Rect* re = new CEGUI::Rect( CEGUI::Point(0 , 0), CEGUI::Size(0, 0));
	//CEGUI::MouseCursor::getSingleton().setConstraintArea(re);
  }

  void	PNGUILoadingScreen::resetGUI(pnEventType type, PNObject* source, PNEventData* data)
  {
	hide();
  }

  void	PNGUILoadingScreen::show()
  {
	_mainSheet->show();
  }

  void	PNGUILoadingScreen::hide()
  {
	_mainSheet->hide();
  }

}
