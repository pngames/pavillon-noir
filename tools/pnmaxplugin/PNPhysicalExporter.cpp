/*
* PNPhysicalExporter.cpp
* 
* Description :
* PNPhysicalExporter definition
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

#include "PNPhysicalExporter.hpp"
#include "pnmaxplugin.h"

//#include "PNMaterialWin.hpp"

//////////////////////////////////////////////////////////////////////////

void			PNPhysicalExporterDesc::SetInstance(HINSTANCE hInstance)
{
  _hInstance = hInstance;
}

int 			PNPhysicalExporterDesc::IsPublic()
{
  return TRUE;
}

void *			PNPhysicalExporterDesc::Create(BOOL loading)
{
  return new PNPhysicalExporter();
}

const TCHAR *	PNPhysicalExporterDesc::ClassName()
{
  return theApp.GetString(IDS_CLASS_NAME);
}

SClass_ID		PNPhysicalExporterDesc::SuperClassID()
{
  return SCENE_EXPORT_CLASS_ID;
}

Class_ID		PNPhysicalExporterDesc::ClassID()
{
  return PNPHYSICALEXPORTER_CLASS_ID;
}

const TCHAR* 	PNPhysicalExporterDesc::Category()
{
  return theApp.GetString(IDS_CATEGORY);
}

const TCHAR*	PNPhysicalExporterDesc::InternalName()
{
  return _T("PNPhysicalExporter");
}

HINSTANCE		PNPhysicalExporterDesc::HInstance()
{
  return _hInstance;
}

//////////////////////////////////////////////////////////////////////////
//--- pnmaxplugin -------------------------------------------------------

PNPhysicalExporter::PNPhysicalExporter()
{
  _ext = PNP_EXT;
  _longDesc = PNP_LONGDESC;
  _shortDesc = PNP_SHORTDESC;
}

PNPhysicalExporter::~PNPhysicalExporter() 
{

}

void PNPhysicalExporter::ShowAbout(HWND hWnd)
{			
  // Optional
}

//////////////////////////////////////////////////////////////////////////

int			PNPhysicalExporter::initExport()
{
  return TRUE;
}

int			PNPhysicalExporter::initFiles(CString file)
{
  return TRUE;
}

int			PNPhysicalExporter::export(CString path)
{
  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int			PNPhysicalExporter::exportHeader()
{
  return TRUE;
}

int			PNPhysicalExporter::exportBody()
{
  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int			PNPhysicalExporter::releaseExport()
{
  return TRUE;
}

int			PNPhysicalExporter::configure()
{
  // throw window

  return TRUE;
}
