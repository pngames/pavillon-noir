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
#include "PNFXIntParameter.hpp"
#include "PNFXUIntParameter.hpp"
#include "PNFXRealParameter.hpp"
#include "PNFXFileParameter.hpp"
#include "PNFXDirParameter.hpp"
#include "PNFXLinksParameter.hpp"
#include "PNFXDialXYZParameter.hpp"
#include "PNFXEventBoxParameter.hpp"
#include "PNFXAnimListParameter.hpp"
#include "PNFXMaterialListParameter.hpp"
#include "PNFXScriptListParameter.hpp"
#include "PNFXStringListParameter.hpp"
#include "PNFXCheckButtonParameter.hpp"
#include "PNFXVPPNObjectParameter.hpp"
#include "PNFXDefaultParameter.hpp"
//#include "PNFXScriptParameter.hpp"
#include "PNFXSeparatorParameter.hpp"


namespace PN {
//////////////////////////////////////////////////////////////////////////

  // Map
  /*FXDEFMAP(PNPropertiesGrid) PNPropertiesGridMap[]={};*/
  //FXIMPLEMENT(PNPropertiesGrid,FXComposite,PNPropertiesGridMap,ARRAYNUMBER(PNPropertiesGridMap))
FXIMPLEMENT(PNPropertiesGrid,FXComposite,NULL,0)

PNPropertiesGrid::PNPropertiesGrid(FXComposite* p)
: FXMatrix(p, 2, LAYOUT_FILL_X|LAYOUT_FILL_Y|MATRIX_BY_COLUMNS)
{
  _object = NULL;
}

PNPropertiesGrid::~PNPropertiesGrid()
{
}

//////////////////////////////////////////////////////////////////////////

void 
PNPropertiesGrid::setObject(PNConfigurableObject* object, pnbool create/* = true*/)
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
	pnerror(PN_LOGLVL_DEBUG, "void PNPropertiesGrid::setObject() : add parameter %s", current_param->getLabel().c_str());
	if (current_param->getType() == PN_PARAMTYPE_SEPARATOR)
	{
	  new PNFXSeparatorParameter(this, current_param);
	  new PNFXSeparatorParameter(this, current_param);

	  FXLabel* label = new FXLabel(this, current_param->getLabel().c_str());
	  label->setTextColor(0x883333);
	  new PNFXSeparatorParameter(this, current_param);

	  continue;
	}

    new FXLabel(this, current_param->getLabel().c_str(), NULL, JUSTIFY_LEFT|LAYOUT_FILL_X|LAYOUT_CENTER_Y);

	switch (current_param->getType())
	{
	case PN_PARAMTYPE_STRING:
	  _params.push_back(new PNFXStringParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_BOOLEAN:
	  _params.push_back(new PNFXCheckButtonParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_INT:
	  _params.push_back(new PNFXIntParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_UINT:
	  _params.push_back(new PNFXUIntParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_REAL:
	  _params.push_back(new PNFXRealParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_FILE:
	  _params.push_back(new PNFXFileParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_DIR:
	  _params.push_back(new PNFXDirParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_LINK:
	  _params.push_back(new PNFXLinksParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_DIALX:
	case PN_PARAMTYPE_DIALY:
	case PN_PARAMTYPE_DIALZ:
	  _params.push_back(new PNFXDialXYZParameter(this, current_param));
	  break;
	case PN_PARAMTYPE_EVENTBOX:
	  _params.push_back(new PNFXEventBoxParameter(this, current_param));
	  break;

	case PN_LISTPARAMTYPE_INT:
	case PN_LISTPARAMTYPE_UINT:
	case PN_LISTPARAMTYPE_REAL:
	  _params.push_back(new PNFXListParameter(this, (PNConfigurableParameterList*)current_param));
	  break;
	case PN_LISTPARAMTYPE_ANIM:
	  _params.push_back(new PNFXAnimListParameter(this, (PNConfigurableParameterList*)current_param));
	  break;
	case PN_LISTPARAMTYPE_MATERIAL:
	  _params.push_back(new PNFXMaterialListParameter(this, (PNConfigurableParameterList*)current_param));
	  break;
	case PN_PARAMTYPE_SCRIPTLIST:
	  _params.push_back(new PNFXScriptListParameter(this, (PNConfigurableParameterList*)current_param));
	  break;
	case PN_LISTPARAMTYPE_STRING:
	  _params.push_back(new PNFXStringListParameter(this, (PNConfigurableParameterList*)current_param));
	  break;
	case PN_LISTPARAMTYPE_VPPNOBJECT:
	  _params.push_back(new PNFXVPPNObjectParameter(this, (PNConfigurableParameterList*)current_param));
	  break;
	//case PN_PARAMTYPE_SCRIPT:
	//  _params.push_back(new PNFXScriptParameter(this, (PNConfigurableParameterList*)current_param));
	//  break;
	default:
	  _params.push_back(new PNFXDefaultParameter(this, current_param));
	  break;
	}
  }

  if (create)
	this->create();
  recalc();
}

void 
PNPropertiesGrid::update()
{
  for (std::list<PNPropertiesGridParameter*>::iterator it = _params.begin(); it != _params.end(); it++)
    (*it)->updateParam();
}

PNConfigurableObject* 
PNPropertiesGrid::getObject()
{
  return _object;
}

//////////////////////////////////////////////////////////////////////////

void
PNPropertiesGrid::applyAll()
{
  for (PNPPList::iterator it = _params.begin(); it != _params.end(); ++it)
  {
	(*it)->apply();
  }
}

//////////////////////////////////////////////////////////////////////////
};
