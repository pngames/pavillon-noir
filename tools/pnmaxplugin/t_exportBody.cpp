/*
 * t_exportBody.cpp
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

using namespace PN;
using namespace std;

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

int		PNMaterialExporter::exportBody()
{
  IGameMaterial*  igMat = _matToExport->igMaterial;

  CString dir = _directory;

  CString matDir = PN::DEF::materialFilePath.c_str();
  matDir.Replace('/', '\\');

  if (dir.Find(matDir) >= 0)
  {
	dir.Truncate(dir.Find(matDir));
	dir += PN::DEF::texturesFilePath.c_str();
  }

  for (int i = 0; i < _header.nbMap; ++i)
  {
	IGameTextureMap*  texMap = igMat->GetIGameTextureMap(i);
	pntMap_t		  map;
	char*			  fileName = NULL;

	if (texMap->IsEntitySupported())  // Texture file
	{
	  fileName = PathFindFileName(texMap->GetBitmapFileName());

	  //////////////////////////////////////////////////////////////////////////
	  PNMainWin::WriteLine("Copy image file %s", texMap->GetBitmapFileName());
	  PNMainWin::WriteLine("to %s", dir + fileName);

	  CopyFile(texMap->GetBitmapFileName(), dir + fileName, FALSE);

	  //////////////////////////////////////////////////////////////////////////

	  map.lenght = (pnuint)strlen(fileName) + 1;
	}
	else
	  map.lenght = 0;

	_file->Write(&map, sizeof(map));
	_file->Write(fileName, map.lenght);
  }

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////
};
