/*
 * PNMaterialExporter.cpp
 * 
 * Description :
 * PNMaterialExporter definition
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

#include "PNMaterialExporter.hpp"
#include "pnmaxplugin.h"

#include "PNMaterialWin.hpp"

//////////////////////////////////////////////////////////////////////////

void			PNMaterialExporterDesc::SetInstance (HINSTANCE hInstance)
{
  _hInstance = hInstance;
}

int 			PNMaterialExporterDesc::IsPublic()
{
  return TRUE;
}

void *			PNMaterialExporterDesc::Create(BOOL loading)
{
  return new PNMaterialExporter();
}

const TCHAR *	PNMaterialExporterDesc::ClassName()
{
  return theApp.GetString(IDS_CLASS_NAME);
}

SClass_ID		PNMaterialExporterDesc::SuperClassID()
{
  return SCENE_EXPORT_CLASS_ID;
}

Class_ID		PNMaterialExporterDesc::ClassID()
{
  return PNMATERIALEXPORTER_CLASS_ID;
}

// The Skin modifier checks the category to decide whether the modifier is a Skin Gizmo.  This 
// must not be changed
const TCHAR* 	PNMaterialExporterDesc::Category()
{
  return theApp.GetString(IDS_CATEGORY);
}

const TCHAR*	PNMaterialExporterDesc::InternalName()
{
  return _T("PNMaterialExporter");
}

HINSTANCE		PNMaterialExporterDesc::HInstance()
{
  return _hInstance;
}

//////////////////////////////////////////////////////////////////////////
//--- pnmaxplugin -------------------------------------------------------

PNMaterialExporter::PNMaterialExporter()
{
  _ext = PNT_EXT;
  _longDesc = theApp.GetString(IDS_PNT_LONGDESC);
  _shortDesc = theApp.GetString(IDS_PNT_SHORTDESC);
}

PNMaterialExporter::~PNMaterialExporter() 
{

}

void PNMaterialExporter::ShowAbout(HWND hWnd)
{			
  // Optional
}

//////////////////////////////////////////////////////////////////////////

int			PNMaterialExporter::releaseExport()
{
  return TRUE;
}

int			PNMaterialExporter::configure()
{
  PNMaterialWin  win(_vectorMaterials);

  win.DoModal();

  return TRUE;
}

int			PNMaterialExporter::getNBMaterials()
{
  return (int)_vectorMaterials.size();
}

CString		PNMaterialExporter::getMaterialFile(int index)
{
  return _vectorMaterials[index].file;
}
