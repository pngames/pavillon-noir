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
#include "PN3DSkeletonObject.hpp"

#include "PN3DSkeletonAnimation.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PN3DSkeletonAnimation::PN3DSkeletonAnimation(PN3DAnimation* anim, PN3DSkeletonObject* object)
{
  _object = object;

  this->looping = false;

  this->step = (pnuint)-1;

  this->weight = 1.0f;
  this->speed = 1.0f;

  this->anim = anim;

  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_BOOLEAN, &looping, "looping", "looping"));
  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL, &weight, "weight", "weight"));
  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL, &speed, "speed", "speed"));
}

PN3DSkeletonAnimation::~PN3DSkeletonAnimation()
{
  for (ParametersVector::iterator it = _params.begin(); it != _params.end(); ++it)
	delete *it;
}

PN3DSkeletonObject*
PN3DSkeletonAnimation::getParent() const
{
  return _object;
}

//////////////////////////////////////////////////////////////////////////

pnbool
PN3DSkeletonAnimation::update(pnuint deltaTime)
{
  this->step += (pnuint)(this->speed * deltaTime);

  if (this->anim->getTotalTime() < this->step)
  {
	if (this->looping)
	{
	  this->step -= this->anim->getTotalTime();

	  PNEventManager::getInstance()->addEvent(PN_EVENT_OA_LOOPED, _object,
		new PNObjectAnimationEventData(playId, looping, step, speed, weight));
	}
	else
	{
	  this->step = (pnuint)-1;

	  PNEventManager::getInstance()->addEvent(PN_EVENT_OA_ENDED, _object,
		new PNObjectAnimationEventData(playId, looping, step, speed, weight));

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
  looping = XMLUtils::xmlGetProp(root, PNO_ANIM_XMLPROP_LOOP, looping);
  step = XMLUtils::xmlGetProp(root, PNO_ANIM_XMLPROP_STEP, step);
  speed = XMLUtils::xmlGetProp(root, PNO_ANIM_XMLPROP_SPEED, speed);
  weight = XMLUtils::xmlGetProp(root, PNO_ANIM_XMLPROP_WEIGHT, weight);

  return PNEC_SUCCESS;
}

/// Save 3DObject into XML file
pnint
PN3DSkeletonAnimation::serializeInXML(xmlNode* root, pnbool isroot)
{
  XMLUtils::xmlNewProp(root, PNO_ANIM_XMLPROP_LOOP, looping);
  XMLUtils::xmlNewProp(root, PNO_ANIM_XMLPROP_STEP, step);
  XMLUtils::xmlNewProp(root, PNO_ANIM_XMLPROP_SPEED, speed);
  XMLUtils::xmlNewProp(root, PNO_ANIM_XMLPROP_WEIGHT, weight);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
// ConfigurableObject stuffs

void
PN3DSkeletonAnimation::update(PNConfigurableParameter* p)
{ 
}

pnint
PN3DSkeletonAnimation::getNbParameters()
{
  return (pnint)_params.size();
}

PNConfigurableParameter*
PN3DSkeletonAnimation::getParameter(pnint idx)
{
  return _params[idx];
}

const std::string&
PN3DSkeletonAnimation::getName()
{
  return *anim->getFile();
}

//////////////////////////////////////////////////////////////////////////
};
