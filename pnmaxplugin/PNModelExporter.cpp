/*
 * PNModelExporter.cpp
 * 
 * Description :
 * PNModelExporter definition
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

#include "PNModelExporter.hpp"
#include "pnmaxplugin.h"
#include "PNMainWin.hpp"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

void			PNModelExporterDesc::SetInstance(HINSTANCE hInstance)
{
  _hInstance = hInstance;
}

int 			PNModelExporterDesc::IsPublic()
{
  return TRUE;
}

void *			PNModelExporterDesc::Create(BOOL loading)
{
  return new PNModelExporter();
}

const TCHAR *	PNModelExporterDesc::ClassName()
{
  return theApp.GetString(IDS_CLASS_NAME);
}

SClass_ID		PNModelExporterDesc::SuperClassID()
{
  return SCENE_EXPORT_CLASS_ID;
}

Class_ID		PNModelExporterDesc::ClassID()
{
  return PNMODELEXPORTER_CLASS_ID;
}

// The Skin modifier checks the category to decide whether the modifier is a Skin Gizmo.  This 
// must not be changed
const TCHAR* 	PNModelExporterDesc::Category()
{
  return theApp.GetString(IDS_CATEGORY);
}

const TCHAR*	PNModelExporterDesc::InternalName()
{
  return _T("PNModelExporter");
}

HINSTANCE		PNModelExporterDesc::HInstance()
{
  return _hInstance;
}

//////////////////////////////////////////////////////////////////////////
//--- PNModelExporter -------------------------------------------------------

PNModelExporter::PNModelExporter()
{
  _ext = PNM_EXT;
  _longDesc = PNM_LONGDESC;
  _shortDesc = PNM_SHORTDESC;
}

PNModelExporter::~PNModelExporter() 
{

}

void PNModelExporter::ShowAbout(HWND hWnd)
{			
  // Optional
}

//////////////////////////////////////////////////////////////////////////

int	PNModelExporter::releaseExport()
{


  return TRUE;
}

int PNModelExporter::configure()
{


  return TRUE;
}
