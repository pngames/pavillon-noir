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
#include "pnresources.h"

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

/*// Map
FXDEFMAP(PNFXAnimListParameter) PNFXAnimListParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXAnimListParameter::ID_EDIT, PNFXAnimListParameter::onEdit)
};*/

//////////////////////////////////////////////////////////////////////////
//FXIMPLEMENT(PNFXAnimListParameter, PNFXListParameter, PNFXAnimListParameterMap, ARRAYNUMBER(PNFXAnimListParameterMap))
FXIMPLEMENT(PNFXAnimListParameter, PNFXListParameter, NULL, 0)

PNFXAnimListParameter::PNFXAnimListParameter(FXComposite* p, PNConfigurableParameterList* param) :
PNFXListParameter(p, param)
{ 
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

bool
PNFXAnimListParameter::_deleteObject(FXint index)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::deleteObject");
  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem(); 

  v->erase(v->begin() + index);
  _update();

  return true;
}

PN3DAnimation*  
PNFXAnimListParameter::openAnim()
{
  FXFileDialog fd(this, "Choose animation file to add");
  fd.setPatternList("PN Animations (*.pna)\nAll Files (*)");
  
  FXString* dir_path = new FXString(fd.getDirectory().text());
  dir_path->append("/");
  dir_path->append(DEF::animationFilePath.c_str());
  fd.setDirectory(*dir_path);

  if (fd.execute())
  {
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
		return anim;
	  else
		FXMessageBox::error(this, MBOX_OK, "File Error", "An error occurred. Please check file format.");
	}
  }

  return NULL;
}

bool
PNFXAnimListParameter::_addNewObject(FXint index)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::addNewObject");
  PN3DAnimation* anim = openAnim();

  if (anim != NULL)
  {  
	PN3DSkeletonAnimation* skanim = new PN3DSkeletonAnimation(anim, NULL);

	_skanim = skanim;
	if (showAnim(skanim))
	{
	  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem(); 

	  v->insert(v->begin() + index, _skanim);
	  return true;
	}
  }

  return false;
}

FXuint
PNFXAnimListParameter::showAnim(PNConfigurableObject* skanim)
{
  _animDialBox =  new FXDialogBox(this, "Add Anim", DECOR_TITLE | DECOR_BORDER);
  FXVerticalFrame* vframe = new FXVerticalFrame(_animDialBox, LAYOUT_FILL_X | LAYOUT_FILL_Y);
  FXGroupBox* group = new FXGroupBox(vframe, "Animation properties", LAYOUT_FILL_X | LAYOUT_FILL_Y | FRAME_GROOVE);
  PNPropertiesGrid* grid = new PNPropertiesGrid(group);
  
  _animDialBox->create();
  vframe->create();
  group->create();
  
  grid->setObject(skanim);

  new FXHorizontalSeparator(vframe, LAYOUT_FILL_X);
  FXHorizontalFrame*	buttons = new FXHorizontalFrame(vframe,LAYOUT_FILL_X | LAYOUT_FILL_Y);
  new FXButton(buttons, "&Ok", NULL, _animDialBox, FXDialogBox::ID_ACCEPT, BUTTON_DEFAULT | LAYOUT_RIGHT | LAYOUT_CENTER_Y | FRAME_RAISED | FRAME_THICK, 10, 10, 0, 0, 20, 20);
  new FXButton(buttons, "&Cancel", NULL, _animDialBox, FXDialogBox::ID_CANCEL, BUTTON_DEFAULT | LAYOUT_RIGHT | LAYOUT_CENTER_Y | FRAME_RAISED | FRAME_THICK, 10, 10, 0, 0, 20, 20);
  buttons->create();
  
  // FIXME : dialog box does not automatically resize, so we force it. Correct that.
  _animDialBox->setHeight(180);
  _animDialBox->setWidth(170);
  
  return _animDialBox->execute();
}

bool
PNFXAnimListParameter::_editObject(FXint index)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::editObject");
  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem();

  showAnim((*v)[index]);

  return true;
}

/*
*	Updates AnimList
*/
void
PNFXAnimListParameter::_update(void)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::update");
  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem();

  _listBox->clearItems();

  for (PN3DSkeletonObject::AnimationVector::iterator it = v->begin(); it != v->end(); ++it)
  {
	PN3DSkeletonAnimation*	skanim = *it;

	_listBox->appendItem(FXFile::name(skanim->anim->getFile()->c_str()), NULL,  skanim->anim);
  }

  _listBox->setNumVisible(_listBox->getNumItems()< 5 ? _listBox->getNumItems() : 5);
}

/*
*	Updates AnimList, sets the current selection to index
*/
void
PNFXAnimListParameter::_update(pnuint index)
{
  _update();
  _setCurrentItem(index);
}
//////////////////////////////////////////////////////////////////////////
};
