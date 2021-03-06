/*
 * IPNSerializable.hpp
 *
 * Description :
 * Base interface for serialization support
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

#ifndef _IPNSERIALIZATION_HPP_
# define _IPNSERIALIZATION_HPP_

#include <iostream>
#include <string>

#include <boost/filesystem/path.hpp>

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNAPI							IPNSerializable
{
protected:
  IPNSerializable();
  virtual ~IPNSerializable() {}

  //////////////////////////////////////////////////////////////////////////

public:
  std::string*						getPath();
  void								setPath(const std::string& path);

  //////////////////////////////////////////////////////////////////////////

protected:
  /// Load object from file
  virtual pnint						unserializeFromFile(const boost::filesystem::path& file);
  /// Save object to file
  virtual pnint						serializeInFile(const boost::filesystem::path& file);

public:
  /// Load object from path
  virtual pnint						unserializeFromPath(const std::string& file);
  /// Load object from stream
  virtual pnint						unserializeFromStream(std::istream& i);
  /// Load object
  virtual pnint						unserialize();
  /// Save object to path
  virtual pnint						serializeInPath(const std::string& file);
  /// Save object to stream
  virtual pnint						serializeInStream(std::ostream& o);
  /// Save object
  virtual pnint						serialize();
protected:
  pnbool							_hasFile;
  /// File that represent object
  std::string						_path;
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*!_IPNSERIALIZATION_HPP_*/

