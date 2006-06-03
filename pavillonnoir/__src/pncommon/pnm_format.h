/*
 * pnm_format.h
 * 
 * Description :
 * Model files format
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

#ifndef _PNM_FORMAT_H_
# define _PNM_FORMAT_H_

#include "pnbasetypes.h"
#include "pnmath.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

#define PNM_EXT			"pnm"

#define	PNM_MAGIC		"PNM0001"
#define	PNM_MAGIC_SIZE	8

typedef	struct			pnmHeader_s
{
  pnchar				magic[PNM_MAGIC_SIZE];
  pnuint				version;

  pnuint				nbSupportedBones;
  pnuint				nbSupportedMaterials;

  pnuint				nbVerts;

  pnuint				nbMeshes;

  //-> list of pnmVertex_t
  //-> list of pnmMesh_t
}						pnmHeader_t;

typedef struct			pnmVertex_s
{
  pnpoint3f				coord;
  pnpoint3f_t			normale;
  pncolor_t				color;

  pnuint				nbBones;
  
  //-> list of pnmBoneID_t
}						pnmVertex_t;

typedef	struct			pnmBoneID_s
{
  pnint					boneIdx;
  pnfloat				weight;
}						pnmBoneID_t;

typedef	struct			pnmMesh_s
{
  pnint					materialIdx;
  pnuchar				colored;

  pnuint				nbVerts;

  pnuint				nbFaces;

  //-> list of pnmMeshVertex_t
  //-> list of pnpoint3ui
}						pnmMesh_t;

typedef struct			pnmMeshVertex_s
{
  pnuint				vertexIdx;
  pnpoint2f_t			texCoord;
}						pnmMeshVertex_t;

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNM_FORMAT_H_*/
