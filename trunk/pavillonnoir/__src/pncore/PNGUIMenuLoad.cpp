/*
* PNGUIMenuLoad.cpp
* 
* Description :
* PNGUIMenuLoad definition
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

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>


#include "PNGUIMenuLoad.hpp"
#include "PNGameEventData.hpp"
#include "PNConsole.hpp"
#include "PNGUIMsgBox.hpp"
#include "pnresources.h"


namespace fs = boost::filesystem;
using namespace PN;

#define RGBA(R,G,B,A) (B+(G<<8)+(R<<16)+(A<<24))

namespace PN
{

  static float val = 0.0f;
  
  PNGUIMenuLoad*				PNGUIMenuLoad::_instance = NULL;
  
  PNGUIMenuLoad::PNGUIMenuLoad()
  {
	_mainSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"./datafiles/layouts/PNMenuLoad.layout"); 
	_cbBox = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"MenuLoad/Listbox");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_mainSheet);
	setupEventHandlers();
	hide();
  }

  PNGUIMenuLoad::~PNGUIMenuLoad()
  {
	_mainSheet->destroy();
  }

  PNGUIMenuLoad*	PNGUIMenuLoad::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIMenuLoad();
	
	return _instance;
  }

  void PNGUIMenuLoad::startGUI()
  {
	show();
  }

  void PNGUIMenuLoad::resetGUI()
  {
	hide();
  }

  void PNGUIMenuLoad::setupEventHandlers()
  {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	wmgr.getWindow((CEGUI::utf8*)"MenuLoad/ButtonOk")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMenuLoad::handleOk, this));
	wmgr.getWindow((CEGUI::utf8*)"MenuLoad/ButtonBack")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMenuLoad::handleBack, this));
	
  }

  void  PNGUIMenuLoad::updateList()
  {

	_cbBox->resetList();

	fs::path mapPath(PN::DEF::mapsFilePath, fs::no_check);
	unsigned long dir_count = 0;

	if (fs::is_directory(mapPath))
	{
	  fs::directory_iterator end_iter;
	  std::string entitiesPath;

	  for ( fs::directory_iterator dir_itr(mapPath); dir_itr != end_iter; ++dir_itr )
	  {
		if ( fs::is_directory( *dir_itr ) && strcmp(dir_itr->leaf().c_str(),".svn") == 1)
		{
		  entitiesPath = PN::DEF::mapsFilePath + dir_itr->leaf();
		  entitiesPath += "/entities.xml";

		  if (fs::exists(entitiesPath) == true)
		  {
			++dir_count;
			CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(dir_itr->leaf().c_str());
			item->setSelectionBrushImage((CEGUI::utf8*)"Vanilla-Images", (CEGUI::utf8*)"GenericBrush");
			item->setSelectionColours(CEGUI::colour(RGBA(159,159,159,255)));
			
			_cbBox->addItem(item);
		  }
		}
	  }
	}
  }

  bool PNGUIMenuLoad::handleOk(const CEGUI::EventArgs& e)
  {
	if (_mainSheet->isMuted() == true)
	  return true;
	if (_cbBox->getFirstSelectedItem() != NULL)
	{
	  PNGameLoadMapEventData* data = new PNGameLoadMapEventData();
	  data->mapName =  DEF::mapsFilePath;
	  data->mapName += _cbBox->getFirstSelectedItem()->getText().c_str();
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_NEW_GAME, 0, data);
	  delete (data);
	}
	else
	  new PNGUIMsgBox("Erreur","Vous devez selectionner\nune sauvegarde.",PNGUIMsgBox::OK, PNGUIMsgBox::MsgBoxCallback(this, &PNGUIMenuLoad::callbackMsgBox),_mainSheet);
	return true;
  }

  void PNGUIMenuLoad::callbackMsgBox(const unsigned int& enu)
  {

  }

  bool PNGUIMenuLoad::handleBack(const CEGUI::EventArgs& e)
  {	
	if (_mainSheet->isMuted() == true)
	  return true;
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GUI_MENU_LOAD, NULL, NULL);
	return true;
  }

  void PNGUIMenuLoad::show()
  {
	_mainSheet->show();
	_mainSheet->setMutedState(false);
	_mainSheet->activate();
	CEGUI::MouseCursor::getSingleton().show();
	updateList();
  }

  void PNGUIMenuLoad::hide()
  {
	_mainSheet->hide();
	_mainSheet->setMutedState(true);
  }

  CEGUI::Window* PNGUIMenuLoad::getWindow()
  {
	return (_mainSheet);
  }
}
