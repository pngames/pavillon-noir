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
#include "pnrender.h"

#include "PNGameMap.hpp"
#include "PNGameInterface.hpp"
#include "PN3DModel.hpp"
#include "PN3DCameraModel.hpp"
#include "PNPlane.hpp"

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

  _viewFar = 50000.0f;
  _viewNear = 0.1f;

  setFov(45.0f);

  _renderMode = RENDER_MODEL;

  _model = PN3DCameraModel::getInstance();

  PNEventManager::getInstance()->addCallback(PN_EVENT_RSU_STARTING, EventCallback(this, &PN3DCamera::_updateFrustrum));
  PNEventManager::getInstance()->addCallback(PN_EVENT_RSU_ENDING, EventCallback(this, &PN3DCamera::_onRSUEnding));
}

PN3DCamera::~PN3DCamera()
{
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_RSU_STARTING, EventCallback(this, &PN3DCamera::_updateFrustrum));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_RSU_ENDING, EventCallback(this, &PN3DCamera::_onRSUEnding));
}

//////////////////////////////////////////////////////////////////////////

void
PN3DCamera::setFar(pnfloat far)
{
  PNLOCK(this);

  _viewFar = far;
}

void
PN3DCamera::setNear(pnfloat near)
{
  PNLOCK(this);

  _viewNear = near;
}

void
PN3DCamera::setFov(pnfloat deg)
{
  PNLOCK(this);

  _viewFov = 45.0f;
  setHFov(DEGREE_TO_RADIAN_F(deg));
  setVFov(DEGREE_TO_RADIAN_F(deg));
}

void
PN3DCamera::setHFov(pnfloat rad)
{
  PNLOCK(this);

  _viewHRadFov = rad;

  //////////////////////////////////////////////////////////////////////////
  
  _viewLeftFov = _viewHRadFov / 2 + (pnfloat)DEGREE_TO_RADIAN(90.0);
  _viewRightFov = -_viewLeftFov;
}

void
PN3DCamera::setVFov(pnfloat rad)
{
  PNLOCK(this);

  _viewVRadFov = rad;

  //////////////////////////////////////////////////////////////////////////
  
  _viewTopFov = _viewVRadFov / 2 + (pnfloat)DEGREE_TO_RADIAN(90.0);
  _viewBackFov = -_viewTopFov;
}

//////////////////////////////////////////////////////////////////////////

pnfloat
PN3DCamera::getFar() const
{
  return _viewFar;
}

pnfloat
PN3DCamera::getNear() const
{
  return _viewNear;
}

//////////////////////////////////////////////////////////////////////////

void
PN3DCamera::_onRSUEnding(pnEventType type, PNObject* source, PNEventData* ed)
{
  if (this != getRenderCam())
	render();
}

void
PN3DCamera::render()
{
  PNRendererInterface* pnri = PNRendererInterface::getInstance();

  pnfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f};

  //pnri->renderSphere(15.0f, 20, 20, color, _coord);
}

//////////////////////////////////////////////////////////////////////////

pnbool
PN3DCamera::_isPointVisile(const PNVector3f& targetV, const PNVector3f& vFov1, const PNVector3f& vFov2)
{
  _inTest1 = vFov1.scalarProduct(targetV) < 0;
  _inTest2 = vFov2.scalarProduct(targetV) < 0;

  if (!_isIn1)
	_isIn1 = (_inTest1 != _firstInTest1);
  if (!_isIn2)
	_isIn2 = (_inTest2 != _firstInTest2);

  return (_inTest1 && _inTest2) || (_isIn1 && _isIn2);
}

pnbool
PN3DCamera::_isPointVisile(const PNPoint3f& point, const PNPlane& plane1, const PNPlane& plane2)
{
  _inTest1 = plane1.getDistanceFromPlane(point) < 0;
  _inTest2 = plane1.getDistanceFromPlane(point) < 0;

  return (_inTest1 && _inTest2) || (_inTest1 != _firstInTest1 && _inTest2 != _firstInTest2);
}

//////////////////////////////////////////////////////////////////////////

