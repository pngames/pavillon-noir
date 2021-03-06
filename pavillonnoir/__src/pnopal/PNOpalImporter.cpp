/*
 * PNOpalImporter.cpp
 * 
 * Description :
 * PNOpalImporter definition
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

#include <opal/opal.h>

#include "pndefs.h"
#include "pnplugins.h"

#include "PNOpalImporter.hpp"

#include "PNPhysicsInterface.hpp"
#include "PNOpalObject.hpp"
#include "PNOpal.hpp"

namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNOpalImporter::PNOpalImporter()
{
  _name = _label = "PNP Importer";
}

PNOpalImporter::~PNOpalImporter()
{

}

//////////////////////////////////////////////////////////////////////////

pnbool
PNOpalImporter::isManaged(const std::string& path)
{
  return true;
}

IPNImportedObject*
PNOpalImporter::doImport(const std::string& path)
{
  pnerror(PN_LOGLVL_INFO, "Import %s", path.c_str());

  PNOpalObject* physicalObject = new PNOpalObject((opal::Simulator*)((PNOpal*)PNPhysicsInterface::getInstance())->getSimulation());

  pnuint error = physicalObject->unserializeFromPath(path);

  if (error != PNEC_SUCCESS)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", path.c_str(), pnGetErrorString(error));
	delete physicalObject;
	physicalObject = NULL;
  }

  return physicalObject;
}

importtype
PNOpalImporter::getImportType()
{
  return PN_IMPORT_PHYSICS;
}

//////////////////////////////////////////////////////////////////////////
};
