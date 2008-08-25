/*
 * PNGLViewer.cpp
 *
 * Description :
 * PNGLViewer definition
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


#include <fxkeys.h>

/////////////////////////////////////

#include "pneditorcommon.hpp"
#include "PNEditor.hpp"
#include "PN3DObject.hpp"
#include "PNPropertiesPanel.hpp"
#include "PNGLViewer.hpp"

/////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

FXDEFMAP(PNGLViewer) PNGLViewerMap[]=
{
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,0,PNGLViewer::onLeftBtnRelease),
  /*	  FXMAPFUNC(SEL_CHANGED,ID_POS_X,PNGLViewer::onPosX),
  FXMAPFUNC(SEL_UPDATE,ID_POS_Y,PNGLViewer::onPosY),
  FXMAPFUNC(SEL_COMMAND,ID_POS_Z,PNGLViewer::onPosZ),*/
  FXMAPFUNC(SEL_KEYPRESS, 0, PNGLViewer::onKeyPress),
  FXMAPFUNC(SEL_SELECTED, 0, PNGLViewer::onSelected)
};

//////////////////////////////////////////////////////////////////////////

FXIMPLEMENT(PNGLViewer,FXGLViewer,PNGLViewerMap,ARRAYNUMBER(PNGLViewerMap))

//////////////////////////////////////////////////////////////////////////

/*!
*	\brief
*	Default PNGLViewer constructor.
*/
PNGLViewer::PNGLViewer(FXComposite* p,FXGLVisual *vis,FXObject* tgt,FXSelector sel,
					   FXuint opts,FXint x,FXint y,FXint w,FXint h)
					   : FXGLViewer(p,vis,tgt,sel,opts,x,y,w,h)
{
  _parent=p;
  _ed=(PNEditor*)p;
  _instance = this;
  _multiSelection = false;
}

/*!
*	\brief
*	Construct GL viewer widget sharing display list with another GL viewer
*/
PNGLViewer::PNGLViewer(FXComposite* p,FXGLVisual *vis,FXGLViewer* sharegroup,FXObject* tgt,
					   FXSelector sel,FXuint opts,FXint x,FXint y,FXint w,FXint h)
					   : FXGLViewer(p,vis,sharegroup,tgt,sel,opts,x,y,w,h)
{
  _instance = this;
  _multiSelection = false;
}


// fox ///////////////////////////////////////////////////////////////////

void
PNGLViewer::create()
{
  FXGLViewer::create();
}

// events ////////////////////////////////////////////////////////////////

/*!
*	\brief
*	Handles left button released event.
*
*	Displays the adequate tabitem depending of the type of the selected object.
*/
long
PNGLViewer::onLeftBtnRelease(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "long PNGLViewer::onLeftBtnRelease(FXObject*,FXSelector,void*)");
  long rcode = FXGLViewer::handle(obj, sel,ptr);
  PNGLShape* s = (PNGLShape*)getSelection();

  if (s != NULL)
  {
	switch(s->getObj()->getObjType())
	{
	case PN3DObject::OBJTYPE_3DOBJ:
	case PN3DObject::OBJTYPE_3DSKELETONOBJ:
	case PN3DObject::OBJTYPE_GROUND:
	case PN3DObject::OBJTYPE_CHARACTER:
	  _ed->getObjPanel()->setObject((PNConfigurableObject*)s);
	  _ed->setCurrentTab(1);
	  break;
	case PN3DObject::OBJTYPE_WAYPOINT:
	  _ed->getWpPanel()->setObject((PNConfigurableObject*)s);
	  _ed->setCurrentTab(2);
	  break;
	case PN3DObject::OBJTYPE_CAMERA:
	  break;
	default:
	  ;
	}
  }
  return rcode;
}

/*!
*	\brief
*	Handles key pressed event.
*
*	Here is the place where convenient shortcuts can be defined (move left, delete selection, ...)
*/
long
PNGLViewer::onKeyPress(FXObject* obj, FXSelector sel, void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "long PNGLViewer::onKeyPress(FXObject* obj,FXSelector sel,void* ptr)");
  FXEvent* event=(FXEvent*)ptr;
  PNGLShape* s = (PNGLShape*)getSelection();

  FXVec3f eye = getEyePosition();

  float x = .0f;
  float y = .0f;
  float z = .0f;
  //if (s != NULL)
  switch(event->code)
  {
  case KEY_d:
  case KEY_D:
  case KEY_Right:
  case KEY_KP_Right:
	x = 50.0f;
	break;
  case KEY_a:
  case KEY_A:
  case KEY_Left:
  case KEY_KP_Left:
	x = -50.0f;
	break;
  case KEY_w:
  case KEY_W:
  case KEY_Up:
  case KEY_KP_Up:
	z = -50.0f;
	break;
  case KEY_s:
  case KEY_S:
  case KEY_Down:
  case KEY_KP_Down:
	z = 50.0f;
	break;
  case KEY_e:
  case KEY_E:
  case KEY_Page_Up:
	y = 50.0f;
	break;
  case KEY_q:
  case KEY_Q:
  case KEY_Page_Down:
	y  = -50.0f;
	break;
  default:
	FXGLViewer::handle(obj, sel,ptr);
	;
  }
  translate(getOrientation().invert() * FXVec3f(x, y, z));
  _ed->redraw();

  return 1;
}

long
PNGLViewer::onSelected(FXObject* obj, FXSelector sel, void* ptr)
{
  long result = FXGLViewer::handle(obj, sel, ptr);

  if (!_multiSelection)
	_selectedObjects.clear();

  _selectedObjects.insert(((PNGLShape**)ptr)[0]);

  return result;
}

/*
long PNGLViewer::onPosX(FXObject* obj,FXSelector sel,void* ptr)
{
return 1;
}

long PNGLViewer::onPosY(FXObject* obj,FXSelector sel,void* ptr)
{
return 1;
}

long PNGLViewer::onPosZ(FXObject* obj,FXSelector sel,void* ptr)
{
return 1;
}
*/
// viewer ////////////////////////////////////////////////////////////////


/*!
*	\brief
*/
void
PNGLViewer::makeViewerCurrent()
{
  makeCurrent();
  return;
}

/*!
*	\brief
*/
void
PNGLViewer::makeViewerNonCurrent()
{
  makeNonCurrent();
  return;
}

//////////////////////////////////////////////////////////////////////////

void
PNGLViewer::setMultiselection(pnbool multiSelection)
{
  _multiSelection = multiSelection;
}

pnbool
PNGLViewer::getMultiSelection()
{
  return _multiSelection;
}

pnbool
PNGLViewer::isSelected(PNGLShape* object)
{
  return _selectedObjects.find(object) != _selectedObjects.end();
}

const PNGLViewer::ObjectSet&
PNGLViewer::getSelectedObjects()
{
  return _selectedObjects;
}

//////////////////////////////////////////////////////////////////////////
};

//////////////////////////////////////////////////////////////////////////
};
