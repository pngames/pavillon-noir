/*
 * PNExporter.cpp
 * 
 * Description :
 * PNExporter definition
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

#include "PNExporter.hpp"
#include "pnmaxplugin.h"

using namespace PN;

int		PNExporter::export(CString path)
{
  PNMainWin::WriteLine("Start export");

  PNMainWin::WriteLine("");
  PNMainWin::WriteLine("Opening file %s ...", path);
  _file = new CFile(path, CFile::modeCreate | CFile::modeReadWrite);
  PNMainWin::WriteLine("File opened", path);

  PNMainWin::WriteLine("");
  PNMainWin::WriteLine("Starting export");
  int	err = TRUE;

  try
  {
	PNMainWin::WriteLine("Export Header");
	err = exportHeader();
	PNMainWin::WriteLine("Export Body");
	if (err == TRUE)
	  err = exportBody();
  }
  catch (...)
  {
	PNMainWin::WriteLine("CONNERIE D'EXPORTER !");
  }

  PNMainWin::WriteLine("");
  PNMainWin::WriteLine("Closing file %s ...", path);
  _file->Close();
  delete _file;

  return err;
}

int		PNExporter::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

  _igameScene = GetIGameInterface();

  IGameConversionManager*	cm = GetConversionManager();
  cm->SetCoordSystem(IGameConversionManager::IGAME_OGL);

  _igameScene->InitialiseIGame(options == TRUE);

  if (!suppressPrompts)
  {
	CString	path = name;
	char*	ext = PathFindExtension(path.GetString());
	CString	ext2 = ext;
	path.Replace(ext, ext2.MakeLower());

	PNMainWin	mw(path, i);

	mw._exporter = this;

	mw.DoModal();
  }

  releaseExport();

  _igameScene->ReleaseIGame();

  return TRUE;
}

int		PNExporter::initFiles(CString file)
{
  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int PNExporter::ExtCount()
{
  //TODO: Returns the number of file name extensions supported by the plug-in.
  return 1;
}

const TCHAR *PNExporter::Ext(int n)
{		
  //TODO: Return the 'i-th' file name extension (i.e. "3DS").
  return _ext.GetString();
}

const TCHAR *PNExporter::LongDesc()
{
  //TODO: Return long ASCII description (i.e. "Targa 2.0 Image File")
  return _longDesc.GetString();
}

const TCHAR *PNExporter::ShortDesc() 
{			
  //Return short ASCII description (i.e. "Targa")
  return _shortDesc.GetString();
}

const TCHAR *PNExporter::AuthorName()
{			
  //Return ASCII Author name
  return theApp.GetString(IDS_AUTHORNAME);
}

const TCHAR *PNExporter::CopyrightMessage() 
{	
  //ASCII Copyright message
  return theApp.GetString(IDS_COPYRIGHT);
}

const TCHAR *PNExporter::OtherMessage1() 
{		
  //Return Other message #1 if any
  return _T("");
}

const TCHAR *PNExporter::OtherMessage2() 
{		
  //TODO: Return other message #2 in any
  return _T("");
}

unsigned int PNExporter::Version()
{				
  //TODO: Return Version number * 100 (i.e. v3.01 = 301)
  return PN_PLUGIN_VERSION;
}

BOOL PNExporter::SupportsOptions(int ext, DWORD options)
{
  // TODO Decide which options to support.  Simply return
  // true for each option supported by each Extension 
  // the exporter supports.

  return TRUE;
}

CString  PNExporter::transformToSystem(CString str)
{
  PNMainWin::WriteLine("transformToUTF8 in : %s", str);

  str = transformToUTF8(str);

  for (int i = 0; i < str.GetLength(); ++i)
	if (
	  !(str[i] >= '0' && str[i] <= '9') &&
	  !(str[i] >= 'A' && str[i] <= 'Z') &&
	  !(str[i] >= 'a' && str[i] <= 'z') &&
	  !(str[i] >= '#' && str[i] <= '.') &&
	  str[i] != ' ')
	  str.SetAt(i, '&');

  PNMainWin::WriteLine("transformToUTF8 out : %s", str);

  return str;
}

CString  PNExporter::transformToUTF8(CString str)
{
  PNMainWin::WriteLine("transformToUTF8 in : %s", str);

  for (int i = 0; i < str.GetLength(); ++i)
	if (!(str[i] >= 0 && str[i] <= 128))
	{
	  switch (str[i])
	  {
	  case 0xC8:
	  case 0xC9:
	  case 0xCA:
	  case 0xCB:
		str.SetAt(i, 'E');
		break;
	  case 0xE8:
	  case 0xE9:
	  case 0xEA:
	  case 0xEB:
		str.SetAt(i, 'e');
		break;
	  case 0xC0:
	  case 0xC1:
	  case 0xC2:
	  case 0xC3:
	  case 0xC5:
	  case 0xC6:
		str.SetAt(i, 'A');
		break;
	  case 0xE0:
	  case 0xE1:
	  case 0xE2:
	  case 0xE3:
	  case 0xE4:
	  case 0xE5:
	  case 0xE6:
		str.SetAt(i, 'a');
		break;
	  default:
		str.SetAt(i, '_');
	  }
	}

  PNMainWin::WriteLine("transformToUTF8 out : %s", str);

  return str;
}

//////////////////////////////////////////////////////////////////////////

void  PNExporter::_getPoint3Property(IGameProperty* prop, pnfloat* color, const pnfloat* def)
{
  if (prop != NULL)
  {
	Point3 p;

	prop->GetPropertyValue(p);

	memcpy(color, p, sizeof(pnpoint3f));
  }
  else
	memcpy(color, def, sizeof(pnpoint3f));
}

float  PNExporter::_getFloatProperty(IGameProperty* prop, pnfloat def)
{
  if (prop == NULL)
	return def;

  float f;

  prop->GetPropertyValue(f);

  return f;
}
