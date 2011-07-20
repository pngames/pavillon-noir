/*
 * PNSkeletonExporter.cpp
 * 
 * Description :
 * PNSkeletonExporter definition
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

#include "PNSkeletonExporter.hpp"
#include "PNSkeletonWin.hpp"
#include "PNSBone.hpp"

//////////////////////////////////////////////////////////////////////////

void			PNSkeletonExporterDesc::SetInstance (HINSTANCE hInstance)
{
  _hInstance = hInstance;
}

int 			PNSkeletonExporterDesc::IsPublic()
{
  return TRUE;
}

void *			PNSkeletonExporterDesc::Create(BOOL loading)
{
  return new PNSkeletonExporter();
}

const TCHAR *	PNSkeletonExporterDesc::ClassName()
{
  return theApp.GetString(IDS_CLASS_NAME);
}

SClass_ID		PNSkeletonExporterDesc::SuperClassID()
{
  return SCENE_EXPORT_CLASS_ID;
}

Class_ID		PNSkeletonExporterDesc::ClassID()
{
  return PNSKELETONEXPORTER_CLASS_ID;
}

// The Skin modifier checks the category to decide whether the modifier is a Skin Gizmo.  This 
// must not be changed
const TCHAR* 	PNSkeletonExporterDesc::Category()
{
  return theApp.GetString(IDS_CATEGORY);
}

const TCHAR*	PNSkeletonExporterDesc::InternalName()
{
  return _T("PNSkeletonExporter");
}

HINSTANCE		PNSkeletonExporterDesc::HInstance()
{
  return _hInstance;
}

//////////////////////////////////////////////////////////////////////////
//--- PNSkeletonExporter -------------------------------------------------------

PNSkeletonExporter::PNSkeletonExporter() : _tabBones(NULL)
{
  _ext = PNS_EXT;
  _longDesc = theApp.GetString(IDS_PNS_LONGDESC);
  _shortDesc = theApp.GetString(IDS_PNS_SHORTDESC);
}

PNSkeletonExporter::~PNSkeletonExporter() 
{
  
}

void PNSkeletonExporter::ShowAbout(HWND hWnd)
{			
  // Optional
}

//////////////////////////////////////////////////////////////////////////

int PNSkeletonExporter::configure()
{
  PNSkeletonWin  win(this);

  win.DoModal();

  return TRUE;
}

int	PNSkeletonExporter::releaseExport()
{
  if (_topLevelBone != NULL)
	delete _topLevelBone;
  _topLevelBone = NULL;

  return TRUE;
}
