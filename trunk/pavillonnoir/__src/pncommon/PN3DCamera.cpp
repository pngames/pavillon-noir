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

#include <iostream>

#include "pndefs.h"
#include "pnmath.h"
#include "pnevent.h"

#include "PNGameMap.hpp"
#include "PNGameInterface.hpp"

#include "PN3DCamera.hpp"

namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////
PN3DCamera* PN3DCamera::_playerCamera = NULL;

PN3DCamera::PN3DCamera()
{
  _objType = OBJTYPE_CAMERA;

  _target = NULL;

  _viewFar = 20000.0f;
  _viewNear = 0.1f;
  _viewFov = 45.0f;
  _viewXRadFov = _viewYRadFov = (pnfloat)DEGREE_TO_RADIAN(_viewFov);

  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PN3DCamera::_onMPStarted));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PN3DCamera::_onMPEnded));
}

PN3DCamera::PN3DCamera(PN3DObject* object)
{
  _objType = OBJTYPE_CAMERA;
  _target = object;
}

PN3DCamera::~PN3DCamera()
{
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PN3DCamera::_onMPStarted));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PN3DCamera::_onMPEnded));
}

//////////////////////////////////////////////////////////////////////////

void
PN3DCamera::_onMPStarted(pnEventType type, PNObject* source, PNEventData* ed)
{
  PNEventManager::getInstance()->addCallback(PN_EVENT_RU_STARTING, EventCallback(this, &PN3DCamera::_updateFrustrum));
}

void
PN3DCamera::_onMPEnded(pnEventType type, PNObject* source, PNEventData* ed)
{
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_RU_STARTING, EventCallback(this, &PN3DCamera::_updateFrustrum));
}

pnbool
PN3DCamera::_is3DObjVisible(PN3DObject* obj)
{
  return true;

  PNLOCK(obj);

  PNVector3f	targetVector = obj->getCoord();
  targetVector -= _coord;

  PNVector3f	frontDirection = _orient * _frontDirection.getVector();

//  cout << "#####################################" << endl;

//  cout << "_viewY=" << RADIAN_TO_DEGREE(_viewYRadFov) << " || " << "_viewX=" << RADIAN_TO_DEGREE(_viewXRadFov) << endl;

//  cout << "frontDirection=" << frontDirection << endl;
//  cout << "targetVector=" << targetVector << endl;

  //////////////////////////////////////////////////////////////////////////
  // NEER-FAR

  

  //////////////////////////////////////////////////////////////////////////
  // FOV

  frontDirection.setNorm(1.0f);
  targetVector.setNorm(1.0f);

  pndouble	sp = frontDirection.scalarProduct(targetVector);

  cout << "sp=" << sp << endl;

  return sp > cosf(max(_viewYRadFov, _viewXRadFov)/2);

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  // TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 
  
  PNPoint coord = _coord - obj->getCoord();
  //coord = obj->getOrient().getInvert() * coord;

  //frontDirection = obj->getOrient().getInvert() * frontDirection;
  targetVector = PNPoint::ZERO - coord;

  cout << "frontDirection=" << frontDirection << endl;
  cout << "targetVector=" << targetVector << endl;

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  pnfloat	normy1 = sqrtf(SQNBR(frontDirection.x) + SQNBR(frontDirection.z));
  pnfloat	normy2 = sqrtf(SQNBR(targetVector.x) + SQNBR(targetVector.z));

  pndouble	py = ((frontDirection.x / normy1) * (targetVector.x / normy2)) + ((frontDirection.z / normy1) * (targetVector.z / normy2));

  // The test is for handle precision problems
  pndouble	yangle = ABS(py) >= 1.0 ? 0.0 : acos(py);

//  cout << "ps=" << py << " --> " << "yangle=" << RADIAN_TO_DEGREE(yangle) << endl;

  //////////////////////////////////////////////////////////////////////////

  pnfloat	normx1 = sqrtf(SQNBR(frontDirection.y) + SQNBR(frontDirection.z));
  pnfloat	normx2 = sqrtf(SQNBR(targetVector.y) + SQNBR(targetVector.z));

  pndouble	px = ((frontDirection.y / normx1) * (targetVector.y / normx2)) + ((frontDirection.z / normx1) * (targetVector.z / normx2));

  // The test is for handle precision problems
  pndouble	xangle = ABS(px) >= 1.0 ? 0.0 : acos(px);

//  cout << "px=" << px << " --> " << "yangle=" << RADIAN_TO_DEGREE(xangle) << endl;

  //////////////////////////////////////////////////////////////////////////

  return (ABS(yangle) < (_viewYRadFov / 2))/* && (ABS(xangle) < (_viewXRadFov / 2))*/;
}

void
PN3DCamera::_updateFrustrum(pnEventType type, PNObject* source, PNEventData* ed)
{
  PNLOCK(this);

  PNGameMap*	gmap = PNGameInterface::getInstance()->getGameMap();

  if (gmap == NULL)
	return ;

  const PNGameMap::ObjMap&	list = gmap->getEntityList();

  PN3DObjList::iterator		oldIt = _list3DObj.begin();

  for (PNGameMap::ObjMap::const_iterator it = list.begin(); it != list.end(); ++it)
  {
	if (oldIt == _list3DObj.end() || *oldIt != it->second)
	{
	  if (_is3DObjVisible(it->second))
	  {
		_list3DObj.insert(oldIt, it->second);
		PNEventManager::getInstance()->addEvent(PN_EVENT_F_IN, this, new PNFrustrumEventData(it->second));
	  }
	}
	else if (!_is3DObjVisible(it->second))
	{
	  PN3DObjList::iterator	itmp = oldIt++;
	  _list3DObj.erase(itmp);
	  PNEventManager::getInstance()->addEvent(PN_EVENT_F_OUT, this, new PNFrustrumEventData(it->second));
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
