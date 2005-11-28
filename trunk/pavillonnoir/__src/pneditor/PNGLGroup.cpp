/*
* PNGLGoup.cpp
* 
* Description :
* PNGLGoup definition
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
#include <sstream>

#include "pndefs.h"
#include "pnevent.h"
#include "pnxml.h"
#include "pnresources.h"

#include "PN3DObject.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PNCharacter.hpp"

#include "PNGLShape.hpp"

#include "PNGLGroup.hpp"

namespace fs = boost::filesystem;
using namespace PN::EDITOR;

namespace PN { namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

FXIMPLEMENT(PNGLGroup,FXGLGroup,NULL,0)

//////////////////////////////////////////////////////////////////////////

PNGLGroup::PNGLGroup()
{
  
}

PNGLGroup::~PNGLGroup()
{
  clear();
}

//////////////////////////////////////////////////////////////////////////

void
PNGLGroup::clear()
{
  FXGLGroup::clear();

  _groundGroup.clear();
  _staticGroup.clear();
  _dynGroup.clear();
}

void
PNGLGroup::_updateView()
{
  FXGLGroup::clear();

  if (_view & VIEW_GROUND)
	append(&_groundGroup);
  if (_view & VIEW_STATIC)
	append(&_staticGroup);
  if (_view & VIEW_DYNAMIC)
	append(&_dynGroup);
}

pnbool
PNGLGroup::contains(viewOption view)
{
  return (_view & view) != 0;
}

void
PNGLGroup::setOptionView(pnuint view)
{
  _view = view;

  _updateView();
}

pnuint
PNGLGroup::getOptionView()
{
  return _view;
}

void
PNGLGroup::enableOptionView(viewOption view, pnbool enable/* = true*/)
{
  if (enable)
	addOptionView(view);
  else
	deleteOptionView(view);
}

void
PNGLGroup::addOptionView(viewOption view)
{
  setOptionView(_view | view);
}

void
PNGLGroup::deleteOptionView(viewOption view)
{
  setOptionView(_view & ~view);
}

//////////////////////////////////////////////////////////////////////////

/// Append child object
void
PNGLGroup::append(FXGLObject* obj)
{
  PNGLShape*	pnobj = (PNGLShape*)obj;

  switch (pnobj->getEnvType())
  {
  case PN_GROUND:
	_groundGroup.append(obj);
	break;
  case PN_STATIC:
	_staticGroup.append(obj);
	break;
  case PN_DYNAMIC:
	_dynGroup.append(obj);
	break;
  default:
    break;
  }
}

/// Remove child object
void
PNGLGroup::remove(FXGLObject* obj)
{
  FXGLGroup::remove(obj);

  PNGLShape*	pnobj = (PNGLShape*)obj;

  switch (pnobj->getEnvType())
  {
  case PN_GROUND:
	_groundGroup.remove(obj);
  	break;
  case PN_STATIC:
	_staticGroup.remove(obj);
	break;
  case PN_DYNAMIC:
	_dynGroup.remove(obj);
	break;
  default:
    break;
  }
}

//////////////////////////////////////////////////////////////////////////

void
PNGLGroup::setPropertiesPanel(PNPropertiesPanel* panel)
{
  _grid = panel;
}

