/*
 * s_exportHeader.cpp
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

#include "PNSkeletonExporter.hpp"
#include "PNSBone.hpp"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

int PNSkeletonExporter::exportHeader()
{
  _file->Write(&_sheader, sizeof(_sheader));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////

int	PNSkeletonExporter::parseNodeHeader(PNSBone*  parent, IGameNode* node)
{
  if (node == NULL)
	return TRUE;

  IGameObject *obj = node->GetIGameObject();

  if (obj->GetIGameType() == IGameObject::IGAME_BONE ||
	obj->GetIGameType() == IGameObject::IGAME_HELPER ||
	node->GetChildCount())
  {
	parent = new PNSBone(parent, node);
  }

  node->ReleaseIGameObject();

  for (pnuint i = 0; i < node->GetChildCount(); ++i)
  {
	parseNodeHeader(parent, node->GetNodeChild(i));
  }

  return TRUE;
}

int PNSkeletonExporter::initExport()
{
  PNMainWin::WriteLine("## Init skeleton exporter ##");

  memset(&_sheader, 0, sizeof (_sheader));

  //////////////////////////////////////////////////////////////////////////
  // magic

  memcpy(_sheader.magic, PNS_MAGIC, strlen(PNS_MAGIC));
  _sheader.version = 001;

  //////////////////////////////////////////////////////////////////////////
  // bones

  _topLevelBone = new PNSBone();

  for (pnuint i = 0; i < _igameScene->GetTopLevelNodeCount(); ++i)
  {
	parseNodeHeader(_topLevelBone, _igameScene->GetTopLevelNode(i));
  }

  //////////////////////////////////////////////////////////////////////////
  
  _sheader.nbBones = _topLevelBone->getNbBones();

  //////////////////////////////////////////////////////////////////////////
  
  PNMainWin::WriteLine("nb bones: %i", _sheader.nbBones);

  //////////////////////////////////////////////////////////////////////////

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////
};
