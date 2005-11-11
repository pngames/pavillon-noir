/*
 * PNPhysicalObject.hpp
 * 
 * Description :
 * PNPhysicalObject declaration
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

#ifndef _PNPHYSICALOBJECT_HPP_
# define _PNPHYSICALOBJECT_HPP_

#include "PNObject.hpp"
#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNPoint;
class PNQuatf;

class PNPhysicalObject: public PNObject, public IPNXMLSerializable
{
public:
  virtual ~PNPhysicalObject(void) {}

  //////////////////////////////////////////////////////////////////////////

  virtual void			update(pnuint elapsed_time)=0;
  virtual void			render()=0;

  //////////////////////////////////////////////////////////////////////////

  virtual const PNPoint&	getCoord()=0;
  virtual const PNQuatf&	getOrient()=0;
  virtual const PNPoint&	getOffset()=0;

  //////////////////////////////////////////////////////////////////////////

  virtual void			setStatic(bool state)=0;
  virtual void			setCoord(const PNPoint& coord)=0;
  virtual void			setCoord(pnfloat x, pnfloat y, pnfloat z)=0;
  virtual void			setOrient(const PNQuatf& orient)=0;
  virtual void			setOrient(pnfloat x, pnfloat y, pnfloat z, pnfloat w)=0;

  //////////////////////////////////////////////////////////////////////////

  virtual void			addForce(pnfloat x, pnfloat y, pnfloat z, pnfloat duration)=0;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNPHYSICALOBJECT_HPP_*/
