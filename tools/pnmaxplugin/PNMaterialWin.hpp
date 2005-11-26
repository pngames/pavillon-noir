/*
* PNMaterialWin.hpp
* 
* Description :
* PNMaterialWin declaration
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

#pragma once
#include "afxcmn.h"

#include "PNMaterialExporter.hpp"

// Bo�e de dialogue PNMaterialWin

class PNMaterialWin : public CDialog
{
  DECLARE_DYNAMIC(PNMaterialWin)

public:
  PNMaterialWin(VECTOR_MATERIALS& materials, CWnd* pParent = NULL);   // constructeur standard
  virtual ~PNMaterialWin();

  // Donn�s de bo�e de dialogue
  enum { IDD = IDD_T_CONFIG };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV

  DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
private:
  VECTOR_MATERIALS& _listMaterials;
  CListCtrl _materials;
public:
  afx_msg void OnBnClickedOk();
  afx_msg void OnLvnEndlabeleditMaterials(NMHDR *pNMHDR, LRESULT *pResult);
};