pnbool
PN3DCamera::_isBoxSpeedVisible()
{
  PNVector3f	targetVector1 = _tTargetVector + _point1;
  PNVector3f	targetVector2 = _tTargetVector + _point2;
  PNVector3f	targetVector3 = _tTargetVector + _point3;
  PNVector3f	targetVector4 = _tTargetVector + _point4;
  PNVector3f	targetVector5 = _tTargetVector + _point5;
  PNVector3f	targetVector6 = _tTargetVector + _point6;
  PNVector3f	targetVector7 = _tTargetVector + _point7;
  PNVector3f	targetVector8 = _tTargetVector + _point8;

  //////////////////////////////////////////////////////////////////////////

  pnfloat		norm1 = targetVector1.getNorm();
  pnfloat		norm2 = targetVector2.getNorm();
  pnfloat		norm3 = targetVector3.getNorm();
  pnfloat		norm4 = targetVector4.getNorm();
  pnfloat		norm5 = targetVector5.getNorm();
  pnfloat		norm6 = targetVector6.getNorm();
  pnfloat		norm7 = targetVector7.getNorm();
  pnfloat		norm8 = targetVector8.getNorm();

  //////////////////////////////////////////////////////////////////////////
  // FOV
  //////////////////////////////////////////////////////////////////////////

  targetVector1 /= norm1;
  targetVector2 /= norm2;
  targetVector3 /= norm3;
  targetVector4 /= norm4;
  targetVector5 /= norm5;
  targetVector6 /= norm6;
  targetVector7 /= norm7;
  targetVector8 /= norm8;

  //////////////////////////////////////////////////////////////////////////

  _firstInTest1 = _tRightFov.scalarProduct(targetVector1) < 0;
  _firstInTest2 = _tLeftFov.scalarProduct(targetVector1) < 0;
  _isIn1 = _isIn2 = false;

  pnbool	inHFoV = 
	_isPointVisile(targetVector1, _tRightFov, _tLeftFov) ||
	_isPointVisile(targetVector2, _tRightFov, _tLeftFov) ||
	_isPointVisile(targetVector3, _tRightFov, _tLeftFov) ||
	_isPointVisile(targetVector4, _tRightFov, _tLeftFov) ||
	_isPointVisile(targetVector5, _tRightFov, _tLeftFov) ||
	_isPointVisile(targetVector6, _tRightFov, _tLeftFov) ||
	_isPointVisile(targetVector7, _tRightFov, _tLeftFov) ||
	_isPointVisile(targetVector8, _tRightFov, _tLeftFov);

  if (!inHFoV)
	return false;

  //////////////////////////////////////////////////////////////////////////

  _firstInTest1 = _tTopFov.scalarProduct(targetVector1) < 0;
  _firstInTest2 = _tBackFov.scalarProduct(targetVector1) < 0;
  _isIn1 = _isIn2 = false;

  pnbool	inVFoV = 
	_isPointVisile(targetVector1, _tTopFov, _tBackFov) ||
	_isPointVisile(targetVector2, _tTopFov, _tBackFov) ||
	_isPointVisile(targetVector3, _tTopFov, _tBackFov) ||
	_isPointVisile(targetVector4, _tTopFov, _tBackFov) ||
	_isPointVisile(targetVector5, _tTopFov, _tBackFov) ||
	_isPointVisile(targetVector6, _tTopFov, _tBackFov) ||
	_isPointVisile(targetVector7, _tTopFov, _tBackFov) ||
	_isPointVisile(targetVector8, _tTopFov, _tBackFov);

  if (!inVFoV)
	return false;

  //////////////////////////////////////////////////////////////////////////

  pnbool	inFov = inHFoV && inVFoV;

  if (!inFov)
	return inFov;

  //////////////////////////////////////////////////////////////////////////
  // NEAR-FAR
  //////////////////////////////////////////////////////////////////////////

  _firstInTest1 = _tNearPlane.getDistanceFromPlane(targetVector1) < 0;
  _firstInTest2 = _tFarPlane.getDistanceFromPlane(targetVector1) < 0;
  _isIn1 = _isIn2 = false;

  pnbool	inNearFar = 
	_isPointVisile(_point1, _tNearPlane, _tFarPlane) ||
	_isPointVisile(_point2, _tNearPlane, _tFarPlane) ||
	_isPointVisile(_point3, _tNearPlane, _tFarPlane) ||
	_isPointVisile(_point4, _tNearPlane, _tFarPlane) ||
	_isPointVisile(_point5, _tNearPlane, _tFarPlane) ||
	_isPointVisile(_point6, _tNearPlane, _tFarPlane) ||
	_isPointVisile(_point7, _tNearPlane, _tFarPlane) ||
	_isPointVisile(_point8, _tNearPlane, _tFarPlane);

  return inNearFar;
}

pnbool
PN3DCamera::_isBoxSlowVisible()
{
  return true;
}

pnbool
PN3DCamera::_isBoxVisible()
{
  const PNPoint3f&  minCoords = _testedObj->get3DModel()->getMin();
  const PNPoint3f&  maxCoords = _testedObj->get3DModel()->getMax();

  _point1.set(minCoords);
  _point2.set(minCoords.x, minCoords.y, maxCoords.z);
  _point3.set(minCoords.x, maxCoords.y, minCoords.z);
  _point4.set(maxCoords.x, minCoords.y, minCoords.z);
  _point5.set(maxCoords.x, maxCoords.y, minCoords.z);
  _point6.set(maxCoords.x, minCoords.y, maxCoords.z);
  _point7.set(minCoords.x, maxCoords.y, maxCoords.z);
  _point8.set(maxCoords);

  //////////////////////////////////////////////////////////////////////////

  return _isBoxSpeedVisible() && _isBoxSlowVisible();
}

