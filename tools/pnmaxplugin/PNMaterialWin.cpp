/*
 * PNMaterialWin.cpp
 * 
 * Description :
 * PNMaterialWin definition
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

#include "PNMaterialWin.hpp"


// Bo�e de dialogue PNMaterialWin

IMPLEMENT_DYNAMIC(PNMaterialWin, CDialog)
PNMaterialWin::PNMaterialWin(VECTOR_MATERIALS& materials, CWnd* pParent /*=NULL*/)
: CDialog(PNMaterialWin::IDD, pParent), _listMaterials(materials)
{
  
}

PNMaterialWin::~PNMaterialWin()
{
}

void PNMaterialWin::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MATERIALS, _materials);
}


BEGIN_MESSAGE_MAP(PNMaterialWin, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_NOTIFY(LVN_ENDLABELEDIT, IDC_MATERIALS, OnLvnEndlabeleditMaterials)
END_MESSAGE_MAP()


// Gestionnaires de messages PNMaterialWin

BOOL  PNMaterialWin::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  ListView_SetExtendedListViewStyle(_materials.m_hWnd, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);

  int i = 0;
  for (VECTOR_MATERIALS::iterator it = _listMaterials.begin(); it != _listMaterials.end(); ++it, ++i)
  {
	_materials.InsertItem(LVIF_TEXT|LVIF_STATE, i, (*it).file, 0, 0, 0, 0);
	ListView_SetItemState(_materials.m_hWnd, i, UINT((int((*it).exported) + 1) << 12), LVIS_STATEIMAGEMASK);
  }

  return TRUE;
}

void PNMaterialWin::OnBnClickedOk()
{
  int i = 0;
  for (VECTOR_MATERIALS::iterator it = _listMaterials.begin(); it != _listMaterials.end(); ++it, ++i)
  {
	(*it).file = _materials.GetItemText(i, 0);
	(*it).exported = _materials.GetCheck(i) == TRUE;//ListView_GetCheckState(_materials.m_hWnd, i) != 0;
  }

  //////////////////////////////////////////////////////////////////////////
  
  OnOK();
}

void PNMaterialWin::OnLvnEndlabeleditMaterials(NMHDR *pNMHDR, LRESULT *pResult)
{
  NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

  if (pDispInfo->item.pszText != NULL)
	_materials.SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);
  
  *pResult = 0;
}
