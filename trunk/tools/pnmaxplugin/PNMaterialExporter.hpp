/*
 * PNMaterialExporter.hpp
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

#ifndef _PNMATERIALEXPORTER_HPP_
# define _PNMATERIALEXPORTER_HPP_

#ifdef _DEBUG
# define PNMATERIALEXPORTER_CLASS_ID	Class_ID(0x64b3832, 0x17841e1)
# define PNT_LONGDESC					"Material exporter for Pavillon Noir 3D objects (debug)"
# define PNT_SHORTDESC					"Pavillon Noir Material export (debug)"
#else
# define PNMATERIALEXPORTER_CLASS_ID	Class_ID(0x360a1c1e, 0x727c35c2)
# define PNT_LONGDESC					"Material exporter for Pavillon Noir 3D objects"
# define PNT_SHORTDESC					"Pavillon Noir Material export"
#endif

#include "PNExporter.hpp"

#include "pnt_format.h"

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef struct	  material_s
{
  bool			  exported;
  CString		  name;
  IGameMaterial*  igMaterial;

  CString		  file;

  material_s(bool e, const char* n, IGameMaterial* m) : exported(e), name(n), igMaterial(m) {}
}				  material_t;

typedef std::vector<material_t> VECTOR_MATERIALS;

class PNMaterialExporter : public PNExporter
{
protected:
  VECTOR_MATERIALS  _vectorMaterials;
public:
  static HWND	hParams;

  void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

  //Constructor/Destructor
  PNMaterialExporter();
  ~PNMaterialExporter();
  //////////////////////////////////////////////////////////////////////////
public:
  virtual int	initExport();
  virtual int	initFiles(CString file);
  virtual int	export(CString path);

  virtual int	releaseExport();

  virtual int	exportHeader();
  virtual int	exportBody();

  virtual int	configure();

  int			getNBMaterials();
  CString		getMaterialFile(int index);
protected:
  pntHeader_t	_header;

  material_t*	_matToExport;
};

class PNMaterialExporterDesc : public ClassDesc2
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

#endif /*_PNMATERIALEXPORTER_HPP_*/
