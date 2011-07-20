/*
 * PNRenderMaterial.hpp
 * 
 * Description :
 * PNRenderMaterial declaration
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

#ifndef _PNRENDERMATERIAL_HPP_
# define _PNRENDERMATERIAL_HPP_

#include <string>

#include "pnmath.h"

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNTexture;

class /*PNAPI*/			PNRenderMaterial : public PNObject
{
protected:
  virtual ~PNRenderMaterial() {}
  //////////////////////////////////////////////////////////////////////////
public:
  virtual void			setOpacity(pnfloat opac)=0;
  virtual void			setGlossiness(pnfloat glossi)=0;

  virtual void			setAmbient(const pnfloat* color)=0;
  virtual void			setDiffuse(const pnfloat* color)=0;
  virtual void			setEmissive(const pnfloat* color)=0;
  virtual void			setSpecular(const pnfloat* color)=0;

  virtual pnint			setTexture(const std::string& path, void* lightMap = NULL)=0;
  virtual PNTexture*	getTexture()=0;
  virtual void			setTextureRepeat(pnbool repeat)=0;

  virtual pnint			bind()=0;
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNRENDERMATERIAL_HPP_*/

