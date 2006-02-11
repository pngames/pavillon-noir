/*
 * PNObjectWindow.cpp
 * 
 * Description :
 * PNObjectWindow definition
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
#include "pnresources.h"

#include "PNOConfig.hpp"

#include "PNObjectWindow.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Bo�e de dialogue PNObjectWindow

IMPLEMENT_DYNAMIC(PNObjectWindow, CDialog)
PNObjectWindow::PNObjectWindow(PN3DObjectExporter* exporter, CWnd* pParent /*=NULL*/)
	: CDialog(PNObjectWindow::IDD, pParent), _exporter(exporter)
{
}

PNObjectWindow::~PNObjectWindow()
{
}

//////////////////////////////////////////////////////////////////////////

CString		
PNObjectWindow::getModelFile()
{
  return _exporter->_modelPath;
}

CString		
PNObjectWindow::getModelFullPath()
{
  return makePathFromDir(_exporter->_rootPath, _exporter->_modelPath, PNM_EXT, PN::DEF::modelFilePath.c_str());
}

int		
PNObjectWindow::getNbMaterials()
{
  return _exporter->_materialsExporter.getNBMaterials();
}

CString		
PNObjectWindow::getMaterialFile(int index)
{
  CString	path = _exporter->_materialsExporter.getMaterialFile(index) + "." + PNT_EXT;

  CFile		file;
  file.SetFilePath(_exporter->_materialsPath);

  CString	name = _exporter->_materialsPath;
  name.Replace(file.GetFileName(), path);

  PNMainWin::WriteLine(name);

  return name;
}

CString	
PNObjectWindow::getMaterialsFullPath()
{
  return makePathFromDir(_exporter->_rootPath, _exporter->_materialsPath, PNT_EXT, PN::DEF::materialFilePath.c_str());
}

CString	
PNObjectWindow::getSkeletonFile()
{
  return _exporter->_skeletonPath;
}

CString	
PNObjectWindow::getSkeletonFullPath()
{
  return makePathFromDir(_exporter->_rootPath, _exporter->_skeletonPath, PNS_EXT, PN::DEF::skeletonFilePath.c_str());
}

CString		
PNObjectWindow::getAnimationFile()
{
  return _exporter->_animationPath;
}

CString		
PNObjectWindow::getAnimationFullPath()
{
  return makePathFromDir(_exporter->_rootPath, _exporter->_animationPath, PNA_EXT, PN::DEF::animationFilePath.c_str());
}

CString	
PNObjectWindow::getPhysicalFile()
{
  return _exporter->_physicalPath;
}

CString
PNObjectWindow::getPhysicalFullPath()
{
  return makePathFromDir(_exporter->_rootPath, _exporter->_physicalPath, PNP_EXT, PN::DEF::physicsFilePath.c_str());
}

//////////////////////////////////////////////////////////////////////////

void 
PNObjectWindow::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_C_MODEL, _c_model);
  DDX_Control(pDX, IDC_T_ROOT, t_root);
  DDX_Control(pDX, IDC_T_MODEL, t_model);
  DDX_Control(pDX, IDC_T_MATERIALS, t_materials);
  DDX_Control(pDX, IDC_T_SKELETON, t_skeleton);
  DDX_Control(pDX, IDC_T_ANIMATION, t_animation);
  DDX_Control(pDX, IDC_BB_MODEL, bt_model);
  DDX_Control(pDX, IDC_BO_MODEL, bt_option_model);
  DDX_Control(pDX, IDC_BO_MATERIALS, bt_option_materials);
  DDX_Control(pDX, IDC_BB_MATERIAL, bt_materials);
  DDX_Control(pDX, IDC_BO_SKELETON, bt_option_skeleton);
  DDX_Control(pDX, IDC_BB_SKELETON, bt_skeleton);
  DDX_Control(pDX, IDC_BO_ANIMATION, bt_option_animation);
  DDX_Control(pDX, IDC_BB_ANIMATION, bt_animation);
  DDX_Control(pDX, IDC_T_PHYSICS, t_physics);
  DDX_Control(pDX, IDC_BB_PHYSICS, bt_physics);
  DDX_Control(pDX, IDC_BO_PHYSICS, bt_option_physics);
}


