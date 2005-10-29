/*
 * PNPropertiesPopup.cpp
 * 
 * Description :
 * PNPropertiesPopup definition
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

#include "PNPropertiesPopup.hpp"
#include "PNFXRealParameter.hpp"


namespace PN {
  //////////////////////////////////////////////////////////////////////////

  // Map
  FXDEFMAP(PNPropertiesPopup) PNPropertiesPopupMap[]={
  FXMAPFUNC(SEL_COMMAND,PNPropertiesPopup::ID_DELETE,PNPropertiesPopup::onDelete)
  };

  //////////////////////////////////////////////////////////////////////////
  FXIMPLEMENT(PNPropertiesPopup,FXDialogBox,PNPropertiesPopupMap,ARRAYNUMBER(PNPropertiesPopupMap));

  PNPropertiesPopup::PNPropertiesPopup(FXWindow* owner) : FXDialogBox(owner,"Properties",DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNPropertiesPopup::PNPropertiesPopup(FXWindow* owner)");
	new FXButton(this,"&Cancel",NULL,this,FXDialogBox::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	new FXButton(this,"&Ok",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
  }

  PNPropertiesPopup::PNPropertiesPopup(FXWindow* owner, PNConfigurableParameter* cp) : FXDialogBox(owner,"Properties",DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE)
  {
	//PNWayPoint* wp = (PNWayPoint*)cp->getElem();
	pnerror(PN_LOGLVL_DEBUG, "PNPropertiesPopup::PNPropertiesPopup(FXWindow* owner, PNConfigurableObject* co)");

	low = new FXHorizontalFrame(this,LAYOUT_SIDE_BOTTOM|FRAME_NONE|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
//	FXButton* c = new FXButton(low,"&Cancel",NULL,this,FXDialogBox::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK); // UNUSED
	new FXButton(low,"&Cancel",NULL,this,FXDialogBox::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK);
//	FXButton* o = new FXButton(low,"&Ok",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK); // UNUSED
	new FXButton(low,"&Ok",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK);
//		FXButton* d = new FXButton(low,"&Delete",NULL,NULL,FXDialogBox::ID_DELETE,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK); // UNUSED	
	new FXButton(low,"&Delete",NULL,NULL,FXDialogBox::ID_DELETE,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK);

	new FXHorizontalSeparator(this,LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|SEPARATOR_GROOVE);

	high = new FXHorizontalFrame(this,LAYOUT_SIDE_BOTTOM|FRAME_NONE|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
	
	//PNFXRealParameter* weight = new PNFXRealParameter(high, );
  }

  PNPropertiesPopup::~PNPropertiesPopup()
  {
  }
  //////////////////////////////////////////////////////////////////////////

  long PNPropertiesPopup::onDelete(FXObject*,FXSelector,void*)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNPropertiesPopup::onDelete(FXObject*,FXSelector,void*)");
	return 1;
  }
};
