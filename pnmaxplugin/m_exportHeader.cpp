/*
 * m_exportHeader.cpp
 * 
 * Description :
 * PNModelExporter definition
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 *
 * This file is part of pnmaxplugin.
 *
 * pnmaxplugin is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * pnmaxplugin is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with pnmaxplugin; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "stdafx.h"

#include "PNModelExporter.hpp"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

int	PNModelExporter::exportHeader()
{ 
  _file->Write(&_header, sizeof(_header));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int	PNModelExporter::parseNodeHeader(IGameNode* node)
{
  if (node == NULL)
	return TRUE;

  IGameObject *obj = node->GetIGameObject();

  if (obj->GetIGameType() == IGameObject::IGAME_BONE ||
	obj->GetIGameType() == IGameObject::IGAME_HELPER ||
	node->GetChildCount())
  {
	_mapBonesId[node->GetNodeID()] = _header.nbSupportedBones++;
  }
  else if (obj->GetIGameType() == IGameObject::IGAME_MESH)
  {
	IGameMesh *mesh = (IGameMesh *)obj;

	mesh->SetCreateOptimizedNormalList();

	if (obj->IsRenderable() && mesh->InitializeData())
	{
	  for (pnuint i = 0; i < mesh->GetNumberOfFaces(); ++i)
	  {
		FaceEx*	  face = mesh->GetFace(i);

		int	vIdTmp0 = _header.nbVerts + face->vert[0];
		int	vIdTmp1 = _header.nbVerts + face->vert[1];
		int	vIdTmp2 = _header.nbVerts + face->vert[2];

		if (mesh->GetNumberOfNormals() > 0)
		{
		  _mapVertex[vIdTmp0].normal[_nbNormals + face->norm[0]] = _nbNormals + face->norm[0];
		  _mapVertex[vIdTmp1].normal[_nbNormals + face->norm[1]] = _nbNormals + face->norm[1];
		  _mapVertex[vIdTmp2].normal[_nbNormals + face->norm[2]] = _nbNormals + face->norm[2];
		}

		if (mesh->GetNumberOfColorVerts() > 0)
		{
		  _mapVertex[vIdTmp0].color[_nbColorVerts + face->color[0]] = _nbColorVerts + face->color[0];
		  _mapVertex[vIdTmp1].color[_nbColorVerts + face->color[1]] = _nbColorVerts + face->color[1];
		  _mapVertex[vIdTmp2].color[_nbColorVerts + face->color[2]] = _nbColorVerts + face->color[2];
		}

		IGameMaterial*	mat = mesh->GetMaterialFromFace(face);
		int				matId;

		if (mat != NULL)
		{
		  matId = _mapMaterialsId[mat];

		  //PNMainWin::WriteLine("%i 0 %f %f", face->vert[0], mesh->GetTexVertex(face->texCoord[0]).x, mesh->GetTexVertex(face->texCoord[0]).y);
		  //PNMainWin::WriteLine("%i 1 %f %f", face->vert[1], mesh->GetTexVertex(face->texCoord[1]).x, mesh->GetTexVertex(face->texCoord[1]).y);
		  //PNMainWin::WriteLine("%i 2 %f %f", face->vert[2], mesh->GetTexVertex(face->texCoord[2]).x, mesh->GetTexVertex(face->texCoord[2]).y);

		  memcpy(_mapMeshes[matId].verts_texCoords[vIdTmp0].texCoord[_nbTexCoords + face->texCoord[0]].coord,
			mesh->GetTexVertex(face->texCoord[0]),
			sizeof(pnpoint2f));
		  memcpy(_mapMeshes[matId].verts_texCoords[vIdTmp1].texCoord[_nbTexCoords + face->texCoord[1]].coord,
			mesh->GetTexVertex(face->texCoord[1]),
			sizeof(pnpoint2f));
		  memcpy(_mapMeshes[matId].verts_texCoords[vIdTmp2].texCoord[_nbTexCoords + face->texCoord[2]].coord,
			mesh->GetTexVertex(face->texCoord[2]),
			sizeof(pnpoint2f));
		}
		else
		{
		  matId = -1;

		  memcpy(_mapMeshes[matId].verts_texCoords[vIdTmp0].texCoord[-1].coord, _defaultTexCoord, sizeof(pnpoint2f));
		  memcpy(_mapMeshes[matId].verts_texCoords[vIdTmp1].texCoord[-1].coord, _defaultTexCoord, sizeof(pnpoint2f));
		  memcpy(_mapMeshes[matId].verts_texCoords[vIdTmp2].texCoord[-1].coord, _defaultTexCoord, sizeof(pnpoint2f));
		}

		face_t	ftmp;

		ftmp.vertStep = _header.nbVerts;
		ftmp.texStep = _nbTexCoords;
		ftmp.face = *face;

		_mapMeshes[matId].faces.push_back(ftmp);
	  }

	  _header.nbVerts += mesh->GetNumberOfVerts();
	  _nbNormals += mesh->GetNumberOfNormals();
	  _nbTexCoords += mesh->GetNumberOfTexVerts();
	  _nbColorVerts += mesh->GetNumberOfColorVerts();

	  _listMeshes.push_back(node);
	}
  }

  node->ReleaseIGameObject();

  for (pnuint i = 0; i < node->GetChildCount(); ++i)
  {
	parseNodeHeader(node->GetNodeChild(i));
  }

  return TRUE;
}

int PNModelExporter::initExport()
{
  PNMainWin::WriteLine("## Init model exporter ##");

  memset(&_header, 0, sizeof (_header));

  //////////////////////////////////////////////////////////////////////////
  // magic

  memcpy(_header.magic, PNM_MAGIC, strlen(PNM_MAGIC));
  _header.version = 001;

  //////////////////////////////////////////////////////////////////////////
  // materials

  _mapMaterialsId.clear();

  for (int i = 0; i < _igameScene->GetRootMaterialCount(); ++i)
  {
	IGameMaterial *material = _igameScene->GetRootMaterial(i);

	if (material->IsSubObjType())
	  for (int i = 0; i < material->GetSubMaterialCount(); ++i)
		_mapMaterialsId[material->GetSubMaterial(i)] = _header.nbSupportedMaterials++;
	else
	  _mapMaterialsId[material] = _header.nbSupportedMaterials++;
  }

  PNMainWin::WriteLine("nb materials: %i", _header.nbSupportedMaterials);

  //////////////////////////////////////////////////////////////////////////
  // object

  _listMeshes.clear();
  _mapBonesId.clear();
  _mapMeshes.clear();
  _mapVertex.clear();

  _nbNormals = 0;
  _nbTexCoords = 0;
  _nbColorVerts = 0;

  for (pnuint i = 0; i < _igameScene->GetTopLevelNodeCount(); ++i)
	parseNodeHeader(_igameScene->GetTopLevelNode(i));

  _header.nbMeshes = (pnuint)_mapMeshes.size();

  //////////////////////////////////////////////////////////////////////////

  PNMainWin::WriteLine("nb bones: %i", _header.nbSupportedBones);

  PNMainWin::WriteLine("nb Verts: %i", _header.nbVerts);
  PNMainWin::WriteLine("nb Normals: %i", _nbNormals);
  PNMainWin::WriteLine("nb TexCoords: %i", _nbTexCoords);
  PNMainWin::WriteLine("nb ColorVerts: %i", _nbColorVerts);
  PNMainWin::WriteLine("nb Meshes: %i", _header.nbMeshes);

  //////////////////////////////////////////////////////////////////////////

  return TRUE;
}
