/*
 * PNFXListParameter.cpp
 * 
 * Description :
 * PNFXListParameter definition
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
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "pneditorcommon.h"
#include "pnproperties.h"
#include "pnimport.h"

#include "PNImportManager.hpp"
#include "PNGLContext.hpp"
#include "PN3DMaterial.hpp"
#include "PN3DObject.hpp"
#include "PN3DModel.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNPropertiesGrid.hpp"
#include "PNFXListParameter.hpp"

using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXListParameter) PNFXListParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND,PNFXListParameter::ID_DELETE,PNFXListParameter::onDelete),
  FXMAPFUNC(SEL_COMMAND,PNFXListParameter::ID_ADD,PNFXListParameter::onAdd)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT_ABSTRACT(PNFXListParameter, FXHorizontalFrame, PNFXListParameterMap, ARRAYNUMBER(PNFXListParameterMap))

PNFXListParameter::PNFXListParameter(FXComposite* p, PNConfigurableParameterList* param)
: FXHorizontalFrame(p), PNPropertiesGridParameterList(param)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXListParameter::PNFXListParameter(FXComposite* p, PNConfigurableParameter* param)");

  _changed = FALSE;
  _listBox = new FXListBox(this, NULL, 0, LAYOUT_FILL_X | FRAME_SUNKEN | FRAME_THICK, 0,0,50,0);
  _buttonAdd = new FXButton(this, "Add", NULL, this, ID_ADD,FRAME_RAISED|FRAME_THICK);
  _buttonDelete = new FXButton(this, "Delete", NULL, this, ID_DELETE,FRAME_RAISED|FRAME_THICK);
}

PNFXListParameter::~PNFXListParameter()
{
  delete _buttonAdd;
  delete _buttonDelete;
  delete _listBox;
}
//////////////////////////////////////////////////////////////////////////

void
PNFXListParameter::create()
{
  FXHorizontalFrame::create();

  _listBox->create();
  _buttonDelete->create();
  _buttonAdd->create();
}

void
PNFXListParameter::update()
{
  FXHorizontalFrame::update();

  _update();

  _buildList();
  _listBox->sortItems();
}

/*
*	Deletes selected object.
*/
long
PNFXListParameter::onDelete(FXObject* obj, FXSelector sel, void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXListParameter::onDelete");

  if (_deleteObject(_listBox->getNumItems() == 0 ? 0 : _listBox->getCurrentItem()))
  {
	sendParamModif();
	update();
  }

  return 1;
}

long
PNFXListParameter::onAdd(FXObject* obj, FXSelector sel, void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXListParameter::onAdd");
  
  if (_addNewObject(_listBox->getNumItems() == 0 ? 0 : _listBox->getCurrentItem()))
  {
	sendParamModif();
	update();
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
};
