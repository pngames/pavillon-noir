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
#include "PN3DCameraModel.hpp"

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

  _renderMode = RENDER_MODEL;

  _model = PN3DCameraModel::getInstance();

  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PN3DCamera::_onMPStarted));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PN3DCamera::_onMPEnded));
}

PN3DCamera::PN3DCamera(PN3DObject* object)
{
  _objType = OBJTYPE_CAMERA;
  _positionTarget = _viewTarget = object;

  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PN3DCamera::_onMPStarted));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PN3DCamera::_onMPEnded));
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
  PNLOCK(obj);

  //////////////////////////////////////////////////////////////////////////

  if (obj->get3DModel() == NULL || obj->getRenderMode() == 0)
	return false;

  //////////////////////////////////////////////////////////////////////////

  _viewMaxCosFov = cosf(max(_viewYRadFov, _viewXRadFov)/2);

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

  //////////////////////////////////////////////////////////////////////////

  pnfloat norm1 = targetVector1.getNorm();
  pnfloat norm2 = targetVector2.getNorm();
  pnfloat norm3 = targetVector3.getNorm();
  pnfloat norm4 = targetVector4.getNorm();
  pnfloat norm5 = targetVector5.getNorm();
  pnfloat norm6 = targetVector6.getNorm();
  pnfloat norm7 = targetVector7.getNorm();
  pnfloat norm8 = targetVector8.getNorm();

  pnbool	inNearFar = true;
  pnbool	inFov = true;

  //////////////////////////////////////////////////////////////////////////
  // FOV

  targetVector1 /= norm1;
  pndouble	sp1 = frontDirection.scalarProduct(targetVector1);
  targetVector2 /= norm2;
  pndouble	sp2 = frontDirection.scalarProduct(targetVector2);
  targetVector3 /= norm3;
  pndouble	sp3 = frontDirection.scalarProduct(targetVector3);
  targetVector4 /= norm4;
  pndouble	sp4 = frontDirection.scalarProduct(targetVector4);
  targetVector5 /= norm5;
  pndouble	sp5 = frontDirection.scalarProduct(targetVector5);
  targetVector6 /= norm6;
  pndouble	sp6 = frontDirection.scalarProduct(targetVector6);
  targetVector7 /= norm7;
  pndouble	sp7 = frontDirection.scalarProduct(targetVector7);
  targetVector8 /= norm8;
  pndouble	sp8 = frontDirection.scalarProduct(targetVector8);

  inFov = 
	sp1 > _viewMaxCosFov ||
	sp2 > _viewMaxCosFov ||
	sp3 > _viewMaxCosFov ||
	sp4 > _viewMaxCosFov ||
	sp5 > _viewMaxCosFov ||
	sp6 > _viewMaxCosFov ||
	sp7 > _viewMaxCosFov ||
	sp8 > _viewMaxCosFov;

  //////////////////////////////////////////////////////////////////////////
  // NEER-FAR

  inNearFar = 
	(sp1 > 0.0 && norm1 >= _viewNear && norm1 <= _viewFar) ||
	(sp2 > 0.0 && norm2 >= _viewNear && norm2 <= _viewFar) ||
	(sp3 > 0.0 && norm3 >= _viewNear && norm3 <= _viewFar) ||
	(sp4 > 0.0 && norm4 >= _viewNear && norm4 <= _viewFar) ||
	(sp5 > 0.0 && norm5 >= _viewNear && norm5 <= _viewFar) ||
	(sp6 > 0.0 && norm6 >= _viewNear && norm6 <= _viewFar) ||
	(sp7 > 0.0 && norm7 >= _viewNear && norm7 <= _viewFar) ||
	(sp8 > 0.0 && norm8 >= _viewNear && norm8 <= _viewFar);

  //////////////////////////////////////////////////////////////////////////

  if (inNearFar && inFov)
	return true;

  //////////////////////////////////////////////////////////////////////////
  // BIGGER THAN NEER-FAR

  if (inNearFar == false)
  {
	pnbool bigger = sp1 > 0.0 && norm1 > _viewFar;

	bigger = 
	  (sp2 > 0.0 && norm2 > _viewFar != bigger) ||
	  (sp3 > 0.0 && norm3 > _viewFar != bigger) ||
	  (sp4 > 0.0 && norm4 > _viewFar != bigger) ||
	  (sp5 > 0.0 && norm5 > _viewFar != bigger) ||
	  (sp6 > 0.0 && norm6 > _viewFar != bigger) ||
	  (sp7 > 0.0 && norm7 > _viewFar != bigger) ||
	  (sp8 > 0.0 && norm8 > _viewFar != bigger);

	if (bigger)
	{
	  if (inFov)
		return true;
	  else
		inNearFar = true;
	}
	else
	  return false;
  }

  //////////////////////////////////////////////////////////////////////////
  // BIGGER THAN FOV

  pndouble	spr1 = rightDirection.scalarProduct(targetVector1);
  pndouble	spr2 = rightDirection.scalarProduct(targetVector2);
  pndouble	spr3 = rightDirection.scalarProduct(targetVector3);
  pndouble	spr4 = rightDirection.scalarProduct(targetVector4);
  pndouble	spr5 = rightDirection.scalarProduct(targetVector5);
  pndouble	spr6 = rightDirection.scalarProduct(targetVector6);
  pndouble	spr7 = rightDirection.scalarProduct(targetVector7);
  pndouble	spr8 = rightDirection.scalarProduct(targetVector8);

  pnbool	rightFov = spr1 >= 0.0;

  rightFov = 
	(spr2 >= 0.0 != rightFov) ||
	(spr3 >= 0.0 != rightFov) ||
	(spr4 >= 0.0 != rightFov) ||
	(spr5 >= 0.0 != rightFov) ||
	(spr6 >= 0.0 != rightFov) ||
	(spr7 >= 0.0 != rightFov) ||
	(spr8 >= 0.0 != rightFov);

  pndouble	spt1 = topDirection.scalarProduct(targetVector1);
  pndouble	spt2 = topDirection.scalarProduct(targetVector2);
  pndouble	spt3 = topDirection.scalarProduct(targetVector3);
  pndouble	spt4 = topDirection.scalarProduct(targetVector4);
  pndouble	spt5 = topDirection.scalarProduct(targetVector5);
  pndouble	spt6 = topDirection.scalarProduct(targetVector6);
  pndouble	spt7 = topDirection.scalarProduct(targetVector7);
  pndouble	spt8 = topDirection.scalarProduct(targetVector8);

  pnbool	topFov = spt1 >= 0.0;

  topFov = 
	(spt2 >= 0.0 != topFov) ||
	(spt3 >= 0.0 != topFov) ||
	(spt4 >= 0.0 != topFov) ||
	(spt5 >= 0.0 != topFov) ||
	(spt6 >= 0.0 != topFov) ||
	(spt7 >= 0.0 != topFov) ||
	(spt8 >= 0.0 != topFov);

  inFov = rightFov && topFov;

  return (inFov && inNearFar);
}

