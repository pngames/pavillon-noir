/*
 * PNSkeletonWin.cpp
 * 
 * Description :
 * PNSkeletonWin definition
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
#include "PNSkeletonWin.hpp"
#include "PNSBone.hpp"
#include "PNMainWin.hpp"
#include "PNSkeletonExporter.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

#define UNCHECK 1
#define CHECK 2

// Boite de dialogue PNSkeletonWin

IMPLEMENT_DYNAMIC(PNSkeletonWin, CDialog)
PNSkeletonWin::PNSkeletonWin(PNSkeletonExporter *skeleton, UINT nIDTemplate /*= IDD*/, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent), _topLevelBone(skeleton->_topLevelBone)
{
}

PNSkeletonWin::~PNSkeletonWin()
{
}

void 
PNSkeletonWin::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TREE_SQUELETOR, _treeSkeletor);
}

BEGIN_MESSAGE_MAP(PNSkeletonWin, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_NOTIFY(NM_CLICK, IDC_TREE_SQUELETOR, OnNMClickTreeSqueletor)
END_MESSAGE_MAP()

void  PNSkeletonWin::_parseBone(HTREEITEM parent, PNSBone* bone)
{
  TVINSERTSTRUCT tvInsert;
  tvInsert.hParent = parent;
  tvInsert.hInsertAfter = TVI_LAST;
  tvInsert.item.state = TVIS_EXPANDED | INDEXTOSTATEIMAGEMASK(bone->isExported() ? CHECK : UNCHECK);
  tvInsert.item.stateMask = TVIS_EXPANDED | TVIS_STATEIMAGEMASK;
  tvInsert.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_STATE;
  IGameNode*		node = bone->getNode();
  tvInsert.item.pszText = _T(node != NULL ? node->GetName() : "");
  tvInsert.item.lParam = (LPARAM)bone;

  HTREEITEM hBone = _treeSkeletor.InsertItem(&tvInsert);

  for (PNSBone::iterator it = bone->begin(); it != bone->end(); ++it)
	_parseBone(hBone, *it);
}

BOOL  PNSkeletonWin::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  _treeSkeletor.ModifyStyle(TVS_CHECKBOXES, 0);
  _treeSkeletor.ModifyStyle(0, TVS_CHECKBOXES);

  _parseBone(NULL, _topLevelBone);

  return TRUE;
}

// Gestionnaires de messages PNSkeletonWin

void  PNSkeletonWin::_updateBone(HTREEITEM hItem)
{
  PNMainWin::WriteLine("**********************************");

  PNSBone* bone = (PNSBone*)_treeSkeletor.GetItemData(hItem);

  bone->setExported(_treeSkeletor.GetCheck(hItem) == TRUE);
  PNMainWin::WriteLine("   : %i", bone->isExported());

  if (!_treeSkeletor.ItemHasChildren(hItem))
	return ;

  for (hItem = _treeSkeletor.GetChildItem(hItem); hItem != 0; hItem = _treeSkeletor.GetNextSiblingItem(hItem))
  {
	if (!bone->isExported())
	{
	  _treeSkeletor.SetCheck(hItem, FALSE);
	}

	_updateBone(hItem);
  }
}

void PNSkeletonWin::OnBnClickedOk()
{
  _updateBone(_treeSkeletor.GetRootItem());

  OnOK();
}

void PNSkeletonWin::OnNMClickTreeSqueletor(NMHDR *pNMHDR, LRESULT *pResult)
{
  _updateBone(_treeSkeletor.GetRootItem());
}

//////////////////////////////////////////////////////////////////////////
};
