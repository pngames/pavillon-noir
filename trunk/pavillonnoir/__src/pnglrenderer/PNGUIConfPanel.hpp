/*
* PNGUIConfPanel.hpp
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

#ifndef _PNGUICONFPANEL_HPP_
#define _PNGUICONFPANEL_HPP_

#include "myCEGUI.h"
#include <boost/thread/recursive_mutex.hpp>
#include "pndefs.h"
#include "pnevent.h"
#include "pnproperties.h"
#include "PNConfPanel.hpp"

namespace PN{

  /*class confPanelTEST : public PNConfigurableObject
  {
	
	std::string		  		_label;
	float _aReal;
	bool  _aBool;
	int	_aInt;
	std::string	_aString;

  protected:
	typedef std::vector<PNConfigurableParameter*> ParametersVector;
	ParametersVector			_params;
  public:
	confPanelTEST(std::string label = "No label");
	void						update(PNConfigurableParameter* p);
	int							getNbParameters() { return _params.size(); }
	PNConfigurableParameter*	getParameter(int idx) { return _params[idx]; }

	void						setModified() {}
	void						setUnmodified() {}
	const std::string&		getLabel() { return _label; }
  };*/

  class PNGUIConfPanel : PNConfPanel
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	boost::recursive_mutex			_mutex;
  protected:
  private:
	bool					_visibility;
	bool					_cursorVisibility;
	CEGUI::Window*			_pnConfPanel;
	CEGUI::TabControl*		_tabControl;
	CEGUI::Window*			_testTab;
	//static PNGUIConfPanel*	_instance;
	int						_nbTAB;
	std::vector<std::string> _vectTabNames;

	typedef std::map<std::string, PNConfigurableParameter*>	confPanelMap;
	 confPanelMap		_confPanelMap;
	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIConfPanel* getInstance();
	void  update();
	//void  update(PNConfigurableParameter* current_param);
	//void  update(PNConfigurableObject* pncobj);
  protected:
  private:
	void			addItem(CEGUI::Window* curTab,  PNConfigurableParameter* current_param, int idx);
	void			confPanelVisibility(pnEventType type, PNObject* source, PNEventData* data);
	void			addConfigurableObject(PNConfigurableObject* pncobj);
	std::string		removeWhitespace(const std::string& str);
	std::string		itemNameGenerator(const std::string& tabName, const std::string& itemName);
	CEGUI::Window*	addTab(std::string tabName);
	bool			mainEventHandler(const CEGUI::EventArgs& e);
	std::string		getStringByType(PNConfigurableParameter* current_param);
	std::string		isWinPresent(const std::string& name, const std::string& chartoadd);

	// std::string getWinNameByConfParam(PNConfigurableParameter* current_param);
	 void	update(std::string winName, PNConfigurableParameter* current_param);
	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIConfPanel();
	~PNGUIConfPanel();
  protected:
  private:
  };
}



#endif /*_PNGUICONFPANEL_HPP_*/
