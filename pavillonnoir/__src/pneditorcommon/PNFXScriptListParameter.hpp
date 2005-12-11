/*
 * PNFXScriptListParameter.hpp
 * 
 * Description :
 * PNFXScriptListParameter declaration
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


#ifndef _PNFXSCRIPTLISTPARAMETER_HPP_
# define _PNFXSCRIPTLISTPARAMETER_HPP_

#include <fx.h>
#include <map>

#include "pnproperties.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNIAGraph;

class PNEDAPI PNFXScriptListParameter : public FXHorizontalFrame, public PNPropertiesGridParameter
{
  FXDECLARE(PNFXScriptListParameter);

  FXComposite*				_parent;

  FXListBox*					_eventList;
  FXTextField*				_event;
  FXButton*					_buttonDeleteEvent;
  FXButton*					_buttonAddEvent;
  FXButton*					_buttonEditScripts;

  FXDialogBox*				_dbox;
  FXListBox*					_scriptList;
  FXButton*					_buttonDeleteScript;
  FXButton*					_buttonAddScript;

protected:
  PNFXScriptListParameter() {}
  PNFXScriptListParameter(PNFXScriptListParameter&) {}
public:
  PNFXScriptListParameter(FXComposite* p, PNConfigurableParameter* param);
  ~PNFXScriptListParameter();

  void	create();

  enum 
  {
	ID_ADD_EVENT = FXHorizontalFrame::ID_LAST,
	ID_DELETE_EVENT,
	ID_ADD_SCRIPT,
	ID_DELETE_SCRIPT,
	ID_EDIT_SCRIPTS,
	ID_ADD_EVENT_OK,
	ID_ADD_EVENT_CANCEL,
	ID_OK
  };

public:
  long	onCmdListBox(FXObject*,FXSelector,void*);
  long	onDeleteEvent(FXObject*,FXSelector,void* ptr);
  long	onAddEvent(FXObject* obj,FXSelector sel,void* ptr);
  long	onAddEventOK(FXObject* obj,FXSelector sel,void* ptr);
  long	onAddEventCancel(FXObject* obj,FXSelector sel,void* ptr);
  long	onDeleteScript(FXObject*,FXSelector,void* ptr);
  long	onAddScript(FXObject* obj,FXSelector sel,void* ptr);
  long	onEditScripts(FXObject* obj,FXSelector sel,void* ptr);
  void	buildList(void);
  void	update(void);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* !_PNFXSCRIPTLISTPARAMETER_HPP_ */
