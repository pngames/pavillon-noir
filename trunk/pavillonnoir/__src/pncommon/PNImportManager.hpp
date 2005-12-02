/*
 * PNImportManager.hpp
 * 
 * Description :
 * PNImportManager declaration
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

#ifndef _PNIMPORTMANAGER_HPP_
# define _PNIMPORTMANAGER_HPP_

#include <list>
#include <map>
#include <boost/filesystem/path.hpp>

#include "pnevent.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNImportInterface;
class PNObject;
class IPNImportedObject;

class PNAPI			PNImportManager
{
  static PNImportManager*	_instance;

  PNImportManager();
  ~PNImportManager();
public:
  static PNImportManager*	getInstance();

  //////////////////////////////////////////////////////////////////////////

public:
  void					addImporter(PNImportInterface* importer);

  //////////////////////////////////////////////////////////////////////////

  IPNImportedObject*	import(const boost::filesystem::path& file, importtype type = PN_IMPORT_DEFAULT, bool copy = false);

  void					clean();

  //////////////////////////////////////////////////////////////////////////
private:
  typedef std::list<PNImportInterface*>									LIST_IMPORTER;
  typedef std::map<const boost::filesystem::path, IPNImportedObject*>	MAPIMPORTER;

  MAPIMPORTER			_mapObject;
  LIST_IMPORTER			_tabImporter[PN_IMPORT_NB_TYPES];
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNIMPORTMANAGER_HPP_*/
