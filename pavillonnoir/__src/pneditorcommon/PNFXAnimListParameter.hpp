/*
 * PNFXAnimListParameter
 * 
 * Description :
 * PNFXAnimListParameter declaration
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

#ifndef _PNFXAnimListPARAMETER_HPP_
# define _PNFXAnimListPARAMETER_HPP_

/////////////////////////////////////

#include <fx.h>
#include "pnproperties.h"

/////////////////////////////////////

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  class PNIAGraph;
  class PNEDAPI PNFXAnimListParameter : public FXHorizontalFrame, public PNPropertiesGridParameter
  {
	FXDECLARE(PNFXAnimListParameter);

	FXComposite*				_parent;
	PNConfigurableParameter*	_param;

	FXListBox*					_listBox;
	FXButton*					_buttonDelete;
	FXButton*					_buttonAdd;

  protected:
	PNFXAnimListParameter() {}
	PNFXAnimListParameter(PNFXAnimListParameter&) {}
  public:
	PNFXAnimListParameter(FXComposite* p, PNConfigurableParameter* param);
	~PNFXAnimListParameter();

	void	create();

	enum 
	{
	  ID_ADD = FXHorizontalFrame::ID_LAST,
	  ID_DELETE
	};

  public:
//	long	onCmdListBox(FXObject*,FXSelector,void*);
	long	onDelete(FXObject*,FXSelector,void* ptr);
	long	onAdd(FXObject* obj,FXSelector sel,void* ptr);
	void	buildList(void);
	void	update(void);
  };

  //////////////////////////////////////////////////////////////////////////
};

#endif /*_PNFXAnimListPARAMETER_HPP_*/
