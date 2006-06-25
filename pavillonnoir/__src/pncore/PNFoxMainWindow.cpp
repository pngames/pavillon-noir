/*
* PNFoxMainWindow.cpp
* 
* Description :
* PNFoxMainWindow definition
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
#include <iostream>

namespace fs = boost::filesystem;

//////////////////////////////////////////////////////////////////////////

#include "pndefs.h"

#include "PNFoxOptionWindow.hpp"

#include "top_image2.h"
#include "pnresources.h"
#include "PNConf.hpp"

#include "PNFoxMainWindow.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

/*!
\brief
Constructor of the main Fox window, creates all widgets.
\param a
FXApp.
\param returnState
Bool set to true if "New Game" is pushed or false when "Quit".
*/
PNFoxMainWindow::PNFoxMainWindow(FXApp* a, bool *returnState):
FXMainWindow(a,"Pavillon Noir",NULL,NULL,DECOR_TITLE|DECOR_MINIMIZE|DECOR_CLOSE|DECOR_BORDER|DECOR_MENU,0,0,0,0)
{
  _imageFile = new FXGIFIcon(getApp(),top_image2);

  _returnState = returnState;

  // Main container
  _contentMain = new FXVerticalFrame(this,LAYOUT_SIDE_TOP|FRAME_NONE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // Set the picture container
  new FXImageView(_contentMain,_imageFile,NULL,0,IMAGEVIEW_CENTER_X|IMAGEVIEW_CENTER_Y|IMAGEVIEW_TOP|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,0,0,312,285);

  // Set the combobox by browsing the map dir
  new FXLabel(_contentMain,"Choose your map :",NULL,JUSTIFY_NORMAL);
  _mapSelector = new FXComboBox(_contentMain,10,NULL,0,COMBOBOX_STATIC|FRAME_SUNKEN|FRAME_THICK|LAYOUT_FIX_WIDTH,0,0,312,45);

  std::string	conffilepath = PNConf::getInstance()->getConfPath("config.cfg");
  char		buffer[1024];
  if (fs::exists(fs::path(conffilepath, fs::native))) {
	std::FILE*	file = fopen(conffilepath.c_str(), "r");
	memset(buffer, 0, sizeof(buffer));
	fread(buffer, 1, 1023, file);
	fclose(file);
  }

  std::string	  tmp(buffer);
  tmp = tmp.substr(0,tmp.find("/"));
  //_mapSelector->findItem(tmp.c_str(),);

  PNResourcesManager* rm = PNResourcesManager::getInstance();

  const PNResourcesManager::DatafileList& dfList = rm->getDatafiles();

  unsigned long dir_count = 0;

  for (PNResourcesManager::DatafileList::const_iterator it = dfList.begin(); it != dfList.end(); ++it)
  {
	const PNResourcesManager::datafile& df = *it;

	fs::path mapPath(rm->getResourcePath(df.id, PNRT_map), fs::no_check);

	if (fs::exists(mapPath) && fs::is_directory(mapPath))
	{
	  fs::directory_iterator end_iter;

	  for (fs::directory_iterator dir_itr(mapPath); dir_itr != end_iter; ++dir_itr)
	  {
		std::cout << dir_itr->leaf() << std::endl;

		if (fs::is_directory(*dir_itr))
		{
		  if (fs::exists(*dir_itr / "entities.xml"))
		  {
			++dir_count;
			_mapSelector->setNumVisible(dir_count);
			_mapSelector->appendItem(dir_itr->leaf().c_str());
		  }
		}
	  }
	}
  }

  int val = _mapSelector->findItem(tmp.c_str(),SEARCH_WRAP);
  if (val == -1)
	val = 0;

  if (_mapSelector->getNumItems() == 0)
	_mapSelector->setCurrentItem(val);

  // Create the 3 main buttons
  FXButton* buttonStart = new FXButton(_contentMain,"&START GAME\tTO LAUNCH GAME",NULL,this,ID_LAUCH_GAME,BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,0,0,312,45);
  buttonStart->setFocus();	
  FXButton* buttonOptions = new FXButton(_contentMain,"&OPTIONS\tTO SET THE OPTIONS",NULL,this,ID_SHOWOPTIONDIALOG,FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,0,0,312,45);
  //buttonOptions->setState(FX::STATE_CHECKED);
  new FXButton(_contentMain,"&QUIT\tTO QUIT THE GAME",NULL,this,ID_CLOSE,FRAME_RAISED|FRAME_THICK|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT,0,0,312,45);
}

/*!
\brief
Destructor of the main Fox window.
*/
PNFoxMainWindow::~PNFoxMainWindow()
{
  delete _mapSelector;
  delete _imageFile;
  delete _contentMain;
}

FXDEFMAP(PNFoxMainWindow) MainConfigWindowMap[]={
  FXMAPFUNC(SEL_COMMAND, PNFoxMainWindow::ID_SHOWOPTIONDIALOG, PNFoxMainWindow::onCmdShowOption),
  FXMAPFUNC(SEL_COMMAND, PNFoxMainWindow::ID_LAUCH_GAME, PNFoxMainWindow::onCmdLauchGame),
};

FXIMPLEMENT(PNFoxMainWindow,FXMainWindow,MainConfigWindowMap,ARRAYNUMBER(MainConfigWindowMap))

/*!
\brief
Called when "New Game" is pushed and write the chosen map in config.cfg file.
Close the main Fox window.
*/
long	PNFoxMainWindow::onCmdLauchGame(FXObject*,FXSelector,void*)
{
  std::string mapPath;

  *_returnState = true;
  mapPath = _mapSelector->getItemText(_mapSelector->getCurrentItem()).text();
  //mapPath += "/entities.xml";

  std::string conffilepath = PNConf::getInstance()->getConfPath("config.cfg");
  std::FILE* configFile = fopen(conffilepath.c_str(), "w");
  fwrite( mapPath.c_str(), sizeof( char ), mapPath.length(), configFile);
  fclose(configFile);

  this->close(0);
  return 0;
}

/*!
\brief
Called when "Options" is pushed, open Options Fox Window.
*/
long	PNFoxMainWindow::onCmdShowOption(FXObject*,FXSelector,void*)
{
  PNFoxOptionWindow	optionWindow(this);

  optionWindow.execute();

  return 1;
}


void	PNFoxMainWindow::create()
{
  FXMainWindow::create();
}

//////////////////////////////////////////////////////////////////////////
};
