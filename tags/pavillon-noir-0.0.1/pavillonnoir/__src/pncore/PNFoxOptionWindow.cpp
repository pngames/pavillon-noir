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

#include "PNFoxOptionWindow.hpp"

FXIMPLEMENT(PNFoxOptionWindow,FXDialogBox,NULL,0)

/*
* Ctor
*/
PNFoxOptionWindow::PNFoxOptionWindow(FXWindow* owner):FXDialogBox(owner,"Options",DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE,0,0,500,300, 0,0,0,0, 4,4)
{
	FXVerticalFrame *vertical = new FXVerticalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame *horizontal = new FXHorizontalFrame(vertical,LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXVerticalFrame *buttons = new FXVerticalFrame(horizontal,LAYOUT_LEFT|LAYOUT_FILL_Y|FRAME_SUNKEN|PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT,0,0,0,0, 0,0,0,0, 0,0);
	FXSwitcher *switcher = new FXSwitcher(horizontal,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);


	// Graphic tab
	FXVerticalFrame* graphic = new FXVerticalFrame(switcher,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0, 0,0);
	new FXLabel(graphic,"Graphic settings",NULL,LAYOUT_LEFT);
	new FXHorizontalSeparator(graphic,SEPARATOR_LINE|LAYOUT_FILL_X);

	FXMatrix *graphicMatrix=new FXMatrix(graphic,3,MATRIX_BY_COLUMNS|PACK_UNIFORM_HEIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,10,0, 6, 6);

	new FXLabel(graphicMatrix,"Full screen :",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X);
	checkButton = new FXCheckButton(graphicMatrix,NULL,NULL,0,LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN,0,0,0,0, 0,0,0,0);
	new FXFrame(graphicMatrix,0);

	//FXGroupBox *gp=new FXGroupBox(group3,"Group Box",LAYOUT_SIDE_TOP|FRAME_GROOVE|LAYOUT_FILL_X, 0,0,0,0);

	//	new FXRadioButton(gp,"Radio &1",&radiotarget,FXDataTarget::ID_OPTION+1,ICON_BEFORE_TEXT|LAYOUT_SIDE_TOP);


	new FXLabel(graphicMatrix,"Resolution :",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X);
	new FXLabel(graphicMatrix,"640 x 480",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X);
	new FXRadioButton(graphicMatrix,NULL,NULL,0,LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN,0,0,0,0, 0,0,0,0);
	new FXFrame(graphicMatrix,0);

	new FXLabel(graphicMatrix,"800 x 600",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X);
	new FXRadioButton(graphicMatrix,NULL,NULL,0,LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN,0,0,0,0, 0,0,0,0);
	new FXFrame(graphicMatrix,1);

	new FXLabel(graphicMatrix,"1024 x 768",NULL,JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_X);
	new FXRadioButton(graphicMatrix,NULL,NULL,0,LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_COLUMN,0,0,0,0, 0,0,0,0);
	new FXFrame(graphicMatrix,1);


	new FXButton(buttons,"GRAPHIC",NULL,switcher,FXSwitcher::ID_OPEN_FIRST,FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);


	// Sound tab
	FXVerticalFrame* sound=new FXVerticalFrame(switcher,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0, 0,0);
	new FXLabel(sound,"Sound settings",NULL,LAYOUT_LEFT);
	new FXHorizontalSeparator(sound,SEPARATOR_LINE|LAYOUT_FILL_X);

	//FXVerticalFrame *sub3=new FXVerticalFrame(sound,LAYOUT_FILL_Y|LAYOUT_FILL_X,0,0,0,0, 0,0,10,0, 0,0);

	new FXButton(buttons,"SOUND",NULL,switcher,FXSwitcher::ID_OPEN_SECOND,FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);



	// Input tab
	FXVerticalFrame* input=new FXVerticalFrame(switcher,LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0, 0,0);
	new FXLabel(input,"Input settings",NULL,LAYOUT_LEFT);
	new FXHorizontalSeparator(input,SEPARATOR_LINE|LAYOUT_FILL_X);
	//FXVerticalFrame *sub4=new FXVerticalFrame(input,LAYOUT_FILL_Y|LAYOUT_FILL_X,0,0,0,0, 0,0,10,0, 0,0);

	new FXButton(buttons,"INPUT",NULL,switcher,FXSwitcher::ID_OPEN_THIRD,FRAME_RAISED|ICON_ABOVE_TEXT|LAYOUT_FILL_Y);


	// Bottom part
	new FXHorizontalSeparator(vertical,SEPARATOR_RIDGE|LAYOUT_FILL_X);
	FXHorizontalFrame *closebox=new FXHorizontalFrame(vertical,LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
	new FXButton(closebox,"&Accept",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	new FXButton(closebox,"&Cancel",NULL,this,FXDialogBox::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	new FXButton(closebox,"&Ok",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
}

/*
* Dtor
*/
PNFoxOptionWindow::~PNFoxOptionWindow()
{	
}
