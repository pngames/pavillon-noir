/*
 * PNGLShape.cpp
 * 
 * Description :
 * PNGLShape definition
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

#include <sstream>
#include <libxml/xmlreader.h>
#include <boost/filesystem/operations.hpp>

#include "pneditorcommon.hpp"
#include "pnimport.h"
#include "pnexception.h"

#include "pnxml.h"
#include "pno_format.h"

#include "PN3DObject.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PNCharacter.hpp"
#include "PNMatrixTR4f.hpp"

#include "PNImportManager.hpp"
#include "pnresources.h"
#include "PN3DModel.hpp"
#include "PNGLShape.hpp"
#include "PNWayPoint.hpp"
#include "PNPropertiesGrid.hpp"
#include "PNPropertiesPanel.hpp"
#include "pnproperties.h"
#include "PNEditor.hpp"
#include "PNGLViewer.hpp"

namespace fs = boost::filesystem;
using namespace PN;
using namespace PN::EDITOR;

//////////////////////////////////////////////////////////////////////////

namespace PN
{
namespace EDITOR
{
//////////////////////////////////////////////////////////////////////////

/* Map
FXDEFMAP(PNGLShape) PNGLShapeMap[]=
{
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,0,PNGLShape::onLeftBtnRelease),
  FXMAPFUNC(SEL_DND_DROP,0,PNGLShape::onDNDDrop),
  FXMAPFUNC(SEL_SELECTED,0,PNGLShape::onSelected)
};
*/

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT_ABSTRACT(PNGLShape,FXGLShape,NULL,0)

#define FACTOR  0.5f
#define BIAS    0.002f

// GLU versions prior to 1.1 have GLUquadric
#if !defined(GLU_VERSION_1_1) && !defined(GLU_VERSION_1_2) && !defined(GLU_VERSION_1_3)
#define GLUquadricObj GLUquadric

#endif

// Sphere fidelity
#define SPHERE_SLICES  20
#define SPHERE_STACKS  20

//////////////////////////////////////////////////////////////////////////

PNGLShape::PNGLShape(void)
: radius(0.5f), slices(SPHERE_SLICES), stacks(SPHERE_STACKS)
{
  FXTRACE((100,"PNGLShape::PNGLShape\n"));

  range.lower.x = -radius; range.upper.x = radius;
  range.lower.y = -radius; range.upper.y = radius;
  range.lower.z = -radius; range.upper.z = radius;
}

PNGLShape::PNGLShape(PN3DObject *obj, PNPropertiesPanel* panel, PNEditor* ed, PNEnvType envType, std::string classStr, int id, std::string label)
: radius(0.5f), slices(SPHERE_SLICES), stacks(SPHERE_STACKS)
{
  FXTRACE((100,"PNGLShape::PNGLShape\n"));

  _obj = obj;
  _ed = ed;
  _id = id;
  _envType = envType;
  _canDrag = TRUE;
  _label = label;
  _panel = panel;
  _classStr = classStr;
  _modified = FALSE;

  setPosFromObj();
  setMinMax();
  buildParams();
}

PNGLShape::PNGLShape(xmlNode* node, PNPropertiesPanel* panel, PNEditor* ed)
: radius(0.5f), slices(SPHERE_SLICES), stacks(SPHERE_STACKS)
{
  FXTRACE((100,"PNGLShape::PNGLShape\n"));

  pnint error = unserializeFromXML(node);

  if (error != PNEC_SUCCESS)
	throw PNException(error);

  _panel = panel;
  _ed = ed;

  setPosFromObj();
  setMinMax();
  buildParams();
}

// Destroy
PNGLShape::~PNGLShape()
{
  FXTRACE((100,"PNGLShape::~PNGLShape\n"));

  for (ParametersVector::iterator it = _params.begin(); it != _params.end(); ++it)
	delete *it;
}

//////////////////////////////////////////////////////////////////////////

