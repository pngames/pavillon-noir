/*
 * PNGLMaterial.hpp
 * 
 * Description :
 * PNGLMaterial declaration
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

#ifndef _PNGLMATERIAL_HPP_
# define _PNGLMATERIAL_HPP_

#include <GL/glew.h>

#include "pndefs.h"

#include "PNGLRenderer.hpp"
#include "PNRenderMaterial.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNGLTexture;

class				PNGLMaterial : public PNRenderMaterial
{
  friend PNRenderMaterial* PNGLRenderer::newMaterial();
  friend void PNGLRenderer::deleteMaterial(PNRenderMaterial* material);
private:
  PNGLMaterial();
  virtual ~PNGLMaterial();
public:
  //////////////////////////////////////////////////////////////////////////
  // PNRENDERMATERIAL

  void				setOpacity(pnfloat opac);
  void				setGlossiness(pnfloat glossi);

  void				setAmbient(const pnfloat* color);
  void				setDiffuse(const pnfloat* color);
  void				setEmissive(const pnfloat* color);
  void				setSpecular(const pnfloat* color);

  pnint				setTexture(const std::string& path, void* lightMap = NULL);
  void				setTextureRepeat(pnbool repeat);

  //////////////////////////////////////////////////////////////////////////

  pnint				bind();

  pnfloat			getOpacity();
  pnfloat			getGlossiness();

  const pnfloat* 	getAmbient();
  const pnfloat*	getDiffuse();
  const pnfloat*	getEmissive();
  const pnfloat*	getSpecular();

  PNTexture*		getTexture();
private:
  PNGLTexture*		_texture;

  GLfloat			_glossiness;

  GLfloat			_ambient[4];
  GLfloat			_diffuse[4];
  GLfloat			_emissive[4];
  GLfloat			_specular[4];
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNGLMATERIAL_HPP_*/
