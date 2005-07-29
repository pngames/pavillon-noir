/*
 * PNIVertex.cpp
 * 
 * Description :
 * PNIVertex definition
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

#include "PNIVertex.hpp"
#include "PNI3DMesh.hpp"
#include "PNMatrixTR4f.hpp"
#include "PN3DSkeleton.hpp"
#include "PNVector3f.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNIVertex::PNIVertex(pnmVertex_t& vert, pnmBoneID_t* bonesId) : PNPoint(vert.coord)
{
  initVert(vert, bonesId);
}

PNIVertex::~PNIVertex()
{
  
}

void
PNIVertex::initVert(pnmVertex_t& vert, pnmBoneID_t* bonesId)
{
  set(vert.coord);
  normale = vert.normale;
  color = vert.color;

  for (pnuint i = 0; i < vert.nbBones; ++i)
  {
	_bones.push_back(bonesId[i]);
  }
}

//////////////////////////////////////////////////////////////////////////

void
PNIVertex::addIndex(PNI3DMesh* mesh, pnuint index)
{
  _indexes.push_back(PAIR_INDEX(mesh, index));
}

//////////////////////////////////////////////////////////////////////////

void
PNIVertex::transform(PN3DSkeleton* sk)
{
  if (_bones.size() == 0)
	return ;

  LIST_INDEXES::iterator it = _indexes.begin();

  PAIR_INDEX&		index = *it;

  static pnfloat	tmp[3];

  pnpoint3f_t&		vtmp = index.first->_vertBuffer[index.second];
  pnpoint3f_t&		ntmp = index.first->_normBuffer[index.second];

  memset(&vtmp, 0, sizeof(vtmp));
  memset(&ntmp, 0, sizeof(ntmp));

  for (LIST_BONES::iterator itb = _bones.begin(); itb != _bones.end(); ++itb)
  {
	pnmBoneID_t& bone = *itb;

	sk->getMatrix(bone.boneIdx).transform(tmp, &x, bone.weight);

	vtmp.x += tmp[0];
	vtmp.y += tmp[1];
	vtmp.z += tmp[2];

	//////////////////////////////////////////////////////////////////////////

	sk->getMatrix(bone.boneIdx).transform3(tmp, &normale.x, bone.weight);

	ntmp.x += tmp[0];
	ntmp.y += tmp[1];
	ntmp.z += tmp[2];
  }

  PNVector3f::setNorm(&ntmp.x, 1.0f);

  //////////////////////////////////////////////////////////////////////////
  // modify vertex in all buffers

  for (++it; it != _indexes.end(); ++it)
  {
	PAIR_INDEX&	index = *it;

	index.first->_vertBuffer[index.second].x = vtmp.x;
	index.first->_vertBuffer[index.second].y = vtmp.y;
	index.first->_vertBuffer[index.second].z = vtmp.z;

	index.first->_normBuffer[index.second].x = ntmp.x;
	index.first->_normBuffer[index.second].y = ntmp.y;
	index.first->_normBuffer[index.second].z = ntmp.z;
  }
}

//////////////////////////////////////////////////////////////////////////
};
