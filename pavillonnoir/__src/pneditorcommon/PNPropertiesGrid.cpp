/*
 * PNPropertiesGrid.cpp
 * 
 * Description :
 * PNPropertiesGrid definition
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


#include "pneditorcommon.h"

#include "PNPropertiesGrid.hpp"
#include "PNFXStringParameter.hpp"
#include "PNFXActiveStringParameter.hpp"
#include "PNFXIntParameter.hpp"
#include "PNFXRealParameter.hpp"
#include "PNFXFileParameter.hpp"
#include "PNFXDirParameter.hpp"
#include "PNFXLinksParameter.hpp"
#include "PNFXDialXYZParameter.hpp"
#include "PNFXAnimListParameter.hpp"
#include "PNFXMaterialListParameter.hpp"
#include "PNFXScriptListParameter.hpp"
#include "PNFXStringListParameter.hpp"

namespace PN
{
  // Map
  /*FXDEFMAP(PNPropertiesGrid) PNPropertiesGridMap[]={};*/
  //FXIMPLEMENT(PNPropertiesGrid,FXComposite,PNPropertiesGridMap,ARRAYNUMBER(PNPropertiesGridMap))
  FXIMPLEMENT(PNPropertiesGrid,FXComposite,NULL,0)

PNPropertiesGrid::PNPropertiesGrid(FXComposite* p, PNEditorObject* parent)
: FXMatrix(p, 2, LAYOUT_FILL_X|LAYOUT_FILL_Y|MATRIX_BY_COLUMNS)
{
  _parent = parent;
}

PNPropertiesGrid::~PNPropertiesGrid()
{
}

//////////////////////////////////////////////////////////////////////////

void  PNPropertiesGrid::create()
{
  FXComposite::create();
}

void  PNPropertiesGrid::setObject(PNConfigurableObject* object)
{
  // FIXME : y'a un bug d'affichage ici, lorsqu'on efface les widgets les unes 
  // apres les autres on apercoit un FXDial en haut a gauche de la grille
  while (childAtRowCol(0,0) != NULL)
    delete childAtRowCol(0,0);

  _params.clear();
  _object = object;
  
  for (int idx = 0; idx < _object->getNbParameters(); idx++)
  {
    PNConfigurableParameter* current_param = _object->getParameter(idx);
    new FXLabel(this, current_param->getLabel().c_str(), NULL, JUSTIFY_LEFT|LAYOUT_FILL_X|LAYOUT_CENTER_Y);

	switch (current_param->getType())
	{
	case PN_PARAMTYPE_STRING:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXStringParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_ACTIVESTRING:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXActiveStringParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_INT:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXIntParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_REAL:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXRealParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_FILE:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXFileParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_DIR:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXDirParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_LINK:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXLinksParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_DIALX:
	case PN_PARAMTYPE_DIALY:
	case PN_PARAMTYPE_DIALZ:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXDialXYZParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_ANIMLIST:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXAnimListParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_MATERIALLIST:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXMaterialListParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_SCRIPTLIST:
	  _params.push_back((PNPropertiesGridParameter*)(new PNFXScriptListParameter(this, current_param)));
	  break;
	case PN_PARAMTYPE_STRINGLIST:
		_params.push_back((PNPropertiesGridParameter*)(new PNFXStringListParameter(this, current_param)));
	  break;
	default:
	break;
	}
  }

  create();
  recalc();
}

void PNPropertiesGrid::update()
{
  for (std::list<PNPropertiesGridParameter*>::iterator it = _params.begin(); it != _params.end(); it++)
    (*it)->update();
  return;
}

void PNPropertiesGrid::updateParent()
{
  // BUG : _parent est de type FXFont
  // BUG2 : _parent->update() => PNPropertiesGrid->update() n'est pas appele
  if (_parent != NULL)
  {
	pnerror(PN_LOGLVL_DEBUG, "void PNPropertiesGrid::updateParent() : _parent->update()");
	//_parent->update();
  }
  return;
}

PNConfigurableObject*  PNPropertiesGrid::getObject()
{
  return _object;
}

//////////////////////////////////////////////////////////////////////////
};
