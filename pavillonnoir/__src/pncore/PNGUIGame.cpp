/*
 * PNGUIGame.cpp
 * 
 * Description :
 * PNGUIGame definition
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

#include <iostream>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "pndefs.h"
#include "pnmath.h"
#include "pnevent.h"
#include "pnrender.h"
#include "pnresources.h"

#include "PNGUIGame.hpp"
#include "PNGUIStateManager.hpp"
#include "PNGUIEscMenu.hpp"
#include "PN3DCamera.hpp"

#include "PNConsole.hpp"

#include "PN3DSkeletonObject.hpp"  // FIXME : testing requirement

#include "PNSoundInterface.hpp"
#include "PNPhysicsInterface.hpp"
#include "PNGameEventData.hpp"
#include "PNGameInterface.hpp"
#include "PNGameMap.hpp"

#include "PNMatrixTR4f.hpp"
#include "PNQuatf.hpp"
#include "PNWayPoint.hpp"
#include "PNCharacter.hpp"

using namespace PN;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

void  PNGUIGame::_commandLoadMap(const std::string&, std::istream& i)
{
  std::string path;

  i >> path;

  if (path.size() == 0)
	PNConsole::writeError(PN_LOGLVL_ERROR, "You have to put a file name");

  PNGameLoadMapEventData data;
  data.mapName =  DEF::mapsFilePath + path;

  fs::path	file(data.mapName, fs::no_check);

  if (!fs::exists(file))
	PNConsole::writeError(PN_LOGLVL_ERROR, pnGetErrorString(PNEC_FILE_NOT_FOUND));

  PNEventManager::getInstance()->sendEvent(PN_EVENT_MU_START, 0, NULL);
  PNEventManager::getInstance()->sendEvent(PN_EVENT_ML_START, 0, &data);
}

void  PNGUIGame::_commandRenderSK(const std::string&, std::istream& i)
{
  if (PN3DCamera::getRenderCam()->getListObj().size() == 0)
	return ;

  bool	b;

  i >> b;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->getListObj().begin();

  if (obj != NULL)
  {
	PNLOCK(obj);

	if (b)
	  obj->setRenderMode(obj->getRenderMode() | PN3DObject::RENDER_MODEL);
	else
	  obj->setRenderMode(obj->getRenderMode() ^ PN3DObject::RENDER_MODEL);
  }
  else
  {
	PNConsole::writeLine("Error: there's no object");
  }
}

void  PNGUIGame::_commandRenderM(const std::string&, std::istream& i)
{
  if (PN3DCamera::getRenderCam()->getListObj().size() == 0)
	return ;

  bool	b;

  i >> b;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->getListObj().begin();

  if (obj != NULL)
  {
	PNLOCK(obj);

	if (b)
	  obj->setRenderMode(obj->getRenderMode() | PN3DSkeletonObject::RENDER_SKELETON);
	else
	  obj->setRenderMode(obj->getRenderMode() ^ PN3DSkeletonObject::RENDER_SKELETON);
  }
  else
  {
	PNConsole::writeLine("Error: there's no object");
  }
}

void  PNGUIGame::_commandSwitchMSK(const std::string& command, std::istream& i)
{
  if (PN3DCamera::getRenderCam()->getListObj().size() == 0)
	return ;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->getListObj().begin();

  if (obj != NULL)
  {
	PNLOCK(obj);

	if (obj->getRenderMode() & PN3DObject::RENDER_MODEL)
	{
	  obj->setRenderMode(obj->getRenderMode() ^ PN3DObject::RENDER_MODEL);
	  obj->setRenderMode(obj->getRenderMode() | PN3DSkeletonObject::RENDER_SKELETON);
	}
	else
	{
	  obj->setRenderMode(obj->getRenderMode() | PN3DObject::RENDER_MODEL);
	  obj->setRenderMode(obj->getRenderMode() ^ PN3DSkeletonObject::RENDER_SKELETON);
	}
  }
  else
  {
	PNConsole::writeLine("Error: there's no object");
  }
}

void  PNGUIGame::_commandLooping(const std::string&, std::istream& i)
{
  if (PN3DCamera::getRenderCam()->getListObj().size() == 0)
	return ;

  bool	b;

  i >> b;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->getListObj().begin();

  if (obj != NULL)
  {
	PNLOCK(obj);

	obj->setEnableLoop(b);

	PNConsole::writeLine("EnableLoop : %s", b ? "true" : "false");
  }
  else
  {
	PNConsole::writeLine("Error: there's no object");
  }
}

void  PNGUIGame::_commandAnimSpeed(const std::string&, std::istream& i)
{
  if (PN3DCamera::getRenderCam()->getListObj().size() == 0)
	return ;

  double speed;

  i >> speed;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->getListObj().begin();

  if (obj != NULL)
  {
	PNLOCK(obj);

	obj->setAnimSpeed(speed);

	PNConsole::writeLine("Speed changed : %f", speed);
  }
  else
  {
	PNConsole::writeLine("Error: there's no object");
  }
}

void  PNGUIGame::_commandRenderCameraMovingSpeed(const std::string&, std::istream& i)
{
  float speed;

  i >> speed;

  PN3DCamera* camera = PN3DCamera::getRenderCam();

  if (camera != NULL)
  {
	PNLOCK(camera);

	camera->setMovingSpeed(speed);

	PNConsole::writeLine("Render Camera speed changed : %f", speed);
  }
  else
	PNConsole::writeLine("Error: there's no render camera");
}


void  PNGUIGame::_commandShowWP(const std::string&, std::istream& i)
{
  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	PN3DObject*	obj = it->second;

	if (obj != NULL && obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	{
	  obj->setRenderMode(PN3DObject::RENDER_MODEL);
	}
  }
}

void  PNGUIGame::_commandHideWP(const std::string&, std::istream& i)
{
  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	PN3DObject*	obj = it->second;

	if (obj != NULL && obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	{
	  obj->setRenderMode(0);
	}
  }
}

//FIXME: this is the cradest way to test PF!
void  PNGUIGame::_commandMoveTo(const std::string&, std::istream& i)
{
  PN3DObjList::iterator it;
  PNPoint				p(4900.0, 0.0, 4900.0);

  PNGameInterface::getInstance()->getGameMap()->executeScript("temp/ia_tests.lua");
 // for (it = PN3DCamera::getRenderCam()->_list3DObj.begin(); it != PN3DCamera::getRenderCam()->_list3DObj.end(); it++)
 // {
	//PN3DObject*	obj = (PN3DObject*)*it;

	//if (obj != NULL && obj->getObjType() == PN3DObject::OBJTYPE_CHARACTER)
	//{
	//  ((PNCharacter*)obj)->moveTo(p);
	//  pnerror(PN_LOGLVL_DEBUG, "a PNCharacter has been told to move");
	//}
 // }
}

  //////////////////////////////////////////////////////////////////////////

void  PNGUIGame::_setPhysics(const std::string&, std::istream& i)
{
  bool	b;
  i >> b;

  if (b == true)
  {
	PNConsole::writeLine("Physical simulation activated");
	PNPhysicsInterface::getInstance()->setPause(false);
  }
  else
  {
	PNConsole::writeLine("Physical simulation desactivated");
	PNPhysicsInterface::getInstance()->setPause(true);
  }
}

void  PNGUIGame::_renderPhysics(const std::string&, std::istream& i)
{
  bool	b;
  i >> b;

  for (PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin(); it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end(); it++)
  {
	PN3DObject*	current_obj = it->second;
	PNLOCK_BEGIN(current_obj);
	{
	  if (current_obj->getPhysicalObject())
	  {
		if (b == true)
		  current_obj->setRenderMode(current_obj->getRenderMode() | PN3DObject::RENDER_PHYSICAL);
		else
		  current_obj->setRenderMode(current_obj->getRenderMode() ^ PN3DObject::RENDER_PHYSICAL);
	  }
	}
	PNLOCK_END(current_obj);
  }
}

void  PNGUIGame::_setAlldynamic(const std::string&, std::istream& i)
{
  bool	b;
  i >> b;

  if (b == true)
  {
	PNPhysicsInterface::getInstance()->setAllPhysicalObjectsStatic(false);
  }
  else
  {
	PNPhysicsInterface::getInstance()->setAllPhysicalObjectsStatic(true);
  }
}

void  PNGUIGame::_addForce(const std::string&, std::istream& i)
{
 // FIXME, deprecated
}

void  PNGUIGame::_setScriptingDebug(const std::string&, std::istream& i)
{
 /* bool	b;
  i >> b;

  if (b == true)
  {
	PNConsole::writeLine("Lua debug logging activated");
	PNGameInterface::getInstance()->setDebug(true);
  }
  else
  {
	PNConsole::writeLine("Lua debug logging desactivated");
	PNGameInterface::getInstance()->setDebug(false);
  }*/
}

