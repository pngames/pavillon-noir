/*
* PNGUIConfPanel.cpp
* 
* Description :
* PNGUIConfPanel declaration
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

#include "PNGUIConfPanel.hpp"

using namespace PN;

namespace PN
{

  confPanelTEST::confPanelTEST(std::string label)
  {
	_label = label;

	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL,	  &_aReal, "position x", "position x"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_BOOLEAN, &_aBool, "position y", "position y"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_INT,	  &_aInt, "position z", "position z"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_STRING,  &_aString, "class", "class"));
  }


  /**************************************************************************************/
  
  PNGUIConfPanel* PNGUIConfPanel::_instance = NULL;
 
  PNGUIConfPanel::PNGUIConfPanel()
  {
	_visibility = false;
	_cursorVisibility = false;
	_nbTAB = 0;

	_pnConfPanel = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNConfPanel.layout");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_pnConfPanel);
	_pnConfPanel->hide();
	_tabControl = (CEGUI::TabControl*)CEGUI::WindowManager::getSingleton().getWindow("PNConfPanel/tabControl");
	_tabControl->setTabTextPadding(0.00f);
	//_testTab = CEGUI::WindowManager::getSingleton().getWindow("PNConfPanel/tabControl/testTab");

	 //PNEventManager::getInstance()->addCallback(PN_EVENT_CONFPANEL, EventCallback(this, &PNGUIConfPanel::confPanelVisibility));
	 
	confPanelTEST* testobj = new confPanelTEST("123456789abcde");

	 /*addConfigurableObject(testobj);
	 addConfigurableObject(testobj);
	 addConfigurableObject(testobj);
	 addConfigurableObject(testobj);
	  addConfigurableObject(testobj);
	   addConfigurableObject(testobj);*/
  }

  PNGUIConfPanel::~PNGUIConfPanel()
  {
  }

  PNGUIConfPanel* PNGUIConfPanel::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIConfPanel();
	return _instance;
  }

  void  PNGUIConfPanel::confPanelVisibility(pnEventType type, PNObject* source, PNEventData* data)
  {
	if (_visibility == false)
	{
	  _pnConfPanel->show();
	  _cursorVisibility = CEGUI::MouseCursor::getSingleton().isVisible();
	  if (_cursorVisibility == false) 
		CEGUI::MouseCursor::getSingleton().show();
	  _visibility = true;
	}
	else if (_visibility == true)
	{
	  if (_cursorVisibility == false) 
		CEGUI::MouseCursor::getSingleton().hide();
	  _pnConfPanel->hide();
	  _visibility = false;
	} 
  }

  bool  PNGUIConfPanel::mainEventHandler(const CEGUI::EventArgs& e)
  {
	CEGUI::WindowEventArgs* KeyEv = (CEGUI::WindowEventArgs*)&e;
	CEGUI::Window* tmp = KeyEv->window;
	std::string name = tmp->getName().c_str();
	
	PNConfigurableParameter* obj = _confPanelMap[name]; 
	
	//TODO regarder le type du PNCP 
	
	return true;
  }

  std::string PNGUIConfPanel::itemNameGenerator(const std::string& tabName, const std::string& itemName)
  {
	std::string tmp = removeWhitespace(tabName);
	tmp += "_";
	tmp += removeWhitespace(itemName);
	return tmp;
  }

  std::string PNGUIConfPanel::isWinPresent(const std::string& name, const std::string& chartoadd)
  {
	bool tabExsist = false;
	tabExsist = CEGUI::WindowManager::getSingleton().isWindowPresent(name.c_str());
	std::string tmpName = name;

	while (tabExsist == true) 
	{
	  tmpName += chartoadd;
	  tabExsist = CEGUI::WindowManager::getSingleton().isWindowPresent(tmpName.c_str());
	}

	return tmpName;
  }

  std::string PNGUIConfPanel::getStringByType(PNConfigurableParameter* current_param)
  {
	switch(current_param->getType()) 
	{
	case PN_PARAMTYPE_STRING:
	case PN_PARAMTYPE_ACTIVESTRING:
	  return " (string)";
	case PN_PARAMTYPE_INT:
	 return " (int)";
	case PN_PARAMTYPE_REAL:
	 return " (float)";
	case PN_PARAMTYPE_BOOLEAN:
		return " (bool)";
	default:
	  return " (none)";
	}
  }

  void  PNGUIConfPanel::addItem(CEGUI::Window* curTab,  PNConfigurableParameter* current_param, int idx)
  {
	CEGUI::DefaultWindow* win = NULL;
	CEGUI::Editbox* eb = NULL;
	CEGUI::Checkbox* cb = NULL;
	CEGUI::StaticText* st = NULL;

	float incVal = 0.05f * idx;

	std::string itemName = itemNameGenerator(curTab->getText().c_str(), current_param->getLabel());

	std::string DWname = "PNConfPanel/DefaultWin_" + itemName;
	std::string EBname = "PNConfPanel/Editbox_" + itemName;
	std::string CBname = "PNConfPanel/Editbox_" + itemName;
	std::string STname = "PNConfPanel/Statictext_" + itemName;
	std::string tmpName = "";

	tmpName = isWinPresent(DWname, "_");

	win = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"DefaultWindow", tmpName.c_str());
	win->setFont("VeraSe-8");
	//largeur hauteur
	win->setSize(CEGUI::Size(1.00f, 0.05f));
	// x y
	win->setPosition(CEGUI::Point(0.0f, incVal));
	curTab->addChildWindow(win);

	if (current_param->getType() == PN_PARAMTYPE_BOOLEAN)
	{
	  tmpName = isWinPresent(CBname, "_");
	  cb =  (CEGUI::Checkbox*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"TaharezLook/Checkbox", tmpName.c_str());
	  cb->setSize(CEGUI::Size(0.30f, 1.00f));
	  cb->setPosition(CEGUI::Point(0.10f, 0.00f));
	  cb->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&PNGUIConfPanel::mainEventHandler, this));
	  win->addChildWindow(cb);
	  _confPanelMap[CBname]  = current_param;
	}
	else
	{
	  tmpName = isWinPresent(EBname, "_");
	  eb =  (CEGUI::Editbox*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/Editbox", tmpName.c_str());
	  eb->setSize(CEGUI::Size(0.30f, 1.00f));
	  eb->setPosition(CEGUI::Point(0.0f, 0.00f));
	  eb->setFont("VeraSe-8");
	  eb->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNGUIConfPanel::mainEventHandler, this));
	  win->addChildWindow(eb);
	  _confPanelMap[EBname]  = current_param;
	}
	tmpName = isWinPresent(STname, "_");
	st = (CEGUI::StaticText*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"Vanilla/StaticText", tmpName.c_str());
	st->setSize(CEGUI::Size(0.70f, 1.00f));
	st->setPosition(CEGUI::Point(0.30f, 0.00f));
	st->setFont("VeraSe-8");
	st->setText(current_param->getLabel().c_str());
	std::string tooltip = current_param->getAltText() + getStringByType(current_param);
	st->setTooltipText(tooltip.c_str());
	win->addChildWindow(st);

	//TODO controle d'erreur sur le nom du controle

  }

  CEGUI::Window*  PNGUIConfPanel::addTab(std::string tabName)
  {
	//TODO ajouter des controles de taille en largeur et sur le nom

	
	std::string name = "PNConfPanel/Tab/" + removeWhitespace(tabName);
	std::string tmpName = isWinPresent(name, "_");
	
	
	CEGUI::DefaultWindow* win = (CEGUI::DefaultWindow*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"DefaultWindow", tmpName.c_str());
	if (tabName.length() > 8)
	  tabName = tabName.substr(0,8);
	win->setText(tabName.c_str());
	_tabControl->addChildWindow(win);
	_nbTAB++;

	// on doit augmenter la largeur
	/*if (_nbTAB > 5)
	{
	  _tabControl->setPosition(CEGUI::Point(0.10f, 0.00f))
	   _tabControl->setSize(CEGUI::Size(0.55f, 0.99f));
	}*/
	return win;
  }

  void	PNGUIConfPanel::addConfigurableObject(PNConfigurableObject* pncobj)
  {
	CEGUI::Window* tmpTab = addTab(pncobj->getLabel());
	
	//LIMIT DU TAB 20 elements
	if (pncobj->getNbParameters() > 20)
	  return;

	for (int idx = 0; idx < pncobj->getNbParameters(); idx++)
	{
	  PNConfigurableParameter* current_param = pncobj->getParameter(idx);

	  switch (current_param->getType())
	  {
	  case PN_PARAMTYPE_STRING:
	  case PN_PARAMTYPE_ACTIVESTRING:
	  case PN_PARAMTYPE_INT:
	  case PN_PARAMTYPE_REAL:
	  case PN_PARAMTYPE_BOOLEAN:
		addItem(tmpTab, current_param, idx);
		break;
	  default:
		break;
	  }
	}
  }


  std::string PNGUIConfPanel::removeWhitespace(const std::string& str)
  {
	std::string s;
	for (unsigned int i = 0; i < str.length(); ++i)
	  if ((unsigned char)str[i] > (unsigned char)' ')
		s += str[i];
	return s;
  }

}