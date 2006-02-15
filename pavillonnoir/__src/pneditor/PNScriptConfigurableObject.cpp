/*
* PNScriptConfigurableObject.cpp
* 
* Description :
* PNScriptConfigurableObject definition
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

#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnxml.h"
#include "pnresources.h"

#include "PNScriptConfigurableObject.hpp"

using namespace PN;
using namespace EDITOR;

namespace PN
{
  //////////////////////////////////////////////////////////////////////////

namespace EDITOR {
  //////////////////////////////////////////////////////////////////////////

  PNScriptConfigurableObject::PNScriptConfigurableObject()
  {
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_FILE, &_initScriptPath, "Init script", "Init script"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_FILE, &_actionScriptPath, "Action script", "Action script"));
	// TODO : remplacer STRING par TEXT
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_STRING, &_initCode, "Init code", "Init code"));
	_params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_STRING, &_actionCode, "Action code", "Action code"));
  }

  PNScriptConfigurableObject::~PNScriptConfigurableObject()
  {
	for (ParametersVector::iterator it = _params.begin(); it != _params.end(); ++it)
	  delete *it;
  }

  //////////////////////////////////////////////////////////////////////////

  void
	PNScriptConfigurableObject::update(PNConfigurableParameter* p)
  {
	return;
  }

  pnint
	PNScriptConfigurableObject::getNbParameters()
  {
	return (pnint)_params.size();
  }

  PNConfigurableParameter*
	PNScriptConfigurableObject::getParameter(pnint idx)
  {
	return _params[idx];
  }


  const std::string&
	PNScriptConfigurableObject::getLabel()
  {
	return _type;
  }
  

  pnbool
	PNScriptConfigurableObject::modified() 
  { 
	return _modified; 
  }
  
  void
	PNScriptConfigurableObject::setModified() 
  { 
	_modified = true; 
  }

  void
	PNScriptConfigurableObject::setUnmodified() 
  { 
	_modified = false; 
  }

  //////////////////////////////////////////////////////////////////////////

  // TODO : load src files when PNXML_SRC_ATTR is present
  pnint
	PNScriptConfigurableObject::unserializeFromXML(xmlNode* node)
  {
	xmlNode* root = node;

	_type = (pnchar *)xmlGetProp(root, PNXML_TYPE_ATTR); // NULL if PNXML_TYPE_ATTR doesn't exist

	xmlChar* attr = NULL;

	for (xmlNodePtr node = root->children; node != NULL; node = node->next)
	{
	  if (xmlStrEqual(node->name, PNXML_ACTIONCODE_MKP))
	  {
		if ((attr = xmlGetProp(node, PNXML_SRC_ATTR)) != NULL)
		{ // load src file (READ)
		  _actionScriptPath = (pnchar*)attr;
		  ;
		}
		else
		{ // node contents the code
		  _actionCode = (char*)node->content;
		}
	  }
	  else if (xmlStrEqual(node->name, PNXML_INITCODE_MKP))
	  {
		if ((attr = xmlGetProp(node, PNXML_SRC_ATTR)) != NULL)
		{ // load src file (READ)
		  _initScriptPath = (pnchar*)attr;
		  ;
		}
		else
		{ // node contents the code
		  _initCode = (char*)node->content;
		}
	  }
	}
	return PNEC_SUCCESS;
  }
  
  pnint
	PNScriptConfigurableObject::serializeInXML(xmlNode* node, pnbool isroot)
  {
	xmlNode* root = node;

	if (_initCode != "" || _actionCode != "" || _initScriptPath != "" || _actionScriptPath != "") 
	{
	  if (isroot == false)
		root = xmlNewChild(node, NULL, BAD_CAST PNXML_SCRIPT_MKP, NULL);

	  _serializeContent(root);
	}

	return PNEC_SUCCESS;
  }

  pnint
	PNScriptConfigurableObject::_serializeContent(xmlNode* root)
  {
	//xmlNewProp(root, PNXML_TYPE_ATTR, _type);
	xmlNewProp(root, PNXML_TYPE_ATTR, BAD_CAST _type.c_str());

	//////////////////////////////////////////////////////////////////////////

	xmlNode* node = NULL;

	node = xmlNewChild(root, NULL, BAD_CAST PNXML_INITCODE_MKP, NULL);
	//XMLUtils::xmlNewProp(node, PNXML_SRC_ATTR, (pnchar*)_initScriptPath.c_str() /*DEF::convertPath(DEF::gamedefFilePath, _initScriptPath).c_str()*/); // check de la valeur de _initScriptPath
    XMLUtils::xmlNewProp(node, PNXML_SRC_ATTR, DEF::convertPath(DEF::gamedefFilePath, _initScriptPath).c_str()); // check de la valeur de _initScriptPath
	if (_initCode != "")
	  node->content = BAD_CAST _initCode.c_str();

	node = xmlNewChild(root, NULL, BAD_CAST PNXML_ACTIONCODE_MKP, NULL);
	XMLUtils::xmlNewProp(node, PNXML_SRC_ATTR, (pnchar*)_actionScriptPath.c_str() /*DEF::convertPath(DEF::gamedefFilePath, _actionScriptPath).c_str()*/); // check de la valeur de _actionScriptPath
	if (_actionCode != "")
	  node->content = BAD_CAST _actionCode.c_str();

	return PNEC_SUCCESS;
  }

  //////////////////////////////////////////////////////////////////////////

  std::string&
	PNScriptConfigurableObject::getType()
  {
	return _type;
  }

  std::string&
	PNScriptConfigurableObject::getInitScriptPath()
  {
	return _initScriptPath;
  }

  std::string&
	PNScriptConfigurableObject::getActionScriptPath()
  {
	return _actionScriptPath;
  }

  std::string&
	PNScriptConfigurableObject::getInitCode()
  {
	return _initCode;
  }

  std::string&
	PNScriptConfigurableObject::getActionCode()
  {
	return _actionCode;
  }
  
  //////////////////////////////////////////////////////////////////////////
};

  //////////////////////////////////////////////////////////////////////////
};
