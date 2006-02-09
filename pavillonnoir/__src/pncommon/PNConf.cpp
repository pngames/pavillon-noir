/*
* PNConf.cpp
* 
* Description :
* PNConf definition
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

#include <cstdlib>
#include <boost/filesystem/operations.hpp>

#ifdef WIN32
# include <Windows.h>
# include <shlobj.h>
#endif

#include "pndefs.h"
#include "pnresources.h"

#include "PNConf.hpp"

using namespace PN;
namespace fs = boost::filesystem;

//////////////////////////////////////////////////////////////////////////

#define PNCONFPATH	".pavillon-noir"

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNConf* PNConf::_instance = NULL;

PNConf*
PNConf::getInstance()
{
  if (_instance == NULL)
	_instance = new PNConf();

  return _instance;
}

PNConf::PNConf()
{
#ifdef WIN32
  TCHAR szPath[MAX_PATH];
  if (SUCCEEDED(SHGetFolderPath(NULL,
	CSIDL_APPDATA|CSIDL_FLAG_CREATE,
	NULL, 0, szPath)))
	_homePath = szPath;
#else
  _homePath = getenv("HOME");
#endif

  _confPath = _homePath + PATHSEP + PNCONFPATH;

  fs::path	confPath(_confPath, fs::no_check);

  if (!fs::exists(confPath))
	fs::create_directory(confPath);

  //////////////////////////////////////////////////////////////////////////
  
  _loadDefaultConf();
}

PNConf::~PNConf()
{
  
}

std::string
PNConf::getConfPath(const std::string file/* = ""*/)
{
  return _confPath + PATHSEP + file;
}

//////////////////////////////////////////////////////////////////////////

void
PNConf::_copyDirectory(const fs::path& path, const std::string& target)
{
  fs::directory_iterator end_iter;

  for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr)
  {
	if (fs::is_directory(*dir_itr))
	{
	  if (dir_itr->leaf() != ".svn")
		_copyDirectory(*dir_itr, target + dir_itr->leaf() + PATHSEP);
	}
	else
	{
	  fs::path targetFile(target + dir_itr->leaf(), fs::no_check);

	  if (!fs::exists(targetFile))
		copy_file(*dir_itr, targetFile);
	}
  }
}

void
PNConf::_loadDefaultConf()
{
  _copyDirectory(fs::path(DEF::confFilePath, fs::no_check), _confPath + PATHSEP);
}

//////////////////////////////////////////////////////////////////////////
};

