/*
 * PN3DGround.hpp
 * 
 * Description :
 * PN3DGround declaration
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

#ifndef _PN3DGROUND_HPP_
# define _PN3DGROUND_HPP_

#include <list>
#include <boost/filesystem/path.hpp>

#include "PN3DObject.hpp"

#include "PNWorldCollision.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DCamera;
class PNTriangle;
class PNFace;
class PNRendererObject;
class PNBoundingSphere;

typedef 	 std::list<PN3DObject *> LIST_3DOBJ;

class PNAPI				PN3DGround : public PN3DObject
{
private:
  PN3DGround();
  PN3DGround(const boost::filesystem::path& file);
  ~PN3DGround();

public:
  static PN3DGround*	getInstance();	

public:
  pnint					unserializeFromFile(const boost::filesystem::path& file);

public:
  virtual bool			collisionProcess(const PNBoundingSphere& bSphere, const PNVector3f& translation, PNVector3f& trResult);
  virtual void			handleStaticCollision(PN3DObject& object, pnfloat rX, pnfloat rY, pnfloat rZ);

public:
  virtual void			setConfig();

public:
  virtual void			partialRender(void);
  virtual void			totalRender(void);
  virtual void			find3DObjects(PN3DCamera& camera);
  virtual void			render(PN3DCamera& camera);

private:
  bool					_convertIntoGroundRepresentation(PN3DObject& groundModel);
  void					_dump();

private:
  pnuint				_nbFace;
  pnuint				_nbVertex;
  PNFace*				_faces;
  PNRendererObject*		_renderer;
  PNTriangle*			_triangles;
  pnuint				_nbTriangle;

  PNWorldCollision		_worldCollision;
};

//////////////////////////////////////////////////////////////////////////
}; /* END namespace PN */

#endif /*_PN3DGROUND_HPP_*/
