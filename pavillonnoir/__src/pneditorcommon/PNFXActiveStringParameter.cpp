/*
 * PNFXActiveStringParameter.cpp
 * 
 * Description :
 * PNFXActiveStringParameter definition
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


/////////////////////////////////////

#include <fxkeys.h>

/////////////////////////////////////

#include "pneditorcommon.hpp"
#include "pnproperties.h"

/////////////////////////////////////

#include "PNFXActiveStringParameter.hpp"
#include "PNPropertiesGrid.hpp"

/////////////////////////////////////

using namespace std;

/////////////////////////////////////

namespace PN 
{ 

  //////////////////////////////////////////////////////////////////////////

  FXDEFMAP(PNFXActiveStringParameter) PNFXActiveStringParameterMap[]={
	FXMAPFUNC(SEL_KEYRELEASE,0,PNFXActiveStringParameter::onKeyRelease),
  };

  //////////////////////////////////////////////////////////////////////////
    
  FXIMPLEMENT(PNFXActiveStringParameter,PNFXStringParameter,PNFXActiveStringParameterMap,ARRAYNUMBER(PNFXActiveStringParameterMap))

  //////////////////////////////////////////////////////////////////////////

  /*! 
   *	\brief
   *	Constructor for PNFXActiveStringParameter.
   *
   *	\param		p
   *	Parent object (FXComposite)
   *
   *	\parma		param
   */
	PNFXActiveStringParameter::PNFXActiveStringParameter(FXComposite* p, PNConfigurableParameter* param)
	: PNFXStringParameter(p, param)
  {
	_param = param;
  }

  /*! 
   *	\brief
   *	Default destructor for PNFXActiveStringParameter.
   */
  PNFXActiveStringParameter::~PNFXActiveStringParameter()
  {
  }

  // fox ////////////////////////////////////////////////////////////////////

  void	PNFXActiveStringParameter::create()
  {
	PNFXStringParameter::create();
  }

  //////////////////////////////////////////////////////////////////////////

  /*!
   */
  void	PNFXActiveStringParameter::update()
  {
	PNFXStringParameter::update();
  }

  // events ////////////////////////////////////////////////////////////////

  /*!
   *	\brief
   *	Handles validation (KEY_Return, KEY_KP_Enter)
   */
  long	PNFXActiveStringParameter::onKeyRelease(FXObject* obj,FXSelector sel, void* ptr)
  {
	PNFXStringParameter::handle(obj, sel, ptr);
	FXEvent* event=(FXEvent*)ptr;
	switch(event->code)
	{
	case KEY_Return:
	case KEY_KP_Enter:
	  {
		_param->getConfigurableObject()->update(_param);
		((PNPropertiesGrid*)obj)->updateParent();
		return 1;
	  }
	default:
	  {
		return 1;
	  }
	}
  }

  //////////////////////////////////////////////////////////////////////////
};