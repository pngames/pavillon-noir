/*
 * PNSoundInterface.hpp
 * 
 * Description :
 * PNSoundInterface declaration
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

#ifndef _PNSOUNDINTERFACE_HPP_
# define _PNSOUNDINTERFACE_HPP_

#include "pndefs.h"
#include "pnplugins.h"
#include "PNInterface.hpp"
#include "PNSoundEventData.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNAPI				PNSoundInterface : public PNInterface
{
protected:
  static PNSoundInterface*  _instance;
  PNSoundInterface() {_instance = this;}
public:
  static PNSoundInterface*  getInstance();

  //////////////////////////////////////////////////////////////////////////
public:
  plugintypes			getType() const {return PN_PLUGIN_SOUND;}

public:
  virtual void			setListenerPosition(pnfloat x, pnfloat y, pnfloat z)=0;
  virtual void			setListenerOrientation(pnfloat fx, pnfloat fy, pnfloat fz, pnfloat ux, pnfloat uy, pnfloat uz)=0;
  virtual void			setDopplerEffect(pnfloat velocity, pnfloat factor)=0;
  virtual void			setProperties(const std::string &name, pnfloat x, pnfloat y, pnfloat z, pnfloat vx, pnfloat vy, pnfloat vz)=0;

  virtual pnint			getMaxId()=0;
  virtual void			setMaxid(pnint id)=0;
  
  //////////////////////////////////////////////////////////////////////////

  virtual pnint			createNewSound(const std::string &name, const char* file, char looping, pnfloat x, pnfloat y, pnfloat z)=0;
  virtual bool			loadSound(const std::string &name, const pnchar *fname, char looping)=0;
  virtual void			playSound(const std::string &name)=0;
  virtual void			stopSound(const std::string &name)=0;
  virtual void			pauseSound(const std::string &name)=0;
  virtual void			changeSoundVolume(const std::string &name, float value)=0;
  virtual void			destroySound(const std::string &name)=0;

  virtual void			disableSound()=0;
  virtual void  		enableSound()=0;
  
  virtual void			showLoadedSounds()=0;
  virtual void			clearSoundMap()=0;

  /// Events
  virtual void			onPlaySound(pnEventType evt, PNObject* source, PNEventData* data)=0;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNSOUNDINTERFACE_HPP_*/
