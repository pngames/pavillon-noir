/*
 * PNGUIEscMenu.hpp
 * 
 * Description :
 * PNGUIEscMenu declaration
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

#ifndef _PNGUIESCMENU_HPP_
#define _PNGUIESCMENU_HPP_

#include "myCEGUI.h"
#include "pndefs.h"
#include "pnevent.h"
#include "pnrender.h"

namespace PN{
  class PNGUIEscMenu : public PNObject
  {
	/*/////////////////////////////////////////////////////////////////////////////
   /                                   Properties                                /
   /////////////////////////////////////////////////////////////////////////////*/
  public:
	typedef				enum
	{
	  HIDE_RESUME		= 0x000001,
	  HIDE_NEW_GAME		= 0x000001 << 1,
	  HIDE_LOAD_GAME	= 0x000001 << 2,
	  HIDE_SAVE_GAME	= 0x000001 << 3,
	  HIDE_OPTIONS		= 0x000001 << 4,
	  HIDE_MAIN_MENU	= 0x000001 << 5,
	  HIDE_QUIT_GAME	= 0x000001 << 6,
	}					itemHideEscMenu;
	
  private:
	static PNGUIEscMenu* _instance;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIEscMenu*	getInstance();
	void setupEventHandlers();
	void showEscMenu();
	void hideEscMenu();
  private:
	bool handleResume(const CEGUI::EventArgs& e);
	bool handleLoadGame(const CEGUI::EventArgs& e);
	bool handleSaveGame(const CEGUI::EventArgs& e);
	bool handleOptions(const CEGUI::EventArgs& e);
	bool handleMainMenu(const CEGUI::EventArgs& e);
	bool handleNewGame(const CEGUI::EventArgs& e);
	bool handleQuit(const CEGUI::EventArgs& e);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIEscMenu();
  private:
	~PNGUIEscMenu();
  };
}

#endif /*_PNGUIESCMENU_HPP_*/