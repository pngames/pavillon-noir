/*
 * t_exportHeader.cpp
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

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

int	  PNMaterialExporter::exportHeader()
{
  IGameMaterial*  igMat = _matToExport->igMaterial;

  _getPoint3Property(igMat->GetAmbientData(), _header.ambient, (pnfloat*)&_defaultColor);
  _header.ambient[3] = _getFloatProperty(igMat->GetOpacityData(), 1.0f);

  //////////////////////////////////////////////////////////////////////////
  
  _getPoint3Property(igMat->GetDiffuseData(), _header.diffuse, (pnfloat*)&_defaultColor);
  _header.diffuse[3] = _getFloatProperty(igMat->GetOpacityData(), 1.0f);

  //////////////////////////////////////////////////////////////////////////
  
  _getPoint3Property(igMat->GetEmissiveData(), _header.emissive, (pnfloat*)&_defaultColor);
  _header.diffuse[3] = 1.0f;

  //////////////////////////////////////////////////////////////////////////
  
  _getPoint3Property(igMat->GetSpecularData(), _header.specular, (pnfloat*)&_defaultColor);
  _header.diffuse[3] = 1.0f;

  //////////////////////////////////////////////////////////////////////////
  
  _header.opacity = _getFloatProperty(igMat->GetOpacityData(), 1.0f);
  _header.glossiness = _getFloatProperty(igMat->GetGlossinessData(), 1.0f);

  //////////////////////////////////////////////////////////////////////////
  
  _header.nbMap = igMat->GetNumberOfTextureMaps();

  //////////////////////////////////////////////////////////////////////////
  
  PNMainWin::WriteLine("Ambient : %f %f %f %f", _header.ambient[0], _header.ambient[1], _header.ambient[2], _header.ambient[3]);
  PNMainWin::WriteLine("Diffuse : %f %f %f %f", _header.diffuse[0], _header.diffuse[1], _header.diffuse[2], _header.diffuse[3]);
  PNMainWin::WriteLine("Emissive : %f %f %f %f", _header.emissive[0], _header.emissive[1], _header.emissive[2], _header.emissive[3]);
  PNMainWin::WriteLine("Specular : %f %f %f %f", _header.specular[0], _header.specular[1], _header.specular[2], _header.specular[3]);

  PNMainWin::WriteLine("Opacity : %f", _header.opacity);
  PNMainWin::WriteLine("Glossiness : %f", _header.glossiness);

  PNMainWin::WriteLine("nbMap : %d", _header.nbMap);

  _file->Write(&_header, sizeof(_header));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////
};
