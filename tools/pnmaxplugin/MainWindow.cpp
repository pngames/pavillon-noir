/*
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

// MainWindow.cpp : fichier d'impl�entation
//

#include "stdafx.h"
#include "pnmaxplugin.h"
#include "MainWindow.hpp"

// Bo�e de dialogue MainWindow

IMPLEMENT_DYNAMIC(MainWindow, CDialog)
MainWindow::MainWindow(CWnd* pParent /*=NULL*/)
	: CDialog(MainWindow::IDD, pParent)
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainWindow, CDialog)
END_MESSAGE_MAP()


// Gestionnaires de messages MainWindow
