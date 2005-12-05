/*
 * pnmaxplugin.h
 * 
 * Description :
 * Plugin declaration
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

#pragma once

#ifndef __AFXWIN_H__
#error inclut 'stdafx.h' avant d'inclure ce fichier pour PCH
#endif

#include "resource.h"		// symboles principaux

#define PN_PLUGIN_VERSION	001

class PNAnimationExporterDesc;
class PNModelExporterDesc;
class PNSkeletonExporterDesc;
class PNMaterialExporterDesc;
class PNPhysicalExporterDesc;
class PN3DObjectExporterDesc;

// CpnmaxpluginApp:
// Consultez pnmaxplugin-mfc.cpp pour l'impl�entation de cette classe
//

class CpnmaxpluginApp : public CWinApp
{
  static PNModelExporterDesc		_modelExporter;
  static PNMaterialExporterDesc		_materialExporter;
  static PNSkeletonExporterDesc		_skeletonExporter;
  static PNAnimationExporterDesc	_animationExporter;
  static PNPhysicalExporterDesc		_physicsExporter;
  static PN3DObjectExporterDesc		_objectExporter;

public:
  CpnmaxpluginApp();

  virtual BOOL	InitInstance();
public:
  ClassDesc*	GetClassDesc(int id);
  int			GetClassDescCount();
  TCHAR*		GetString(int id);

  CString		getStringOption(CString section, CString key, CString def);
  int			getIntOption(CString section, CString key, int def);

  void			setStringOption(CString section, CString key, CString value);
  void			setIntOption(CString section, CString key, int value);

  // Substitutions
public:
  //virtual BOOL	InitInstance();

  // Impl�entation

  DECLARE_MESSAGE_MAP()
};

extern CpnmaxpluginApp theApp;
