/*
 * PNFXFileParameter.hpp
 * 
 * Description :
 * PNFXFileParameter declaration
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


#ifndef _PNFXFILEPARAMETER_HPP_
# define _PNFXFILEPARAMETER_HPP_

#include <fx.h>
#include <boost/filesystem/path.hpp>

#include "pnproperties.h"

/*
 *	This widget is composed of a text field containing the path to the wanted 
 *  file and a "browse" button to graphically select that file
 */

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  class PNEDAPI PNFXFileParameter : public FXHorizontalFrame, public PNPropertiesGridParameter
  {
	FXDECLARE(PNFXFileParameter);

	PNConfigurableParameter*	_param;
	FXTextField*				_field;
	FXButton*					_button;

  protected:
	PNFXFileParameter() {}
	PNFXFileParameter(PNFXFileParameter&) {}
  public:
	PNFXFileParameter(FXComposite* p, PNConfigurableParameter* param);
	~PNFXFileParameter();

	void  create();
	void  update();

	enum 
	{
	  ID_BROWSE = FXHorizontalFrame::ID_LAST
	};

  public:
	long	PNFXFileParameter::onBrowse(FXObject*,FXSelector,void* ptr);
  };

  //////////////////////////////////////////////////////////////////////////
};

#endif /*_PNFXFILEPARAMETER_HPP_*/
