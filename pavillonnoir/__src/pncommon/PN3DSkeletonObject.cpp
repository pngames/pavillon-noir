/*
 * PN3DSkeletonObject.cpp
 * 
 * Description :
 * PN3DSkeletonObject definition
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
#include <boost/filesystem/operations.hpp>
#include <assert.h>

#include "pndefs.h"
#include "pnmath.h"
#include "pnimport.h"
#include "pnrender.h"
#include "pnevent.h"
#include "pnresources.h"

#include "PN3DSkeletonObject.hpp"
#include "PN3DModel.hpp"
#include "PN3DSkeleton.hpp"
#include "PN3DAnimation.hpp"
#include "PNPhysicalObject.hpp"

#include "pno_format.h"

namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PN3DSkeletonObject::PN3DSkeletonObject() : _skeleton(NULL)
{
  _objType = OBJTYPE_3DSKELETONOBJ;

  _defaultAnimSpeed = 1.0f;
  _defaultAnimWeight = 1.0f;

  _animTransTime = 0;
  _animTransitionStep = 1.0f;
}

PN3DSkeletonObject::~PN3DSkeletonObject()
{
  if (_skeleton != NULL)
	delete _skeleton;

  for (AnimationVector::iterator it = _anims.begin(); it != _anims.end(); ++it)
	delete *it;
}

//////////////////////////////////////////////////////////////////////////

int
PN3DSkeletonObject::_parseAnimations(xmlNode* parent)
{
  _anims.clear();

  _defaultAnimSpeed = XMLUtils::xmlGetProp(parent, PNO_ANIM_XMLPROP_SPEED, _defaultAnimSpeed);

  for (xmlNodePtr  node = parent->children; node != NULL ; node = node->next)
  {
	if (node->type != XML_ELEMENT_NODE)
	  continue;

	//////////////////////////////////////////////////////////////////////////
	
	xmlChar*	  attr = xmlGetProp(node, PNO_XMLPROP_PATH);

	PN3DAnimation*	anim = NULL;

	if (attr != NULL)
	{
	  if ((anim = (PN3DAnimation*)PNImportManager::getInstance()->import(PNRT_animation, (const char*)attr, PN_IMPORT_3DANIMATION)) == NULL)
		return PNEC_ERROR;
	}
	else
	  return PNEC_FAILED_TO_PARSE;

	PN3DSkeletonAnimation*	skanim = new PN3DSkeletonAnimation(anim, this);

	//////////////////////////////////////////////////////////////////////////

	skanim->speed = _defaultAnimSpeed;

	_anims.push_back(skanim);

	if (XMLUtils::xmlGetProp(node, PNO_XMLPROP_ENABLED, false))
	  startAnimation((pnuint)_anims.size() - 1);

	skanim->unserializeFromXML(node);
  }

  return PNEC_SUCCESS;
}

int
PN3DSkeletonObject::_parseSkeleton(xmlNode* node)
{
  xmlChar*	  attr = NULL;

  _skeleton = NULL;

  if ((attr = xmlGetProp(node, (const xmlChar *)PNO_XMLPROP_PATH)) != NULL)
  {
    _skeleton = (PN3DSkeleton*)PNImportManager::getInstance()->import(PNRT_skeleton, (const char*)attr, PN_IMPORT_3DSKELETON, true);

	if (_skeleton == NULL)
	  return PNEC_LOADING_MODEL;
  }

  return PNEC_SUCCESS;
}

pnint
PN3DSkeletonObject::_unserializeNode(xmlNode* node)
{
  if (PNO_XMLNODE_LISTANIMS == (const char*)node->name)
	_parseAnimations(node);
  else if (PNO_XMLNODE_SKELETON == (const char*)node->name)
	_parseSkeleton(node);
  else
	PN3DObject::_unserializeNode(node);

  return PNEC_SUCCESS;
}

int
PN3DSkeletonObject::unserializeFromXML(xmlNode* root)
{
  PNLOCK(this);

  _skeleton = NULL;
  _anims.clear();

  //////////////////////////////////////////////////////////////////////////

  return PN3DObject::unserializeFromXML(root);
}

//////////////////////////////////////////////////////////////////////////

pnint
PN3DSkeletonObject::_serializeContent(xmlNode* root)
{
  PN3DObject::_serializeContent(root);

  //////////////////////////////////////////////////////////////////////////

  xmlNode* node = NULL;

  if (_skeleton != NULL && _skeleton->getFile() != NULL)
  {
	node = xmlNewChild(root, NULL, BAD_CAST PNO_XMLNODE_SKELETON.c_str(), NULL);
	xmlNewProp(node, BAD_CAST PNO_XMLPROP_PATH, BAD_CAST PNResourcesManager::getInstance()->convertPath(PNRT_skeleton, *_skeleton->getFile()).c_str());
  }

  if (_anims.size() > 0)
  {
	root = xmlNewChild(root, NULL, BAD_CAST PNO_XMLNODE_LISTANIMS.c_str(), NULL);

	for (AnimationVector::iterator it = _anims.begin(); it != _anims.end(); ++it)
	  if ((*it)->anim != NULL && (*it)->anim->getFile() != NULL)
	  {
		PN3DSkeletonAnimation* skAnimation = *it;
  
		node = xmlNewChild(root, NULL, BAD_CAST PNOA_XMLNODE_ROOT.c_str(), NULL);
		xmlNewProp(node, PNO_XMLPROP_PATH, BAD_CAST PNResourcesManager::getInstance()->convertPath(PNRT_animation, *skAnimation->anim->getFile()).c_str());

		skAnimation->serializeInXML(node, true);

		if (_animsToPlay.find(skAnimation) != _animsToPlay.end())
		  XMLUtils::xmlNewProp(node, PNO_XMLPROP_ENABLED, true);
	  }
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

void
PN3DSkeletonObject::update(pnuint deltaTime)
{
  if (isUpdated())
	return ;

  //////////////////////////////////////////////////////////////////////////

  PN3DObject::update(deltaTime);

  //////////////////////////////////////////////////////////////////////////

  PNLOCK(this);

  if (_skeleton == NULL)
	return ;

  //////////////////////////////////////////////////////////////////////////
  
  if (_animTransitionStep < 1.0)
	_animTransitionStep += deltaTime / (pnfloat)_animTransTime;

  //////////////////////////////////////////////////////////////////////////

  if (_animTransitionStep < 1.0)
  {
	if (_animsToPlay.size() > 0)
	  _skeleton->update(_animTransitionStep, _animsToPlay);
	else
	  _skeleton->reinit(_animTransitionStep);
  }
  else
  {
	AnimationSet  setTmp = _animsToPlay;

	for (AnimationSet::iterator it = setTmp.begin(); it != setTmp.end(); ++it)
	{
	  PN3DSkeletonAnimation*  anim = *it;
	  if (!anim->update(deltaTime))
	  {
		_setEnabled(anim, false);
		setEnabled(anim->next, true);
	  }
	}

	//////////////////////////////////////////////////////////////////////////

	if (_animsToPlay.size() > 0)
	  _skeleton->update(_animsToPlay);
	else
	  _skeleton->reinit();
  }
}

void
PN3DSkeletonObject::render()
{
  PNLOCK(this);

  if (_skeleton != NULL && _renderMode & RENDER_SKELETON)
	_skeleton->render();

  if (_model != NULL && _renderMode & RENDER_MODEL)
  {
	if (_renderMode & RENDER_MATERIALS && _materials.size() > 0)
	  _model->render(&_materials, _skeleton);
	else
	  _model->render(NULL, _skeleton);
  }

  if (_physicalObject != NULL && _renderMode & RENDER_PHYSICAL)
	_physicalObject->render();
}

const PN3DSkeletonObject::AnimationVector&
PN3DSkeletonObject::getAnimations() const
{
  return _anims;
}

const PN3DSkeleton*
PN3DSkeletonObject::getSkeleton() const
{
  return _skeleton;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PN3DSkeletonObject::_setEnabled(PN3DSkeletonAnimation* anim, pnbool enabled)
{
  if (enabled)
  {
	_animsToPlay.insert(anim);
	if (anim->step == (pnuint)-1)
	  anim->step = 0;
  }
  else
	_animsToPlay.erase(anim);

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::setEnabled(pnuint animId, pnbool enabled)
{
  PNLOCK(this);

  if (animId < 0 || (pnuint)animId >= _anims.size())
	return PNEC_ERROR;
  
  _anims[animId]->playId = (pnint)animId;

  return _setEnabled(_anims[animId], enabled);
}

pnbool
PN3DSkeletonObject::isEnabled(pnuint animId) const
{
  if (animId < 0 || (pnuint)animId >= _anims.size())
	return false;

  return _animsToPlay.find(_anims[animId]) != _animsToPlay.end();
}

pnuint
PN3DSkeletonObject::stopAnimation()
{
  PNLOCK(this);

  for (AnimationSet::iterator it = _animsToPlay.begin(); it != _animsToPlay.end(); ++it)
	(*it)->stop();

  _animsToPlay.clear();

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::stopAnimation(pnuint animId)
{
  PNLOCK(this);

  if (animId < 0 || (pnuint)animId >= _anims.size())
	return PNEC_ERROR;

  //////////////////////////////////////////////////////////////////////////

  _anims[animId]->stop();

  return setEnabled(animId, false);
}

pnuint
PN3DSkeletonObject::startAnimation()
{
  PNLOCK(this);

  for (AnimationSet::iterator it = _animsToPlay.begin(); it != _animsToPlay.end(); ++it)
	((PN3DSkeletonAnimation*)*it)->start();

  //////////////////////////////////////////////////////////////////////////
  
  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::startAnimation(pnuint animId)
{
  PNLOCK(this);

  if (animId < 0 || (pnuint)animId >= _anims.size())
	return PNEC_ERROR;

  //////////////////////////////////////////////////////////////////////////

  _anims[animId]->start();

  return setEnabled(animId, true);
}

//////////////////////////////////////////////////////////////////////////

pnuint
PN3DSkeletonObject::setAnimSpeed(pnfloat speed)
{
  PNLOCK(this);

  _defaultAnimSpeed = speed;

  for (AnimationVector::iterator it = _anims.begin(); it != _anims.end(); ++it)
	(*it)->speed = speed;

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::setAnimSpeed(pnint animId, pnfloat speed)
{
  PNLOCK(this);

  if (animId < 0 || (pnuint)animId >= _anims.size())
	return PNEC_ERROR;

  _anims[animId]->speed = speed;

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::setAnimWeight(pnfloat weight)
{
  PNLOCK(this);

  _defaultAnimWeight = weight;

  for (AnimationVector::iterator it = _anims.begin(); it != _anims.end(); ++it)
	(*it)->weight = weight;

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::setAnimWeight(pnint animId, pnfloat weight)
{
  PNLOCK(this);

  if (animId < 0 || (pnuint)animId >= _anims.size())
	return PNEC_ERROR;

  _anims[animId]->weight = weight;

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::setAnimNext(pnint animId, pnint nextAnimId)
{
  PNLOCK(this);

  if (animId < 0 || (pnuint)animId >= _anims.size())
	return PNEC_ERROR;

  _anims[animId]->next = nextAnimId;

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::setEnableLoop(pnbool loop)
{
  PNLOCK(this);

  for (AnimationVector::iterator it = _anims.begin(); it != _anims.end(); ++it)
	(*it)->looping = loop;

  return PNEC_SUCCESS;
}

pnuint
PN3DSkeletonObject::setEnableLoop(pnint animId, pnbool loop)
{
  PNLOCK(this);

  if (animId < 0 || (pnuint)animId >= _anims.size())
	return PNEC_ERROR;

  _anims[animId]->looping = loop;

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

void
PN3DSkeletonObject::clearAnimationIds()
{
  PNLOCK(this);

  _animsToPlay.clear();
}

//////////////////////////////////////////////////////////////////////////
};

