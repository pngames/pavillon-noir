/*
 * m_exportBody.cpp
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

int					PNModelExporter::exportFaces(mesh_t& mesh, pnmMesh_t& meshToExport)
{
  //////////////////////////////////////////////////////////////////////////
  // FACES
  mesh_t::LIST_FACE&	lst = mesh.faces;

  pnpoint3ui*		tabFaces = new pnpoint3ui[meshToExport.nbFaces];

  int i = 0;
  for (mesh_t::LIST_FACE::iterator it = lst.begin(); it != lst.end(); ++it, ++i)
  {
	//PNMainWin::WriteLine("  face %i", i);

	face_t&	  face = *it;

	int tcoord0 = -1;
	int tcoord1 = -1;
	int tcoord2 = -1;

	if (meshToExport.materialIdx >= 0)
	{
	  tcoord0 = face.texStep + face.face.texCoord[0];
	  tcoord1 = face.texStep + face.face.texCoord[1];
	  tcoord2 = face.texStep + face.face.texCoord[2];
	}

	tabFaces[i][0] = mesh.verts_texCoords[face.vertStep + face.face.vert[0]].texCoord[tcoord0].id;
	tabFaces[i][1] = mesh.verts_texCoords[face.vertStep + face.face.vert[1]].texCoord[tcoord1].id;
	tabFaces[i][2] = mesh.verts_texCoords[face.vertStep + face.face.vert[2]].texCoord[tcoord2].id;

	//PNMainWin::WriteLine("    idx: %i %i %i", tabFaces[i][0], tabFaces[i][1], tabFaces[i][2]);
  }

  _file->Write(tabFaces, sizeof(*tabFaces) * meshToExport.nbFaces);

  delete[] tabFaces;

  return TRUE;
}

int					PNModelExporter::exportMeshs()
{
  PNMainWin::WriteLine("- Export Meshes");

  pnmMesh_t			meshToExport;
  pnmMeshVertex_t	vertToExport;

  for (MAP_MESH::iterator it = _mapMeshes.begin(); it != _mapMeshes.end(); ++it)
  {
	meshToExport.colored = true;
	meshToExport.materialIdx = it->first;

	PNMainWin::WriteLine(" Export Meshe %i", meshToExport.materialIdx);

	mesh_t&		  mesh = it->second;

	//////////////////////////////////////////////////////////////////////////
	// VERTS
	//////////////////////////////////////////////////////////////////////////

	std::vector<pnmMeshVertex_t>  vectorVert;

	meshToExport.nbVerts = 0;
	for (mesh_t::MAP_MESHVERTEX::iterator it = mesh.verts_texCoords.begin(); it != mesh.verts_texCoords.end() ; ++it)
	{
	  //PNMainWin::WriteLine("  vertex %i", meshToExport.nbVerts);

	  int			vertId = it->first;
	  meshVertex_t&	vert = it->second;

	  texCoord_t  tmp;
	  texCoord_t  tmp2;

	  tmp.coord[0] = tmp2.coord[0] = 0;
	  tmp.coord[1] = tmp2.coord[1] = 0;

	  typedef std::map<std::pair<float, float>, MAP_INT>  MAP_FILER;
	  MAP_FILER			filter;

	  for (meshVertex_t::MAPTEXCOORD::iterator it2 = vert.texCoord.begin(); it2 != vert.texCoord.end(); ++it2)
	  {
		texCoord_t&  coord = it2->second;

		filter[std::pair<float, float>(coord.coord[0], coord.coord[1])][it2->first] = it2->first;
	  }

	  for (MAP_FILER::iterator it2 = filter.begin(); it2 != filter.end(); ++it2)
	  {
		MAP_INT&	tlist = it2->second;

		for (MAP_INT::iterator it3 = tlist.begin(); it3 != tlist.end(); ++it3)
		{
		  vert.texCoord[it3->first].id = meshToExport.nbVerts;
		  //PNMainWin::WriteLine("    same texCoord %i", it3->first);
		}

		texCoord_t&  coord = vert.texCoord[tlist.begin()->first];

		vertToExport.vertexIdx = vertId;
		vertToExport.texCoord.x = coord.coord[0];
		vertToExport.texCoord.y = coord.coord[1];

		vectorVert.push_back(vertToExport);
		++meshToExport.nbVerts;

		//////////////////////////////////////////////////////////////////////////

		//PNMainWin::WriteLine("    index %i -> %i", meshToExport.nbVerts, vertToExport.vertexIdx);
		//PNMainWin::WriteLine("    texCoord %f %f", vertToExport.texCoord.x, vertToExport.texCoord.y);
	  }
	}

	//////////////////////////////////////////////////////////////////////////
	// MESH HEADER
	//////////////////////////////////////////////////////////////////////////

	meshToExport.nbVerts = (pnuint)vectorVert.size();
	meshToExport.nbFaces = (pnuint)mesh.faces.size();

	//////////////////////////////////////////////////////////////////////////

	PNMainWin::WriteLine("  nb Verts %i", meshToExport.nbVerts);
	PNMainWin::WriteLine("  nb Faces %i", meshToExport.nbFaces);
	PNMainWin::WriteLine("  materialsID %i", meshToExport.materialIdx);

	_file->Write(&meshToExport, sizeof(pnmMesh_t));

	//////////////////////////////////////////////////////////////////////////
	// EXPORT VERTS
	//////////////////////////////////////////////////////////////////////////

	_file->Write(&vectorVert[0], sizeof(pnmMeshVertex_t) * meshToExport.nbVerts);

	//////////////////////////////////////////////////////////////////////////
	// EXPORT FACES
	//////////////////////////////////////////////////////////////////////////

	exportFaces(mesh, meshToExport);
  }

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int					PNModelExporter::exportBody()
{
  PNMainWin::WriteLine("PNModelExporter::exportBody()");

  // Vertexes
  pnmVertex2_t*		tabVerts = new pnmVertex2_t[_header.nbVerts];
  pnmVertex2_t*		vtmp = tabVerts;

  // Normals
  pnpoint3f*		tabNormals = new pnpoint3f[_nbNormals];
  pnpoint3f*		ntmp = tabNormals;

  // ColorVerts
  pnpoint4f*		tabColorVerts = new pnpoint4f[_nbColorVerts];
  pnpoint4f*		ctmp = tabColorVerts;

  //////////////////////////////////////////////////////////////////////////

  for (LIST_MESH::iterator it = _listMeshes.begin(); it != _listMeshes.end(); ++it)
  {
	IGameNode*		node = *it;
	IGameObject*	obj = node->GetIGameObject();
	IGameMesh*		mesh = (IGameMesh *)obj;

	mesh->SetCreateOptimizedNormalList();
	mesh->InitializeData();

	//////////////////////////////////////////////////////////////////////////
	// VERTEXES

	for (pnuint i = 0; i < mesh->GetNumberOfVerts(); ++i, ++vtmp)
	{
	  pnmVertex2_t&	vertex = *vtmp;

	  memset(&vertex, 0, sizeof(pnmVertex2_t));

	  //////////////////////////////////////////////////////////////////////////

	  memcpy(vertex.vertex.coord, mesh->GetVertex(i), sizeof(pnpoint3f));

	  PNMainWin::WriteLine("   COORDS: %f %f %f", mesh->GetVertex(i).x, mesh->GetVertex(i).y, mesh->GetVertex(i).z);

	  //////////////////////////////////////////////////////////////////////////
	  // BONES

	  if (obj->GetIGameSkin() != NULL)
	  {
		IGameSkin*	igskin = obj->GetIGameSkin();

		vertex.vertex.nbBones = igskin->GetNumberOfBones(i);
		vertex.bones = new pnmBoneID_t[igskin->GetNumberOfBones(i)];
		for (int j = 0; j < igskin->GetNumberOfBones(i); ++j)
		{
		  vertex.bones[j].boneIdx = _mapBonesId[igskin->GetIGameBone(i, j)->GetNodeID()];
		  vertex.bones[j].weight = igskin->GetWeight(i, j);
		}
	  }
	}

	//////////////////////////////////////////////////////////////////////////
	// NORMALS

	for (pnuint i = 0; i < mesh->GetNumberOfNormals(); ++i, ++ntmp)
	{
	  memcpy(ntmp, mesh->GetNormal(i), sizeof(pnpoint3f));
	}

	//////////////////////////////////////////////////////////////////////////
	// CVERTS

	for (pnuint i = 0; i < mesh->GetNumberOfColorVerts(); ++i, ++ctmp)
	{
	  memcpy(ctmp, mesh->GetColorVertex(i), sizeof(pnpoint3f));
	  (*ctmp)[3] = 1.0f;
	}

	//////////////////////////////////////////////////////////////////////////

	node->ReleaseIGameObject();
  }

  //////////////////////////////////////////////////////////////////////////
  PNMainWin::WriteLine("- Export Vertexes %i", _header.nbVerts);

  //vtmp = tabVerts;
  for (int i = 0; i < _header.nbVerts; ++i)
  {
	pnmVertex2_t&	vertex = tabVerts[i];

	PNMainWin::WriteLine("  vertex %i", i);

	//////////////////////////////////////////////////////////////////////////
	// Compute
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// NORMALE
	MAP_INT&	nmap = _mapVertex[i].normal;

	for (MAP_INT::iterator it = nmap.begin(); it != nmap.end(); ++it)
	{
	  vertex.vertex.normale.x += tabNormals[it->second][0];
	  vertex.vertex.normale.y += tabNormals[it->second][1];
	  vertex.vertex.normale.z += tabNormals[it->second][2];
	}

	Point3	ptmp(vertex.vertex.normale.x, vertex.vertex.normale.y, vertex.vertex.normale.z);
	ptmp.Normalize();

	vertex.vertex.normale.x = ptmp.x;
	vertex.vertex.normale.y = ptmp.y;
	vertex.vertex.normale.z = ptmp.z;

	//////////////////////////////////////////////////////////////////////////
	// COLOR
	MAP_INT&	cmap = _mapVertex[i].color;

	if (cmap.size() > 0)
	{
	  for (MAP_INT::iterator it = cmap.begin(); it != cmap.end(); ++it)
	  {
		vertex.vertex.color.r += tabColorVerts[it->second][0];
		vertex.vertex.color.g += tabColorVerts[it->second][1];
		vertex.vertex.color.b += tabColorVerts[it->second][2];
		vertex.vertex.color.a += tabColorVerts[it->second][3];
	  }

	  vertex.vertex.color.r /= cmap.size();
	  vertex.vertex.color.g /= cmap.size();
	  vertex.vertex.color.b /= cmap.size();
	  vertex.vertex.color.a /= cmap.size();
	}
	else
	  vertex.vertex.color = _defaultColor;

	//////////////////////////////////////////////////////////////////////////
	// EXPORT
	//////////////////////////////////////////////////////////////////////////

	PNMainWin::WriteLine("    coords: %f %f %f", vertex.vertex.coord[0], vertex.vertex.coord[1], vertex.vertex.coord[2]);
	PNMainWin::WriteLine("    normale: %f %f %f", vertex.vertex.normale.x, vertex.vertex.normale.y, vertex.vertex.normale.z);
	PNMainWin::WriteLine("    color: %f %f %f %f", vertex.vertex.color.r, vertex.vertex.color.g, vertex.vertex.color.b, vertex.vertex.color.a);

	//_file->Write("vertex", strlen("vertex") + 1);
	_file->Write(&vertex.vertex, sizeof(pnmVertex_t));

	_file->Write(vertex.bones, sizeof(*vertex.bones) * vertex.vertex.nbBones);
	
	//////////////////////////////////////////////////////////////////////////

	if (vertex.bones != NULL)
	  delete[] vertex.bones;
  }

  exportMeshs();

  //////////////////////////////////////////////////////////////////////////
  
  delete[] tabVerts;
  delete[] tabNormals;
  delete[] tabColorVerts;

  //////////////////////////////////////////////////////////////////////////

  _listMeshes.clear();
  _mapBonesId.clear();
  _mapMaterialsId.clear();

  return TRUE;
}
