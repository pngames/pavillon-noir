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

/*// Map
FXDEFMAP(PNFXMaterialListParameter) PNFXMaterialListParameterMap[]=
{
  
};*/

//////////////////////////////////////////////////////////////////////////
//FXIMPLEMENT(PNFXMaterialListParameter, PNFXListParameter, PNFXMaterialListParameterMap, ARRAYNUMBER(PNFXMaterialListParameterMap))
FXIMPLEMENT(PNFXMaterialListParameter, PNFXListParameter, NULL, 0)

PNFXMaterialListParameter::PNFXMaterialListParameter(FXComposite* p, PNConfigurableParameterList* param)
: PNFXListParameter(p, param)
{
}

PNFXMaterialListParameter::~PNFXMaterialListParameter()
{
}

//////////////////////////////////////////////////////////////////////////

void	PNFXMaterialListParameter::create()
{
  PNFXListParameter::create();
}

bool
PNFXMaterialListParameter::_deleteObject(FXint index)
{
  PN3DObject::VectorMaterial* v = (PN3DObject::VectorMaterial*)_param->getElem(); 

  v->erase(v->begin() + index);

  return true;
}

bool
PNFXMaterialListParameter::_addNewObject(FXint index)
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
	  PN3DMaterial* mat = (PN3DMaterial*)PNImportManager::getInstance()->import(
		str.replace(0, (FXint)strlen(buf) + 1, "").text(), PN_IMPORT_MATERIAL);

	  if (mat != NULL)
	  {
		v->push_back(mat);

		std::string s = *v->at(i)->getFile();
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

/*
*	Updates MaterialListlist
*/
void
PNFXMaterialListParameter::_update(void)
{
  PN3DObject::VectorMaterial* v = (PN3DObject::VectorMaterial*)_param->getElem();

  _listBox->clearItems();

  for (PN3DObject::VectorMaterial::iterator it = v->begin(); it != v->end(); ++it)
  {
	PN3DMaterial*	material = *it;

	_listBox->appendItem(FXFile::name(material->getFile()->c_str()), NULL, material);
  }
}

//////////////////////////////////////////////////////////////////////////
};
