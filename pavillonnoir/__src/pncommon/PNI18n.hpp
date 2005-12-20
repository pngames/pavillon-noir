/*
* PNI18n.hpp
* 
* Description :
* Internationnalisation system
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

#ifndef _PNI18N_HPP_
# define _PNI18N_HPP_

#include <string>
#include <map>

#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNLocale;

class PNAPI					StringMap : public std::map<std::string, std::string>
{
public:
  const std::string&		getString(const std::string& key);
  void						addString(const std::string& key, const std::string& value);
};

class PNAPI					VarientMap : public std::map<std::string, StringMap>
{
public:
  const std::string&		getString(const std::string& key, const PNLocale& locale);
  void						addString(const std::string& key, const std::string& value, const PNLocale& locale);
};

class PNAPI					CountryMap : public std::map<std::string, VarientMap>
{
public:
  const std::string&		getString(const std::string& key, const PNLocale& locale);
  void						addString(const std::string& key, const std::string& value, const PNLocale& locale);
};

class PNAPI					PNI18n : public std::map<std::string, CountryMap>, public IPNXMLSerializable
{
  static PNI18n*			_instance;
public:
  static PNI18n*			getInstance();
private:
  PNI18n();
  ~PNI18n();

  const std::string&		_getString(const std::string& key, const PNLocale& locale);

  pnint						_unserializeString(xmlNode* node);
  pnint						_unserializeNode(xmlNode* node);
public:
  void						addString(const std::string& key, const std::string& value, const PNLocale& locale);

  static const std::string&	getString(const std::string& key);
  static const std::string&	getString(const std::string& key, const PNLocale& locale);

  //////////////////////////////////////////////////////////////////////////

  const std::string&		getDTD() const;
  const std::string&		getDTDName() const;
  const std::string&		getRootNodeName() const;

  pnint						unserializeFromXML(xmlNode* node);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNI18N_HPP_*/
