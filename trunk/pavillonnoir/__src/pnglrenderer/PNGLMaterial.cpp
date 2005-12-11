/*
 * PNGLMaterial.cpp
 * 
 * Description :
 * PNGLMaterial definition
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

#include "pndefs.h"

#include "PNGLRenderer.hpp"
#include "PNGLTexture.hpp"
#include "PNGLTextureManager.hpp"

#include "PNGLMaterial.hpp"

using namespace PN;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNGLMaterial::PNGLMaterial()
{
  setGlossiness(0.0f);

  static pnfloat  tmp_color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

  setAmbient(tmp_color);
  setDiffuse(tmp_color);
  setEmissive(tmp_color);
  setSpecular(tmp_color);

  _texture = NULL;
}

PNGLMaterial::~PNGLMaterial()
{
}

//////////////////////////////////////////////////////////////////////////

void
PNGLMaterial::setOpacity(pnfloat opac)
{
  _ambient[3] = opac;
  _diffuse[3] = opac;
  _emissive[3] = opac;
  _specular[3] = opac;
}

void
PNGLMaterial::setGlossiness(pnfloat glossi)
{
  _glossiness = glossi;
}

void
PNGLMaterial::setAmbient(const pnfloat* color)
{
  _ambient[0] = color[0];
  _ambient[1] = color[1];
  _ambient[2] = color[2];
  _ambient[3] = color[3];
}

void
PNGLMaterial::setDiffuse(const pnfloat* color)
{
  _diffuse[0] = color[0];
  _diffuse[1] = color[1];
  _diffuse[2] = color[2];
  _diffuse[3] = color[3];
}

void
PNGLMaterial::setEmissive(const pnfloat* color)
{
  _emissive[0] = color[0];
  _emissive[1] = color[1];
  _emissive[2] = color[2];
  _emissive[3] = color[3];
}

void
PNGLMaterial::setSpecular(const pnfloat* color)
{
  _specular[0] = color[0];
  _specular[1] = color[1];
  _specular[2] = color[2];
  _specular[3] = color[3];
}

pnint
PNGLMaterial::setTexture(const std::string& path, void* lightMap)
{
  _texture = PNGLTextureManager::getInstance()->getTexture(path, lightMap);

  if (_texture == NULL)
	return PNEC_ERROR;

  return PNEC_SUCCESS;
}

void
PNGLMaterial::setTextureRepeat(pnbool repeat)
{
  if (_texture != NULL)
	_texture->setRepeat(repeat);
}

//////////////////////////////////////////////////////////////////////////

pnfloat
PNGLMaterial::getOpacity()
{
  return _diffuse[3];
}

pnfloat
PNGLMaterial::getGlossiness()
{
  return _glossiness;
}

const pnfloat*
PNGLMaterial::getAmbient()
{
  return _ambient;
}

const pnfloat*
PNGLMaterial::getDiffuse()
{
  return _diffuse;
}

const pnfloat*
PNGLMaterial::getEmissive()
{
  return _emissive;
}

const pnfloat*
PNGLMaterial::getSpecular()
{
  return _specular;
}

PNTexture*
PNGLMaterial::getTexture()
{
  return _texture;
}

pnint
PNGLMaterial::bind()
{
  glMaterialfv(GL_FRONT,  GL_AMBIENT,	_ambient);
  glMaterialfv(GL_FRONT,  GL_DIFFUSE,	_diffuse);
  glMaterialfv(GL_FRONT,  GL_SPECULAR,	_specular);
  glMaterialfv(GL_FRONT,  GL_EMISSION,	_emissive);
  glMaterialf (GL_FRONT,  GL_SHININESS, _glossiness);

  if (_texture != NULL)
  {
	glEnable(GL_TEXTURE_2D);
	_texture->bind();
  }
  else
  {
	glDisable(GL_TEXTURE_2D);
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
