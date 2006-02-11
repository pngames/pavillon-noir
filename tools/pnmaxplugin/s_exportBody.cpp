/*
 * s_exportBody.cpp
 * 
 * Description :
 * PNSkeletonExporter definition
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

#include "PNSBone.hpp"
#include "PNSkeletonExporter.hpp"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

static int index = 0;

int		PNSkeletonExporter::exportBone(PNSBone* bone)
{
  if (bone->getId() >= 0)
  {
	PNMainWin::WriteLine("export bone: %i", index);

	pnsBone_t&	boneToExport = _tabBones[index++];

	boneToExport.id = bone->getId();
	boneToExport.parent = bone->getParent()->getId();
	memcpy(boneToExport.name, bone->getNode()->GetName(), min(strlen(bone->getNode()->GetName()), 31));

	memcpy(boneToExport.m_relative, &bone->getNode()->GetLocalTM(), sizeof(boneToExport.m_relative));

	PNMainWin::WriteLine("bone id: %i", boneToExport.id);
	PNMainWin::WriteLine("bone name: %s", boneToExport.name);
	PNMainWin::WriteLine("bone parent: %i", boneToExport.parent);
	PNMainWin::WriteLine("matrix relative to parent: ", boneToExport.parent);
	PNMainWin::WriteLine("\t%f %f %f %f", boneToExport.m_relative[0], boneToExport.m_relative[1], boneToExport.m_relative[2], boneToExport.m_relative[3]);
	PNMainWin::WriteLine("\t%f %f %f %f", boneToExport.m_relative[4], boneToExport.m_relative[5], boneToExport.m_relative[6], boneToExport.m_relative[7]);
	PNMainWin::WriteLine("\t%f %f %f %f", boneToExport.m_relative[8], boneToExport.m_relative[9], boneToExport.m_relative[10], boneToExport.m_relative[11]);
	PNMainWin::WriteLine("\t%f %f %f %f", boneToExport.m_relative[12], boneToExport.m_relative[13], boneToExport.m_relative[14], boneToExport.m_relative[15]);
  }

  for (PNSBone::iterator it = bone->begin(); it != bone->end(); ++it)
	exportBone(*it);

  return TRUE;
}

int	PNSkeletonExporter::exportBody()
{
  _tabBones = new pnsBone_t[_sheader.nbBones];
  memset(_tabBones, 0, sizeof(*_tabBones) * _sheader.nbBones);

  index = 0;

  exportBone(_topLevelBone);

  //////////////////////////////////////////////////////////////////////////
  // EXPORT

  _file->Write(_tabBones, sizeof(*_tabBones) * _sheader.nbBones);

  //////////////////////////////////////////////////////////////////////////
  // CLEAN

  delete _tabBones;

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////
};
