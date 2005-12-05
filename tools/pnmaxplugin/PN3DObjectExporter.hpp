/*
 * PN3DObjectExporter.hpp
 * 
 * Description :
 * PN3DObjectExporter declaration
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

#ifndef _PN3DOBJECTEXPORTER_HPP_
# define _PN3DOBJECTEXPORTER_HPP_

#ifdef _DEBUG
# define PN3DOBJECEXPORTER_CLASS_ID	Class_ID(0x5e3b4160, 0x5a106653)
# define PNO_LONGDESC				"3DObject exporter for Pavillon Noir (debug)"
# define PNO_SHORTDESC				"Pavillon Noir 3DObject export (debug)"
#else
# define PN3DOBJECEXPORTER_CLASS_ID	Class_ID(0xfed2fc7, 0x6b731dc)
# define PNO_LONGDESC				"3DObject exporter for Pavillon Noir"
# define PNO_SHORTDESC				"Pavillon Noir 3DObject export"
#endif

#include "PNExporter.hpp"

#include "PNModelExporter.hpp"
#include "PNMaterialExporter.hpp"
#include "PNSkeletonExporter.hpp"
#include "PNAnimationExporter.hpp"
#include "PNPhysicalExporter.hpp"

class PNObjectWindow;

class					PN3DObjectExporter : public PNExporter
{
  friend class PNObjectWindow;
private:
  CString				_rootPath;

  bool					_hasModel;
  bool					_saveModel;
  CString				_modelPath;
  PNModelExporter		_modelExporter;

  bool					_hasMaterials;
  bool					_saveMaterials;
  CString				_materialsPath;
  PNMaterialExporter	_materialsExporter;

  bool					_hasSkeleton;
  bool					_saveSkeleton;
  CString				_skeletonPath;
  PNSkeletonExporter	_skeletonExporter;

  bool					_hasAnimation;
  bool					_saveAnimation;
  CString				_animationPath;
  PNAnimationExporter	_animationExporter;

  bool					_hasPhysics;
  bool					_savePhysics;
  CString				_physicalPath;
  PNPhysicalExporter	_physicalExporter;

  PNObjectWindow*		_owin;

  CFile					_initFile;
public:
  bool					DefaultDirection;
  Point3				Front;
  Point3				Right;
  Point3				Top;
public:
  static HWND	hParams;

  void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

  //Constructor/Destructor
  PN3DObjectExporter();
  ~PN3DObjectExporter();
  //////////////////////////////////////////////////////////////////////////
public:
  CFile*		getInitFile() {return &_initFile;}

  virtual int	initExport();
  virtual int	initFiles(CString file);
  virtual int	releaseExport();
  virtual int	exportHeader();
  virtual int	exportBody();
  virtual int	configure();
};

class PN3DObjectExporterDesc : public ClassDesc2
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

#endif /*_PN3DOBJECTEXPORTER_HPP_*/
