/*
 * PNGLVideo.hpp
 * 
 * Description :
 * PNGLVideo definition
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

//////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdlib.h>
#include <boost/thread/thread.hpp>
#include <fastdelegate/FastDelegate.h>

#include "pnevent.h"
 
#include "PNGLVideo.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
PNStringParameter	PNGLVideo::_pMoviePlayer("win32\\mplayer\\mplayer.exe -really-quiet -fs", "Movie Player", "Movie Player", true);
#else
PNStringParameter	PNGLVideo::_pMoviePlayer("xine --auto-play=Fhq", "Movie Player", "Movie Player", true);
#endif

PNStringParameter*  PNGLVideo::getPMoviePlayer()
{
  return &_pMoviePlayer;
}

//////////////////////////////////////////////////////////////////////////

PNGLVideo::PNGLVideo(const std::string& path)
{
  _path = path;
}

PNGLVideo::~PNGLVideo()
{
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNGLVideo::play()
{
  PNEventManager::getInstance()->addEvent(PN_EVENT_VIDEO_STARTED, this, NULL);

#ifdef WIN32
  _command = (std::string&)_pMoviePlayer + " " + _path;
#else
  _command = (std::string&)_pMoviePlayer + " " + _path;
#endif

  boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNGLVideo::_playVideo));

  return PNEC_SUCCESS;
}

pnuint
PNGLVideo::pause()
{
  return PNEC_NOT_IMPLEMENTED;
}

pnuint
PNGLVideo::stop()
{
  return PNEC_NOT_IMPLEMENTED;
}

void
PNGLVideo::_playVideo()
{
  system(_command.c_str());

  PNEventManager::getInstance()->addEvent(PN_EVENT_VIDEO_ENDED, this, NULL);

  delete this;
}

//////////////////////////////////////////////////////////////////////////
};
