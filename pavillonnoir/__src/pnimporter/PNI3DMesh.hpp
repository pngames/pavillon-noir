/*
 * PNI3DMesh.hpp
 * 
 * Description :
 * PNI3DMesh declaration
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

#ifndef _PNI3DMESH_HPP_
# define _PNI3DMESH_HPP_

#include <vector>
#include <stdio.h>

#include "PNObject.hpp"
#include "IPNSerializable.hpp"

#include "pnm_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNI3DModel;
class PN3DMaterial;
class PN3DSkeleton;
class PNRendererObject;
class PNFace;

class				PNI3DMesh : public PNObject, public IPNSerializable
{
  friend class		PNIVertex;
private:
  PNI3DModel&		_parent;

  pnmMesh_t			_header;

  //////////////////////////////////////////////////////////////////////////
  
  PNRendererObject*	_robject;

  pnpoint3f_t*		_vertBuffer;
  pnpoint3f_t*		_normBuffer;
  pnpoint2f_t*		_texCoordBuffer;
  pncolor_t*		_colorBuffer;

  pnpoint3ui*		_idBuffer;
public:
  PNI3DMesh(PNI3DModel& parent);
  ~PNI3DMesh();

  void				dispose();

  //////////////////////////////////////////////////////////////////////////

  void				render(std::vector<PN3DMaterial*>& mat);
  void				render();

  pnuint			getNbVerts() const;
  pnuint			getNbFaces() const;

  //////////////////////////////////////////////////////////////////////////
  
  pnuint			computeVertex(pnfloat* buffer);
  pnuint			computeNormales(pnfloat* buffer);
  pnuint			computeTextCoord(pnfloat* buffer);
  pnuint			computeColors(pnfloat* buffer);

  pnuint			computeFaces(std::vector<PN3DMaterial*>& mat, PNFace* faces, pnuint step);

  //////////////////////////////////////////////////////////////////////////
 
  pnint				unserializeFromStream(std::istream& i);

  //////////////////////////////////////////////////////////////////////////
 
private:
  pnint				_parseVertices();
  pnint				_parseFaces();
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNI3DMESH_HPP_*/
