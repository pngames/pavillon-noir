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

#include "PNVector3f.hpp"

#include "PNObject.hpp"
#include "IPNImportedObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNPoint3f;
class PNQuatf;

class						PNPhysicalObject: public PNObject, public IPNImportedObject
{
public:
  virtual ~PNPhysicalObject(void) {}

  //////////////////////////////////////////////////////////////////////////

  virtual void				render()=0;

  //////////////////////////////////////////////////////////////////////////

  virtual const PNPoint3f&	getCoord()=0;
  virtual const PNQuatf&	getOrient()=0;
  virtual const PNPoint3f&	getOffset()=0;
  virtual const PNPoint3f&	getRenderOffset()=0;

  //////////////////////////////////////////////////////////////////////////

  virtual void				setStatic(bool state)=0;
  virtual bool				isStatic()=0;
  virtual void				setTransform(const PNPoint3f& coord, const PNQuatf& orient, pnfloat scale)=0;

  //////////////////////////////////////////////////////////////////////////

  virtual void				addForce(const PNVector3f& vec, pnfloat magnitude, pnfloat duration, pnbool isLocal)=0;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNPHYSICALOBJECT_HPP_*/

