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
#include <GL/glew.h>

#include "pnrender.h"
#include "pnevent.h"

#include "PNRendererInterface.hpp"
#include "PNGLRendererCamera.hpp"
#include "PNGLSceneGraph.hpp"

#include "PNInfoPanel.hpp"

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
class PNEventData;
class PNStringParameter;

#define PNGL_MAX_FACES		4096

class						PNGLRenderer : public PNRendererInterface
{
private:
  std::map<pnrenderflag, GLenum>	_converter;

  PNGLRenderer();
  ~PNGLRenderer();

  //////////////////////////////////////////////////////////////////////////

  void						_onPlayVideo(pnEventType, PNObject*, PNEventData*);

  //////////////////////////////////////////////////////////////////////////

  PNGLSceneGraph			_scene;

  pnbool					_isProgramLooping;
  
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
private:
  PNConfigurableParameter*	_pFullScreen;
  PNConfigurableParameter*	_pDefinition;
  PNConfigurableParameter*	_pBpp;
  PNStringParameter*		_pTitle;
public:
  void						update(PNConfigurableParameter* p);

  //////////////////////////////////////////////////////////////////////////

  void						run();
  void						endRendering();
  
  //////////////////////////////////////////////////////////////////////////
  
  pnuint					getTicks();

  //////////////////////////////////////////////////////////////////////////
  
  void						enable(pnrenderflag flag);
  void						disable(pnrenderflag flag);

  //////////////////////////////////////////////////////////////////////////
public:
  PNRendererObject*			newObj();

  PNRendererObject*			newObj(
	void* interleave, pnuint size, pnrenderflag format,
	pnuint* index, pnuint nb_index, pnrenderflag mode = PN_TRIANGLES);

  PNRendererObject*			newObj(pnfloat* vertices, pnfloat* normals, 
	pnfloat* colors, pnfloat* textures, pnuint nb_vert,
	pnuint* index, pnuint nb_index, pnrenderflag mode = PN_TRIANGLES);

  void						deleteObj(PNRendererObject* obj);

  //////////////////////////////////////////////////////////////////////////
  // SKY

  /// Set the skyBox enabled or disabled
  virtual void				setSkyBoxEnabled(pnbool enabled);

  /// Set the sky box properties
  virtual void				setSkyBox(PNRendererObject* skyBox);
  /// Set the sky box properties
  virtual void				setSkyBox(pnfloat* textCoords, PNRenderMaterial* skyBox);
  /// Set the sky box properties
  virtual void				setSkyBox(PNRenderMaterial* top, PNRenderMaterial* bottom, PNRenderMaterial* left, PNRenderMaterial* right, PNRenderMaterial* front, PNRenderMaterial* back);

  /// Use by pneditor to print skyBox
  virtual void				renderSkyBox(pnfloat size);

  //////////////////////////////////////////////////////////////////////////
  
  PNRenderMaterial*			newMaterial();
  void						deleteMaterial(PNRenderMaterial* material);

  void						cleanSceneTextures();

  //////////////////////////////////////////////////////////////////////////
  // MAIN
  //////////////////////////////////////////////////////////////////////////

  void						initSDL(int widht, int height, int bpp, char* title, bool fullscreen);
  void						setSDLFlags(int *flags, bool fullscreen);

  void						initGL(GLsizei width, GLsizei height);

  //////////////////////////////////////////////////////////////////////////
  
  void						renderSphere(pndouble radius, pnint slices, pnint stacks, const pnfloat* color, const PNPoint3f& coord = PNPoint3f::ZERO, pnbool outside = true);
  void						renderCylinder(pndouble baseRadius, pndouble topRadius, pndouble height, pnint slices, pnint stacks, const pnfloat* color, const PNPoint3f& coord = PNPoint3f::ZERO, pnbool outside = true);
  void						renderBox(pnfloat width, pnfloat height, pnfloat depth, const pnfloat* color, const PNPoint3f& coord = PNPoint3f::ZERO, pnbool outside = true);

  void						renderLink(const PNPoint3f& p1, const PNPoint3f& p2, const pnfloat* color, pnuint direction = 0, pnfloat thickness = 1.0f);

  //////////////////////////////////////////////////////////////////////////
  // CEGUI
  PNInfoPanel*				_infoPanel;
  CEGUI::Renderer*			_guirenderer;
  void						updateGUI(pnEventType type, PNObject* source, PNEventData* data);
  void*						getGUIRenderer();
  guiType					getGUIType();
  void						initGUI(); 
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNGLRENDERER_HPP_*/
