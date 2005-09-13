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
#include "PN3DCamera.hpp"

#include "PNConsole.hpp"

#include "PN3DSkeletonObject.hpp"  // FIXME : just tests

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
  bool	b;

  i >> b;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->_list3DObj.begin();

  if (obj != NULL)
  {
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
  bool	b;

  i >> b;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->_list3DObj.begin();

  if (obj != NULL)
  {
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
  PN3DObject *obj = *PN3DCamera::getRenderCam()->_list3DObj.begin();

  if (obj != NULL)
  {
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
  bool	b;

  i >> b;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->_list3DObj.begin();

  if (obj != NULL)
  {
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
  double speed;

  i >> speed;

  PN3DObject *obj = *PN3DCamera::getRenderCam()->_list3DObj.begin();

  if (obj != NULL)
  {
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
	camera->setMovingSpeed(speed);

	PNConsole::writeLine("Render Camera speed changed : %f", speed);
  }
  else
	PNConsole::writeLine("Error: there's no render camera");
}

//////////////////////////////////////////////////////////////////////////

void  PNGUIGame::_commandNewSound(const std::string&, std::istream& i)
{
  std::string name;
  std::string file;
  std::string loop;
  std::string tmp;
  char		loop_flag;
  float		x = 0.0;
  float		y = 0.0;
  float		z = 0.0;

  i >> name;
  i >> file;
  i >> loop;
  i >> x;
  i >> y;
  i >> z;

  //PNConsole::writeLine("Command => newsound : name = %s | file = %s | loop = %s | X = %f | Y = %f | Z = %f\n", name.c_str(), file.c_str(), loop.c_str(), x, y, z);

  if (loop == "TRUE")
	loop_flag = true;
  else
	loop_flag = 0;

  if (name == "" || file == "" || loop == "")
	PNConsole::writeLine("Error : wrong arguments to function newsound");
  else
  {
	PNSoundInterface *si = PNSoundInterface::getInstance();
	pnint toto = si->getMaxId();
	toto;
	std::string soundPath =  DEF::musicFilePath + file.c_str();

	if (si->createNewSound(name, soundPath.c_str(), loop_flag, x, y, z) != 0)
	  si->playSound(name);
  }
}

void  PNGUIGame::_commandPlaySound(const std::string&, std::istream& i)
{
  PNSoundInterface *si = PNSoundInterface::getInstance();
  std::string name;

  i >> name;
  if (name != "")
  {
	PNConsole::writeLine("Command => playsound : name = %s", name.c_str());
	si->playSound(name);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function playsound");
}

void  PNGUIGame::_commandStopSound(const std::string&, std::istream& i)
{
  PNSoundInterface *si = PNSoundInterface::getInstance();
  std::string name;

  i >> name;
  if (name != "")
  {
	PNConsole::writeLine("Command => stopsound : name = %s", name.c_str());
	si->stopSound(name);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function stopsound");
}

void  PNGUIGame::_commandPauseSound(const std::string&, std::istream& i)
{
  PNSoundInterface *si = PNSoundInterface::getInstance();
  std::string name;

  i >> name;
  if (name != "")
  {
	PNConsole::writeLine("Command => Pausesound : name = %s", name.c_str());
	si->pauseSound(name);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function stopsound");
}


void  PNGUIGame::_commandLoadedSounds(const std::string&, std::istream& i)
{
  PNSoundInterface *si = PNSoundInterface::getInstance();

  PNConsole::writeLine("Command => loadedsounds");
  si->showLoadedSounds();
}

void  PNGUIGame::_commandChangeSoundVolume(const std::string&, std::istream& i)
{
  PNSoundInterface *si = PNSoundInterface::getInstance();
  std::string name;
  float value;

  i >> name;
  i >> value;
  if (name != "" && value <= 1.0)
  {
	PNConsole::writeLine("Command => changesoundvolume : name = %s, value = %f", name.c_str(), value);
	si->changeSoundVolume(name, value);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function stopsound");
}

void  PNGUIGame::_commandShowWP(const std::string&, std::istream& i)
{
  PN3DObjList::iterator it;
  
  for (it = PN3DCamera::getRenderCam()->_list3DObj.begin(); it != PN3DCamera::getRenderCam()->_list3DObj.end(); it++)
  {
	PN3DObject*	obj = (PN3DObject*)*it;

	if (obj != NULL && obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	{
	  obj->setRenderMode(PN3DObject::RENDER_MODEL);
	}
  }
}

void  PNGUIGame::_commandHideWP(const std::string&, std::istream& i)
{
  PN3DObjList::iterator it;

  for (it = PN3DCamera::getRenderCam()->_list3DObj.begin(); it != PN3DCamera::getRenderCam()->_list3DObj.end(); it++)
  {
	PN3DObject*	obj = (PN3DObject*)*it;

	if (obj != NULL && obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	{
	  obj->setRenderMode(NULL);
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
  pnuint  nb;
  pnfloat x;
  pnfloat y;
  pnfloat z;
  pnfloat duration;

  i >> nb;
  i >> x;
  i >> y;
  i >> z;
  i >> duration;

  PNPhysicsInterface::getInstance()->addForceToObj(nb, x, y, z, duration);
}

//////////////////////////////////////////////////////////////////////////

PNGUIGame::PNGUIGame()
{
 
  //_rootWin = CEGUI::System::getSingleton().getGUISheet();
  CEGUI::Window* rootSheet = CEGUI::System::getSingleton().getGUISheet();
  _rootWin = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNGUIGame.layout");
  rootSheet->addChildWindow(_rootWin);
//_rootWin->setEnabled(true);
//_rootWin->setVisible(true);
_rootWin->activate();

  _progBarVal = 1;

_myri = PNRendererInterface::getInstance();
  _skipFirstFrame = false;
  _inputHandleModifier = 0;

  //register main events for the game to the root window 
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseMove, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseMoveHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNGUIGame::eventKeyPressedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventKeyUp, CEGUI::Event::Subscriber(&PNGUIGame::eventKeyReleasedHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseClickdHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseClickdHandler, this));
  _rootWin->subscribeEvent(CEGUI::Window::EventMouseWheel, CEGUI::Event::Subscriber(&PNGUIGame::eventMouseWheel, this));

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
  
  PNConsole::addFonction("newsound", &PNGUIGame::_commandNewSound, "Loads a new sound in the sound map, parameters : string SoundName | string SoundFile | bool loop [TRUE | FALSE] | float XPosition | pnfloat YPosition | pnfloat ZPosition");
  PNConsole::addFonction("playsound", &PNGUIGame::_commandPlaySound, "Plays an already loaded sound, parameter : string SoundName (Sound identifier given by command \"loadedsounds)\"");
  PNConsole::addFonction("stopsound", &PNGUIGame::_commandStopSound, "Stops an already loaded sound, parameter : string SoundName (Sound identifier given by command \"loadedsounds)\"");
  PNConsole::addFonction("pausesound", &PNGUIGame::_commandPauseSound, "Pauses an already loaded sound, parameter : string SoundName (Sound identifier given by command \"loadedsounds)\"");
  PNConsole::addFonction("loadedsounds", &PNGUIGame::_commandLoadedSounds, "Shows already loaded sounds, no params");
  PNConsole::addFonction("changesoundvolume", &PNGUIGame::_commandChangeSoundVolume, "changes a specific sound volume, parameter : string SoundName, float value (between 0.0 and 1.0)");
  //////////////////////////////////////////////////////////////////////////
  
  PNConsole::addFonction("physics", &PNGUIGame::_setPhysics, "Physical simulation, 0=false or 1=true");
  PNConsole::addFonction("addforce", &PNGUIGame::_addForce, "Add force to a physical object, addforce object_number x y z duration");
  PNConsole::addFonction("setdyn", &PNGUIGame::_setAlldynamic, "Set all physical objects dynamic, 0=false or 1=true");

  //////////////////////////////////////////////////////////////////////////
  
  PNConsole::addFonction("showwp", &PNGUIGame::_commandShowWP, "Show WayPoints");
  PNConsole::addFonction("hidewp", &PNGUIGame::_commandHideWP, "Hide WayPoints");
  PNConsole::addFonction("moveto", &PNGUIGame::_commandMoveTo, "Move selected character to given position");

 // PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE_HIDE, EventCallback(this, &PNGUIGame::inputHandleModifierState));
 // PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE_SHOW, EventCallback(this, &PNGUIGame::inputHandleModifierState));
PNEventManager::getInstance()->addCallback(PN_EVENT_CONSOLE, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_GRAB_OFF, EventCallback(this, &PNGUIGame::inputHandleModifierState));
  PNEventManager::getInstance()->addCallback(PN_EVENT_SDL_GRAB_ON, EventCallback(this, &PNGUIGame::inputHandleModifierState));
}

PNGUIGame::~PNGUIGame()
{
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

  //////////////////////////////////////////////////////////////////////////
  cam->rotatePitchRadians((pnfloat)DEGREE_TO_RADIAN(-me->moveDelta.d_y));
  cam->rotateYawRadians((pnfloat)DEGREE_TO_RADIAN(-me->moveDelta.d_x));

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

  PN3DCamera* cam = PN3DCamera::getRenderCam();

  PN3DObject*	obj = *cam->_list3DObj.begin();

  PNVector3f axis(1.0f, 0.0f, 0.0f);
  pnfloat phi;
  static PNMatrixTR4f  mat;
  PNQuatf rot;

//  std::cout << obj->getFile().string().c_str() << std::endl;

  switch(me->scancode)
  {
	//////////////////////////////////////////////////////////////////////////
	// TRANSLATION
  case CEGUI::Key::R : //key "r" move top
	std::cout << "top";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_TOP);
	break;

  case CEGUI::Key::F : //key "f" move top
	std::cout << "back";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_BACK);
	break;

  case CEGUI::Key::Z : //key "z" move forward
  case CEGUI::Key::W :
	std::cout << "forward";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::S : //key "s" move backward
	std::cout << "backward";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::A :
  case CEGUI::Key::Q : //key "q" step left
	std::cout << "left";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::D : //key "d" step right
	std::cout << "right";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_T_RIGHT);
	break;

	//////////////////////////////////////////////////////////////////////////
	// ROTATION
  case CEGUI::Key::ArrowLeft :
	std::cout << "ArrowLeft";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_R_LEFT);
	break;
  case CEGUI::Key::ArrowRight :
	std::cout << "ArrowRight";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_R_RIGHT);
	break;
  case CEGUI::Key::ArrowUp :
	std::cout << "ArrowUp";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_R_TOP);
	break;
  case CEGUI::Key::ArrowDown :
	std::cout << "ArrowDown";
	cam->setMovingState(cam->getMovingState() | PN3DObject::STATE_R_BACK);
	break;

	//////////////////////////////////////////////////////////////////////////
	// LOCK
  case CEGUI::Key::LeftControl :
  case CEGUI::Key::RightControl :
	std::cout << "Control";
	cam->setTarget(obj);
	cam->setMovingMode(PN3DObject::MMODE_VIEW_ABS_LOCKED);
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
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_TOP);
	break;

  case CEGUI::Key::F : //key "f" move top
	std::cout << "back";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_BACK);
	break;

  case CEGUI::Key::Z : //key "z" move forward
  case CEGUI::Key::W :
	std::cout << "forward";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_FORWARD);
	break;

  case CEGUI::Key::S : //key "s" move backward
	std::cout << "backward";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_BACKWARD);
	break;

  case CEGUI::Key::A :
  case CEGUI::Key::Q : //key "q" step left
	std::cout << "left";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_LEFT);
	break;

  case CEGUI::Key::D : //key "d" step right
	std::cout << "right";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_T_RIGHT);
	break;

	//////////////////////////////////////////////////////////////////////////
	// ROTATION
  case CEGUI::Key::ArrowLeft :
	std::cout << "ArrowLeft";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_R_LEFT);
	break;
  case CEGUI::Key::ArrowRight :
	std::cout << "ArrowRight";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_R_RIGHT);
	break;
  case CEGUI::Key::ArrowUp :
	std::cout << "ArrowUp";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_R_TOP);
	break;
  case CEGUI::Key::ArrowDown :
	std::cout << "ArrowDown";
	cam->setMovingState(cam->getMovingState() ^ PN3DObject::STATE_R_BACK);
	break;

	//////////////////////////////////////////////////////////////////////////
	// LOCK
  case CEGUI::Key::LeftControl :
  case CEGUI::Key::RightControl :
	std::cout << "Control";
	cam->setTarget(NULL);
	cam->setMovingMode(PN3DObject::MMODE_FREE);
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

//////////////////////////////////////////////////////////////////////////
};
