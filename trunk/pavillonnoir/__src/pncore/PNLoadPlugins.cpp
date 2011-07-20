/*
 * PNLoadPlugins.cpp
 * 
 * Description :
 * PNLoadPlugins definition
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
#include "pndefs.h"

#include "PNLoadPlugins.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {

  PNLoadPlugins::PNLoadPlugins()
  {
	_plist = PNPluginManager::getInstance(); 
  }

  PNLoadPlugins::~PNLoadPlugins()
  {
  }

  /*!
  \brief
  Add a directory who contains plugins to load
  \param dir
  Boost path to the directory
  */
  void PNLoadPlugins::addDirectory(const fs::path& dir)
  {
	pnuint error = _plist->addDirectory(dir, false);

	if (error != PNEC_SUCCESS)
	  pnerror(PN_LOGLVL_ERROR, "%s: %s", dir.native_file_string().c_str(), pnGetErrorString(error));
  }

  /*!
  \brief
   Add a single one plugin file from plugins default directory to load
  \param plugName
   Plugin name
  */
  void  PNLoadPlugins::addDefaultPlugin(const std::string& plugName)
  {
  	pnuint error = _plist->addDefaultPlugin(plugName);

	if (error != PNEC_SUCCESS)
	  pnerror(PN_LOGLVL_ERROR, "%s: %s", plugName.c_str(), pnGetErrorString(error));
  }

  /*!
  \brief
   Add a single one plugin file to load
  \param file
   Boost path to the plugin file
  */
  void PNLoadPlugins::addPlugin(const fs::path& file)
  {
	pnuint error = _plist->addPlugin(file);

	if (error != PNEC_SUCCESS)
	  pnerror(PN_LOGLVL_ERROR, "%s: %s", file.native_file_string().c_str(), pnGetErrorString(error));
  }

  /*!
  \brief
   Launch every plugins which are load
  */
  void PNLoadPlugins::launchPlugins()
  {
	for (PNPluginManager::iterator it = _plist->begin(); it != _plist->end(); it++)
	{
	  launchPlugin(*it);
	}
  }

  /*!
  \brief
   Launch only one plugin which is load
  \param pl
   Pointer to the plugin to launch
  */
  void PNLoadPlugins::launchPlugin(PNPlugin* pl)
  {
	PNPlugDesc*	desc = pl->getPlugDesc();

	if (desc == NULL)
	{
	  std::cerr << "Error: Impossible de charger la description du plugin " << pl->getPath().native_file_string() << std::endl;
	  return;
	}

	std::cout << "Name = " << desc->getName() << std::endl;
	std::cout << "Version = " << desc->getVersion() << std::endl;
	std::cout << "Nb Interfaces = " << desc->getNbInterface() << std::endl;

	for (pnuint i = 0; i < desc->getNbInterface(); i++)
	{
	  std::cout << "[Loading Interface " << desc->getName() << " ...]" << std::endl;
	  PNInterface*	interf = desc->getInterface(i);

	  if (interf == NULL)
	  {
		std::cerr << "Error: Impossible de charger l'interface du plugin " << pl->getPath().native_file_string() << std::endl;
		return;
	  }

	  try	{ interf->init(); }
	  catch (...)
	  {
		pnerror(PN_LOGLVL_WARNING, "%s interface %i", desc->getName(), i);
	  }
	}
  }
}
