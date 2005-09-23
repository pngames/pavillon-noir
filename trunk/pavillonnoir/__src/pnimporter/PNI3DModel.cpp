/*
 * PNI3DModel.cpp
 * 
 * Description :
 * PNI3DModel definition
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

#include "PNI3DModel.hpp"
#include "PNI3DMesh.hpp"
#include "PNFace.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNI3DModel::PNI3DModel()
{
}

PNI3DModel::~PNI3DModel()
{
  dispose();
}

void
PNI3DModel::dispose()
{
  _meshes.clear();
  _vertex.clear();
}

//////////////////////////////////////////////////////////////////////////

void
PNI3DModel::render(std::vector<PN3DMaterial*>& mats, PN3DSkeleton* sk)
{
  if (sk != NULL)
  {
	for (VECTOR_VERTEX::iterator it = _vertex.begin(); it != _vertex.end(); ++it)
	{
	  PNIVertex&  vert = *it;

	  vert.transform(sk);

	  _min.x = PNMIN(_min.x, vert.x); _max.x = PNMAX(_max.x, vert.x);
	  _min.y = PNMIN(_min.y, vert.y); _max.y = PNMAX(_max.y, vert.y);
	  _min.z = PNMIN(_min.z, vert.z); _max.z = PNMAX(_max.z, vert.z);
	}

	/*PNVector3f dim = PNVector3f(_min, _max);
	dim /= 2;
	_center = min;
	_center += *dim;*/
  }

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
	(*it)->render(mats);
}

void
PNI3DModel::render(PN3DSkeleton* sk)
{
  if (sk != NULL)
  {
	for (VECTOR_VERTEX::iterator it = _vertex.begin(); it != _vertex.end(); ++it)
	{
	  PNIVertex&  vert = *it;

	  vert.transform(sk);

	  _min.x = PNMIN(_min.x, vert.x); _max.x = PNMAX(_max.x, vert.x);
	  _min.y = PNMIN(_min.y, vert.y); _max.y = PNMAX(_max.y, vert.y);
	  _min.z = PNMIN(_min.z, vert.z); _max.z = PNMAX(_max.z, vert.z);
	}

	/*PNVector3f dim = PNVector3f(_min, _max);
	dim /= 2;
	_center = min;
	_center += *dim;*/
  }

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
	(*it)->render();
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNI3DModel::getNbSupportedBones() const
{
  return _header.nbSupportedBones;
}

pnuint
PNI3DModel::getNbSupportedMaterials() const
{
  return _header.nbSupportedMaterials;
}

pnuint
PNI3DModel::getNbVerts() const
{
  return _header.nbVerts;
}

pnuint
PNI3DModel::getNbFaces() const
{
  return _nbFaces;
}

//////////////////////////////////////////////////////////////////////////

const PNPoint&
PNI3DModel::getMin() const
{
  return _min;
}

const PNPoint&
PNI3DModel::getMax() const
{
  return _max;
}

const PNPoint&
PNI3DModel::getCenter() const
{
  return _center;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNI3DModel::getNbVertexComputed()
{
  pnuint  nb = 0;

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
  {
	//if (it == _meshes.begin())
	  nb += ((PNI3DMesh*)*it)->getNbVerts();
  }

  return nb;
}

pnuint
PNI3DModel::computeVertex(pnfloat* buffer, pnuint step)
{
  int nb = step;

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
  {
	//if (it == _meshes.begin())
	  nb += ((PNI3DMesh*)*it)->computeVertex(buffer + nb);
  }

  return nb - step;
}

pnuint
PNI3DModel::computeNormales(pnfloat* buffer, pnuint step)
{
  int nb = step;

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
  {
	//if (it == _meshes.begin())
	  nb += ((PNI3DMesh*)*it)->computeNormales(buffer + nb);
  }

  return nb - step;
}

pnuint
PNI3DModel::computeTextCoord(pnfloat* buffer, pnuint step)
{
  int nb = step;

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
  {
	//if (it == _meshes.begin())
	  nb += ((PNI3DMesh*)*it)->computeTextCoord(buffer + nb);
  }

  return nb - step;
}

pnuint
PNI3DModel::computeColors(pnfloat* buffer, pnuint step)
{
  int nb = step;

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
  {
	//if (it == _meshes.begin())
	  nb += ((PNI3DMesh*)*it)->computeColors(buffer + nb);
  }

  return nb - step;
}

pnuint
PNI3DModel::getNbFacesComputed()
{
  //return ((PNI3DMesh*)*_meshes.begin())->getNbFaces();

  return getNbFaces();
}

pnuint
PNI3DModel::computeFaces(std::vector<PN3DMaterial*>& mat, PNFace* faces, pnuint step)
{
  int	  nb = step;
  pnuint  stepVerts = 0;

  for (LIST_3DMESH::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
  {
	//if (it == _meshes.begin())
	{
	  nb += ((PNI3DMesh*)*it)->computeFaces(mat, faces + nb, stepVerts);
	  stepVerts += ((PNI3DMesh*)*it)->getNbVerts();
	}
  }

  return nb - step;
}

//////////////////////////////////////////////////////////////////////////

pnint				PNI3DModel::unserializeFromStream(std::istream& i)
{
  _istream = &i;

  int err = PNEC_SUCCES;

  if ((err = parseHeader()) == 0)
	err = parseBody();

  return err;
}

//////////////////////////////////////////////////////////////////////////
};
