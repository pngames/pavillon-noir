/*
 * PNGLTexture.hpp
 * 
 * Description :
 * PNGLTexture declaration
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

#ifndef _PNGLTEXTURE_HPP_
# define _PNGLTEXTURE_HPP_

#include <GL/glew.h>

#include "PNGLRenderer.hpp"

#include "PNTexture.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class		PNGLTexture : public PNTexture
{
private:
  friend	PNGLTexture*	PNGLRenderer::newTexture(void);
  friend	void			PNGLRenderer::deleteTexture(PNGLTexture* texture);

  PNGLTexture();
  ~PNGLTexture(void);
public:
  pnushort	getWidth(void) const;
  pnushort	getHeight(void) const;

  //////////////////////////////////////////////////////////////////////////

  pnint		loadFromFile(const boost::filesystem::path& file, void* lightMap = NULL);

  GLuint	getOGLTexid(void) const;

private:
  GLuint 	_ogltexture;	/// The 'real' texture.
  pnushort	_width;			/// cached width of the texture
  pnushort	_height;		/// cached height of the texture

  std::string _file;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* _PNGLTEXTURE_HPP_ */
