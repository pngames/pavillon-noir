/*
 * PNI3DModel.hpp
 * 
 * Description :
 * PNI3DModel declaration
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

#ifndef _PNI3DModel_HPP_
# define _PNI3DModel_HPP_

#include <stdio.h>
#include <vector>
#include <list>
#include <fstream>

#include "PN3DModel.hpp"

#include "PNVector3f.hpp"
#include "PNIVertex.hpp"
#include "PNI3DMesh.hpp"

#include "pnm_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class 				PNI3DModel : public PN3DModel
{
  friend class	PNI3DMesh;
private:
  std::istream*		_istream;

  pnmHeader_t		_header;
  pnuint			_nbFaces;

  typedef std::list<PNI3DMesh*>		LIST_3DMESH;
  LIST_3DMESH		_meshes;

  typedef std::vector<PNIVertex>	VECTOR_VERTEX;
  VECTOR_VERTEX		_vertex;
private:
  PNPoint3f			_min;
  PNPoint3f			_max;
  PNPoint3f			_center;
public:
  PNI3DModel();
  ~PNI3DModel();
  
  void				dispose();

  //////////////////////////////////////////////////////////////////////////
  // PN3DModel
  //////////////////////////////////////////////////////////////////////////

  void				render(std::vector<PN3DMaterial*>& mat, PN3DSkeleton* sk = NULL);
  void				render(PN3DSkeleton* sk = NULL);

  //////////////////////////////////////////////////////////////////////////
  
  pnuint			getNbSupportedBones() const;
  pnuint			getNbSupportedMaterials() const;

  pnuint			getNbVerts() const;
  pnuint			getNbFaces() const;

  //////////////////////////////////////////////////////////////////////////

  const PNPoint3f&	getMin() const;
  const PNPoint3f&	getMax() const;
  const PNPoint3f&	getCenter() const;

  //////////////////////////////////////////////////////////////////////////
  
  pnuint			getNbVertexComputed();

  pnuint			computeVertex(pnfloat* buffer, pnuint step = 0);
  pnuint			computeNormales(pnfloat* buffer, pnuint step = 0);
  pnuint			computeTextCoord(pnfloat* buffer, pnuint step = 0);
  pnuint			computeColors(pnfloat* buffer, pnuint step = 0);

  pnuint			getNbFacesComputed();

  pnuint			computeFaces(std::vector<PN3DMaterial*>& mat, PNFace* faces, pnuint step);

  //////////////////////////////////////////////////////////////////////////
  // PNObject
  //////////////////////////////////////////////////////////////////////////
  
  pnint				unserializeFromStream(std::istream& i);

  //////////////////////////////////////////////////////////////////////////
  // MAIN
  //////////////////////////////////////////////////////////////////////////
  
  pnint				parseVertexes();

  pnint				parseMeshes();

  pnint				parseHeader();
  pnint				parseBody();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNI3DModel_HPP_*/
