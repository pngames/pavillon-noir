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
#include "PNInterface.hpp"

#include "PN3DCamera.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

typedef enum
{
  PN_GUI_CEGUI,
} guiType;

class PNRendererObject;
class PNRenderMaterial;
class PNPoint;

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
  
  virtual void				initRender(pnuint widht, pnuint height, pnuint bpp, pnchar* title, pnbool fullscreen)=0;

  //////////////////////////////////////////////////////////////////////////
  
  virtual void				run()=0;
  virtual void				endRendering()=0;

  //////////////////////////////////////////////////////////////////////////
  
  virtual pnuint			getTicks()=0;

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

  virtual void				deleteObj(PNRendererObject* obj)=0;

  //////////////////////////////////////////////////////////////////////////
  // Material

  virtual PNRenderMaterial*	newMaterial()=0;
  virtual void				deleteMaterial(PNRenderMaterial* material)=0;

  //////////////////////////////////////////////////////////////////////////
  
  virtual void				renderSphere(pndouble radius, pnint slices, pnint stacks, const pnfloat* color)=0;
  virtual void				renderBox(pnuint width, pnuint height, pnuint depth, const pnfloat* color)=0;

  typedef enum
  {
	PN_LINK_RIGHT = 0x000001,
	PN_LINK_LEFT = 0x000001 < 1,
  } linkDirection;

  virtual void				renderLink(const PNPoint& p1, const PNPoint& p2, const pnfloat* color, pnuint direction = 0, pnfloat thickness = 1.0f)=0;

  //////////////////////////////////////////////////////////////////////////
  // CEGUI
  virtual guiType			getGUIType()=0;
  virtual void*				getGUIRenderer()=0;

  virtual void				initGUI()=0;
  //////////////////////////////////////////////////////////////////////////

};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNRENDERERINTERFACE_HPP_*/