//////////////////////////////////////////////////////////////////////////

pnbool
PN3DCamera::_isSphereVisible()
{
  PNQuatf	invertOrient = _testedObj->getOrient().getInvert();

  PNPoint3f	center = _testedObj->getCenter();
  pnfloat radius = _testedObj->getRadius();

  //////////////////////////////////////////////////////////////////////////
  
  _tTopDirection = _orient * _topDirection.getVector();
  _tTopDirection = invertOrient * _tTopDirection;
  _tTopDirection.setNorm(1.0f);
  
  _tRightFov.set(PNQuatf(_tTopDirection, _viewRightFov) * _tFrontDirection);
  _tRightPlane.setPlane(_tCoord, _tRightFov);

  if (_tRightPlane.getDistanceFromPlane(center) > radius)
	return false;

  //////////////////////////////////////////////////////////////////////////

  _tLeftFov.set(PNQuatf(_tTopDirection, _viewLeftFov) * _tFrontDirection);
  _tLeftPlane.setPlane(_tCoord, _tLeftFov);

  if (_tLeftPlane.getDistanceFromPlane(center) > radius)
	return false;

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  _tRightDirection = _orient * _rightDirection.getVector();
  _tRightDirection = invertOrient * _tRightDirection;
  _tRightDirection.setNorm(1.0f);

  _tTopFov.set(PNQuatf(_tRightDirection, _viewTopFov) * _tFrontDirection);
  _tTopPlane.setPlane(_tCoord, _tTopFov);

  if (_tTopPlane.getDistanceFromPlane(center) > radius)
	return false;

  //////////////////////////////////////////////////////////////////////////
  
  _tBackFov.set(PNQuatf(_tRightDirection, _viewBackFov) * _tFrontDirection);
  _tBackPlane.setPlane(_tCoord, _tBackFov);

  if (_tBackPlane.getDistanceFromPlane(center) > radius)
	return false;

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  
  PNPoint3f	nearCoord(
	_tCoord.x + (_tFrontDirection.x * _viewNear),
	_tCoord.y + (_tFrontDirection.y * _viewNear),
	_tCoord.z + (_tFrontDirection.z * _viewNear));

  _tNearPlane.setPlane(nearCoord, -_tFrontDirection);

  if (_tNearPlane.getDistanceFromPlane(center) > radius)
	return false;

  //////////////////////////////////////////////////////////////////////////
  
  PNPoint3f	farCoord(
	_tCoord.x + (_tFrontDirection.x * _viewFar),
	_tCoord.y + (_tFrontDirection.y * _viewFar),
	_tCoord.z + (_tFrontDirection.z * _viewFar));

  _tFarPlane.setPlane(farCoord, _tFrontDirection);

  if (_tFarPlane.getDistanceFromPlane(center) > radius)
	return false;

  //////////////////////////////////////////////////////////////////////////

  return true;
}

//////////////////////////////////////////////////////////////////////////

bool
PN3DCamera::_is3DObjVisible(PN3DObject* obj)
{
  PNLOCK(_testedObj = obj);

  if (_testedObj->get3DModel() == NULL || !_testedObj->isVisible())
	return false;

  PNQuatf	invertOrient = _testedObj->getOrient().getInvert();

  //////////////////////////////////////////////////////////////////////////

  _tFrontDirection = _orient * _frontDirection.getVector();
  _tFrontDirection = invertOrient * _tFrontDirection;
  _tFrontDirection.setNorm(1.0f);

  //////////////////////////////////////////////////////////////////////////
  
  _tCoord = _coord - _testedObj->getCoord();
  _tCoord = invertOrient * _tCoord;
  _tTargetVector = -_tCoord;

  //////////////////////////////////////////////////////////////////////////

  return _isSphereVisible() && _isBoxVisible();
}

//////////////////////////////////////////////////////////////////////////

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
		std::cout << "PN_EVENT_F_IN : " << it->second->getId() << std::endl;
	  }
	}
	else if (!_is3DObjVisible(it->second))
	{
	  PN3DObjList::iterator	itmp = oldIt++;
	  _list3DObj.erase(itmp);
	  PNEventManager::getInstance()->addEvent(PN_EVENT_F_OUT, this, new PNFrustrumEventData(it->second));
	  std::cout << "PN_EVENT_F_OUT : " << it->second->getId() << std::endl;
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

