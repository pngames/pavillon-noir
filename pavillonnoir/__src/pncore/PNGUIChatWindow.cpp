/*
* PNGUIChatWindow.cpp
* 
* Description :
* PNGUIChatWindow declaration
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

#include "PNGUIChatWindow.hpp"

using namespace PN;

namespace PN
{
  PNGUIChatWindow::PNGUIChatWindow()
  {
	_mainSheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"./datafiles/layouts/PNChatWindow.layout"); 
	_listBox = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNChatWindow/Listbox");
	_textQuestion = (CEGUI::StaticText*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNChatWindow/Text");

	//_listBox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&PNGUIChatWindow::handleListBox, this));
	 CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNChatWindow/ButtonValid")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&PNGUIChatWindow::handleValid, this));

	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_mainSheet);
	hide();
  }

  PNGUIChatWindow::~PNGUIChatWindow()
  {
	_mainSheet->destroy();
  }

  void	PNGUIChatWindow::startGUI()
  {
	show();
  }

  void	PNGUIChatWindow::resetGUI()
  {
	hide();
  }

  void	PNGUIChatWindow::show()
  {
	_mainSheet->show();
	_mainSheet->setMutedState(false);
	_mainSheet->activate();
	CEGUI::MouseCursor::getSingleton().show();
  }

  void	PNGUIChatWindow::hide()
  {
	_mainSheet->hide();
	_mainSheet->setMutedState(true);
  }

  CEGUI::Window*  PNGUIChatWindow::getWindow()
  {
	return _mainSheet;
  }

  bool	PNGUIChatWindow::handleListBox(const CEGUI::EventArgs& e)
  {
	return true;
  }

  bool	PNGUIChatWindow::handleValid(const CEGUI::EventArgs& e)
  {
	if (_listBox->getFirstSelectedItem() != NULL)
	{

	}
	return true;
  }

  void  PNGUIChatWindow::updateItems(std::string question, std::vector<std::string> responses)
  {
  }

}
