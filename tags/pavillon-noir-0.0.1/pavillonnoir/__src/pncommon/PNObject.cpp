/*
 * PNObject.cpp
 * 
 * Description :
 * PNObject definition
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

#include "PNObject.hpp"

using namespace PN;
using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

/**
 * @brief		Load object from file
 *
 * @param file	File to load
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
 *
 * @see			pnGetErrorString
 */
pnint	PNObject::unserialize(const boost::filesystem::path& file)
{
  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;

  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  ifstream	i(file.string().c_str(), ifstream::binary);

  return unserialize(i);
}

/**
 * @brief		Load object from stream
 *
 * @param i		Stream to load from
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
 *
 * @see			pnGetErrorString
 */
pnint	PNObject::unserialize(istream& i)
{
  return PNEC_NOT_IMPLEMENTED;
}

/**
* @brief		Load object
*
* @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
*
* @see			pnGetErrorString
*/
pnint	PNObject::unserialize()
{
  return PNEC_NOT_IMPLEMENTED;
}

/**
 * @brief		Save object to file
 *
 * @param file	File to save
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
 *
 * @see			pnGetErrorString
 */
pnint	PNObject::serialize(const boost::filesystem::path& file)
{
  if (fs::exists(file))
	if (fs::is_directory(file))
	  return PNEC_NOT_A_FILE;

  ofstream	o(file.string().c_str(), ofstream::binary);

  return serialize(o);
}

/**
 * @brief		Save object to stream
 *
 * @param o		Stream to load from
 *
 * @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
 *
 * @see			pnGetErrorString
 */
pnint	PNObject::serialize(ostream& o)
{
  return PNEC_NOT_IMPLEMENTED;
}

/**
* @brief		Save object
*
* @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
*
* @see			pnGetErrorString
*/
pnint	PNObject::serialize()
{
  return PNEC_NOT_IMPLEMENTED;
}

//////////////////////////////////////////////////////////////////////////
}
