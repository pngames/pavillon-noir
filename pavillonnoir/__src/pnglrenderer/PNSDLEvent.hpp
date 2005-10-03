/*
 * PNSDLEvent.hpp
 * 
 * Description :
 * PNSDLEvent declaration
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

#ifndef _PNSDLEVENT_H_
# define _PNSDLEVENT_H_

#include <SDL/SDL.h>
#include "myCEGUI.h"
#include <map>
#include <set>

#include "pndefs.h"
#include "pnevent.h"
#include "pnplugins.h"
#include "pnrender.h"

#include "PNInfoPanel.hpp"

namespace PN{
  class PNSDLEvent : public PNObject
  {
 
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  private:
	typedef std::map<SDLKey, CEGUI::Key::Scan> InputKeyMap;
	InputKeyMap	_keyMap;

	/// Set of all the keys currently depressed based on buffered input events
	typedef std::set<SDLKey> BufferedKeysDownSet;
	BufferedKeysDownSet mBufferedKeysDown;

	//double _lastTimePulse;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	void	pnSdlEvent(SDL_Event *event);
	void	pninjectTimePulse();
  private:
	void	handleKeyPress(SDL_keysym*	key, bool state);
	void	handleMouse(SDL_MouseMotionEvent* event);
	void	handleKeyMouse(SDL_MouseButtonEvent* event, bool state);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNSDLEvent();
	~PNSDLEvent();
  private: 
  };
}

#endif /* _PNSDLEVENT_H_ */
