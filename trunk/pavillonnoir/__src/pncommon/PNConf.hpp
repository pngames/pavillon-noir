/*
 * PNConf.hpp
 * 
 * Description :
 * PNConf declaration
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

#ifndef _PNCONF_HPP_
# define _PNCONF_HPP_

#include <string>
#include <map>
#include <boost/filesystem/path.hpp>

#define PNCONFFILE	"configuration.xml"
#define PNCONFPATH	"pavillon-noir"
#ifdef WIN32
# define UNIXPREFIX	""
#else
# define UNIXPREFIX	"."
#endif

namespace PN
{
  /**
  * Configuration file management class
  */
  class PNAPI							PNConf
  {
  private:
	static PNConf*						_instance;
	std::string							_homePath;
	boost::filesystem::path				_confFilePath;
	std::map<std::string, std::string>	_confHash;
	std::map<std::string, std::string>	_defaultHash;

	PNConf();
	~PNConf();
	void								_loadConfFile();
	void								_createDefaultConf();
  public:

	static void							initialize();
	static PNConf*						getInstance();
	void								setKey(const std::string& key, const std::string& value);
	const std::string&					getKey(const std::string& key);
	void								saveConf();
	boost::filesystem::path				getConfPath();
  };
}

#endif /*_PNCONF_HPP_*/
