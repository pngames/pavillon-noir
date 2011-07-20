/*
 * m_parseBody.cpp
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

#include <iostream>

#include "pndefs.h"

#include "PNI3DMesh.hpp"
#include "PNI3DModel.hpp"
#include "PNIVertex.hpp"

#include "pnm_format.h"

using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

pnint
PNI3DModel::parseVertexes()
{
  _vertex.reserve(_header.nbVerts);

  static pnmVertex_t	vert;
  static pnmBoneID_t*	tabBones;

  _min.setNull();
  _max.setNull();

  for (pnuint i = 0; i < _header.nbVerts; ++i)
  {
	_istream->read((char*)&vert, sizeof(vert));

	//////////////////////////////////////////////////////////////////////////

	tabBones = NULL;

	if (vert.nbBones > 0)
	{
	  tabBones = new pnmBoneID_t[vert.nbBones];
	  _istream->read((char*)tabBones, sizeof(*tabBones) * vert.nbBones);
	}

	//////////////////////////////////////////////////////////////////////////

	_vertex.push_back(PNIVertex(vert, tabBones));

	//////////////////////////////////////////////////////////////////////////

	PNIVertex&	v = _vertex.back();

	_min.x = PNMIN(_min.x, v.x); _max.x = PNMAX(_max.x, v.x);
	_min.y = PNMIN(_min.y, v.y); _max.y = PNMAX(_max.y, v.y);
	_min.z = PNMIN(_min.z, v.z); _max.z = PNMAX(_max.z, v.z);

	//////////////////////////////////////////////////////////////////////////

	//cout << i << " nbBones=" << vert.nbBones << endl;
	//cout << i << " : " << v << endl;
  }

  PNVector3f dim = PNVector3f(_min, _max);
  dim /= 2.0f;
  _center = _min;
  _center += dim;
  _radius = dim.getNorm();

  return PNEC_SUCCESS;
}

pnint
PNI3DModel::parseMeshes()
{
  PNI3DMesh*	mesh = NULL;
  _nbFaces = 0;

  for (pnuint i = 0; i < _header.nbMeshes; ++i)
  {
	mesh = new PNI3DMesh(*this);

	_nbFaces += mesh->getNbFaces();

	_meshes.push_back(mesh);
  }

  return PNEC_SUCCESS;
}

pnint
PNI3DModel::parseBody()
{
  parseVertexes();

  parseMeshes();

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