//////////////////////////////////////////////////////////////////////////
PNGUIGame*	PNGUIGame::_instance = NULL;

PNGUIGame::PNGUIGame()
{
  _label = "PNGUIGame";
  _rootWin = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNGUIGame.layout");
  CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_rootWin);

  _rootWin->activate();

  _lifeBar = (CEGUI::ProgressBar*)CEGUI::WindowManager::getSingleton().getWindow("PNGUIGame/lifeBar");
  _myri = PNRendererInterface::getInstance();
  _skipFirstFrame = false;
  _inputHandleModifier = 0;

  //register main events for the game to the root window 
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseMove, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseMoveHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNGUIGame::eventKeyPressedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventKeyUp, CEGUI::Event::Subscriber(&PNGUIGame::eventKeyReleasedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseClickdHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseWheel, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseWheel, this));

  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL, &_lifeValue, "life bar value", "life bar value"));
 // CEGUI::MouseCursor::getSingleton().hide();
}

PNGUIGame::~PNGUIGame()
{
  resetGUI();
  _rootWin->destroy();
}

PNGUIGame*	PNGUIGame::getInstance()
{
  if (_instance == NULL)
	_instance = new PNGUIGame();
  return _instance;
}

void PNGUIGame::startGUI()
{
  PNGUIStateManager::getInstance()->setMainState(PNGUIStateManager::INGAME);
  PNGUIStateManager::getInstance()->setSubState(PNGUIStateManager::NONE);

  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("loadmap", &PNGUIGame::_commandLoadMap, "Load game map, parameter : string MapFileName");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("rendersk", &PNGUIGame::_commandRenderSK, "Render skeleton, 0=false or 1=true");
  PNConsole::addFonction("renderm", &PNGUIGame::_commandRenderM, "Render model, 0=false or 1=true");
  PNConsole::addFonction("looping", &PNGUIGame::_commandLooping, "Loop animation, 0=false or 1=true");
  PNConsole::addFonction("animspeed", &PNGUIGame::_commandAnimSpeed, "Set animation speed, 1.0=normal");
  PNConsole::addFonction("switchmsk", &PNGUIGame::_commandSwitchMSK, "Switch between model rendering or skeleton rendering");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("rcspeed", &PNGUIGame::_commandRenderCameraMovingSpeed, "Set render camera moving speed, 1.0=normal");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("physics", &PNGUIGame::_setPhysics, "Physical simulation, 0=false or 1=true");
  PNConsole::addFonction("renderphysics", &PNGUIGame::_renderPhysics, "Display object's AABB, 0=false or 1=true");
  PNConsole::addFonction("addforce", &PNGUIGame::_addForce, "Add force to a physical object, addforce object_number x y z duration");
  PNConsole::addFonction("setdyn", &PNGUIGame::_setAlldynamic, "Set all physical objects dynamic, 0=false or 1=true");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("setscriptingdebug", &PNGUIGame::_setScriptingDebug, "Activates or deactivates the scripting's debug logging to file \"pnscript.log\", 0=false or 1=true");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("showwp", &PNGUIGame::_commandShowWP, "Show WayPoints");
  PNConsole::addFonction("hidewp", &PNGUIGame::_commandHideWP, "Hide WayPoints");
  PNConsole::addFonction("moveto", &PNGUIGame::_commandMoveTo, "Move selected character to given position");

  PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_GRAB_OFF, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_GRAB_ON, EventCallback(this, &PNGUIGame::inputHandleModifierState));
   PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_ESC, EventCallback(this, &PNGUIGame::inputHandleEsc));

  show();
}

