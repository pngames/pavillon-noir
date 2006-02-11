/*
 * PNSDLEvent.cpp
 * 
 * Description :
 * PNSDLEvent definition
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

#include "myCEGUI.h"

#include <iostream>
#include "PNSDLEvent.hpp"

using namespace PN;

static double _lastTimePulse = 0;
/*!
\brief
Default constructor, creates a map contains correspondences between SDL key codes
and CEGUI Key codes for the entire keyboard.
*/
PNSDLEvent::PNSDLEvent()
{
 /* /// 0 to 9
  _keyMap.insert(InputKeyMap::value_type(SDLK_1, CEGUI::Key::One));
  _keyMap.insert(InputKeyMap::value_type(SDLK_2, CEGUI::Key::Two));
  _keyMap.insert(InputKeyMap::value_type(SDLK_3, CEGUI::Key::Three));
  _keyMap.insert(InputKeyMap::value_type(SDLK_4, CEGUI::Key::Four));
  _keyMap.insert(InputKeyMap::value_type(SDLK_5, CEGUI::Key::Five));
  _keyMap.insert(InputKeyMap::value_type(SDLK_6, CEGUI::Key::Six));
  _keyMap.insert(InputKeyMap::value_type(SDLK_7, CEGUI::Key::Seven));
  _keyMap.insert(InputKeyMap::value_type(SDLK_8, CEGUI::Key::Eight));
  _keyMap.insert(InputKeyMap::value_type(SDLK_9, CEGUI::Key::Nine));
  _keyMap.insert(InputKeyMap::value_type(SDLK_0, CEGUI::Key::Zero));

  // keypad : 0 to 9
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP0, CEGUI::Key::Numpad0));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP1, CEGUI::Key::Numpad1));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP2, CEGUI::Key::Numpad2));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP3, CEGUI::Key::Numpad3));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP4, CEGUI::Key::Numpad4));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP5, CEGUI::Key::Numpad5));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP6, CEGUI::Key::Numpad6));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP7, CEGUI::Key::Numpad7));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP8, CEGUI::Key::Numpad8));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP9, CEGUI::Key::Numpad9));

  // keypad others
  _keyMap.insert(InputKeyMap::value_type(SDLK_NUMLOCK, CEGUI::Key::NumLock));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP_MINUS, CEGUI::Key::Subtract));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP_PLUS, CEGUI::Key::Add));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP_PERIOD, CEGUI::Key::Decimal));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP_EQUALS, CEGUI::Key::NumpadEquals));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP_DIVIDE, CEGUI::Key::Divide));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP_ENTER, CEGUI::Key::NumpadEnter));
  _keyMap.insert(InputKeyMap::value_type(SDLK_KP_MULTIPLY, CEGUI::Key::Multiply));

  // F1 to F15
  _keyMap.insert(InputKeyMap::value_type(SDLK_F1, CEGUI::Key::F1));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F2, CEGUI::Key::F2));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F3, CEGUI::Key::F3));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F4, CEGUI::Key::F4));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F5, CEGUI::Key::F5));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F6, CEGUI::Key::F6));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F7, CEGUI::Key::F7));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F8, CEGUI::Key::F8));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F9, CEGUI::Key::F9));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F10, CEGUI::Key::F10));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F11, CEGUI::Key::F11));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F12, CEGUI::Key::F12));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F13, CEGUI::Key::F13));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F14, CEGUI::Key::F14));
  _keyMap.insert(InputKeyMap::value_type(SDLK_F15, CEGUI::Key::F15));

  // a to z
  _keyMap.insert(InputKeyMap::value_type(SDLK_q, CEGUI::Key::Q));
  _keyMap.insert(InputKeyMap::value_type(SDLK_w, CEGUI::Key::W));
  _keyMap.insert(InputKeyMap::value_type(SDLK_e, CEGUI::Key::E));
  _keyMap.insert(InputKeyMap::value_type(SDLK_r, CEGUI::Key::R));
  _keyMap.insert(InputKeyMap::value_type(SDLK_t, CEGUI::Key::T));
  _keyMap.insert(InputKeyMap::value_type(SDLK_y, CEGUI::Key::Y));
  _keyMap.insert(InputKeyMap::value_type(SDLK_u, CEGUI::Key::U));
  _keyMap.insert(InputKeyMap::value_type(SDLK_i, CEGUI::Key::I));
  _keyMap.insert(InputKeyMap::value_type(SDLK_o, CEGUI::Key::O));
  _keyMap.insert(InputKeyMap::value_type(SDLK_p, CEGUI::Key::P));
  _keyMap.insert(InputKeyMap::value_type(SDLK_a, CEGUI::Key::A));
  _keyMap.insert(InputKeyMap::value_type(SDLK_s, CEGUI::Key::S));
  _keyMap.insert(InputKeyMap::value_type(SDLK_d, CEGUI::Key::D));
  _keyMap.insert(InputKeyMap::value_type(SDLK_f, CEGUI::Key::F));
  _keyMap.insert(InputKeyMap::value_type(SDLK_g, CEGUI::Key::G));
  _keyMap.insert(InputKeyMap::value_type(SDLK_h, CEGUI::Key::H));
  _keyMap.insert(InputKeyMap::value_type(SDLK_j, CEGUI::Key::J));
  _keyMap.insert(InputKeyMap::value_type(SDLK_k, CEGUI::Key::K));
  _keyMap.insert(InputKeyMap::value_type(SDLK_l, CEGUI::Key::L));
  _keyMap.insert(InputKeyMap::value_type(SDLK_z, CEGUI::Key::Z));
  _keyMap.insert(InputKeyMap::value_type(SDLK_x, CEGUI::Key::X));
  _keyMap.insert(InputKeyMap::value_type(SDLK_c, CEGUI::Key::C));
  _keyMap.insert(InputKeyMap::value_type(SDLK_v, CEGUI::Key::V));
  _keyMap.insert(InputKeyMap::value_type(SDLK_b, CEGUI::Key::B));
  _keyMap.insert(InputKeyMap::value_type(SDLK_n, CEGUI::Key::N));
  _keyMap.insert(InputKeyMap::value_type(SDLK_m, CEGUI::Key::M));

  _keyMap.insert(InputKeyMap::value_type(SDLK_ESCAPE, CEGUI::Key::Escape));

  _keyMap.insert(InputKeyMap::value_type(SDLK_MINUS, CEGUI::Key::Minus));
  _keyMap.insert(InputKeyMap::value_type(SDLK_EQUALS, CEGUI::Key::Equals));
  _keyMap.insert(InputKeyMap::value_type(SDLK_BACKSPACE, CEGUI::Key::Backspace));

  _keyMap.insert(InputKeyMap::value_type(SDLK_COMMA, CEGUI::Key::Comma));
  _keyMap.insert(InputKeyMap::value_type(SDLK_PERIOD, CEGUI::Key::Period));

  _keyMap.insert(InputKeyMap::value_type(SDLK_SEMICOLON, CEGUI::Key::Semicolon));
  _keyMap.insert(InputKeyMap::value_type(SDLK_COLON, CEGUI::Key::Colon));
  _keyMap.insert(InputKeyMap::value_type(SDLK_QUOTE, CEGUI::Key::Apostrophe));
  _keyMap.insert(InputKeyMap::value_type(SDLK_BACKQUOTE, CEGUI::Key::Grave));

  _keyMap.insert(InputKeyMap::value_type(SDLK_BACKSLASH, CEGUI::Key::Backslash));

  _keyMap.insert(InputKeyMap::value_type(SDLK_SYSREQ, CEGUI::Key::SysRq));

  _keyMap.insert(InputKeyMap::value_type(SDLK_TAB, CEGUI::Key::Tab));
  _keyMap.insert(InputKeyMap::value_type(SDLK_CAPSLOCK, CEGUI::Key::Capital));
  _keyMap.insert(InputKeyMap::value_type(SDLK_RALT, CEGUI::Key::RightAlt));
  _keyMap.insert(InputKeyMap::value_type(SDLK_LALT, CEGUI::Key::LeftAlt));
  _keyMap.insert(InputKeyMap::value_type(SDLK_LSHIFT, CEGUI::Key::LeftShift));
  _keyMap.insert(InputKeyMap::value_type(SDLK_RSHIFT, CEGUI::Key::RightShift));
  _keyMap.insert(InputKeyMap::value_type(SDLK_LCTRL, CEGUI::Key::LeftControl));
  _keyMap.insert(InputKeyMap::value_type(SDLK_RCTRL, CEGUI::Key::RightControl));

  _keyMap.insert(InputKeyMap::value_type(SDLK_LSUPER, CEGUI::Key::LeftWindows));
  _keyMap.insert(InputKeyMap::value_type(SDLK_RSUPER, CEGUI::Key::RightWindow));
  _keyMap.insert(InputKeyMap::value_type(SDLK_SPACE, CEGUI::Key::Space));
  _keyMap.insert(InputKeyMap::value_type(SDLK_RETURN, CEGUI::Key::Return));



  _keyMap.insert(InputKeyMap::value_type(SDLK_INSERT, CEGUI::Key::Insert));
  _keyMap.insert(InputKeyMap::value_type(SDLK_DELETE, CEGUI::Key::Delete));
  _keyMap.insert(InputKeyMap::value_type(SDLK_HOME, CEGUI::Key::Home));
  _keyMap.insert(InputKeyMap::value_type(SDLK_END, CEGUI::Key::End));
  _keyMap.insert(InputKeyMap::value_type(SDLK_PAGEDOWN, CEGUI::Key::PageDown));
  _keyMap.insert(InputKeyMap::value_type(SDLK_PAGEUP, CEGUI::Key::PageUp));


  _keyMap.insert(InputKeyMap::value_type(SDLK_UP, CEGUI::Key::ArrowUp));
  _keyMap.insert(InputKeyMap::value_type(SDLK_DOWN, CEGUI::Key::ArrowDown));
  _keyMap.insert(InputKeyMap::value_type(SDLK_LEFT, CEGUI::Key::ArrowLeft));
  _keyMap.insert(InputKeyMap::value_type(SDLK_RIGHT, CEGUI::Key::ArrowRight));

  _keyMap.insert(InputKeyMap::value_type(SDLK_PAUSE, CEGUI::Key::Pause));*/
  /*
  SDLK_CLEAR		= 12,

  SDLK_EXCLAIM		= 33,
  SDLK_QUOTEDBL		= 34,
  SDLK_HASH		= 35,
  SDLK_DOLLAR		= 36,
  SDLK_AMPERSAND		= 38,
  SDLK_LEFTPAREN		= 40,
  SDLK_RIGHTPAREN		= 41,
  SDLK_ASTERISK		= 42,
  SDLK_PLUS		= 43,
  SDLK_SLASH		= 47,
  SDLK_LESS		= 60,
  SDLK_GREATER		= 62,
  SDLK_QUESTION		= 63,
  SDLK_AT			= 64,
  SDLK_LEFTBRACKET	= 91,
  SDLK_RIGHTBRACKET	= 93,
  SDLK_CARET		= 94,
  SDLK_UNDERSCORE		= 95,
  SDLK_SCROLLOCK		= 302,
  SDLK_RMETA		= 309,
  SDLK_LMETA		= 310,
  SDLK_MODE		= 313,		 //"Alt Gr" key 
  SDLK_COMPOSE		= 314,	
  SDLK_HELP		= 315,
  SDLK_PRINT		= 316,
  SDLK_BREAK		= 318,
  SDLK_MENU		= 319,
  SDLK_POWER		= 320,		// Power Macintosh power key 
  SDLK_EURO		= 321,		// Some european keyboards 
  SDLK_UNDO		= 322,		*/

  _lastTimePulse = 0.001*static_cast<double>(SDL_GetTicks());

 // PNEventManager::getInstance()->addEvent(PN_EVENT_SDL_GRAB_OFF, this, NULL);
 // PNEventManager::getInstance()->addEvent(PN_EVENT_SDL_GRAB_ON, this, NULL);
 

  SDL_WM_GrabInput(SDL_GRAB_ON);
  SDL_ShowCursor(SDL_DISABLE);

  PNEventManager::getInstance()->sendEvent(PN_EVENT_SDL_GRAB_ON, NULL, NULL);
}

