/*
 * PNGLRendererCamera.hpp
 * 
 * Description :
 * PNGLRendererCamera declaration
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

#ifndef _PNGLRENDERERCAMERA_HPP_
# define _PNGLRENDERERCAMERA_HPP_

#include <GL/glew.h>

#include "PN3DCamera.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class			PNGLRendererCamera : public PN3DCamera
{
  friend class PNGLRenderer;
  friend class PNGLSceneGraph;

  EventCallback	_cfCallback;
  EventCallback	_ufCallback;

public:
  void			updateViewMatrix();

  void			resizeGLWindow(pnfloat width, pnfloat height);
  pnfloat		getWidth() const;
  pnfloat		getHeight() const;

  void			setUpdateGLFov(pnbool updatePersp);

  //////////////////////////////////////////////////////////////////////////
private:
  PNGLRendererCamera();
  ~PNGLRendererCamera();

  void			rotateRollRadians(pnfloat roll);
  void			rotateYawRadians(pnfloat yaw);
  
  pnfloat 		_frustumPlanes[6][4];

  //////////////////////////////////////////////////////////////////////////

  void			_cleanFrustrum(pnEventType type, PNObject* source, PNEventData* ed);
  void			_updateGLFOV(pnEventType type, PNObject* source, PNEventData* ed);

  //////////////////////////////////////////////////////////////////////////
private:
  pnfloat		_width;
  pnfloat		_height;

  pnbool		_updateGLFov;
};
//////////////////////////////////////////////////////////////////////////
};

#endif //_PNGLRENDERERCAMERA_HPP_