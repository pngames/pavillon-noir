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
#include "pnexception.h"

#include "PN3DObject.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PNCharacter.hpp"

#include "PNGLShape.hpp"
#include "PNPropertiesPanel.hpp"
#include "PNEDSkyboxPanel.hpp"
#include "PNEditor.hpp"

#include "PNGLGroup.hpp"

namespace fs = boost::filesystem;
using namespace PN::EDITOR;

namespace PN { namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

FXIMPLEMENT(PNGLGroup,FXGLGroup,NULL,0)

//////////////////////////////////////////////////////////////////////////

PNGLGroup::PNGLGroup()
{
   _mpp = 1.0f;
   _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL, &_mpp, "mpp", "meters per pixel"));
}

PNGLGroup::~PNGLGroup()
{
  clear();

  for (ParametersVector::iterator it = _params.begin(); it != _params.end(); ++it)
	delete *it;
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
  else
	remove(&_groundGroup);

  if (_view & VIEW_STATIC)
	append(&_staticGroup);
  else
	remove(&_staticGroup);

  if (_view & VIEW_DYNAMIC)
	append(&_dynGroup);
  else
	remove(&_dynGroup);

  if (_view & VIEW_SKYBOX)
	append(&_skybox);
  else
	remove(&_skybox);
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

void
PNGLGroup::append(FXGLGroup* group)
{
  FXGLGroup::append(group);
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
PNGLGroup::init(PNEditor* editor, PNPropertiesPanel* panel)
{
  _editor = editor;
  _grid = panel;

  _skybox.setContext(_grid, _editor);
  _editor->getSKPanel()->setObject(&_skybox);
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
PNGLGroup::_unserializeSkyBox(xmlNode* node)
{
  return _skybox.unserializeFromXML(node);
}

pnint
PNGLGroup::_unserializeEntity(xmlNode* node)
{
  try
  {
	PNGLShape* shape = new PNGLShape(node, _grid, _editor);

	switch (shape->getEnvType())
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
  }
  catch (PNException ex)
  {
	return ex.getErrorCode();
  }

  return PNEC_SUCCESS;
}

pnint
PNGLGroup::_unserializeNode(xmlNode* node)
{
  if (xmlStrEqual(PNXML_ENTITY_MKP, node->name))
	_unserializeEntity(node);
  if (xmlStrEqual(PNXML_SKYBOX_MKP, node->name))
	_unserializeSkyBox(node);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNGLGroup::unserializeFromXML(xmlNode* root)
{
  pnerror(PN_LOGLVL_DEBUG, "%s : %s", "PNEditor - node name", root->name);

  //////////////////////////////////////////////////////////////////////////

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

	  shape->serializeInXML(root);
	}
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

}};
