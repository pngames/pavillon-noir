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

#define MAPID "id_1"
#define PLAYERID "id_4"

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
#include "PNGUIDeath.hpp"
#include "PNGUIWin.hpp"
#include "PNGUIEscMenu.hpp"
#include "PN3DCamera.hpp"
#include "PNGUIChatWindow.hpp"

#include "PNConsole.hpp"

#include "PN3DSkeletonObject.hpp"  // FIXME : testing requirement

#include "PNSoundInterface.hpp"
#include "PNPhysicsInterface.hpp"
#include "PNPhysicalObject.hpp"
#include "PNGameEventData.hpp"
#include "PNGameInterface.hpp"
#include "PNGameMap.hpp"

#include "PNPoint2f.hpp"
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
  data.mapName = PNResourcesManager::getInstance()->findPath(PNRT_map, path);

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

  if (obj != NULL && obj->getObjType() == PN3DObject::OBJTYPE_3DSKELETONOBJ)
  {
	PN3DSkeletonObject*	sk = (PN3DSkeletonObject*)obj;

	sk->setEnableLoop(b);

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

  if (obj != NULL && obj->getObjType() == PN3DObject::OBJTYPE_3DSKELETONOBJ)
  {
	PN3DSkeletonObject*	sk = (PN3DSkeletonObject*)obj;

	sk->setAnimSpeed(speed);

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

//FIXME: this is the ugliest way to test PF!
void  PNGUIGame::_commandMoveTo(const std::string&, std::istream& i)
{
  PN3DObjList::iterator it;
  PNPoint3f				p(4900.0, 0.0, 4900.0);

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

void  PNGUIGame::_commandSkyBox(const std::string&, std::istream& i)
{
  bool	enable;

  i >> enable;

  PNRendererInterface::getInstance()->setSkyBoxEnabled(enable);
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

void  PNGUIGame::_addForce(const std::string&, std::istream& i)
{
  std::string objectid;
  pnfloat x = 0.0f;
  pnfloat y = 0.0f;
  pnfloat z = 0.0f;
  pnfloat duration = 0.0f;
  pnfloat magnitude = 0.0f;

  i >> objectid;
  i >> x;
  i >> y;
  i >> z;
  i >> magnitude;
  i >> duration;

  if (!(x == 0.0f && y == 0.0f && z == 0.0f && duration == 0.0f))
  {
	PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().find(objectid.c_str());
	  
	if (it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end())
	{
	  PN3DObject* current_obj = it->second;
	  PNVector3f vec;
	  vec.x = x;
	  vec.y = y;
	  vec.z = z;

	  current_obj->getPhysicalObject()->addForce(vec, magnitude, duration, true);
	}
	else
	  PNConsole::writeLine("object %s does not exist", objectid.c_str());
  }
  else
	PNConsole::writeLine("Syntax : addforce objectid x y z duration");
}

void  PNGUIGame::_listPhysicalObjects(const std::string&, std::istream& i)
{
  // TODO
}

void  PNGUIGame::_setPhysicalObjectsDynamic(const std::string&, std::istream& i)
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

void PNGUIGame::_showObjectCoord(const std::string&, std::istream& i)
{
  std::string objectid;
  i >> objectid;

  PNGameMap::ObjMap::const_iterator it = PNGameInterface::getInstance()->getGameMap()->getEntityList().find(objectid.c_str());

  if (it != PNGameInterface::getInstance()->getGameMap()->getEntityList().end())
  {
	PN3DObject* current_obj = it->second;
	PNPoint3f coords = current_obj->getCoord();
	
	PNConsole::writeLine("%s coords : %f, %f, %f", objectid.c_str(), coords.x, coords.y, coords.z);
  }
  else
	PNConsole::writeLine("object %s does not exist", objectid.c_str());
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

  _rootWin = CEGUI::WindowManager::getSingleton().loadWindowLayout(PNResourcesManager::getInstance()->findPath(PNRT_layout, "PNGUIGame.layout"));

  CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_rootWin);

  _rootWin->activate();

  _myri = PNRendererInterface::getInstance();
  _skipFirstFrame = false;
  _inputHandleModifier = 0;

  //register main events for the game to the root window 
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseMove, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseMoveHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNGUIGame::eventKeyPressedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventKeyUp, CEGUI::Event::Subscriber(&PNGUIGame::eventKeyReleasedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseClickdHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseButtonPressedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseButtonUp, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseButtonReleasedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseWheel, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseWheel, this));

  _mapLife[0] = "FioleImages/fiole_OK";
  _mapLife[1] = "FioleImages/fiole_LIGHT";
  _mapLife[2] = "FioleImages/fiole_SERIOUS";
  _mapLife[3] = "FioleImages/fiole_DANGEROUS";
  _mapLife[4] = "FioleImages/fiole_CRITIC";
  _mapLife[5] = "FioleImages/fiole_COMA";
  _mapLife[6] = "FioleImages/fiole_LETHAL";

 _statImg = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().getWindow("PNGUIGame/fiole");
 _miniMap = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().getWindow("PNGUIGame/MiniMap");
 _miniMapPoint = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().getWindow("PNGUIGame/MiniMapPos");

  PNGUIChatWindow::getInstance();
  PNGUIDeath::getInstance();
  PNGUIWin::getInstance();

  _miniMap->hide(); 
  _miniMapPoint->hide();

  _mapObj = NULL;
  _playerObj = NULL;
  _mapSizeX = 0.0f;
  _mapSizeY = 0.0f;

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

void PNGUIGame::suscribeConsoleCommand()
{
  //////////////////////////////////////////////////////////////////////////
  // DO NOT FORGET TO DELETE YOUR FUNCTIONS IN unsuscribeConsoleCommand !!!!
  //////////////////////////////////////////////////////////////////////////


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
  PNConsole::addFonction("renderphysics", &PNGUIGame::_renderPhysics, "Display object's physical entities, 0=false or 1=true");
  PNConsole::addFonction("addforce", &PNGUIGame::_addForce, "Add force to a physical object, addforce objectid x y z magnitude duration");
  PNConsole::addFonction("listphysics", &PNGUIGame::_listPhysicalObjects, "List physical objects");
  PNConsole::addFonction("setdyn", &PNGUIGame::_setPhysicalObjectsDynamic, "Set all physical objects dynamic, 0=false or 1=true");
  PNConsole::addFonction("showobjcoord", &PNGUIGame::_showObjectCoord, "Display the object coordinates, showobjcoord objectid");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("setscriptingdebug", &PNGUIGame::_setScriptingDebug, "Activates or deactivates the scripting's debug logging to file \"pnscript.log\", 0=false or 1=true");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("showwp", &PNGUIGame::_commandShowWP, "Show WayPoints");
  PNConsole::addFonction("hidewp", &PNGUIGame::_commandHideWP, "Hide WayPoints");
  PNConsole::addFonction("moveto", &PNGUIGame::_commandMoveTo, "Move selected character to given position");
  //////////////////////////////////////////////////////////////////////////
  PNConsole::addFonction("skybox", &PNGUIGame::_commandSkyBox, "Active/unactive skybox");

 
}

void PNGUIGame::unsuscribeConsoleCommand()
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
 /* PNConsole::delFonction("newsound");
  PNConsole::delFonction("playsound");
  PNConsole::delFonction("stopsound");
  PNConsole::delFonction("pausesound");
  PNConsole::delFonction("loadedsounds");
  PNConsole::delFonction("changesoundvolume");*/
  /////////////////////////////////////////////
  PNConsole::delFonction("physics");
  PNConsole::delFonction("renderphysics");
  PNConsole::delFonction("addforce");
  PNConsole::delFonction("listphysics");
  PNConsole::delFonction("setdyn");
  /////////////////////////////////////////////
  PNConsole::delFonction("setscriptingdebug");
  /////////////////////////////////////////////
  PNConsole::delFonction("showwp");
  PNConsole::delFonction("hidewp");
  PNConsole::delFonction("moveto");
  /////////////////////////////////////////////
  PNConsole::delFonction("skybox");
  
}

void PNGUIGame::startGUI()
{
  setMiniMapTools();
  PNGUIStateManager::getInstance()->setMainState(PNGUIStateManager::INGAME);
  PNGUIStateManager::getInstance()->setSubState(PNGUIStateManager::NONE);

  PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_GRAB_OFF, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_GRAB_ON, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_ESC, EventCallback(this, &PNGUIGame::inputHandleEsc));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_OVER, EventCallback(this, &PNGUIGame::playerDied));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_WIN, EventCallback(this, &PNGUIGame::playerWin));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_LIFEVAL, EventCallback(this, &PNGUIGame::changeLife));
  PNEventManager::getInstance()->addCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNGUIGame::startChat));
  PNEventManager::getInstance()->addCallback(PN_EVENT_OM, EventCallback(this, &PNGUIGame::updateCoordPlayer));

  suscribeConsoleCommand();
  show();
}

