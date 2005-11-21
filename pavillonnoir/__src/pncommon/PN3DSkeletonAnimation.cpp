/*
* PN3DSkeletonAnimation.cpp
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

#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnevent.h"

#include "pno_format.h"

#include "PN3DAnimation.hpp"

#include "PN3DSkeletonAnimation.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PN3DSkeletonAnimation::PN3DSkeletonAnimation(PN3DAnimation* anim, pnint id)
{
  this->id = id;

  this->weight = 1.0f;
  this->speed = 1.0f;

  this->anim = anim;
}

PN3DSkeletonAnimation::~PN3DSkeletonAnimation()
{
  
}

pnbool
PN3DSkeletonAnimation::update(pnuint deltaTime)
{
  this->step += (pnuint)(this->speed * deltaTime);

  if (this->anim->getTotalTime() < this->step)
  {
	if (this->looping)
	{
	  this->step -= this->anim->getTotalTime();
	  //TODO: Throw loop event
	}
	else
	{
	  this->step = (pnuint)-1;
	  //TODO: Throw stop event

	  return false;
	}
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PN3DSkeletonAnimation::getRootNodeName() const
{
  return PNOA_XMLNODE_ROOT;
}

/// Parse XML root node
pnint
PN3DSkeletonAnimation::unserializeFromXML(xmlNode* root)
{
  for (root = root->children ; root != NULL; root = root->next)
	;///TODO: parse

  return PNEC_SUCCESS;
}

/// Save 3DObject into XML file
pnint
PN3DSkeletonAnimation::serializeInXML(xmlNode* node, pnbool isroot)
{
  ///TODO: write

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
