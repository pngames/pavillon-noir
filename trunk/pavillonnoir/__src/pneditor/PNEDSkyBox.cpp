/*
* PNEDSkybox.cpp
* 
* Description :
* PNEDSkybox definition
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

#include <sstream>
#include <libxml/xmlreader.h>

#include "pneditorcommon.hpp"
#include "pnimport.h"
#include "pnexception.h"
#include "pnrender.h"
#include "pnresources.h"

#include "pnxml.h"

#include "PNPropertiesGrid.hpp"
#include "PNPropertiesPanel.hpp"
#include "PNEditor.hpp"

#include "PNEDSkyBox.hpp"

namespace fs = boost::filesystem;
using namespace PN;
using namespace PN::EDITOR;

//////////////////////////////////////////////////////////////////////////

namespace PN {
namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

/* Map
FXDEFMAP(PNEDSkybox) PNEDSkyboxMap[]=
{
FXMAPFUNC(SEL_LEFTBUTTONRELEASE,0,PNEDSkybox::onLeftBtnRelease),
FXMAPFUNC(SEL_DND_DROP,0,PNEDSkybox::onDNDDrop),
FXMAPFUNC(SEL_SELECTED,0,PNEDSkybox::onSelected)
};
*/

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT_ABSTRACT(PNEDSkybox,FXGLShape,NULL,0)

//////////////////////////////////////////////////////////////////////////

const std::string	PNEDSkybox::_label = "SkyBox";

PNEDSkybox::PNEDSkybox(void)
{
  FXTRACE((100,"PNEDSkybox::PNEDSkybox\n"));

  range.lower.x = 0;
  range.lower.y = 0;
  range.lower.z = 0;
  range.upper.x = 1000;
  range.upper.y = 1000;
  range.upper.z = 1000;

  buildParams();
}

void
PNEDSkybox::setContext(PNPropertiesPanel* grid, PNEditor* ed)
{
  _grid = grid;
  _ed = ed;
}

// Destroy
PNEDSkybox::~PNEDSkybox()
{
  FXTRACE((100,"PNEDSkybox::~PNEDSkybox\n"));
}

//////////////////////////////////////////////////////////////////////////

void
PNEDSkybox::buildParams()
{
  _params.push_back(new PNConfigurableParameter(this, PN_PARAMTYPE_BOOLEAN, &_enabled, "enabled", "enable"));
}

// Draw this object in a viewer
void
PNEDSkybox::drawshape(FXGLViewer* v)
{
  PNRendererInterface::getInstance()->renderSkyBox(2000);
}

//////////////////////////////////////////////////////////////////////////

void
PNEDSkybox::update(PNConfigurableParameter* p)
{
  PNRendererInterface::getInstance()->setSkyBoxEnabled(_enabled);

  //////////////////////////////////////////////////////////////////////////

  _ed->redraw();
}

int
PNEDSkybox::getNbParameters()
{
  return _params.size();
}

PNConfigurableParameter*
PNEDSkybox::getParameter(int idx)
{
  return _params[idx];
}

void
PNEDSkybox::reset()
{
  
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNEDSkybox::getRootNodeName() const
{
  return PNENTITY_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNEDSkybox::unserializeFromXML(xmlNode* root)
{
  _enabled = XMLUtils::xmlGetProp(root, PNXML_ENABLED_ATT, true);

  //////////////////////////////////////////////////////////////////////////

  _grid->addObject(this);

  update(NULL);

  return PNEC_SUCCESS;
}

pnint
PNEDSkybox::serializeInXML(xmlNode* root, pnbool isroot/* = false*/)
{
  if (isroot == false)
	root = xmlNewChild(root, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  //////////////////////////////////////////////////////////////////////////

  XMLUtils::xmlNewProp(root, PNXML_ENABLED_ATT, _enabled);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
//////////////////////////////////////////////////////////////////////////
};
