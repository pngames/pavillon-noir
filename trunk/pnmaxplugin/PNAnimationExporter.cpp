/*
 * PNAnimationExporter.cpp
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

#include "pnmaxplugin.h"

#include "PNAnimationExporter.hpp"
#include "PNAnimationWin.hpp"

//////////////////////////////////////////////////////////////////////////

void			PNAnimationExporterDesc::SetInstance(HINSTANCE hInstance)
{
  _hInstance = hInstance;
}

int 			PNAnimationExporterDesc::IsPublic()
{
  return TRUE;
}

void *			PNAnimationExporterDesc::Create(BOOL loading)
{
  return new PNAnimationExporter();
}

const TCHAR *	PNAnimationExporterDesc::ClassName()
{
  return theApp.GetString(IDS_CLASS_NAME);
}

SClass_ID		PNAnimationExporterDesc::SuperClassID()
{
  return SCENE_EXPORT_CLASS_ID;
}

Class_ID		PNAnimationExporterDesc::ClassID()
{
  return PNANIMATIONEXPORTER_CLASS_ID;
}

// The Skin modifier checks the category to decide whether the modifier is a Skin Gizmo.  This 
// must not be changed
const TCHAR* 	PNAnimationExporterDesc::Category()
{
  return theApp.GetString(IDS_CATEGORY);
}

const TCHAR*	PNAnimationExporterDesc::InternalName()
{
  return _T("PNAnimationExporter");
}

HINSTANCE		PNAnimationExporterDesc::HInstance()
{
  return _hInstance;
}

//////////////////////////////////////////////////////////////////////////
//--- pnmaxplugin -------------------------------------------------------

PNAnimationExporter::PNAnimationExporter() : name("no name"), framerate(4)
{
  _ext = PNA_EXT;
  _longDesc = theApp.GetString(IDS_PNA_LONGDESC);
  _shortDesc = theApp.GetString(IDS_PNA_SHORTDESC);
}

PNAnimationExporter::~PNAnimationExporter()
{

}

void PNAnimationExporter::ShowAbout(HWND hWnd)
{			
  // Optional
}

//////////////////////////////////////////////////////////////////////////

int PNAnimationExporter::configure()
{
  PNAnimationWin  win(this);

  win.DoModal();

  return TRUE;
}

int	PNAnimationExporter::releaseExport()
{ 
  PNSkeletonExporter::releaseExport();

  theApp.setIntOption("pna", "framerate", framerate);

  return TRUE;
}