PNSDLEvent::~PNSDLEvent()
{
  //SDL_WM_GrabInput(SDL_GRAB_OFF);
  SDL_WM_GrabInput(SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_ON ? SDL_GRAB_OFF : SDL_GRAB_OFF);
  //SDL_ShowCursor(SDL_ENABLE);
  SDL_ShowCursor(SDL_ShowCursor(SDL_QUERY) == SDL_DISABLE ? SDL_ENABLE : SDL_ENABLE);
}

CEGUI::uint PNSDLEvent::SDLKeyToCEGUIKey(SDLKey key)
{
  using namespace CEGUI;
  switch (key)
  {
  case SDLK_BACKSPACE:    return Key::Backspace;
  case SDLK_TAB:          return Key::Tab;
  case SDLK_RETURN:       return Key::Return;
  case SDLK_PAUSE:        return Key::Pause;
  case SDLK_ESCAPE:       return Key::Escape;
  case SDLK_SPACE:        return Key::Space;
  case SDLK_COMMA:        return Key::Comma;
  case SDLK_MINUS:        return Key::Minus;
  case SDLK_PERIOD:       return Key::Period;
  case SDLK_SLASH:        return Key::Slash;
  case SDLK_0:            return Key::Zero;
  case SDLK_1:            return Key::One;
  case SDLK_2:            return Key::Two;
  case SDLK_3:            return Key::Three;
  case SDLK_4:            return Key::Four;
  case SDLK_5:            return Key::Five;
  case SDLK_6:            return Key::Six;
  case SDLK_7:            return Key::Seven;
  case SDLK_8:            return Key::Eight;
  case SDLK_9:            return Key::Nine;
  case SDLK_COLON:        return Key::Colon;
  case SDLK_SEMICOLON:    return Key::Semicolon;
  case SDLK_EQUALS:       return Key::Equals;
  case SDLK_LEFTBRACKET:  return Key::LeftBracket;
  case SDLK_BACKSLASH:    return Key::Backslash;
  case SDLK_RIGHTBRACKET: return Key::RightBracket;
  case SDLK_a:            return Key::A;
  case SDLK_b:            return Key::B;
  case SDLK_c:            return Key::C;
  case SDLK_d:            return Key::D;
  case SDLK_e:            return Key::E;
  case SDLK_f:            return Key::F;
  case SDLK_g:            return Key::G;
  case SDLK_h:            return Key::H;
  case SDLK_i:            return Key::I;
  case SDLK_j:            return Key::J;
  case SDLK_k:            return Key::K;
  case SDLK_l:            return Key::L;
  case SDLK_m:            return Key::M;
  case SDLK_n:            return Key::N;
  case SDLK_o:            return Key::O;
  case SDLK_p:            return Key::P;
  case SDLK_q:            return Key::Q;
  case SDLK_r:            return Key::R;
  case SDLK_s:            return Key::S;
  case SDLK_t:            return Key::T;
  case SDLK_u:            return Key::U;
  case SDLK_v:            return Key::V;
  case SDLK_w:            return Key::W;
  case SDLK_x:            return Key::X;
  case SDLK_y:            return Key::Y;
  case SDLK_z:            return Key::Z;
  case SDLK_DELETE:       return Key::Delete;
  case SDLK_KP0:          return Key::Numpad0;
  case SDLK_KP1:          return Key::Numpad1;
  case SDLK_KP2:          return Key::Numpad2;
  case SDLK_KP3:          return Key::Numpad3;
  case SDLK_KP4:          return Key::Numpad4;
  case SDLK_KP5:          return Key::Numpad5;
  case SDLK_KP6:          return Key::Numpad6;
  case SDLK_KP7:          return Key::Numpad7;
  case SDLK_KP8:          return Key::Numpad8;
  case SDLK_KP9:          return Key::Numpad9;
  case SDLK_KP_PERIOD:    return Key::Decimal;
  case SDLK_KP_DIVIDE:    return Key::Divide;
  case SDLK_KP_MULTIPLY:  return Key::Multiply;
  case SDLK_KP_MINUS:     return Key::Subtract;
  case SDLK_KP_PLUS:      return Key::Add;
  case SDLK_KP_ENTER:     return Key::NumpadEnter;
  case SDLK_KP_EQUALS:    return Key::NumpadEquals;
  case SDLK_UP:           return Key::ArrowUp;
  case SDLK_DOWN:         return Key::ArrowDown;
  case SDLK_RIGHT:        return Key::ArrowRight;
  case SDLK_LEFT:         return Key::ArrowLeft;
  case SDLK_INSERT:       return Key::Insert;
  case SDLK_HOME:         return Key::Home;
  case SDLK_END:          return Key::End;
  case SDLK_PAGEUP:       return Key::PageUp;
  case SDLK_PAGEDOWN:     return Key::PageDown;
  case SDLK_F1:           return Key::F1;
  case SDLK_F2:           return Key::F2;
  case SDLK_F3:           return Key::F3;
  case SDLK_F4:           return Key::F4;
  case SDLK_F5:           return Key::F5;
  case SDLK_F6:           return Key::F6;
  case SDLK_F7:           return Key::F7;
  case SDLK_F8:           return Key::F8;
  case SDLK_F9:           return Key::F9;
  case SDLK_F10:          return Key::F10;
  case SDLK_F11:          return Key::F11;
  case SDLK_F12:          return Key::F12;
  case SDLK_F13:          return Key::F13;
  case SDLK_F14:          return Key::F14;
  case SDLK_F15:          return Key::F15;
  case SDLK_NUMLOCK:      return Key::NumLock;
  case SDLK_SCROLLOCK:    return Key::ScrollLock;
  case SDLK_RSHIFT:       return Key::RightShift;
  case SDLK_LSHIFT:       return Key::LeftShift;
  case SDLK_RCTRL:        return Key::RightControl;
  case SDLK_LCTRL:        return Key::LeftControl;
  case SDLK_RALT:         return Key::RightAlt;
  case SDLK_LALT:         return Key::LeftAlt;
  case SDLK_LSUPER:       return Key::LeftWindows;
  case SDLK_RSUPER:       return Key::RightWindows;
  case SDLK_SYSREQ:       return Key::SysRq;
  case SDLK_MENU:         return Key::AppMenu;
  case SDLK_POWER:        return Key::Power;
  default:                return 0;
  }
  return 0;
}

