/*
 * PNFXScriptListParameter.cpp
 * 
 * Description :
 * PNFXScriptListParameter definition
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


#include <fxkeys.h>
#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "pneditorcommon.h"
#include "pnproperties.h"

#include "pnevent.h"

#include "PNEventManager.hpp"
#include "PNPropertiesGrid.hpp"
#include "PNFXScriptListParameter.hpp"

using namespace std;
namespace fs = boost::filesystem;

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  // Map
  FXDEFMAP(PNFXScriptListParameter) PNFXScriptListParameterMap[]={
	  FXMAPFUNC(SEL_COMMAND,PNFXScriptListParameter::ID_DELETE_EVENT,PNFXScriptListParameter::onDeleteEvent),
	  FXMAPFUNC(SEL_COMMAND,PNFXScriptListParameter::ID_ADD_EVENT,PNFXScriptListParameter::onAddEvent),
	  FXMAPFUNC(SEL_COMMAND,PNFXScriptListParameter::ID_DELETE_SCRIPT,PNFXScriptListParameter::onDeleteScript),
	  FXMAPFUNC(SEL_COMMAND,PNFXScriptListParameter::ID_ADD_SCRIPT,PNFXScriptListParameter::onAddScript),
	  FXMAPFUNC(SEL_COMMAND,PNFXScriptListParameter::ID_EDIT_SCRIPTS,PNFXScriptListParameter::onEditScripts),
	  FXMAPFUNC(SEL_COMMAND,PNFXScriptListParameter::ID_ADD_EVENT_OK,PNFXScriptListParameter::onAddEventOK),
	  FXMAPFUNC(SEL_COMMAND,PNFXScriptListParameter::ID_ADD_EVENT_CANCEL,PNFXScriptListParameter::onAddEventCancel)
  };

  //////////////////////////////////////////////////////////////////////////
  FXIMPLEMENT(PNFXScriptListParameter,FXHorizontalFrame,PNFXScriptListParameterMap,ARRAYNUMBER(PNFXScriptListParameterMap))

	/*
	*	  Construct a PNFXScriptListParameter : 
	*		- all availables ScriptList for the selected waypoint are listed in a FXListBox
	*		- the coefficient of the selected link is visible in a FXTextField (real values only)
	*		- Two FXButtons ("Add" and "Delete") permit ScriptList list edition.
	*	  on creation this widget retrieves waypoints graph to edit it.
	*/
	PNFXScriptListParameter::PNFXScriptListParameter(FXComposite* p, PNConfigurableParameter* param)
	: FXHorizontalFrame(p)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptListParameter::PNFXScriptListParameter()");
	_parent = p;
	_param = param;
	_eventList = new FXListBox(this, NULL, 0, LAYOUT_FILL_X | FRAME_SUNKEN | FRAME_THICK, 0,0,10,0);
	_buttonAddEvent = new FXButton(this, "Add", NULL, this, ID_ADD_EVENT, FRAME_RAISED | FRAME_THICK);
	_buttonEditScripts = new FXButton(this, "Edit", NULL, this, ID_EDIT_SCRIPTS, FRAME_RAISED | FRAME_THICK);
	_buttonDeleteEvent = new FXButton(this, "Delete", NULL, this, ID_DELETE_EVENT, FRAME_RAISED | FRAME_THICK);
	//_event = new FXTextField(this, 8, NULL, 0, TEXTFIELD_NORMAL | FRAME_SUNKEN | FRAME_THICK | LAYOUT_SIDE_TOP);
	update();
  }

  PNFXScriptListParameter::~PNFXScriptListParameter()
  {
	delete _eventList;
	//delete _event;
	delete _buttonAddEvent;
	delete _buttonDeleteEvent;
  }
  //////////////////////////////////////////////////////////////////////////

  void	PNFXScriptListParameter::create()
  {
	FXHorizontalFrame::create();
	_eventList->create();
	_buttonDeleteEvent->create();
	_buttonAddEvent->create();
	_buttonEditScripts->create();
	//_event->create();

	return;
  }

  /*
  *	Builds ScriptList list for current parameter.
  */
  void	PNFXScriptListParameter::buildList(void)
  {
	scriptMap* smap = (scriptMap*)_param->getElem();

	_eventList->clearItems();
	for (scriptMap::iterator it = smap->begin(); it != smap->end(); it++)
	{
	  FXString			str = PNEventManager::getInstance()->getNameByType(it->first).c_str();

	  _eventList->appendItem(str,NULL,(void*)&(it->first));
	}
	_eventList->setNumVisible(_eventList->getNumItems());

	return;
  }

  long	PNFXScriptListParameter::onAddEvent(FXObject* obj,FXSelector sel,void* ptr)
  {
	_dbox = new FXDialogBox(_parent,"Add Event",DECOR_TITLE|DECOR_BORDER);
	
	FXVerticalFrame*	  vf = new FXVerticalFrame(_dbox, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame*	  hf = new FXHorizontalFrame(vf, LAYOUT_FILL_X|LAYOUT_LEFT);
	_event = new FXTextField(hf, 40, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN|FRAME_THICK|LAYOUT_SIDE_TOP);

	new FXHorizontalSeparator(vf, LAYOUT_FILL_X);

	FXHorizontalFrame*	  buttons = new FXHorizontalFrame(vf, LAYOUT_FILL_X|LAYOUT_RIGHT|LAYOUT_BOTTOM);
	new FXButton(buttons,"&Ok",NULL,this,ID_ADD_EVENT_OK,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);
	new FXButton(buttons,"&Cancel",NULL,this,ID_ADD_EVENT_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);

	_dbox->execute();
	update();
	return 1;
  }

  long	PNFXScriptListParameter::onAddEventOK(FXObject* obj,FXSelector sel,void* ptr)
  {
	scriptMap*	smap = (scriptMap*)_param->getElem();
	pnEventType	t = PNEventManager::getInstance()->getTypeByName(_event->getText().text());

	if (t > 1 && t <= PN_NUMBER_EVENTS)
	  if (smap->find(t) == smap->end())
		(*smap)[t] = new scriptList;
	
	_dbox->getApp()->stopModal(_dbox, TRUE);
	_dbox->close();
	update();
    return 1;
  }

  long	PNFXScriptListParameter::onAddEventCancel(FXObject* obj,FXSelector sel,void* ptr)
  {
	_dbox->getApp()->stopModal(_dbox, TRUE);
	_dbox->close();
	update();
	return 1;
  }

  /*
  *	Deletes selected event.
  */
  long	PNFXScriptListParameter::onDeleteEvent(FXObject* obj,FXSelector sel,void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptListParameter::onDelete");
	if (_eventList->getNumItems() != 0)
	{
	  scriptMap*		  smap = (scriptMap*)_param->getElem();
	  scriptMap::iterator it = smap->find(*((pnEventType*)_eventList->getItemData(_eventList->getCurrentItem())));

	  delete it->second;
	  smap->erase(it);
	  update();
	}

	return 1;
  }

  long	PNFXScriptListParameter::onEditScripts(FXObject* obj,FXSelector sel,void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXScriptListParameter::onEditScripts");
	if (_eventList->getNumItems() > 0)
	{
	  _dbox = new FXDialogBox(_parent,"Edit Scripts",DECOR_TITLE|DECOR_BORDER);

	  FXVerticalFrame* vf = new FXVerticalFrame(_dbox,LAYOUT_FILL_X|LAYOUT_FILL_Y);

	  FXGroupBox* gboxScripts =  new FXGroupBox(vf, "Scripts", LAYOUT_FILL_X|FRAME_GROOVE);
	  _scriptList = new FXListBox(gboxScripts, this, 0, LAYOUT_LEFT|FRAME_SUNKEN|FRAME_THICK);
	  
	  new FXHorizontalSeparator(vf, LAYOUT_FILL_X);

	  FXHorizontalFrame*	buttons = new FXHorizontalFrame(vf, LAYOUT_FILL_X);
	  new FXButton(buttons,"&Add",NULL,this,ID_ADD_SCRIPT,BUTTON_DEFAULT|LAYOUT_LEFT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	  new FXButton(buttons,"&Delete",NULL,this,ID_DELETE_SCRIPT,BUTTON_DEFAULT|LAYOUT_LEFT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	  new FXVerticalSeparator(buttons, LAYOUT_FILL_Y|LAYOUT_FIX_WIDTH,0,0,40,0);
	  new FXButton(buttons,"&OK",NULL,_dbox,FXDialogBox::ID_ACCEPT,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);

	  scriptMap* smap = (scriptMap*)_param->getElem();
	  scriptList* slist = smap->find(*(pnEventType*)_eventList->getItemData(_eventList->getCurrentItem()))->second;
	  for (scriptList::iterator i = slist->begin(); i != slist->end(); i++)
		_scriptList->appendItem((*i)->string().c_str(), NULL, *i);

	  _dbox->execute();
	  update();
	  delete _scriptList;
	  delete _dbox;
	}

	return 1;
  }

  long	PNFXScriptListParameter::onAddScript(FXObject* obj,FXSelector sel,void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::onAdd");
	FXFileDialog fd(this, "Choose script file");

	if (fd.execute())
	{
	  scriptMap* smap = (scriptMap*)_param->getElem();
	  scriptList* slist = smap->find(*(pnEventType*)_eventList->getItemData(_eventList->getCurrentItem()))->second;
	  FXString	str = fd.getFilename().substitute('\\', '/');;

	  char buf[512] = "";
	  getcwd(buf, 512);
	  FXString cwd(buf);

	  if (str.find(cwd.substitute('\\', '/')) == -1)
	  {
			FXMessageBox::error(this, MBOX_OK, "Path Error", "An error occured. Please check file path.");
	  }
	  else
	  {
		fs::path* p =  new fs::path(str.replace(0, strlen(buf) + 1, "").text(), fs::no_check);

		slist->push_back(p);

		std::string s = p->string();
		if (s.size() > 49)
		  s = s.substr(0, 15) + "[...]" + s.substr(s.size()-30, s.size());
		_scriptList->appendItem(s.c_str(), NULL, p);
		_scriptList->setNumVisible(_scriptList->getNumItems() < 5 ? _scriptList->getNumItems() : 5);
	  }
	}
	return 1;
  }

  long	PNFXScriptListParameter::onDeleteScript(FXObject* obj,FXSelector sel,void* ptr)
  {
	if (_scriptList->getNumItems() > 0)
	{
	  scriptMap* smap = (scriptMap*)_param->getElem();
	  scriptList* slist = smap->find(*(pnEventType*)_eventList->getItemData(_eventList->getCurrentItem()))->second;

	  for (scriptList::iterator it = slist->begin(); it != slist->end(); it++)
	  {
		if (*it == (fs::path*)_scriptList->getItemData(_scriptList->getCurrentItem()))
		{
		  slist->erase(it);
		  delete *it;
		  break;
		}
	  }

	  _scriptList->clearItems();
	  for (scriptList::iterator i = slist->begin(); i != slist->end(); i++)
		_scriptList->appendItem((*i)->string().c_str(), NULL, *i);
	  _scriptList->setNumVisible(_scriptList->getNumItems() < 5 ? _scriptList->getNumItems() : 5);
	}

	return 1;
  }

  /*
  *	Updates ScriptListlist
  */
  void	PNFXScriptListParameter::update(void)
  {
	_eventList->clearItems();
	buildList();
	_param->getConfigurableObject()->update(_param);
	_eventList->sortItems();

	return;
  }


  //////////////////////////////////////////////////////////////////////////
};
