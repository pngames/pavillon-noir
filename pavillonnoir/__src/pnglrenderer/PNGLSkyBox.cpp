/*
* PNGLSkyBox.cpp
* 
* Description :
* PNGLSkyBox definition
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
#include "pnrender.h"

#include "PNGLRendererCamera.hpp"

#include "PNGLSkyBox.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNGLSkyBox*		PNGLSkyBox::_instance = NULL;

PNGLSkyBox*
PNGLSkyBox::getInstance()
{
  if (_instance == NULL)
	_instance = new PNGLSkyBox();

  return _instance;
}

//////////////////////////////////////////////////////////////////////////

PNGLSkyBox::PNGLSkyBox()
{
  _enabled = false;

  _skyObj = NULL;

  _textCoords = NULL;
  _skyBox = NULL;

  _top = NULL;
  _bottom = NULL;
  _left = NULL;
  _right = NULL;
  _front = NULL;
  _back = NULL;
}

PNGLSkyBox::~PNGLSkyBox(void)
{
  
}

//////////////////////////////////////////////////////////////////////////

/// Set the skyBox enabled or disabled
void
PNGLSkyBox::setEnabled(pnbool enabled)
{
  
}

/// Set the sky box properties
void
PNGLSkyBox::set(PNRendererObject* skyBox)
{
  
}

/// Set the sky box properties
void
PNGLSkyBox::set(pnfloat* textCoords, PNRenderMaterial* skyBox)
{
  
}

/// Set the sky box properties
void
PNGLSkyBox::set(PNRenderMaterial* top, PNRenderMaterial* bottom, PNRenderMaterial* left, PNRenderMaterial* right, PNRenderMaterial* front, PNRenderMaterial* back)
{
  
}

//////////////////////////////////////////////////////////////////////////

void
PNGLSkyBox::render()
{
  PNGLRendererCamera*	camera = (PNGLRendererCamera*)PN3DCamera::getRenderCam();

  pnfloat	color[4] = {0.2f, 0.2f, 0.8f, 1.0f};

  PNRendererInterface::getInstance()->renderBox(1000/*camera->getFar()*/, 1000/*camera->getFar()*/, 1000/*camera->getFar()*/, color);
}

//////////////////////////////////////////////////////////////////////////
};
