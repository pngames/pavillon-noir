/*
 * PNWaypointObject.cpp
 * 
 * Description :
 * PNWaypointObject definition
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

#include <iostream>

///////////////////////////////

#include "pneditorcommon.hpp"

///////////////////////////////

#include "PNWaypointObject.hpp"
#include "PNConfigurableParameter.hpp"

///////////////////////////////

using namespace std;

///////////////////////////////

namespace PN { namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

/*! \brief Default PNWaypointObject constructor.
*  Constructs a new PNWaypointObject.
*  \param	label	  User friendly naming style to distinguish waypoints (!=id).
*/
PNWaypointObject::PNWaypointObject(std::string label)
{
  _label = label;
}

/*! \brief Default PNWaypointObject destructor.
*/
PNWaypointObject::~PNWaypointObject()
{
  for (ParametersVector::iterator it = _params.begin(); it != _params.end(); ++it)
	delete *it;
}

//////////////////////////////////////////////////////////////////////////

// FIXME : doc
/*! \brief
*  \param	p		PNConfigurableParameter.
*/
void      PNWaypointObject::update(PNConfigurableParameter* p)
{ 
  switch (p->getType())
  {
  case PN_PARAMTYPE_INT:
	std::cout << "update:" << p->getLabel() << "=" << *((int*)p->getElem()) << std::endl;
  case PN_PARAMTYPE_STRING:
	std::cout << "update:" << p->getLabel() << "=" << *((string*)p->getElem()) << std::endl;
  default:
	;
  }
  return;
}

/*! \brief  Adds a parameter.
*  \param	type	  Type of the new parameter.
*  \param	elem	  Data of the new parameter.
*  \param	label	  Label to display in the grid.
*  \param	altText	  Alttext/tooltip for this parameter.
*/
void      PNWaypointObject::addParameter(pnparamtype type, void* elem, const std::string& label, const std::string& altText)
{
  _params.push_back(new PNConfigurableParameter(this, type, elem, label, altText));
}

/*! \brief  Returns the number of parameters for this object.
*/
int PNWaypointObject::getNbParameters() 
{ 
  return _params.size();
}

/*! \brief  Returns the paramter at index idx.
*  \param	idx		  Index of paramter to return.
*/
PNConfigurableParameter* PNWaypointObject::getParameter(int idx) 
{
  return _params[idx]; 
}

////////////////////////////////////////////////////////////////////////// 
};};
