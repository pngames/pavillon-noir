/*
* PNLocale.hpp
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

#include <string>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNAPI					PNLocale : public PNObject
{
  static PNLocale			_defaultLocale;
public:
  static const PNLocale&	defaultLocale();
  static void				setDefaultLocale(const PNLocale& locale);

private:
  std::string				_language;
  std::string				_country;
  std::string				_variant;
public:
  PNLocale(const std::string& str);
  PNLocale(const std::string& language, const std::string& country, const std::string& variant);
  PNLocale(const PNLocale& l);

  ~PNLocale();

  //////////////////////////////////////////////////////////////////////////
  
  const std::string&		getLanguage() const;
  const std::string&		getCountry() const;
  const std::string&		getVariant() const;

  //////////////////////////////////////////////////////////////////////////
public:
  static const PNLocale		none;

  static const PNLocale		FR;
  static const PNLocale		EN;
};
 
//////////////////////////////////////////////////////////////////////////
};

