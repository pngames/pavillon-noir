/*
 * PN3DCamera.hpp
 * 
 * Description :
 * PN3DCamera declaration
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

#ifndef _PN3DCAMERA_HPP_
# define _PN3DCAMERA_HPP_

#include <list>

#include "pnevent.h"

#include "PNPoint3f.hpp"
#include "PNVector3f.hpp"
#include "PNPlane.hpp"

#include "PN3DObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNPlane;
class PNPoint3f;
class PNVector3f;

typedef std::list<PN3DObject *> PN3DObjList;

/// Camera implementation
class PNAPI					PN3DCamera : public PN3DObject
{
public:
  /// Default constructor for PN3DCamera.
  PN3DCamera();
  /// Destructor for PN3DObject.
  ~PN3DCamera();

  //////////////////////////////////////////////////////////////////////////

public:
  /// Return unique rendering camera
  static PN3DCamera*		getRenderCam();

  /// Return list of 3d objects in camera frustrum
  const PN3DObjList&		getListObj();
  
  //////////////////////////////////////////////////////////////////////////
  
  void						setFar(pnfloat near);
  void						setNear(pnfloat far);

  virtual void				setFov(pnfloat deg);
  void						setHFov(pnfloat rad);
  void						setVFov(pnfloat rad);

  //////////////////////////////////////////////////////////////////////////
  
  pnfloat					getFar() const;
  pnfloat					getNear() const;

  //////////////////////////////////////////////////////////////////////////
  
  /// Render object using PNRendererInterface
  virtual void				render();

  //////////////////////////////////////////////////////////////////////////
protected:
  PN3DObjList				_list3DObj;

  //////////////////////////////////////////////////////////////////////////
protected:
  PN3DObject*				_testedObj;

  pnbool					_firstInTest1, _firstInTest2;
  pnbool					_inTest1, _inTest2;
  pnbool					_isIn1, _isIn2;

  pnbool					_isPointVisile(const PNVector3f& targetV, const PNVector3f& vFov1, const PNVector3f& vFov2);
  pnbool					_isPointVisile(const PNPoint3f& point, const PNPlane& plane1, const PNPlane& plane2);

  //////////////////////////////////////////////////////////////////////////
  
  pnbool					_isSphereVisible();

  //////////////////////////////////////////////////////////////////////////

  PNPoint3f					_point1;
  PNPoint3f					_point2;
  PNPoint3f					_point3;
  PNPoint3f					_point4;
  PNPoint3f					_point5;
  PNPoint3f					_point6;
  PNPoint3f					_point7;
  PNPoint3f					_point8;
  
  pnbool					_isBoxSpeedVisible();
  pnbool					_isBoxSlowVisible();
  pnbool					_isBoxVisible();

  //////////////////////////////////////////////////////////////////////////
  
  pnfloat					_viewLeftFov;
  pnfloat					_viewRightFov;
  pnfloat					_viewTopFov;
  pnfloat					_viewBackFov;

  PNVector3f				_tFrontDirection;
  PNVector3f				_tRightDirection;
  PNVector3f				_tTopDirection;

  PNPoint3f					_tCoord;
  PNVector3f				_tTargetVector;

  PNVector3f				_tRightFov;
  PNVector3f				_tLeftFov;
  PNVector3f				_tTopFov;
  PNVector3f				_tBackFov;

  PNPlane					_tRightPlane;
  PNPlane					_tLeftPlane;
  PNPlane					_tTopPlane;
  PNPlane					_tBackPlane;
  PNPlane					_tNearPlane;
  PNPlane					_tFarPlane;

  pnbool					_is3DObjVisible(PN3DObject* obj);

  void			  		  	_updateFrustrum(pnEventType type, PNObject* source, PNEventData* ed);

  void						_onRSUEnding(pnEventType type, PNObject* source, PNEventData* ed);

  //////////////////////////////////////////////////////////////////////////

  pnfloat					_viewFar;
  pnfloat					_viewNear;
  pnfloat					_viewFov;
  pnfloat					_viewHRadFov;
  pnfloat					_viewVRadFov;

  //////////////////////////////////////////////////////////////////////////

  /// Unique rendering camera
  static PN3DCamera*		_playerCamera;
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PN3DGROUND_HPP_*/
