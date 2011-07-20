/*
 * t_export.cpp
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

using namespace std;

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef map<CString,CString> MAP_STRING;

int PNMaterialExporter::initFiles(CString file)
{
  int		lenght;
  CString	path = PathFindFileName(file);
  CString	ptmp = path;
  ptmp.Truncate(ptmp.GetLength() - 4);

  CString	lpath = path.MakeLower();

  CString	tmp;

  for (VECTOR_MATERIALS::iterator it = _vectorMaterials.begin(); it != _vectorMaterials.end(); ++it)
  {
	material_t&	mat = *it;

	tmp.Format("_%s.pnt", mat.name);

	if (
	  (lenght = lpath.Find(tmp.MakeLower())) != -1
	  && ptmp.GetLength() > lenght)
	{
	  ptmp.Truncate(lenght);
	}
  }

  for (VECTOR_MATERIALS::iterator it = _vectorMaterials.begin(); it != _vectorMaterials.end(); ++it)
  {
	material_t&	mat = *it;

	mat.file.Format("%s_%s", ptmp, mat.name);
  }

  PNMainWin::WriteLine("nb materials: %i", _vectorMaterials.size());

  return TRUE;
}

int PNMaterialExporter::initExport()
{
  PNMainWin::WriteLine("## Init materials exporter ##");

  memset(&_header, 0, sizeof (_header));

  //////////////////////////////////////////////////////////////////////////
  // magic

  memcpy(_header.magic, PNT_MAGIC, strlen(PNT_MAGIC));
  _header.version = 001;

  //////////////////////////////////////////////////////////////////////////
  // materials

  MAP_STRING  mapString;

  for (int i = 0; i < _igameScene->GetRootMaterialCount(); ++i)
  {
	IGameMaterial *material = _igameScene->GetRootMaterial(i);

	if (material->IsSubObjType())
	  for (int i = 0; i < material->GetSubMaterialCount(); ++i)
	  {
		material_t	mat(true, transformToSystem(material->GetSubMaterial(i)->GetMaterialName()), material->GetSubMaterial(i));

		//////////////////////////////////////////////////////////////////////////

		CString	ntmp(mat.name);

		for (int i = 0; mapString.find(mat.name) != mapString.end(); ++i)
		  mat.name.Format("%s%i", ntmp, i);

		//////////////////////////////////////////////////////////////////////////

		PNMainWin::WriteLine("new materials : %s", mat.name);

		_vectorMaterials.push_back(mat);
	  }
	else
	{
	  material_t	mat(true, transformToSystem(material->GetMaterialName()), material);

	  //////////////////////////////////////////////////////////////////////////

	  CString	ntmp(mat.name);

	  for (int i = 0; mapString.find(mat.name) != mapString.end(); ++i)
		mat.name.Format("%s_%i", ntmp, i);

	  //////////////////////////////////////////////////////////////////////////

	  PNMainWin::WriteLine("new materials : %s", mat.name);

	  _vectorMaterials.push_back(mat);
	}
  }

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int		PNMaterialExporter::export(CString path)
{
  _directory = path;
  _directory.Truncate(_directory.GetLength() - (int)strlen(PathFindFileName(_directory)));

  int err = TRUE;

  for (VECTOR_MATERIALS::iterator it = _vectorMaterials.begin(); it != _vectorMaterials.end(); ++it)
  {
	_matToExport = &(*it);

	if (!_matToExport->exported)
	  continue ;

	PNMainWin::WriteLine("Start export %s", _matToExport->name);

	//////////////////////////////////////////////////////////////////////////

	CString	ftmp = _directory + _matToExport->file + "." + PNT_EXT;

	//////////////////////////////////////////////////////////////////////////

	PNMainWin::WriteLine("");
	PNMainWin::WriteLine("Opening file %s ...", ftmp);

	_file = new CFile(ftmp, CFile::modeCreate | CFile::modeReadWrite);
	PNMainWin::WriteLine("File opened", ftmp);

	//////////////////////////////////////////////////////////////////////////

	PNMainWin::WriteLine("");
	PNMainWin::WriteLine("Starting export");

	//////////////////////////////////////////////////////////////////////////
	

	PNMainWin::WriteLine("Export Header");
	err = exportHeader();
	if (err == TRUE)
	{
	  PNMainWin::WriteLine("Export Body");
	  err = exportBody();
	}

	//////////////////////////////////////////////////////////////////////////

	PNMainWin::WriteLine("");
	PNMainWin::WriteLine("Closing file %s ...", ftmp);

	_file->Close();

	delete _file;
  }

  return err;
}

//////////////////////////////////////////////////////////////////////////
};
