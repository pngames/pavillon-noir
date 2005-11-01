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

#include "PNFoxOptionWindow.hpp"
#include "PNFoxOptionsObject.hpp"
#include "pnproperties.h"
#include "PNConfigurableParameter.hpp"
#include "PNFXStringListParameter.hpp"
#include "PNPropertiesGrid.hpp"

namespace PN
{

  // Map
  FXDEFMAP(PNFoxOptionWindow) PNFoxOptionWindowMap[]={
	FXMAPFUNC(SEL_COMMAND,FXDialogBox::ID_ACCEPT,PNFoxOptionWindow::onAccept),
	FXMAPFUNC(SEL_COMMAND,PNFoxOptionWindow::ID_APPLY,PNFoxOptionWindow::onApply)
  };

  //////////////////////////////////////////////////////////////////////////

  FXIMPLEMENT(PNFoxOptionWindow,FXDialogBox,PNFoxOptionWindowMap,ARRAYNUMBER(PNFoxOptionWindowMap))

  //////////////////////////////////////////////////////////////////////////
  
/*
* Ctor
*/
PNFoxOptionWindow::PNFoxOptionWindow(FXWindow* owner):FXDialogBox(owner,"Options",DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,0,0,500,300, 0,0,0,0, 4,4)
{
	// General layout, buttons on the left, options on the right
	FXVerticalFrame* vertical = new FXVerticalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame* horizontal = new FXHorizontalFrame(vertical,LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXVerticalFrame* buttons = new FXVerticalFrame(horizontal,LAYOUT_LEFT|LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT,0,0,0,0, 0,0,0,0, 0,0);
	FXSwitcher* switcher = new FXSwitcher(horizontal,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);

	// probably dirty but the app crashes if we don't do that, eat some fox documentation!
	owner->create();
	this->create();
	vertical->create();
	horizontal->create();
	switcher->create();


	// ** Graphic Tab ** //
	_graphicObj  = new PNFoxOptionsObject("Graphic settings");
	FXVerticalFrame* graphicFrame = new FXVerticalFrame(switcher,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0, 0,0);
	graphicFrame->create();
	new FXLabel(graphicFrame,_graphicObj->getLabel().c_str(),NULL,LAYOUT_LEFT);
	new FXHorizontalSeparator(graphicFrame,SEPARATOR_LINE|LAYOUT_FILL_X);
	new FXButton(buttons,"GRAPHIC",NULL,switcher,FXSwitcher::ID_OPEN_FIRST,FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);

	//// First Parameter : resolutions list
	stringList resolutionsList;
	resolutionsList.push_back("800x600");
	resolutionsList.push_back("1024x768");
	resolutionsList.push_back("1152x864");
	_graphicObj->addParam(new PNConfigurableParameter(_graphicObj, PN_PARAMTYPE_STRINGLIST, &resolutionsList, "Resolution", "Choose your resolution if you dare!", TRUE));
//	PNFXStringListParameter* strlistGraphic = (PNFXStringListParameter*)_graphicObj->getParameter(_graphicObj->getNbParameters()-1);
//	strlistGraphic->setNumVisibleItems(0);
//	strlistGraphic->setLabelsNumChars(0);

	//// Second Parameter : fullscreen
	// TODO : hey! change my type to PN_PARAMTYPE_CHECKBOX, thx (needs a PNFXCheckbox class)
	stringList fullscreenYesNo;
	fullscreenYesNo.push_back("yes");
	fullscreenYesNo.push_back("no");
	_graphicObj->addParam(new PNConfigurableParameter(_graphicObj, PN_PARAMTYPE_STRINGLIST, &fullscreenYesNo, "Fullscreen", "Do you want to play fullscreen ?", TRUE));
	
	// Use a grid to display our parameters
	_graphicGrid = new PNPropertiesGrid(graphicFrame, NULL);
	_graphicGrid->setObject(_graphicObj);


	// ** Audio Tab ** //
	_audioObj  = new PNFoxOptionsObject("Audio settings");
	FXVerticalFrame* audioFrame=new FXVerticalFrame(switcher,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0, 0,0);
	audioFrame->create();
	new FXLabel(audioFrame,_audioObj->getLabel().c_str(),NULL,LAYOUT_LEFT);
	new FXHorizontalSeparator(audioFrame,SEPARATOR_LINE|LAYOUT_FILL_X);
	new FXButton(buttons,"AUDIO",NULL,switcher,FXSwitcher::ID_OPEN_SECOND,FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);

	//// First Parameter : music volume
	// TODO : hey! change my type to PN_PARAMTYPE_DIAL_something..., thx (needs a something class)
	stringList volumeGraduation;
	volumeGraduation.push_back("Mute");
	volumeGraduation.push_back("10");
	volumeGraduation.push_back("20");
	volumeGraduation.push_back("30");
	volumeGraduation.push_back("40");
	volumeGraduation.push_back("50");
	volumeGraduation.push_back("60");
	volumeGraduation.push_back("70");
	volumeGraduation.push_back("80");
	volumeGraduation.push_back("90");
	volumeGraduation.push_back("100");
	_audioObj->addParam(new PNConfigurableParameter(_audioObj, PN_PARAMTYPE_STRINGLIST, &volumeGraduation, "Music volume", "Don't mute me!", TRUE));

	//// Second Parameter : game volume
	// TODO : hey! change my type to PN_PARAMTYPE_DIAL_something..., thx (needs a something class)
	_audioObj->addParam(new PNConfigurableParameter(_audioObj, PN_PARAMTYPE_STRINGLIST, &volumeGraduation, "Game volume", "Don't mute me!", TRUE));

	// Use a grid to display our parameters
	_audioGrid = new PNPropertiesGrid(audioFrame, NULL);
	_audioGrid->setObject(_audioObj);


	// ** Input Tab ** //
	_inputObj  = new PNFoxOptionsObject("Input settings");
	FXVerticalFrame* inputFrame=new FXVerticalFrame(switcher,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0, 0,0);
	inputFrame->create();
	new FXLabel(inputFrame,_inputObj->getLabel().c_str(),NULL,LAYOUT_LEFT);
	new FXHorizontalSeparator(inputFrame,SEPARATOR_LINE|LAYOUT_FILL_X);
	new FXButton(buttons,"INPUT",NULL,switcher,FXSwitcher::ID_OPEN_THIRD,FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);

	stringList inputConfList;
	inputConfList.push_back("Default");
	inputConfList.push_back("Emacs");
	inputConfList.push_back("Killer Profile");
	_inputObj->addParam(new PNConfigurableParameter(_inputObj, PN_PARAMTYPE_STRINGLIST, &inputConfList, "Key binding profile", "Try it!", TRUE));
	
	// peut-etre pas tres utilisable
	// type=table
	//_graphicObj->addParam(new PNConfigurableParameter(_inputObj, PN_PARAMTYPE_STRING , void*elem, "Input Configuration", "Key bindings", TRUE));

	// Use a grid to display our parameters
	_inputGrid = new PNPropertiesGrid(inputFrame, NULL);
	_inputGrid->setObject(_inputObj);


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

void  PNFoxOptionWindow::create()
{
	FXDialogBox::create();
}

/*! \brief Saves the preferences using PNConf
* For each grid in the option window, goes through the different parameters
* and get a string value to save.
*/
long  PNFoxOptionWindow::onApply(FXObject* obj,FXSelector sel,void* ptr)
{
  // TODO : FACTORIZE
  pnerror(PN_LOGLVL_DEBUG, "PNFoxOptionWindow::onApply");
  PNConf* conf = PNConf::getInstance();

  // first the graphical options
  // conf->setComment("First the graphical options")
  saveGrid(_graphicGrid, conf);
  // AUDIO
  saveGrid(_audioGrid, conf);
  // INPUT
  saveGrid(_inputGrid, conf);

  conf->saveConf();

  return 1;
}

void  PNFoxOptionWindow::saveGrid(PNPropertiesGrid* grid, PNConf* conf)
{
  std::list<PNPropertiesGridParameter*> gridParameters = grid->getParams();
  for (std::list<PNPropertiesGridParameter*>::iterator it = gridParameters.begin(); 
	it != gridParameters.end(); it++)
  {
	PNConfigurableParameter* configurableParameter  = (*it)->getParam();
	PNPropertiesGridParameter* gridParameter;
	// first check the type of the GridParameters we're dealing with (float, string, stringlist ...)
	// then call the appropriate method
	switch (configurableParameter->getType())
	{
	case PN_PARAMTYPE_STRINGLIST:
	  gridParameter = (PNFXStringListParameter*)(*it);
	  conf->setKey(gridParameter->getParam()->getLabel().c_str(), gridParameter->getStringValue().c_str());
	  break;
	default:
	  break;
	}
  }
}


/*! \brief Saves the preferences using PNConf and closes the window.
*/
long  PNFoxOptionWindow::onAccept(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFoxOptionWindow::onAccept");
  onApply(obj,sel,ptr);
  return FXDialogBox::onCmdAccept(obj, sel, ptr);
}

};
