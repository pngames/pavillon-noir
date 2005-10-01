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


#include <boost/filesystem/operations.hpp>

#include "pneditorcommon.hpp"
#include "pnimport.h"

#include "PNImportManager.hpp"
#include "pnresources.h"
#include "PN3DObject.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PN3DModel.hpp"
#include "PNGLShape.hpp"
#include "PNWayPoint.hpp"
#include "PNPropertiesGrid.hpp"
#include "PNPropertiesPanel.hpp"
#include "pnproperties.h"
#include "PNEditor.hpp"

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

PNGLShape::PNGLShape(PN3DObject *obj, PNPropertiesPanel* grid, PNEditor* ed, PNEnvType envType, std::string classStr, int id, std::string label)
: radius(0.5f), slices(SPHERE_SLICES), stacks(SPHERE_STACKS)
{
  _obj = obj;
  _ed = ed;
  _id = id;
  _envType = envType;
  _canDrag = TRUE;
  _label = label;
  _grid = grid;
  _classStr = classStr;

  FXTRACE((100,"PNGLShape::PNGLShape\n"));

  setPosFromObj();	
  setMinMax();
  buildParams();
}

void
PNGLShape::setMinMax()
{
  PN::PN3DModel*		m = _obj->get3DModel();
  const PN::PNPoint&	min = m->getMin();
  const PN::PNPoint&	max = m->getMax();
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
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_ACTIVESTRING, &_label, "label", "label"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_FILE, &_temppath, "model", "model"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_DIALX, _obj, "Pitch", "Pitch"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_DIALY, _obj, "Yaw", "Yaw"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_DIALZ, _obj, "Roll", "Roll"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_MATERIALLIST, (void*)&_obj->getMaterials(), "Materials", "Materials"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_SCRIPTLIST, &_scripts, "Events & Scripts", "Events & Scripts"));
	if (_obj->getObjType() == PN3DObject::OBJTYPE_3DSKELETONOBJ)
	  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_ANIMLIST, &((PN3DSkeletonObject*)_obj)->getAnimations(), "Animations", "Animations"));
  }

  _grid->addObject(this);
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
FXbool	PNGLShape::drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty)
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
void PNGLShape::drawshape(FXGLViewer* v)
{
  PNMatrixTR4f	m;

  glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT|GL_ENABLE_BIT|GL_LIGHTING_BIT|GL_POLYGON_BIT|GL_TEXTURE_BIT);
  m.loadIdentity();
  m.setRotationQuaternion(_obj->getOrient());
  glPushMatrix();
  glMultMatrixf(m.getMatrix());


  if (_obj->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
  {
	PNWayPoint* wp = (PNWayPoint*)_obj;

	if (v->getSelection() == (FXObject*)this)
	{
	  wp->setSelected();
	  wp->render();
	}
	else
	{
	  wp->render();
	}
  }
  else
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
  boost::filesystem::path* scriptPath = new boost::filesystem::path(PN::DEF::gamedefFilePath + name);

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

// Destroy
PNGLShape::~PNGLShape()
{
  FXTRACE((100,"PNGLShape::~PNGLShape\n"));

//  delete _obj;
}

//////////////////////////////////////////////////////////////////////////

void PNGLShape::update(PNConfigurableParameter* p)
{
  if (p->getElem() == &position.x || p->getElem() == &position.y || p->getElem() == &position.z)
	_obj->setCoord(position.x, position.y, position.z);
  else if (p->getElem() == &_temppath)
  {
	PN3DModel* m = (PN3DModel*)PNImportManager::getInstance()->import(_temppath, PN_IMPORT_3DMODEL);
	_obj->set3DModel(m);
  }
  _ed->redraw();

  return;
}

int PNGLShape::getNbParameters()
{
  return _params.size();
}

PNConfigurableParameter* PNGLShape::getParameter(int idx)
{
  return _params[idx];
}

void			PNGLShape::makeViewerCurrent()
{
  _ed->makeViewerCurrent();
}

void			PNGLShape::makeViewerNonCurrent()
{
  _ed->makeViewerNonCurrent();
}

};
//////////////////////////////////////////////////////////////////////////
};
