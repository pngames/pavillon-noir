/*
 * PNFXAnimListParameter.cpp
 * 
 * Description :
 * PNFXAnimListParameter definition
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
#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "pneditorcommon.h"
#include "pnproperties.h"
#include "pnimport.h"

#include "PNFXAnimListParameter.hpp"

#include "PNImportManager.hpp"
#include "PN3DAnimation.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PN3DModel.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNPropertiesGrid.hpp"

using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXAnimListParameter) PNFXAnimListParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXAnimListParameter::ID_EDIT, PNFXAnimListParameter::onEdit),
  FXMAPFUNC(SEL_COMMAND, PNFXAnimListParameter::ID_DIAL_OK, PNFXAnimListParameter::onDialOK),
  FXMAPFUNC(SEL_COMMAND, PNFXAnimListParameter::ID_DIAL_CANCEL, PNFXAnimListParameter::onDialCancel)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXAnimListParameter, PNFXListParameter, PNFXAnimListParameterMap, ARRAYNUMBER(PNFXAnimListParameterMap))

PNFXAnimListParameter::PNFXAnimListParameter(FXComposite* p, PNConfigurableParameterList* param) :
PNFXListParameter(p, param)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::PNFXAnimListParameter(FXComposite* p, PNConfigurableParameter* param)");

  _buttonEdit = new FXButton(this, "Edit", NULL, this, ID_EDIT,FRAME_RAISED|FRAME_THICK);

  _buildList();
}

PNFXAnimListParameter::~PNFXAnimListParameter()
{
}

//////////////////////////////////////////////////////////////////////////

void
PNFXAnimListParameter::create()
{
  PNFXListParameter::create();
}

/*
*	Builds AnimList list for current parameter.
*/
void
PNFXAnimListParameter::_buildList(void)
{
  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem();

  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::buildList");
  _listBox->clearItems();

  for (PN3DSkeletonObject::AnimationVector::iterator it = v->begin(); it != v->end(); ++it)
  {
	PN3DSkeletonAnimation*	skanim = *it;

	_listBox->appendItem(FXFile::name(skanim->anim->getFile()->c_str()), NULL,  skanim->anim);
  }

  _listBox->setNumVisible(_listBox->getNumItems()< 5 ? _listBox->getNumItems() : 5);
  pnerror(PN_LOGLVL_DEBUG, "End of PNFXAnimListParameter::buildList");
}

bool
PNFXAnimListParameter::_deleteObject(FXint index)
{
  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem(); 

  v->erase(v->begin() + index);

  return true;
}

bool
PNFXAnimListParameter::_addNewObject(FXint index)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::onAdd");

  PN3DAnimation* anim = this->openAnim();
  if (anim != NULL)
  {  
	PN3DSkeletonAnimation* skanim = new PN3DSkeletonAnimation(anim, NULL);
	_skanim = skanim;
	showAnim(skanim);
  }

  return false;
}

PN3DAnimation*  
PNFXAnimListParameter::openAnim(void)
{
  FXFileDialog fd(this, "Choose animation file to add");

  if (fd.execute())
  {
	PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem(); 
	pnint i = (pnint)v->size();
	FXString	str = fd.getFilename().substitute('\\', '/');;

	char buf[512] = "";
	getcwd(buf, 512);
	FXString cwd(buf);

	if (str.find(cwd.substitute('\\', '/')) == -1)
	{
	  FXMessageBox::error(this, MBOX_OK, "Path Error", "An error occurred. Please check file path.");	  	
	}
	else
	{
	  PN3DAnimation* anim = (PN3DAnimation*)PNImportManager::getInstance()->import(
		str.replace(0, (FXint)strlen(buf) + 1, "").text(), PN_IMPORT_3DANIMATION);

	  if (anim != NULL)
	  {
		/*
		v->push_back(PN3DSkeletonAnimation(anim, NULL));

		std::string s = *v->at(i).anim->getFile();
		if (s.size() > 29)
		  s = s.substr(0, 10) + "[...]" + s.substr(s.size()-15, s.size());
		_listBox->appendItem(s.c_str(), NULL, v->at(i).anim);
		_listBox->setNumVisible(_listBox->getNumItems()<5 ? _listBox->getNumItems() : 5);
		PNConfigurableObject* co = _param->getConfigurableObject();
		co->setModified();
		*/
		return anim;
	  }
	  else
	  {
		FXMessageBox::error(this, MBOX_OK, "File Error", "An error occurred. Please check file format.");
	  }
	}
  }
  return NULL;
}


long
PNFXAnimListParameter::onEdit(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::onEdit");

  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem();
  int i = 0;
  for (PN3DSkeletonObject::AnimationVector::iterator it = v->begin(); it != v->end(); ++it, ++i)
  {
	if (i == _listBox->getCurrentItem())
	{
	  showAnim(*it);
	  break;
	}
  }

  return 1;
}


void
PNFXAnimListParameter::showAnim(PNConfigurableObject* skanim)
{
  _animDialBox =  new FXDialogBox(this, "Add Anim", DECOR_TITLE|DECOR_BORDER);
  FXVerticalFrame* vframe = new FXVerticalFrame(_animDialBox, LAYOUT_FILL_X | LAYOUT_FILL_Y);
  FXGroupBox* group = new FXGroupBox(vframe, "Animation properties", LAYOUT_FILL_X | LAYOUT_FILL_Y | FRAME_GROOVE);
  PNPropertiesGrid* grid = new PNPropertiesGrid(group);
  _animDialBox->create();
  vframe->create();
  group->create();

  grid->setObject(skanim);

  new FXHorizontalSeparator(vframe, LAYOUT_FILL_X);
  FXHorizontalFrame*	buttons = new FXHorizontalFrame(vframe,LAYOUT_FILL_X|LAYOUT_FILL_Y);
  new FXButton(buttons,"&Ok",NULL,this,PNFXAnimListParameter::ID_DIAL_OK,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);
  new FXButton(buttons,"&Cancel",NULL,this,PNFXAnimListParameter::ID_DIAL_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);
  buttons->create();

  _animDialBox->execute();
}


long
PNFXAnimListParameter::onDialOK(FXObject* obj,FXSelector sel,void* ptr)
{
  if (_skanim != NULL)
  {
	PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem(); 
	v->push_back(_skanim);
	_skanim = NULL;
  }

  _animDialBox->getApp()->stopModal(_animDialBox, TRUE);
  _animDialBox->close();
  update();

  return 1;
}


long
PNFXAnimListParameter::onDialCancel(FXObject* obj,FXSelector sel,void* ptr)
{
  _animDialBox->getApp()->stopModal(_animDialBox, TRUE);
  _animDialBox->close();

  return 1;
}


/*
*	Updates AnimList
*/
void
PNFXAnimListParameter::_update(void)
{
}

//////////////////////////////////////////////////////////////////////////
};

