/*
 * PNEDSkyboxPanel.cpp
 * 
 * Description :
 * PNEDSkyboxPanel definition
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

#include "PNEDSkyboxPanel.hpp"

namespace PN { namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

// Map
/*FXDEFMAP(PNEDSkyboxPanel) PNEDSkyboxPanelMap[]={
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_LISTBOX_SEL,PNEDSkyboxPanel::onCmdListBox),
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_ADD,PNEDSkyboxPanel::onCmdAdd),
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_DELETE,PNEDSkyboxPanel::onCmdDelete),
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_SAVE,PNEDSkyboxPanel::onCmdSave),
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_RESET,PNEDSkyboxPanel::onCmdReset),
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_ADDWP,PNEDSkyboxPanel::onAccept),
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_CANCEL,PNEDSkyboxPanel::onCancel),
  FXMAPFUNC(SEL_COMMAND,PNEDSkyboxPanel::ID_ADDOBJECT,PNEDSkyboxPanel::onAddObject)
};*/

//////////////////////////////////////////////////////////////////////////

//FXIMPLEMENT(PNEDSkyboxPanel, FXVerticalFrame, PNEDSkyboxPanelMap, ARRAYNUMBER(PNEDSkyboxPanelMap))
FXIMPLEMENT(PNEDSkyboxPanel, FXVerticalFrame, NULL, 0)

PNEDSkyboxPanel::PNEDSkyboxPanel(FXComposite* p, EDITOR::PNEditor* ed)
: FXVerticalFrame(p, FRAME_THICK | FRAME_RAISED | LAYOUT_FILL_Y | LAYOUT_CENTER_X | LAYOUT_TOP | LAYOUT_LEFT,
				  0, 0, 0, 0, 
				  10, 10, 10, 10)
{
  _ed = ed;

  _grid = new PNPropertiesGrid(this);
}

PNEDSkyboxPanel::~PNEDSkyboxPanel()
{
}

// fox ///////////////////////////////////////////////////////////////////

void
PNEDSkyboxPanel::create()
{
  FXComposite::create();

  _grid->create();
}

// object manipulation ////////////////////////////////////////////////////////////////////////

void
PNEDSkyboxPanel::setObject(PNConfigurableObject* object)
{
  _grid->setObject(object);
}

PNConfigurableObject*	PNEDSkyboxPanel::getObject()
{ 
  return _grid->getObject();
}

// update ////////////////////////////////////////////////////////////////

void
PNEDSkyboxPanel::update()
{
  updateGrid();
  updateView();
}

//////////////////////////////////////////////////////////////////////////

void
PNEDSkyboxPanel::updateGrid()
{
  _grid->update();
}

void
PNEDSkyboxPanel::updateView()
{
  _ed->redraw();
}

//////////////////////////////////////////////////////////////////////////
};};