void
PNGLGroup::setEditor(PNEditor* editor)
{
  _editor = editor;
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNGLGroup::getDTD() const
{
  return PNMAP_XMLDTD;
}

const std::string&
PNGLGroup::getDTDName() const
{
  return PNMAP_XMLDTD_NAME;
}

const std::string&
PNGLGroup::getRootNodeName() const
{
  return PNMAP_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNGLGroup::_unserializeActions(xmlNode* node, PNGLShape* shape)
{
  std::string	name((char *)xmlGetProp(node, PNXML_REFERENCE_ATTR));
  pnEventType t = PNEventManager::getInstance()->getTypeByName(name);

  pnerror(PN_LOGLVL_DEBUG, "action: ref %s val %d", xmlGetProp(node, PNXML_REFERENCE_ATTR), t);
  if (t > 1 && t <= PN_NUMBER_EVENTS)
  {
	for (xmlNodePtr current = node->children; current != NULL; current = current->next)
	{ 
	  if (current->type != XML_ELEMENT_NODE)
		continue; 
	  if (!xmlStrcmp(current->name, PNXML_SCRIPT_MKP))
		shape->addScript(t, (char*)xmlGetProp(current, PNXML_REFERENCE_ATTR));
	}
  }
  return 1;
}

pnint
PNGLGroup::_parseID(std::string id)
{
  std::string idstr((const char *)PNXML_IDBASE_VAL);
  std::string::size_type	  index = id.find(idstr);

  if (index == std::string::npos)
	return atoi(id.c_str());

  return atoi(id.c_str() + index + idstr.size());
}

pnint
PNGLGroup::_unserializeEntity(xmlNode* node)
{
  /// int id = atoi((const char *)xmlGetProp(current, PNXML_ID_ATTR));
  int id = _parseID((const char *)xmlGetProp(node, PNXML_ID_ATTR));
  std::string mdref((const char *)xmlGetProp(node, PNXML_MODELREFERENCE_ATTR));
  std::string label((const char *)xmlGetProp(node, PNXML_LABEL_ATTR));
  std::string classStr((const char *)xmlGetProp(node, PNXML_CLASS_ATTR));
  PNEnvType	  envType;
  pnfloat	  x, y, z, xx, yy, zz, ww;

  pnerror(PN_LOGLVL_DEBUG, "PNEditor - New entity : name=%s, id=%s, mdref=%s", 
	node->name, xmlGetProp(node, PNXML_ID_ATTR), mdref.c_str());

  PN3DObject  *object = NULL;

  //id = atoi((const char *)xmlGetProp(current, PNXML_ID_ATTR));
  if (!xmlStrcmp(xmlGetProp(node, PNXML_ENVTYPE_ATTR), PNXML_GROUND_VAL))
	envType = PN_GROUND;
  else if (!xmlStrcmp(xmlGetProp(node, PNXML_ENVTYPE_ATTR), PNXML_STATIC_VAL))
	envType = PN_STATIC;
  else if (!xmlStrcmp(xmlGetProp(node, PNXML_ENVTYPE_ATTR), PNXML_DYNAMIC_VAL))
	envType = PN_DYNAMIC;

  if (!xmlStrcmp(xmlGetProp(node, PNXML_OBJTYPE_ATTR), PNXML_OBJECT_VAL))
	object = new PN3DObject();
  else if (!xmlStrcmp(xmlGetProp(node, PNXML_OBJTYPE_ATTR), PNXML_DYNAMIC_VAL))
	object = new PN3DSkeletonObject();
  else if (!xmlStrcmp(xmlGetProp(node, PNXML_OBJTYPE_ATTR), PNXML_CHARACTER_VAL))
	object = new PNCharacter();

  if (object == NULL)
	return PNEC_FAILED_TO_PARSE;

  bool fromFile = TRUE;
  if (!node->last || !node->last->prev)
	//if (!current->children)
  {
	pnint obj_error = object->unserializeFromPath(DEF::objectFilePath + mdref);
	if (obj_error != PNEC_SUCCESS)
	{
	  pnerror(PN_LOGLVL_ERROR, "%s%s : %s", DEF::objectFilePath.c_str(), mdref.c_str(), pnGetErrorString(obj_error));
	  return obj_error;
	}
  }
  else
  {
	pnint obj_error = object->unserializeFromXML(node->last->prev);
	if (obj_error != PNEC_SUCCESS)
	{
	  pnerror(PN_LOGLVL_ERROR, "%s%s : %s", DEF::objectFilePath.c_str(), mdref.c_str(), pnGetErrorString(obj_error));
	  return obj_error;
	}

	fs::path  file(DEF::objectFilePath + mdref, fs::native);
	object->setFile(file);
	fromFile = FALSE;
  } 

  x = (pnfloat)atof((const char *)xmlGetProp(node, PNXML_COORDX_ATTR));
  y = (pnfloat)atof((const char *)xmlGetProp(node, PNXML_COORDY_ATTR));
  z = (pnfloat)atof((const char *)xmlGetProp(node, PNXML_COORDZ_ATTR));
  object->setCoord(x, y, z);

  xx = (pnfloat)atof((const char *)xmlGetProp(node, PNXML_ROTX_ATTR));
  yy = (pnfloat)atof((const char *)xmlGetProp(node, PNXML_ROTY_ATTR));
  zz = (pnfloat)atof((const char *)xmlGetProp(node, PNXML_ROTZ_ATTR));
  ww = (pnfloat)atof((const char *)xmlGetProp(node, PNXML_ROTW_ATTR));
  object->setOrient(xx, yy, zz, ww);

  // build PMGLShape in _genScene
  PNGLShape* shape = new PNGLShape(object, _grid, _editor, envType, classStr, id, label);
  if (fromFile == FALSE)
	shape->setModified();

  // go through child nodes to load actions (scripts) and models definitions (materials, animations ...)
  for (xmlNodePtr current = node->children; current != NULL; current = current->next)
  {  
	if (current->type != XML_ELEMENT_NODE)
	  continue;
	if (!xmlStrcmp(current->name, PNXML_MODEL_MKP))
	  object->unserializeFromXML(current);
	if (!xmlStrcmp(current->name, PNXML_OBJECT_MKP))
	  pnerror(PN_LOGLVL_DEBUG, "PNEditor - current children is : %s", current->name);
	if (!xmlStrcmp(current->name, PNXML_ACTION_MKP))
	  _unserializeActions(current, shape);
  }

  switch (envType)
  {
  case PN_GROUND:
	_groundGroup.append(shape);
	break;
  case PN_STATIC:
	_staticGroup.append(shape);
	break;
  case PN_DYNAMIC:
	_dynGroup.append(shape);
	break;
  default:
	break;
  }

  return PNEC_SUCCESS;
}

pnint
PNGLGroup::_unserializeNode(xmlNode* node)
{
  if (strcmp((const char*)PNXML_ENTITY_MKP, (const char*)node->name) == 0)
	_unserializeEntity(node);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNGLGroup::unserializeFromXML(xmlNode* root)
{
  pnerror(PN_LOGLVL_DEBUG, "%s : %s", "PNEditor - node name", root->name);

  if (strcmp((const char*)root->name, (const char*)PNXML_LISTENTITIES_MKP) == 0)
	for (root = root->children ; root != NULL; root = root->next)
	  _unserializeNode(root);

  return PNEC_SUCCESS;
}

pnint
PNGLGroup::serializeInXML(xmlNode* node, pnbool isroot/* = false*/)
{
  xmlNode* root = node;

  if (isroot == false)
	root = xmlNewChild(node, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  //////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < list.no(); i++)
  {
	FXObjectList&	view = ((FXGLGroup*)list[i])->getList();
	for (int j = 0; j < view.no(); j++)
	{
	  PNGLShape		*shape = (PNGLShape *)view[j];
	  PN3DObject	*obj = shape->getObj();
	  PNPoint3f		p = obj->getCoord();
	  PNQuatf		q = obj->getOrient();

	  xmlNodePtr current = xmlNewChild(root, NULL, PNXML_ENTITY_MKP, NULL);
	  {
		std::ostringstream os;
		os << PNXML_IDBASE_VAL << shape->getId();

		xmlNewProp(current, PNXML_ID_ATTR, BAD_CAST os.str().c_str());

		xmlNewProp(current, PNXML_LABEL_ATTR, BAD_CAST shape->getLabel().c_str());
		xmlNewProp(current, PNXML_MODELREFERENCE_ATTR,BAD_CAST DEF::convertPath(DEF::objectFilePath, obj->getFile()->string()).c_str());

		if (shape->getEnvType() == PN_GROUND)
		  xmlNewProp(current, PNXML_ENVTYPE_ATTR, PNXML_GROUND_VAL);
		else if (shape->getEnvType() == PN_STATIC)
		  xmlNewProp(current, PNXML_ENVTYPE_ATTR, PNXML_STATIC_VAL);
		else if (shape->getEnvType() == PN_DYNAMIC)
		  xmlNewProp(current, PNXML_ENVTYPE_ATTR, PNXML_DYNAMIC_VAL);

		switch (obj->getObjType())
		{
		case PN3DObject::OBJTYPE_3DSKELETONOBJ:
		  xmlNewProp(current, PNXML_OBJTYPE_ATTR, PNXML_DYNAMIC_VAL);
		  break;
		case PN3DObject::OBJTYPE_3DOBJ:
		  xmlNewProp(current, PNXML_OBJTYPE_ATTR, PNXML_OBJECT_VAL);
		  break;
		case PN3DObject::OBJTYPE_CHARACTER:
		  xmlNewProp(current, PNXML_OBJTYPE_ATTR, PNXML_CHARACTER_VAL);
		  break;
		default:
		  break;
		}

		xmlNewProp(current, PNXML_CLASS_ATTR, BAD_CAST shape->getClassStr().c_str());

		XMLUtils::xmlNewProp(current, PNXML_COORDX_ATTR, p.x);
		XMLUtils::xmlNewProp(current, PNXML_COORDY_ATTR, p.y);
		XMLUtils::xmlNewProp(current, PNXML_COORDZ_ATTR, p.z);

		XMLUtils::xmlNewProp(current, PNXML_ROTX_ATTR, q.x);
		XMLUtils::xmlNewProp(current, PNXML_ROTY_ATTR, q.y);
		XMLUtils::xmlNewProp(current, PNXML_ROTZ_ATTR, q.z);
		XMLUtils::xmlNewProp(current, PNXML_ROTW_ATTR, q.w);
	  }

	  // actions
	  scriptMap&	  scripts = shape->getScripts();
	  for (scriptMap::iterator i = scripts.begin(); i != scripts.end(); i++)
	  {
		xmlNodePtr node2 = xmlNewChild(current, NULL, PNXML_ACTION_MKP, NULL);
		xmlNewProp(node2, PNXML_REFERENCE_ATTR, BAD_CAST PNEventManager::getInstance()->getNameByType(i->first).c_str());

		for (scriptList::iterator j = i->second->begin(); j != i->second->end(); j++)
		{
		  std::string str = (*j)->string().substr(PN::DEF::gamedefFilePath.size(),
			(*j)->string().size() - PN::DEF::gamedefFilePath.size());

		  xmlNewChild(node2, NULL, PNXML_SCRIPT_MKP, NULL);
		  xmlNewProp(node2, PNXML_REFERENCE_ATTR, BAD_CAST str.c_str());
		}
	  }

	  // save modifications of the pno if necessary
	  if (shape->modified())
		obj->serializeInXML(current);
	}
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
}};
