/*
 * PNInterface.hpp
 * 
 * Description :
 * PNInterface declaration
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

#ifndef _PNINTERFACE_HPP_
# define _PNINTERFACE_HPP_

#include <vector>

#include "PNObject.hpp"
#include "PNConfigurableObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNConfigurableParameter;

typedef enum
{
  PN_PLUGIN_DEFAULT,
  PN_PLUGIN_IMPORTER,
  PN_PLUGIN_EXPORTER,
  PN_PLUGIN_RENDERER,
  PN_PLUGIN_PHYSICS,
  PN_PLUGIN_SOUND,
  PN_PLUGIN_GAME,
  PN_PLUGIN_NB_TYPES
} plugintypes;

class PNAPI							PNInterface : public PNObject, public PNConfigurableObject
{
protected:
  PNInterface();
public:
  virtual ~PNInterface();

  virtual void						init()=0;

  virtual plugintypes				getType();

  //////////////////////////////////////////////////////////////////////////
  // PNConfigurableObject

  virtual void						update(PNConfigurableParameter* p);

  pnint								getNbParameters();
  PNConfigurableParameter*			getParameter(pnint idx);

  const std::string&				getLabel();
  const std::string&				getName();

protected:
  void								addParam(PNConfigurableParameter* p);
  void								addSeparator(const std::string& sepLabel);

  std::string						_label;
  std::string						_name;

private:
  typedef std::vector<PNConfigurableParameter*>	VECTOR_PARAMETERS;

  VECTOR_PARAMETERS					_vectorParameters;
};

//////////////////////////////////////////////////////////////////////////
}

#endif  /*_PNINTERFACE_HPP_*/
