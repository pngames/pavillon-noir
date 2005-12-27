/*
* PNLocale.cpp
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

#include "pndefs.h"

#include "PNLocale.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNLocale		PNLocale::_defaultLocale("fr");

const PNLocale&	
PNLocale::defaultLocale()
{
  return _defaultLocale;
}

void
PNLocale::setDefaultLocale(const PNLocale& locale)
{
  _defaultLocale = locale;
}

//////////////////////////////////////////////////////////////////////////

const PNLocale	PNLocale::none("");
const PNLocale	PNLocale::FR("fr");
const PNLocale	PNLocale::EN("en");

//////////////////////////////////////////////////////////////////////////

PNLocale::PNLocale(const std::string& str)
{
  std::string lstring = str;

  _language = lstring;

  std::string::size_type nb = _language.find('_');
  if (nb != std::string::npos)
  {
	_language = lstring.substr(0, nb);
	lstring = lstring.erase(0, nb);

	_country = lstring;

	nb = _country.find('_');
	if (nb != std::string::npos)
	{
	  _country = lstring.substr(0, nb);
	  _variant = lstring.erase(0, nb);
	}
  }
}

PNLocale::PNLocale(const std::string& language, const std::string& country, const std::string& variant)
{
  _language = language;
  _country = country;
  _variant = variant;
}

PNLocale::PNLocale(const PNLocale& l)
{
  _language = l._language;
  _country = l._country;
  _variant = l._variant;
}

PNLocale::~PNLocale()
{
  
}

//////////////////////////////////////////////////////////////////////////

const std::string&		
PNLocale::getLanguage() const
{
  return _language;
}

const std::string&	
PNLocale::getCountry() const
{
  return _country;
}

const std::string&	
PNLocale::getVariant() const
{
  return _variant;
}

//////////////////////////////////////////////////////////////////////////
};
