/*
 * PNGUIConsole.cpp
 * 
 * Description :
 * PNGUIConsole definition
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

#include <stdarg.h>
#include <iostream>
#include <sstream>

#include "PNGUIConsole.hpp"
#include "pnrender.h"

using namespace PN;


namespace PN {
//////////////////////////////////////////////////////////////////////////

PNGUIConsole::PNGUIConsole()
{
  _listboxItemSize = 1000;
  _historyLimit = 200;
  _historyCount = 1;
  ite = _ConsoleHistory.begin();

  _pnConsole = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNConsole.layout");
  CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_pnConsole);
  _pnConsole->hide();
  _consoleVisibility = false;

  _editBox =  (CEGUI::Editbox*)CEGUI::WindowManager::getSingleton().getWindow("PNConsole/EditBox");
  
  _listBox = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow((CEGUI::utf8*)"PNConsole/ListBox");

  _editBox->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNGUIConsole::textChangedHandler, this));

  //////////////////////////////////////////////////////////////////////////
  addFonction("setalpha", changeAlpha, "change alpha to the console");
  addFonction("quit", quitGame, "quit game");
  addFonction("exit", quitGame, "quit game");

  //PNEventManager::getInstance()->addEvent(PN_EVENT_CONSOLE_HIDE, this, NULL);
  //PNEventManager::getInstance()->addEvent(PN_EVENT_CONSOLE_SHOW, this, NULL);

  //  PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE_HIDE, EventCallback(this, &PNGUIConsole::consoleVisibility));
  //  PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE_SHOW, EventCallback(this, &PNGUIConsole::consoleVisibility));

  PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE, EventCallback(this, &PNGUIConsole::consoleVisibility));
}

PNGUIConsole::~PNGUIConsole()
{
}

/////////////////////////////////////////////////////////////////////////////////

/*!
\brief
To get the PNGUIConsole instance
*/
PNGUIConsole* PNGUIConsole::getInstance()
{
  if (_instance == NULL)
	_instance = new PNGUIConsole();

  return (PNGUIConsole*)_instance;
}

/////////////////////////////////////////////////////////////////////////////////

/*!
\brief
Function called to write a line into the console and writes the sentence into the log file
\param format
Char* contains the sentence to write
*/
void	PNGUIConsole::_writeLine(const pnchar* format)
{ 
  PNLOCK(this);

  if (PNConsole::_consoleLogFile != NULL)
  {
	std::string tmp = format;
	tmp += "\n";
	tmp = PNConsole::getTime() + tmp;
	fwrite( tmp.c_str(), sizeof( char ), tmp.length(), PNConsole::_consoleLogFile);
  }

  CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(format); 
  addItemToListBox(item);
}

/*!
\brief
Function called to write a particular line into the console with
a level of information and writes the sentence into the log file
\param lvl
Enum of informations levels
\param format
Char* contains the sentence to write
*/
void	PNGUIConsole::_writeError(pnloglevel lvl, const pnchar* format)
{ 
  PNLOCK(this);

  std::string tmp;
  std::string strformat = format;
  CEGUI::ListboxTextItem* item;

  switch (lvl)
  {
  case PN_LOGLVL_INFO:
	tmp = "[Info: "+ strformat + "]";
	item = new CEGUI::ListboxTextItem(tmp.c_str());
	item->setTextColours(CEGUI::colour(1.0f,1.0f,1.0f));
	addItemToListBox(item);
	break ;
#ifdef DEBUG
  case PN_LOGLVL_DEBUG:
	tmp = "[Debug: "+ strformat + "]";
	item = new CEGUI::ListboxTextItem(tmp.c_str());
	item->setTextColours(CEGUI::colour(1.0f,1.0f,1.0f));
	addItemToListBox(item);
	break ;
#endif
  case PN_LOGLVL_TODO:
	tmp = "[Todo: "+ strformat + "]";
	item = new CEGUI::ListboxTextItem(tmp.c_str());
	item->setTextColours(CEGUI::colour(0.0f,1.0f,0.0f));
	addItemToListBox(item);
	break ;
  case PN_LOGLVL_WARNING:
	tmp = "[Warning: "+ strformat + "]";
	item = new CEGUI::ListboxTextItem(tmp.c_str());
	item->setTextColours(CEGUI::colour(0.4f,0.0f,0.0f));
	addItemToListBox(item);
	break ;
  case PN_LOGLVL_ERROR:
	tmp = "[Error: "+ strformat + "]";
	item = new CEGUI::ListboxTextItem(tmp.c_str());
	item->setTextColours(CEGUI::colour(0.6f,0.0f,0.0f));
	addItemToListBox(item);
	break ;
  case PN_LOGLVL_CRITICAL:
	tmp = "[Critical: "+ strformat + "]";
	item = new CEGUI::ListboxTextItem(tmp.c_str());
	item->setTextColours(CEGUI::colour(1.0f,0.0f,0.0f));
	addItemToListBox(item);
	break ;
  default:
	break ;
  }

  if (PNConsole::_consoleLogFile != NULL)
  {
	tmp += "\n";
	tmp = PNConsole::getTime() + tmp;
	fwrite( tmp.c_str(), sizeof( char ), tmp.length(), PNConsole::_consoleLogFile);
  }
}

