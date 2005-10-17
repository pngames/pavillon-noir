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
| ______  ___ Graphics ________________________________________________ |
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
|_______________________________________________________________________|

************************************************************************/

#ifndef _PNFOXOPTIONWINDOW_HPP_
# define _PNFOXOPTIONWINDOW_HPP_

#include <fx.h>

#include "PNFoxMainWindow.hpp"
#include "PNFoxOptionsObject.hpp"

namespace PN
{

class	PNFoxOptionWindow : public FXDialogBox 
{
	FXDECLARE(PNFoxOptionWindow)

private:
	PNFoxOptionsObject*		_graphicObj;
	PNFoxOptionsObject*		_audioObj;
	PNFoxOptionsObject*		_inputObj;

protected:
	FXHorizontalFrame*		buttons;

private:
	PNFoxOptionWindow(){}

public:
	PNFoxOptionWindow(FXWindow* owner);
	virtual					~PNFoxOptionWindow();

	virtual void	create();
};

};

#endif /* _PNFOXOPTIONWINDOW_HPP_ */
