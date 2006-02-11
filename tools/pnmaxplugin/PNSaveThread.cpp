/*
 * PNSaveThread.cpp
 * 
 * Description :
 * PNSaveThread definition
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
#include "PNSaveThread.hpp"
#include "PNMainWin.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(PNSaveThread, CWinThread)

PNSaveThread::PNSaveThread()
{
}

PNSaveThread::~PNSaveThread()
{
}

BOOL PNSaveThread::InitInstance()
{
	// TODO:  effectuez ici une initialisation par thread
	return TRUE;
}

int PNSaveThread::ExitInstance()
{
	// TODO:  effectuez ici un nettoyage par thread
	return CWinThread::ExitInstance();
}

int	PNSaveThread::Run()
{
  PNMainWin::WriteLine("Demarage du thread");
  //lancer le chargement

  return TRUE;
}

BEGIN_MESSAGE_MAP(PNSaveThread, CWinThread)
END_MESSAGE_MAP()


// Gestionnaires de messages PNSaveThread

//////////////////////////////////////////////////////////////////////////
};
