/*
 * PNIVertex.hpp
 * 
 * Description :
 * PNIVertex declaration
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

#ifndef _PNIVERTEX_HPP_
# define _PNIVERTEX_HPP_

#include <list>

#include "pnm_format.h"

#include "PNPoint3f.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNI3DMesh;
class PN3DSkeleton;

class			PNIVertex : public PNPoint3f
{
public:
  typedef std::list<pnmBoneID_t>	LIST_BONES;

  typedef std::pair<PNI3DMesh*, pnuint>	PAIR_INDEX;
  typedef std::list<PAIR_INDEX>			LIST_INDEXES;
public:
  pnpoint3f_t	normale;
  pncolor_t		color;

private:
  LIST_BONES	_bones;

  LIST_INDEXES	_indexes;
public:
  PNIVertex(pnmVertex_t& vert, pnmBoneID_t* bonesId);
  ~PNIVertex();

  void	initVert(pnmVertex_t& vert, pnmBoneID_t* bonesId);

  void	addIndex(PNI3DMesh* mesh, pnuint index);

  //////////////////////////////////////////////////////////////////////////
  
  void	transform(PN3DSkeleton* sk);
};

  //////////////////////////////////////////////////////////////////////////
}

#endif /*_PNIVERTEX_HPP_*/
