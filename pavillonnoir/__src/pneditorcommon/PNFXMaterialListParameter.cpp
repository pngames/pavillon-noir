/*
 * PNFXMaterialListParameter.cpp
 * 
 * Description :
 * PNFXMaterialListParameter definition
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

#include "PNImportManager.hpp"
#include "PNGLContext.hpp"
#include "PN3DMaterial.hpp"
#include "PN3DObject.hpp"
#include "PN3DModel.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNPropertiesGrid.hpp"
#include "PNFXMaterialListParameter.hpp"

using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXMaterialListParameter) PNFXMaterialListParameterMap[]={
  FXMAPFUNC(SEL_COMMAND,PNFXMaterialListParameter::ID_DELETE,PNFXMaterialListParameter::onDelete),
  FXMAPFUNC(SEL_COMMAND,PNFXMaterialListParameter::ID_ADD,PNFXMaterialListParameter::onAdd)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXMaterialListParameter,FXHorizontalFrame,PNFXMaterialListParameterMap,ARRAYNUMBER(PNFXMaterialListParameterMap))

PNFXMaterialListParameter::PNFXMaterialListParameter(FXComposite* p, PNConfigurableParameter* param)
: FXHorizontalFrame(p)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXMaterialListParameter::PNFXMaterialListParameter(FXComposite* p, PNConfigurableParameter* param)");
  _parent = p;
  _param = param;
  _changed = FALSE;
  _listBox = new FXListBox(this, NULL, 0, LAYOUT_FILL_X | FRAME_SUNKEN | FRAME_THICK, 0,0,50,0);
  _buttonAdd = new FXButton(this, "Add", NULL, this, ID_ADD,FRAME_RAISED|FRAME_THICK);
  _buttonDelete = new FXButton(this, "Delete", NULL, this, ID_DELETE,FRAME_RAISED|FRAME_THICK);
  update();
}

PNFXMaterialListParameter::~PNFXMaterialListParameter()
{
  delete _buttonAdd;
  delete _buttonDelete;
  delete _listBox;
}
//////////////////////////////////////////////////////////////////////////

void	PNFXMaterialListParameter::create()
{
  FXHorizontalFrame::create();
  _listBox->create();
  _buttonDelete->create();
  _buttonAdd->create();
  return;
}

/*
*	Builds MaterialList list for current parameter.
*/
void	PNFXMaterialListParameter::buildList(void)
{
  PN3DObject::VectorMaterial* v = (PN3DObject::VectorMaterial*)_param->getElem();

  _listBox->clearItems();

  for (PN3DObject::VectorMaterial::iterator it = v->begin(); it != v->end(); ++it)
  {
	PN3DMaterial*	material = *it;
	/*
	boost::filesystem::path* f = v->at(i)->getFile();
	if (fs::exists(*f))
	{
	std::string s = f->string();
	if (s.size() > 29)
	s = s.substr(0, 10) + "[...]" + s.substr(s.size()-15, s.size());
	_listBox->appendItem(s.c_str(), NULL, v->at(i));
	}
	else
	{
	pnerror(PN_LOGLVL_WARNING, "Material does not exist.");
	}
	*/

	std::string s = material->getFile()->string();
	if (s.size() > 29)
	  s = s.substr(0, 10) + "[...]" + s.substr(s.size()-15, s.size());
	_listBox->appendItem(s.c_str(), NULL, material);

  }

  _listBox->setNumVisible(_listBox->getNumItems()<5 ? _listBox->getNumItems() : 5);
}

/*
*	Deletes selected link.
*/
long	PNFXMaterialListParameter::onDelete(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXMaterialListParameter::onDelete");
  if (_listBox->getNumItems() != 0)
  {
	PN3DObject::VectorMaterial* v = (PN3DObject::VectorMaterial*)_param->getElem(); 

	v->erase(v->begin() + _listBox->getCurrentItem());

	PNConfigurableObject* co = _param->getConfigurableObject();
	co->setModified();
	update();
  }

  return 1;
}

long	PNFXMaterialListParameter::onAdd(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXMaterialListParameter::onAdd");
  FXFileDialog fd(this, "Choose material file");

  if (fd.execute())
  {
	PN3DObject::VectorMaterial* v = (PN3DObject::VectorMaterial*)_param->getElem(); 
	PN3DObject::VectorMaterial::size_type i = v->size();
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
	  EDITOR::PNGLContext::getInstance()->makeViewerCurrent();
	  fs::path p(str.replace(0, (FXint)strlen(buf) + 1, "").text(), fs::no_check);
	  PN3DMaterial* mat = (PN3DMaterial*)PNImportManager::getInstance()->import(p, PN_IMPORT_MATERIAL);

	  if (mat != NULL)
	  {
		v->push_back(mat);

		std::string s = v->at(i)->getFile()->string();
		if (s.size() > 29)
		  s = s.substr(0, 10) + "[...]" + s.substr(s.size()-15, s.size());
		_listBox->appendItem(s.c_str(), NULL, v->at(i));
		_listBox->setNumVisible(_listBox->getNumItems() < 5 ? _listBox->getNumItems() : 5 );
		PNConfigurableObject* co = _param->getConfigurableObject();
		co->setModified();
	  }
	  else
	  {
		FXMessageBox::error(this, MBOX_OK, "File Error", "An error occured. Please check file format.");
	  }
	  EDITOR::PNGLContext::getInstance()->makeViewerNonCurrent();
	  _param->getConfigurableObject()->update(_param);
	}
  }
  return 1;
}

long	PNFXMaterialListParameter::onReset(FXObject* obj,FXSelector sel,void* ptr)
{
  return 1;
}


/*
*	Updates MaterialListlist
*/
void	PNFXMaterialListParameter::update(void)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXMaterialListParameter::update");
  PNConfigurableObject* co = _param->getConfigurableObject();
  buildList();
  co->update(_param);
  _listBox->sortItems();
  return;
}

//////////////////////////////////////////////////////////////////////////
};
