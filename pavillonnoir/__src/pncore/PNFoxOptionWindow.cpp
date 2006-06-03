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
#include <fxkeys.h>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnplugins.h"
#include "pnproperties.h"

#include "pcf_format.h"

#include "PNConf.hpp"

#include "PNFoxOptionWindow.hpp"
#include "PNFoxOptionsObject.hpp"
#include "PNPropertiesGrid.hpp"

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
PNFoxOptionWindow::PNFoxOptionWindow(FXWindow* owner)
: FXDialogBox(owner,"Options",DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,0,0,600,400, 0,0,0,0, 4,4)
{
  PNPluginManager*	plist = PNPluginManager::getInstance();

  for (PNPluginManager::iterator it = plist->begin(); it != plist->end(); ++it)
  {
	PNPlugDesc*	desc = (*it)->getPlugDesc();

	for (pnuint i = 0; i < desc->getNbInterface(); ++i)
	{
	  PNInterface*	interf = desc->getInterface(i);

	  if (interf != NULL)
		_interfaces[interf->getName()] = interf;
	}
  }

  unserializeFromPath(PNConf::getInstance()->getConfPath("configuration.pcf"));

  //////////////////////////////////////////////////////////////////////////
  
  // General layout, buttons on the left, options on the right
  _vertical = new FXVerticalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
  
  _horizontal = new FXHorizontalFrame(_vertical, LAYOUT_FILL_X|LAYOUT_FILL_Y);
  _buttons = new FXVerticalFrame(_horizontal, LAYOUT_LEFT|LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT,0,0,0,0, 0,0,0,0, 0,0);
  _switcher = new FXSwitcher(_horizontal, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0,0,0,0, 0,0,0,0);

  // for each plugin, read configuration informations and display them first in switcher (desc) then in tabs (interfaces)
  int switcherID = FXSwitcher::ID_OPEN_FIRST;

  for (PNPluginManager::iterator it = plist->begin(); it != plist->end(); ++it, ++switcherID)
  {
    PNPlugin* pl = (*it);
    PNPlugDesc*	desc = pl->getPlugDesc();
  
	// adds a button to the switcher and a tabbook to display the infos, plugdesc name as button label
    new FXButton(_buttons, desc->getName(), NULL, _switcher, switcherID, FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);
    FXTabBook*  tabbook = new FXTabBook(_switcher, NULL, 0, LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0);

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
		new FXTabItem(tabbook, interf->getLabel().c_str());

		// ConfigurableParameters are displayed in a PropertiesGird, the grid is added to our list so that we 
		// can check its values later when saving configuration
		PNPropertiesGrid* grid = new PNPropertiesGrid(tabbook);
		grid->setObject(interf, false);
	  }
	}
  }

  // Bottom part
  new FXHorizontalSeparator(_vertical,SEPARATOR_RIDGE|LAYOUT_FILL_X);
  FXHorizontalFrame *closebox=new FXHorizontalFrame(_vertical,LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
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

//////////////////////////////////////////////////////////////////////////

void
PNFoxOptionWindow::create()
{
  FXDialogBox::create();
}

//////////////////////////////////////////////////////////////////////////

/*! \brief Saves the preferences using PNConf
* Saves each grid in the option window.
*/
long 
PNFoxOptionWindow::onApply(FXObject* obj, FXSelector sel, void* ptr)
{
  serialize();

  return 1;
}

/*! \brief Saves the preferences using PNConf and closes the window.
*/
long
PNFoxOptionWindow::onAccept(FXObject* obj,FXSelector sel,void* ptr)
{
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
  case KEY_Escape:
	break;

  default:
	FXDialogBox::handle(s, sel, ptr);
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNFoxOptionWindow::getDTD() const
{
  return PCF_XMLDTD;
}

const std::string&
PNFoxOptionWindow::getDTDName() const
{
  return PCF_XMLDTD_NAME;
}

const std::string&
PNFoxOptionWindow::getRootNodeName() const
{
  return PCF_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNFoxOptionWindow::_unserializeNode(xmlNode* node)
{
  if (PCF_OBJECT_XMLDTD_NAME == (const char*)node->name)
	return _interfaces[(const char *)xmlGetProp(node, PCF_XMLPROP_NAME)]->unserializeFromXML(node);

  return PNEC_SUCCESS;
}

pnint
PNFoxOptionWindow::_serializeContent(xmlNode* node)
{
  for (IFaceMap::iterator it = _interfaces.begin(); it != _interfaces.end(); ++it)
	it->second->serializeInXML(node, false);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
