/*
 * PNConfigurableParameter.cpp
 * 
 * Description :
 * PNConfigurableParameter definition
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

#include "PNConfigurableParameter.hpp"

using namespace std;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNConfigurableParameter::PNConfigurableParameter(PNConfigurableObject* p, 
												 pnparamtype type, 
                                                 void* elem, 
                                                 const string& label, 
                                                 const string& altText,
												 bool editable)
{	
  _p = p;
  _elem = elem;
  _label = label;
  _altText = altText;
  _type = type;
  _editable = editable;
}

PNConfigurableParameter::~PNConfigurableParameter()
{
}

//////////////////////////////////////////////////////////////////////////

pnparamtype   PNConfigurableParameter::getType()
{
  return _type;
}

void*         PNConfigurableParameter::getElem()
{
  return _elem;
}

const string&      PNConfigurableParameter::getLabel()
{
  return _label;
}

const string&		PNConfigurableParameter::getAltText()
{
  return _altText;
}

bool				PNConfigurableParameter::isEditable()
{
  return _editable;
}

PNConfigurableObject*	PNConfigurableParameter::getConfigurableObject()
{
  return _p;
}


//////////////////////////////////////////////////////////////////////////

void          PNConfigurableParameter::dump()
{
/*  std::cout << "_type=" << _type << std::endl;
  if (_elem != NULL) 
    std::cout << _elem << std::endl;
  else
    std::cout << "_elem=NULL" << std::endl;
  std::cout << "_label=" << getLabel() << std::endl;
  std::cout << "_altText=" << getAltText() << std::endl;*/
}

//////////////////////////////////////////////////////////////////////////
};