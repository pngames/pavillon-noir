/*
 * PNConfigurableObject.cpp
 * 
 * Description :
 * PNConfigurableObject definition
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
#include "pcf_format.h"

#include "PNConfigurableParameter.hpp"

#include "PNConfigurableObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNConfigurableObject::~PNConfigurableObject() 
{

}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNConfigurableObject::getLabel()
{
  return getName();
}

//////////////////////////////////////////////////////////////////////////

pnbool					
PNConfigurableObject::modified()
{
  return false; 
}

void		
PNConfigurableObject::setModified() 
{

}

void				
PNConfigurableObject::setUnmodified() 
{

}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNConfigurableObject::getDTD() const
{
  return PCF_OBJECT_XMLDTD;
}

const std::string&
PNConfigurableObject::getDTDName() const
{
  return PCF_OBJECT_XMLDTD_NAME;
}

const std::string&
PNConfigurableObject::getRootNodeName() const
{
  return PCF_OBJECT_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableObject::_unserializeNode(xmlNode* node)
{
  for (int i = 0; i < getNbParameters(); ++i)
  {
	PNConfigurableParameter*  param = getParameter(i);
	if (param->getName() == (const char*)node->name)
	{
	  param->unserializeFromXML(node);

	  return PNEC_SUCCESS;
	}
  }

  return PNEC_SUCCESS;
}

pnint
PNConfigurableObject::unserializeFromXML(xmlNode* root)
{
  for (root = root->children ; root != NULL; root = root->next)
	_unserializeNode(root);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNConfigurableObject::_serializeContent(xmlNode* node)
{
  xmlNewProp(node, PCF_XMLPROP_NAME, BAD_CAST getName().c_str());

  //////////////////////////////////////////////////////////////////////////
  
  for (int i = 0; i < getNbParameters(); ++i)
  {
	PNConfigurableParameter*  param = getParameter(i);
	param->serializeInXML(node);
  }

  return PNEC_SUCCESS;
}

pnint
PNConfigurableObject::serializeInXML(xmlNode* root, pnbool isroot/* = false*/)
{
  if (!isroot)
	root = xmlNewChild(root, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  return _serializeContent(root);
}

//////////////////////////////////////////////////////////////////////////
};
