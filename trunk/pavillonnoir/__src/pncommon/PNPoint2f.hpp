/*
* PNPoint2f.hpp
* 
* Description :
* PNPoint2f declaration
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

#ifndef _PNPOINT2F_HPP_
# define _PNPOINT2F_HPP_

#include <iostream>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNAPI					PNPoint2f: public PNObject
{
private:
  friend PNAPI PNPoint2f	operator+(const PNPoint2f& p1, const PNPoint2f& p2);
  friend PNAPI PNPoint2f	operator-(const PNPoint2f& p1, const PNPoint2f& p2);
  friend PNAPI PNPoint2f	operator*(const PNPoint2f& p1, const PNPoint2f& p2);
  friend PNAPI PNPoint2f	operator/(const PNPoint2f& p1, const PNPoint2f& p2);
  friend PNAPI pnbool		operator==(const PNPoint2f& p1, const PNPoint2f& p2);
  friend PNAPI pnbool		operator!=(const PNPoint2f& p1, const PNPoint2f& p2);

  //////////////////////////////////////////////////////////////////////////

  friend PNAPI std::ostream&	operator<<(std::ostream& o, const PNPoint2f& p);
  friend PNAPI std::istream&	operator>>(std::istream& i, PNPoint2f& p);

  //////////////////////////////////////////////////////////////////////////
public:
  pnfloat					x;
  pnfloat					y;
public:
  PNPoint2f(void);
  PNPoint2f(const pnfloat& x, const pnfloat& y);
  PNPoint2f(const pnfloat* coord);
  PNPoint2f(const PNPoint2f& p);
  ~PNPoint2f(void);

  void						setNull();
  virtual bool				isNull() const;

  void						set(const pnfloat& x, const pnfloat& y);
  void						set(const pnfloat* coord);
  void						set(const PNPoint2f& p);
  pnfloat					getDistance(const PNPoint2f& target) const;

public:
  bool						isEquals(const PNPoint2f& point);  
  bool						isEquals(pnfloat x, pnfloat y);

  //////////////////////////////////////////////////////////////////////////
  
  std::string				serialize() const;
  void						unserialize(const std::string& str);
  void						unserialize(std::istream& istr);

  virtual std::string		toString();

  //////////////////////////////////////////////////////////////////////////
public:

  operator					const pnfloat*() const;

  //////////////////////////////////////////////////////////////////////////

  PNPoint2f&				operator=(const pnfloat* p);

  PNPoint2f&				operator+=(const PNPoint2f& p);
  PNPoint2f&				operator+=(const pnfloat k);
  PNPoint2f&				operator-=(const PNPoint2f& p);
  PNPoint2f&				operator-=(const pnfloat k);
  PNPoint2f&				operator*=(const PNPoint2f& p);
  PNPoint2f&				operator*=(const pnfloat k);
  PNPoint2f&				operator/=(const PNPoint2f& p);
  PNPoint2f&				operator/=(const pnfloat k);

  PNPoint2f					operator-();

public:
  static const PNPoint2f	ZERO;
};
//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNPOINT2F_HPP_*/
