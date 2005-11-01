/*
 * PNPoint.hpp
 * 
 * Description :
 * PNPoint declaration
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

#ifndef _PNPOINT_H_
# define _PNPOINT_H_

#include <iostream>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNAPI		PNPoint : public PNObject
{
private:
  friend PNAPI PNPoint			operator+(const PNPoint& p1, const PNPoint& p2);
  friend PNAPI PNPoint			operator-(const PNPoint& p1, const PNPoint& p2);
  friend PNAPI PNPoint			operator*(const PNPoint& p1, const PNPoint& p2);
  friend PNAPI PNPoint			operator/(const PNPoint& p1, const PNPoint& p2);
  friend PNAPI pnbool			operator==(const PNPoint& p1, const PNPoint& p2);
  friend PNAPI pnbool			operator!=(const PNPoint& p1, const PNPoint& p2);

  //////////////////////////////////////////////////////////////////////////

  friend PNAPI std::ostream&	operator<<(std::ostream& o, const PNPoint& p);
  friend PNAPI std::istream&	operator>>(std::istream& i, PNPoint& p);

  //////////////////////////////////////////////////////////////////////////
public:
  pnfloat		x;
  pnfloat		y;
  pnfloat		z;
public:
  PNPoint(void);
  PNPoint(const pnfloat& x, const pnfloat& y, const pnfloat& z);
  PNPoint(const pnfloat* coord);
  PNPoint(const PNPoint& p);
  ~PNPoint(void);

  void			setNull();

  void			set(const pnfloat& x, const pnfloat& y, const pnfloat& z);
  void			set(const pnfloat* coord);
  void			set(const PNPoint& p);
  pnfloat		getDistance(const PNPoint& target) const;
  
public:
  bool			isEquals(const PNPoint & point);  
  bool			isEquals(pnfloat x, pnfloat y, pnfloat z);
  
  //////////////////////////////////////////////////////////////////////////
public:

  operator const pnfloat*() const;

  //////////////////////////////////////////////////////////////////////////
  
  PNPoint&		operator=(const pnfloat* p);

  PNPoint&		operator+=(const PNPoint& p);
  PNPoint&		operator+=(const pnfloat k);
  PNPoint&		operator-=(const PNPoint& p);
  PNPoint&		operator-=(const pnfloat k);
  PNPoint&		operator*=(const PNPoint& p);
  PNPoint&		operator*=(const pnfloat k);
  PNPoint&		operator/=(const PNPoint& p);
  PNPoint&		operator/=(const pnfloat k);

  PNPoint		operator-();

public:
  static const PNPoint ZERO;
};
//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNPOINT_H_*/
