/*
 * PNRendererObject.hpp
 * 
 * Description :
 * PNRendererObject declaration
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

#ifndef _PNRENDEREROBJECT_HPP_
# define _PNRENDEREROBJECT_HPP_

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef enum 
{
  PN_VARRAY		= 0x000001,
  PN_NARRAY		= 0x000001 << 1,
  PN_CARRAY		= 0x000001 << 2,
  PN_TCARRAY	= 0x000001 << 3
} pnrenderarray;

class PNFace;
class PNRenderMaterial;

class /*PNAPI*/ PNRendererObject : public PNObject
{
protected:
  virtual ~PNRendererObject(void) {}
public:
  //////////////////////////////////////////////////////////////////////////
  // buffers

  virtual void		setMode(pnrenderflag mode)=0;

  virtual void		setDFLColor(const pnfloat *color)=0;
  virtual void		setDFLColor(pnfloat r, pnfloat g, pnfloat b, pnfloat a)=0;

  virtual void		setNbVerts(pnint nbVerts)=0;
  virtual void		setBuffer(pnrenderarray flag_array, pnfloat* array)=0;

  virtual void		setInterleaveArray(void* array, pnuint size, pnrenderflag format = PN_T2F_C4F_N3F_V3F)=0;

  virtual void		setIndexBuffer(pnuint* array, pnint nbIndex)=0;
  
  //////////////////////////////////////////////////////////////////////////
  // FACES

  /** Add triangle to render stack */
  virtual pnint		addFaces(PNFace* faces, pnuint nb = 1)=0;
  /** Compute and rend all triangles from render stack */
  virtual pnint		renderAllFaces(pnbool clear = true)=0;
  virtual pnint		renderAllFaces(pnrenderflag mode, pnbool clear = true)=0;

  //////////////////////////////////////////////////////////////////////////
  // Material

  /** set the Material to bind before object render */
  virtual void		setMaterial(PNRenderMaterial* mat)=0;

  //////////////////////////////////////////////////////////////////////////

  virtual  void		render()=0;
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNRENDEREROBJECT_HPP_*/
