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

#include "pno_format.h"

namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PN3DSkeletonObject::PN3DSkeletonObject() : _skeleton(NULL)
{
  _objType = OBJTYPE_3DSKELETONOBJ;
}

PN3DSkeletonObject::~PN3DSkeletonObject()
{
  if (_skeleton != NULL)
	delete _skeleton;
}

//////////////////////////////////////////////////////////////////////////

int
PN3DSkeletonObject::_parseAnimations(xmlNode* parent)
{
  _animations.clear();

  for (xmlNodePtr  node = parent->children; node != NULL ; node = node->next)
  {
	if (node->type != XML_ELEMENT_NODE)
	  continue;

	xmlChar*	  attr = xmlGetProp(node, (const xmlChar *)PNO_XMLPROP_PATH);

	PN3DAnimation*	anim = NULL;

	if (attr != NULL)
	{
	  fs::path	  p(DEF::animationFilePath + (const char*)attr, fs::native);

	  anim = (PN3DAnimation*)PNImportManager::getInstance()->
		import(p, PN_IMPORT_3DANIMATION);
	}

	_animations.push_back(anim);
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
	fs::path p(DEF::skeletonFilePath + (const char*)attr, fs::native);

	if (fs::exists(p))
	  _skeleton = (PN3DSkeleton*)PNImportManager::getInstance()->import(p, PN_IMPORT_3DSKELETON, true);

	if (_skeleton == NULL)
	  return PNEC_LOADING_MODEL;
  }

  return PNEC_SUCCESS;
}

pnint
PN3DSkeletonObject::_unserializeNode(xmlNode* node)
{
  if (PNO_XMLNODE_LISTMATERIALS == (const char*)node->name)
	_parseMaterials(node);
  else if (PNO_XMLNODE_LISTANIMS == (const char*)node->name)
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
  _animations.clear();

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
	xmlNewProp(node, BAD_CAST PNO_XMLPROP_PATH, BAD_CAST DEF::convertPath(DEF::skeletonFilePath, _skeleton->getFile()->string()).c_str());
  }

  if (_animations.size() > 0)
  {
	root = xmlNewChild(root, NULL, BAD_CAST PNO_XMLNODE_LISTANIMS.c_str(), NULL);

	for (VECTORANIMATION::iterator it = _animations.begin(); it != _animations.end(); ++it)
	  if (*it != NULL && ((PN3DAnimation*)*it)->getFile() != NULL)
	  {
		node = xmlNewChild(root, NULL, BAD_CAST PNO_XMLNODE_ANIM.c_str(), NULL);
		xmlNewProp(node, BAD_CAST PNO_XMLPROP_PATH, BAD_CAST DEF::convertPath(DEF::animationFilePath, ((PN3DAnimation*)*it)->getFile()->string()).c_str());
	  }
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

void
PN3DSkeletonObject::update(pnuint deltaTime)
{
  PN3DObject::update(deltaTime);

  //////////////////////////////////////////////////////////////////////////

  PNLOCK(this);

  if (_skeleton == NULL)
	return ;

  if (_running)
  {
	pnuint	step;

	if (_paused)
	  step = (pnuint)(_animSpeed * (_animTimePause - _animTimeStart));
	else
	  step = (pnuint)(_animSpeed * (PNRendererInterface::getInstance()->getTicks() - _animTimeStart));

	if (_animTransTime > 0)
	  _skeleton->update(step / (double)_animTransTime, _animations[_animId]);
	else
	  if (!_skeleton->update(step, _animations[_animId]))
	  {
		if (_looping)
		{
		  _animTimeStart =  PNRendererInterface::getInstance()->getTicks() - (step - _animations[_animId]->getTotalTime());

		  PNEventManager::getInstance()->addEvent(PN_EVENT_OA_LOOPED, this, NULL);
		}
		else
		  stopAnimation();
	  }
  }
  else
	_skeleton->update((pnuint)0, NULL);
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
	  _model->render(_materials, _skeleton);
	else
	  _model->render(_skeleton);
  }
}

PN3DSkeletonObject::VECTORANIMATION&
PN3DSkeletonObject::getAnimations()
{
  return _animations;
}

PN3DSkeleton*
PN3DSkeletonObject::getSkeleton()
{
  return _skeleton;
}

//////////////////////////////////////////////////////////////////////////
};
