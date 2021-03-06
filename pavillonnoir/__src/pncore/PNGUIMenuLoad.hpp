/*
* PNGUIMenuLoad.hpp
* 
* Description :
* PNGUIMenuLoad definition
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

#ifndef _PNGUIMENULOAD_HPP_
# define _PNGUIMENULOAD_HPP_

#include "myCEGUI.h"


namespace PN{

  class PNGUIMenuLoad
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  protected:
  private:
	static PNGUIMenuLoad* _instance;
	CEGUI::Window* _mainSheet;
	CEGUI::Listbox* _cbBox;
	CEGUI::ProgressBar* _progBar;
	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIMenuLoad*	getInstance();
	void show();
	void hide();
	CEGUI::Window* getWindow();
	void callbackMsgBox(const unsigned int& enu);
	void resetGUI();
	void startGUI();
  protected:
  private:
	void setupEventHandlers();
	void updateList();
	bool handleOk(const CEGUI::EventArgs& e);
	bool handleBack(const CEGUI::EventArgs& e);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIMenuLoad();
	~PNGUIMenuLoad();
  protected:
  private:
	
  };

}


#endif /*_PNGUIMENULOAD_HPP_*/