BEGIN_MESSAGE_MAP(PNObjectWindow, CDialog)
  ON_BN_CLICKED(IDC_BB_ROOT, OnBnClickedBbRoot)
  ON_BN_CLICKED(IDC_BB_MODEL, OnBnClickedBbModel)
  ON_BN_CLICKED(IDC_BB_MATERIAL, OnBnClickedBbMaterial)
  ON_BN_CLICKED(IDC_BB_SKELETON, OnBnClickedBbSkeleton)
  ON_BN_CLICKED(IDC_BB_ANIMATION, OnBnClickedBbAnimation)
  ON_BN_CLICKED(IDC_C_MODEL, OnBnClickedCModel)
  ON_BN_CLICKED(IDC_C_MATERIALS, OnBnClickedCMaterials)
  ON_BN_CLICKED(IDC_C_SKELETON, OnBnClickedCSkeleton)
  ON_BN_CLICKED(IDC_C_ANIMATION, OnBnClickedCAnimation)
  ON_EN_UPDATE(IDC_T_MODEL, OnEnUpdateTModel)
  ON_EN_UPDATE(IDC_T_MATERIALS, OnEnUpdateTMaterials)
  ON_EN_UPDATE(IDC_T_SKELETON, OnEnUpdateTSkeleton)
  ON_EN_UPDATE(IDC_T_ANIMATION, OnEnUpdateTAnimation)
  ON_BN_CLICKED(IDC_BO_MODEL, OnBnClickedBoModel)
  ON_BN_CLICKED(IDC_BO_MATERIALS, OnBnClickedBoMaterials)
  ON_BN_CLICKED(IDC_BO_SKELETON, OnBnClickedBoSkeleton)
  ON_BN_CLICKED(IDC_BO_ANIMATION, OnBnClickedBoAnimation)
  ON_EN_CHANGE(IDC_T_MATERIALS, OnEnChangeTMaterials)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDC_BO_GENERAL, OnBnClickedBoGeneral)
  ON_BN_CLICKED(IDC_BO_PHYSICS, OnBnClickedBoPhysics)
  ON_BN_CLICKED(IDC_C_PHYSICS, OnBnClickedCPhysics)
  ON_BN_CLICKED(IDC_BB_PHYSICS, OnBnClickedBbPhysics)
  ON_BN_CLICKED(IDC_RB_PHYS_MODEL, OnBnClickedRbPhysModel)
  ON_BN_CLICKED(IDC_RB_PHYS_OPTIONS, OnBnClickedRbPhysOptions)
END_MESSAGE_MAP()

// Gestionnaires de messages PNObjectWindow

