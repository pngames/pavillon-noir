/*
 * PNPropertiesGridParameter.cpp
 * 
 * Description :
 * PNPropertiesGridParameter definition
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

#include "pndefs.h"

#include "PNConfigurableObject.hpp"
#include "PNConfigurableParameter.hpp"

#include "PNPropertiesGridParameter.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNPropertiesGridParameter::PNPropertiesGridParameter(PNConfigurableParameter* param)
: _param(param)
{
  
}

PNPropertiesGridParameter::~PNPropertiesGridParameter() 
{
  
}

//////////////////////////////////////////////////////////////////////////

PNConfigurableParameter*
PNPropertiesGridParameter::getParam()
{
  return _param;
}

void
PNPropertiesGridParameter::sendParamModif()
{
  if (_param->getConfigurableObject())
  {
	_param->getConfigurableObject()->update(_param);
	_param->setModified();
  }
}

//////////////////////////////////////////////////////////////////////////

std::string
PNPropertiesGridParameter::toString()
{
  return _param->toString();
}

void
PNPropertiesGridParameter::fromString(const std::string& str)
{
  _param->fromString(str);
}

//////////////////////////////////////////////////////////////////////////
};

