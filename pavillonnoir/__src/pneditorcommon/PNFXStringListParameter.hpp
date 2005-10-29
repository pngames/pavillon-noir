/*
 * PNFXStringListParameter
 * 
 * Description :
 * PNFXStringListParameter declaration
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

#ifndef _PNFXSTRINGLISTPARAMETER_HPP_
# define _PNFXSTRINGLISTPARAMETER_HPP_

/////////////////////////////////////

#include <fx.h>
#include <list>
#include <string>

/////////////////////////////////////

#include "pneditorcommon.h"
#include "pnproperties.h"
#include "PNConfigurableParameter.hpp"

/////////////////////////////////////

namespace PN {

  typedef std::list<std::string> stringList;

  //////////////////////////////////////////////////////////////////////////

  class PNEDAPI PNFXStringListParameter : public FXHorizontalFrame, public PNPropertiesGridParameter
  {
	FXDECLARE(PNFXStringListParameter);

	FXComposite*				_parent;
	PNConfigurableParameter*	_param;

	FXListBox*					_listBox;
	FXButton*					_buttonDelete;
	FXButton*					_buttonAdd;

	int							_labelsNumChars;
	int							_numVisibleItems;

  protected:
	PNFXStringListParameter() {}
	PNFXStringListParameter(PNFXStringListParameter&) {}
  public:
	PNFXStringListParameter(FXComposite* p, PNConfigurableParameter* param);
	~PNFXStringListParameter();

	void	create();

  public:
	long	onCmdListBox(FXObject*,FXSelector,void*);
	void	buildList(void);
	void	update(void);

	int		getNumVisibleItems() { return _numVisibleItems; }
	int		getLabelsNumChars() { return _labelsNumChars; }

	void	setNumVisibleItems(int numItems);
	void	setLabelsNumChars(int numChars);
	
  public:
	  enum {
		// _objectsListBox selection changed
		ID_LISTBOX_SEL = FXComposite::ID_LAST,
		ID_LAST
	  };
  };

  //////////////////////////////////////////////////////////////////////////
};

#endif /*_PNFXSTRINGLISTPARAMETER_HPP_*/
