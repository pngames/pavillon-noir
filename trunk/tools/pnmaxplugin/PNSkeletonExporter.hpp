/*
 * PNSkeletonExporter.hpp
 * 
 * Description :
 * PNSkeletonExporter declaration
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

#ifndef _PNSKELETONEXPORTER_HPP_
# define _PNSKELETONEXPORTER_HPP_

#ifdef _DEBUG
# define PNSKELETONEXPORTER_CLASS_ID	Class_ID(0x6ced3dd8, 0x6ea47fc5)
# define PNS_LONGDESC					"Skeleton exporter for Pavillon Noir 3D objects (debug)"
# define PNS_SHORTDESC					"Pavillon Noir Squeletor export (debug)"
#else
# define PNSKELETONEXPORTER_CLASS_ID	Class_ID(0x15281775, 0x549078a7)
# define PNS_LONGDESC					"Skeleton exporter for Pavillon Noir 3D objects"
# define PNS_SHORTDESC					"Pavillon Noir Squeletor export"
#endif

#include "PNExporter.hpp"

#include "pns_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNSBone;

class PNSkeletonExporter : public PNExporter
{
  friend class PNSkeletonWin;
public:
  static HWND hParams;

  void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

  //Constructor/Destructor
  PNSkeletonExporter();
  ~PNSkeletonExporter();
  //////////////////////////////////////////////////////////////////////////
public:
  virtual int	initExport();
  virtual int	releaseExport();

  int			parseNodeHeader(PNSBone*  parent, IGameNode* node);
  virtual int	exportHeader();

  virtual int	exportBone(PNSBone* bone);
  virtual int	exportBody();

  virtual int	configure();

protected:
  pnsHeader_t	_sheader;

  PNSBone*		_topLevelBone;

  pnsBone_t*	_tabBones;
};

class PNSkeletonExporterDesc : public ClassDesc2
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

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNSKELETONEXPORTER_HPP_*/