void PNGUIGame::resetGUI()
{
  PNConsole::delFonction("loadmap");
  /////////////////////////////////////////////
  PNConsole::delFonction("rendersk");
  PNConsole::delFonction("renderm");
  PNConsole::delFonction("looping");
  PNConsole::delFonction("animspeed");
  PNConsole::delFonction("switchmsk");
  /////////////////////////////////////////////
  PNConsole::delFonction("rcspeed");
  /////////////////////////////////////////////
  PNConsole::delFonction("newsound");
  PNConsole::delFonction("playsound");
  PNConsole::delFonction("stopsound");
  PNConsole::delFonction("pausesound");
  PNConsole::delFonction("loadedsounds");
  PNConsole::delFonction("changesoundvolume");
  /////////////////////////////////////////////
  PNConsole::delFonction("physics");
  PNConsole::delFonction("renderphysics");
  PNConsole::delFonction("addforce");
  PNConsole::delFonction("setdyn");
  /////////////////////////////////////////////
  PNConsole::delFonction("setscriptingdebug");
  /////////////////////////////////////////////
  PNConsole::delFonction("showwp");
  PNConsole::delFonction("hidewp");
  PNConsole::delFonction("moveto");

  PNEventManager::getInstance()->deleteCallback(PN_EVENT_CONSOLE, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_SDL_GRAB_OFF, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_SDL_GRAB_ON, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_SDL_ESC, EventCallback(this, &PNGUIGame::inputHandleEsc));

  hide();
}

