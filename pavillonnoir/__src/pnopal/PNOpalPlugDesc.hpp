/*
 * PNOpalPlugDesc.hpp
 * 
 * Description :
 * PNOpalPlugDesc
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

#ifndef _PNOPALPLUGDESC_HPP_
# define _PNOPALPLUGDESC_HPP_

#include "PNOpal.hpp"
#include "PNPlugDesc.hpp"

#include "PNOpalImporter.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNOpal;

class PNOpalPlugDesc : public PNPlugDesc
{
protected:
  PNOpal*			_physicsInterface;
  PNOpalImporter*	_importerInterface; 

public:
  PNInterface*	getInterface(pnuint id);
  pnuint		getNbInterface();

  //////////////////////////////////////////////////////////////////////////

  // nom du plugin
  const pnchar*	getName() {return "Open Physics Abstraction Layer module";};

  // version du plugin
  pnuint		getVersion() {return 1;};

  //////////////////////////////////////////////////////////////////////////
public:
  PNOpalPlugDesc();
  ~PNOpalPlugDesc();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNOPALPLUGDESC_HPP_*/
