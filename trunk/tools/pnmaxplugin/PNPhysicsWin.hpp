/*
* PNPhysicsWin.hpp
* 
* Description :
* PNPhysicsWin declaration
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

class PNPhysicalExporter;

class					PNPhysicsWin : public CDialog
{
  DECLARE_DYNAMIC(PNPhysicsWin)

public:
  PNPhysicsWin(PNPhysicalExporter* exporter, CWnd* pParent = NULL);
  virtual ~PNPhysicsWin();

  enum { IDD = IDD_PNP_CONFIG };

protected:
  virtual void			DoDataExchange(CDataExchange* pDX);

  DECLARE_MESSAGE_MAP()
protected:
  PNPhysicalExporter*	_exporter;
public:
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedBbPhysics();
  afx_msg void OnBnClickedOk();
};
