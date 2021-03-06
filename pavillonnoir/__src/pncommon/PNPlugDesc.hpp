/*
 * PNPlugDesc.hpp
 * 
 * Description :
 * PNPlugDesc declaration
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

#ifndef _PNPLUGDESC_HPP_
# define _PNPLUGDESC_HPP_

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNInterface;

// descrition du plugin
class PNAPI PNPlugDesc
{
public:
  // renvoie l'interface de communication du plugin
  virtual PNInterface*	getInterface(pnuint id)=0;
  virtual pnuint		getNbInterface()=0;

  //////////////////////////////////////////////////////////////////////////
  
  // nom du plugin
  virtual const pnchar*	getName()=0;

  // version du plugin
  virtual pnuint		getVersion()=0;

  //////////////////////////////////////////////////////////////////////////
  
  virtual ~PNPlugDesc() {}
};

//////////////////////////////////////////////////////////////////////////
};

#endif  /*_PNINTERFACE_HPP_*/

