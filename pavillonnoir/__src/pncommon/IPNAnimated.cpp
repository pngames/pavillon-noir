/*
 * IPNAnimated.cpp
 * 
 * Description :
 * Interface for Animation support (play, pause, ...)
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
 
#include "pndefs.h"
#include "pnrender.h"
#include "pnevent.h"

#include "IPNAnimated.hpp"
#include "PNObject.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

IPNAnimated::IPNAnimated()
{
  _pmutex = NULL;

  _animId = -1;
  _running = false;
  _paused = false;
  _looping = false;

  _animTransTime = 0;
  _animSpeed = 1.0f;

  _startedEventType = -1;
  _stopedEventType = -1;
}

IPNAnimated::~IPNAnimated()
{
}

pnuint
IPNAnimated::startAnimation(pnint animation, pnuint transTime)
{
  PNLOCKP(this);

  _animId = animation;
  
  return startAnimation(transTime);
}

pnuint
IPNAnimated::startAnimation(pnint animation)
{
  PNLOCKP(this);

  _animId = animation;

  return startAnimation(0);
}

pnuint
IPNAnimated::startAnimation(pnuint transTime)
{
  PNLOCKP(this);

  _animTransTime = transTime;

  return startAnimation();
}

pnuint
IPNAnimated::startAnimation()
{
  PNLOCKP(this);

  _running = true;
  _paused = false;
  
  _animTimeCurrent = 0;

  printf("IPNAnimated::startAnimation()\n");
  
  if (_startedEventType > -1)
    PNEventManager::getInstance()->addEvent((pnEventType)_startedEventType, (PNObject* )this, NULL);
  
  return PNEC_SUCCESS;
}

void
IPNAnimated::stopAnimation()
{
  PNLOCKP(this);

  _running = false;

  if (_stopedEventType > -1)
    PNEventManager::getInstance()->addEvent((pnEventType)_stopedEventType, (PNObject* )this, NULL);
}

void
IPNAnimated::pause()
{
  PNLOCKP(this);

  if (_paused)
  {
	_paused = false;

    if (_pausedEventType > -1)
	  PNEventManager::getInstance()->addEvent((pnEventType)_pausedEventType, (PNObject* )this, NULL);
  }
  else
	_paused = true;
}

void
IPNAnimated::setAnimSpeed(pndouble speed)
{
  PNLOCKP(this);

  _animSpeed = speed;
}

void
IPNAnimated::setEnableLoop(pnbool enabled)
{
  PNLOCKP(this);

  _looping = enabled;
}

//////////////////////////////////////////////////////////////////////////
};
