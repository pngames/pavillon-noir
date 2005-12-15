/*
 * PNFXListParameter.hpp
 * 
 * Description :
 * PNFXListParameter declaration
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


#ifndef _PNFXLISTPARAMETER_HPP_
# define _PNFXLISTPARAMETER_HPP_

#include <fx.h>
#include <map>

#include "pneditorcommon.h"

#include "PNConfigurableParameter.hpp"
#include "PNPropertiesGridParameter.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNIAGraph;

class PNEDAPI				PNFXListParameter : public FXHorizontalFrame, public PNPropertiesGridParameterList
{
  FXDECLARE_ABSTRACT(PNFXListParameter);

protected:
  FXListBox*				_listBox;
  FXButton*					_buttonDelete;
  FXButton*					_buttonAdd;

  bool						_changed;
  //FXImage ? FXBouton avec image (cliquable = defaut) ?  // temoin de modification

protected:
  PNFXListParameter() : PNPropertiesGridParameterList(NULL) {}
  PNFXListParameter(PNFXListParameter&) : PNPropertiesGridParameterList(NULL) {}
public:
  PNFXListParameter(FXComposite* p, PNConfigurableParameterList* param);
  ~PNFXListParameter();

  void						create();

  void						update();

  enum 
  {
	ID_ADD = FXHorizontalFrame::ID_LAST,
	ID_DELETE,

	ID_LAST
  };

protected:
  virtual bool				_deleteObject(FXint index)=0;
  virtual bool				_addNewObject(FXint index)=0;

  virtual void				_buildList(void)=0;
  virtual void				_update()=0;
public:
  long						onDelete(FXObject*,FXSelector,void* ptr);
  long						onAdd(FXObject* obj,FXSelector sel,void* ptr);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNFXLISTPARAMETER_HPP_*/