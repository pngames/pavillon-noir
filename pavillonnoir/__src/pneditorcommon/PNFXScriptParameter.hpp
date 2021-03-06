/*
* PNFXScriptParameter.hpp
* 
* Description :
* PNFXScriptParameter declaration
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


#ifndef _PNFXSCRIPTPARAMETER_HPP_
# define _PNFXSCRIPTPARAMETER_HPP_

#include <fx.h>

#include "pnproperties.h"

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  //class PNIAGraph;

  class PNEDAPI					PNFXScriptParameter : public FXHorizontalFrame, public PNPropertiesGridParameter
  {
	FXDECLARE(PNFXScriptParameter);

	FXComposite*				_parent;

	PNConfigurableParameter*	_param;

	FXButton*					_editButton;
	FXLabel*					_description;

	// main window
	FXDialogBox*				_editWindow;
	// init
	FXTextField*				_initScriptFileLocation;
	FXButton*					_initScriptButton;
	FXFileDialog*				_initScriptFileDialog;
	// action
	FXTextField*				_actionScriptFileLocation;
	FXFileDialog*				_actionScriptFileDialog;
	FXButton*					_actionScriptButton;
	// buttons
	FXButton*					_okButton;
	FXButton*					_cancelButton;
	FXButton*					_resetButton;

  protected:
	PNFXScriptParameter() : PNPropertiesGridParameter(NULL) {}
	PNFXScriptParameter(PNFXScriptParameter&) : PNPropertiesGridParameter(NULL) {}
  public:
	PNFXScriptParameter(FXComposite* p, PNConfigurableParameter* param);
	~PNFXScriptParameter();

	void	create();

	enum 
	{
	  ID_EDIT_TRIGGER = FXHorizontalFrame::ID_LAST,
	  ID_RESET_TRIGGER,
	  ID_OK,
	  ID_CANCEL
	};

  public:
	long	onEditTrigger(FXObject*,FXSelector,void*);
	long	onChooseInitFile(FXObject*,FXSelector,void*);
	long	onChooseActionFile(FXObject*,FXSelector,void*);
	long	onResetTrigger(FXObject*,FXSelector,void*);

	long	onOK(FXObject*,FXSelector,void*);
	long	onCancel(FXObject*,FXSelector,void*);

	void	update(void);
  };

  //////////////////////////////////////////////////////////////////////////
};

#endif /* !_PNFXSCRIPTPARAMETER_HPP_ */
