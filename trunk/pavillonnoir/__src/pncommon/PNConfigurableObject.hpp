/*
 * PNConfigurableObject.hpp
 * 
 * Description :
 * PNConfigurableObject declaration
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

#ifndef _PN_CONFIGURABLE_OBJECT_HPP_
# define _PN_CONFIGURABLE_OBJECT_HPP_

#include <string>

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNConfigurableParameter;

class PNConfigurableObject
{
public:
  virtual ~PNConfigurableObject() {};

  virtual void						update(PNConfigurableParameter* p) = 0;

  virtual int						getNbParameters() = 0;
  virtual PNConfigurableParameter*	getParameter(int idx) = 0;

  virtual const std::string&		getLabel() = 0;

  virtual bool						modified() { return FALSE; }
  virtual void						setModified() { }
  virtual void						setUnmodified() { }

  void						addParam(PNConfigurableParameter* p);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PN_CONFIGURABLE_OBJECT_HPP_*/