void PNGUIGame::resetGUI()
{
  cleanMiniMapTools();
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_CONSOLE, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_SDL_GRAB_OFF, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_SDL_GRAB_ON, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_SDL_ESC, EventCallback(this, &PNGUIGame::inputHandleEsc));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_OVER, EventCallback(this, &PNGUIGame::playerDied));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_WIN, EventCallback(this, &PNGUIGame::playerWin));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_LIFEVAL, EventCallback(this, &PNGUIGame::changeLife));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_GAME_ACTION, EventCallback(this, &PNGUIGame::startChat));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_OM, EventCallback(this, &PNGUIGame::updateCoordPlayer));
  unsuscribeConsoleCommand();
  hide();
}

void  PNGUIGame::changeLife(pnEventType type, PNObject* source, PNEventData* data)
{
  PNLOCK(this);
  
  int val = ((PNGameLifeValEventData*)data)->lifeVal;
  
  if (val < 7)
  {
	_statImg->setImage("FioleImages", _mapLife[val]);
  }
}

void  PNGUIGame::playerDied(pnEventType type, PNObject* source, PNEventData* data)
{
  if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::INGAME &&
	PNGUIStateManager::getInstance()->getSubState() == PNGUIStateManager::NONE)
  {
	this->resetGUI();
	PNGUIDeath::getInstance()->startGUI();
  }
}

