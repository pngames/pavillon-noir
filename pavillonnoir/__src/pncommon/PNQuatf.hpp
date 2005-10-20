/*
 * PNQuatf.hpp
 * 
 * Description :
 * PNQuatf declaration
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

#ifndef _PNQUATF_H_
# define _PNQUATF_H_

#include <string.h>
#include <iostream>

#include "PNObject.hpp"

namespace PN {

class PNPoint;
class PNVector3f;

class PNAPI				PNQuatf : public PNObject
{
  friend PNAPI std::ostream&	operator<<(std::ostream& o, const PNQuatf& p);

  //////////////////////////////////////////////////////////////////////////
public:
  pnfloat				x;
  pnfloat				y;
  pnfloat				z;
  pnfloat				w;
public:
  PNQuatf();
  PNQuatf(const pnfloat* quat);
  PNQuatf(const PNQuatf& quat);
  PNQuatf(pnfloat r1, pnfloat r2, pnfloat r3, pnfloat r4);
  PNQuatf(const PNQuatf& q1, PNQuatf& q2, pnfloat interp);
  PNQuatf(const PNVector3f& axis, pnfloat phi);
  ~PNQuatf();

  void					loadIdentity();

  void					invert();
  PNQuatf				getInvert() const;

  void					set(pnfloat r1, pnfloat r2, pnfloat r3, pnfloat r4);
  void					set(const pnfloat* quat);
  void					fromDegrees(const pnfloat* angles);
  void					fromDegrees(pnfloat x, pnfloat y, pnfloat z);
  void					fromRadians(const pnfloat* angles);
  void					fromRadians(pnfloat x, pnfloat y, pnfloat z);

  void					getDegrees(pnfloat* angles) const;
  void					getDegrees(pnfloat& x, pnfloat& y, pnfloat& z) const;
  void					getRadians(pnfloat* angles) const;
  void					getRadians(pnfloat& x, pnfloat& y, pnfloat& z) const;

  void					fromAxisDegrees(const PNVector3f& axis, pnfloat phi);
  void					fromAxisRadians(const PNVector3f& axis, pnfloat phi);
  
  void					slerp(const PNQuatf& q1, PNQuatf& q2, pnfloat interp);

  PNPoint				multiply(const pnfloat *point) const;
  PNPoint	  			multiply(const PNPoint& point) const;

  //////////////////////////////////////////////////////////////////////////

  PNPoint				operator*(const PNPoint& vec) const;
  PNQuatf				operator*(const PNQuatf& quat) const;

  //////////////////////////////////////////////////////////////////////////
  
  PNQuatf&				operator=(const pnfloat* q);
};

//////////////////////////////////////////////////////////////////////////

inline					PNQuatf::PNQuatf()
{}

inline					PNQuatf::PNQuatf(const PNQuatf& quat)
{
  x = quat.x;
  y = quat.y;
  z = quat.z;
  w = quat.w;
}

inline					PNQuatf::PNQuatf(const pnfloat* quat)
{
  x = quat[0];
  y = quat[1];
  z = quat[2];
  w = quat[3];
}

inline					PNQuatf::PNQuatf(pnfloat r1, pnfloat r2, pnfloat r3, pnfloat r4)
{
  x = r1;
  y = r2;
  z = r3;
  w = r4;
}

inline					PNQuatf::PNQuatf(const PNQuatf& q1, PNQuatf& q2, pnfloat interp)
{
  slerp(q1, q2, interp);
}

inline					PNQuatf::PNQuatf(const PNVector3f& axis, pnfloat phi)
{
  fromAxisRadians(axis, phi);
}

inline					PNQuatf::~PNQuatf()
{}

//////////////////////////////////////////////////////////////////////////

inline void				PNQuatf::invert()
{
  x = -x;
  y = -y;
  z = -z;
  w = -w;
}

inline void				PNQuatf::set(pnfloat r1, pnfloat r2, pnfloat r3, pnfloat r4)
{
  x = r1;
  y = r2;
  z = r3;
  w = r4;
}

inline void				PNQuatf::set(const pnfloat* quat)
{
  x = quat[0];
  y = quat[1];
  z = quat[2];
  w = quat[3];
}

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNQUATF_H_*/
