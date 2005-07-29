/*
 * PNInfoPanel.cpp
 * 
 * Description :
 * PNInfoPanel definition
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

#include "PNInfoPanel.hpp"
#include "PNConsole.hpp"

using namespace PN;

PNInfoPanel::PNInfoPanel()										  
{
  _minFPS = 0;
  _maxFPS = 0;
_FPS = 0;

  _updateFreq = 1;
  _updateFreqU = _updateFreq * 1000;

  _skipCount = 0;
  _panelState = 1;
  
  _fpsVisible = false;
  _triVisible = false;
  _panelVisible = false;

  _nbTriBSP = 0;
  _nbTriOBJDYN = 0;
  _nbTriCEGUI = 0;
  _nbTriTOTAL = 0;

  CEGUI::Window* sheet = CEGUI::System::getSingleton().getGUISheet();
  CEGUI::Window* panel = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNInfoPanel.layout");
  sheet->addChildWindow(panel);
  panel->hide();
 

  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/CurrentFPS")->hide();
  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/MinFPS")->hide();
  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/MaxFPS")->hide();

  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriBSP")->hide();
  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriOBJDYN")->hide();
  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriCEGUI")->hide();
  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriTOTAL")->hide();

 //sheet->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNInfoPanel::eventHandler, this));
   PNEventManager::getInstance()->addCallback(PN_EVENT_INFO_PANEL, EventCallback(this, &PNInfoPanel::showTRI));
   PNEventManager::getInstance()->addCallback(PN_EVENT_INFO_PANEL, EventCallback(this, &PNInfoPanel::showFPS));
}

PNInfoPanel::~PNInfoPanel()
{
}

bool PNInfoPanel::eventHandler(const CEGUI::EventArgs& e)
{
 /* std::cout << "infopanel show" << std::endl;
  CEGUI::KeyEventArgs*	me = (CEGUI::KeyEventArgs*)&e;

  if (me->scancode == CEGUI::Key::F12)
	showTRI();

  if (me->scancode == CEGUI::Key::F11)
	showFPS();
*/
  return true;
}

void  PNInfoPanel::runInfoPanel()
{
  if (_fpsVisible == true)
	calculFPS();
  //if (_triVisible == true)
  //	calculTRI();
}

void  PNInfoPanel::setUpdateFreq(int upd)
{
  _updateFreq = upd;
}

void  PNInfoPanel::hide(char* item)
{
  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)item)->hide();
}

void  PNInfoPanel::show(char* item)
{
  CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)item)->show();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FPS

void  PNInfoPanel::ShowHideAllFPS(bool showhide)
{
  if (showhide == true)
  {
	show("PNInfoPanel/CurrentFPS");
	show("PNInfoPanel/MinFPS");
	show("PNInfoPanel/MaxFPS");
  }
  else
  {
	hide("PNInfoPanel/CurrentFPS");
	hide("PNInfoPanel/MinFPS");
	hide("PNInfoPanel/MaxFPS");
  }
}

void PNInfoPanel::showFPS(pnEventType type, PNObject* source, PNEventData* data)
{
  if (_panelVisible == false && _fpsVisible == false)
  {
	show("PNInfoPanel");
	ShowHideAllFPS(true);
	_panelVisible = true;
	_fpsVisible = true;
  }
  else if (_panelVisible == true)
  {
	if (_triVisible == true && _fpsVisible == true)
	{
	  ShowHideAllFPS(false);
	  _fpsVisible = false;
	}
	else if (_triVisible == true && _fpsVisible == false)
	{
	  ShowHideAllFPS(true);
	  _fpsVisible = true;
	}
	else if (_triVisible == false && _fpsVisible == true)
	{
	  ShowHideAllFPS(false);
	  hide("PNInfoPanel");
	  _fpsVisible = false;
	  _panelVisible = false;
	}
  }
}

