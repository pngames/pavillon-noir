/*
* PNGUIStateManager.hpp
* 
* Description :
* PNGUIStateManager declaration
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

#ifndef _PNGUISTATEMANAGER_HPP_
# define _PNGUISTATEMANAGER_HPP_

#include "pnevent.h"
#include "PNGameEventData.hpp"

namespace PN
{
  class PNGUIStateManager
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	typedef enum
	{
	  MENUROOT,
	  INGAME,
	  MENULOAD,
	  MENUPAUSE,
	  PAUSE_MENULOAD,
	  PAUSE_MENUSAVE,
	  CHAT_WINDOW,
	  INVENTORY_WINDOW,
	  NONE
	} guiStates;
  protected:
  private:
	guiStates				  _currentMainState;
	guiStates				  _currentSubState;
	guiStates				  _nextStep;
	PNGameLoadMapEventData*	  _nextData;
	static PNGUIStateManager* _instance;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIStateManager*	getInstance();
	void  setMainState(guiStates state);
	void  setSubState(guiStates state);
	guiStates	getMainState();
	guiStates	getSubState();
	void		LoadManager(PNGameLoadMapEventData* data, guiStates nextStep);
  protected:
  private:
	 void	  LoadManagerHandler(pnEventType type, PNObject* source, PNEventData* data);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIStateManager();
	~PNGUIStateManager();
  protected:
  private:
	
  };
}

#endif /*_PNGUISTATEMANAGER_HPP_*/
