/*
 * stdafx.h
 *
 * Description :
 * All system include and rarelly modified
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

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclure les en-t�es Windows rarement utilis�
#endif

// Modifiez les d�initions suivantes si vous devez cibler une plate-forme avant celles sp�ifi�s ci-dessous.
// Reportez-vous �MSDN pour obtenir les derni�es informations sur les valeurs correspondantes pour les diff�entes plates-formes.
#ifndef WINVER				// Autorise l'utilisation des fonctionnalit� sp�ifiques �Windows95 et Windows NT4 ou version ult�ieure.
#define WINVER 0x0400		// Attribuez la valeur appropri� �cet ��ent pour cibler Windows98 et Windows2000 ou version ult�ieure.
#endif

#ifndef _WIN32_WINNT		// Autorise l'utilisation des fonctionnalit� sp�ifiques �Windows NT4 ou version ult�ieure.
#define _WIN32_WINNT 0x0400		// Attribuez la valeur appropri� �cet ��ent pour cibler Windows98 et Windows2000 ou version ult�ieure.
#endif						

#ifndef _WIN32_WINDOWS		// Autorise l'utilisation des fonctionnalit� sp�ifiques �Windows98 ou version ult�ieure.
#define _WIN32_WINDOWS 0x0410 // Attribuez la valeur appropri� �cet ��ent pour cibler WindowsMe ou version ult�ieure.
#endif

#ifndef _WIN32_IE			// Autorise l'utilisation des fonctionnalit� sp�ifiques �IE4.0 ou version ult�ieure.
#define _WIN32_IE 0x0400	// Attribuez la valeur appropri� �cet ��ent pour cibler IE5.0 ou version ult�ieure.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// certains constructeurs CString seront explicites

// d�active le masquage MFC de certains messages d'avertissement courants et par ailleurs souvent ignor�
#define _AFX_ALL_WARNINGS

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

#include <afxwin.h>         // composants MFC principaux et standard
#include <afxext.h>         // extensions MFC

#include <Shlwapi.h>

#include "Max.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "decomp.h"

#include "IGame/IGame.h"
#include "IGame/IGameObject.h"
#include "IGame/IGameProperty.h"
#include "IGame/IGameControl.h"
#include "IGame/IGameModifier.h"
#include "IGame/IConversionManager.h"
#include "IGame/IGameError.h"

/*#include "simpmod.h"
#include "simpobj.h"
#include "hsv.h"
#include <direct.h>
#include <commdlg.h>
#include <guplib.h>
#include "frontend.h"
#include "tvnode.h"
#include "bmmlib.h"
#include "fltlib.h"
#include "ViewFile.h"
#include "meshadj.h"
#include "XTCObject.h"
#include "samplers.h"
#include "texutil.h"
#include "shaders.h"
#include "macrorec.h"
#include "gport.h"
#include "shadgen.h"
#include "stdmat.h"
#include "imtl.h"
#include "macrorec.h"
#include "tvutil.h"
#include "utilapi.h"
#include "IKSolver.h"
#include "ISkin.h"
#include "ISkinCodes.h"
#include "icurvctl.h"
#include "Manipulator.h"
#include "gizmo.h"
#include "gizmoimp.h"
#include "XTCObject.h"*/

#include "pndefs.h"
#include "pnmath.h"
#include "pnresources.h"

#include "resource.h"

#include <afxdtctl.h>		// Prise en charge des MFC pour les contr�es communs Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Prise en charge des MFC pour les contr�es communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

