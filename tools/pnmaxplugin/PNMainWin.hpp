/*
 * PNMainWin.hpp
 * 
 * Description :
 * PNMainWin declaration
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

#include "pndefs.h"

class PNSaveThread;
class PNExporter;

#define DEBUG_TODO(msg)		PNMainWin::WriteLine("TODO : %s", msg)
#define DEBUG_WARNING(msg)	PNMainWin::WriteLine("WARNING : %s", msg)

// Bo�e de dialogue PNMainWin

class PNMainWin : public CDialog
{
	DECLARE_DYNAMIC(PNMainWin)

	static PNMainWin* _instance;

	const TCHAR*	  _name;
	Interface*		  _maxInterface;
public:
  PNExporter*		  _exporter;
public:
  static PNMainWin* getInstance()
  {
	return _instance;
  }

  PNMainWin(const TCHAR *name, Interface *maxInterface, CWnd* pParent = NULL);   // constructeur standard
public:
	virtual ~PNMainWin();

// Donn�s de bo�e de dialogue
	enum { IDD = IDD_PN_MWIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
  static void	WriteLine(const char* str, ...);
  static void	WriteLine(const CString& str);
public:
  virtual BOOL OnInitDialog();

  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();
  static CListBox _console;
  CButton _btOK;
  afx_msg void OnBnClickedMwinConfig();
};
