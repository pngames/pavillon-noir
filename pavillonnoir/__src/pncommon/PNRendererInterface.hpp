/*
 * PNRendererInterface.hpp
 * 
 * Description :
 * PNRendererInterface declaration
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

#ifndef _PNRENDERERINTERFACE_HPP_
# define _PNRENDERERINTERFACE_HPP_

#include <list>

#include "pnrender.h"

#include "PNPoint3f.hpp"

#include "PNInterface.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

typedef enum
{
  PN_GUI_CEGUI,
} guiType;

class PNRendererObject;
class PNRenderMaterial;

class PNAPI					PNRendererInterface : public PNInterface
{
protected:
  static PNRendererInterface*  _instance;
public:
  static PNRendererInterface*  getInstance();
protected:
  PNRendererInterface();
  virtual ~PNRendererInterface();

  //////////////////////////////////////////////////////////////////////////
public:
  plugintypes				getType();
  
  virtual void				initRender()=0;

  //////////////////////////////////////////////////////////////////////////
  
  virtual void				run()=0;
  virtual void				endRendering()=0;
  virtual void				flushSDLEvents()=0;
  virtual pnbool			getSDLGrabState()=0;
  
  virtual void				setFullScreen(pnbool fullscreen)=0;
  virtual pnbool			getFullScreen()=0;

  //////////////////////////////////////////////////////////////////////////
  
  virtual pnuint			getTicks()=0;
  virtual pnuint			getCurrentDelta()=0;

  //////////////////////////////////////////////////////////////////////////
  
  virtual void				enable(pnrenderflag flag)=0;
  virtual void				disable(pnrenderflag flag)=0;

  //////////////////////////////////////////////////////////////////////////
  // OBJ

  virtual PNRendererObject* newObj()=0;

  virtual PNRendererObject* newObj(
	void* interleave, pnuint size, pnrenderflag format,
	pnuint  *index, pnuint nb_index, pnrenderflag mode = PN_TRIANGLES)=0;

  virtual PNRendererObject* newObj(
	pnfloat *vertices, pnfloat *normals, 
	pnfloat *colors, pnfloat *textures, pnuint nb_vert,
	pnuint  *index, pnuint nb_index, pnrenderflag mode = PN_TRIANGLES)=0;

  virtual PNRendererObject* duplicateObj(PNRendererObject* obj)=0;

  virtual void				deleteObj(PNRendererObject* obj)=0;

  //////////////////////////////////////////////////////////////////////////
  // SKY

  /// Set the skyBox enabled or disabled
  virtual void				setSkyBoxEnabled(pnbool enabled)=0;

  /// Set the sky box properties
  virtual void				setSkyBox(PNRendererObject* skyBox)=0;
  /// Set the sky box properties
  virtual void				setSkyBox(pnfloat* textCoords, PNRenderMaterial* skyBox)=0;
  /// Set the sky box properties
  virtual void				setSkyBox(PNRenderMaterial* top, PNRenderMaterial* bottom, PNRenderMaterial* left, PNRenderMaterial* right, PNRenderMaterial* front, PNRenderMaterial* back)=0;

  /// Use by pneditor to print skyBox
  virtual void				renderSkyBox(pnfloat size)=0;

  //////////////////////////////////////////////////////////////////////////
  // Material

  /// Make a new material
  virtual PNRenderMaterial*	newMaterial()=0;
  /// Delete a material
  virtual void				deleteMaterial(PNRenderMaterial* material)=0;

  //////////////////////////////////////////////////////////////////////////
  
  /// Render sphere
  virtual void				renderSphere(pndouble radius, pnint slices, pnint stacks, const pnfloat* color, const PNPoint3f& coord = PNPoint3f::ZERO, pnbool outside = true)=0;

  /// Render cylinder
  virtual void				renderCylinder(pndouble baseRadius, pndouble topRadius, pndouble height, pnint slices, pnint stacks, const pnfloat* color, const PNPoint3f& coord = PNPoint3f::ZERO, pnbool outside = true)=0;

  /// Render box
  virtual void				renderBox(pnfloat width, pnfloat height, pnfloat depth, const pnfloat* color, const PNPoint3f& coord = PNPoint3f::ZERO, pnbool outside = true)=0;

  typedef enum
  {
	PN_LINK_RIGHT = 0x000001,
	PN_LINK_LEFT = 0x000001 < 1,
  } linkDirection;

  virtual void				renderLink(const PNPoint3f& p1, const PNPoint3f& p2, const pnfloat* color, pnuint direction = 0, pnfloat thickness = 1.0f)=0;

  //////////////////////////////////////////////////////////////////////////
  // CEGUI
  virtual guiType			getGUIType()=0;
  virtual void*				getGUIRenderer()=0;

  virtual void				initGUI()=0;
};

inline PNRendererInterface*
PNRendererInterface::getInstance()
{
  return _instance;
}

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNRENDERERINTERFACE_HPP_*/

