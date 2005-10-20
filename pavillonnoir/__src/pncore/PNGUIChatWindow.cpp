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
#include "PNConsole.hpp"

using namespace PN;

#define RGBA(R,G,B,A) (B+(G<<8)+(R<<16)+(A<<24))

namespace PN
{
   PNGUIChatWindow*				PNGUIChatWindow::_instance = NULL;

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

  PNGUIChatWindow*  PNGUIChatWindow::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIChatWindow(); 

	return _instance;
  }

  void	PNGUIChatWindow::startGUI()
  {
	show();
	std::vector<std::string> responses;
	responses.push_back("l'amour");
	responses.push_back("le jeu");
	responses.push_back("la bouffe");
	responses.push_back("le saiske");
	responses.push_back("la picole");
	responses.push_back("la drogue");
	
	updateItems("Qu'est ce qui vous rend heureux dans la vie ?", responses);
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
	  resetGUI();
	  PNConsole::writeLine("Vous avez choisi : %s",_listBox->getFirstSelectedItem()->getText().c_str());
	}
	return true;
  }

  void  PNGUIChatWindow::updateItems(const std::string question, std::vector<std::string> responses)
  {

	_textQuestion->setText(question.c_str());
	
	_listBox->resetList();

	std::vector<std::string>::iterator p_beg = responses.begin();
	std::vector<std::string>::iterator p_end = responses.end();
	for (;p_beg != p_end; p_beg++)
	{
	  std::string tmp = *p_beg;
	  CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(tmp.c_str());
	  item->setSelectionBrushImage((CEGUI::utf8*)"Vanilla-Images", (CEGUI::utf8*)"GenericBrush");
	  item->setSelectionColours(CEGUI::colour(RGBA(159,159,159,255)));
	  _listBox->addItem(item);
	}

	
  }

}

