/*
 * PNGLRenderer.hpp
 * 
 * Description :
 * PNGLRenderer declaration
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

#ifndef _PNGLRENDERER_HPP_
#define  _PNGLRENDERER_HPP_

#include <list>
#include <map>

#include "mygl.h"
#include "myglu.h"

#include "pnrender.h"

#include "PNRendererInterface.hpp"
#include "PNGLRendererCamera.hpp"

namespace CEGUI
{
  class Renderer;
};

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNRendererObject;
class PN3DObject;
class PNFace;
class PNGLTexture;

#define PNGL_MAX_FACES		4096

class						PNGLRenderer : public PNRendererInterface
{
private:
  std::map<pnrenderflag, GLenum>	_converter;

  PNGLRenderer();
  ~PNGLRenderer();

  PNGLRendererCamera		_renderCam;

  pnbool					_isProgramLooping;

  pnuint					_widht;
  pnuint					_height;
  
  pnuint                    _lastRenderTime; 
public:
  static PNGLRenderer*		getInstance();

  GLenum					convertFlag(pnrenderflag flag);

  //////////////////////////////////////////////////////////////////////////
  // PNRENDERERINTERFACE
  //////////////////////////////////////////////////////////////////////////

  void						init();

  void						initRender(pnuint widht, pnuint height, pnuint bpp, pnchar* title, pnbool fullscreen);

  //////////////////////////////////////////////////////////////////////////

  void						run();
  void						endRendering();

  void						rotate(pnfloat x,pnfloat y, pnfloat z, pnfloat angle);
  void						translate(pnfloat x, pnfloat y, pnfloat z);
  void						scale(pnfloat x, pnfloat y, pnfloat z);
  
  //////////////////////////////////////////////////////////////////////////
  
  pnuint					getTicks();

  //////////////////////////////////////////////////////////////////////////
  
  void						enable(pnrenderflag flag);
  void						disable(pnrenderflag flag);

  //////////////////////////////////////////////////////////////////////////
  
  PNRendererObject*			newObj();

  PNRendererObject*			newObj(
	void* interleave, pnuint size, pnrenderflag format,
	pnuint* index, pnuint nb_index, pnrenderflag mode = PN_TRIANGLES);

  PNRendererObject*			newObj(pnfloat* vertices, pnfloat* normals, 
	pnfloat* colors, pnfloat* textures, pnuint nb_vert,
	pnuint* index, pnuint nb_index, pnrenderflag mode = PN_TRIANGLES);

  void						deleteObj(PNRendererObject* obj);

  //////////////////////////////////////////////////////////////////////////
  
  PNRenderMaterial*			newMaterial();
  void						deleteMaterial(PNRenderMaterial* material);

  //////////////////////////////////////////////////////////////////////////
  // MAIN
  //////////////////////////////////////////////////////////////////////////

  void						initSDL(int widht, int height, int bpp, char* title, bool fullscreen);
  void						setSDLFlags(int *flags, bool fullscreen);

  void						initGL(GLsizei width, GLsizei height);
  void						resizeGLWindow(GLsizei width, GLsizei height);

  void						initFrame();

  void						pushMatrix();
  void						popMatrix();

  //////////////////////////////////////////////////////////////////////////
  
  PNGLTexture*				newTexture(void);
  void						deleteTexture(PNGLTexture* texture);

  //////////////////////////////////////////////////////////////////////////
  
  void						renderSphere(pndouble radius, pnint slices, pnint stacks, const pnfloat* color);
  void						renderBox(pnuint width, pnuint height, pnuint depth, const pnfloat* color);

  void						renderLink(const PNPoint& p1, const PNPoint& p2, const pnfloat* color, pnuint direction = 0, pnfloat thickness = 1.0f);

  //////////////////////////////////////////////////////////////////////////
  // CEGUI

  CEGUI::Renderer*			_guirenderer;

  void*						getGUIRenderer();
  guiType					getGUIType();
  void						initGUI();

  //////////////////////////////////////////////////////////////////////////

 
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNGLRENDERER_HPP_*/
