/*
 * a_exportBody.cpp
 * 
 * Description :
 * PNAnimationExporter definition
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
#include "PNAnimationExporter.hpp"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

int		PNAnimationExporter::exportRotSampleKeys(IGameControl *control, DWORD type, IGameKeyTab &keyTab)
{
  if (control == NULL)
	return TRUE;

  pnaKeyRot_t* tabRot = new pnaKeyRot_t[keyTab.Count()];

  for (int i = 0; i < keyTab.Count(); ++i)
  {
	IGameKey&	  key = keyTab[i];
	pnaKeyRot_t&  rot = tabRot[i];

	//////////////////////////////////////////////////////////////////////////
	
	rot.time = key.t;

	//////////////////////////////////////////////////////////////////////////
	
	if (type == IGAME_TM)
	{
	  Matrix3&	mat = key.sampleKey.gval.ExtractMatrix3();

	  AffineParts ap;
	  decomp_affine(mat, &ap);

	  memcpy(rot.rot, ap.q.Inverse(), sizeof(rot.rot));
	}
	else
	{
	  memcpy(rot.rot, key.sampleKey.qval.Inverse(), sizeof(rot.rot));
	}
  }

  //////////////////////////////////////////////////////////////////////////

  _file->Write(tabRot, sizeof(*tabRot) * keyTab.Count());

  //////////////////////////////////////////////////////////////////////////
  // CLEAN

  delete[] tabRot;

  return TRUE;
}

int		PNAnimationExporter::exportPosSampleKeys(IGameControl *control, DWORD type, IGameKeyTab &keyTab)
{
  if (control == NULL)
	return TRUE;

  pnaKeyPos_t* tabPos = new pnaKeyPos_t[keyTab.Count()];

  for (int i = 0; i < keyTab.Count(); ++i)
  {
	IGameKey&		key = keyTab[i];
	pnaKeyPos_t&  pos = tabPos[i];

	//////////////////////////////////////////////////////////////////////////

	pos.time = key.t;

	//////////////////////////////////////////////////////////////////////////

	if (type == IGAME_TM)
	{
	  Matrix3&	mat = key.sampleKey.gval.ExtractMatrix3();

	  AffineParts ap;
	  decomp_affine(mat, &ap);

	  memcpy(pos.pos, ap.t, sizeof(pos.pos));
	}
	else
	{
	  memcpy(pos.pos, key.sampleKey.pval, sizeof(pos.pos));
	}
  }

  //////////////////////////////////////////////////////////////////////////

  _file->Write(tabPos, sizeof(*tabPos) * keyTab.Count());

  //////////////////////////////////////////////////////////////////////////
  // CLEAN

  delete[] tabPos;

  return TRUE;
}

int		PNAnimationExporter::exportBone(PNSBone* bone)
{
  if (bone->getId() >= 0)
  {
	PNMainWin::WriteLine("Export bone: %i %s", bone->getId(), bone->getNode()->GetName());

	pnaBone_t	boneToExport;

	boneToExport.id = bone->getId();

	IGameKeyTab r_sample;
	IGameKeyTab p_sample;

	IGameControl* control = bone->getNode()->GetIGameControl();

	bool  biped = false;

	if (control == NULL || !bone->isExported())
	{
	  boneToExport.nbRot = 0;
	  boneToExport.nbPos = 0;
	}
	else
	{
	  if (
		control->GetControlType(IGAME_ROT) == IGameControl::IGAME_BIPED ||
		control->GetControlType(IGAME_POS) == IGameControl::IGAME_BIPED)
		biped = true;

	  if (biped == false)
	  {
		control->GetFullSampledKeys(r_sample, framerate, IGameControlType(IGAME_ROT), false);
		control->GetFullSampledKeys(p_sample, framerate, IGameControlType(IGAME_POS), false);
	  }
	  else
	  {
		control->GetFullSampledKeys(r_sample, framerate, IGameControlType(IGAME_TM));
		control->GetFullSampledKeys(p_sample, framerate, IGameControlType(IGAME_TM));
	  }

	  boneToExport.nbRot = r_sample.Count();
	  boneToExport.nbPos = p_sample.Count();
	}

	//////////////////////////////////////////////////////////////////////////

	_file->Write(&boneToExport, sizeof(boneToExport));

	//////////////////////////////////////////////////////////////////////////
	// EXPORT tabs

	if (biped == false)
	{
	  exportRotSampleKeys(control, IGAME_ROT, r_sample);
	  exportPosSampleKeys(control, IGAME_POS, p_sample);
	}
	else
	{
	  exportRotSampleKeys(control, IGAME_TM, r_sample);
	  exportPosSampleKeys(control, IGAME_TM, p_sample);
	}
  }

  for (PNSBone::iterator it = bone->begin(); it != bone->end(); ++it)
	exportBone(*it);

  return TRUE;
}

int		PNAnimationExporter::exportBody()
{
  exportBone(_topLevelBone);

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////
};
