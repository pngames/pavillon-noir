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

#ifndef _PNSOUNDMANAGER_HPP_
#define _PNSOUNDMANAGER_HPP_

#include <map>
#include <AL/al.h>
#include <AL/alut.h>
#include "pndefs.h"
#include "PNConsole.hpp"
#include "PNSoundInterface.hpp"
#include "PNSound.hpp"
#include "PNSoundEventData.hpp"


using namespace PN;

class PNSoundManager : PNSoundInterface
{
private:
  pnint			_maxId;
  PNSoundManager() {};
  ~PNSoundManager();
public:

  static PNSoundManager*	getInstance();
  void					init();
  void					setListenerPosition(float x, float y, float z);
  void					setListenerOrientation(float fx, float fy, float fz, float ux, float uy, float uz);
  void					setDopplerEffect(ALfloat velocity, ALfloat factor);

  //////////////////////////////////////////////////////////////////////////
  bool					loadSound(const std::string &name, const pnchar *fname, char looping);
  void					setProperties(const std::string &name, pnfloat x, pnfloat y, pnfloat z, pnfloat vx, pnfloat vy, pnfloat vz);
  void					playSound(const std::string &name);
  void					stopSound(const std::string &name);
  void					pauseSound(const std::string &name);
  void					changeSoundVolume(const std::string &name, float value);
  void					destroySound(const std::string &name);
  void					clearSoundMap();
  void			 		disableSound();
  void  				enableSound();

  //////////////////////////////////////////////////////////////////////////
  /// Events
  void					registerCallbacks();
  void					onPlaySound(pnEventType evt, PNObject* source, PNEventData* data);
  void					onCreateSound(pnEventType evt, PNObject* source, PNEventData* data);
  void					onVolumeSound(pnEventType evt, PNObject* source, PNEventData* data);
  void					onStopSound(pnEventType evt, PNObject* source, PNEventData* data);
  void					onPauseSound(pnEventType evt, PNObject* source, PNEventData* data);
  //////////////////////////////////////////////////////////////////////////

  std::map<std::string , PNSound *> soundMap;
  pnint			getMaxId();
  void			setMaxid(pnint id);
  pnint			createNewSound(const std::string &name, const char* file, char looping, pnfloat x, pnfloat y, pnfloat z);
  void			showLoadedSounds();
};

#endif