void
PNGLShape::setMinMax()
{
  if (_obj->get3DModel() == NULL)
	return ;

  PN::PN3DModel*		m = _obj->get3DModel();
  const PN::PNPoint3f&	min = m->getMin();
  const PN::PNPoint3f&	max = m->getMax();

  if (m->getFile() != NULL)
	_temppath = *(m->getFile());

  range.lower.x = min.x;
  range.lower.y = min.y;
  range.lower.z = min.z;
  range.upper.x = max.x;
  range.upper.y = max.y;
  range.upper.z = max.z;

  pnerror(PN_LOGLVL_DEBUG, "New obj: minx=%f miny=%f minz=%f maxx=%f maxy=%f maxz=%f",
	min.x, min.y, min.z, max.x, max.y, max.z);
}

void
PNGLShape::buildParams()
{
  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL, &position.x, "position x", "position x"));
  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL, &position.y, "position y", "position y"));
  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_REAL, &position.z, "position z", "position z"));
  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_STRING, &_classStr, "class", "class"));

  if (_obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_LINK, _obj, "links", "links")); // FIXME _obj should'nt be given as param
  else
  {
	_pOrientX = new PNConfigurableParameter(this, PN_PARAMTYPE_DIALX, _obj, "Pitch", "Pitch");
	_pOrientY = new PNConfigurableParameter(this, PN_PARAMTYPE_DIALY, _obj, "Yaw", "Yaw");
	_pOrientZ = new PNConfigurableParameter(this, PN_PARAMTYPE_DIALZ, _obj, "Roll", "Roll");
	_pMaterialList = new PNConfigurableParameterList(this, PN_LISTPARAMTYPE_MATERIAL, (void*)&_obj->getMaterials(), "Materials", "Materials");
	_pScriptList = new PNConfigurableParameter(this, PN_PARAMTYPE_SCRIPTLIST, &_scripts, "Events & Scripts", "Events & Scripts");
	
	_pMaterialList->enableSetModified(true);
	_pScriptList->enableSetModified(true);

	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_STRING, &_label, "label", "label"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_FILE, &_temppath, "model", "model"));
	_params.push_back(_pOrientX);
	_params.push_back(_pOrientY);
	_params.push_back(_pOrientZ);
	_params.push_back(_pMaterialList);
	_params.push_back(_pScriptList);

	if (_obj->getObjType() == PN3DObject::OBJTYPE_3DSKELETONOBJ || _obj->getObjType() == PN3DObject::OBJTYPE_CHARACTER)
	{
	  PNConfigurableParameterList* pAnimList = new PNConfigurableParameterList(this, PN_LISTPARAMTYPE_ANIM, (void*)&((PN3DSkeletonObject*)_obj)->getAnimations(), "Animations", "Animations");
	  pAnimList->enableSetModified(true);

	  _params.push_back(pAnimList);
	}
  }

  _panel->addObject(this);
}

void
PNGLShape::setPosNull()
{
  position.x = 0.0f;
  position.y = 0.0f;
  position.z = 0.0f;
}

void
PNGLShape::setPosFromObj()
{
  position.x = _obj->getX();
  position.y = _obj->getY();
  position.z = _obj->getZ();
}

// overloaded function to update the PN3DObject coords
FXbool
PNGLShape::drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty)
{
  //pnerror(PN_LOGLVL_DEBUG, "FXbool	PNGLShape::drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty)");
  if (_canDrag)
  {
	FXfloat zz = viewer->worldToEyeZ(position);
	FXVec3f wf = viewer->eyeToWorld(viewer->screenToEye(fx,fy,zz));
	FXVec3f wt = viewer->eyeToWorld(viewer->screenToEye(tx,ty,zz));
	position += wt - wf;
	_obj->setCoord(position.x, position.y, position.z);

	return TRUE;
  }
  return TRUE;
}

