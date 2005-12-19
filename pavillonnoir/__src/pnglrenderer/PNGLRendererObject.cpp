/*
 * PNGLRendererObject.cpp
 * 
 * Description :
 * PNGLRendererObject definition
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

#include <iostream>

#include "pndefs.h"

#include "PNGLRenderer.hpp"
#include "PNGLRendererObject.hpp"
#include "PNGLMaterial.hpp"
#include "PNFace.hpp"
#include "PNGLTexture.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNGLRendererObject::PNGLRendererObject(PNGLRenderer* renderer) : _renderer(renderer)
{
  _material = NULL;

  _nbVerts = 0;
  _verticesArrays = NULL;
  _verticesArraysId = (GLuint)-1;
  _normalsArrays = NULL;
  _normalsArraysId = (GLuint)-1;
  _colorsArrays = NULL;
  _colorsArraysId = (GLuint)-1;
  _texturesArrays = NULL;
  _texturesArraysId = (GLuint)-1;

  _size = 0;
  _format = PN_T2F_C4F_N3F_V3F;
  _interleaveArrays = NULL;
  _interleaveArraysId = (GLuint)-1;

  _nbIndex = 0;
  _mode = PN_TRIANGLES;
  _indexArrays = NULL;
  _indexArraysId = (GLuint)-1;

  //_color = DFLCOLOR;
  _color.r = 1.0f;
  _color.g = 0.0f;
  _color.b = 0.0f;
  _color.a = 1.0f;
}

PNGLRendererObject::PNGLRendererObject(const PNGLRendererObject& obj)
{
  memcpy(this, &obj, sizeof(obj));
}

PNGLRendererObject::~PNGLRendererObject()
{
  if (_verticesArraysId != (GLuint)-1)
	glDeleteBuffersARB(1, &_verticesArraysId);

  if (_normalsArraysId != (GLuint)-1)
	glDeleteBuffersARB(1, &_normalsArraysId);

  if (_colorsArraysId != (GLuint)-1)
	glDeleteBuffersARB(1, &_colorsArraysId);

  if (_texturesArraysId != (GLuint)-1)
	glDeleteBuffersARB(1, &_texturesArraysId);
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRendererObject::setMode(pnrenderflag mode)
{
  _mode = mode;
}

void
PNGLRendererObject::setDFLColor(const pnfloat *color)
{
  _color.r = color[0];
  _color.g = color[1];
  _color.b = color[2];
  _color.a = color[3];
}

void
PNGLRendererObject::setDFLColor(pnfloat r, pnfloat g, pnfloat b, pnfloat a)
{
  setDFLColor(&r);
}

void
PNGLRendererObject::setNbVerts(pnint nbVerts)
{
  _nbVerts = nbVerts;
}

void
PNGLRendererObject::setBuffer(pnrenderarray flag_array, pnfloat *array, pnbool compressed/* = false*/)
{
  static GLboolean	vertex_buffer_object_ENABLED = GLEW_ARB_vertex_buffer_object;
  
  GLuint			*id = NULL;
  GLsizeiptrARB		buffSize = _nbVerts * sizeof(pnfloat);

  switch (flag_array)
  {
  case 	PN_VARRAY:
	id = &_verticesArraysId;
	_verticesArrays = array;
	buffSize *= 3;

	break;

  case 	PN_NARRAY:
	id = &_normalsArraysId;
	_normalsArrays = array;
	buffSize *= 3;

	break;

  case	PN_CARRAY:
	id = &_colorsArraysId;
	_colorsArrays = array;
	buffSize *= 4;

	break;

  case PN_TCARRAY:
	id = &_texturesArraysId;
	_texturesArrays = array;
	buffSize *= 2;

	break;
  }

  if (vertex_buffer_object_ENABLED && compressed && id != NULL && array != NULL)
  {
	if (*id == (GLuint)-1)
	  glGenBuffersARB(1, id);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, *id);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, buffSize, array, GL_STATIC_DRAW_ARB);

	GLint	stmp = 0;
	glGetBufferParameterivARB(GL_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &stmp);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	if (stmp <= 0)
	{
	  glDeleteBuffersARB(1, id);
	  *id = (GLuint)-1;

	  return;
	}
  }
}

void
PNGLRendererObject::setInterleaveArray(void* array, pnuint size, pnrenderflag format)
{
  _interleaveArrays = array;
  _size = size;

  _format = format;
}

