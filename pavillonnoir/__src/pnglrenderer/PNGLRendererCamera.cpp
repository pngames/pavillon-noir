/*
 * PNGLRendererCamera.cpp
 * 
 * Description :
 * PNGLRendererCamera definition
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

#include <GL/glew.h>

#include "pndefs.h"
#include "pnmath.h"

#include "PNGLRendererCamera.hpp"
#include "PNQuatf.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNGLRendererCamera::PNGLRendererCamera() : _cfCallback(this, &PNGLRendererCamera::_cleanFrustrum), _ufCallback(this, &PNGLRendererCamera::_updateGLFOV)
{
  _coord.set(0.0f, 0.0f, -150.0f);

  //setTargetDirection(_rightDirection);
  //_targetDirection = _rightDirection.getVector();

  _playerCamera = this;
  _updateGLFov = false;

  _id = "renderCam";

  setUpdateGLFov(true);

  PNEventManager::getInstance()->addCallback(PN_EVENT_MU_START, _cfCallback);
}

PNGLRendererCamera::~PNGLRendererCamera()
{
  _cleanFrustrum(PN_EVENT_MU_START, NULL, NULL);

  setUpdateGLFov(false);
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRendererCamera::setUpdateGLFov(pnbool updatePersp)
{
  PNLOCK(this);

  if (updatePersp)
	PNEventManager::getInstance()->addCallback(PN_EVENT_RU_STARTING , _ufCallback);
  else
	PNEventManager::getInstance()->deleteCallback(PN_EVENT_RU_STARTING, _ufCallback);

  _updateGLFov = updatePersp;
}

void
PNGLRendererCamera::setFov(pnfloat deg)
{
  PNLOCK(this);

  pnfloat ratio = _width / _height;

  if (ratio < 1.0)
  {
	_viewVRadFov = DEGREE_TO_RADIAN_F(deg);
	_viewHRadFov = DEGREE_TO_RADIAN_F(deg * ratio);
  }
  else
  {
	_viewVRadFov = DEGREE_TO_RADIAN_F(deg * ratio);
	_viewHRadFov = DEGREE_TO_RADIAN_F(deg);
  }

  setUpdateGLFov(true);
}

void
PNGLRendererCamera::resizeGLWindow(pnint width, pnint height)
{
  PNLOCK(this);

  _width = (pnfloat)width;
  _height =(pnfloat)height;

  setFov(_viewFov);
}

pnfloat
PNGLRendererCamera::getWidth() const
{
  return _width;
}

pnfloat
PNGLRendererCamera::getHeight() const
{
  return _height;
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRendererCamera::_cleanFrustrum(pnEventType type, PNObject* source, PNEventData* ed)
{
  PNLOCK(this);

  _list3DObj.clear();
  setTarget(NULL);
}

void
PNGLRendererCamera::_updateGLFOV(pnEventType type, PNObject* source, PNEventData* ed)
{
  PNLOCK(this);

  setUpdateGLFov(false);

  GLint matrixMode;
  glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
  {
	glViewport(0, 0, (GLsizei)_width, (GLsizei)_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_viewFov, _width / _height, _viewNear, _viewFar);
  }
  glMatrixMode(matrixMode);
}

//////////////////////////////////////////////////////////////////////////

void	PNGLRendererCamera::updateViewMatrix()
{
  PNLOCK(this);

  PNMatrixTR4f	mat;

  mat.loadIdentity();
  mat.setRotationQuaternion(_orient.getInvert());

  glLoadMatrixf(mat.getMatrix());

  //////////////////////////////////////////////////////////////////////////
  mat.loadIdentity();

  //_coord = _orient * _coord;

  mat[12] = -_coord.x;
  mat[13] = -_coord.y;
  mat[14] = -_coord.z;

  glMultMatrixf(mat.getMatrix());

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  
  //glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
  //glTranslatef(-_coord.x, -_coord.y, -_coord.z);
}

//////////////////////////////////////////////////////////////////////////

void	PNGLRendererCamera::rotateRollRadians(pnfloat roll)
{
  return ;
}

void	PNGLRendererCamera::rotateYawRadians(pnfloat yaw)
{
  rotateYRadians(yaw);
}

//////////////////////////////////////////////////////////////////////////
};
