/*
 * PNGUIConsole.hpp
 * 
 * Description :
 * PNGUIConsole declaration
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

#ifndef _PNGUICONSOLE_HPP_
# define _PNGUICONSOLE_HPP_

#include "myCEGUI.h"
#include <list>
#include <stdio.h>
//#include <fstream.h>

#include "pndefs.h"
#include "pnevent.h"
#include "PNConsole.hpp"

namespace PN{
  class PNGUIConsole : public PNConsole
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  private:
	CEGUI::Window*		  	  	  		  _pnConsole;
	typedef std::list<CEGUI::ListboxItem*> ConsoleListboxItem;
	ConsoleListboxItem					  _ConsoleListboxItem;
	typedef std::list<std::string>		  ConsoleHistory;
	ConsoleHistory						  _ConsoleHistory;
	ConsoleHistory::iterator			  ite;
	int									  _historyLimit;
	int									  _historyCount;
	pnuint								  _listboxItemSize;
	std::string							  _currentHistoryLine;
	bool								  _consoleVisibility;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static	PNGUIConsole* getInstance();

  private:
	void  _writeLine(const pnchar* message);
	void  _writeError(pnloglevel lvl, const pnchar* message);
	void  _writePerror(pnloglevel lvl, const pnchar* message);

	void  setlistboxItemSize(int size);

	bool  textAccepteddHandler(const CEGUI::EventArgs& e);
	bool  eventKeyPressedHandler(const CEGUI::EventArgs& e);
	bool  textChangedHandler(const CEGUI::EventArgs& e);
	void  consoleVisibility(pnEventType type, PNObject* source, PNEventData* data);
	void  addItemToListBox(CEGUI::ListboxTextItem* item);
	static void  changeAlpha(const std::string& command, std::istream &parameters);
	static void	 quitGame(const std::string& command, std::istream &parameters);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  private:
	PNGUIConsole();
	~PNGUIConsole();

  };
}
#endif /*_PNGUICONSOLE_HPP_*/
