/*
 * PNIImporter.cpp
 * 
 * Description :
 * PNIImporter definition
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

#include "PNIImporter.hpp"

namespace fs = boost::filesystem;
using namespace std;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNIImporter::PNIImporter()
{
}

PNIImporter::~PNIImporter()
{
}

//////////////////////////////////////////////////////////////////////////

pnbool
PNIImporter::isManaged(const std::string& path)
{
  ifstream	file(path.c_str(), ifstream::binary);

  char	buff[256];

  file.read(buff, _magicSize);

  return strncmp(buff, _magic, _magicSize) == 0;
}

//////////////////////////////////////////////////////////////////////////
};
