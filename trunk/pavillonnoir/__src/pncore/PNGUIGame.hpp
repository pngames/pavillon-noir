/*
 * PNGUIGame.hpp
 * 
 * Description :
 * PNGUIGame declaration
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

#ifndef _PNGUIGAME_HPP_
# define _PNGUIGAME_HPP_

#include "myCEGUI.h"
#include <boost/thread/recursive_mutex.hpp>
#include <set>
#include <sstream>

#include "pnevent.h"
#include "pnproperties.h"

namespace PN{

  class PNRendererInterface;

  class PNGUIGame :  public PNConfigurableObject
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	boost::recursive_mutex	_mutex;

  public:
	typedef			enum
	{
	  STATE_CONSOLE		= 0x000001,
	  STATE_SDL_GRAB	= 0x000001 << 1,
	}				inputHandleModifier;
  private:
	static	PNGUIGame* _instance;
	int				_inputHandleModifier;
	CEGUI::Window* _rootWin;
	CEGUI::ProgressBar*	_lifeBar;

	typedef std::set<CEGUI::Key::Scan> BufferedKeysDownSet;
	BufferedKeysDownSet mBufferedKeysDown;

	std::string		_label;
	float			_lifeValue; 

	CEGUI::StaticImage* _statImg;
	typedef std::map<int, std::string> MapLife;
	MapLife _mapLife;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	static PNGUIGame*	getInstance();
	void  show();
	void  hide();
	CEGUI::Window*  getWindow();
	void  resetGUI();
	void  startGUI();
	//void  setLifeValue(float val);
	static void  changeLife(int val);
  private:
	bool eventMouseMoveHandler(const CEGUI::EventArgs& e);
	bool eventKeyPressedHandler(const CEGUI::EventArgs& e);
	bool eventKeyReleasedHandler(const CEGUI::EventArgs& e);
	bool eventMouseClickdHandler(const CEGUI::EventArgs& e);
    bool eventMouseButtonPressedHandler(const CEGUI::EventArgs& e);
    bool eventMouseButtonReleasedHandler(const CEGUI::EventArgs& e);
	bool eventMouseWheel(const CEGUI::EventArgs& e);
	void  inputHandleModifierState(pnEventType type, PNObject* source, PNEventData* data);
	void  inputHandleEsc(pnEventType type, PNObject* source, PNEventData* data);
	void  playerDied(pnEventType type, PNObject* source, PNEventData* data);
	static void  test(const std::string& tmp, std::istream& tmp2);
	void unsuscribeConsoleCommand();
	void suscribeConsoleCommand();

	//////////////////////////////////////////////////////////////////////////
	// ConfigurableObject

  protected:
	typedef std::vector<PNConfigurableParameter*> ParametersVector;
	ParametersVector			_params;
  public:
	void						update(PNConfigurableParameter* p);
	int							getNbParameters();
	PNConfigurableParameter*	getParameter(int idx);
	//void						reset();

	const std::string&			getName() {return _label;}
	const std::string&			getLabel() {return _label;}
	
	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
	public:
	PNGUIGame();
	~PNGUIGame();
  private:
	PNRendererInterface* _myri;	
	bool _skipFirstFrame;

  private:// FIXME : for test
	static void  _commandLoadMap(const std::string&, std::istream& i);
	static void  _commandRenderSK(const std::string&, std::istream& i);
	static void  _commandRenderM(const std::string&, std::istream& i);
	static void  _commandLooping(const std::string&, std::istream& i);
	static void  _commandSwitchMSK(const std::string&, std::istream& i);
	static void  _commandAnimSpeed(const std::string&, std::istream& i);
	static void  _commandRenderCameraMovingSpeed(const std::string&, std::istream& i);
	static void  _commandShowWP(const std::string&, std::istream& i);
	static void  _commandHideWP(const std::string&, std::istream& i);
	static void  _commandMoveTo(const std::string&, std::istream& i);
	static void  _commandSkyBox(const std::string&, std::istream& i);
	
	//////////////////////////////////////////////////////////////////////////
	
	static void  _setPhysics(const std::string&, std::istream& i);
	static void  _renderPhysics(const std::string&, std::istream& i);
	static void  _addForce(const std::string&, std::istream& i);
	static void  _listPhysicalObjects(const std::string&, std::istream& i);
	static void	 _setPhysicalObjectsDynamic(const std::string&, std::istream& i);
	static void	 _showObjectCoord(const std::string&, std::istream& i);

	//////////////////////////////////////////////////////////////////////////

	static void  _setScriptingDebug(const std::string&, std::istream& i);
  };
}
#endif /*_PNGUIGAME_HPP_*/
