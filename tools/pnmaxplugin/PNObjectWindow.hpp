/*
 * PNObjectWindow.hpp
 * 
 * Description :
 * PNObjectWindow declaration
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
#include "afxwin.h"

#include "PN3DObjectExporter.hpp"

// Bo�e de dialogue PNObjectWindow

class PNObjectWindow : public CDialog
{
	DECLARE_DYNAMIC(PNObjectWindow)

public:
	PNObjectWindow(PN3DObjectExporter* exporter, CWnd* pParent = NULL);   // constructeur standard
	virtual ~PNObjectWindow();

// Donn�s de bo�e de dialogue
	enum { IDD = IDD_OBJ_EXPORT };

public:

  bool		hasModel() {return _exporter->_hasModel;}
  CString	getModelFile();
  CString	getModelFullPath();
  
  bool		hasMaterials() {return _exporter->_hasMaterials;}
  int		getNbMaterials();
  CString	getMaterialFile(int index);
  CString	getMaterialsFullPath();

  bool		hasSkeleton() {return _exporter->_hasSkeleton;}
  CString	getSkeletonFile();
  CString	getSkeletonFullPath();
  
  bool		hasAnimation() {return _exporter->_hasAnimation;}
  CString	getAnimationFile();
  CString	getAnimationFullPath();

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV

  DECLARE_MESSAGE_MAP()
private:
  CString	makePathFromDir(CString& root, CString& filename, LPCTSTR lpszDefExt, LPCSTR subDirectory);
  CString	makePathFromDir(CEdit& textField, LPCTSTR lpszDefExt, LPCSTR subDirectory);
  void		getPath(CEdit& textField, LPCTSTR lpszDefExt, LPCTSTR lpszFilter, LPCSTR lpstrTitle, LPCSTR subDirectory);
  BOOL		verifSubTextfield(CEdit& textField);

  PN3DObjectExporter* _exporter;
public:
  virtual BOOL OnInitDialog();

  CButton _c_model;

  afx_msg void OnBnClickedBbRoot();
  CEdit t_root;
  afx_msg void OnBnClickedBbModel();
  CEdit t_model;
  afx_msg void OnBnClickedBbMaterial();
  afx_msg void OnBnClickedBbSkeleton();
  afx_msg void OnBnClickedBbAnimation();
  CEdit t_materials;
  CEdit t_skeleton;
  CEdit t_animation;
  afx_msg void OnBnClickedCModel();
  CButton bt_model;
  CButton bt_option_model;
  afx_msg void OnBnClickedCMaterials();
  CButton bt_option_materials;
  CButton bt_materials;
  afx_msg void OnBnClickedCSkeleton();
  afx_msg void OnBnClickedCAnimation();
  CButton bt_option_skeleton;
  CButton bt_skeleton;
  CButton bt_option_animation;
  CButton bt_animation;
  afx_msg void OnEnUpdateTModel();
  afx_msg void OnEnUpdateTMaterials();
  afx_msg void OnEnUpdateTSkeleton();
  afx_msg void OnEnUpdateTAnimation();
  afx_msg void OnBnClickedBoModel();
  afx_msg void OnBnClickedBoMaterials();
  afx_msg void OnBnClickedBoSkeleton();
  afx_msg void OnBnClickedBoAnimation();
  afx_msg void OnEnChangeTMaterials();
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedBoGeneral();
};
