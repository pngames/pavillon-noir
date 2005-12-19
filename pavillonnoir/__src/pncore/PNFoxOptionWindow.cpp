/*
 * PNFoxOptionWindow.cpp
 * 
 * Description :
 * PNFoxOptionWindow definition
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


#include <list>
#include <string>

#include "pndefs.h"

#include "PNFoxOptionWindow.hpp"
#include "PNFoxOptionsObject.hpp"
#include "pnproperties.h"
#include "PNConfigurableParameter.hpp"
#include "PNFXStringListParameter.hpp"
#include "PNPropertiesGrid.hpp"
#include "pnconfkeys.h"
#include "pnplugins.h"
#include "fxkeys.h"

namespace PN
{

// Map
FXDEFMAP(PNFoxOptionWindow) PNFoxOptionWindowMap[]={
  FXMAPFUNC(SEL_COMMAND,FXDialogBox::ID_ACCEPT,PNFoxOptionWindow::onAccept),
  FXMAPFUNC(SEL_COMMAND,PNFoxOptionWindow::ID_APPLY,PNFoxOptionWindow::onApply),
  FXMAPFUNC(SEL_KEYPRESS,0,PNFoxOptionWindow::onKeyPress)
};

//////////////////////////////////////////////////////////////////////////

FXIMPLEMENT(PNFoxOptionWindow,FXDialogBox,PNFoxOptionWindowMap,ARRAYNUMBER(PNFoxOptionWindowMap))

//////////////////////////////////////////////////////////////////////////

/*
* Ctor
*/
PNFoxOptionWindow::PNFoxOptionWindow(FXWindow* owner):FXDialogBox(owner,"Options",DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,0,0,600,400, 0,0,0,0, 4,4)
{
  _conf = PNConf::getInstance();
  _plist = PNPluginManager::getInstance();
  _gridslist.clear();

  // General layout, buttons on the left, options on the right
  FXVerticalFrame* vertical = new FXVerticalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
/* -- 
  std::string* tmpstr = new std::string("");
  PNFoxOptionsObject* confobject = new PNFoxOptionsObject();
  PNConfigurableParameter* confparam = new PNConfigurableParameter(confobject, PN_PARAMTYPE_EVENTBOX, tmpstr, "Jump", "Jump ?", FALSE);
  confobject->addParam(confparam);
  pnerror(PN_LOGLVL_DEBUG, "PNFoxOptionWindow::PNFoxOptionWindow() : confobject->getNbParameters()=%i", confobject->getNbParameters());

  owner->create();
  this->create();
  vertical->create();

  new FXLabel(vertical, "LABEL1");
  PNPropertiesGrid* grid = new PNPropertiesGrid(vertical, NULL);
  grid->setObject(confobject);
  grid->update();
  new FXLabel(vertical, "LABEL2");
 -- */

/* --  */
  FXHorizontalFrame* horizontal = new FXHorizontalFrame(vertical,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FXVerticalFrame* buttons = new FXVerticalFrame(horizontal,LAYOUT_LEFT|LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT,0,0,0,0, 0,0,0,0, 0,0);
  FXSwitcher* switcher = new FXSwitcher(horizontal,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
	
  // probably dirty but the app crashes if we don't do that, eat some fox documentation!
  owner->create();
  create();
  vertical->create();
  horizontal->create();
  buttons->create();
  switcher->create();

  // for each plugin, read configuration informations and display them first in switcher (desc) then in tabs (interfaces)
  int switcherID = FXSwitcher::ID_OPEN_FIRST;
  for (PNPluginManager::iterator it = _plist->begin(); it != _plist->end(); it++, switcherID++)
  {
    PNPlugin* pl = (*it);
    PNPlugDesc*	desc = pl->getPlugDesc();
  
	// adds a button to the switcher and a tabbook to display the infos, plugdesc name as button label
    new FXButton(buttons,desc->getName(),NULL,switcher,switcherID,FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);
    FXTabBook*  tabbook = new FXTabBook(switcher, NULL, 0, LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0);
    tabbook->create();

	pnerror(PN_LOGLVL_DEBUG, "[PNFoxOptionWindow] adding switcher section %s (version=%i, nb interfaces=%i)", 
		desc->getName(), desc->getVersion(), desc->getNbInterface()); 

    // creates a tab for each Interface
    for (pnuint i = 0; i < desc->getNbInterface(); ++i)
    {
	  PNInterface*	interf = desc->getInterface(i);
  	  if (interf == NULL)
	  {
	    pnerror(PN_LOGLVL_ERROR, "[PNFoxOptionWindow] could not load interface configuration for plugin %s", 
			pl->getPath().native_file_string().c_str()); 
	  }
	  else 
	  {
		// sets the interface's label as the tab name/title
		pnerror(PN_LOGLVL_DEBUG, "[PNFoxOptionWindow] adding tab for interface %s", interf->getLabel().c_str());
		new FXTabItem(tabbook, interf->getLabel().c_str());

		// ConfigurableParameters are displayed in a PropertiesGird, the grid is added to our list so that we 
		// can check its values later when saving configuration
		PNPropertiesGrid* grid = new PNPropertiesGrid(tabbook);
		grid->setObject(interf);
		_gridslist.push_back(grid);
		loadGrid(grid, _conf, interf->getLabel().c_str());
	  }
	}
  }
/* -- */

  // Bottom part
  new FXHorizontalSeparator(vertical,SEPARATOR_RIDGE|LAYOUT_FILL_X);
  FXHorizontalFrame *closebox=new FXHorizontalFrame(vertical,LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
  new FXButton(closebox,"&Ok",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
  new FXButton(closebox,"&Cancel",NULL,this,FXDialogBox::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
  new FXButton(closebox,"&Apply",NULL,this,PNFoxOptionWindow::ID_APPLY,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
}

/*
* Dtor
*/
PNFoxOptionWindow::~PNFoxOptionWindow()
{	
}

// --

void
PNFoxOptionWindow::create()
{
  FXDialogBox::create();
}

/*! \brief Loads the preferences using PNConf
* For the given grid (group of configuration widgets displaying parameters) 
* goes through the different parameters and gets the string value to load.
*/
void 
PNFoxOptionWindow::loadGrid(PNPropertiesGrid* grid, PNConf* conf, const pnchar* section)
{
  PNPropertiesGrid::PNPPList& gridParameters = grid->getParams();

  if (gridParameters.size() != 0)
  {
    for (PNPropertiesGrid::PNPPList::iterator it = gridParameters.begin(); it != gridParameters.end(); it++)
	{
	  PNPropertiesGridParameter* gridParameter = *it;

  	  std::string key = gridParameter->getParam()->getLabel();

	  /*pnbool ok = gridParameter->setStringValue(conf->getKey(key, section, std::string()));
	  if (ok == false)
		pnerror(PN_LOGLVL_DEBUG, "Could not load values for key \"%s\"", key.c_str());*/
	}
  }
  else
  {
	new FXLabel(grid, "No options available for this plugin.");
  }
}

/*! \brief Saves the preferences using PNConf
* For the given grid, goes through the different parameters
* and get a string value to save.
*/
void 
PNFoxOptionWindow::saveGrid(PNPropertiesGrid* grid, PNConf* conf, const pnchar* section)
{
  PNPropertiesGrid::PNPPList& gridParameters = grid->getParams();

  for (PNPropertiesGrid::PNPPList::iterator it = gridParameters.begin(); it != gridParameters.end(); ++it)
  {
	PNPropertiesGridParameter* gridParameter = *it;

	// then call the appropriate method
	conf->setKey(gridParameter->getParam()->getLabel().c_str(), gridParameter->getStringValue().c_str(), section);
  }
}

/*! \brief Saves the preferences using PNConf
* Saves each grid in the option window.
*/
long 
PNFoxOptionWindow::onApply(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFoxOptionWindow::onApply");

  // save each grid in our list (filled earlier in constructor)
  for (std::list<PNPropertiesGrid*>::iterator it = _gridslist.begin(); it != _gridslist.end(); it++)
  {
	PNPropertiesGrid* current_grid = (*it);
	saveGrid(current_grid, _conf, current_grid->getObject()->getLabel().c_str());
  }

  _conf->saveConf();

  return 1;
}

/*! \brief Saves the preferences using PNConf and closes the window.
*/
long
PNFoxOptionWindow::onAccept(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFoxOptionWindow::onAccept");
  onApply(obj,sel,ptr);

  return FXDialogBox::onCmdAccept(obj, sel, ptr);
}

/*! Disables ESC key handling of FSDialogBox.
*/
long	
PNFoxOptionWindow::onKeyPress(FXObject* s,FXSelector sel,void* ptr)
{
  FXEvent* event=(FXEvent*)ptr;

  switch (event->code)
  {
  case KEY_Escape: break;
  default: FXDialogBox::handle(s, sel, ptr);
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
};
