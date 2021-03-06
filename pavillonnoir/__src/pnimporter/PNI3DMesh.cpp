/*
 * PNI3DMesh.cpp
 * 
 * Description :
 * PNI3DMesh definition
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
#include "pnmath.h"
#include "pnrender.h"

#include "PN3DMaterial.hpp"
#include "PNI3DMesh.hpp"
#include "PNI3DModel.hpp"
#include "PNFace.hpp"

using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNI3DMesh::PNI3DMesh(PNI3DModel& parent) :
_parent(parent), _robject(NULL), _defaultrobject(NULL),
_vertBuffer(NULL), _normBuffer(NULL), _texCoordBuffer(NULL), _colorBuffer(NULL), _idBuffer(NULL),
_defaultVertBuffer(NULL), _defaultNormBuffer(NULL)
{
  unserializeFromStream(*parent._istream);
}

PNI3DMesh::~PNI3DMesh()
{
  dispose();
}

void
PNI3DMesh::dispose()
{
  if (_vertBuffer != NULL)
	delete[] _vertBuffer;
  _vertBuffer = NULL;

  if (_defaultVertBuffer != NULL)
	delete[] _defaultVertBuffer;
  _defaultVertBuffer = NULL;

  if (_normBuffer != NULL)
	delete[] _normBuffer;
  _normBuffer = NULL;

  if (_defaultNormBuffer != NULL)
	delete[] _defaultNormBuffer;
  _defaultNormBuffer = NULL;

  if (_colorBuffer != NULL)
	delete[] _colorBuffer;
  _colorBuffer = NULL;

  if (_idBuffer != NULL)
	delete[] _idBuffer;
  _idBuffer = NULL;

  PNRendererInterface::getInstance()->deleteObj(_robject);
  _robject = NULL;

  PNRendererInterface::getInstance()->deleteObj(_defaultrobject);
  _defaultrobject = NULL;
}

//////////////////////////////////////////////////////////////////////////

void
PNI3DMesh::render(std::vector<PN3DMaterial*>* mat, pnbool defaultRender)
{
  PNRendererObject*	robject = defaultRender ? _defaultrobject : _robject;

  if (mat != NULL && mat->size() > (pnuint)_header.materialIdx && (*mat)[_header.materialIdx] != NULL)
	robject->setMaterial((*mat)[_header.materialIdx]->getRenderMaterial());
  else
	robject->setMaterial(NULL);

  robject->render();
}

pnuint
PNI3DMesh::getNbVerts() const
{
  return _header.nbVerts;
}

pnuint
PNI3DMesh::getNbFaces() const
{
  return _header.nbFaces;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNI3DMesh::computeVertex(pnfloat* buffer)
{
  if (_vertBuffer != NULL)
	memcpy(buffer, _vertBuffer, sizeof(*_vertBuffer) * getNbVerts());

  return getNbVerts() * 3;
}

pnuint
PNI3DMesh::computeNormales(pnfloat* buffer)
{
  if (_normBuffer != NULL)
	memcpy(buffer, _normBuffer, sizeof(*_normBuffer) * getNbVerts());

  return getNbVerts() * 3;
}

pnuint
PNI3DMesh::computeTextCoord(pnfloat* buffer)
{
  if (_texCoordBuffer != NULL)
	memcpy(buffer, _texCoordBuffer, sizeof(*_texCoordBuffer) * getNbVerts());

  return getNbVerts() * 2;
}

pnuint
PNI3DMesh::computeColors(pnfloat* buffer)
{
  if (_colorBuffer != NULL)
	memcpy(buffer, _colorBuffer, sizeof(*_colorBuffer) * getNbVerts());

  return getNbVerts() * 4;
}

pnuint
PNI3DMesh::computeFaces(std::vector<PN3DMaterial*>& mat, PNFace* faces, pnuint step)
{
  for (pnuint i = 0; i < _header.nbFaces; ++i, ++faces)
  {
	faces->set(step + _idBuffer[i][0], step + _idBuffer[i][1], step + _idBuffer[i][2]);

	if (_header.materialIdx >= 0 && _header.materialIdx < (pnint)mat.size())
	  faces->setMaterial(mat[_header.materialIdx]);
	else
	  faces->setMaterial(NULL);
  }

  return getNbFaces();
}

//////////////////////////////////////////////////////////////////////////

pnint
PNI3DMesh::_parseVertices()
{
  _vertBuffer = new pnpoint3f_t[_header.nbVerts];
  _normBuffer = new pnpoint3f_t[_header.nbVerts];

  if (_header.materialIdx >= 0)
	_texCoordBuffer = new pnpoint2f_t[_header.nbVerts];

  if (_header.colored)
	_colorBuffer = new pncolor_t[_header.nbVerts];

  //////////////////////////////////////////////////////////////////////////
  
  pnmMeshVertex_t*	tabVertices = new pnmMeshVertex_t[_header.nbVerts];

  _parent._istream->read((char*)tabVertices, sizeof(*tabVertices) * _header.nbVerts);

  for (pnuint i = 0; i < _header.nbVerts; ++i)
  {
	pnmMeshVertex_t&  vert = tabVertices[i];

	PNIVertex&		  ivert = _parent._vertex[vert.vertexIdx];

	//////////////////////////////////////////////////////////////////////////
	
	_vertBuffer[i].x = ivert.x;
	_vertBuffer[i].y = ivert.y;
	_vertBuffer[i].z = ivert.z;

	//////////////////////////////////////////////////////////////////////////

	_normBuffer[i].x = ivert.normale.x;
	_normBuffer[i].y = ivert.normale.y;
	_normBuffer[i].z = ivert.normale.z;

	//////////////////////////////////////////////////////////////////////////

	if (_header.materialIdx >= 0)
	  _texCoordBuffer[i] = vert.texCoord;

	//////////////////////////////////////////////////////////////////////////

	if  (_header.colored)
	  _colorBuffer[i] = ivert.color;

	//////////////////////////////////////////////////////////////////////////

	ivert.addIndex(this, i);
  }

  return PNEC_SUCCESS;
}

pnint
PNI3DMesh::_parseFaces()
{
  _idBuffer = new pnpoint3ui[_header.nbFaces];

  _parent._istream->read((char*)_idBuffer, sizeof(*_idBuffer) * _header.nbFaces);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNI3DMesh::unserializeFromStream(std::istream& i)
{
  dispose();

  //////////////////////////////////////////////////////////////////////////
  
  i.read((char*)&_header, sizeof(_header));

  /*cout << "nbVerts=" << _header.nbVerts << endl;
  cout << "nbFaces=" << _header.nbFaces << endl;*/

  //////////////////////////////////////////////////////////////////////////

  _parseVertices();

  _parseFaces();

  //////////////////////////////////////////////////////////////////////////
  
  _robject = PNRendererInterface::getInstance()->newObj();

  //////////////////////////////////////////////////////////////////////////

  _robject->setNbVerts(_header.nbVerts);

  _robject->setBuffer(PN_VARRAY, (pnfloat*)_vertBuffer);
  _robject->setBuffer(PN_NARRAY, (pnfloat*)_normBuffer);

  //////////////////////////////////////////////////////////////////////////

  if (_colorBuffer != NULL)
	_robject->setBuffer(PN_CARRAY, (pnfloat*)_colorBuffer, true);

  //////////////////////////////////////////////////////////////////////////

  if (_texCoordBuffer != NULL)
  {
	_robject->setBuffer(PN_TCARRAY, (pnfloat*)_texCoordBuffer, true);

	_robject->setTextureRepeat(false);

	for (pnuint i = 0; i <  _header.nbVerts; ++i)
	{
	  if (_texCoordBuffer[i].x > 1.0f || _texCoordBuffer[i].y > 1.0f)
	  {
		_robject->setTextureRepeat(true);
		break;
	  }
	}
  }

  //////////////////////////////////////////////////////////////////////////

  _robject->setIndexBuffer((pnuint*)_idBuffer, _header.nbFaces * 3, true);

  //////////////////////////////////////////////////////////////////////////

  _defaultrobject = PNRendererInterface::getInstance()->duplicateObj(_robject);

  _defaultVertBuffer = new pnpoint3f_t[_header.nbVerts];
  _defaultNormBuffer = new pnpoint3f_t[_header.nbVerts];

  memcpy(_defaultVertBuffer, _vertBuffer, sizeof(pnpoint3f_t) * _header.nbVerts);
  memcpy(_defaultNormBuffer, _normBuffer, sizeof(pnpoint3f_t) * _header.nbVerts);

  _defaultrobject->setBuffer(PN_VARRAY, (pnfloat*)_defaultVertBuffer, true);
  _defaultrobject->setBuffer(PN_NARRAY, (pnfloat*)_defaultNormBuffer, true);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
