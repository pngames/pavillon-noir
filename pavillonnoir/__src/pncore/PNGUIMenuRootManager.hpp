/*
* PNGUIMenuRootManager.hpp
* 
* Description :
* PNGUIMenuRootManager declaration
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

#ifndef _PNGUIMENUROOTMANAGER_HPP_
# define _PNGUIMENUROOTMANAGER_HPP_

#include "pndefs.h"

#include "pnevent.h"
#include "pnplugins.h"
#include "pnrender.h"

#include "PNGUIMenuRoot.hpp"
#include "PNGUIMenuLoad.hpp"
#include "PNGUIMsgBox.hpp"


namespace PN{


  class PNGUIMenuRootManager
  {
	typedef enum
	{
	  MENUROOT,
	  LOAD,
	  OPTIONS,
	  CREDITS,
	  NEWGAME,
	  QUIT,
	  NONE
	} menuRootStates;
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	menuRootStates _currentState;
  private:
	static PNGUIMenuRootManager*	_instance;
	PNGUIMenuRoot*					_guiMenuRoot;
	PNGUIMenuLoad*					_guiMenuLoad;
	// PNGUIOptions*				_guiMenuOptions;
	// PNGUICredits*				_guiMenuCredits;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIMenuRootManager*	getInstance();
  private:
	void	launchMenuRoot(pnEventType type, PNObject* source, PNEventData* data);
	void	launchMenuLoad(pnEventType type, PNObject* source, PNEventData* data);
	void	launchMenuOptions(pnEventType type, PNObject* source, PNEventData* data);
	void	launchMenuCredits(pnEventType type, PNObject* source, PNEventData* data);
	void	launchNewGame(pnEventType type, PNObject* source, PNEventData* data);
	void	launchLoadGame(pnEventType type, PNObject* source, PNEventData* data);
	void	launchQuit(pnEventType type, PNObject* source, PNEventData* data);
	void	hidePrevious();
	void	deleteAllInstances();
	void	resetAllInstances();
	void	callbackQuit(const unsigned int& enu);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIMenuRootManager();
	~PNGUIMenuRootManager();
  private:

  };
}

#endif /*_PNGUIMENUROOTMANAGER_HPP_*/
