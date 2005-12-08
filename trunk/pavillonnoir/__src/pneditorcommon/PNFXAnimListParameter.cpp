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
FXDEFMAP(PNFXAnimListParameter) PNFXAnimListParameterMap[]={
  FXMAPFUNC(SEL_COMMAND,PNFXAnimListParameter::ID_DELETE,PNFXAnimListParameter::onDelete),
  FXMAPFUNC(SEL_COMMAND,PNFXAnimListParameter::ID_ADD,PNFXAnimListParameter::onAdd)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXAnimListParameter,FXHorizontalFrame,PNFXAnimListParameterMap,ARRAYNUMBER(PNFXAnimListParameterMap))

PNFXAnimListParameter::PNFXAnimListParameter(FXComposite* p, PNConfigurableParameter* param)
: FXHorizontalFrame(p),
PNPropertiesGridParameter(param)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::PNFXAnimListParameter(FXComposite* p, PNConfigurableParameter* param)");
  _parent = p;
  _listBox =  new FXListBox(this, NULL, 0, LAYOUT_FILL_X | FRAME_SUNKEN | FRAME_THICK, 0,0,50,0);
  _buttonAdd = new FXButton(this, "Add", NULL, this, ID_ADD,FRAME_RAISED|FRAME_THICK);
  _buttonDelete = new FXButton(this, "Delete", NULL, this, ID_DELETE,FRAME_RAISED|FRAME_THICK);
  buildList();
}

PNFXAnimListParameter::~PNFXAnimListParameter()
{
  delete _buttonAdd;
  delete _buttonDelete;
  delete _listBox;
}
//////////////////////////////////////////////////////////////////////////

void
PNFXAnimListParameter::create()
{
  FXHorizontalFrame::create();
  _buttonDelete->create();
  _buttonAdd->create();
  _listBox->create();
}

/*
*	Builds AnimList list for current parameter.
*/
void
PNFXAnimListParameter::buildList(void)
{
  PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem();

  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::buildList");
  _listBox->clearItems();

  for (PN3DSkeletonObject::AnimationVector::iterator it = v->begin(); it != v->end(); ++it)
  {
	PN3DSkeletonAnimation&	skanim = *it;

	std::string s = skanim.anim->getFile()->string();

	if (s.size() > 29)
	  s = s.substr(0, 10) + "[...]" + s.substr(s.size()-15, s.size());

	_listBox->appendItem(s.c_str(), NULL, skanim.anim);
  }

  _listBox->setNumVisible(_listBox->getNumItems()< 5 ? _listBox->getNumItems() : 5);
  pnerror(PN_LOGLVL_DEBUG, "End of PNFXAnimListParameter::buildList");
}

/*
*	Deletes selected link.
*/
long
PNFXAnimListParameter::onDelete(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::onDelete");
  if (_listBox->getNumItems() != 0)
  {
	PN3DSkeletonObject::AnimationVector* v = (PN3DSkeletonObject::AnimationVector*)_param->getElem(); 

	v->erase(v->begin() + _listBox->getCurrentItem());
	PNConfigurableObject* co = _param->getConfigurableObject();
	co->setModified();
	update();
  }

  return 1;
}

long
PNFXAnimListParameter::onAdd(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::onAdd");
  FXFileDialog fd(this, "Choose animation file");

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
	  FXMessageBox::error(this, MBOX_OK, "Path Error", "An error occured. Please check file path.");	  	
	}
	else
	{
	  fs::path p(str.replace(0, (FXint)strlen(buf) + 1, "").text(), fs::no_check);
	  PN3DAnimation* anim = (PN3DAnimation*)PNImportManager::getInstance()->import(p, PN_IMPORT_3DANIMATION);

	  if (anim != NULL)
	  {
		v->push_back(PN3DSkeletonAnimation(anim, NULL));

		std::string s = v->at(i).anim->getFile()->string();
		if (s.size() > 29)
		  s = s.substr(0, 10) + "[...]" + s.substr(s.size()-15, s.size());
		_listBox->appendItem(s.c_str(), NULL, v->at(i).anim);
		_listBox->setNumVisible(_listBox->getNumItems()<5 ? _listBox->getNumItems() : 5);
		PNConfigurableObject* co = _param->getConfigurableObject();
		co->setModified();
	  }
	  else
	  {
		FXMessageBox::error(this, MBOX_OK, "File Error", "An error occured. Please check file format.");
	  }
	}
  }
  return 1;
}

/*
*	Updates AnimList
*/
void
PNFXAnimListParameter::update(void)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXAnimListParameter::update");
  PNConfigurableObject* co = _param->getConfigurableObject();
  buildList();
  co->update(_param);
  _listBox->sortItems();
}

//////////////////////////////////////////////////////////////////////////
};
