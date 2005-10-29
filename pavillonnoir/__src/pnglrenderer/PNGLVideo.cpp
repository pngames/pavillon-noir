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
 
#include <math.h>
#include <stdlib.h>
#include <boost/thread/thread.hpp>
#include <fastdelegate/FastDelegate.h>

#include "pndefs.h"
#include "pnevent.h"
 
#include "PNGLVideo.hpp"

namespace PN {
	
PNGLVideo::PNGLVideo()
{
  _startedEventType = PN_EVENT_VIDEO_STARTED;
  _stopedEventType = PN_EVENT_VIDEO_ENDED;
}

PNGLVideo::~PNGLVideo()
{
}

pnint
PNGLVideo::unserializeFromFile(const boost::filesystem::path& file)
{		  
  _file = file;

  return PNEC_SUCCESS;
}

pnuint
PNGLVideo::startAnimation()
{
  printf("PNGLVideo::startAnimation()\n");

  pnuint err = IPNAnimated::startAnimation();

  if (err != PNEC_SUCCESS)
    return err;

#ifdef WIN32
  _command = std::string("win32\\mplayer\\mplayer.exe -really-quiet -fs ") + _file.string();
#else
  _command = std::string("xine --auto-play=Fhq ") + _file.string();
#endif

  boost::thread thrd(fastdelegate::FastDelegate0<void>(this, &PNGLVideo::_playVideo));

  return PNEC_SUCCESS;
}

void
PNGLVideo::_playVideo()
{
  system(_command.c_str());

  stopAnimation();
}

};