void
PNGLRendererObject::setIndexBuffer(pnuint *array, pnint nbIndex, pnbool compressed)
{
  _indexArrays = array;
  _nbIndex = nbIndex;

  static GLboolean	vertex_buffer_object_ENABLED = GLEW_ARB_vertex_buffer_object;

  if (vertex_buffer_object_ENABLED && compressed && array != NULL)
  {
	if (_indexArraysId == (GLuint)-1)
	  glGenBuffersARB(1, &_indexArraysId);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indexArraysId);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _nbIndex * sizeof(*_indexArrays), _indexArrays, GL_STATIC_DRAW_ARB);

	GLint	stmp = 0;
	glGetBufferParameterivARB(GL_ELEMENT_ARRAY_BUFFER_ARB, GL_BUFFER_SIZE_ARB, &stmp);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	if (stmp <= 0)
	{
	  glDeleteBuffersARB(1, &_indexArraysId);
	  _indexArraysId = (GLuint)-1;

	  return;
	}
  }
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRendererObject::setMaterial(PNRenderMaterial* mat)
{
  _material = mat;
}

void	
PNGLRendererObject::setTextureRepeat(pnbool repeat)
{
  _textureRepeat = repeat;
}

//////////////////////////////////////////////////////////////////////////

void	
PNGLRendererObject::_initAttrib()
{
  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
  glPushAttrib(GL_ALL_ATTRIB_BITS);
}

void
PNGLRendererObject::_restoreAttrib()
{
  glPopClientAttrib();
  glPopAttrib();
}

void	
PNGLRendererObject::render()
{
  if (_nbIndex <= 0)
	return ;

  _initAttrib();
  _setBuffers();

  //////////////////////////////////////////////////////////////////////////

  if (_material != NULL)
  {
	_material->setTextureRepeat(_textureRepeat);
	_material->bind();
  }
  else
  {
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }

  //////////////////////////////////////////////////////////////////////////
  // Rend object by indices

  if (_indexArrays == NULL)
	glDrawArrays(_renderer->convertFlag(_mode), 0, _nbIndex);
  else
  {
	if (_indexArraysId != (GLuint)-1) 
	{
	  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _indexArraysId); 
	  glDrawElements(_renderer->convertFlag(_mode), _nbIndex, GL_UNSIGNED_INT, NULL);
	  glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0); 
	}
	else 
	  glDrawElements(_renderer->convertFlag(_mode), _nbIndex, GL_UNSIGNED_INT, _indexArrays);
  }

  //////////////////////////////////////////////////////////////////////////

  _unsetBuffers();
  _restoreAttrib();
}

//////////////////////////////////////////////////////////////////////////

pnint
PNGLRendererObject::addFaces(PNFace* faces, pnuint nb)
{
  for (pnuint i = 0; i < nb; ++i, ++faces)
	_faces.push_back(faces);

  return PNEC_SUCCESS;
}

