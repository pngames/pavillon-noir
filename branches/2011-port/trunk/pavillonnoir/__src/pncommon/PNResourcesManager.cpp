/*
* PNResourcesManager.cpp
* 
* Description :
* PNResourcesManager definition
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
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnresources.h"
#include "datafiles_format.h"

#include "PNResourcesManager.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNResourcesManager*	PNResourcesManager::_instance = NULL;

PNResourcesManager*	PNResourcesManager::getInstance()
{
  if (_instance == NULL)
	_instance = new PNResourcesManager();

  return _instance;
}
//////////////////////////////////////////////////////////////////////////

PNResourcesManager::PNResourcesManager()
{
  _root = "datafiles";

  _names[PNRT_model] = "models";
  _names[PNRT_material] = "materials";
  _names[PNRT_texture] = "textures";
  _names[PNRT_skeleton] = "skeletons";
  _names[PNRT_animation] = "animations";
  _names[PNRT_physics] = "physics";

  _names[PNRT_object] = "objects";

  _names[PNRT_map] = "maps";

  _names[PNRT_gamedef] = "gamedef";

  _names[PNRT_music] = "music";
  _names[PNRT_sound] = "sounds";
  _names[PNRT_video] = "videos";

  _names[PNRT_layout] = "layouts";
  _names[PNRT_looknfeel] = "looknfeel";
  _names[PNRT_scheme] = "schemes";
  _names[PNRT_imageset] = "imagesets";
  _names[PNRT_font] = "fonts";

  _names[PNRT_chat] = "chats";

  //////////////////////////////////////////////////////////////////////////
  
  unserializeFromPath(_root + PATHSEP + "datafiles.xml");
}

PNResourcesManager::~PNResourcesManager()
{

}

//////////////////////////////////////////////////////////////////////////


void
PNResourcesManager::setDefault(const std::string& id)
{
  for (DatafileList::iterator it = _datafiles.begin(); it != _datafiles.end(); ++it)
	if ((*it).id == id)
	{
	  _datafiles.splice(_datafiles.begin(), _datafiles, it);

	  break;
	}
}

const std::string&
PNResourcesManager::getDefault()
{
  return (*_datafiles.begin()).id;
}

std::string
PNResourcesManager::getDefault(pnResourceType rt)
{
  return (*_datafiles.begin()).path + PATHSEP + _names[rt] + PATHSEP;
}

const std::string&
PNResourcesManager::getRoot()
{
  return _root;
}

//////////////////////////////////////////////////////////////////////////

const PNResourcesManager::DatafileList&
PNResourcesManager::getDatafiles()
{
  return _datafiles;
}

std::string
PNResourcesManager::getResourcePath(const std::string& id, pnResourceType rt)
{
  for (DatafileList::iterator it = _datafiles.begin(); it != _datafiles.end(); ++it)
	if ((*it).id == id)
	  return _root + PATHSEP + (*it).path + PATHSEP + _names[rt] + PATHSEP;

  return _root + PATHSEP + id + PATHSEP + _names[rt] + PATHSEP;
}

//////////////////////////////////////////////////////////////////////////

std::string
PNResourcesManager::findPath(const std::string& rt, const std::string& path)
{
  std::string outPath;

  if (findPath(rt, path, outPath) != PNEC_SUCCESS)
	return "";

  return outPath;
}

pnerrorcode
PNResourcesManager::findPath(const std::string& rt, const std::string& path, std::string& outPath)
{
  std::string	subPath = rt + PATHSEP + path;

  for (DatafileList::iterator it = _datafiles.begin(); it != _datafiles.end(); ++it)
  {
	const datafile&	df = *it;

	outPath = _root + PATHSEP + df.path + PATHSEP + subPath;

	if (fs::exists(fs::path(outPath, fs::no_check)))
	  return PNEC_SUCCESS;
  }

  return PNEC_ERROR;
}

std::string
PNResourcesManager::findPath(pnResourceType rt, const std::string& path)
{
  return findPath(_names[rt], path);
}

pnerrorcode
PNResourcesManager::findPath(pnResourceType rt, const std::string& path, std::string& outPath)
{
  return findPath(_names[rt], path, outPath);
}

pnbool
PNResourcesManager::isExist(const std::string& datafile, pnResourceType rt, const std::string& path)
{
  return fs::exists(fs::path(_root + PATHSEP + datafile + PATHSEP + _names[rt] + PATHSEP + path, fs::no_check));
}

std::string
PNResourcesManager::convertPath(pnResourceType rt, const std::string& path)
{
  std::string::size_type	  index = path.rfind(_names[rt] + PATHSEP);

  if (index == std::string::npos)
  {
	index = path.rfind(_names[rt] + '/');

	if (index == std::string::npos)
	  return path;
  }

  return path.c_str() + index + _names[rt].size() + 1;
}

//////////////////////////////////////////////////////////////////////////

/// Parse XML datafile node
pnint
PNResourcesManager::_parseDatadirectory(xmlNode* node)
{
  datafile	df;

  const xmlChar* id = xmlGetProp(node, DATAFILES_XMLPROP_ID);

  df.path = (const char*)xmlGetProp(node, DATAFILES_XMLPROP_PATH);

  if (id != NULL)
	df.id = (const char*)id;
  else
	df.id = df.path;

  _datafiles.push_back(df);

  return PNEC_SUCCESS;
}

/// Parse XML datafiles internal node
pnint
PNResourcesManager::_unserializeNode(xmlNode* node)
{
  if (DATAFILES_XMLNODE_DATAD == (const char*)node->name)
	_parseDatadirectory(node);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNResourcesManager::getDTD() const
{
  return DATAFILES_XMLDTD;
}

const std::string&
PNResourcesManager::getDTDName() const
{
  return DATAFILES_XMLDTD_NAME;
}

const std::string&
PNResourcesManager::getRootNodeName() const
{
  return DATAFILES_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////
};
