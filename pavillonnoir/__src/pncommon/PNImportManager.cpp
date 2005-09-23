/*
 * PNImportManager.cpp
 * 
 * Description :
 * PNImportManager definition
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

#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif

#include <boost/filesystem/operations.hpp>

#include "pndefs.h"
#include "pnimport.h"

#include "PNImportManager.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNImportManager*	PNImportManager::_instance = NULL;

PNImportManager*
PNImportManager::getInstance()
{
  if (_instance == NULL)
	_instance = new PNImportManager();

  return _instance;
}

//////////////////////////////////////////////////////////////////////////

PNImportManager::PNImportManager()
{
  
}

PNImportManager::~PNImportManager()
{
  clean();
}

//////////////////////////////////////////////////////////////////////////

void
PNImportManager::addImporter(PNImportInterface* importer)
{
  _tabImporter[0].push_front(importer);
  _tabImporter[importer->getImportType()].push_front(importer);
}

//////////////////////////////////////////////////////////////////////////

PNObject*
PNImportManager::import(const fs::path& file, importtype type, bool copy)
{
  pnerror(PN_LOGLVL_INFO, "Import %s %i", file.string().c_str(), type);
  char buf[512];
  if (fs::exists(file))
	pnerror(PN_LOGLVL_INFO, "loading file %s from dir %s", file.string().c_str(), getcwd(buf, 511));

  MAPIMPORTER::const_iterator cit = _mapObject.find(file);

  if (cit != _mapObject.end())
  {
	if (!copy)
	  return cit->second;

	PNDEBUG_TODO("Faire une copie de l'objet");
  }

  LIST_IMPORTER&  lst = _tabImporter[type];

  PNObject*  obj = NULL;

  for (LIST_IMPORTER::iterator it = lst.begin(); it != lst.end(); it++)
  {
	obj = ((PNImportInterface*)(*it))->doImport(file);

	if (obj != NULL)
	{
	  std::cout << "add object : " << std::endl;

	  if (!copy)
		_mapObject[file] = obj;

	  break ;
	}
  }

  return obj;
}

void
PNImportManager::clean()
{
  for (MAPIMPORTER::iterator it = _mapObject.begin(); it != _mapObject.end(); it++)
	delete it->second;

  _mapObject.clear();
}

//////////////////////////////////////////////////////////////////////////
};
