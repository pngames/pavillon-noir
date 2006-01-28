/*
 * PNPoint3f.hpp
 * 
 * Description :
 * PNPoint3f declaration
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

#ifndef _PNPOINT3F_HPP_
# define _PNPOINT3F_HPP_

#include <iostream>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNAPI					PNPoint3f: public PNObject
{
  PNDECLARE(PNPoint3f)

private:
  friend PNAPI PNPoint3f	operator+(const PNPoint3f& p1, const PNPoint3f& p2);
  friend PNAPI PNPoint3f	operator-(const PNPoint3f& p1, const PNPoint3f& p2);
  friend PNAPI PNPoint3f	operator*(const PNPoint3f& p1, const PNPoint3f& p2);
  friend PNAPI PNPoint3f	operator/(const PNPoint3f& p1, const PNPoint3f& p2);
  friend PNAPI pnbool		operator==(const PNPoint3f& p1, const PNPoint3f& p2);
  friend PNAPI pnbool		operator!=(const PNPoint3f& p1, const PNPoint3f& p2);

  //////////////////////////////////////////////////////////////////////////

  friend PNAPI std::ostream&	operator<<(std::ostream& o, const PNPoint3f& p);
  friend PNAPI std::istream&	operator>>(std::istream& i, PNPoint3f& p);

  //////////////////////////////////////////////////////////////////////////
public:
  pnfloat					x;
  pnfloat					y;
  pnfloat					z;
public:
  PNPoint3f(void);
  PNPoint3f(const pnfloat& x, const pnfloat& y, const pnfloat& z);
  PNPoint3f(const pnfloat* coord);
  PNPoint3f(const PNPoint3f& p);
  PNPoint3f(const std::string& str);
  ~PNPoint3f(void);

  void						setNull();
  virtual bool				isNull() const;

  void						set(const pnfloat& x, const pnfloat& y, const pnfloat& z);
  void						set(const pnfloat* coord);
  void						set(const PNPoint3f& p);
  pnfloat					getDistance(const PNPoint3f& target) const;
  pnfloat					getFlatDistance(const PNPoint3f& target) const;
  
public:
  bool						isEquals(const PNPoint3f& point);  
  bool						isEquals(pnfloat x, pnfloat y, pnfloat z);
  
  //////////////////////////////////////////////////////////////////////////
public:
  virtual std::string		toString() const;
  virtual void				fromString(const std::string& str);

  //////////////////////////////////////////////////////////////////////////
public:

  operator					const pnfloat*() const;

  //////////////////////////////////////////////////////////////////////////
  
  PNPoint3f&				operator=(const pnfloat* p);

  PNPoint3f&				operator+=(const PNPoint3f& p);
  PNPoint3f&				operator+=(const pnfloat k);
  PNPoint3f&				operator-=(const PNPoint3f& p);
  PNPoint3f&				operator-=(const pnfloat k);
  PNPoint3f&				operator*=(const PNPoint3f& p);
  PNPoint3f&				operator*=(const pnfloat k);
  PNPoint3f&				operator/=(const PNPoint3f& p);
  PNPoint3f&				operator/=(const pnfloat k);

  PNPoint3f					operator-();

public:
  static const PNPoint3f	ZERO;
};
//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNPOINT3F_HPP_*/