void  PNGUIGame::playerWin(pnEventType type, PNObject* source, PNEventData* data)
{
  if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::INGAME &&
	PNGUIStateManager::getInstance()->getSubState() == PNGUIStateManager::NONE)
  {
	this->resetGUI();
	PNGUIWin::getInstance()->startGUI();
  }
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

void  PNGUIGame::startChat(pnEventType type, PNObject* source, PNEventData* data)
{
  if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::INGAME &&
	PNGUIStateManager::getInstance()->getSubState() == PNGUIStateManager::NONE)
  {
	if (((PNGameActionEventData*)data)->action == "Chat" && ((PNGameActionEventData*)data)->value == 1.0)
	{
	  resetGUI();
	  PNGUIChatWindow::getInstance()->startGUI(((PNGameActionEventData*)data)->targetId);
	}
  }
}

void PNGUIGame::setMiniMapTools()
{
  _playerObj = PNGameInterface::getInstance()->getGameMap()->getPlayer();
  _mapObj = PNGameInterface::getInstance()->getGameMap()->getGround();

  if (_playerObj != NULL && _mapObj != NULL)
  {
	_miniMap->show();
	_miniMapPoint->show();

	PNPoint2f mapMin(_mapObj->getMin().x, _mapObj->getMin().z);
	PNPoint2f mapMax(_mapObj->getMax().x, _mapObj->getMax().z);


	_mapSizeX = mapMax.x - mapMin.x;
	_mapSizeY = mapMax.y - mapMin.y;

	float tmpX = (_playerObj->getCoord().x - _mapObj->getMin().x)/ _mapSizeX;
	float tmpZ = (_playerObj->getCoord().z - _mapObj->getMin().z /*+ 3359*/) / _mapSizeY;

	_miniMapPoint->setPosition(CEGUI::Point(tmpX-0.02f, tmpZ-0.03f));
  }
  else
  {
	_miniMap->hide(); 
	_miniMapPoint->hide();
  }
}

void PNGUIGame::cleanMiniMapTools()
{
  _playerObj = NULL;
  _mapObj = NULL;

  _mapSizeX = 0.0f;
  _mapSizeY = 0.0f;
}

