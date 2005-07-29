/*
 * PNSkeletonWin.hpp
 * 
 * Description :
 * PNSkeletonWin declaration
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


// Bo�e de dialogue PNSkeletonWin

class PNSBone;
class PNSkeletonExporter;

class PNSkeletonWin : public CDialog
{
	DECLARE_DYNAMIC(PNSkeletonWin)

public:
	PNSkeletonWin(PNSkeletonExporter *skeleton, UINT nIDTemplate = IDD, CWnd* pParent = NULL);   // constructeur standard
	virtual ~PNSkeletonWin();

// Donn�s de bo�e de dialogue
	enum { IDD = IDD_S_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
  void		_parseBone(HTREEITEM parent, PNSBone* bone);
  void		_updateBone(HTREEITEM hItem);

  PNSkeletonExporter* _skeleton;
  PNSBone*	_topLevelBone;
public:
  virtual BOOL OnInitDialog();

  CTreeCtrl _treeSkeletor;
  afx_msg void OnBnClickedOk();
};
