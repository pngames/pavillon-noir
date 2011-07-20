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


#ifndef _PNFOXOPTIONWINDOW_HPP_
# define _PNFOXOPTIONWINDOW_HPP_

#include <map>
#include <list>
#include <fx.h>

#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNPropertiesGrid;
class PNInterface;

class						PNFoxOptionWindow : public FXDialogBox, public IPNXMLSerializable
{
  FXDECLARE(PNFoxOptionWindow)

private:

  typedef std::map<std::string, PNInterface*> IFaceMap;
  IFaceMap	_interfaces;

protected:
  FXVerticalFrame*			_vertical;
  FXHorizontalFrame*		_horizontal;
  FXVerticalFrame*			_buttons;
  FXSwitcher*				_switcher;

private:
  PNFoxOptionWindow(){}

public:
  PNFoxOptionWindow(FXWindow* owner);
  virtual					~PNFoxOptionWindow();

  virtual void				create();
  long						onAccept(FXObject* obj, FXSelector sel, void* ptr);
  long						onApply(FXObject* obj, FXSelector sel, void* ptr);
  long						onKeyPress(FXObject*, FXSelector, void* ptr);

public:
  enum {
	ID_APPLY = FXDialogBox::ID_LAST,
	ID_LAST
  };

  //////////////////////////////////////////////////////////////////////////

private:
  pnint						_unserializeNode(xmlNode* node);
  pnint						_serializeContent(xmlNode* node);

public:
  const std::string&		getDTD() const;
  const std::string&		getDTDName() const;
  const std::string&		getRootNodeName() const;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* _PNFOXOPTIONWINDOW_HPP_ */
