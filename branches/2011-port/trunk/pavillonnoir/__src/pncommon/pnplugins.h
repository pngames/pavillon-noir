/*
 * pnplugins.h
 * 
 * Description :
 * Meta-include for plugins management
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 * This software has been written in EPITECH <http://www.epitech.net>
 * EPITECH is computer science school in Paris - FRANCE -
 * under the direction of flav <http://www.epita.fr/~flav>.
 * and Jerome Landrieu.
 *
 * This file is part of Pavillon Noir.
 *
 * Pavillon Noir is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Pavillon Noir is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Pavillon Noir; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef _PNPLUGINS_H_
# define _PNPLUGINS_H_

#include "PNInterface.hpp"
#include "PNPlugDesc.hpp"

#define PNDLFCTDECLARE	PNPLUGEXPORT void*	pnDlMain()
#define PNDLFCTNAMESTR	"pnDlMain"

#include "PNPlugin.hpp"
#include "PNPluginManager.hpp"

#include <string>

namespace PN {
//////////////////////////////////////////////////////////////////////////
  namespace DEF
  {
    static const std::string defaultWin32RPluginFilePath = "win32/plugins/";
    static const std::string defaultWin32DPluginFilePath = defaultWin32RPluginFilePath + "Debug/";
    static const std::string defaultLinuxRPluginFilePath = "linux/plugins/";    
    static const std::string defaultLinuxDPluginFilePath = defaultLinuxRPluginFilePath + "Debug/";
    
#ifdef WIN32
# ifdef DEBUG
#   define defaultPluginFilePath defaultWin32DPluginFilePath
# else
#   define defaultPluginFilePath defaultWin32RPluginFilePath
# endif
#else
# ifdef DEBUG
#   define defaultPluginFilePath defaultLinuxDPluginFilePath
# else
#   define defaultPluginFilePath defaultLinuxRPluginFilePath
# endif
#endif
  }
//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNPLUGINS_H_*/
