/*
 * PNPlugin.cpp
 * 
 * Description :
 * PNPlugin definition
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

#include <iostream>
#include <boost/filesystem/operations.hpp>

#ifdef WIN32
# define DLOPEN(path)	LoadLibrary(path.native_file_string().c_str())
# define DLSYM			GetProcAddress
# define DLCLOSE		FreeLibrary
# define DLERROR(str)	pnperror(PN_LOGLVL_WARNING, "%s", (const pnchar*)str)
#else
# include <dlfcn.h>
# define DLOPEN(path)	dlopen(path.native_file_string().c_str(), RTLD_NOW)
# define DLSYM			dlsym
# define DLCLOSE		dlclose
# define DLERROR(str)	pnerror(PN_LOGLVL_WARNING, "%s", dlerror())
#endif

#include "pndefs.h"
#include "pnerror.h"
#include "pnplugins.h"

#include "PNPlugin.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNPlugin::PNPlugin(const fs::path& path) : _dlHandle(NULL), _dlFct(NULL), _plugDesc(NULL),
_file(fs::system_complete(path))
{
  reload();
}

PNPlugin::~PNPlugin()
{
  unload();
}

//////////////////////////////////////////////////////////////////////////

// renvoie l'interface de communication du plugin
PNPlugDesc*	PNPlugin::getPlugDesc() const
{
  return _plugDesc;
}

// recharge le plugin
pnbool		PNPlugin::reload()
{
  unload();

  if (!fs::exists(_file))
	return false;

  if (!(_dlHandle = DLOPEN(_file)))
  {
	DLERROR(_file.native_file_string().c_str());
	return (false);
  }

  try
  {
	if ((_dlFct = (pndlfct)DLSYM(_dlHandle, PNDLFCTNAMESTR)))
	{
	  if (!(_plugDesc = (PNPlugDesc*)_dlFct()))
	  {
		DLERROR("Recuperation de PNPlugDesc ");
		unload();
		return false;
	  }

	  return true;
	}
  }
  catch (...)
  {}

  DLERROR(_file.native_file_string().c_str());
  unload();

  return false;
}

// decharge le plugin
pnbool		PNPlugin::unload()
{		
  if (_dlHandle == NULL)
	return false;

  if (_plugDesc != NULL)
  {
  	delete _plugDesc;
	_plugDesc = NULL;
	return false;
  }

  DLCLOSE(_dlHandle);
  _dlHandle = NULL;
  _dlFct = NULL;

  return true;
}

//////////////////////////////////////////////////////////////////////////

pnbool
PNPlugin::isValid() const
{
  return getPlugDesc() != NULL;
}

const fs::path&
PNPlugin::getPath() const
{
  return _file;
}

//////////////////////////////////////////////////////////////////////////
};