void	PNGUIConsole::_writePerror(pnloglevel lvl, const pnchar* format)
{ 
  _writeError(lvl, format);
}

/////////////////////////////////////////////////////////////////////////////////

bool  PNGUIConsole::eventKeyPressedHandler(const CEGUI::EventArgs& e)
{
  //CEGUI::KeyEventArgs* me = (CEGUI::KeyEventArgs*)&e;

  /* if (me->scancode == CEGUI::Key::F1)
  {
	if (_consoleVisibility == false)
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_CONSOLE_SHOW, this, NULL);
	else if (_consoleVisibility == true)
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_CONSOLE_HIDE, this, NULL);
	//showhideConsole();
  }*/
  return true;
}

/*!
\brief
Add an item to console's list box.
\param item
CEGUI item to add into the list box
*/
void  PNGUIConsole::addItemToListBox(CEGUI::ListboxTextItem* item)
{
  PNLOCK(this);

  
  _ConsoleListboxItem.push_back(item);
  if (_ConsoleListboxItem.size() > _listboxItemSize)
  {
	ConsoleListboxItem::iterator iter = _ConsoleListboxItem.begin();
	_listBox->removeItem((CEGUI::ListboxItem*)*iter);
	_ConsoleListboxItem.pop_front();
  }

  _listBox->addItem(item);
  _listBox->ensureItemIsVisible(item);
  ite = _ConsoleHistory.begin();
}

/*!
\brief
Called when the return key is pressed in the input box and calls the right registered function.
Save the command for the history.
*/
bool  PNGUIConsole::textAccepteddHandler(/*const CEGUI::EventArgs& e*/)
{
  CEGUI::String line;

 
  line = _editBox->getText();

  if (line.empty() == false)
  {
	typedef std::basic_stringstream<char> stringstream;
	stringstream buffer;

	if (line.find(" ") != CEGUI::String::npos)
	{
	  buffer << line.substr(line.find(" "),line.length()).c_str();
	  PNConsole::callFonction(line.substr(0,line.find(" ")).c_str(), buffer);
	}
	else
	{
	  buffer << "";
	  PNConsole::callFonction(line.c_str(), buffer);
	}

	if (_historyLimit >= _historyCount)
	  _historyCount++;
	else
	{
	  _ConsoleHistory.pop_front();
	}
	_ConsoleHistory.push_back(line.c_str());

	ite = _ConsoleHistory.end();
	_editBox->setText("");
  }
  return true;
}