void  PNGUIGame::inputHandleEsc(pnEventType type, PNObject* source, PNEventData* data)
{
  if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::INGAME &&
	PNGUIStateManager::getInstance()->getSubState() == PNGUIStateManager::NONE)
  {
	resetGUI();
	PNGUIEscMenu::getInstance()->startGUI();
  }
}

/*!
\brief
Called when the mouse wheel is moving in game screen
*/
bool PNGUIGame::eventMouseWheel(const CEGUI::EventArgs& e)
{
  CEGUI::MouseEventArgs* me = (CEGUI::MouseEventArgs*)&e;
  PN3DCamera* cam = PN3DCamera::getRenderCam();
  
  //cam->moveZ( me->wheelChange*2);
  //cam->moveZ( me->wheelChange*2);
  //cam->moveUD(me->wheelChange*2);
	
  return true;
}

/*!
\brief
Called when the mouse is moving in game screen
*/
bool PNGUIGame::eventMouseMoveHandler(const CEGUI::EventArgs& e)
{
  CEGUI::MouseEventArgs* me = (CEGUI::MouseEventArgs*)&e;
  PN3DCamera* cam = PN3DCamera::getRenderCam();

  //PNQuatf	rot;
  //rot.fromAxisDegrees(PNVector3f::UNIT_Y, 90.0f);

  //cam->setOrient(rot);
  PNGameMouseMoveEventData mouseData(PNPoint(-me->moveDelta.d_x, -me->moveDelta.d_y, 0.0));
  //////////////////////////////////////////////////////////////////////////
  PNEventManager::getInstance()->sendEvent(PN_EVENT_MOUSE_MOVE, NULL, &mouseData);
  //cam->rotatePitchRadians((pnfloat)DEGREE_TO_RADIAN(-me->moveDelta.d_y));
  //cam->rotateYawRadians((pnfloat)DEGREE_TO_RADIAN(-me->moveDelta.d_x));

  return true;
}

