/*
 * PNFXLinksParameter.hpp
 * 
 * Description :
 * PNFXLinksParameter declaration
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


// TODO : renommer en PNConfigurableParametersList

#ifndef _PNFXLINKSPARAMETER_HPP_
# define _PNFXLINKSPARAMETER_HPP_

#include <fx.h>
#include <map>

#include "pnproperties.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNIAGraph;

class PNEDAPI				PNFXLinksParameter : public FXHorizontalFrame, public PNPropertiesGridParameter
{
  FXDECLARE(PNFXLinksParameter);

  std::map<int,int>			_lnkMap;
  PNIAGraph*				_graph;

  FXComposite*				_parent;

  FXListBox*				_listbox;
  FXButton*					_buttonDelete;
  FXButton*					_buttonAdd;
  FXTextField*				_fieldCoef;

  FXDialogBox*				_dbox;
  FXListBox*				_lnkList;
  FXTextField*				_fieldAddCoef;
  FXRadioButton*			_simpleLnk;
  FXRadioButton*			_doubleLnk;

protected:
  PNFXLinksParameter() : PNPropertiesGridParameter(NULL) {}
  PNFXLinksParameter(PNFXLinksParameter&) : PNPropertiesGridParameter(NULL) {}
public:
  PNFXLinksParameter(FXComposite* p, PNConfigurableParameter* param);
  ~PNFXLinksParameter();

  void	create();

  enum 
  {
	ID_LISTBOX_SEL = FXHorizontalFrame::ID_LAST,
	ID_ADD,
	ID_DELETE,
	ID_RADIO_SIMPLE,
	ID_RADIO_DOUBLE,
	ID_MAKELINK,
	ID_CANCEL
  };

public:
  long						onCmdListBox(FXObject*,FXSelector,void*);
  long						onDelete(FXObject*,FXSelector,void* ptr);
  long						onAdd(FXObject* obj,FXSelector sel,void* ptr);
  long						onRadioSimple(FXObject* obj,FXSelector sel,void* ptr);
  long						onRadioDouble(FXObject* obj,FXSelector sel,void* ptr);
  long						onAccept(FXObject* obj,FXSelector sel,void* ptr);
  long						onCancel(FXObject* obj,FXSelector sel,void* ptr);
  void						buildList(void);
  void						update(void);
  void						updateCoef(void);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNFXLINKSPARAMETER_HPP_*/
