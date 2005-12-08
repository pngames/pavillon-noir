/*
* PNPhysicsWin.cpp
* 
* Description :
* PNPhysicsWin definition
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

#include "PNPhysicalExporter.hpp"

#include "PNPhysicsWin.hpp"
#include ".\pnphysicswin.hpp"

IMPLEMENT_DYNAMIC(PNPhysicsWin, CDialog)
PNPhysicsWin::PNPhysicsWin(PNPhysicalExporter* exporter, CWnd* pParent /*=NULL*/)
: CDialog(PNPhysicsWin::IDD, pParent), _exporter(exporter)
{
}

PNPhysicsWin::~PNPhysicsWin()
{
}

void
PNPhysicsWin::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}

BOOL  
PNPhysicsWin::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  

  return TRUE;
}

BEGIN_MESSAGE_MAP(PNPhysicsWin, CDialog)
  ON_BN_CLICKED(IDC_BB_PHYSICS, OnBnClickedBbPhysics)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// Gestionnaires de messages PNPhysicsWin


void PNPhysicsWin::OnBnClickedBbPhysics()
{
  CString	name;
  GetDlgItemText(IDC_T_PHYSICS, name);

  CFileDialog fileDlg(FALSE, "xml", name, OFN_HIDEREADONLY 
	| (IsDlgButtonChecked(IDC_C_SAVE) == TRUE ? OFN_OVERWRITEPROMPT : OFN_FILEMUSTEXIST), 
	  "Opal Files(*.xml)|*.xml|Model Files(*.pnm)|*.pnm||", this);

  // Initializes m_ofn structure
  fileDlg.m_ofn.lpstrTitle = "Choice file link";

  // Call DoModal
  if (fileDlg.DoModal() == IDOK)
  {
	name = fileDlg.GetPathName();
	SetDlgItemText(IDC_T_PHYSICS, name);

	_exporter->type = fileDlg.GetOFN().nFilterIndex;
  }
}

void PNPhysicsWin::OnBnClickedOk()
{
  _exporter->save = IsDlgButtonChecked(IDC_C_SAVE) == TRUE;
  
  GetDlgItemText(IDC_T_PATH, _exporter->path);

  OnOK();
}
