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

IPNAnimated::IPNAnimated()
{
}

IPNAnimated::~IPNAnimated()
{
}

pnuint
IPNAnimated::startAnimation(pnint animation, pnuint transTime)
{
  _animId = animation;
  _animTimeStart = PNRendererInterface::getInstance()->getTicks();

  _running = true;
  _paused = false;

  PNEventManager::getInstance()->addEvent(PN_EVENT_OA_STARTED, (PNObject* )this, NULL);

  return PNEC_SUCCES;
}

void
IPNAnimated::stopAnimation()
{
  _running = false;

  PNEventManager::getInstance()->addEvent(PN_EVENT_OA_ENDED, (PNObject* )this, NULL);
}

void
IPNAnimated::pause()
{
  if (_paused)
  {
	_paused = false;
	_animTimeStart += PNRendererInterface::getInstance()->getTicks() - _animTimePause;

	PNEventManager::getInstance()->addEvent(PN_EVENT_OA_PAUSED, (PNObject* )this, NULL);
  }
  else
  {
	_paused = true;
	_animTimePause = PNRendererInterface::getInstance()->getTicks();
  }
}

void
IPNAnimated::setAnimSpeed(pndouble speed)
{
  _animSpeed = speed;
}

void
IPNAnimated::setEnableLoop(pnbool enabled)
{
  _looping = enabled;
}

}
