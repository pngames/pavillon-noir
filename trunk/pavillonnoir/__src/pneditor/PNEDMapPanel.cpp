/*
* PNEDMapPanel.cpp
* 
* Description :
* PNEDMapPanel definition
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

#include <fxkeys.h>
#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif

#include <iostream>
#include <libxml/xmlreader.h>

/////////////////////////////////////

#include "pnresources.h"
#include "pnxml.h"

/////////////////////////////////////

#include "pneditorcommon.hpp"

/////////////////////////////////////

#include "PNEditor.hpp"

#include "PNEDMapPanel.hpp"


namespace PN { namespace EDITOR {
  //////////////////////////////////////////////////////////////////////////

  FXIMPLEMENT(PNEDMapPanel, FXVerticalFrame, NULL, 0)

	PNEDMapPanel::PNEDMapPanel(FXComposite* p, EDITOR::PNEditor* ed)
	: FXVerticalFrame(p, FRAME_THICK | FRAME_RAISED | LAYOUT_FILL_Y | LAYOUT_CENTER_X | LAYOUT_TOP | LAYOUT_LEFT,
	0, 0, 0, 0, 
	10, 10, 10, 10)
  {
	_ed = ed;

	_grid = new PNPropertiesGrid(this);
  }

  PNEDMapPanel::~PNEDMapPanel()
  {
  }

  // fox ///////////////////////////////////////////////////////////////////

  void	PNEDMapPanel::create()
  {
	FXComposite::create();

	_grid->create();
  }

  // object manipulation ////////////////////////////////////////////////////////////////////////

  void	PNEDMapPanel::setObject(PNConfigurableObject* object)
  {
	_grid->setObject(object);
  }

  PNConfigurableObject*	PNEDMapPanel::getObject()
  { 
	return _grid->getObject();
  }

  // update ////////////////////////////////////////////////////////////////

  void	PNEDMapPanel::update()
  {
	updateGrid();
	updateView();
  }

  //////////////////////////////////////////////////////////////////////////

  void	PNEDMapPanel::updateGrid()
  {
	_grid->update();
  }

  void	PNEDMapPanel::updateView()
  {
	_ed->redraw();
  }

  //////////////////////////////////////////////////////////////////////////
};};
