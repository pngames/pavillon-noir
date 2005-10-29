/*
 * PNPlugin.hpp
 * 
 * Description :
 * PNPlugin declaration
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

#ifndef _PNPLUGIN_HPP_
# define _PNPLUGIN_HPP_

#ifdef WIN32
# include <Windows.h>
#endif

#include <string>
#include <boost/filesystem/path.hpp>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
typedef HINSTANCE		pndltype;
#else
typedef void			*pndltype;
#endif

typedef void			*(*pndlfct)();

class PNPlugDesc;

// gestion d'un plugin
class PNAPI					PNPlugin : public PNObject
{
  pndltype					_dlHandle;
  pndlfct					_dlFct;
  
  ///point d'entre du plugin  contenant les information le concernant
  PNPlugDesc*	  			_plugDesc;
  ///fichier representant le plugin
  boost::filesystem::path	_file;

public:
  PNPlugin(const boost::filesystem::path& file);
  ~PNPlugin();

public:
  /// renvoie l'interface de communication du plugin
  PNPlugDesc*				getPlugDesc() const;

  //////////////////////////////////////////////////////////////////////////

  /// recharge le plugin
  pnbool					reload();
  /// decharge le plugin
  pnbool					unload();

  //////////////////////////////////////////////////////////////////////////

  pnbool					isValid() const;
  const boost::filesystem::path&	getPath() const;
};

//////////////////////////////////////////////////////////////////////////
};

#endif  /*_PNPLUGIN_HPP_*/
