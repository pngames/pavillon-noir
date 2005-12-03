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
#include "pnexception.h"

#include "PNGLRendererCamera.hpp"
#include "PN3DMaterial.hpp"
#include "PNTexture.hpp"

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

pnbool
PNGLSkyBox::isEnabled()
{
  return _enabled;
}

//////////////////////////////////////////////////////////////////////////

/// Set the skyBox enabled or disabled
void
PNGLSkyBox::setEnabled(pnbool enabled)
{
  _enabled = enabled;
}

/// Set the sky box properties
void
PNGLSkyBox::set(PNRendererObject* skyObj)
{
  throw PNException("Not implemented.");

  _skyObj = skyObj;
}

/// Set the sky box properties
void
PNGLSkyBox::set(pnfloat* textCoords, PNRenderMaterial* skyBox)
{
  throw PNException("Not implemented.");

  _textCoords = textCoords;
  _skyBox = skyBox;
}

/// Set the sky box properties
void
PNGLSkyBox::set(PNRenderMaterial* top, PNRenderMaterial* bottom, PNRenderMaterial* left, PNRenderMaterial* right, PNRenderMaterial* front, PNRenderMaterial* back)
{
  _top = top;
  _bottom = bottom;
  _left = left;
  _right = right;
  _front = front;
  _back = back;
}

//////////////////////////////////////////////////////////////////////////

void
PNGLSkyBox::_renderBox(pnfloat size)
{
  pnfloat	color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  glColor4fv(color);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

  pnfloat xmin = -0.5f * size;
  pnfloat xmax = 0.5f * size;
  pnfloat ymin = -0.5f * size;
  pnfloat ymax = 0.5f * size;
  pnfloat zmin = -0.5f * size;
  pnfloat zmax = 0.5f * size;

  if (_front != NULL)
  {
	_front->setTextureRepeat(false);
	_front->bind();
  }

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xmax, ymin, zmax);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xmax, ymax, zmax);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xmin, ymin, zmax);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xmin, ymax, zmax);
  }
  glEnd();

  if (_back != NULL)
  {
	_back->setTextureRepeat(false);
	_back->bind();
  }

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xmin, ymin, zmin);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xmin, ymax, zmin);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xmax, ymin, zmin);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xmax, ymax, zmin);
  }
  glEnd();

  if (_right != NULL)
  {
	_right->setTextureRepeat(false);
	_right->bind();
  }

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xmax, ymin, zmin);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xmax, ymax, zmin);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xmax, ymin, zmax);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xmax, ymax, zmax);
  }
  glEnd();

  if (_left != NULL)
  {
	_left->setTextureRepeat(false);
	_left->bind();
  }

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xmin, ymin, zmax);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xmin, ymax, zmax);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xmin, ymin, zmin);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xmin, ymax, zmin);
  }
  glEnd();

  if (_top != NULL)
  {
	_top->setTextureRepeat(false);
	_top->bind();
  }

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xmin, ymax, zmin);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xmin, ymax, zmax);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xmax, ymax, zmin);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xmax, ymax, zmax);
  }
  glEnd();

  if (_bottom != NULL)
  {
	_bottom->setTextureRepeat(false);
	_bottom->bind();
  }

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, -1.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(xmin, ymin, zmax);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(xmin, ymin, zmin);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(xmax, ymin, zmax);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(xmax, ymin, zmin);
  }
  glEnd();
}

void
PNGLSkyBox::_renderObj()
{
  
}

void
PNGLSkyBox::render(pnfloat size)
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glCullFace(GL_FRONT);

  _renderBox(size);

  glPopAttrib();
}

void
PNGLSkyBox::render()
{
  PNGLRendererCamera*	camera = (PNGLRendererCamera*)PN3DCamera::getRenderCam();

  pnfloat size = sqrtf((camera->getFar() * camera->getFar()) / 2);

  render(size);
}

//////////////////////////////////////////////////////////////////////////
};
