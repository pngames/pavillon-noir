/*
* PNSound.cpp
* 
* Description :
* PNSound and PNSoundManager definitions
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

#include "PNSound.hpp"
#include "PNSoundManager.hpp"

/*! Gets an instance of the sound manager */
PNSoundManager*  PNSoundManager::getInstance()
{
  if (_instance == NULL)
	return new PNSoundManager();

  return (PNSoundManager*)_instance;
}


/*! Disables sound management */
void			 		PNSoundManager::disableSound()
{
  return;
}


/*! Enables sound management */
void  					PNSoundManager::enableSound()
{
  return;
}


/*! Sound manager's init */
void PNSoundManager::init()
{
  printf("==--OpenAL init--==\n");
  alutInit(0, NULL);

  _maxId = 0;
  return;
}


/*! Classes destructor */
PNSoundManager::~PNSoundManager()
{
  alutExit();
}


/*! Sets the listener's position to x, y, z */
void PNSoundManager::setListenerPosition(float x, float y, float z)
{
  alListener3f(AL_POSITION, x,y,z);
}


/*! Sets the listener's orientation */
void PNSoundManager::setListenerOrientation(float fx, float fy, float fz, float ux, float uy, float uz)
{
  float vec[6];
  vec[0] = fx;
  vec[1] = fy;
  vec[2] = fz;
  vec[3] = ux;
  vec[4] = uy;
  vec[5] = uz;
  alListenerfv(AL_ORIENTATION, vec);
  return;
}


/*! Sets the doppler effect */
void PNSoundManager::setDopplerEffect(ALfloat velocity, ALfloat factor)
{
  alDopplerFactor(factor);
  alDopplerVelocity(velocity);
  return;
}


/*! Gets the bigest Id in the map */
pnint	PNSoundManager::getMaxId()
{
  return _maxId;
}


/*! Sets the bigest Id in the map */
void	PNSoundManager::setMaxid(pnint id)
{
  _maxId = id;
  return;
}


/*! Creates a new sound and puts it in the map, return the element's Id */
pnint	PNSoundManager::createNewSound(const std::string &name, const char* file, char looping, pnfloat x, pnfloat y, pnfloat z)
{
  pnint newId = getMaxId();
  setMaxid(++newId);

  PNSound* newSound = new PNSound(newId);

  if (newSound->loadSound(file, looping) != true)
  {
	PNConsole::writeLine("Error loading file : \"%s\", are you sure that this file exists ?", file);
	delete newSound;
	return (0);
  }
  PNConsole::writeLine("Sound \"%s\" created and loaded with name \"%s\" :)", file, name.c_str());
  newSound->setProperties(x, y, z, 0.0, 0.0, 0.0);
  newSound->current_file = file;
  soundMap[name] = newSound;
  return (newId);
}


/*! Loads a new sound */
bool			PNSoundManager::loadSound(const std::string &name, const pnchar *fname, char looping)
{
  if (soundMap.find(name) != soundMap.end())
  {
	if ((soundMap[name]->loadSound(fname, looping) != true))
	{
	  PNConsole::writeLine("Error loading file : \"%s\", are you sure that this file exists ?", fname);
	  return false;
	}
	soundMap[name]->current_file = fname;
	PNConsole::writeLine("Loaded file : %s", soundMap[name]->current_file.c_str());
	return true;
  }
  PNConsole::writeLine("Error loading file : %s", fname);
  return false;
}


/*! Sets the ptroprieties for sound \"name\" in the map */
void			PNSoundManager::setProperties(const std::string &name, pnfloat x, pnfloat y, pnfloat z, pnfloat vx, pnfloat vy, pnfloat vz)
{
  if (soundMap.find(name) != soundMap.end())
	soundMap[name]->setProperties(x, y, z, vx, vy, vz);
  return;
}


/*! Plays sound \"name\" */
void			PNSoundManager::playSound(const std::string &name)
{
  printf("*Playing sound \"%s\"\n", name.c_str());
  if (soundMap.find(name) != soundMap.end())
	soundMap[name]->playSound();
  return;
}


/*! Stops sound \"name\" */
void			PNSoundManager::stopSound(const std::string &name)
{
  printf("*Stopping sound \"%s\"\n", name.c_str());
  if (soundMap.find(name) != soundMap.end())
	soundMap[name]->stopSound();
  return;
}


/*! Pauses sound \"name\" */
void			PNSoundManager::pauseSound(const std::string &name)
{
  printf("*Paused sound \"%s\"\n", name.c_str());
  if (soundMap.find(name) != soundMap.end())
	soundMap[name]->pauseSound();
  return;
}


/*! Sets sound volume to value (between 0.1 and 1.0) for sound \"name\" */
void			PNSoundManager::changeSoundVolume(const std::string &name, float value)
{
  printf("*Change sound volume sound \"%s\" : value = %f\n", name.c_str(), value);
  if (soundMap.find(name) != soundMap.end())
	soundMap[name]->changeSoundVolume(value);
  return;
}


/*! Destroys sound \"name\" */
void			PNSoundManager::destroySound(const std::string &name)
{
  if (soundMap.find(name) != soundMap.end())
	soundMap[name]->destroySound();
  return;
}


/*! Shows actualy loaded sounds in the console */
void			PNSoundManager::showLoadedSounds()
{
  std::map<std::string , PNSound *>::iterator it;

  it = soundMap.begin();
  PNConsole::writeLine("Loaded sounds are :");
  for (it = soundMap.begin(); it != soundMap.end(); it++)
  {
	PNConsole::writeLine("+ Identifier \"%s\" for file \"%s\"", it->first.c_str(), it->second->current_file.c_str());
  }
  return;
}

