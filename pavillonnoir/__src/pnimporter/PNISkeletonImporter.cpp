/*
 * PNISkeletonImporter.cpp
 * 
 * Description :
 * PNISkeletonImporter definition
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

#include <fstream>

#include "pndefs.h"
#include "pnplugins.h"

#include "PNISkeletonImporter.hpp"
#include "PNI3DSkeleton.hpp"

namespace fs = boost::filesystem;
using namespace std;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNISkeletonImporter*	PNISkeletonImporter::_instance = NULL;

PNISkeletonImporter::PNISkeletonImporter(void)
{
  _name = _label = "PNS Importer";

  _magic = PNS_MAGIC;
  _magicSize = PNS_MAGIC_SIZE;
}

PNISkeletonImporter::~PNISkeletonImporter(void)
{
  
}

//////////////////////////////////////////////////////////////////////////

IPNImportedObject*
PNISkeletonImporter::doImport(const std::string& path)
{
  PNI3DSkeleton* obj = new PNI3DSkeleton();

  pnuint error = obj->unserializeFromPath(path);

  if (error != PNEC_SUCCESS)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", path.c_str(), pnGetErrorString(error));
	delete obj;
	obj = NULL;
  }

  return obj;
}

importtype
PNISkeletonImporter::getImportType()
{
  return PN_IMPORT_3DSKELETON;
}

//////////////////////////////////////////////////////////////////////////
};
