/*
* PNGUIChatWindow.hpp
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

#ifndef _PNGUICHATWINDOW_HPP_
#define _PNGUICHATWINDOW_HPP_

#include <vector>
#include <libxml/xmlreader.h>
#include <set>
#include "myCEGUI.h"

#include "pnevent.h"
#include "PNChatTree.hpp"

namespace PN
{
  class PNGUIChatWindow
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  protected:
  private:
	static PNGUIChatWindow* _instance;
	CEGUI::Window* _mainSheet;
	CEGUI::Listbox*	_listBox;
	CEGUI::StaticText* _textQuestion;
	CEGUI::StaticText* _textName;
	std::string _currentChatXml;
	typedef std::set<std::string>			ListResolvedDependencies;
	ListResolvedDependencies				_resolvedDependencies;
	PNChatTree* _chatTree;
	xmlNode* _currentNode;
	bool _quitBuddy;
	std::string _currentIdTalking;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIChatWindow*	getInstance();
	void  startGUI(std::string id_player);
	void  resetGUI();
	CEGUI::Window*  getWindow();
  protected:
  private:
	void  hide();
	void  show();
	bool  handleListBox(const CEGUI::EventArgs& e);
	bool  handleValid(const CEGUI::EventArgs& e);
	void  updateItems(xmlNode* node);
	bool	showNextBuddy(xmlNode* node);
	void setMapChatPath(std::string id_player);
	void handleAll();
	void  cleanResolvedDep(pnEventType type, PNObject* source, PNEventData* data);
	void  manageInventoryItem(pnEventType type, PNObject* source, PNEventData* data);
	void setName(xmlNode* node);
	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIChatWindow();
	~PNGUIChatWindow();
  protected:
  private:

  };
}

#endif /*_PNGUICHATWINDOW_HPP_*/

