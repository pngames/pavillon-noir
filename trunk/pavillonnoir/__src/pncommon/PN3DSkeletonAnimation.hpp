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
#include <vector>

#include "IPNXMLSerializable.hpp"
#include "PNObject.hpp"

#include "pnproperties.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DAnimation;
class PN3DSkeletonObject;

//////////////////////////////////////////////////////////////////////////

class PNAPI							PN3DSkeletonAnimation : public PNObject, public PNConfigurableObject
{
  PN3DSkeletonObject*				_object;
public:
  PN3DAnimation*					anim;
public:
  PN3DSkeletonAnimation(PN3DAnimation* anim, PN3DSkeletonObject* object);
  ~PN3DSkeletonAnimation();

  pnbool							update(pnuint current);
public:
  pnint								playId;
  pnint								next;

  pnbool							looping;

  pnuint							step;

  pnfloat							speed;
  pnfloat							weight;

  //////////////////////////////////////////////////////////////////////////
  
  void								start();
  void								stop();
  void								loop();

  //////////////////////////////////////////////////////////////////////////

  PN3DSkeletonObject*				getParent() const;

protected:
  const std::string&				getRootNodeName() const;

public:
  /// Parse XML root node
  pnint								unserializeFromXML(xmlNode* node);

  /// Save 3DObject into XML file
  pnint								serializeInXML(xmlNode* node, pnbool isroot = false);

  //////////////////////////////////////////////////////////////////////////

  // ConfigurableObject stuffs

protected:
  typedef std::vector<PNConfigurableParameter*> ParametersVector;
  ParametersVector					_params;

public:
  void								update(PNConfigurableParameter* p);
  pnint								getNbParameters();
  virtual PNConfigurableParameter*	getParameter(pnint idx);

  virtual const std::string&		getName();
};

//////////////////////////////////////////////////////////////////////////

/// List of animations associated in play
typedef std::set<PN3DSkeletonAnimation*>	AnimationSet;

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PN3DSKELETONANIMATION_HPP_*/

