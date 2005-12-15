/*
 * PNGLVideo.hpp
 * 
 * Description :
 * PNGLVideo declaration
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

#ifndef _PNGLVIDEO_HPP_
# define _PNGLVIDEO_HPP_

#include <string>
#include <boost/filesystem/path.hpp>

#ifndef WIN32
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>

# include <xine.h>
# include <xine/xineutils.h>
#endif

#include "pnproperties.h"

#include "PNObject.hpp"
#include "IPNAnimated.hpp"
#include "IPNSerializable.hpp"

namespace PN {
	
class				PNGLVideo : public PNObject, public IPNAnimated, public IPNSerializable
{
  static PNStringParameter	_pMoviePlayer;
public:
  static PNStringParameter*  getPMoviePlayer();
public:
  PNGLVideo();
  ~PNGLVideo();

  pnint				unserializeFromFile(const boost::filesystem::path& file);
	
  pnuint			startAnimation();
private:
  std::string		_command;

  void				_playVideo();
};

};

#endif /*_PNGLVIDEO_HPP_*/
