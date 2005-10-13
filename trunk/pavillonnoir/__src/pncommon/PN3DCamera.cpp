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
#include "PN3DModel.hpp"

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
  _positionTarget = _viewTarget = object;
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
  //return true;

  PNLOCK(obj);

  //////////////////////////////////////////////////////////////////////////

  if (obj->get3DModel() == NULL || obj->getRenderMode() == 0)
	return false;

  //////////////////////////////////////////////////////////////////////////

  pnfloat angle = (pnfloat)DEGREE_TO_RADIAN(30);
  _viewMaxCosFov = cosf(angle/*max(_viewYRadFov, _viewXRadFov)*//2);

  PNVector3f	frontDirection = _orient * _frontDirection.getVector();
  PNVector3f	rightDirection = _orient * _rightDirection.getVector();
  PNVector3f	topDirection = _orient * _topDirection.getVector();

  frontDirection.setNorm(1.0f);
  rightDirection.setNorm(1.0f);
  topDirection.setNorm(1.0f);

  //////////////////////////////////////////////////////////////////////////

  PNPoint coord = _coord - obj->getCoord();
  coord = obj->getOrient().getInvert() * coord;
  frontDirection = obj->getOrient().getInvert() * frontDirection;

  PNVector3f	targetVector = PNPoint::ZERO - coord;

  const PNPoint&  minCoords = obj->get3DModel()->getMin();
  const PNPoint&  maxCoords = obj->get3DModel()->getMax();

  PNVector3f	targetVector1(minCoords);
  targetVector1 += targetVector;
  PNVector3f	targetVector2(minCoords.x, minCoords.y, maxCoords.z);
  targetVector2 += targetVector;
  PNVector3f	targetVector3(minCoords.x, maxCoords.y, minCoords.z);
  targetVector3 += targetVector;
  PNVector3f	targetVector4(maxCoords.x, minCoords.y, minCoords.z);
  targetVector4 += targetVector;
  PNVector3f	targetVector5(maxCoords.x, maxCoords.y, minCoords.z);
  targetVector5 += targetVector;
  PNVector3f	targetVector6(maxCoords.x, minCoords.y, maxCoords.z);
  targetVector6 += targetVector;
  PNVector3f	targetVector7(minCoords.x, maxCoords.y, maxCoords.z);
  targetVector7 += targetVector;
  PNVector3f	targetVector8(maxCoords);
  targetVector8 += targetVector;

  cout << "#####################################" << endl;

  /*cout << "targetVector=" << targetVector << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector1 << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector2 << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector3 << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector4 << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector5 << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector6 << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector7 << " sp=" << sp1 << endl;
  cout << "targetVector1=" << targetVector8 << " sp=" << sp1 << endl;*/

//  cout << "_viewY=" << RADIAN_TO_DEGREE(_viewYRadFov) << " || " << "_viewX=" << RADIAN_TO_DEGREE(_viewXRadFov) << endl;

//  cout << "frontDirection=" << frontDirection << endl;
//  cout << "targetVector=" << targetVector << endl;

  //////////////////////////////////////////////////////////////////////////
  // NEER-FAR

  

  //////////////////////////////////////////////////////////////////////////
  // FOV

  targetVector1.setNorm(1.0f);
  pndouble	sp1 = frontDirection.scalarProduct(targetVector1);
  targetVector2.setNorm(1.0f);
  pndouble	sp2 = frontDirection.scalarProduct(targetVector2);
  targetVector3.setNorm(1.0f);
  pndouble	sp3 = frontDirection.scalarProduct(targetVector3);
  targetVector4.setNorm(1.0f);
  pndouble	sp4 = frontDirection.scalarProduct(targetVector4);
  targetVector5.setNorm(1.0f);
  pndouble	sp5 = frontDirection.scalarProduct(targetVector5);
  targetVector6.setNorm(1.0f);
  pndouble	sp6 = frontDirection.scalarProduct(targetVector6);
  targetVector7.setNorm(1.0f);
  pndouble	sp7 = frontDirection.scalarProduct(targetVector7);
  targetVector8.setNorm(1.0f);
  pndouble	sp8 = frontDirection.scalarProduct(targetVector8);

  targetVector.setNorm(1.0f);

  pndouble	spf = frontDirection.scalarProduct(targetVector);
  pndouble	spr = rightDirection.scalarProduct(targetVector);
  pndouble	spt = topDirection.scalarProduct(targetVector);

  cout << "spf=" << spf << " spr=" << spr << " spt=" << spt << endl;

  if (sp1 > _viewMaxCosFov)
	return true;
  if (sp2 > _viewMaxCosFov)
	return true;
  if (sp3 > _viewMaxCosFov)
	return true;
  if (sp4 > _viewMaxCosFov)
	return true;
  if (sp5 > _viewMaxCosFov)
	return true;
  if (sp6 > _viewMaxCosFov)
	return true;
  if (sp7 > _viewMaxCosFov)
	return true;
  if (sp8 > _viewMaxCosFov)
	return true;
  if (spf > _viewMaxCosFov)
	return true;

  //////////////////////////////////////////////////////////////////////////
  // BIGGER THAN NEER-FAR

  PNVector3f  sizeVector(minCoords, maxCoords);
  if (sizeVector.getNorm() >= _viewFar - _viewNear)
	return true;

  //////////////////////////////////////////////////////////////////////////
  // BIGGER THAN FOV

  return false;

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  // TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST TEST 
  
  coord = _coord - obj->getCoord();
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