pnint
PNGLRendererObject::renderAllFaces(pnbool clear)
{
  _initAttrib();

  //////////////////////////////////////////////////////////////////////////

  PNGLMaterial* currentMaterial = NULL;
  PNGLTexture*	currentTexture = NULL;

  _sizeFaceBuffer = 0;
  pnuint*	facesTmp = (pnuint*)_facesBuffer;

  for (FaceList::iterator it = _faces.begin(); it != _faces.end(); it++)
  {
	PNFace*	face = *it;

	PNGLMaterial* mat = (PNGLMaterial*)face->getMaterial();

	if (mat != currentMaterial)
	{
	  _renderBuffer();
	  facesTmp = (pnuint*)_facesBuffer;

	  if (_mode <= PN_TRIANGLE_FAN && mat != NULL)
	  {
		glMaterialfv(GL_FRONT,  GL_AMBIENT,	mat->getAmbient());
		glMaterialfv(GL_FRONT,  GL_DIFFUSE,	mat->getDiffuse());
		glMaterialfv(GL_FRONT,  GL_SPECULAR, mat->getSpecular());
		glMaterialfv(GL_FRONT,  GL_EMISSION, mat->getEmissive());
		glMaterialf (GL_FRONT,  GL_SHININESS, mat->getGlossiness());

		mat->setTextureRepeat(face->getTextureRepeat());
		PNGLTexture*  tex = (PNGLTexture*)mat->getTexture();

		if (tex == NULL)
		  glDisable(GL_TEXTURE_2D);
		else if (tex != currentTexture)
		{
		  glEnable(GL_TEXTURE_2D);
		  tex->bind();

		  currentTexture = tex;
		}
	  }
	  else
	  {
		glMaterialfv(GL_FRONT,  GL_AMBIENT,	(const GLfloat *)&DFLCOLOR);
		glMaterialfv(GL_FRONT,  GL_DIFFUSE,	(const GLfloat *)&DFLCOLOR);
		glMaterialfv(GL_FRONT,  GL_SPECULAR, (const GLfloat *)&DFLCOLOR);
		glMaterialfv(GL_FRONT,  GL_EMISSION, (const GLfloat *)&DFLCOLOR);
		glMaterialf (GL_FRONT,  GL_SHININESS, 0.0f);
		glDisable(GL_TEXTURE_2D);
	  }

	  currentMaterial = mat;
	}
	
	facesTmp[0] = face->v0;
	facesTmp[1] = face->v1;
	facesTmp[2] = face->v2;

	if (_mode == PN_LINES)
	{
	  facesTmp[3] = face->v0;
	  facesTmp += 4;
	  _sizeFaceBuffer += 4;
	}
	else
	{
	  facesTmp += 3;
	  _sizeFaceBuffer += 3;
	}
  }

  _renderBuffer();

  facesTmp = (pnuint*)_facesBuffer;

  if (clear == true)
	_faces.clear();

  //////////////////////////////////////////////////////////////////////////
  
  _restoreAttrib();

  return PNEC_SUCCESS;
}

pnint
PNGLRendererObject::renderAllFaces(pnrenderflag mode, pnbool clear)
{
  pnrenderflag	tmp = _mode;

  setMode(mode);
  pnint error = renderAllFaces(clear);
  setMode(tmp);

  return error;
}

pnint
PNGLRendererObject::_renderBuffer()
{
  if (_sizeFaceBuffer <= 0)
	return PNEC_SUCCESS;

  glDrawElements(_renderer->convertFlag(_mode), _sizeFaceBuffer, GL_UNSIGNED_INT, _facesBuffer);

  _sizeFaceBuffer = 0;

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

#define		SET_BUFFER(id, array, fct)	\
  if (id != (GLuint)-1) \
{ \
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, id); \
  fct(GL_FLOAT, 0, NULL); \
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0); \
} \
else \
  fct(GL_FLOAT, 0, array);

#define		SET_BUFFER_SIZE(id, array, size, fct) \
  if (id != (GLuint)-1) \
{ \
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, id); \
  fct(size, GL_FLOAT, 0, NULL); \
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0); \
} \
else \
  fct(size, GL_FLOAT, 0, array);

void	
PNGLRendererObject::_setBuffers()
{ 
  glColor4fv((const GLfloat *)&_color);
  glMaterialfv(GL_FRONT,  GL_DIFFUSE, (const GLfloat *)&_color);

  if (_size > 0)
  {
	//////////////////////////////////////////////////////////////////////////
	// Set interleave

	glInterleavedArrays(_renderer->convertFlag(_format), 0, _interleaveArrays);
  }
  else
  {
	//////////////////////////////////////////////////////////////////////////
	// Set buffers

	glEnableClientState(GL_VERTEX_ARRAY);
	SET_BUFFER_SIZE(_verticesArraysId, _verticesArrays, 3, glVertexPointer);

	if (_mode <= PN_TRIANGLE_FAN && _normalsArrays != NULL)
	{
	  glEnableClientState(GL_NORMAL_ARRAY);
	  SET_BUFFER(_normalsArraysId, _normalsArrays, glNormalPointer);
	}
	else
	  glDisableClientState(GL_NORMAL_ARRAY);

	if (_colorsArrays != NULL)
	{
	  glEnableClientState(GL_COLOR_ARRAY);
	  SET_BUFFER_SIZE(_colorsArraysId, _colorsArrays, 4, glColorPointer);
	}
	else
	  glDisableClientState(GL_COLOR_ARRAY);

	if (_texturesArrays != NULL)
	{
	  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	  SET_BUFFER_SIZE(_texturesArraysId, _texturesArrays, 2, glTexCoordPointer);
	}
	else
	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
}

void
PNGLRendererObject::_unsetBuffers()
{
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
//////////////////////////////////////////////////////////////////////////
};