/*!
\brief
Called when a key is pressed in game screen
*/
bool PNGUIGame::eventKeyPressedHandler(const CEGUI::EventArgs& e)
{
  std::cout << "pressed: ";

  //TODO : utiliser un vector pour stocker la liste des touches et leur correspondance ascii : DONE

  CEGUI::KeyEventArgs* me = (CEGUI::KeyEventArgs*)&e;
  // Update keydown map
  mBufferedKeysDown.insert(static_cast<CEGUI::Key::Scan>(me->scancode));

  PN3DCamera*	cam = PN3DCamera::getRenderCam();

  PN3DObject*	obj = NULL;
  
  if (PNGameInterface::getInstance()->getGameMap()->getEntityList().size() > 0)
  {
	obj = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin()->second;
  }

  PNVector3f axis(1.0f, 0.0f, 0.0f);
  pnfloat phi;
  static PNMatrixTR4f  mat;
  PNQuatf rot;

//  std::cout << obj->getFile().string().c_str() << std::endl;

  switch(me->scancode)
  {
	  PNGameActionEventData *actionEvent;
	//////////////////////////////////////////////////////////////////////////
	// TRANSLATION
  case CEGUI::Key::R : //key "r" move top
	std::cout << "top";
	cam->addMovingState(PN3DObject::STATE_T_TOP);
	break;

  case CEGUI::Key::F : //key "f" move top
	std::cout << "back";
	cam->addMovingState(PN3DObject::STATE_T_BACK);
	break;

  case CEGUI::Key::Z : //key "z" move forward
  case CEGUI::Key::W :
	std::cout << "forward";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveForward","Player","null",true));
	cam->addMovingState(PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::S : //key "s" move backward
	std::cout << "backward";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveBackward","Player","null",true));
	cam->addMovingState(PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::A :
  case CEGUI::Key::Q : //key "q" step left
	std::cout << "left";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveLeft","Player","null",true));
	cam->addMovingState(PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::D : //key "d" step right
	std::cout << "right";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveRight","Player","null",true));
	cam->addMovingState(PN3DObject::STATE_T_RIGHT);
	break;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////player move/////////////////////
  case CEGUI::Key::Numpad8 : //key "z" move forward
	std::cout << "forward\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveForward","Player","null",true));
	//cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::Numpad5 : //key "s" move backward
	std::cout << "backward\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveBackward","Player","null",true));
	//cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::Numpad4 : //key "q" step left
	std::cout << "left\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("RotateLeft","Player","null",true));
	//cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::Numpad6 : //key "d" step right
	std::cout << "right\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("RotateRight","Player","null",true));
	//cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_RIGHT);
	break;

	//////////////////////////////////////////////////////////////////////////
	// ROTATION
  case CEGUI::Key::ArrowLeft :
	std::cout << "ArrowLeft";
	cam->addMovingState(PN3DObject::STATE_R_LEFT);
	break;
  case CEGUI::Key::ArrowRight :
	std::cout << "ArrowRight";
	cam->addMovingState(PN3DObject::STATE_R_RIGHT);
	break;
  case CEGUI::Key::ArrowUp :
	std::cout << "ArrowUp";
	cam->addMovingState(PN3DObject::STATE_R_TOP);
	break;
  case CEGUI::Key::ArrowDown :
	std::cout << "ArrowDown";
	cam->addMovingState(PN3DObject::STATE_R_BACK);
	break;

	//////////////////////////////////////////////////////////////////////////
	// LOCK
  case CEGUI::Key::LeftControl :
  case CEGUI::Key::RightControl :
	std::cout << "Control";
	cam->setTargetMode(PN3DObject::TMODE_VIEW_ABS_LOCKED);
	cam->setTarget(obj);
	break;

	//////////////////////////////////////////////////////////////////////////

  case CEGUI::Key::PageUp : //key "q" step left
	std::cout << "PageUp";
	break;

  case CEGUI::Key::PageDown : //key "d" step right
	std::cout << "PageDown";
	break;

  case CEGUI::Key::Return : // key Return start animation
	std::cout << "Return";
	if (obj != NULL)
	  obj->startAnimation(0, 0);
	break;

  default:
	std::cout << "not managed key";
	break;
  }

  std::cout << std::endl;

  return true;
}

