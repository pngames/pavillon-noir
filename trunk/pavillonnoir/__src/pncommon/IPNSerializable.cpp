/*
 * IPNSerializable.cpp
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
 
#include <fstream>
#include <boost/filesystem/operations.hpp>

#include "pndefs.h"

#include "IPNSerializable.hpp"

using namespace PN;
using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

IPNSerializable::IPNSerializable()
{
  _hasFile = false;
}

//////////////////////////////////////////////////////////////////////////

/**
 * @brief Get 3DObject associated file for serialize/unserialize system.
 *
 * @return File
 */
boost::filesystem::path*
IPNSerializable::getFile()
{
  return _hasFile ? &_file : NULL;
}

/**
 * @brief	Modify 3DObject associated file for serialize/unserialize system
 *
 * @param	file		File
 * @return	void
 */
void
IPNSerializable::setFile(const boost::filesystem::path& file)
{
  _file = fs::path(file.string(), fs::native);
  _hasFile = true;
}

//////////////////////////////////////////////////////////////////////////

/**
 * @brief		Load object from file
 *
 * @param file	File to load
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
 *
 * @see			pnGetErrorString
 */
pnint
IPNSerializable::unserializeFromFile(const boost::filesystem::path& file)
{
  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;

  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  setFile(file);

  ifstream	i(_file.string().c_str(), ifstream::binary);

  return unserializeFromStream(i);
}

pnint
IPNSerializable::unserializeFromPath(const std::string& file)
{
  return unserializeFromFile(fs::path(file, fs::native));
}

/**
 * @brief		Load object from stream
 *
 * @param i		Stream to load from
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
 *
 * @see			pnGetErrorString
 */
pnint
IPNSerializable::unserializeFromStream(istream& i)
{
  return PNEC_NOT_IMPLEMENTED;
}

/**
* @brief		Load object
*
* @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
*
* @see			pnGetErrorString
*/
pnint
IPNSerializable::unserialize()
{
  return unserializeFromFile(_file);
}

/**
 * @brief		Save object to file
 *
 * @param file	File to save
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
 *
 * @see			pnGetErrorString
 */
pnint
IPNSerializable::serializeInFile(const boost::filesystem::path& file)
{
  if (fs::exists(file) && fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  setFile(file);

  ofstream	o(file.string().c_str(), ofstream::binary);

  return serializeInStream(o);
}

pnint
IPNSerializable::serializeInFile(const std::string& file)
{
  return serializeInFile(fs::path(file, fs::native));
}

/**
 * @brief		Save object to stream
 *
 * @param o		Stream to load from
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
 *
 * @see			pnGetErrorString
 */
pnint
IPNSerializable::serializeInStream(ostream& o)
{
  return PNEC_NOT_IMPLEMENTED;
}

/**
* @brief		Save object
*
* @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
*
* @see			pnGetErrorString
*/
pnint
IPNSerializable::serialize()
{
  return serializeInFile(_file);
}

//////////////////////////////////////////////////////////////////////////
}
