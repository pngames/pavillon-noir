/*
* PNGUIMsgBox.hpp
* 
* Description :
* PNGUIMsgBox declaration
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

#ifndef _PN_GUIMSGBOX_HPP_
#define _PN_GUIMSGBOX_HPP_

#include "myCEGUI.h"
#include <fastdelegate/FastDelegate.h>

namespace PN
{
  class PNGUIMsgBox
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	typedef enum
	{
	  YES_NO,
	  OK_CANCEL,
	  OK,
	  NO,
	  YES,
	  CANCEL,
	  CONF
	} msgboxtype;

	typedef fastdelegate::FastDelegate1<const unsigned int&> MsgBoxCallback;

  protected:
  private:
	MsgBoxCallback			fonctionCallback;
	CEGUI::FrameWindow*	_frameWin;
	CEGUI::StaticText*	_msgTxt;
	CEGUI::Window*		_parentWin;
	CEGUI::Window*		_backWin;
	CEGUI::Font*		_defaultFont;
	float _boxWidth;
	float _boxHeight;
	float _textWidth;
	float _textHeight;

	std::string			_actionName;
	std::string			_argsKind;
	CEGUI::EventArgs	_ceguiArgs;
	bool	_cursorVisibility;
	//CEGUI::Key			_ceguiKey;
	

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	  std::string	PNGUIMsgBox::getActionName();
	  std::string	PNGUIMsgBox::getArgsKind();
	  CEGUI::EventArgs	PNGUIMsgBox::getCeguiArgs();

  protected:
  private:
	void	genericCreationWindow(const std::string& title, const std::string& text, unsigned int msgtype, CEGUI::Window* parentWin, std::string convert);
	bool	onClickOk(const CEGUI::EventArgs& arg);
	bool	onClickCancel(const CEGUI::EventArgs& arg);
	bool	onClickYes(const CEGUI::EventArgs& arg);
	bool	onClickNo(const CEGUI::EventArgs& arg);
	void	deleteMsgBox(msgboxtype msgt);
	bool	eventKeyConfHandler(const CEGUI::EventArgs& e);
	bool	eventMouseClickConfHandler(const CEGUI::EventArgs& e);
	bool	eventMouseWheelConfHandler(const CEGUI::EventArgs& e);
	void	confNextStep();
	int		str_to_vector(const std::string& str, const std::string& separators, std::vector<std::string>* p_result);
	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIMsgBox(const std::string& title, const std::string& text, unsigned int msgtype, const MsgBoxCallback& fonction, CEGUI::Window* parentWin = NULL);
	//PNGUIMsgBox(const std::string& text, unsigned int msgtype, const Callback& fonction, const std::string& actionName, CEGUI::Window* parentWin = NULL);
	~PNGUIMsgBox();
  };
}

#endif /*_PN_GUIMSGBOX_HPP_*/
