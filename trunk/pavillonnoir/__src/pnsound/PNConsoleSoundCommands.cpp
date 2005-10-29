/*
 * PNConsoleSoundCommands.cpp
 * 
 * Description :
 * PNSound and PNSoundManager declarations
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

#include "PNSoundManager.hpp"

//////////////////////////////////////////////////////////////////////////

void  PNSoundManager::_commandNewSound(const std::string&, std::istream& i)
{
  PNSoundEventData *data;
  std::string name;
  std::string file;
  std::string loop;
  std::string tmp;

  char		loop_flag;
  float		x = 0.0;
  float		y = 0.0;
  float		z = 0.0;
  float		volume = 1.0f;

  i >> name;
  i >> file;
  i >> loop;
  i >> x;
  i >> y;
  i >> z;
  i >> volume;

  

  //PNConsole::writeLine("Command => newsound : name = %s | file = %s | loop = %s | X = %f | Y = %f | Z = %f\n", name.c_str(), file.c_str(), loop.c_str(), x, y, z);

  if (loop == "TRUE")
	loop_flag = true;
  else
	loop_flag = 0;

  if (name == "" || file == "" || loop == "")
	PNConsole::writeLine("Error : wrong arguments to function newsound");
  else
  {
	data = new PNSoundEventData(name, DEF::soundsFilePath + file.c_str(), loop_flag, x, y, z, volume);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_CREATE, 0, data);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_PLAY, 0, data);
	
	//PNSoundInterface *si = PNSoundInterface::getInstance();
	//std::string soundPath =  DEF::musicFilePath + file.c_str();
	//if (si->createNewSound(name, soundPath.c_str(), loop_flag, x, y, z) != 0)
	  //si->playSound(name);
  }
}

void  PNSoundManager::_commandPlaySound(const std::string&, std::istream& i)
{
  //PNSoundInterface *si = PNSoundInterface::getInstance();
  std::string name;
  PNSoundEventData *data;
  float volume = 1.0f;
	
  i >> name;
  i >> volume;
  if (name != "")
  {
	PNConsole::writeLine("Command => playsound : name = %s", name.c_str());
	data = new PNSoundEventData(name, volume);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_PLAY, 0, data);
	//si->playSound(name);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function playsound");
}

void  PNSoundManager::_commandStopSound(const std::string&, std::istream& i)
{
  //PNSoundInterface *si = PNSoundInterface::getInstance();
  std::string name;
  PNSoundEventData *data;

  i >> name;
  if (name != "")
  {
	PNConsole::writeLine("Command => stopsound : name = %s", name.c_str());
	data = new PNSoundEventData(name, 1.0f);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_STOP, 0, data);
	//si->stopSound(name);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function stopsound");
}

void  PNSoundManager::_commandPauseSound(const std::string&, std::istream& i)
{
  //PNSoundInterface *si = PNSoundInterface::getInstance();
  PNSoundEventData *data;
std::string name;

  i >> name;
  if (name != "")
  {
	PNConsole::writeLine("Command => Pausesound : name = %s", name.c_str());
	data = new PNSoundEventData(name, 1.0f);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_PAUSE, 0, data);
	//si->pauseSound(name);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function stopsound");
}

void  PNSoundManager::_commandEnableSound(const std::string&, std::istream& i)
{
  int	value;

  i >> value;
  if (value == 0)
  {
	PNConsole::writeLine("Sound disabled");
	PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_DISABLE, 0, 0);
  }
  else
  {
	  PNConsole::writeLine("Sound enabled");
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_ENABLE, 0, 0);
  }
}

void  PNSoundManager::_commandLoadedSounds(const std::string&, std::istream& i)
{
  PNSoundInterface *si = PNSoundInterface::getInstance();

  PNConsole::writeLine("Command => loadedsounds");
  si->showLoadedSounds();
}

void  PNSoundManager::_commandChangeSoundVolume(const std::string&, std::istream& i)
{
  //PNSoundInterface *si = PNSoundInterface::getInstance();
  PNSoundEventData *data;
  std::string name;
  float volume;

  i >> name;
  i >> volume;
  if (name != "" && volume <= 1.0)
  {
	PNConsole::writeLine("Command => changesoundvolume : name = %s, volume = %f", name.c_str(), volume);
	data = new PNSoundEventData(name, volume);
	PNEventManager::getInstance()->sendEvent(PN_EVENT_SOUND_VOLUME, 0, data);
	//si->changeSoundVolume(name, volume);
  }
  else
	PNConsole::writeLine("Error : wrong arguments to function stopsound");
}