void  PNGUIGame::updateCoordPlayer(pnEventType type, PNObject* source, PNEventData* data)
{
  PNLOCK(this);

  if (((PN3DObject*)source)->getId() == PLAYERID)
  {
	if (_playerObj != NULL && _mapObj != NULL)
	{
	  PNPoint3f coord = ((PN3DObject*)source)->getCoord();

	  float tmpX = (coord.x - _mapObj->getMin().x)/ _mapSizeX;
	  float tmpZ = (coord.z - _mapObj->getMin().z) / _mapSizeY;

	  _miniMapPoint->setPosition(CEGUI::Point(tmpX-0.02f, tmpZ-0.03f));
	}
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
  PNGameMouseMoveEventData mouseData(PNPoint3f(-me->moveDelta.d_x, -me->moveDelta.d_y, 0.0));
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
  std::string playerid = "";

  if (PNGameInterface::getInstance()->getGameMap()->getPlayer() != NULL)
	playerid = PNGameInterface::getInstance()->getGameMap()->getPlayer()->getId();

  CEGUI::KeyEventArgs* me = (CEGUI::KeyEventArgs*)&e;

  PN3DCamera*	cam = PN3DCamera::getRenderCam();
  PN3DObject*	obj = NULL;
  if (PNGameInterface::getInstance()->getGameMap()->getEntityList().size() > 0)
	obj = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin()->second;

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
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveForward",playerid,"null", 1.0));
	//cam->addMovingState(PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::S : //key "s" move backward
	std::cout << "backward";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveBackward",playerid,"null", 1.0));
	//cam->addMovingState(PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::A :
  case CEGUI::Key::Q : //key "q" step left
	std::cout << "left";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveLeft",playerid,"null", 1.0));
	//cam->addMovingState(PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::D : //key "d" step right
	std::cout << "right";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveRight",playerid,"null", 1.0));
	//cam->addMovingState(PN3DObject::STATE_T_RIGHT);
	break;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////player move/////////////////////
  case CEGUI::Key::Numpad8 : //key "z" move forward
	std::cout << "forward\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveForward",playerid,"null", 1.0));
	//cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::Numpad5 : //key "s" move backward
	std::cout << "backward\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveBackward",playerid,"null", 1.0));
	//cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::Numpad4 : //key "q" step left
	std::cout << "left\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("RotateLeft",playerid,"null", 1.0));
	//cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::Numpad6 : //key "d" step right
	std::cout << "right\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("RotateRight",playerid,"null", 1.0));
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
  case CEGUI::Key::P :
	cam->addTargetMode(PN3DObject::TMODE_VIEW_ABS_LOCKED);
	cam->setTarget(obj);
	break;

  case CEGUI::Key::O :
	cam->addTargetMode(PN3DObject::TMODE_POSITION_LOCKED);
	cam->setTarget(obj);
	cam->setTargetPosition(0.0f, 0.0f, 0.0f);
	break;

  case CEGUI::Key::LeftControl :
  case CEGUI::Key::RightControl :
	std::cout << "Control";
	//cam->setTargetMode(PN3DObject::TMODE_VIEW_ABS_LOCKED);
	//cam->setTarget(obj);
    PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("Crouch",playerid,"null", 1.0));
	break;
  case CEGUI::Key::LeftShift :
  case CEGUI::Key::RightShift :
	std::cout << "shift";
	//cam->setTarget(NULL);
	//cam->setTargetMode(PN3DObject::TMODE_FREE);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("Run",playerid,"null", 1.0));
    break;
	//////////////////////////////////////////////////////////////////////////

  case CEGUI::Key::PageUp : //key "q" step left
	std::cout << "PageUp";
	break;

  case CEGUI::Key::PageDown : //key "d" step right
	std::cout << "PageDown";
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
  std::string playerid = "";

  if (PNGameInterface::getInstance()->getGameMap()->getPlayer() != 0)
	playerid = PNGameInterface::getInstance()->getGameMap()->getPlayer()->getId();
  CEGUI::KeyEventArgs* me = (CEGUI::KeyEventArgs*)&e;

  PN3DCamera*	cam = PN3DCamera::getRenderCam();
  PN3DObject*	obj = NULL;
  if (PNGameInterface::getInstance()->getGameMap()->getEntityList().size() > 0)
	obj = PNGameInterface::getInstance()->getGameMap()->getEntityList().begin()->second;

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
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveForward",playerid,"null", 0.0));
	//cam->subMovingState(PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::S : //key "s" move backward
	std::cout << "backward";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveBackward",playerid,"null", 0.0));
	//cam->subMovingState(PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::A :
  case CEGUI::Key::Q : //key "q" step left
	std::cout << "left";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveLeft",playerid,"null", 0.0));
	//cam->subMovingState(PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::D : //key "d" step right
	std::cout << "right";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveRight",playerid,"null", 0.0));
	//cam->subMovingState(PN3DObject::STATE_T_RIGHT);
	break;
    //////////////////////////////////////////////////////////////////////////
    // move player
  case CEGUI::Key::Numpad8 : //  move forward
	std::cout << "forward\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveForward",playerid,"null", 0.0));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::Numpad5 : // move backward
	std::cout << "backward\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("MoveBackward",playerid,"null", 0.0));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::Numpad6 : // step left
	std::cout << "left\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("RotateRight",playerid,"null", 0.0));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::Numpad4 : // step right
	std::cout << "right\n";
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("RotateLeft",playerid,"null", 0.0));
	//cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_RIGHT);
	break;

  case CEGUI::Key::Add :
	_miniMap->setAlpha(_miniMap->getAlpha()+0.1f);
	break;

  case CEGUI::Key::Subtract :
	_miniMap->setAlpha(_miniMap->getAlpha()-0.1f);
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
  case CEGUI::Key::P :
	cam->subTargetMode(PN3DObject::TMODE_VIEW_ABS_LOCKED);
	break;

  case CEGUI::Key::O :
	cam->subTargetMode(PN3DObject::TMODE_POSITION_LOCKED);
	break;

  case CEGUI::Key::LeftControl :
  case CEGUI::Key::RightControl :
	std::cout << "Control";
	//cam->setTarget(NULL);
	//cam->setTargetMode(PN3DObject::TMODE_FREE);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("Crouch",playerid,"null", 0.0));
    break;
  case CEGUI::Key::LeftShift :
  case CEGUI::Key::RightShift :
	std::cout << "shift";
	//cam->setTarget(NULL);
	//cam->setTargetMode(PN3DObject::TMODE_FREE);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL, &PNGameActionEventData("Run",playerid,"null", 0.0));
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
//resetGUI();
//PNGUIDeath::getInstance()->show();


  CEGUI::MouseEventArgs* me = (CEGUI::MouseEventArgs*)&e;

  if (me->button == CEGUI::LeftButton){
	std::cout << "game left click" << std::endl;
    //PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("PrimaryAttack",playerid,"null", 1.0));

  }
  if (me->button == CEGUI::RightButton)
	std::cout << "game right click" << std::endl;
  if (me->button == CEGUI::MiddleButton)
	std::cout << "game middle click" << std::endl;
  return true;
}

