/*
 * PNIModelImporter.cpp
 * 
 * Description :
 * PNIModelImporter definition
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
#include "pnplugins.h"

#include "PNIModelImporter.hpp"
#include "PNI3DModel.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNIModelImporter::PNIModelImporter()
{
  
}

PNIModelImporter::~PNIModelImporter()
{
  
}

//////////////////////////////////////////////////////////////////////////

pnbool  	PNIModelImporter::isManaged(const fs::path& path)
{
  FILE*		file = fopen(path.native_file_string().c_str(), "r");

  if (file == NULL)
	return false;

  pnmHeader_t	header;
  fread(&header, sizeof(header), 1, file);

  fclose(file);

  return strncmp(header.magic, PNM_MAGIC, PNM_MAGIC_SIZE) == 0;
}

PNObject*	PNIModelImporter::doImport(const fs::path& path)
{
  pnerror(PN_LOGLVL_INFO, "Import %s", path.string().c_str());

  PNObject* obj = new PNI3DModel();

  pnuint error = obj->unserialize(path);

  if (error != PNEC_SUCCES)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", path.string().c_str(), pnGetErrorString(error));
	delete obj;
	obj = NULL;
  }

  return obj;
}

importtype	PNIModelImporter::getImportType()
{
  return PN_IMPORT_3DMODEL;
}

//////////////////////////////////////////////////////////////////////////
}
