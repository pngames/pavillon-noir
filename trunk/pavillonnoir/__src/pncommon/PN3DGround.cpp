/*
 * PN3DGround.cpp
 * 
 * Description :
 * PN3DGround definition
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
#include <list>
using namespace std;

/////////////////////////////////////////////

#include "pndefs.h"
#include "pnmath.h"
#include "pnrender.h"
#include "pnimport.h"

/////////////////////////////////////////////

#include "PN3DCamera.hpp"
#include "PN3DGround.hpp"
#include "PNException.hpp"
#include "PNFace.hpp"

#include "PN3DModel.hpp"

namespace fs = boost::filesystem;
using namespace PN;

/////////////////////////////////////////////

namespace PN {

/////////////////////////////////////////////

static PN3DGround * _instance = NULL;

/////////////////////////////////////////////

PN3DGround::PN3DGround()
{
  _nbFace = 0;
  _nbVertex = 0;
  _renderer = NULL;

  return ;
}

PN3DGround::PN3DGround(const std::string& path)
{
  unserializeFromPath(path);
}

PN3DGround::~PN3DGround()
{
}

PN3DGround*
PN3DGround::getInstance()
{
  if (_instance == NULL)
	_instance = new PN3DGround(); 

  return (_instance);
}

//////////////////////////////////////////////////////////////////////////

/*
* \brief Call when a game is loaded.
*/
pnint
PN3DGround::unserializeFromPath(const std::string& path)
{
  PN3DObject ground;

  if (ground.unserializeFromPath(path) != PNEC_SUCCESS)
	return (PNEC_ERROR);

  if (!_convertIntoGroundRepresentation(ground))
  {
	cerr << "failure while converting model into a ground representation.\n";
	return (PNEC_ERROR);
  }

  return (PNEC_SUCCESS);
}

bool
PN3DGround::_convertIntoGroundRepresentation (PN3DObject & groundModel)
{
  pnpoint3f *		vertices;
  pnpoint3f *		normals;
  pncolor_t *		colors;
  pnpoint2f *		texcoords;
  PNPoint3f			points[3];
  unsigned int	i;

  _nbFace = groundModel.getNbFacesComputed();
  _nbVertex = groundModel.getNbVertexComputed();

  vertices = new pnpoint3f[_nbVertex];
  normals = new pnpoint3f[_nbVertex];
  colors = new pncolor_t[_nbVertex];
  texcoords = new pnpoint2f[_nbVertex];
  _faces = new PNFace[_nbFace]();

  groundModel.computeVertex((pnfloat *) vertices);
  groundModel.computeNormales((pnfloat *) normals);
  groundModel.computeColors((pnfloat *) colors);
  groundModel.computeTextCoord((pnfloat *) texcoords);
  groundModel.computeFaces(_faces);

  _triangles = new PNTriangle[_nbFace]();

  _nbTriangle = 0;
  for (i = 0; i < _nbFace; i++)
  {
	points[0].x = vertices[_faces[i].v0][0];
	points[0].y = vertices[_faces[i].v0][1];
	points[0].z = vertices[_faces[i].v0][2];

	points[1].x = vertices[_faces[i].v1][0];
	points[1].y = vertices[_faces[i].v1][1];
	points[1].z = vertices[_faces[i].v1][2];

	points[2].x = vertices[_faces[i].v2][0];
	points[2].y = vertices[_faces[i].v2][1];
	points[2].z = vertices[_faces[i].v2][2];

	if (!PNTriangle::isFlat(points[0], points[1], points[2]))
	  _triangles[_nbTriangle++].setPoints(points[0], points[1], points[2]);
  }

  PNNormal3f		up(0, 1, 0);

  _worldCollision.loadWorld(_triangles, _nbTriangle);
  _worldCollision.sortByNormals(up, false);

  _renderer = PNRendererInterface::getInstance()->newObj((pnfloat *) vertices, /*(pnfloat *) normals*/ NULL, (pnfloat *) colors, (pnfloat *) texcoords, _nbVertex, NULL, 0);

  return (_renderer != false);
}

void
PN3DGround::render(PN3DCamera & camera)
{
  if (_renderer == NULL)
	return ;

  _renderer->addFaces(_faces, _nbFace);
  _renderer->renderAllFaces();
}


//////////////////////////////////////////////////////////////////////////

void
PN3DGround::setConfig()
{
}

bool
PN3DGround::collisionProcess(const PNBoundingSphere & bSphere, const PNVector3f & translation, PNVector3f & trResult)
{
  PNPoint3f				pos;
  PNPoint3f				radius;
  PNVector3f			posFinal;
  bool					collisionOccurs;

  bSphere.getRadius(radius);
  bSphere.getPosition(pos);
  _worldCollision.setAccuracy(PNMIN(ABS(radius.z), PNMIN(ABS(radius.x), ABS(radius.y))) - 1.0f);
  collisionOccurs = _worldCollision.translateSphere(bSphere, translation, posFinal);		
  trResult.setFromSegment(pos, posFinal);

  return collisionOccurs;
}

void
PN3DGround::handleStaticCollision(PN3DObject & object, pnfloat rX, pnfloat rY, pnfloat rZ)
{
  PNPoint3f				posObject = object.getCoord();
  PNPoint3f				radius(rX, rY, rZ);
  PNVector3f			translation = object.getUpdateTranslation();
  PNVector3f			trResult;
  PNBoundingSphere		camSphere(radius, posObject);

  translation.y -= 4;
  PN3DGround::getInstance()->collisionProcess(camSphere, translation, trResult);		
  object.setUpdateTranslation(trResult);
  object.setCoord(posObject.x + trResult.x, posObject.y + trResult.y, posObject.z + trResult.z);
}

//////////////////////////////////////////////////////////////////////////

void
PN3DGround::partialRender()
{
}


void
PN3DGround::totalRender()
{
}

void
PN3DGround::find3DObjects(PN3DCamera& camera)
{
}

//////////////////////////////////////////////////////////////////////////

} /* END of namespace PN */

//////////////////////////////////////////////////////////////////////////

