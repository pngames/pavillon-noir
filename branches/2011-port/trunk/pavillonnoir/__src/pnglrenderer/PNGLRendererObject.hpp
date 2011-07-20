/*
 * PNGLRendererObject.hpp
 * 
 * Description :
 * PNGLRendererObject declaration
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

#ifndef _PNGLRENDEREROBJECT_HPP_
# define _PNGLRENDEREROBJECT_HPP_

#include "pnrender.h"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNGLRenderer;
class PNRenderMaterial;

class			PNGLRendererObject : public PNRendererObject
{
  friend		PNRendererObject*	PNGLRenderer::newObj();
  friend		PNRendererObject*	PNGLRenderer::duplicateObj(PNRendererObject* obj);
  friend		void				PNGLRenderer::deleteObj(PNRendererObject* obj);
private:
  PNGLRenderer*	_renderer;

  void			_setBuffers();
  void			_unsetBuffers();
private:
  PNGLRendererObject(PNGLRenderer* renderer);
  PNGLRendererObject(const PNGLRendererObject& renderer);
  ~PNGLRendererObject();
public:
  //////////////////////////////////////////////////////////////////////////
  // Buffers

  void			setMode(pnrenderflag mode);

  void			setDFLColor(const pnfloat *color);
  void			setDFLColor(pnfloat r, pnfloat g, pnfloat b, pnfloat a);

  void			setNbVerts(pnint nbVerts);
  void			setBuffer(pnrenderarray flag_array, pnfloat *array, pnbool compressed = false);

  void			setInterleaveArray(void* array, pnuint size, pnrenderflag format = PN_T2F_C4F_N3F_V3F);

  void			setIndexBuffer(pnuint* array, pnint nbIndex, pnbool compressed = false);

  //////////////////////////////////////////////////////////////////////////
  // Faces

private:
  typedef std::list<PNFace*>	FaceList;
  FaceList		_faces;

  GLsizei		_sizeFaceBuffer;
  pnpoint3ui	_facesBuffer[PNGL_MAX_FACES];

  void			_initAttrib();
  void			_restoreAttrib();
  pnint			_renderBuffer();
public:
  pnint			addFaces(PNFace* faces, pnuint nb = 1);
  pnint			renderAllFaces(pnbool clear = true);
  pnint			renderAllFaces(pnrenderflag mode, pnbool clear = true);

  //////////////////////////////////////////////////////////////////////////
  // Material

  void			setMaterial(PNRenderMaterial* mat);
  void			setTextureRepeat(pnbool repeat);

  //////////////////////////////////////////////////////////////////////////
  // Render

  void			render();

  //////////////////////////////////////////////////////////////////////////
private:
  PNRenderMaterial*	_material;
  pnbool			_textureRepeat;

  pncolor_t		_color;

  pnuint		_nbVerts;

  pnfloat*		_verticesArrays;
  GLuint		_verticesArraysId;
  pnfloat*		_normalsArrays;
  GLuint		_normalsArraysId;
  pnfloat*		_colorsArrays;
  GLuint		_colorsArraysId;
  pnfloat*		_texturesArrays;
  GLuint		_texturesArraysId;

  pnuint		_size;
  pnrenderflag	_format;
  void*			_interleaveArrays;
  GLuint		_interleaveArraysId;

  pnuint		_nbIndex;
  pnrenderflag	_mode;
  pnuint*		_indexArrays;
  GLuint		_indexArraysId;

};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNGLRENDEREROBJECT_HPP_*/
