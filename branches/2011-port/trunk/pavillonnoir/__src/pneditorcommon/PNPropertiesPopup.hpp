/*
 * PNPropertiesPopup.hpp
 * 
 * Description :
 * PNPropertiesPopup declaration
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


#ifndef _PN_PROPERTIESPOPUP_HPP_
# define _PN_PROPERTIESPOPUP_HPP_

#include <fx.h>
#include "pndefs.h"
#include "PNConfigurableObject.hpp"

namespace PN
{
  //////////////////////////////////////////////////////////////////////////

  class	PNPropertiesPopup : public FXDialogBox 
  {
	FXDECLARE(PNPropertiesPopup)

  protected:
	FXHorizontalFrame*	high;
	FXHorizontalFrame*	low;

  private:
	PNPropertiesPopup(){}

  public:
	PNPropertiesPopup(FXWindow* owner);
	PNPropertiesPopup(FXWindow* owner, PNConfigurableParameter* cp);
	virtual ~PNPropertiesPopup();

	long onDelete(FXObject*,FXSelector,void*);

	enum 
	{
	  ID_DELETE = FXDialogBox::ID_LAST
	};
  };
};

#endif /*_PN_PROPERTIESPOPUP_HPP_*/
