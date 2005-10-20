/*
* PNGUIMsgBox.cpp
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

#include "PNGUIMsgBox.hpp"
#include "PNConsole.hpp"
#include <iostream>
using namespace PN;

namespace PN
{
  static int winID = 0;
  static bool cursor = false;

  PNGUIMsgBox::PNGUIMsgBox(const std::string& title, const std::string& text, unsigned int msgtype, const MsgBoxCallback& fonction, CEGUI::Window* parentWin)
  {
	
	std::stringstream convert_tmp;
	convert_tmp << (winID-1);
	std::string str_tmp = "_msg_box_";
	str_tmp += convert_tmp.str();

	if (CEGUI::WindowManager::getSingleton().isWindowPresent(str_tmp.c_str()) == true)
	{
	  PNConsole::writeLine("A msgbox is already here !");
	  return;
	}
	
	std::stringstream convert;
	convert << winID;
	winID++;
	fonctionCallback = fonction;

	cursor = CEGUI::MouseCursor::getSingleton().isVisible();
	if (cursor == false) 
	  CEGUI::MouseCursor::getSingleton().show();

	std::string tmp;

	if (msgtype == CONF)
	{
		_actionName = text;
		tmp = "Veuillez presser\nune touche du clavier\nou un bouton de la souris\npour cette action :\n";
		tmp += text;
	}
	else
		tmp = text;	

		genericCreationWindow(title, tmp, msgtype, parentWin, convert.str());

	switch (msgtype)
	{
	case YES_NO:
	  {
		CEGUI::PushButton* btnYES = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_yes_" + convert.str()).c_str()));
		btnYES->setSize(CEGUI::Size(0.45f, 0.18f));
		btnYES->setPosition( CEGUI::Point(0.025f, 0.79f));
		btnYES->setText("Oui");

	/*	CEGUI::RenderableImage img;
		img.setImage(&CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook")->getImage("MouseArrow"));
		img.setHorzFormatting(CEGUI::RenderableImage::HorzStretched);
		img.setVertFormatting(CEGUI::RenderableImage::VertStretched);
		btnYES->setNormalImage(&img);*/

		_frameWin->addChildWindow(btnYES);
		btnYES->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickYes , this));

		CEGUI::PushButton* btnNO = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_no_" + convert.str()).c_str()));
		btnNO->setSize(CEGUI::Size(0.45f, 0.18f));
		btnNO->setPosition(CEGUI::Point(0.525f, 0.79f));

		btnNO->setText("Non");
		_frameWin->addChildWindow(btnNO);
		btnNO->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickNo, this));
	  }
	  break;
	case OK_CANCEL:
	  {
		CEGUI::PushButton* btnOK = static_cast< CEGUI::PushButton* >( CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_ok_" + convert.str()).c_str()));
		btnOK->setSize(CEGUI::Size(0.45f, 0.18f));
		btnOK->setPosition( CEGUI::Point(0.025f, 0.79f));
		btnOK->setText("Ok");		
		_frameWin->addChildWindow(btnOK);
		btnOK->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickOk, this));

		CEGUI::PushButton* btnCANCEL = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ( "_msg_box_btn_cancel_" + convert.str() ).c_str() ) );
		btnCANCEL->setSize(CEGUI::Size(0.45f, 0.18f));
		btnCANCEL->setPosition(CEGUI::Point(0.525f, 0.79f));
		btnCANCEL->setText("Annuler");
		_frameWin->addChildWindow(btnCANCEL);
		btnCANCEL->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickCancel ,this));
	  }
	  break;
	case OK:
	  {
		CEGUI::PushButton* btnOK = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_ok_" + convert.str()).c_str()));
		btnOK->setSize(CEGUI::Size(0.45f, 0.18f));
		btnOK->setPosition(CEGUI::Point(0.25f, 0.79f));
		btnOK->setText("Ok");
		_frameWin->addChildWindow(btnOK);
		btnOK->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickOk, this));
	  }
	  break;
	case CONF:
		{
		//CEGUI::MouseCursor::getSingleton().hide();
		  float height = CEGUI::System::getSingleton().getRenderer()->getHeight();
		  float width = CEGUI::System::getSingleton().getRenderer()->getWidth();

		  //TODO crash si la console ou le panneau d'info apparait avec cette option
		  CEGUI::Rect* re = new CEGUI::Rect( CEGUI::Point((0.5f-_boxWidth*0.5f)*width , (0.5f-_boxHeight*0.5f)*height), CEGUI::Size(_boxWidth*(width-1), _boxHeight*(height-1)));
		  CEGUI::MouseCursor::getSingleton().setConstraintArea(re);

			_frameWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNGUIMsgBox::eventKeyConfHandler, this));
			_frameWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&PNGUIMsgBox::eventMouseClickConfHandler, this));
			_frameWin->subscribeEvent(CEGUI::Window::EventMouseWheel, CEGUI::Event::Subscriber(&PNGUIMsgBox::eventMouseWheelConfHandler, this));

			_frameWin->activate();
		}
		break;
	}

	_parentWin->addChildWindow(_frameWin);
	_parentWin->setMutedState(true);
  }

  PNGUIMsgBox::~PNGUIMsgBox()
  {
  }

  /********************************************************************************************/

  std::string	PNGUIMsgBox::getActionName()
  {
	  return (_actionName);
  }

  std::string	PNGUIMsgBox::getArgsKind()
  {
	  return (_argsKind);
  }

  CEGUI::EventArgs	PNGUIMsgBox::getCeguiArgs()
  {
	  return (_ceguiArgs);
  }

  bool	PNGUIMsgBox::eventKeyConfHandler(const CEGUI::EventArgs& e)
  {
	  _ceguiArgs = e;
	  _argsKind = "Key";
	  CEGUI::KeyEventArgs* KeyEv = (CEGUI::KeyEventArgs*)&e;
	  //KeyEv->scancode;
	  std::cout << "IN eventKeyConfHandler" << std::endl;
	  deleteMsgBox(CONF);
	  return true;
  }

  bool	PNGUIMsgBox::eventMouseClickConfHandler(const CEGUI::EventArgs& e)
  {
	  _ceguiArgs = e;
	  _argsKind = "MouseClick";
	  CEGUI::MouseEventArgs* mouseEv = (CEGUI::MouseEventArgs*)&e;
	  //mouseEv->button;
std::cout << "IN eventMouseClickConfHandler" << std::endl;
	  deleteMsgBox(CONF);
	  return true;
  }

  bool	PNGUIMsgBox::eventMouseWheelConfHandler(const CEGUI::EventArgs& e)
  {
	  _ceguiArgs = e;
	  _argsKind = "MouseWheel";
	  CEGUI::MouseEventArgs* mouseEv = (CEGUI::MouseEventArgs*)&e;
	  //mouseEv->wheelChange;
std::cout << "IN eventMouseWheelConfHandler" << std::endl;
	  deleteMsgBox(CONF);
	  return true;
  }

  void PNGUIMsgBox::genericCreationWindow(const std::string& title, const std::string& text, unsigned int msgtype, CEGUI::Window* parentWin, std::string convert)
  {
	_defaultFont = CEGUI::System::getSingleton().getDefaultFont();
	
	std::string tmp;


	if (!parentWin) 
	  _parentWin = CEGUI::System::getSingleton().getGUISheet();
	else
	  _parentWin = parentWin;

	std::vector<std::string> lines;
	str_to_vector(text, "\n", &lines);
	_textWidth = 0;

	for (unsigned int cnt = 0; cnt < lines.size(); cnt++)
	{
	  tmp = lines[cnt];
	  float lineExtend = _defaultFont->getTextExtent(tmp.c_str());
	  if (_textWidth < lineExtend)
		_textWidth = lineExtend;
	}   

	_textHeight = _defaultFont->getLineSpacing() * float(lines.size());

	float width, height;

	height = CEGUI::System::getSingleton().getRenderer()->getHeight();
	width = CEGUI::System::getSingleton().getRenderer()->getWidth();
	_textWidth /= width;
	_textHeight /= height;

	_boxWidth = 0;
	_boxHeight = 0;

	float minButtonWidth  = 0.1f;
	float minButtonHeight = 0.05f;
	

	switch (msgtype)
	{
	case YES_NO:
	case OK_CANCEL:
	  _boxWidth = std::max(2.0f * minButtonWidth + 0.1f, _textWidth + 0.05f);
	  _boxHeight = minButtonWidth + _textHeight + 0.1f;
	  break;
	case OK:
	  _boxWidth = std::max(minButtonWidth + 0.1f, _textWidth + 0.05f);
	  _boxHeight = minButtonHeight + _textHeight + 0.1f;
	  break;
	case CONF:
		// TODO : a adapter a la taille du contenu
		_boxWidth = std::max(2.0f * minButtonWidth + 0.1f, _textWidth + 0.05f);
		_boxHeight = minButtonWidth + _textHeight + 0.1f;
	  break;
	}
	
	tmp = "_msg_box_";
	tmp += convert.c_str();
	_frameWin = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/FrameWindow", tmp.c_str()));
	
	if (msgtype == CONF)
	{
	  _frameWin->setText("");
	  _frameWin->setTitleBarEnabled(false);
	}
	else
	  _frameWin->setText(title.c_str());
	
	_frameWin->setAlwaysOnTop(true);
	_frameWin->activate();
	_frameWin->setCloseButtonEnabled(false);
	_frameWin->setPosition(CEGUI::Point(0.5f - _boxWidth * 0.5f, 0.5f - _boxHeight * 0.5f));
	_frameWin->setSize(CEGUI::Size(_boxWidth, _boxHeight));
	_frameWin->setSizingEnabled(false);
	

	tmp = "_msg_box_text_";
	tmp += convert.c_str();
	_msgTxt = static_cast<CEGUI::StaticText*>(CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/StaticText", tmp.c_str()));
	_msgTxt->setText(text.c_str());
	_msgTxt->setPosition(CEGUI::Point(0.05f, 0.05f));
	_msgTxt->setSize(CEGUI::Size(0.95f, 0.7f));
	_msgTxt->setBackgroundEnabled(false);
	_msgTxt->setFormatting(CEGUI::StaticText::HorzCentred, CEGUI::StaticText::VertCentred);
	_msgTxt->setFrameEnabled(false);
	_msgTxt->setVerticalScrollbarEnabled(false);
	

	_frameWin->addChildWindow(_msgTxt);
  }

  void PNGUIMsgBox::confNextStep()
  {
	  std::string tmp = "Voulez vous garder cette\ntouche pour cette action ?\nAction : ";
	  tmp += _actionName;
	  tmp += "\nTouche : ";
	  tmp += "Souris Click Gauche";

	  std::stringstream convert;
	  convert << winID;
	  winID++;

	genericCreationWindow("Conserver?", tmp, YES_NO, _parentWin, convert.str());

	  CEGUI::PushButton* btnYES = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_yes_" + convert.str()).c_str()));
	  btnYES->setSize(CEGUI::Size(0.45f, 0.15f));
	  btnYES->setPosition( CEGUI::Point(0.025f, 0.825f));
	  btnYES->setText("Oui");
	  _frameWin->addChildWindow(btnYES);
	  btnYES->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickYes , this));

	  CEGUI::PushButton* btnNO = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("Vanilla/Button", ("_msg_box_btn_no_" + convert.str()).c_str()));
	  btnNO->setSize(CEGUI::Size(0.45f, 0.15f));
	  btnNO->setPosition(CEGUI::Point(0.525f, 0.825f));
	  btnNO->setText("Non");
	  _frameWin->addChildWindow(btnNO);
	  btnNO->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIMsgBox::onClickNo, this));

	  _parentWin->addChildWindow(_frameWin);
  }

  void PNGUIMsgBox::deleteMsgBox(msgboxtype msgt)
  {
	if (msgt == CONF)
	{
		CEGUI::MouseCursor::getSingleton().setConstraintArea(NULL);
		//_frameWin->destroy();
		_frameWin->hide();
		confNextStep();
	}
	else
	{
		_parentWin->setMutedState(false);

		std::stringstream convert;
		convert << (winID-1);

		std::string tmp = "_msg_box_";
		tmp += convert.str();
		CEGUI::FrameWindow* tmpWin = (CEGUI::FrameWindow*)CEGUI::WindowManager::getSingleton().getWindow(tmp.c_str());
		tmpWin->destroy();
		_frameWin->destroy();
		if (cursor == false)
		  CEGUI::MouseCursor::getSingleton().hide();
		fonctionCallback(msgt);
	}
  }

  bool PNGUIMsgBox::onClickOk(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(OK);
	return true;
  }

  bool PNGUIMsgBox::onClickCancel(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(CANCEL);
	return true;
  }

  bool PNGUIMsgBox::onClickYes(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(YES);
	return true;
  }

  bool PNGUIMsgBox::onClickNo(const CEGUI::EventArgs& arg)
  {
	deleteMsgBox(NO);
	return true;
  }

  int PNGUIMsgBox::str_to_vector(const std::string& str, const std::string& separators, std::vector<std::string>* vresult)
  {
	std::string::size_type len = str.length();
	if (!len)
	  return 0;

	if (!separators.length())
	{
	  vresult->push_back(str);
	  return 1;
	}

	std::string::size_type token = 0;
	std::string::size_type end = 0;
	unsigned int org = vresult->size();

	while (end < len)
	{
	  token = str.find_first_not_of(separators, end);
	  end = str.find_first_of(separators, token);

	  if (token != std::string::npos)
		vresult->push_back(str.substr(token,(end != std::string::npos) ? (end - token) : std::string::npos));
	}
	return (vresult->size() - org);
  }
}
