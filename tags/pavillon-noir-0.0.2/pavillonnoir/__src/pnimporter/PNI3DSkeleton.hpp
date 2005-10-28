/*
 * PNI3DSkeleton.hpp
 * 
 * Description :
 * PNI3DSkeleton declaration
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

#ifndef _PNI3DSKELETON_HPP_
# define _PNI3DSKELETON_HPP_

#include <vector>

#include "PN3DSkeleton.hpp"

#include "PNIBone.hpp"

#include "pns_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNRendererObject;

class								PNI3DSkeleton : public PN3DSkeleton
{
private:
  typedef std::vector<PNIBone>		BoneList;
  BoneList							_bones;

  boost::filesystem::path			_path;

  pnsHeader_t						_header;
  
  //////////////////////////////////////////////////////////////////////////
  
  PNRendererObject*					_robject;
  pnpoint3f*						_vertBuffer;
  pnpoint2ui*						_idBuffer;
public:
  PNI3DSkeleton();
  ~PNI3DSkeleton();

  //////////////////////////////////////////////////////////////////////////
  // PN3DSkeleton
  //////////////////////////////////////////////////////////////////////////

  boost::filesystem::path*	getFile();

  const PNMatrixTR4f&				getMatrix(pnuint id) const;

  //////////////////////////////////////////////////////////////////////////
  
  void								render();
  pnbool							update(pnuint time, PN3DAnimation* anim);
  pnbool							update(pndouble rtime, PN3DAnimation* anim);

  //////////////////////////////////////////////////////////////////////////
  // MAIN
  //////////////////////////////////////////////////////////////////////////
  
  pnint 							unserialize(const boost::filesystem::path& file);
  pnint								unserialize(std::istream& i);

  //////////////////////////////////////////////////////////////////////////
  
  int								parseHeader(std::istream& istm);
  int								parseBody(std::istream& istm);
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNI3DSKELETON_HPP_*/