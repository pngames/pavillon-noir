/*
 * PNModelExporter.hpp
 * 
 * Description :
 * PNModelExporter declaration
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

#ifndef _PNMODELEXPORTER_HPP_
# define _PNMODELEXPORTER_HPP_

#ifdef _DEBUG
# define PNMODELEXPORTER_CLASS_ID	Class_ID(0x4b476fba, 0x3a2821be)
# define PNM_LONGDESC				"Model exporter for Pavillon Noir 3D models (debug)"
# define PNM_SHORTDESC				"Pavillon Noir Model export (debug)"
#else
# define PNMODELEXPORTER_CLASS_ID	Class_ID(0x2b094ba8, 0x6fc673ab)
# define PNM_LONGDESC				"Model exporter for Pavillon Noir 3D models"
# define PNM_SHORTDESC				"Pavillon Noir Model export"
#endif

#include "PNExporter.hpp"

#include "pnm_format.h"

//////////////////////////////////////////////////////////////////////////

typedef std::map<int, int>  MAP_INT;

typedef struct		vertex_s
{
  MAP_INT			normal;
  MAP_INT			color;
}					vertex_t;

typedef struct		pnmVertex2_s
{
  pnmVertex_t		vertex;
  pnmBoneID_t*		bones;
}					pnmVertex2_t;

typedef struct		texCoord_s
{
  int				id;

  PN::pnpoint2f		coord;
}					texCoord_t;

typedef struct		meshVertex_s
{
  typedef std::map<int, texCoord_t>	MAPTEXCOORD;
  MAPTEXCOORD		texCoord;
}					meshVertex_t;

typedef struct		face_s
{
  int				vertStep;
  int				texStep;
  FaceEx			face;
}					face_t;

typedef struct		mesh_s
{
  typedef std::map<int, meshVertex_t>	MAP_MESHVERTEX;
  MAP_MESHVERTEX	verts_texCoords;

  typedef std::list<face_t>				LIST_FACE;
  LIST_FACE			faces;
}					mesh_t;

//////////////////////////////////////////////////////////////////////////

class			PNModelExporter : public PNExporter
{
protected:
  PN::pnuint	_nbNormals;
  PN::pnuint	_nbTexCoords;
  PN::pnuint	_nbColorVerts;
protected:
  //////////////////////////////////////////////////////////////////////////

  typedef std::map<IGameMaterial*, int>	MAP_MATERIAL;
  MAP_MATERIAL	_mapMaterialsId;
  //PN::pnuint	_nbMaterials;

  //////////////////////////////////////////////////////////////////////////

  typedef std::list<IGameNode*>		LIST_MESH;
  LIST_MESH		_listMeshes;

  //////////////////////////////////////////////////////////////////////////
  
  MAP_INT		_mapBonesId;
  //PN::pnuint	_nbBones;

  //////////////////////////////////////////////////////////////////////////
  
  typedef std::map<int, vertex_t>	MAP_VERTEX;
  MAP_VERTEX	_mapVertex;

  typedef std::map<int, mesh_t>		MAP_MESH;
  MAP_MESH		_mapMeshes;

  //////////////////////////////////////////////////////////////////////////
public:
  static HWND hParams;

  void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

  //Constructor/Destructor
  PNModelExporter();
  ~PNModelExporter();

  //////////////////////////////////////////////////////////////////////////
public:
  int			parseNodeHeader(IGameNode* node);
  virtual int	initExport();

  virtual int	releaseExport();

  virtual int	exportHeader();

  int			exportFaces(mesh_t& mesh, pnmMesh_t& meshToExport);
  int			exportMeshs();
  virtual int	exportBody();

  virtual int	configure();
protected:
  pnmHeader_t	_header;
};

class PNModelExporterDesc : public ClassDesc2
{
  HINSTANCE		_hInstance;
public:
  void			SetInstance (HINSTANCE hInstance);
public:
  int 			IsPublic();
  void *		Create(BOOL loading = FALSE);
  const TCHAR *	ClassName();
  SClass_ID		SuperClassID();
  Class_ID		ClassID();
  // The Skin modifier checks the category to decide whether the modifier is a Skin Gizmo.  This 
  // must not be changed
  const TCHAR* 	Category();

  const TCHAR*	InternalName();	// returns fixed parsable name (scripter-visible name)
  HINSTANCE		HInstance(); // returns owning module handle
};

#endif /*_PNMODELEXPORTER_HPP_*/