BOOL PNObjectWindow::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  CheckDlgButton(IDC_C_MODEL, _exporter->_hasModel ? BST_CHECKED : BST_UNCHECKED);
  CheckDlgButton(IDC_C_MODEL_SAVE, _exporter->_saveModel ? BST_CHECKED : BST_UNCHECKED);

  CheckDlgButton(IDC_C_MATERIALS, _exporter->_hasMaterials ? BST_CHECKED : BST_UNCHECKED);
  CheckDlgButton(IDC_C_MATERIALS_SAVE, _exporter->_saveMaterials ? BST_CHECKED : BST_UNCHECKED);

  CheckDlgButton(IDC_C_SKELETON, _exporter->_hasSkeleton ? BST_CHECKED : BST_UNCHECKED);
  CheckDlgButton(IDC_C_SKELETON_SAVE, _exporter->_saveSkeleton ? BST_CHECKED : BST_UNCHECKED);

  CheckDlgButton(IDC_C_ANIMATION, _exporter->_hasAnimation ? BST_CHECKED : BST_UNCHECKED);
  CheckDlgButton(IDC_C_ANIMATION_SAVE, _exporter->_saveAnimation ? BST_CHECKED : BST_UNCHECKED);

  CheckDlgButton(IDC_C_PHYSICS, _exporter->_hasPhysics ? BST_CHECKED : BST_UNCHECKED);
  CheckDlgButton(IDC_C_PHYSICS_SAVE, _exporter->_savePhysics ? BST_CHECKED : BST_UNCHECKED);

  //////////////////////////////////////////////////////////////////////////

  CString objPath = PN::DEF::objectFilePath.c_str();
  objPath.Replace('/', '\\');

  PNMainWin::WriteLine(objPath);
  CString name = _exporter->getInitFile()->GetFilePath();
  PNMainWin::WriteLine(name);
  PNMainWin::WriteLine("%d", name.Find(objPath));
  if (name.Find(objPath) >= 0)
	name.Truncate(name.Find(objPath) - 1);
  else
	name.Truncate(0);

  PNMainWin::WriteLine(name);

  t_root.SetWindowText(name);

  name = _exporter->getInitFile()->GetFileName();
  name.Replace(".pno", ".pnm");
  t_model.SetWindowText(name);
  name.Replace(".pnm", ".pnt");
  t_materials.SetWindowText(name);
  name.Replace(".pnt", ".pns");
  t_skeleton.SetWindowText(name);
  name.Replace(".pns", ".pna");
  t_animation.SetWindowText(name);
  name.Replace(".pna", ".pnp");
  t_physics.SetWindowText(name);

  return TRUE;
}

void PNObjectWindow::OnBnClickedBbRoot()
{
  BROWSEINFO bi = {0};
  bi.lpszTitle = _T("Pick a Directory");
  bi.ulFlags = BIF_NEWDIALOGSTYLE;
  LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
  if (pidl != 0)
  {
	TCHAR direct[MAX_PATH];
	if (SHGetPathFromIDList(pidl, direct))
	  t_root.SetWindowText(direct);

	// free memory used
	IMalloc * imalloc = 0;
	if (SUCCEEDED(SHGetMalloc(&imalloc)))
	{
	  imalloc->Free(pidl);
	  imalloc->Release();
	}
  }
}

CString	PNObjectWindow::makePathFromDir(CString& root, CString& filename, LPCTSTR lpszDefExt, LPCSTR subDirectory)
{
  CString	dir = root;

  CString	name = filename;
  if (name.Trim().GetLength() == 0)
  {
	name = _exporter->getInitFile()->GetFileName();
	name.Replace(".pno", CString(".") + lpszDefExt);
  }

  CFileFind	finder;

  dir = dir + "/" + subDirectory;
  dir.Delete(dir.GetLength() - 1);
  dir.Replace('/', '\\');

  if (finder.FindFile(dir) == FALSE)
  {
	dir = _exporter->getInitFile()->GetFilePath();
	dir.Replace(_exporter->getInitFile()->GetFileName(), name);
	int l = name.GetLength();
	name = dir;
	dir.Truncate(dir.GetLength() - l - 1);
  }
  else
	name = dir + '\\' + name;

  return name;
}

CString	PNObjectWindow::makePathFromDir(CEdit& textField, LPCTSTR lpszDefExt, LPCSTR subDirectory)
{
  CString	root;
  t_root.GetWindowText(root);
  CString	filename;
  textField.GetWindowText(filename);

  return makePathFromDir(root, filename, lpszDefExt, subDirectory);
}

void  PNObjectWindow::getPath(CEdit& textField, LPCTSTR lpszDefExt, LPCTSTR lpszFilter, LPCSTR lpstrTitle, LPCSTR subDirectory)
{
  CString	dir;
  t_root.GetWindowText(dir);

  CString	name;
  textField.GetWindowText(name);
  if (name.Trim().GetLength() == 0)
  {
	name = _exporter->getInitFile()->GetFileName();
	name.Replace(".pno", CString(".") + lpszDefExt);
  }

  CFileFind	finder;

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
  }
}