/*!
\brief
Called when there is a mouse click
*/
bool PNGUIGame::eventMouseButtonPressedHandler(const CEGUI::EventArgs& e)
{ 
  CEGUI::MouseEventArgs* me = (CEGUI::MouseEventArgs*)&e;
  std::string playerid = "";

  if (PNGameInterface::getInstance()->getGameMap()->getPlayer() != NULL)
    playerid = PNGameInterface::getInstance()->getGameMap()->getPlayer()->getId();

  if (me->button == CEGUI::LeftButton){
    std::cout << "game left click" << std::endl;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("PrimaryAttack",playerid,"null", 1.0));

  }
  if (me->button == CEGUI::RightButton){
    std::cout << "game right click" << std::endl;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("Defense",playerid,"null", 1.0));
  }
  if (me->button == CEGUI::MiddleButton){
    std::cout << "game middle click" << std::endl;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("Use",playerid,"null", 1.0));
  }
  return true;
}

/*!
\brief
Called when there is a mouse click
*/
bool PNGUIGame::eventMouseButtonReleasedHandler(const CEGUI::EventArgs& e)
{ 
  CEGUI::MouseEventArgs* me = (CEGUI::MouseEventArgs*)&e;

  std::string playerid = "";

  if (PNGameInterface::getInstance()->getGameMap()->getPlayer() != NULL)
    playerid = PNGameInterface::getInstance()->getGameMap()->getPlayer()->getId();

  if (me->button == CEGUI::LeftButton){
    std::cout << "game left click" << std::endl;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("PrimaryAttack",playerid,"null", 0.0));
  }
  if (me->button == CEGUI::RightButton){
    std::cout << "game right click" << std::endl;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("Defense",playerid,"null", 0.0));
  }
  if (me->button == CEGUI::MiddleButton){
    std::cout << "game middle click" << std::endl;
    PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_ACTION, NULL,  &PNGameActionEventData("Use",playerid,"null", 0.0));
  }
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
