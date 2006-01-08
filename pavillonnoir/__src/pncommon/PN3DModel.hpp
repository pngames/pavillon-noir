/*
 * PN3DModel.hpp
 * 
 * Description :
 * PN3DModel declaration
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

#ifndef _PN3DMODEL_HPP_
# define _PN3DMODEL_HPP_

#include <vector>

#include "PNObject.hpp"
#include "IPNImportedObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DMaterial;
class PN3DSkeleton;
class PNPoint3f;
class PNFace;

/// Model
class /*PNAPI*/				PN3DModel : public PNObject, public IPNImportedObject
{
public:
  /// Destructor for PN3DModel.
  virtual ~PN3DModel() {}

  //////////////////////////////////////////////////////////////////////////
  
  /// Render model according to materials list and skeleton
  virtual void				render(std::vector<PN3DMaterial*>* mat, PN3DSkeleton* sk = NULL)=0;

  //////////////////////////////////////////////////////////////////////////
  
  /// Return number of bone this model support
  virtual pnuint			getNbSupportedBones() const=0;
  /// Return number of materials this model support
  virtual pnuint			getNbSupportedMaterials() const=0;

  /// Return number of vertices contained in this model
  virtual pnuint			getNbVerts() const=0;
  /// Return number of faces contained in this model
  virtual pnuint			getNbFaces() const=0;

  //////////////////////////////////////////////////////////////////////////
  
  /// Retrieve number of vertex owned by 3d model
  virtual pnuint			getNbVertexComputed()=0;

  /// Fill buffer from step with vertices owned by 3d model
  virtual pnuint			computeVertex(pnfloat* buffer, pnuint step = 0)=0;
  /// Fill buffer from step with normales owned by 3d model
  virtual pnuint			computeNormales(pnfloat* buffer, pnuint step = 0)=0;
  /// Fill buffer from step with textures coordinates owned by 3d model
  virtual pnuint			computeTextCoord(pnfloat* buffer, pnuint step = 0)=0;
  /// Fill buffer from step with colors owned by 3d model
  virtual pnuint			computeColors(pnfloat* buffer, pnuint step = 0)=0;

  /// Retrieve number of face owned by 3d model
  virtual pnuint			getNbFacesComputed()=0;

  /// Fill buffer from step with faces owned by 3d model
  virtual pnuint			computeFaces(std::vector<PN3DMaterial*>& mat, PNFace* faces, pnuint step = 0)=0;

  //////////////////////////////////////////////////////////////////////////
  
  /// Get minimum x y z coordinate
  virtual const PNPoint3f&	getMin() const=0;
  /// Get maximum x y z coordinate
  virtual const PNPoint3f&	getMax() const=0;
  /// Get center scene coordinate used for rotations
  virtual const	PNPoint3f&	getCenter() const=0;
  /// Get bounding sphere radius
  virtual pnfloat			getRadius() const=0;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PN3DMODEL_HPP_*/
