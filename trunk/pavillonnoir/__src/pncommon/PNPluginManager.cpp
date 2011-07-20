/*
 * PNPluginManager.cpp
 * 
 * Description :
 * PNPluginManager definition
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

#include "pndefs.h"
#include "pnplugins.h"

#include "PNPluginManager.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNPluginManager*	PNPluginManager::_instance = NULL;

PNPluginManager*	PNPluginManager::getInstance()
{
  if (_instance == NULL)
	_instance = new PNPluginManager();

  return _instance;
}
//////////////////////////////////////////////////////////////////////////

PNPluginManager::PNPluginManager()
{
  
}

PNPluginManager::~PNPluginManager()
{
  for (iterator  it = begin(); it != end(); it++)
	delete*it;
}

//////////////////////////////////////////////////////////////////////////

pnint		PNPluginManager::addDefaultPlugin(const std::string& plugName)
{
#ifdef DEBUG
  return addPlugin(DEF::defaultPluginFilePath + plugName + "-dbg.pnp");
#else
  return addPlugin(DEF::defaultPluginFilePath + plugName + ".pnp");
#endif
}

pnint		PNPluginManager::addPlugin(const fs::path& file)
{
  pnerror(PN_LOGLVL_INFO, "Loading plugin: %s ...", file.native_file_string().c_str());

  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;

  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  PNPlugin*		plugin = new PNPlugin(file);

  if (!plugin->isValid())
  {
	delete plugin;
	return PNEC_PLUGIN_INVALID;
  }

  pnerror(PN_LOGLVL_INFO, "%s loading succed.", file.native_file_string().c_str());

  push_front(plugin);

  return PNEC_SUCCESS;
}

pnint			PNPluginManager::addDirectory(const fs::path& dir, pnbool recursive)
{
  pnerror(PN_LOGLVL_INFO, "Loading plugin directory: %s ...", dir.native_file_string().c_str());

  if (!fs::exists(dir))
	return PNEC_DIRECTORY_NOT_FOUND;

  if (!fs::is_directory(dir))
	return PNEC_NOT_A_DIRECTORY;

  fs::directory_iterator end_iter;
  for (fs::directory_iterator dir_itr(dir); dir_itr != end_iter; ++dir_itr)
  {
	fs::path path = *dir_itr;

	if (fs::is_directory(path))
	{
	  if (recursive)
		addDirectory(path, true);
	}
	else
	  addPlugin(path);
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};

