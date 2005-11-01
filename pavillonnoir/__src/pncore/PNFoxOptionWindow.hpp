/*
 * PNFoxOptionWindow.hpp
 * 
 * Description :
 * PNFoxOptionWindow declaration
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


/************************************************************************
 _______________________________________________________________________
| ______  ___ Graphics Settings _______________________________________ |
||      |                                                               |
|| Graph|  Resolution                      FXLISTBOX	                |
||      |  Fullscreen                      FXCHECKBOX                   |
||______|                                                               |
||      |                                                               |
|| Sound|                                                               |
||      |                                                               |
||______|                                                               |
||      |                                                               |
|| Input|                                                               |
||      |                                                               |
||______|                                                               |
|  ___________________________________________________________________  |
|                                       ________   ________   ________  |
|                                      |___OK___| |_CANCEL_| |_ACCEPT_| |
|_______________________________________________________________________|

 - For each tab (Graph, Sound, Input, ...) a PNFoxOptionsObject is created.
 - These objects contain parameters stored in a vector.
 - The vector is displayed in a FXMatrix-like object : PNPropertiesGrid.
 - Each parameter contains some required informations such as the parent 
 object, a type identifier, a name (or label), a tooltip text, ...

************************************************************************/

#ifndef _PNFOXOPTIONWINDOW_HPP_
# define _PNFOXOPTIONWINDOW_HPP_

#include <fx.h>

#include "PNFoxMainWindow.hpp"
#include "PNFoxOptionsObject.hpp"
#include "PNPropertiesGrid.hpp"
#include "PNConf.hpp"

namespace PN
{

class	PNFoxOptionWindow : public FXDialogBox 
{
	FXDECLARE(PNFoxOptionWindow)

private:
	PNFoxOptionsObject*		_graphicObj;
	PNFoxOptionsObject*		_audioObj;
	PNFoxOptionsObject*		_inputObj;
	
	PNPropertiesGrid*		_graphicGrid;
	PNPropertiesGrid*		_audioGrid;
	PNPropertiesGrid*		_inputGrid;

protected:
	FXHorizontalFrame*		buttons;

private:
	PNFoxOptionWindow(){}

public:
	PNFoxOptionWindow(FXWindow* owner);
	virtual					~PNFoxOptionWindow();

	virtual void	create();
	long			onAccept(FXObject* obj,FXSelector sel,void* ptr);
	long			onApply(FXObject* obj,FXSelector sel,void* ptr);
	
	void			saveGrid(PNPropertiesGrid* grid, PNConf* conf);

public:
  enum {
	ID_APPLY = FXDialogBox::ID_LAST,
	ID_LAST
  };
};

};

#endif /* _PNFOXOPTIONWINDOW_HPP_ */