/*!
\brief
Called when a key is released in game screen
*/
bool PNGUIGame::eventKeyReleasedHandler(const CEGUI::EventArgs& e)
{
  std::cout << "release : ";

  CEGUI::KeyEventArgs* me = (CEGUI::KeyEventArgs*)&e;
  // Update keydown map
  mBufferedKeysDown.erase(static_cast<CEGUI::Key::Scan>(me->scancode));

  PN3DCamera* cam = PN3DCamera::getRenderCam();

  //std::cout << me->scancode << " " << CEGUI::Key::W;

  switch(me->scancode) 
  {
	//////////////////////////////////////////////////////////////////////////
	// TRANSLATION
  case CEGUI::Key::R : //key "r" move top
	std::cout << "top";
	cam->subMovingState(PN3DObject::STATE_T_TOP);
	break;

  case CEGUI::Key::F : //key "f" move top
	std::cout << "back";
	cam->subMovingState(PN3DObject::STATE_T_BACK);
	break;

  case CEGUI::Key::Z : //key "z" move forward
  case CEGUI::Key::W :
	std::cout << "forward";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveForward","Player","null",false));
	cam->subMovingState(PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::S : //key "s" move backward
	std::cout << "backward";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveBackward","Player","null",false));
	cam->subMovingState(PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::A :
  case CEGUI::Key::Q : //key "q" step left
	std::cout << "left";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveRight","Player","null",false));
	cam->subMovingState(PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::D : //key "d" step right
	std::cout << "right";
	//PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveLeft","Player","null",false));
	cam->subMovingState(PN3DObject::STATE_T_RIGHT);
	break;
    //////////////////////////////////////////////////////////////////////////
    // move player
  case CEGUI::Key::Numpad8 : //  move forward
	std::cout << "forward\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveForward","Player","null",false));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::Numpad5 : // move backward
	std::cout << "backward\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("MoveBackward","Player","null",false));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::Numpad6 : // step left
	std::cout << "left\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("RotateRight","Player","null",false));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::Numpad4 : // step right
	std::cout << "right\n";
	PNEventManager::getInstance()->addEvent(PN_EVENT_GAME_ACTION, NULL, new PNGameActionEventData("RotateLeft","Player","null",false));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_RIGHT);
	break;

	//////////////////////////////////////////////////////////////////////////
	// ROTATION
  case CEGUI::Key::ArrowLeft :
	std::cout << "ArrowLeft";
	cam->subMovingState(PN3DObject::STATE_R_LEFT);
	break;
  case CEGUI::Key::ArrowRight :
	std::cout << "ArrowRight";
	cam->subMovingState(PN3DObject::STATE_R_RIGHT);
	break;
  case CEGUI::Key::ArrowUp :
	std::cout << "ArrowUp";
	cam->subMovingState(PN3DObject::STATE_R_TOP);
	break;
  case CEGUI::Key::ArrowDown :
	std::cout << "ArrowDown";
	cam->subMovingState(PN3DObject::STATE_R_BACK);
	break;

	//////////////////////////////////////////////////////////////////////////
	// LOCK
  case CEGUI::Key::LeftControl :
  case CEGUI::Key::RightControl :
	std::cout << "Control";
	cam->setTarget(NULL);
	cam->setTargetMode(PN3DObject::TMODE_FREE);
	break;

  default:
	std::cout << "not managed key";
	break;
  }

  std::cout << std::endl;

  return true;
}

/*!
\brief
Called when there is a mouse click
*/
bool PNGUIGame::eventMouseClickdHandler(const CEGUI::EventArgs& e)
{ 
  CEGUI::MouseEventArgs* me = (CEGUI::MouseEventArgs*)&e;

  if (me->button == CEGUI::LeftButton)
	std::cout << "game left click" << std::endl;
  if (me->button == CEGUI::RightButton)
	std::cout << "game right click" << std::endl;
  if (me->button == CEGUI::MiddleButton)
	std::cout << "game middle click" << std::endl;
  return true;
}

/*!
\brief
Called when the console is visible or when the SDL mouse cursor is visible.
If one of them is visible the game screen don't receive events.
*/
void  PNGUIGame::inputHandleModifierState(pnEventType type, PNObject* source, PNEventData* data)
{
  switch(type) {
case PN_EVENT_SDL_GRAB_OFF:
  _inputHandleModifier = _inputHandleModifier | STATE_SDL_GRAB;
  break;
case PN_EVENT_SDL_GRAB_ON:
    if (_inputHandleModifier & STATE_SDL_GRAB)
  _inputHandleModifier = _inputHandleModifier ^ STATE_SDL_GRAB;
  break;

case PN_EVENT_CONSOLE:
  if (_inputHandleModifier & STATE_CONSOLE)
	_inputHandleModifier = _inputHandleModifier ^ STATE_CONSOLE;
  else
	_inputHandleModifier = _inputHandleModifier | STATE_CONSOLE;
	break;
default:
  break;
  }

  if (_inputHandleModifier != 0)
  {
  _rootWin->setMutedState(true);
  }
  if (_inputHandleModifier == 0)
  {
   _rootWin->activate();
   _rootWin->setMutedState(false);
  }
}

void  PNGUIGame::setLifeValue(float val)
{
  PNLOCK(this);
  _lifeBar->setProgress(val);
}

void  PNGUIGame::show()
{
  _rootWin->setMutedState(false);
  _rootWin->show();
  _rootWin->activate();
  CEGUI::MouseCursor::getSingleton().hide();
}

void  PNGUIGame::hide()
{
  _rootWin->setMutedState(true);
  _rootWin->hide();
}

CEGUI::Window*  PNGUIGame::getWindow()
{
  return (_rootWin);
}

void  PNGUIGame::update(PNConfigurableParameter* p)
{

}

int	PNGUIGame::getNbParameters()
{
  return _params.size();
}

PNConfigurableParameter*  PNGUIGame::getParameter(int idx)
{
 return _params[idx];
}

//////////////////////////////////////////////////////////////////////////
};
