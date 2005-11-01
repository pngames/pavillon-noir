/*
* PNGLTextureManager.cpp
* 
* Description :
* PNGLTextureManager definition
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

#include "PNGLTexture.hpp"

#include "PNGLTextureManager.hpp"

namespace fs = boost::filesystem;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNGLTextureManager*		PNGLTextureManager::_instance;

PNGLTextureManager*
PNGLTextureManager::getInstance()
{
  if (_instance == NULL)
	_instance = new PNGLTextureManager();

  return _instance;
}

//////////////////////////////////////////////////////////////////////////

PNGLTextureManager::PNGLTextureManager()
{

}

PNGLTextureManager::~PNGLTextureManager()
{
  clean();
}

//////////////////////////////////////////////////////////////////////////

PNGLTexture*
PNGLTextureManager::getTexture(const boost::filesystem::path& file, void* lightMap)
{
  MAPTEXTURE::const_iterator cit = _textureMap.find(file);

  if (cit != _textureMap.end())
	return cit->second;

  if (!fs::exists(file))
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", file.string().c_str(), pnGetErrorString(PNEC_FILE_NOT_FOUND));
	return NULL;
  }

  if (fs::is_directory(file))
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", file.string().c_str(), pnGetErrorString(PNEC_NOT_A_FILE));
	return NULL;
  }

  PNGLTexture* texture = new PNGLTexture();

  pnint	error= PNEC_SUCCESS;

  if ((error = texture->loadFromFile(file, lightMap)) != PNEC_SUCCESS)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", file.string().c_str(), pnGetErrorString(error));

	delete texture;
	texture = NULL;
  }
  else
	_textureMap[file] = texture;

  return texture;
}

void
PNGLTextureManager::clean()
{
  for (MAPTEXTURE::iterator it = _textureMap.begin(); it != _textureMap.end(); ++it)
	delete it->second;

  _textureMap.clear();
}

//////////////////////////////////////////////////////////////////////////
};
