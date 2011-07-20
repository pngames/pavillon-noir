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

#include <boost/filesystem/operations.hpp>

#include "pndefs.h"

#include "PNGLMaterial.hpp"
#include "PNGLRenderer.hpp"
#include "PNGLTexture.hpp"

using namespace PN;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNGLMaterial::MAPTEXTURE	PNGLMaterial::_textureMap;

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
  if (_texture != NULL)
	PNGLRenderer::getInstance()->deleteTexture(_texture);
}

//////////////////////////////////////////////////////////////////////////

void			PNGLMaterial::setOpacity(pnfloat opac)
{
  _ambient[3] = opac;
  _diffuse[3] = opac;
  _emissive[3] = opac;
  _specular[3] = opac;
}

void			PNGLMaterial::setGlossiness(pnfloat glossi)
{
  _glossiness = glossi;
}

void			PNGLMaterial::setAmbient(const pnfloat* color)
{
  _ambient[0] = color[0];
  _ambient[1] = color[1];
  _ambient[2] = color[2];
  _ambient[3] = color[3];
}

void			PNGLMaterial::setDiffuse(const pnfloat* color)
{
  _diffuse[0] = color[0];
  _diffuse[1] = color[1];
  _diffuse[2] = color[2];
  _diffuse[3] = color[3];
}

void			PNGLMaterial::setEmissive(const pnfloat* color)
{
  _emissive[0] = color[0];
  _emissive[1] = color[1];
  _emissive[2] = color[2];
  _emissive[3] = color[3];
}

void			PNGLMaterial::setSpecular(const pnfloat* color)
{
  _specular[0] = color[0];
  _specular[1] = color[1];
  _specular[2] = color[2];
  _specular[3] = color[3];
}

pnint			PNGLMaterial::setTexture(const boost::filesystem::path& file, void* lightMap)
{
  MAPTEXTURE::const_iterator cit = _textureMap.find(file);

  if (cit != _textureMap.end())
  {
    _texture = cit->second;
	return PNEC_SUCCES;
  }

  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;

  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  _texture = (PNGLTexture*)PNGLRenderer::getInstance()->newTexture();

  if (_texture->loadFromFile(file, lightMap) != PNEC_SUCCES)
  {
	PNGLRenderer::getInstance()->deleteTexture(_texture);
	_texture = NULL;
  }

  return PNEC_SUCCES;
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

pnint			PNGLMaterial::bind()
{
  glMaterialfv(GL_FRONT,  GL_AMBIENT,	_ambient);
  glMaterialfv(GL_FRONT,  GL_DIFFUSE,	_diffuse);
  glMaterialfv(GL_FRONT,  GL_SPECULAR,	_specular);
  glMaterialfv(GL_FRONT,  GL_EMISSION,	_emissive);
  glMaterialf (GL_FRONT,  GL_SHININESS, _glossiness);

  if (_texture != NULL)
  {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texture->getOGLTexid());
  }
  else
  {
	glDisable(GL_TEXTURE_2D);
  }

  return PNEC_SUCCES;
}

//////////////////////////////////////////////////////////////////////////
};