// Draw this object in a viewer
void
PNGLShape::drawshape(FXGLViewer* v)
{
  PNMatrixTR4f	m;
  PNGLViewer*	pnviewer = (PNGLViewer*)v;

  glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT|GL_ENABLE_BIT|GL_LIGHTING_BIT|GL_POLYGON_BIT|GL_TEXTURE_BIT);
  m.loadIdentity();
  m.setRotationQuaternion(_obj->getOrient());
  glPushMatrix();
  glMultMatrixf(m.getMatrix());


  if (_obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
  {
	PNWayPoint* wp = (PNWayPoint*)_obj;

	if (pnviewer->isSelected(this))
	  wp->setSelected();
  }

  _obj->render();

  glPopMatrix();
  glPopAttrib();
}

void
PNGLShape::setInObjView()
{
  _ed->setInObjView((FXGLObject*)this);
}

void
PNGLShape::addScript(pnEventType type, const char* name)
{
  boost::filesystem::path* scriptPath = new boost::filesystem::path(PNResourcesManager::getInstance()->getDefault(PNRT_gamedef) + name);

  if (_scripts.find(type) == _scripts.end())
	_scripts[type] = new scriptList;
  _scripts[type]->push_back(scriptPath);
}

void
PNGLShape::selfRemove()
{
  _ed->removeShape((FXGLShape*)this);
  if (_obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	_ed->deleteWP((PNWayPoint*)_obj);
}

//////////////////////////////////////////////////////////////////////////

void
PNGLShape::update(PNConfigurableParameter* p)
{
  if (p->getElem() == &position.x || p->getElem() == &position.y || p->getElem() == &position.z)
	_obj->setCoord(position.x, position.y, position.z);
  else if (p->getElem() == &_temppath)
  {
	PN3DModel* m = (PN3DModel*)PNImportManager::getInstance()->import(_temppath, PN_IMPORT_3DMODEL);
	_obj->set3DModel(m);
  }
  else if (p->getElem() == &_label)
	_panel->updateListBox();

  _ed->redraw();

  return;
}

int
PNGLShape::getNbParameters()
{
  return _params.size();
}

PNConfigurableParameter* PNGLShape::getParameter(int idx)
{
  return _params[idx];
}

void
PNGLShape::makeViewerCurrent()
{
  _ed->makeViewerCurrent();
}

void
PNGLShape::makeViewerNonCurrent()
{
  _ed->makeViewerNonCurrent();
}

void
PNGLShape::reset()
{
  _obj->unserialize();
  setUnmodified();
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNGLShape::getRootNodeName() const
{
  return PNENTITY_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNGLShape::_parseID(std::string id)
{
  std::string idstr((const char *)PNXML_IDBASE_VAL);
  std::string::size_type	  index = id.find(idstr);

  if (index == std::string::npos)
	return atoi(id.c_str());

  return atoi(id.c_str() + index + idstr.size());
}

pnint
PNGLShape::_unserializeActions(xmlNode* root)
{
  std::string	name((char *)xmlGetProp(root, PNXML_REFERENCE_ATTR));
  pnEventType t = PNEventManager::getInstance()->getTypeByName(name);

  if (t > 1 && t <= PN_NUMBER_EVENTS)
  {
	for (xmlNodePtr node = root->children; node != NULL; node = node->next)
	  if (xmlStrEqual(node->name, PNXML_SCRIPT_MKP))
		addScript(t, (const char*)xmlGetProp(node, PNXML_REFERENCE_ATTR));
  }

  return PNEC_SUCCESS;
}

pnint
PNGLShape::_unserializeNode(xmlNode* node)
{
  if (xmlStrEqual(PNXML_ACTION_MKP, node->name))
	_unserializeActions(node);
  else if (xmlStrEqual(BAD_CAST PNO_XMLNODE_ROOT.c_str(), node->name))
  {
	pnint error = _obj->unserializeFromXML(node);
	_objLoaded = true;

	if (error != PNEC_SUCCESS)
	{
	  pnerror(PN_LOGLVL_WARNING, "%s(%d) : %s", _label.c_str(), _id, pnGetErrorString(error));
	  return error;
	}
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNGLShape::unserializeFromXML(xmlNode* root)
{
  _id = _parseID((const char *)xmlGetProp(root, PNXML_ID_ATTR));
  _label = (const char *)xmlGetProp(root, PNXML_LABEL_ATTR);
  _classStr = (const char *)xmlGetProp(root, PNXML_CLASS_ATTR);

  pnerror(PN_LOGLVL_DEBUG, "PNEditor - New entity : name=%s, id=%d", root->name, _id);

  //////////////////////////////////////////////////////////////////////////

  if (xmlStrEqual(xmlGetProp(root, PNXML_ENVTYPE_ATTR), PNXML_GROUND_VAL))
	_envType = PN_GROUND;
  else if (xmlStrEqual(xmlGetProp(root, PNXML_ENVTYPE_ATTR), PNXML_STATIC_VAL))
	_envType = PN_STATIC;
  else if (xmlStrEqual(xmlGetProp(root, PNXML_ENVTYPE_ATTR), PNXML_DYNAMIC_VAL))
	_envType = PN_DYNAMIC;

  //////////////////////////////////////////////////////////////////////////

  if (xmlStrEqual(xmlGetProp(root, PNXML_OBJTYPE_ATTR), PNXML_OBJECT_VAL))
	_obj = new PN3DObject();
  else if (xmlStrEqual(xmlGetProp(root, PNXML_OBJTYPE_ATTR), PNXML_DYNAMIC_VAL))
	_obj = new PN3DSkeletonObject();
  else if (xmlStrEqual(xmlGetProp(root, PNXML_OBJTYPE_ATTR), PNXML_CHARACTER_VAL))
	_obj = new PNCharacter();

  if (_obj == NULL)
	return PNEC_FAILED_TO_PARSE;

  //////////////////////////////////////////////////////////////////////////

  _objLoaded = false;

  for (xmlNodePtr node = root->children ; node != NULL; node = node->next)
  {
	pnint error = _unserializeNode(node);
	if (error != PNEC_SUCCESS)
	  return error;
  }

  //////////////////////////////////////////////////////////////////////////

  std::string mdref((const char *)xmlGetProp(root, PNXML_MODELREFERENCE_ATTR));

  if (!_objLoaded)
  {
	pnint obj_error = _obj->unserializeFromPath(PNResourcesManager::getInstance()->getDefault(PNRT_object) + mdref);
	if (obj_error != PNEC_SUCCESS)
	{
	  pnerror(PN_LOGLVL_ERROR, "%s%s : %s", PNResourcesManager::getInstance()->getDefault(PNRT_object).c_str(), mdref.c_str(), pnGetErrorString(obj_error));
	  return obj_error;
	}

	setUnmodified();
  }
  else
  {
	_obj->setPath(PNResourcesManager::getInstance()->getDefault(PNRT_object) + mdref);
	setModified();
  }

  //////////////////////////////////////////////////////////////////////////

  pnfloat	  x, y, z, xx, yy, zz, ww;

  x = XMLUtils::xmlGetProp(root, PNXML_COORDX_ATTR, 0.0f);
  y = XMLUtils::xmlGetProp(root, PNXML_COORDY_ATTR, 0.0f);
  z = XMLUtils::xmlGetProp(root, PNXML_COORDZ_ATTR, 0.0f);
  _obj->setCoord(x, y, z);

  xx = XMLUtils::xmlGetProp(root, PNXML_ROTX_ATTR, 0.0f);
  yy = XMLUtils::xmlGetProp(root, PNXML_ROTY_ATTR, 0.0f);
  zz = XMLUtils::xmlGetProp(root, PNXML_ROTZ_ATTR, 0.0f);
  ww = XMLUtils::xmlGetProp(root, PNXML_ROTW_ATTR, 0.0f);
  _obj->setOrient(xx, yy, zz, ww);

  //////////////////////////////////////////////////////////////////////////

  return PNEC_SUCCESS;
}

pnint
PNGLShape::serializeInXML(xmlNode* root, pnbool isroot/* = false*/)
{
  if (isroot == false)
	root = xmlNewChild(root, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  //////////////////////////////////////////////////////////////////////////

  std::ostringstream os;
  os << PNXML_IDBASE_VAL << getId();

  xmlNewProp(root, PNXML_ID_ATTR, BAD_CAST os.str().c_str());

  xmlNewProp(root, PNXML_LABEL_ATTR, BAD_CAST getLabel().c_str());
  xmlNewProp(root, PNXML_MODELREFERENCE_ATTR,BAD_CAST PNResourcesManager::getInstance()->convertPath(PNRT_object, *_obj->getPath()).c_str());

  switch (getEnvType())
  {
  case PN_GROUND:
	xmlNewProp(root, PNXML_ENVTYPE_ATTR, PNXML_GROUND_VAL);
  	break;
  case PN_STATIC:
	xmlNewProp(root, PNXML_ENVTYPE_ATTR, PNXML_STATIC_VAL);
	break;
  case PN_DYNAMIC:
	xmlNewProp(root, PNXML_ENVTYPE_ATTR, PNXML_DYNAMIC_VAL);
	break;
  default:
	break;
  }

  switch (_obj->getObjType())
  {
  case PN3DObject::OBJTYPE_3DSKELETONOBJ:
	xmlNewProp(root, PNXML_OBJTYPE_ATTR, PNXML_DYNAMIC_VAL);
	break;
  case PN3DObject::OBJTYPE_3DOBJ:
	xmlNewProp(root, PNXML_OBJTYPE_ATTR, PNXML_OBJECT_VAL);
	break;
  case PN3DObject::OBJTYPE_CHARACTER:
	xmlNewProp(root, PNXML_OBJTYPE_ATTR, PNXML_CHARACTER_VAL);
	break;
  default:
	break;
  }

  xmlNewProp(root, PNXML_CLASS_ATTR, BAD_CAST getClassStr().c_str());

  PNPoint3f		p = _obj->getCoord();
  PNQuatf		q = _obj->getOrient();

  XMLUtils::xmlNewProp(root, PNXML_COORDX_ATTR, p.x);
  XMLUtils::xmlNewProp(root, PNXML_COORDY_ATTR, p.y);
  XMLUtils::xmlNewProp(root, PNXML_COORDZ_ATTR, p.z);

  XMLUtils::xmlNewProp(root, PNXML_ROTX_ATTR, q.x);
  XMLUtils::xmlNewProp(root, PNXML_ROTY_ATTR, q.y);
  XMLUtils::xmlNewProp(root, PNXML_ROTZ_ATTR, q.z);
  XMLUtils::xmlNewProp(root, PNXML_ROTW_ATTR, q.w);

  //////////////////////////////////////////////////////////////////////////
  // save modifications of the pno if necessary
  if (modified())
	_obj->serializeInXML(root);

  //////////////////////////////////////////////////////////////////////////
  // actions
  scriptMap&	  scripts = getScripts();
  for (scriptMap::iterator i = scripts.begin(); i != scripts.end(); i++)
  {
	xmlNodePtr node = xmlNewChild(root, NULL, PNXML_ACTION_MKP, NULL);
	xmlNewProp(node, PNXML_REFERENCE_ATTR, BAD_CAST PNEventManager::getInstance()->getNameByType(i->first).c_str());

	for (scriptList::iterator j = i->second->begin(); j != i->second->end(); j++)
	{
	  int size = PNResourcesManager::getInstance()->getDefault(PNRT_gamedef).size();

	  std::string str = (*j)->string().substr(size,	(*j)->string().size() - size);

	  xmlNewChild(node, NULL, PNXML_SCRIPT_MKP, NULL);
	  xmlNewProp(node, PNXML_REFERENCE_ATTR, BAD_CAST str.c_str());
	}
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
//////////////////////////////////////////////////////////////////////////
};
