/*
* PNScriptConfigurableObject.hpp
* 
* Description :
* PNScriptConfigurableObject declaration
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

#ifndef _PNSCRIPTCONFIGURABLEOBJECT_HPP_
# define _PNSCRIPTCONFIGURABLEOBJECT_HPP_

#include <string>

#include "pnproperties.h"
#include "pneditorcommon.h"

#include "PNConfigurableObject.hpp"

#include "IPNXMLSerializable.hpp"

namespace PN {
  //////////////////////////////////////////////////////////////////////////

namespace EDITOR {
  //////////////////////////////////////////////////////////////////////////

  class	 			PNScriptConfigurableObject : public PNConfigurableObject
  {
  private:
	std::string					_type;
	std::string					_initScriptPath;
	std::string					_actionScriptPath;
	std::string					_initCode;
	std::string					_actionCode;

	pnbool						_modified;

  protected:
	typedef std::vector<PNConfigurableParameter*> ParametersVector;
	ParametersVector			_params;


  public:
	PNScriptConfigurableObject();
	~PNScriptConfigurableObject();

  public:
	void						update(PNConfigurableParameter* p);
	virtual const std::string&	getLabel();
	pnint						getNbParameters();
	PNConfigurableParameter*	getParameter(pnint idx);

	pnbool						modified();
	void						setModified();
	void						setUnmodified();

	//////////////////////////////////////////////////////////////////////////

  public:
	pnint						unserializeFromXML(xmlNode* node);
	pnint						serializeInXML(xmlNode* node, pnbool root = false);
	pnint						_serializeContent(xmlNode* root);

	//////////////////////////////////////////////////////////////////////////

	std::string&				getType();
	std::string&				getInitScriptPath();
	std::string&				getActionScriptPath();
	std::string&				getInitCode();
	std::string&				getActionCode();
  };

  //////////////////////////////////////////////////////////////////////////
};

  //////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNSCRIPTCONFIGURABLEOBJECT_HPP_*/
