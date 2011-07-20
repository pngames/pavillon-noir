/*
 * a_exportHeader.cpp
 * 
 * Description :
 * PNAnimationExporter definition
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 *
 * This file is part of pnmaxplugin.
 *
 * pnmaxplugin is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * pnmaxplugin is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with pnmaxplugin; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "stdafx.h"

#include "PNAnimationExporter.hpp"

#include "pnmaxplugin.h"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

int	PNAnimationExporter::exportHeader()
{
  _file->Write(&_aheader, sizeof(_aheader));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int	PNAnimationExporter::initExport()
{
  framerate = theApp.getIntOption("pna", "framerate", 4);

  //////////////////////////////////////////////////////////////////////////

  PNMainWin::WriteLine("## Init animation exporter ##");

  PNSkeletonExporter::initExport();

  memset(&_aheader, 0, sizeof (_aheader));

  //////////////////////////////////////////////////////////////////////////
  // magic

  memcpy(_aheader.magic, PNA_MAGIC, strlen(PNA_MAGIC));
  _aheader.version = 001;

  //////////////////////////////////////////////////////////////////////////

  //_aheader.name

  _aheader.frameRate = framerate;
  _aheader.totalTime = _igameScene->GetSceneEndTime();

  _aheader.nbBones = _sheader.nbBones;

  return TRUE;
}

};