/*!
\brief
Called when a key is pressed in the input box, only check the up and down keys for the history
*/
bool  PNGUIConsole::textChangedHandler(const CEGUI::EventArgs& e)
{
  CEGUI::KeyEventArgs* me = (CEGUI::KeyEventArgs*)&e;

  std::string tmp;

  if (me->scancode == CEGUI::Key::ArrowUp)
  {
	if (ite != _ConsoleHistory.begin())
	{ 
	  if (ite == _ConsoleHistory.end())
		_currentHistoryLine = _editBox->getText().c_str();
	  ite--;
	  tmp = *ite;
	  _editBox->setText(tmp.c_str());
	  _editBox->setCaratIndex((CEGUI::uint)tmp.length());
	}
  }
  if (me->scancode == CEGUI::Key::ArrowDown)
  {
	if (ite != _ConsoleHistory.end())
	{
	  ite++;
	  if (ite == _ConsoleHistory.end())
		tmp = _currentHistoryLine;
	  else
		tmp = *ite;
	  _editBox->setText(tmp.c_str());
	  _editBox->setCaratIndex((CEGUI::uint)tmp.length());
	}
  }
  if (me->scancode == CEGUI::Key::Tab)
  {
	std::string cmd = _editBox->getText().c_str();
	std::string text;
	std::vector<std::string> candidates;
	unsigned int matchcnt = PNConsole::getFonctionCompletion(cmd, candidates);

	if (!matchcnt)
	  _writeLine("type 'help' in order to get a complete list of possible commands.");

	std::vector<std::string>::iterator p_beg = candidates.begin();
	std::vector<std::string>::iterator p_end = candidates.end();

	if (matchcnt > 1)
	{
	  text = "possible commands: ";
	  for (;p_beg != p_end; p_beg++)
		text += (*p_beg ) + "  ";

	  text += "\n";
	  _writeLine(text.c_str());

	  bool dobreak = false;
	  unsigned int cnt = cmd.size();

	  do
	  {
		p_beg = candidates.begin();
		p_end = candidates.end();

		char matchc = (*p_beg)[cnt];
		p_beg++;

		for (;p_beg != p_end; p_beg++)
		{
		  std::string curcmd = *p_beg;
		  if ((cnt >= curcmd.length()) || (matchc != curcmd[cnt]))
		  {
			dobreak = true;
			break;
		  }
		}
		cnt++;
	  } while(!dobreak);

	  std::string cmdc = *candidates.begin();
	  cmdc = cmdc.substr(0, cnt-1);
	  _editBox->setText(cmdc.c_str());
	  _editBox->setCaratIndex(cmdc.length());
	}

	if (matchcnt == 1)
	{
	  text = *p_beg;
	  _editBox->setText(text.c_str());
	  _editBox->setCaratIndex(text.length());
	}
  }

  if (me->scancode == CEGUI::Key::Return || me->scancode == CEGUI::Key::NumpadEnter)
  {
	textAccepteddHandler();
  }
  return true;
}

/*!
\brief
Called to hide or show the console, when it shows the console it gives the focus to
the input box
*/
void  PNGUIConsole::consoleVisibility(pnEventType type, PNObject* source, PNEventData* data)
{
  static bool cursor = false;

  if (_consoleVisibility == false)
  {
	_pnConsole->show();
	_editBox->activate();

	cursor = CEGUI::MouseCursor::getSingleton().isVisible();
	if (cursor == false) 
	  CEGUI::MouseCursor::getSingleton().show();
	_consoleVisibility = true;
  }
  else if (_consoleVisibility == true)
  {
	if (cursor == false) 
	  CEGUI::MouseCursor::getSingleton().hide();
	_editBox->deactivate();
	_pnConsole->hide();
	_consoleVisibility = false;
  }  
}

/*!
\brief
Console command to change the alpha of the console
*/
void  PNGUIConsole::changeAlpha(const std::string& command, std::istream& parameters)
{
  bool tmp;  
  parameters >> tmp;
  CEGUI::Window*  pnConsole = CEGUI::WindowManager::getSingleton().getWindow("PNConsole");

  if (tmp == 1)
	pnConsole->setAlpha(1.0f);
 
  if (tmp == 0)
	pnConsole->setAlpha(0.85f);
}

/*!
\brief
Console command to quit the game
*/
void  PNGUIConsole::quitGame(const std::string& command, std::istream& parameters)
{
  PNRendererInterface::getInstance()->endRendering();
}

/*!
\brief
Function to change the line numbers of the list box
\param size
Int for the new size
*/
void  PNGUIConsole::setlistboxItemSize(int size)
{
  _listboxItemSize = size;
}
//////////////////////////////////////////////////////////////////////////
}
