/*
 * PN3DCamera.cpp
 * 
 * Description :
 * PN3DCamera definition
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
#include "pnmath.h"
#include "pnevent.h"

#include "PNGameMap.hpp"
#include "PNGameInterface.hpp"

#include "PN3DCamera.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////
PN3DCamera* PN3DCamera::_playerCamera = NULL;

PN3DCamera::PN3DCamera()
{
  _objType = OBJTYPE_CAMERA;

  PNEventManager::getInstance()->addCallback(PN_EVENT_RU_STARTING, EventCallback(this, &PN3DCamera::_updateFrustrum));
}

PN3DCamera::PN3DCamera(PN3DObject* object)
{
  _objType = OBJTYPE_CAMERA;
  _target = object;
}

PN3DCamera::~PN3DCamera()
{
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_RU_STARTING, EventCallback(this, &PN3DCamera::_updateFrustrum));
}

//////////////////////////////////////////////////////////////////////////

/// Replace with proper function
static bool
is3DObjVisible(PN3DObject* obj)
{
  // calc view
  return true;
}

void
PN3DCamera::_updateFrustrum(pnEventType type, PNObject* source, PNEventData* ed)
{
  PNGameMap*	gmap = PNGameInterface::getInstance()->getGameMap();

  if (gmap == NULL)
	return ;

  const PNGameMap::ObjMap&	list = gmap->getEntityList();

  //_list3DObj.clear();

  PN3DObjList::iterator	oldIt = _list3DObj.begin();

  for (PNGameMap::ObjMap::const_iterator it = list.begin(); it != list.end(); ++it)
  {
	if (*oldIt != it->second)
	{
	  if (is3DObjVisible(it->second))
	  {
		_list3DObj.insert(oldIt, it->second);
		PNEventManager::getInstance()->addEvent(PN_EVENT_F_IN, it->second, NULL);
	  }
	}
	else if (!is3DObjVisible(it->second))
	{
	  PN3DObjList::iterator	itmp = oldIt++;
	  _list3DObj.erase(itmp);
	  PNEventManager::getInstance()->addEvent(PN_EVENT_F_OUT, it->second, NULL);
	}
	else
	  ++oldIt;
  }
}

//////////////////////////////////////////////////////////////////////////

const PN3DObjList&
PN3DCamera::getListObj()
{
  return _list3DObj;
}

PN3DCamera*
PN3DCamera::getRenderCam()
{
  return _playerCamera;
}

//////////////////////////////////////////////////////////////////////////
}
