/*
 * PNGLTexture.cpp
 * 
 * Description :
 * PNGLTexture definition
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
#include <iostream>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "pndefs.h"

#include "PNGLTexture.hpp"

namespace fs = boost::filesystem;

namespace PN
{

  /*************************************************************************
  Constructor
  *************************************************************************/
  PNGLTexture::PNGLTexture()
{
  // generate a OGL texture that we will use.
  glGenTextures(1, &_ogltexture);

  // set some parameters for this texture.
  glBindTexture(GL_TEXTURE_2D, _ogltexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);	// GL_CLAMP_TO_EDGE
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);	// GL_CLAMP_TO_EDGE
}

/*************************************************************************
Destructor
*************************************************************************/
PNGLTexture::~PNGLTexture(void)
{
  // delete OGL texture associated with this object.
  glDeleteTextures(1, &_ogltexture);
}

//////////////////////////////////////////////////////////////////////////

pnushort	PNGLTexture::getWidth(void) const
{
  return _width;
}

pnushort	PNGLTexture::getHeight(void) const
{
  return _height;
}

//////////////////////////////////////////////////////////////////////////

pnint		PNGLTexture::loadFromFile(const boost::filesystem::path& file, void* lightMap)
{
  if (!fs::exists(file))
	return PNEC_FILE_NOT_FOUND;

  if (fs::is_directory(file))
	return PNEC_NOT_A_FILE;

  std::cout << "glBindTexture(GL_TEXTURE_2D, " << _ogltexture << ")" << std::endl;

  glBindTexture(GL_TEXTURE_2D, _ogltexture);

  ILuint imgName = iluGenImage();
  ilBindImage(imgName);

  std::cout << "ilLoadImage((const ILstring)" << file.string().c_str() << std::endl;

  if (ilLoadImage((const ILstring)file.string().c_str()) != IL_FALSE)
  {
	// flip the image
	iluFlipImage();

	// get details about size of loaded image
	ILinfo imgInfo;
	iluGetImageInfo(&imgInfo);

	// set dimensions of texture
	_width = imgInfo.Width;
	_height = imgInfo.Height;
	
	printf("Texture: %s\nw = %d h = %d\nnbsubs = \n", file.string().c_str(), _width, _height/*, t.nbSubs*/);

	//ilutGLTexImage(0);
	ilutGLBuildMipmaps();

	// delete DevIL image
	iluDeleteImage(imgName);

	return PNEC_SUCCES;
  }
  else
  {
  	std::cout << IL_COULD_NOT_OPEN_FILE << " " << IL_ILLEGAL_OPERATION << " " << IL_INVALID_EXTENSION << " " << IL_INVALID_PARAM << std::endl;
  	int err = ilGetError();
	std::cout << file.string().c_str() << " : " << err << " (" << ilGetString(err) << ")" << std::endl;
  }

  // delete DevIL image
  iluDeleteImage(imgName);

  return PNEC_ERROR;
}

GLuint		PNGLTexture::getOGLTexid(void) const
{
  return _ogltexture;
}

//////////////////////////////////////////////////////////////////////////
};
