/*
 * PNAnimationWin.cpp
 * 
 * Description :
 * PNAnimationWin definition
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

#include "pnmaxplugin.h"
#include "PNAnimationWin.hpp"
#include "PNAnimationExporter.hpp"


// Bo�e de dialogue PNAnimationWin

IMPLEMENT_DYNAMIC(PNAnimationWin, CDialog)
PNAnimationWin::PNAnimationWin(PNAnimationExporter* animation, CWnd* pParent /*=NULL*/)
	: PNSkeletonWin(animation, PNAnimationWin::IDD, pParent), _animation(animation)
{
}

PNAnimationWin::~PNAnimationWin()
{
}

void PNAnimationWin::DoDataExchange(CDataExchange* pDX)
{
  PNSkeletonWin::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_A_T_FRAMERATE, t_framerate);
  DDX_Control(pDX, IDC_A_T_NAME, t_name);
}


BEGIN_MESSAGE_MAP(PNAnimationWin, CDialog)
END_MESSAGE_MAP()

BOOL  PNAnimationWin::OnInitDialog()
{
  if (PNSkeletonWin::OnInitDialog() == FALSE)
	return FALSE;

  t_name.SetWindowText(_animation->name);

  CString framerate;
  framerate.Format("%d", _animation->framerate);
  t_framerate.SetWindowText(framerate);

  return TRUE;
}

// Gestionnaires de messages PNAnimationWin
