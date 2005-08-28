/*
 * pnmaxplugin.cpp
 * 
 * Description :
 * Entry point for pnmaxplugin
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
#include "PNModelExporter.hpp"
#include "PNSkeletonExporter.hpp"
#include "PNMaterialExporter.hpp"
#include "PN3DObjectExporter.hpp"

#include "pnmaxplugin.h"

#ifdef _DEBUG
# define new DEBUG_NEW
#endif

//----------------------------------------------------------------------------//
// The one and only DLL instance                                              //
//----------------------------------------------------------------------------//

CpnmaxpluginApp theApp;

//----------------------------------------------------------------------------//
// Exported functions                                                         //
//----------------------------------------------------------------------------//

// This function returns a string that describes the DLL and where the user
// could purchase the DLL if they don't have it.
PNPLUGEXPORT const TCHAR*	LibDescription()
{
  return _T("Pavillon Noir Exporter");
}

// This function returns the number of plug-in classes this DLL
//TODO: Must change this number when adding a new class
PNPLUGEXPORT int			LibNumberClasses()
{
  return theApp.GetClassDescCount();
}

// This function returns the number of plug-in classes this DLL
PNPLUGEXPORT ClassDesc*		LibClassDesc(int i)
{
  return theApp.GetClassDesc(i);
}

// This function returns a pre-defined constant indicating the version of 
// the system under which it was compiled.  It is used to allow the system
// to catch obsolete DLLs.
PNPLUGEXPORT ULONG			LibVersion()
{
  return VERSION_3DSMAX;
}

//////////////////////////////////////////////////////////////////////////

PNAnimationExporterDesc	  CpnmaxpluginApp::_animationExporter;
PNModelExporterDesc		  CpnmaxpluginApp::_modelExporter;
PNSkeletonExporterDesc	  CpnmaxpluginApp::_skeletonExporter;
PNMaterialExporterDesc	  CpnmaxpluginApp::_materialExporter;
PN3DObjectExporterDesc	  CpnmaxpluginApp::_objectExporter;

// CpnmaxpluginApp

BEGIN_MESSAGE_MAP(CpnmaxpluginApp, CWinApp)

END_MESSAGE_MAP()


// construction CpnmaxpluginApp

CpnmaxpluginApp::CpnmaxpluginApp()
{
  // TODO: ajoutez ici du code de construction,
  // Placez toutes les initialisations significatives dans InitInstance
}

BOOL CpnmaxpluginApp::InitInstance()
{
  if (CWinApp::InitInstance() == FALSE)
	return FALSE;

  SetRegistryKey(_T("Pavillon-Noir"));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

TCHAR*		CpnmaxpluginApp::GetString(int id)
{
  static TCHAR buf[256];

  if (m_hInstance)
	return LoadString(m_hInstance, id, buf, sizeof (buf)) ? buf : NULL;

  return NULL;
}

int			CpnmaxpluginApp::GetClassDescCount()
{
  return 5;
}

ClassDesc*	CpnmaxpluginApp::GetClassDesc(int id)
{
  switch (id)
  {
  case 0:
	_animationExporter.SetInstance(m_hInstance);
	return &_animationExporter;
  case 1:
	_modelExporter.SetInstance(m_hInstance);
	return &_modelExporter;
  case 2:
	_skeletonExporter.SetInstance(m_hInstance);
	return &_skeletonExporter;
  case 3:
	_materialExporter.SetInstance(m_hInstance);
	return &_materialExporter;
  case 4:
	_objectExporter.SetInstance(m_hInstance);
	return &_objectExporter;
  default:
	return NULL;
  }
}

CString	CpnmaxpluginApp::getStringOption(CString section, CString key, CString def)
{
  return GetProfileString(section, key, def);
}

int		CpnmaxpluginApp::getIntOption(CString section, CString key, int def)
{
  return GetProfileInt(section, key, def);

  return 0;
}

void	CpnmaxpluginApp::setStringOption(CString section, CString key, CString value)
{
  WriteProfileString(section, key, value);
}

void	CpnmaxpluginApp::setIntOption(CString section, CString key, int value)
{
  WriteProfileInt(section, key, value);
}

// initialisation CpnmaxpluginApp

/*BOOL		CpnmaxpluginApp::InitInstance()
{
  static bool bInitialized = false;

  // initialize controls once
  if (!bInitialized)
  {
	DisableThreadLibraryCalls(m_hInstance);
	InitCustomControls(m_hInstance);
	InitCommonControls();
	bInitialized = true;
  }

  return TRUE;
}*/