/*!
\brief
Function called for every SDL events, call next the right function
depends of the type of the SDL event
\param event
*/
void		PNSDLEvent::pnSdlEvent(SDL_Event* event)
{
  switch (event->type)
  {
  case SDL_KEYDOWN:
	handleKeyPress(&event->key.keysym, true);
	break ;
  case SDL_KEYUP:
	handleKeyPress(&event->key.keysym, false);
	break ;
  case SDL_MOUSEMOTION:
	handleMouse(&event->motion);
	break ;
  case SDL_MOUSEBUTTONUP:
	handleKeyMouse(&event->button, false);
	break ;
  case SDL_MOUSEBUTTONDOWN:
	handleKeyMouse(&event->button, true);
	break ;
  default:
	break ;
  }
}

/*!
\brief
Called when a mouse button is pressed
\param event
\param state
True when the mouse button is down or False when is up
*/
void	PNSDLEvent::handleKeyMouse(SDL_MouseButtonEvent* event, bool state)
{ 
  switch (event->button)
  {
  case SDL_BUTTON_LEFT:
	if (state == false)
	  CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
	else
	  CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
	break;
  case SDL_BUTTON_RIGHT:
	if (state == false)
	{
	/*  SDL_ShowCursor(SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE ? SDL_DISABLE : SDL_ENABLE);
	  if (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_ON)
	  {
		PNEventManager::getInstance()->sendEvent(PN_EVENT_SDL_GRAB_OFF, NULL, NULL);
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	  }
	  else
	  {
		PNEventManager::getInstance()->sendEvent(PN_EVENT_SDL_GRAB_ON, NULL, NULL);
		SDL_WM_GrabInput(SDL_GRAB_ON);
	  }*/
	  CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
	}
	else
	  CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
	break;
  case SDL_BUTTON_MIDDLE:
	if (state == false)
	  CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
	else
	  CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
	break;
  case SDL_BUTTON_WHEELUP:
	CEGUI::System::getSingleton().injectMouseWheelChange(1);
	break;
  case SDL_BUTTON_WHEELDOWN:
	CEGUI::System::getSingleton().injectMouseWheelChange(-1);
	break;
  }
}

