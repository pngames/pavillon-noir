/*
* PNGUILoadingScreen.hpp
* 
* Description :
* PNGUILoadingScreen declaration
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

#ifndef _PNGUILOADINGSCREEN_HPP_
#define _PNGUILOADINGSCREEN_HPP_

#include <list>

#include "pnevent.h"
#include "myCEGUI.h"

#include "IPNLoadingProgess.hpp"

namespace PN{
//////////////////////////////////////////////////////////////////////////

class								PNGUILoadingScreen : public IPNLoadingProgess
{
  /*/////////////////////////////////////////////////////////////////////////////
  /                                   Properties                                /
  /////////////////////////////////////////////////////////////////////////////*/
public:
protected:
private:
  static PNGUILoadingScreen*		_instance;
  CEGUI::Window*					_mainSheet;
  //CEGUI::StaticImage*				_backGround;
  CEGUI::FalagardStaticImage*		_backGround;
  CEGUI::ProgressBar*				_progBar;
  //CEGUI::StaticText*				_staticText;
  CEGUI::FalagardStaticText*		_staticText;
  //CEGUI::StaticImage*				_statImg;
  CEGUI::FalagardStaticImage*		_statImg;
  typedef std::list<std::string>	listImagesetAll;
  listImagesetAll					_listImagesetAll;
  /*/////////////////////////////////////////////////////////////////////////////
  /                                    Methods                                  /
  /////////////////////////////////////////////////////////////////////////////*/
public:
  static PNGUILoadingScreen*		getInstance();
  void								startGUI(pnEventType type, PNObject* source, PNEventData* data);
  void								resetGUI(pnEventType type, PNObject* source, PNEventData* data);
  void								show();
  void								hide();
protected:
  void								setRandomBackground();
  void								refresh();
  void								resetScreen();

  /*/////////////////////////////////////////////////////////////////////////////
  /                           Constructors / Destructor                         /
  /////////////////////////////////////////////////////////////////////////////*/
private	:
  PNGUILoadingScreen();
  ~PNGUILoadingScreen();
protected:
private:
};
}

#endif /*_PNGUILOADINGSCREEN_HPP_*/
