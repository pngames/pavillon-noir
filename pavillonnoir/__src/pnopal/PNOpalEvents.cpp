/*
 * PNOpalEvents.cpp
 * 
 * Description :
 * PNOpalEvents definition
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
#include "pnevent.h"
#include "pnresources.h"

#include "PNEventManager.hpp"
#include "PNSoundInterface.hpp"
#include "PNConsole.hpp"

#include "PNOpalEvents.hpp"
#include "PNPoint.hpp"

#define SOUND_SENSITIVITY 1.0f

namespace PN {

void OPAL_CALL PNOpalCommonEventHandler::handleCollisionEvent(const opal::CollisionEvent& e)
{
  //static float depth = 0;
  //PNPoint collisionPoint;
  //collisionPoint.set(e.pos[0], e.pos[1], e.pos[2]);

  //pnerror(PN_LOGLVL_INFO, "%s", "COLLISION");
  
  //PNEventManager::getInstance()->addEvent(PN_EVENT_COLLISION, &collisionPoint, NULL);
  //if (e.depth > SOUND_SENSITIVITY)
	//PNSoundInterface::getInstance()->PlaySound("ding");
}

}

