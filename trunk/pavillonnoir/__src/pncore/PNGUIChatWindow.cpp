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

#include <boost/filesystem/operations.hpp>

#include "pndefs.h"
#include "pnresources.h"
#include "pnxml.h"
#include "PNGUIChatWindow.hpp"
#include "PNGUIGame.hpp"
#include "PNConsole.hpp"
#include "PNGameMap.hpp"
#include "PNGameInterface.hpp"



using namespace PN;
namespace fs = boost::filesystem;

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

  void PNGUIChatWindow::setMapChatPath(std::string id_player)
  {
	_currentChatXml = "";
	PNGameMap*	gmap = PNGameInterface::getInstance()->getGameMap();
	std::string* tmpMap = gmap->getPath();
	_currentChatXml += *tmpMap;
	_currentChatXml += "/" + DEF::chatDirectory + id_player + ".xml";
  }

  void	PNGUIChatWindow::startGUI(std::string id_player)
  {
	setMapChatPath(id_player);
	_chatTree = new PNChatTree();
	fs::path file(_currentChatXml, fs::no_check);

	_chatTree->unserializeFromFile(file);

	showNextBuddy(_chatTree->getCurrentNode());
	
	/*std::vector<std::string> responses;
	responses.push_back("l'amour");
	responses.push_back("le jeu");
	responses.push_back("la bouffe");
	responses.push_back("le saiske");
	responses.push_back("la picole");
	responses.push_back("la drogue");
	*/

	show();
  }

  void	PNGUIChatWindow::resetGUI()
  {
	delete _chatTree;
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
	PNGUIGame::getInstance()->startGUI();
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
	if (_quitBuddy == true)
	{
	  resetGUI();
	  return true;
	}

	if (_listBox->getFirstSelectedItem() != NULL)
	{
	 PNConsole::writeLine("Vous avez choisi : %s",_listBox->getFirstSelectedItem()->getText().c_str());

	 unsigned int tmp = _listBox->getFirstSelectedItem()->getID();
	 std::string selNodeId = (char *)tmp;
	 
	/* xmlNode* selNode = _chatTree->getNodeFromId(selNodeId);

	 if ((const char*)xmlGetProp(selNode, PNXML_CHECKPOINT_ATTR) == "true")
	   _resolvedDependencies.push_back(selNodeId);
	  
	 if ((const char*)xmlGetProp(selNode, PNXML_QUIT_ATTR) == true)
	 {
	  resetGUI();
	  return true;
	 }

	showNextBuddy(selNode);
*/
	}
	return true;
  }


  void	PNGUIChatWindow::showNextBuddy(xmlNode* node)
  {
	_chatTree->setListDependencies(_resolvedDependencies);
	_currentNode = _chatTree->getBuddyNode(node);
	// si currentNode est null (pas de buddy dispo) quitter mode chat ?
	updateItems(_currentNode);
  }

  void  PNGUIChatWindow::updateItems(xmlNode* node)
  {
	_quitBuddy = false;
	xmlChar* quit = xmlGetProp(node, PNXML_QUIT_ATTR);
	if (quit!= NULL && strcmp((const char*)quit,"true") == 0)
	  _quitBuddy = true;

	_textQuestion->setText((const char*)xmlGetProp(node, PNXML_SENTENCE_ATTR));
	_listBox->resetList();

	if (!_quitBuddy && node->children != NULL)
	{
	  for (xmlNodePtr sub = node->children; sub != NULL; sub = sub->next)
	  {
		if (xmlStrEqual(sub->name, PNXML_PLAYER_MKP))
		{
		  CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem((const char*)xmlGetProp(sub, PNXML_ANSWER_ATTR));
		  item->setID((unsigned int)xmlGetProp(sub, PNXML_ID_ATTR));
		  item->setSelectionBrushImage((CEGUI::utf8*)"Vanilla-Images", (CEGUI::utf8*)"GenericBrush");
		  item->setSelectionColours(CEGUI::colour(RGBA(159,159,159,255)));
		  _listBox->addItem(item);
		}
	  }
	}

/*	_textQuestion->setText(question.c_str());
	
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

*/	
  }

}

