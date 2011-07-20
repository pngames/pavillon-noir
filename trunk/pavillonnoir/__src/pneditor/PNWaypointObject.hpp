/*
 * PNWaypointObject.hpp
 * 
 * Description :
 * PNWaypointObject declaration
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


///////////////////////////////

#ifndef _PNWAYPOINTOBJECT_HPP_
# define _PNWAYPOINTOBJECT_HPP_

///////////////////////////////

#include <vector>
#include <string>

#include "PNConfigurableParameter.hpp"
#include "PNConfigurableObject.hpp"

///////////////////////////////

namespace PN { namespace EDITOR {
//////////////////////////////////////////////////////////////////////////
  
class						PNWaypointObject : public PNConfigurableObject
{
  typedef std::vector<PNConfigurableParameter*> ParametersVector;
  ParametersVector			_params;
private:
  std::string				_label;

public:
  PNWaypointObject(std::string label);
  ~PNWaypointObject();

  void						update(PNConfigurableParameter* p);
  void						addParameter(pnparamtype type, void* elem, const std::string& label, const std::string& altText);

  int						getNbParameters();
  PNConfigurableParameter*	getParameter(int idx);

  // for tests only
  void						setLabel(std::string label) { _label = label; };
  const std::string&		getLabel() { return _label; };
};

//////////////////////////////////////////////////////////////////////////
};};

#endif /* _PNWAYPOINTOBJECT_HPP_ */
