/*
* PNGUIDeath.hpp
* 
* Description :
* PNGUIDeath declaration
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

#ifndef _PNGUIDEATH_HPP_
#define _PNGUIDEATH_HPP_

#include "myCEGUI.h"
#include "pnevent.h"

namespace PN
{
class PNGUIDeath
{
  /*/////////////////////////////////////////////////////////////////////////////
  /                                   Properties                                /
  /////////////////////////////////////////////////////////////////////////////*/
public:
protected:
private:
  CEGUI::Window*	_pnDeath;
  CEGUI::StaticImage* _deathImage;
  CEGUI::Window* _deathWnd;
  static PNGUIDeath* _instance;
  float	_fadeTimer;
  enum 
  {
	winVisible,
	winHidden,
	winFadeIn,
	winFadeOut
  }	_winState;

  /*/////////////////////////////////////////////////////////////////////////////
  /                                    Methods                                  /
  /////////////////////////////////////////////////////////////////////////////*/
public:
  static PNGUIDeath* getInstance();
  void show();
  void hide();
protected:
private:
  void	update(pnEventType type, PNObject* source, PNEventData* data);


  /*/////////////////////////////////////////////////////////////////////////////
  /                           Constructors / Destructor                         /
  /////////////////////////////////////////////////////////////////////////////*/
public:

protected:
private:
  PNGUIDeath();
  ~PNGUIDeath();
};

}

#endif /*_PNGUIDEATH_HPP_*/