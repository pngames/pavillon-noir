/*
 * PNMainWin.cpp
 * 
 * Description :
 * PNMainWin definition
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

#include <stdarg.h>

#include "pnmaxplugin.h"
#include "PNMainWin.hpp"
#include "PNSaveThread.hpp"
#include "PNExporter.hpp"

#include "pnmaxplugin.h"

using namespace PN;

// Bo�e de dialogue PNMainWin
PNMainWin*	PNMainWin::_instance = NULL;
CListBox	PNMainWin::_console;

IMPLEMENT_DYNAMIC(PNMainWin, CDialog)
PNMainWin::PNMainWin(const TCHAR *name, Interface *maxInterface, CWnd* pParent /*=NULL*/)
	: CDialog(PNMainWin::IDD, pParent), _name(name), _maxInterface(maxInterface)
{
   _instance = this;
}

PNMainWin::~PNMainWin()
{
}

void PNMainWin::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_CONSOLE, _console);
  DDX_Control(pDX, IDOK, _btOK);
}


BEGIN_MESSAGE_MAP(PNMainWin, CDialog)
  ON_WM_CREATE()

  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
  ON_BN_CLICKED(ID_MWIN_CONFIG, OnBnClickedMwinConfig)
END_MESSAGE_MAP()

void	PNMainWin::WriteLine(const pnchar* format, ...)
{
  va_list	args;
  pnchar	buffer[1024];

  va_start(args, format);
  _vsnprintf(buffer, 1023, format, args);
  va_end(args);

  _console.AddString(buffer);
}

void	PNMainWin::WriteLine(const CString& str)
{
  _console.AddString(str);
}


// Gestionnaires de messages PNMainWin

BOOL PNMainWin::OnInitDialog()
{
  if (CDialog::OnInitDialog() == FALSE)
	return FALSE;

  try
  {
	_exporter->initExport();
	_exporter->initFiles(_name);
  }
  catch (exception ex)
  {
	WriteLine("ERROR initExport: %s", ex.what());
  }

  WriteLine("");
  WriteLine("Fichiers :  %s", _name);
  WriteLine("");
  WriteLine("Appuyez sur le bouton OK pour continuer");

  return TRUE;
}

void PNMainWin::OnBnClickedOk()
{
  _btOK.EnableWindow(FALSE);

  //_expThread = (PNSaveThread*)AfxBeginThread(RUNTIME_CLASS(PNSaveThread));

  try
  {
	_exporter->export(_name);
  }
  catch (exception ex)
  {
	WriteLine("ERROR export: %s", ex.what());
  }

  //likider tout le bordel

  //OnOK();
}

void PNMainWin::OnBnClickedCancel()
{
  /*if (_expThread != NULL)
  {
	_expThread->SuspendThread();
	//_expThread->PostQuitMessage(0);
    //_expThread->ExitInstance();
  }*/

  //likider tout le bordel

  OnCancel();
}

void PNMainWin::OnBnClickedMwinConfig()
{
  _exporter->configure();
}
