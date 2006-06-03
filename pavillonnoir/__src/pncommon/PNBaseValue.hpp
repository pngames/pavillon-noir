/*
* PNBaseValue.hpp
* 
* Description :
* PNBaseValue definition
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

#ifndef _PNBASEVALUE_HPP_
# define _PNBASEVALUE_HPP_

#include <sstream>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

template<class _Type>
class /*PNAPI*/			PNBaseValue : public PNObject
{
protected:
  _Type					_value;

public:
  PNBaseValue() {}
  PNBaseValue(_Type value) : _value(value) {}
  virtual ~PNBaseValue() {}

  //////////////////////////////////////////////////////////////////////////

  virtual std::string	toString() const
  {
	return staticToString(_value);
  }

  virtual void			fromString(const std::string& str)
  {
	_value = staticToValue(str);
  }

  static std::string	staticToString(_Type value)
  {
	std::ostringstream os;
	os << value;

	return os.str();
  }

  static _Type			staticToValue(const std::string& str)
  {
	std::istringstream	is(str);

	_Type value;
	is >> value;

	return value;
  }

  static _Type			staticToValue(const std::string& str, _Type def)
  {
	std::istringstream	is(str);

	_Type value;
	is >> value;

	if (is.bad())
	  return def;

	return value;
  }

  //////////////////////////////////////////////////////////////////////////

  const _Type&			getValue() const
  {
	return _value;
  }

  void					setValue(const _Type& value)
  {
	_value = value;
  }

  //////////////////////////////////////////////////////////////////////////

  operator				_Type&()
  {
	return _value;
  }

  operator				std::string()
  {
	return toString();
  }

  PNBaseValue<_Type>&	operator=(const _Type& value)
  {
	_value = value;

	return *this;
  }

  PNBaseValue<_Type>&	operator=(const std::string& str)
  {
	fromString(str);

	return *this;
  }
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNBASEVALUE_HPP_*/

