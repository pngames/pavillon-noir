/*
 * PNFXActiveStringParameter.cpp
 * 
 * Description :
 * PNFXActiveStringParameter declaration
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

#ifndef _PNFXACTIVESTRINGPARAMETER_HPP_
# define _PNFXACTIVESTRINGPARAMETER_HPP_

/////////////////////////////////////

#include <fx.h>

/////////////////////////////////////

#include "PNFXStringParameter.hpp"
#include "PNConfigurableParameter.hpp"

/////////////////////////////////////

/*!
 *	  \brief
 *	  This widget is a PNFXStringParameter that redraws its grid once that its content has 
 *	  been changed and validated.
 *
 *	  This widget is a PNFXStringParameter that redraws its grid once that its content has
 *	  been changed and validated using KEY_Return or KEY_KP_Enter. Use it only if some 
 *	  information in the grid has to be refreshed.
 */

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  class PNEDAPI PNFXActiveStringParameter : public PNFXStringParameter
  {
	FXDECLARE(PNFXActiveStringParameter);

	PNConfigurableParameter*	_param;

  protected:
	PNFXActiveStringParameter() {}
	PNFXActiveStringParameter(PNFXStringParameter&) {}
  public:
	PNFXActiveStringParameter(FXComposite* p, PNConfigurableParameter* param);
	~PNFXActiveStringParameter();

	void	create();
	void	update();

  public:
	long	onKeyRelease(FXObject*,FXSelector,void* ptr);
  };

  //////////////////////////////////////////////////////////////////////////
};

#endif /*_PNFXACTIVESTRINGPARAMETER_HPP_*/
