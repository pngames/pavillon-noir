/*
* PN3DSkeletonAnimation.hpp
* 
* Description :
* Interface for Animation support (play, pause, ...)
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

#ifndef _PN3DSKELETONANIMATION_HPP_
# define _PN3DSKELETONANIMATION_HPP_

#include <set>

#include "IPNXMLSerializable.hpp"
#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DAnimation;

//////////////////////////////////////////////////////////////////////////

class PNAPI				PN3DSkeletonAnimation : PNObject, IPNXMLSerializable
{
public:
  PN3DAnimation*		anim;
public:
  PN3DSkeletonAnimation(PN3DAnimation* anim);
  ~PN3DSkeletonAnimation();

  pnbool				update(pnuint current);
public:
  pnbool				looping;

  pnuint				step;

  pnfloat				speed;
  pnfloat				weight;

  //////////////////////////////////////////////////////////////////////////

protected:
  const std::string&	getRootNodeName() const;

public:
  /// Parse XML root node
  pnint					unserializeFromXML(xmlNode* node);

  /// Save 3DObject into XML file
  pnint					serializeInXML(xmlNode* node, pnbool isroot = false);
};

//////////////////////////////////////////////////////////////////////////

/// List of animations associated in play
typedef std::set<PN3DSkeletonAnimation*>	AnimationSet;

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PN3DSKELETONANIMATION_HPP_*/
