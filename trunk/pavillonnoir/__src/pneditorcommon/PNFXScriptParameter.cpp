/*
* PNFXScriptParameter.cpp
* 
* Description :
* PNFXScriptParameter definition
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


#include "pneditorcommon.h"
#include "pnproperties.h"

#include "pnevent.h"

#include "PNPropertiesGrid.hpp"
#include "PNFXScriptParameter.hpp"

using namespace std;
namespace fs = boost::filesystem;

namespace PN {

  //////////////////////////////////////////////////////////////////////////

  // Map
  FXDEFMAP(PNFXScriptParameter) PNFXScriptParameterMap[]={
	FXMAPFUNC(SEL_COMMAND,PNFXScriptParameter::ID_EDIT_TRIGGER,PNFXScriptParameter::onEditTrigger),
	FXMAPFUNC(SEL_COMMAND,PNFXScriptParameter::ID_RESET_TRIGGER,PNFXScriptParameter::onResetTrigger),
	FXMAPFUNC(SEL_COMMAND,PNFXScriptParameter::ID_OK,PNFXScriptParameter::onOK),
	FXMAPFUNC(SEL_COMMAND,PNFXScriptParameter::ID_CANCEL,PNFXScriptParameter::onCancel)
  };

  //////////////////////////////////////////////////////////////////////////

  //FXIMPLEMENT(PNFXScriptParameter,FXHorizontalFrame,PNFXScriptParameterMap,ARRAYNUMBER(PNFXScriptParameterMap))
  FXIMPLEMENT_ABSTRACT(PNFXScriptParameter,FXHorizontalFrame,PNFXScriptParameterMap,ARRAYNUMBER(PNFXScriptParameterMap))

	PNFXScriptParameter::PNFXScriptParameter(FXComposite* p, PNConfigurableParameter* param)
	: FXHorizontalFrame(p), PNPropertiesGridParameter(param)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptParameter::PNFXScriptParameter()");
	_parent = p;
	_param = param;
	_editButton = new FXButton(this, "Edit", NULL, this, ID_EDIT_TRIGGER, FRAME_RAISED | FRAME_THICK);
	_description = new FXLabel(this, param->getAltText().c_str());
  }

  PNFXScriptParameter::~PNFXScriptParameter()
  {
  }

  //////////////////////////////////////////////////////////////////////////

  void	PNFXScriptParameter::create()
  {
	FXHorizontalFrame::create();

	return;
  }

  long	PNFXScriptParameter::onEditTrigger(FXObject* obj,FXSelector sel,void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptParameter::onEditTrigger");
	_editWindow = new FXDialogBox(this, "Edit trigger", DECOR_TITLE|DECOR_BORDER);
	FXVerticalFrame* vframe = new FXVerticalFrame(_editWindow, LAYOUT_FILL_X | LAYOUT_FILL_Y);
	PNPropertiesGrid* grid = new PNPropertiesGrid(vframe);
	_editWindow->create();
	vframe->create();

	grid->setObject((PNConfigurableObject*)_param->getElem());

	new FXHorizontalSeparator(vframe, LAYOUT_FILL_X);
	FXHorizontalFrame*	buttons = new FXHorizontalFrame(vframe,LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXButton(buttons,"&Ok",NULL,this,PNFXScriptParameter::ID_OK,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);
	new FXButton(buttons,"&Cancel",NULL,this,PNFXScriptParameter::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);
	buttons->create();

	_editWindow->execute();
	return 1;
  }

  long	PNFXScriptParameter::onResetTrigger(FXObject* obj,FXSelector sel,void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptParameter::onResetTrigger");
	return 1;
  }

  long	PNFXScriptParameter::onOK(FXObject* obj,FXSelector sel,void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptParameter::onOK");
	_editWindow->getApp()->stopModal(_editWindow, TRUE);
	_editWindow->close();
	this->update();
	return 1;
  }

  long	PNFXScriptParameter::onCancel(FXObject* obj,FXSelector sel,void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptParameter::onCancel");
	_editWindow->onCmdCancel(obj, sel, ptr);
	return 1;
  }

  void	PNFXScriptParameter::update(void)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptParameter::onUpdate");
	return;
  }


  //////////////////////////////////////////////////////////////////////////
};
