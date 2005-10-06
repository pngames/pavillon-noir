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

PNGLRendererCamera::PNGLRendererCamera()
{
  _coord.set(0.0f, 100.0f, -150.0f);

  //setTargetDirection(_rightDirection);
  //_targetDirection = _rightDirection.getVector();

  _playerCamera = this;

  _id = "renderCam";

  PNEventManager::getInstance()->addCallback(PN_EVENT_MU_START, EventCallback(this, &PNGLRendererCamera::_cleanFrustrum));
}

PNGLRendererCamera::~PNGLRendererCamera()
{
  _cleanFrustrum(PN_EVENT_MU_START, NULL, NULL);

  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MU_START, EventCallback(this, &PNGLRendererCamera::_cleanFrustrum));
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRendererCamera::_cleanFrustrum(pnEventType type, PNObject* source, PNEventData* ed)
{
  _list3DObj.clear();
}

//////////////////////////////////////////////////////////////////////////

void	PNGLRendererCamera::updateViewMatrix()
{
  std::cout << " [UPDATE] updateViewMatrix" << std::endl;

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
//			   	  Methods for calculate Frustrum                        //
//////////////////////////////////////////////////////////////////////////


void	PNGLRendererCamera::calcFrustumPlanes()
{
	  pnfloat p[16];   // projection matrix
    pnfloat mv[16];  // model-view matrix
    pnfloat mvp[16]; // model-view-projection matrix
    pnfloat t;

    glGetFloatv( GL_PROJECTION_MATRIX, p );
    glGetFloatv( GL_MODELVIEW_MATRIX, mv );

    //
    // Concatenate the projection matrix and the model-view matrix to produce 
    // a combined model-view-projection matrix.
    //
    
    mvp[ 0] = mv[ 0] * p[ 0] + mv[ 1] * p[ 4] + mv[ 2] * p[ 8] + mv[ 3] * p[12];
    mvp[ 1] = mv[ 0] * p[ 1] + mv[ 1] * p[ 5] + mv[ 2] * p[ 9] + mv[ 3] * p[13];
    mvp[ 2] = mv[ 0] * p[ 2] + mv[ 1] * p[ 6] + mv[ 2] * p[10] + mv[ 3] * p[14];
    mvp[ 3] = mv[ 0] * p[ 3] + mv[ 1] * p[ 7] + mv[ 2] * p[11] + mv[ 3] * p[15];

    mvp[ 4] = mv[ 4] * p[ 0] + mv[ 5] * p[ 4] + mv[ 6] * p[ 8] + mv[ 7] * p[12];
    mvp[ 5] = mv[ 4] * p[ 1] + mv[ 5] * p[ 5] + mv[ 6] * p[ 9] + mv[ 7] * p[13];
    mvp[ 6] = mv[ 4] * p[ 2] + mv[ 5] * p[ 6] + mv[ 6] * p[10] + mv[ 7] * p[14];
    mvp[ 7] = mv[ 4] * p[ 3] + mv[ 5] * p[ 7] + mv[ 6] * p[11] + mv[ 7] * p[15];

    mvp[ 8] = mv[ 8] * p[ 0] + mv[ 9] * p[ 4] + mv[10] * p[ 8] + mv[11] * p[12];
    mvp[ 9] = mv[ 8] * p[ 1] + mv[ 9] * p[ 5] + mv[10] * p[ 9] + mv[11] * p[13];
    mvp[10] = mv[ 8] * p[ 2] + mv[ 9] * p[ 6] + mv[10] * p[10] + mv[11] * p[14];
    mvp[11] = mv[ 8] * p[ 3] + mv[ 9] * p[ 7] + mv[10] * p[11] + mv[11] * p[15];

    mvp[12] = mv[12] * p[ 0] + mv[13] * p[ 4] + mv[14] * p[ 8] + mv[15] * p[12];
    mvp[13] = mv[12] * p[ 1] + mv[13] * p[ 5] + mv[14] * p[ 9] + mv[15] * p[13];
    mvp[14] = mv[12] * p[ 2] + mv[13] * p[ 6] + mv[14] * p[10] + mv[15] * p[14];
    mvp[15] = mv[12] * p[ 3] + mv[13] * p[ 7] + mv[14] * p[11] + mv[15] * p[15];

    //
    // Extract the frustum clipping plane and normalize it.
    //
		//1 = right, 2 = left, 3 = bottom, 4 = top, 5 = far, 6 = near
		
	for (int i = 0; i < 6; i++)
	{
    _frustumPlanes[i][0] = mvp[ 3] - mvp[ 0];
    _frustumPlanes[i][1] = mvp[ 7] - mvp[ 4];
    _frustumPlanes[i][2] = mvp[11] - mvp[ 8];
    _frustumPlanes[i][3] = mvp[15] - mvp[12];

    t = (float) sqrt( _frustumPlanes[i][0] * _frustumPlanes[i][0] + 
                      _frustumPlanes[i][1] * _frustumPlanes[i][1] + 
                      _frustumPlanes[i][2] * _frustumPlanes[i][2] );

    _frustumPlanes[i][0] /= t;
    _frustumPlanes[i][1] /= t;
    _frustumPlanes[i][2] /= t;
    _frustumPlanes[i][3] /= t;
	}
}

//True = point is in, False = point is not in...

bool PNGLRendererCamera::pointInFrustrum(pnfloat x, pnfloat y, pnfloat z)
{
	 for( int i = 0; i < 6; ++i )
    {
        if( _frustumPlanes[i][0] * x +
            _frustumPlanes[i][1] * y +
            _frustumPlanes[i][2] * z +
            _frustumPlanes[i][3] < 0)
            return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
};
