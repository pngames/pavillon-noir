/*
 * PNAnimationExporter.hpp
 * 
 * Description :
 * PNAnimationExporter declaration
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

#ifndef _PNANIMATIONEXPORTER_HPP_
# define _PNANIMATIONEXPORTER_HPP_

#define PNANIMATIONEXPORTER_CLASS_ID	Class_ID(0x68367838, 0x61954c85)

#include "PNSkeletonExporter.hpp"

#include "pna_format.h"

class PNAnimationExporter : public PNSkeletonExporter
{
public:
  static HWND	hParams;

  void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

  //Constructor/Destructor
  PNAnimationExporter();
  ~PNAnimationExporter();
  //////////////////////////////////////////////////////////////////////////
public:
  virtual int	initExport();
  virtual int	releaseExport();
  
  virtual int	exportHeader();

  int			exportRotSampleKeys(IGameControl *control, DWORD Type, IGameKeyTab &keyTab);
  int			exportPosSampleKeys(IGameControl *control, DWORD Type, IGameKeyTab &keyTab);
  virtual int	exportBone(PNSBone* bone);
  virtual int	exportBody();

  virtual int	configure();
protected:
  pnaHeader_t	_aheader;

public:
  CString		name;
  int			framerate;
};



class PNAnimationExporterDesc : public ClassDesc2
{
  HINSTANCE		_hInstance;
public:
  void			SetInstance (HINSTANCE hInstance);
public:
  int 			IsPublic();
  void *		Create(BOOL loading = FALSE);
  const TCHAR *	ClassName();
  SClass_ID		SuperClassID();
  Class_ID		ClassID();
  // The Skin modifier checks the category to decide whether the modifier is a Skin Gizmo.  This 
  // must not be changed
  const TCHAR* 	Category();

  const TCHAR*	InternalName();	// returns fixed parsable name (scripter-visible name)
  HINSTANCE		HInstance(); // returns owning module handle
};

#endif /*_PNANIMATIONEXPORTER_HPP_*/
