/*
* PNConf.cpp
* 
* Description :
* PNConf definition
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

#include <cstdlib>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <libxml/tree.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

#ifdef WIN32
# include <Windows.h>
# include <shlobj.h>
#endif

#include "pndefs.h"
#include "PNConf.hpp"

using namespace PN;
namespace fs = boost::filesystem;

namespace PN
{

PNConf* PNConf::_instance = NULL;

/**
* @brief initialize PNConf class. If called multiple times, do nothing.
* @return nothing
* @sa getInstance()
*/
void
PNConf::initialize()
{
  if (_instance == NULL)
	_instance = new PNConf();
}

/**
* @brief get a sole instance of the class
* @return a pointer to an instance of PNConf
* @sa initialize()
*/
PNConf*
PNConf::getInstance()
{
  if (_instance == NULL)
	_instance = new PNConf();

  return _instance;
}

/**
* @brief class constructor
*
* Tries to read the configuration file and to parse it. If it doesn't exist, then create a default configuration file. It also creates the path to configuration file if it doesn't exist.
* @return nothing
* @sa ~PNConf()
*/
PNConf::PNConf()
{
  /*
  * filling default configuration map
  */
  _defaultHash["video"]["Resolution"] = "1024x768";
  _defaultHash["video"]["Fullscreen"] = "no";
  _defaultHash["game"]["Key binding profile"] = "default";
  _defaultHash["sound"]["Music volume"] = "50";
  _defaultHash["sound"]["Game volume"] = "70";

  xmlKeepBlanksDefault(1);
#ifdef WIN32
  TCHAR szPath[MAX_PATH];
  if(SUCCEEDED(SHGetFolderPath(NULL,
	CSIDL_APPDATA|CSIDL_FLAG_CREATE,
	NULL,
	0,
	szPath)))
	_homePath = szPath;
#else
  _homePath = getenv("HOME");
#endif

  const fs::path pnConfDirPath = this->getConfPath();
  if (!fs::exists(pnConfDirPath))
	fs::create_directory(pnConfDirPath);
  _confFilePath = pnConfDirPath / PNCONFFILE;
  if (!fs::exists(_confFilePath))
	this->_createDefaultConf();
  this->_loadConfFile();
}

/**
* @brief class destructor. On deletion it saves current configuration.
* @return nothing
* @sa PNConf()
*/
PNConf::~PNConf()
{
  saveConf();
}

/**
* @brief save the current configuration held in the class hash to configuration file.
* @return nothing
*/
void
PNConf::saveConf()
{
  xmlDocPtr doc = xmlNewDoc((const xmlChar *)"1.0");
  xmlNodePtr root = xmlNewNode(NULL, (const xmlChar *)"configuration");
  xmlDocSetRootElement(doc, root);

  std::map<std::string, std::map<std::string, std::string> >::iterator section;
  for (section = _confHash.begin(); section != _confHash.end(); ++section)
  {
  	xmlNodePtr node = xmlNewTextChild(root, NULL, (const xmlChar *)"section", NULL);
  	xmlNewProp(node, (const xmlChar *)"name", (const xmlChar *)section->first.c_str());
  	
  	std::map<std::string, std::string>::iterator key;
  	for (key = section->second.begin(); key != section->second.end(); ++key)
  	{
		xmlNodePtr item = xmlNewTextChild(node, NULL, (const xmlChar *)"item", NULL);
		xmlNewProp(item, (const xmlChar *)"key", (const xmlChar *)key->first.c_str());
		xmlNewProp(item, (const xmlChar *)"value", (const xmlChar *)key->second.c_str());
  	}
  }
  xmlSaveFormatFile(_confFilePath.native_file_string().c_str(), doc, 1);
  xmlFreeDoc(doc);
}

/**
* @brief set a key for a section and its value
* @param key string value representing an item key
* @param value string value representing an item value
* @param section string value of the section
* @return nothing
* @sa getKey()
*/
void
PNConf::setKey(const std::string& key, const std::string& value, const std::string& section)
{
  _confHash[section][key] = value;
}

/**
* @brief get the configuration path
* @return the configuration path (boost filesystem type)
*/
fs::path
PNConf::getConfPath()
{
  return fs::path(_homePath + PATHSEPSTRING + UNIXPREFIX + PNCONFPATH, fs::no_check);
}

/**
* @brief load the configuration file
* @return nothing
* @sa PNConf()
*/
void
PNConf::_loadConfFile()
{
  xmlDocPtr xmlDoc = xmlParseFile(_confFilePath.native_file_string().c_str());
  xmlNodePtr xmlNode = xmlDocGetRootElement(xmlDoc);
  if (xmlStrcmp(xmlNode->name, (const xmlChar *) "configuration"))
  {
	xmlFreeNode(xmlNode);
	xmlFreeDoc(xmlDoc);
	throw PNException("Configuration file corrupted !");
  }

  xmlNodePtr Section = xmlNode->xmlChildrenNode;
  while (Section != NULL)
  {
  	if ((!xmlStrcmp(Section->name, (const xmlChar *)"section")))
  	{
		xmlNode = Section->xmlChildrenNode;
		if ((!xmlStrcmp(xmlNode->name, (const xmlChar *)"item")))
			_confHash[(char*)xmlGetProp(Section, (const xmlChar *)"name")][(char*)xmlGetProp(xmlNode, (const xmlChar *)"key")] = (char*)xmlGetProp(xmlNode, (const xmlChar *)"value");

		xmlNode = xmlNode->next;
  	}
  	Section = Section->next;  	
  }
  xmlFreeDoc(xmlDoc);
}

/**
* @brief create a default configuration file
* @return nothing
* @sa PNConf()
*/
void
PNConf::_createDefaultConf()
{
	std::map<std::string, std::map<std::string, std::string> >::iterator section;
	for (section = _defaultHash.begin(); section != _defaultHash.end(); ++section)
	{
		std::map<std::string, std::string>::iterator pos;
		for (pos = section->second.begin(); pos != section->second.end(); ++pos)
			_confHash[section->first][pos->first] = pos->second;
	}
	this->saveConf();
}

}
