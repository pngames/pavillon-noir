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

#include "pnmaxplugin.h"
#include "PNPhysicsWin.hpp"

#include "PNPhysicalExporter.hpp"

//////////////////////////////////////////////////////////////////////////

namespace PN {
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

  type = 0;
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

//////////////////////////////////////////////////////////////////////////

int			PNPhysicalExporter::exportHeader()
{
  PNMainWin::WriteLine("PN3DObjectExporter::exportHeader()");

  _file->Write(PNP_XML_HEADER.c_str(), (UINT)PNP_XML_HEADER.size());

  return TRUE;
}

int			PNPhysicalExporter::exportBody()
{
  PNMainWin::WriteLine("PNPhysicalExporter::exportBody()");

  std::ostringstream	objString;

  objString << "<" << PNP_XMLNODE_ROOT;

  //////////////////////////////////////////////////////////////////////////

  if (type == 0)
  {
	objString	<< " " << PNP_XMLPROP_TYPE << "=\"" << "opal" << "\"";
	objString	<< " " << PNP_XMLPROP_PATH << "=\"" << 
	  PN::DEF::convertPath(PN::DEF::physicsFilePath + "opal/", path.GetString()) << "\"";

	if (save)
	{
	  
	  // recuperer le string du fichier de script
	  // inclure le path dans une variable au debut du script
	  // appeller:
	  //
	  GUP* gp = (GUP*)CreateInstance(GUP_CLASS_ID,Class_ID(470000002,0));
	  // gp->ExecuteStringScript("global savePath=$path\n" + filestring);
	}
  }
  else
  {
	objString	<< " " << PNP_XMLPROP_TYPE << "=\"" << "model" << "\"";
	objString	<< " " << PNP_XMLPROP_PATH << "=\"" << 
	  PN::DEF::convertPath(PN::DEF::modelFilePath, path.GetString()) << "\"";

	if (save)
	{
	  // utiliser l'exporter de model
	}
  }

  //////////////////////////////////////////////////////////////////////////

  objString << ">\n";

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int			PNPhysicalExporter::releaseExport()
{
  return TRUE;
}

int			PNPhysicalExporter::configure()
{
  PNPhysicsWin  win(this);

  win.DoModal();

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////
};
