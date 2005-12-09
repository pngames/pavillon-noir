/*
 * PNIMaterialImporter.cpp
 * 
 * Description :
 * PNIMaterialImporter definition
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
#include <boost/filesystem/operations.hpp>

#include "pndefs.h"
#include "pnplugins.h"
#include "pnrender.h"
#include "pnresources.h"

#include "PNI3DMaterial.hpp"
#include "PNIMaterialImporter.hpp"
#include "PNIException.hpp"

namespace fs = boost::filesystem;
using namespace std;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNIMaterialImporter::PNIMaterialImporter()
{
  _label = "PNT Importer";

  _magic = PNT_MAGIC;
  _magicSize = PNT_MAGIC_SIZE;
}

PNIMaterialImporter::~PNIMaterialImporter()
{

}

//////////////////////////////////////////////////////////////////////////

IPNImportedObject*
PNIMaterialImporter::doImport(const fs::path& path)
{
  pnerror(PN_LOGLVL_INFO, "Import %s", path.string().c_str());

  PNI3DMaterial* mat = new PNI3DMaterial();

  pnuint error = mat->unserializeFromPath(path.string());

  if (error != PNEC_SUCCESS)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", path.string().c_str(), pnGetErrorString(error));
	delete mat;
	mat = NULL;
  }

  return mat;
}

importtype
PNIMaterialImporter::getImportType()
{
  return PN_IMPORT_MATERIAL;
}

//////////////////////////////////////////////////////////////////////////
};
