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

#ifndef _PNCONFIGURABLEOBJECT_HPP_
# define _PNCONFIGURABLEOBJECT_HPP_

#include <string>

#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNConfigurableParameter;

class PNAPI							PNConfigurableObject : public IPNXMLSerializable
{
public:
  virtual ~PNConfigurableObject();

  virtual void						update(PNConfigurableParameter* p) = 0;

  virtual const std::string&		getName()=0;
  virtual const std::string&		getLabel();

  virtual pnbool					modified();
  virtual void						setModified();
  virtual void						setUnmodified();

  //////////////////////////////////////////////////////////////////////////

public:
  virtual pnint						getNbParameters() = 0;
  virtual PNConfigurableParameter*	getParameter(pnint idx) = 0;

  //////////////////////////////////////////////////////////////////////////

public:
  virtual const std::string&		getDTD() const;
  virtual const std::string&		getDTDName() const;
  virtual const std::string&		getRootNodeName() const;

protected:
  virtual pnint						_unserializeNode(xmlNode* node);
  virtual pnint						_serializeContent(xmlNode* node);

public:
  virtual pnint						unserializeFromXML(xmlNode* node);
  virtual pnint						serializeInXML(xmlNode* node, pnbool isroot = false);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNCONFIGURABLEOBJECT_HPP_*/