void PNInfoPanel::calculFPS()
{
  std::stringstream buf;
  static float timer = 0;//(float)SDL_GetTicks();
  //static float timerOld = 0;
  static float nbf = 0;
  static float currentnbf = 0;
  /*static float FPS = 0;
  static float minFPS = 0;
  static float maxFPS = 0;*/
  static bool  firstTime = false;

  if ((SDL_GetTicks() - timer) < _updateFreqU)
	nbf++;
  else
  {
	buf.clear();
	currentnbf = nbf;
	nbf = 0;
	timer = (float)SDL_GetTicks();
	_FPS = (currentnbf / _updateFreq);
	if (_FPS > 0)
	{
	  if (firstTime == false)
	  {
		_minFPS = _FPS;
		_maxFPS = _FPS;
		firstTime = true;
		buf.str("");
		buf << "Min FPS : " << _minFPS;
		CEGUI::Window* guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/MinFPS");
		guiCurr->setText((CEGUI::utf8*)buf.str().c_str());

		buf.str("");
		buf << "Max FPS : " << _minFPS;
		guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/MaxFPS");
		guiCurr->setText((CEGUI::utf8*)buf.str().c_str());
	  }
	  else 
	  {
		if (_FPS < _minFPS)
		{
		  _minFPS = _FPS;
		  buf.str("");
		  buf << "Min FPS : " << _minFPS;
		  //std::cout << buf.str() << std::endl;
		  CEGUI::Window* guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/MinFPS");
		  guiCurr->setText((CEGUI::utf8*)buf.str().c_str());
		}
		if (_FPS > _maxFPS)
		{
		  _maxFPS = _FPS;
		  buf.str("");
		  buf << "Max FPS : " << _maxFPS;
		  //std::cout << buf.str() << std::endl;
		  CEGUI::Window* guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/MaxFPS");
		  guiCurr->setText((CEGUI::utf8*)buf.str().c_str());
		}
	  }
	}
	buf.str("");
	buf << "Current FPS : " << _FPS;
	CEGUI::Window* guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/CurrentFPS");
	guiCurr->setText((CEGUI::utf8*)buf.str().c_str());

	if (_triVisible == true)
	  calculTRI();
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRI

void PNInfoPanel::ShowHideAllTri(bool showhide)
{
  if (showhide == true)
  {
	show("PNInfoPanel/TriBSP");
	show("PNInfoPanel/TriOBJDYN");
	show("PNInfoPanel/TriCEGUI");
	show("PNInfoPanel/TriTOTAL");
  }
  else
  {
	hide("PNInfoPanel/TriBSP");
	hide("PNInfoPanel/TriOBJDYN");
	hide("PNInfoPanel/TriCEGUI");
	hide("PNInfoPanel/TriTOTAL");
  }
}

void PNInfoPanel::showTRI(pnEventType type, PNObject* source, PNEventData* data)
{
  if (_panelVisible == false && _triVisible == false)
  {
	show("PNInfoPanel");
	ShowHideAllTri(true);
	_panelVisible = true;
	_triVisible = true;
  }
  else if (_panelVisible == true)
  {
	if (_triVisible == true && _fpsVisible == true)
	{
	  ShowHideAllTri(false);
	  _triVisible = false;
	}
	else if (_triVisible == false && _fpsVisible == true)
	{	
	   ShowHideAllTri(true);
	  _triVisible = true;
	}
	else if (_triVisible == true && _fpsVisible == false)
	{
	  ShowHideAllTri(false);
	  hide("PNInfoPanel");
	  _triVisible = false;
	  _panelVisible = false;
	}
 }
}

void PNInfoPanel::setTriBSP()
{
  std::stringstream	buf;
  CEGUI::Window*	guiCurr;

  buf << "Tri BSP : " << _nbTriBSP;
  guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriBSP");
  guiCurr->setText((CEGUI::utf8*)buf.str().c_str());
}

void PNInfoPanel::setTriObjDyn()
{
  std::stringstream	buf;
  CEGUI::Window*	guiCurr;

  buf << "Tri Obj Dyn : " << _nbTriOBJDYN;
  guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriOBJDYN");
  guiCurr->setText((CEGUI::utf8*)buf.str().c_str());
}

void PNInfoPanel::setTriCEGUI()
{ 
  std::stringstream	buf;
CEGUI::Window*	guiCurr;

  buf << "Tri CEGUI : " << _nbTriCEGUI;
  guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriCEGUI");
  guiCurr->setText((CEGUI::utf8*)buf.str().c_str());
}

void PNInfoPanel::calculTRI()
{
  std::stringstream	buf;
  CEGUI::Window*	guiCurr;
  int				tmp = 0;
  
  // TRI BSP
	//tmp = BSP.getnbTri();
  if (tmp != _nbTriBSP)
  {
	_nbTriBSP = tmp;
	setTriBSP();
  }
  // TRI OBJ DYN
  //tmp = OBDYN.getnbTri();
  if (tmp != _nbTriOBJDYN)	
  {
	_nbTriOBJDYN = tmp;
	setTriObjDyn();
  }
  // TRI CEGUI
  //tmp = CEGUI.getnbTri();
  if (tmp != _nbTriCEGUI)	
  {
	_nbTriCEGUI = tmp;
	setTriCEGUI();
  }
 

  if (_nbTriTOTAL != (_nbTriOBJDYN+_nbTriOBJDYN+_nbTriCEGUI))
  {
	_nbTriTOTAL = (_nbTriOBJDYN+_nbTriOBJDYN+_nbTriCEGUI);
	buf << "Tri TOTAL :  " << (_nbTriTOTAL);
	guiCurr = CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNInfoPanel/TriTOTAL");
	guiCurr->setText((CEGUI::utf8*)buf.str().c_str());
	//buf.str("");
  }
}