pnbool
#define SUB_FOV_TEST(targetV, vFov1, vFov2)  \
  ((inTest1 = vFov1.scalarProduct(targetV) < 0) || inTest1 != firstInTest1)\
  &&\
  ((inTest2 = vFov2.scalarProduct(targetV) < 0) || inTest2 != firstInTest2)

PN3DCamera::_is3DObjVisible2(PN3DObject* obj)
{
  PNLOCK(obj);

  //////////////////////////////////////////////////////////////////////////

  if (obj->get3DModel() == NULL || obj->getRenderMode() == 0)
	return false;

  //////////////////////////////////////////////////////////////////////////

  _viewMaxCosFov = cosf(max(_viewYRadFov, _viewXRadFov)/2);

  pnfloat		viewLeftFov = _viewYRadFov / 2 + (pnfloat)DEGREE_TO_RADIAN(90.0);
  pnfloat		viewRightFov = -viewLeftFov;
  pnfloat		viewTopFov = _viewXRadFov / 2 + (pnfloat)DEGREE_TO_RADIAN(90.0);
  pnfloat		viewBackFov = -viewTopFov;

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

  //////////////////////////////////////////////////////////////////////////

  pnfloat	  norm1 = targetVector1.getNorm();
  pnfloat	  norm2 = targetVector2.getNorm();
  pnfloat	  norm3 = targetVector3.getNorm();
  pnfloat	  norm4 = targetVector4.getNorm();
  pnfloat	  norm5 = targetVector5.getNorm();
  pnfloat	  norm6 = targetVector6.getNorm();
  pnfloat	  norm7 = targetVector7.getNorm();
  pnfloat	  norm8 = targetVector8.getNorm();

  pnbool	  inNearFar = true;
  pnbool	  inFov = true;

  //////////////////////////////////////////////////////////////////////////
  // FOV
  //////////////////////////////////////////////////////////////////////////

  PNVector3f  rightFov(PNQuatf(topDirection, viewRightFov) * frontDirection);
  PNVector3f  leftFov(PNQuatf(topDirection, viewLeftFov) * frontDirection);
  PNVector3f  topFov(PNQuatf(rightDirection, viewTopFov) * frontDirection);
  PNVector3f  backFov(PNQuatf(rightDirection, viewBackFov) * frontDirection);

  //////////////////////////////////////////////////////////////////////////

  targetVector1 /= norm1;
  targetVector2 /= norm2;
  targetVector3 /= norm3;
  targetVector4 /= norm4;
  targetVector5 /= norm5;
  targetVector6 /= norm6;
  targetVector7 /= norm7;
  targetVector8 /= norm8;

  pnbool  inTest1, inTest2, firstInTest1, firstInTest2;

  //////////////////////////////////////////////////////////////////////////

  firstInTest1 = rightFov.scalarProduct(targetVector1) < 0;
  firstInTest2 = leftFov.scalarProduct(targetVector1) < 0;

  pnbool inHFoV = 
	SUB_FOV_TEST(targetVector1, rightFov, leftFov) ||
	SUB_FOV_TEST(targetVector2, rightFov, leftFov) ||
	SUB_FOV_TEST(targetVector3, rightFov, leftFov) ||
	SUB_FOV_TEST(targetVector4, rightFov, leftFov) ||
	SUB_FOV_TEST(targetVector5, rightFov, leftFov) ||
	SUB_FOV_TEST(targetVector6, rightFov, leftFov) ||
	SUB_FOV_TEST(targetVector7, rightFov, leftFov) ||
	SUB_FOV_TEST(targetVector8, rightFov, leftFov);

  //////////////////////////////////////////////////////////////////////////

  firstInTest1 = topFov.scalarProduct(targetVector1) < 0;
  firstInTest2 = backFov.scalarProduct(targetVector1) < 0;

  pnbool inVFoV = 
	SUB_FOV_TEST(targetVector1, topFov, backFov) ||
	SUB_FOV_TEST(targetVector2, topFov, backFov) ||
	SUB_FOV_TEST(targetVector3, topFov, backFov) ||
	SUB_FOV_TEST(targetVector4, topFov, backFov) ||
	SUB_FOV_TEST(targetVector5, topFov, backFov) ||
	SUB_FOV_TEST(targetVector6, topFov, backFov) ||
	SUB_FOV_TEST(targetVector7, topFov, backFov) ||
	SUB_FOV_TEST(targetVector8, topFov, backFov);

  return inHFoV && inVFoV;

  //////////////////////////////////////////////////////////////////////////
  // NEAR-FAR
  //////////////////////////////////////////////////////////////////////////

  /*inNearFar = 
	(sp1 > 0.0 && norm1 >= _viewNear && norm1 <= _viewFar) ||
	(sp2 > 0.0 && norm2 >= _viewNear && norm2 <= _viewFar) ||
	(sp3 > 0.0 && norm3 >= _viewNear && norm3 <= _viewFar) ||
	(sp4 > 0.0 && norm4 >= _viewNear && norm4 <= _viewFar) ||
	(sp5 > 0.0 && norm5 >= _viewNear && norm5 <= _viewFar) ||
	(sp6 > 0.0 && norm6 >= _viewNear && norm6 <= _viewFar) ||
	(sp7 > 0.0 && norm7 >= _viewNear && norm7 <= _viewFar) ||
	(sp8 > 0.0 && norm8 >= _viewNear && norm8 <= _viewFar);

  //////////////////////////////////////////////////////////////////////////

  if (inNearFar && inFov)
	return true;

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  // BIGGER THAN NEER-FAR

  if (inNearFar == false)
  {
	pnbool bigger = sp1 > 0.0 && norm1 > _viewFar;

	bigger = 
	  (sp2 > 0.0 && norm2 > _viewFar != bigger) ||
	  (sp3 > 0.0 && norm3 > _viewFar != bigger) ||
	  (sp4 > 0.0 && norm4 > _viewFar != bigger) ||
	  (sp5 > 0.0 && norm5 > _viewFar != bigger) ||
	  (sp6 > 0.0 && norm6 > _viewFar != bigger) ||
	  (sp7 > 0.0 && norm7 > _viewFar != bigger) ||
	  (sp8 > 0.0 && norm8 > _viewFar != bigger);

	if (bigger)
	{
	  if (inFov)
		return true;
	  else
		inNearFar = true;
	}
	else
	  return false;
  }

  //////////////////////////////////////////////////////////////////////////
  // BIGGER THAN FOV

  pndouble	spr1 = rightDirection.scalarProduct(targetVector1);
  pndouble	spr2 = rightDirection.scalarProduct(targetVector2);
  pndouble	spr3 = rightDirection.scalarProduct(targetVector3);
  pndouble	spr4 = rightDirection.scalarProduct(targetVector4);
  pndouble	spr5 = rightDirection.scalarProduct(targetVector5);
  pndouble	spr6 = rightDirection.scalarProduct(targetVector6);
  pndouble	spr7 = rightDirection.scalarProduct(targetVector7);
  pndouble	spr8 = rightDirection.scalarProduct(targetVector8);

  pnbool	rightFov = spr1 >= 0.0;

  rightFov = 
	(spr2 >= 0.0 != rightFov) ||
	(spr3 >= 0.0 != rightFov) ||
	(spr4 >= 0.0 != rightFov) ||
	(spr5 >= 0.0 != rightFov) ||
	(spr6 >= 0.0 != rightFov) ||
	(spr7 >= 0.0 != rightFov) ||
	(spr8 >= 0.0 != rightFov);

  pndouble	spt1 = topDirection.scalarProduct(targetVector1);
  pndouble	spt2 = topDirection.scalarProduct(targetVector2);
  pndouble	spt3 = topDirection.scalarProduct(targetVector3);
  pndouble	spt4 = topDirection.scalarProduct(targetVector4);
  pndouble	spt5 = topDirection.scalarProduct(targetVector5);
  pndouble	spt6 = topDirection.scalarProduct(targetVector6);
  pndouble	spt7 = topDirection.scalarProduct(targetVector7);
  pndouble	spt8 = topDirection.scalarProduct(targetVector8);

  pnbool	topFov = spt1 >= 0.0;

  topFov = 
	(spt2 >= 0.0 != topFov) ||
	(spt3 >= 0.0 != topFov) ||
	(spt4 >= 0.0 != topFov) ||
	(spt5 >= 0.0 != topFov) ||
	(spt6 >= 0.0 != topFov) ||
	(spt7 >= 0.0 != topFov) ||
	(spt8 >= 0.0 != topFov);

  inFov = rightFov && topFov;

  return (inFov && inNearFar);*/
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
	  if (_is3DObjVisible2(it->second))
	  {
		_list3DObj.insert(oldIt, it->second);
		PNEventManager::getInstance()->addEvent(PN_EVENT_F_IN, this, new PNFrustrumEventData(it->second));
	  }
	}
	else if (!_is3DObjVisible2(it->second))
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
