/*
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
#include <string>
#include <direct.h>
#include <stdio.h>
#include "pndefs.h"
#include "pnerror.h"
#include "pnplugins.h"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "PNLoadPlugins.hpp"
#include "PNGameInterface.hpp"

using namespace PN;
namespace fs = boost::filesystem;
using boost::filesystem::path;
int main (char **argc,int argv)
{
  char c;
  int errorCode = PNEC_SUCCES;
#ifdef WIN32
  chdir("../");
#else
  chdir("../../../__binaries");
#endif
  fs::path currentDirectory = fs::current_path();
  std::cout << "currentDirectory : " << currentDirectory.string() << std::endl;
  PNLoadPlugins* loadPlugins = new PNLoadPlugins();
#ifdef WIN32
  loadPlugins->addPlugin("win32/plugins/Debug/pnscript-dbg.pnp");
#else
# ifdef DEBUG
  loadPlugins->addPlugin("../__managers/eclipse3/pnglrenderer/Debug/pnscript.so");
# else
  loadPlugins->addPlugin("../__managers/eclipse3/pnglrenderer/Release/pnscript.so");
# endif
#endif
  loadPlugins->launchPlugins();
  PNGameInterface* game = (PNGameInterface*)PNGameInterface::getInstance();
  errorCode = game->run();
  if (errorCode != PNEC_SUCCES)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s\n","Init file" , pnGetErrorString(errorCode));
  }
  fread(&c, 1, 1, stdin);
  return 0;
} 