BOOL  PNObjectWindow::verifSubTextfield(CEdit& textField)
{
  CString	name;
  textField.GetWindowText(name);

  int	lenght = name.GetLength();

  while (name[0] == '/' || name[0] == '\\')
	name.Delete(0);

  if (lenght == name.GetLength() && name == PNExporter::transformToUTF8(name))
	return FALSE;

  textField.SetWindowText(PNExporter::transformToUTF8(name));

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// EVENTS
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// MODELS
void  PNObjectWindow::OnBnClickedBbModel()
{
  getPath(t_model, PNM_EXT, "Model Files(*.pnm)|*.pnm||", "Save Model File", PN::DEF::modelFilePath.c_str());
}

void PNObjectWindow::OnBnClickedCModel()
{
  t_model.EnableWindow(IsDlgButtonChecked(IDC_C_MODEL));
  GetDlgItem(IDC_C_MODEL_SAVE)->EnableWindow(IsDlgButtonChecked(IDC_C_MODEL));

  bt_model.EnableWindow(IsDlgButtonChecked(IDC_C_MODEL));
  bt_option_model.EnableWindow(IsDlgButtonChecked(IDC_C_MODEL));
}

void PNObjectWindow::OnEnUpdateTModel()
{
  verifSubTextfield(t_model);
}

void PNObjectWindow::OnBnClickedBoModel()
{
  _exporter->_modelExporter.configure();
}

//////////////////////////////////////////////////////////////////////////
// MATERIALS

void PNObjectWindow::OnBnClickedBbMaterial()
{
  getPath(t_materials, PNT_EXT, "Material Files(*.pnt)|*.pnt||", "Save Material Files", PN::DEF::materialFilePath.c_str());
}

void PNObjectWindow::OnBnClickedCMaterials()
{
  t_materials.EnableWindow(IsDlgButtonChecked(IDC_C_MATERIALS));
  GetDlgItem(IDC_C_MATERIALS_SAVE)->EnableWindow(IsDlgButtonChecked(IDC_C_MATERIALS));

  bt_materials.EnableWindow(IsDlgButtonChecked(IDC_C_MATERIALS));
  bt_option_materials.EnableWindow(IsDlgButtonChecked(IDC_C_MATERIALS));
}

void PNObjectWindow::OnEnUpdateTMaterials()
{
  verifSubTextfield(t_materials);
}

void PNObjectWindow::OnBnClickedBoMaterials()
{
  _exporter->_materialsExporter.configure();
}

void PNObjectWindow::OnEnChangeTMaterials()
{
  _exporter->_materialsExporter.initFiles(
	makePathFromDir(t_materials, PNT_EXT, PN::DEF::materialFilePath.c_str()));
}

//////////////////////////////////////////////////////////////////////////
// SKELETON

void PNObjectWindow::OnBnClickedBbSkeleton()
{
  getPath(t_skeleton, PNS_EXT, "Skeleton Files(*.pns)|*.pns||", "Save Skeleton File", PN::DEF::skeletonFilePath.c_str());
}

void PNObjectWindow::OnBnClickedCSkeleton()
{
  t_skeleton.EnableWindow(IsDlgButtonChecked(IDC_C_SKELETON));
  GetDlgItem(IDC_C_SKELETON_SAVE)->EnableWindow(IsDlgButtonChecked(IDC_C_SKELETON));

  bt_skeleton.EnableWindow(IsDlgButtonChecked(IDC_C_SKELETON));
  bt_option_skeleton.EnableWindow(IsDlgButtonChecked(IDC_C_SKELETON));
}

void PNObjectWindow::OnEnUpdateTSkeleton()
{
  verifSubTextfield(t_skeleton);
}

void PNObjectWindow::OnBnClickedBoSkeleton()
{
  _exporter->_skeletonExporter.configure();
}

//////////////////////////////////////////////////////////////////////////
// ANIMATIONS

void PNObjectWindow::OnBnClickedBbAnimation()
{
  getPath(t_animation, PNA_EXT, "Animation Files(*.pna)|*.pna||", "Save Animation File", PN::DEF::animationFilePath.c_str());
}

void PNObjectWindow::OnBnClickedCAnimation()
{
  t_animation.EnableWindow(IsDlgButtonChecked(IDC_C_ANIMATION));
  GetDlgItem(IDC_C_ANIMATION_SAVE)->EnableWindow(IsDlgButtonChecked(IDC_C_ANIMATION));

  bt_animation.EnableWindow(IsDlgButtonChecked(IDC_C_ANIMATION));
  bt_option_animation.EnableWindow(IsDlgButtonChecked(IDC_C_ANIMATION));
}

void PNObjectWindow::OnEnUpdateTAnimation()
{
  verifSubTextfield(t_animation);
}

void PNObjectWindow::OnBnClickedBoAnimation()
{
  _exporter->_animationExporter.configure();
}

//////////////////////////////////////////////////////////////////////////
// PHYSICS

void PNObjectWindow::OnBnClickedBbPhysics()
{
  getPath(t_physics, PNP_EXT, "Physics Files(*.pnp)|*.pnp||", "Save Physics File", PN::DEF::physicsFilePath.c_str());
}

void PNObjectWindow::OnBnClickedCPhysics()
{
  t_physics.EnableWindow(IsDlgButtonChecked(IDC_C_PHYSICS));
  GetDlgItem(IDC_C_PHYSICS_SAVE)->EnableWindow(IsDlgButtonChecked(IDC_C_PHYSICS));

  bt_physics.EnableWindow(IsDlgButtonChecked(IDC_C_PHYSICS));
  bt_option_physics.EnableWindow(IsDlgButtonChecked(IDC_C_PHYSICS));
}

void PNObjectWindow::OnBnClickedBoPhysics()
{
  _exporter->_physicalExporter.configure();
}

void PNObjectWindow::OnBnClickedRbPhysModel()
{
  bt_physics.EnableWindow(FALSE);
}

void PNObjectWindow::OnBnClickedRbPhysOptions()
{
  bt_physics.EnableWindow(TRUE);
}

//////////////////////////////////////////////////////////////////////////

void PNObjectWindow::OnBnClickedBoGeneral()
{
  PNOConfig	config(_exporter, this);

  config.DoModal();
}

void PNObjectWindow::OnBnClickedOk()
{
  t_root.GetWindowText(_exporter->_rootPath);

  _exporter->_hasModel = IsDlgButtonChecked(IDC_C_MODEL) == TRUE;
  _exporter->_saveModel = IsDlgButtonChecked(IDC_C_MODEL_SAVE) == TRUE;
  t_model.GetWindowText(_exporter->_modelPath);

  _exporter->_hasMaterials = IsDlgButtonChecked(IDC_C_MATERIALS) == TRUE;
  _exporter->_saveMaterials = IsDlgButtonChecked(IDC_C_MATERIALS_SAVE) == TRUE;
  t_materials.GetWindowText(_exporter->_materialsPath);

  _exporter->_hasSkeleton = IsDlgButtonChecked(IDC_C_SKELETON) == TRUE;
  _exporter->_saveSkeleton = IsDlgButtonChecked(IDC_C_SKELETON_SAVE) == TRUE;
  t_skeleton.GetWindowText(_exporter->_skeletonPath);

  _exporter->_hasAnimation = IsDlgButtonChecked(IDC_C_ANIMATION) == TRUE;
  _exporter->_saveAnimation = IsDlgButtonChecked(IDC_C_ANIMATION_SAVE) == TRUE;
  t_animation.GetWindowText(_exporter->_animationPath);

  _exporter->_hasPhysics = IsDlgButtonChecked(IDC_C_PHYSICS) == TRUE;
  _exporter->_savePhysics = IsDlgButtonChecked(IDC_C_PHYSICS_SAVE) == TRUE;
  t_physics.GetWindowText(_exporter->_physicalPath);
  _exporter->_physicsModel = IsDlgButtonChecked(IDC_RB_PHYS_MODEL) == TRUE;

  OnOK();
}

//////////////////////////////////////////////////////////////////////////
};
