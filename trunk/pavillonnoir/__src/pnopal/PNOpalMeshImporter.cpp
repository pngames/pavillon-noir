/*
* PNOpalMeshImporter.cpp
* 
* Description :
* PNOpalMesh definition
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

#include "PNOpalMeshImporter.hpp"
#include "PNGameInterface.hpp"
#include "PNGameMap.hpp"

#include "pnm_format.h"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNOpalMeshImporter::PNOpalMeshImporter()
{
  
}

PNOpalMeshImporter::~PNOpalMeshImporter()
{
  
}

//////////////////////////////////////////////////////////////////////////

pnint
PNOpalMeshImporter::parseHeader()
{
  _istream->read((char*)&_header, sizeof(_header));

  if (strncmp(_header.magic, PNM_MAGIC, PNM_MAGIC_SIZE) != 0)
	return PNEC_FILETYPE_INVALID;

  std::cout << "PNOpalMesh magic : " << _header.magic << std::endl;
  std::cout << "PNOpalMesh version : " << _header.version << std::endl;
  std::cout << "PNOpalMesh SupportedBones : " << _header.nbSupportedBones << std::endl;
  std::cout << "PNOpalMesh SupportedMaterials : " << _header.nbSupportedMaterials << std::endl;
  std::cout << "PNOpalMesh nbVerts : " << _header.nbVerts << std::endl;
  std::cout << "PNOpalMesh nbMeshes : " << _header.nbMeshes << std::endl;

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNOpalMeshImporter::parseVertexes()
{
  pnfloat	mpp = PNGameInterface::getInstance()->getGameMap()->getMpp();
  _vertices.reserve(_header.nbVerts);

  static pnmVertex_t	vert;

  for (pnuint i = 0; i < _header.nbVerts; ++i)
  {
	_istream->read((char*)&vert, sizeof(vert));

	_vertices.push_back(vert.coord[0] * mpp);
	_vertices.push_back(vert.coord[1] * mpp);
	_vertices.push_back(vert.coord[2] * mpp);
  }

  return PNEC_SUCCESS;
}

pnint
PNOpalMeshImporter::parseMeshes()
{
  pnmMesh_t			header;

  for (pnuint i = 0; i < _header.nbMeshes; ++i)
  {
	_istream->read((char*)&header, sizeof(header));

	cout << "PNOpalMesh (mesh component) nbVerts=" << header.nbVerts << endl;
	cout << "PNOpalMesh (mesh component) nbFaces=" << header.nbFaces << endl;

	//////////////////////////////////////////////////////////////////////////
	// Vertices	

	pnmMeshVertex_t*  verticesBuffer = new pnmMeshVertex_t[header.nbVerts];
	_istream->read((char*)verticesBuffer, sizeof(*verticesBuffer) * header.nbVerts);

	//////////////////////////////////////////////////////////////////////////
	// Faces

	pnpoint3ui* facesBuffer = new pnpoint3ui[header.nbFaces];
	_istream->read((char*)facesBuffer, sizeof(*facesBuffer) * header.nbFaces);

	for (pnuint i = 0; i < header.nbFaces; ++i)
	{
	  _faces.push_back(verticesBuffer[facesBuffer[i][0]].vertexIdx);
	  _faces.push_back(verticesBuffer[facesBuffer[i][1]].vertexIdx);
	  _faces.push_back(verticesBuffer[facesBuffer[i][2]].vertexIdx);
	}
  }

  return PNEC_SUCCESS;
}

pnint
PNOpalMeshImporter::parseBody()
{
  parseVertexes();
  parseMeshes();

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNOpalMeshImporter::unserializeFromStream(std::istream& i)
{
  _istream = &i;

  int err = PNEC_SUCCESS;

  if ((err = parseHeader()) == 0)
	err = parseBody();

  return err; 

  return PNEC_SUCCESS;
}

pnuint
PNOpalMeshImporter::getNbVertices()
{
  return (pnuint)_vertices.size() / 3;
}

pnfloat*
PNOpalMeshImporter::getVertices()
{
  return &_vertices[0];
}

pnuint
PNOpalMeshImporter::getNbFaces()
{
  return (pnuint)_faces.size() / 3;
}

pnuint*
PNOpalMeshImporter::getFaces()
{
  return &_faces[0];
}

//////////////////////////////////////////////////////////////////////////
};