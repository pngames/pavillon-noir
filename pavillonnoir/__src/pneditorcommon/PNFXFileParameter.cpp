/*
 * PNFXFileParameter.cpp
 * 
 * Description :
 * PNFXFileParameter definition
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

#include "pneditorcommon.hpp"
#include "pnproperties.h"

#include "PNFXFileParameter.hpp"

using namespace std;

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  // Map
  FXDEFMAP(PNFXFileParameter) PNFXFileParameterMap[]={
	FXMAPFUNC(SEL_COMMAND,PNFXFileParameter::ID_BROWSE,PNFXFileParameter::onBrowse),
  };

  //////////////////////////////////////////////////////////////////////////
  FXIMPLEMENT(PNFXFileParameter,FXHorizontalFrame,PNFXFileParameterMap,ARRAYNUMBER(PNFXFileParameterMap))

	PNFXFileParameter::PNFXFileParameter(FXComposite* p, PNConfigurableParameter* param)
	: FXHorizontalFrame(p)
  {
	_field = new FXTextField(this, 24, NULL, 0, TEXTFIELD_NORMAL|FRAME_SUNKEN|FRAME_THICK|LAYOUT_SIDE_TOP);
	_button = new FXButton(this, "Browse", NULL, this, ID_BROWSE,FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X|LAYOUT_CENTER_Y);
	_param = param;
	update();
  }

  PNFXFileParameter::~PNFXFileParameter()
  {
  }

  void	PNFXFileParameter::create()
  {
	FXHorizontalFrame::create();
	_field->create();
	_button->create();
  }

  void	PNFXFileParameter::update()
  {
	boost::filesystem::path*	file = (boost::filesystem::path*)_param->getElem();
	_field->setText(file->native_file_string().c_str());
	_field->setEditable(_param->isEditable());

	return;
  }

  long	PNFXFileParameter::onBrowse(FXObject* obj,FXSelector sel, void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNFXFileParameter::onBrowse");
	FXFileDialog open(this, "Choose a file", SELECTFILE_MULTIPLE);

	if (open.execute())
	{
	  char buf[512] = "";
	  getcwd(buf, 512);
	
	  FXString strbuf(buf);
	  strbuf = strbuf.substitute('\\', '/');

	  FXString str = open.getFilename();
	  
	  pnerror(PN_LOGLVL_DEBUG, "strbuf=%s, str=%s", strbuf.text(), str.substitute('\\','/').text());
	  if ( str.substitute('\\','/').find(strbuf.text(), 0) == -1)
	  {
		FXMessageBox dbox(this, "File Error", "403");
		dbox.execute();
	  }
	  else
	  {
		_field->setText(str.replace(0, (FXint)strlen(buf) + 1, "").substitute('\\', '/').text());
		boost::filesystem::path* p = (boost::filesystem::path*)_param->getElem();
		//delete p;
		boost::filesystem::path* fsp = new boost::filesystem::path(_field->getText().text(), boost::filesystem::no_check);
		*p = *fsp;
		_param->getConfigurableObject()->update(_param);
	  }
	}

	return 1;
  }

  //////////////////////////////////////////////////////////////////////////
};
