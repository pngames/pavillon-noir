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

#include "PNPhysicsWin.hpp"
#include ".\pnphysicswin.hpp"

IMPLEMENT_DYNAMIC(PNPhysicsWin, CDialog)
PNPhysicsWin::PNPhysicsWin(CWnd* pParent /*=NULL*/)
: CDialog(PNPhysicsWin::IDD, pParent)
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
END_MESSAGE_MAP()


// Gestionnaires de messages PNPhysicsWin


void PNPhysicsWin::OnBnClickedBbPhysics()
{
  /*CString	name;
  textField.GetWindowText(name);

  /*CFileFind	finder;

  dir = dir + "/" + subDirectory;
  dir.Delete(dir.GetLength() - 1);
  dir.Replace('/', '\\');

  PNMainWin::WriteLine(dir);

  if (finder.FindFile(dir) == FALSE)
  {
	dir = _exporter->getInitFile()->GetFilePath();
	PNMainWin::WriteLine("dir=%s", dir);
	dir.Replace(_exporter->getInitFile()->GetFileName(), name);
	PNMainWin::WriteLine("dir=%s", dir);
	int l = name.GetLength();
	name = dir;
	dir.Truncate(dir.GetLength() - l - 1);
	PNMainWin::WriteLine("dir=%s", dir);
  }
  else
	name = dir + '\\' + name;

  PNMainWin::WriteLine(name);

  // Create an instance
  CFileDialog fileDlg(FALSE, lpszDefExt, name, OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, lpszFilter, this);

  // Initializes m_ofn structure
  fileDlg.m_ofn.lpstrTitle = lpstrTitle;
  //fileDlg.m_ofn.lpstrInitialDir = dir;

  // Call DoModal
  if (fileDlg.DoModal() == IDOK)
  {
	name = fileDlg.GetPathName();
	if (name.Find(dir) == 0)
	  textField.SetWindowText(name.GetString() + dir.GetLength() + 1);
  }*/
}