/*!
\brief
Called when a key is pressed, some SDL codes must have a manual translation
for CEGUI compatibility
\param keysym
\param state
True when the key is down or False when is up
*/
void	PNSDLEvent::handleKeyPress(SDL_keysym*	keysym, bool state)
{
  if (keysym->sym == SDLK_BACKSPACE)
  {
	if (state == false)
	{
	  SDL_ShowCursor(SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE ? SDL_DISABLE : SDL_ENABLE);
	  if (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_ON)
	  {
		PNEventManager::getInstance()->sendEvent(PN_EVENT_SDL_GRAB_OFF, NULL, NULL);
		SDL_WM_GrabInput(SDL_GRAB_OFF);
	  }
	  else
	  {
		PNEventManager::getInstance()->sendEvent(PN_EVENT_SDL_GRAB_ON, NULL, NULL);
		SDL_WM_GrabInput(SDL_GRAB_ON);
	  }
	}
  }

  if (state == true) 
  {
	 CEGUI::uint kc = SDLKeyToCEGUIKey(keysym->sym);
	 CEGUI::System::getSingleton().injectKeyDown(kc);
	 if ((keysym->unicode & 0xFF80) == 0 && (keysym->unicode > 32))
	 {
	   CEGUI::System::getSingleton().injectChar((char)keysym->unicode & 0x7F);
	 }
	 else 
	 {
	   if((int)keysym->sym >= 256 && (int)keysym->sym <= 265)
	   {	
		 CEGUI::System::getSingleton().injectChar((char)(keysym->sym - 208) & 0x7F);
	   }
	   switch (keysym->sym)
	   {		
	   case 266:
		 CEGUI::System::getSingleton().injectChar(46);
		 break ;
	   case 267:
		 CEGUI::System::getSingleton().injectChar(47);
		 break ;
	   case SDLK_SPACE:
		 CEGUI::System::getSingleton().injectChar((char)(SDLK_SPACE) & 0x7F);
		 break ;
	   default:
		 break ;
	   }
	 }

	 switch (keysym->sym)  
	 {
	 case SDLK_ESCAPE:
	   PNEventManager::getInstance()->sendEvent(PN_EVENT_SDL_ESC, NULL, NULL);
	   break ;
	 case SDLK_F1:
	   PNEventManager::getInstance()->sendEvent(PN_EVENT_CONSOLE, NULL, NULL);
	   break ;
	 case SDLK_F2:
	   PNEventManager::getInstance()->sendEvent(PN_EVENT_CONFPANEL, NULL, NULL);
	   break;
	 case SDLK_F11:
	   PNEventManager::getInstance()->sendEvent(PN_EVENT_INFO_PANEL, NULL, NULL);
	   break ;
	 default:
	   break ;
	 }
  }
  else
  {
	CEGUI::uint kc = SDLKeyToCEGUIKey(keysym->sym);
	CEGUI::System::getSingleton().injectKeyUp(kc);
  }
}

/*!
\brief
Called when the mouse is moving
\param event
*/
void	PNSDLEvent::handleMouse(SDL_MouseMotionEvent* event)
{ 
  CEGUI::System::getSingleton().injectMouseMove((float)event->xrel, (float)event->yrel);
}

/*!
\brief
Inject in CEGUI a time pulse to use timers in CEGUI
*/
void	PNSDLEvent::pninjectTimePulse()
{
  // get current "run-time" in seconds
  double t = 0.001*SDL_GetTicks();

  // inject the time that passed since the last call 
  CEGUI::System::getSingleton().injectTimePulse( float(t-_lastTimePulse) );

  // store the new time as the last time
  _lastTimePulse = t;
}
