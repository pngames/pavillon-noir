/*
* pni10n.h
* 
* Description :
* Internationnalisation system
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

#include <map>
#include <string>
#include <libxml/xmlreader.h>

#include "pndefs.h"

#include "i10n_format.h"

#include "PNLocale.hpp"

#include "PNI10n.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

static const std::string  default = "";

static const std::string  error = "!KEY DOES NOT EXIST!";
static const std::string  errrorVariant = "!VARIANT DOES NOT EXIST!";
static const std::string  errrorCountry = "!COUNTRY DOES NOT EXIST!";
static const std::string  errrorLanguage = "!LANGUAGE DOES NOT EXIST!";

//////////////////////////////////////////////////////////////////////////

const std::string&
StringMap::getString(const std::string& key)
{
  iterator	it = find(key);

  if (it == end())
	return error;

  return it->second;
}

void
StringMap::addString(const std::string& key, const std::string& value)
{
  (*this)[key] = value;
}

//////////////////////////////////////////////////////////////////////////

const std::string&
VarientMap::getString(const std::string& key, const PNLocale& locale)
{
  iterator	it = find(locale.getVariant());

  if (it == end())
  {
	it = find(default);
	if (it == end())
	  return errrorVariant;
  }

  return it->second.getString(key);
}

void
VarientMap::addString(const std::string& key, const std::string& value, const PNLocale& locale)
{
  (*this)[locale.getVariant()].addString(key, value);
}

//////////////////////////////////////////////////////////////////////////

const std::string&
CountryMap::getString(const std::string& key, const PNLocale& locale)
{
  iterator	it = find(locale.getCountry());

  if (it == end())
  {
	it = find(default);
	if (it == end())
	  return errrorCountry;
  }

  return it->second.getString(key, locale);
}

void
CountryMap::addString(const std::string& key, const std::string& value, const PNLocale& locale)
{
  (*this)[locale.getCountry()].addString(key, value, locale);
}

//////////////////////////////////////////////////////////////////////////

PNI10n*			PNI10n::_instance = NULL;

PNI10n*			
PNI10n::getInstance()
{
  if (_instance == NULL)
	_instance = new PNI10n();

  return _instance;
}

PNI10n::PNI10n()
{ }

PNI10n::~PNI10n()
{ }

//////////////////////////////////////////////////////////////////////////

void
PNI10n::addString(const std::string& key, const std::string& value, const PNLocale& locale)
{
  (*this)[locale.getLanguage()].addString(key, value, locale);
}

const std::string&	
PNI10n::_getString(const std::string& key, const PNLocale& locale)
{
  iterator	it = find(locale.getLanguage());

  if (it == end())
  {
	it = find(default);
	if (it == end())
	  return errrorLanguage;
  }

  return it->second.getString(key, locale);
}

const std::string&	
PNI10n::getString(const std::string& key)
{
  return getString(key, PNLocale::defaultLocale());
}

const std::string&
PNI10n::getString(const std::string& key, const PNLocale& locale)
{
  return getInstance()->_getString(key, locale);
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PNI10n::getDTD() const
{
  return PNI10N_XMLDTD;
}

const std::string&
PNI10n::getDTDName() const
{
  return PNI10N_XMLDTD_NAME;
}

const std::string&
PNI10n::getRootNodeName() const
{
  return PNI10N_XMLNODE_ROOT;
}

//////////////////////////////////////////////////////////////////////////

pnint
PNI10n::_unserializeString(xmlNode* node)
{
  std::string	key = (const char*)xmlGetProp(node, PNI10N_XMLPROP_KEY);
  std::string	value = (const char*)xmlGetProp(node, PNI10N_XMLPROP_VALUE);

  PNLocale		locale("");

  xmlChar* attr = xmlGetProp(node, PNI10N_XMLPROP_LOCALE);
  if (attr != NULL)
	;

  addString(key, value, locale);

  return PNEC_NOT_IMPLEMENTED;
}

pnint
PNI10n::_unserializeNode(xmlNode* node)
{
  if (PNI10N_XMLNODE_STRING == (const char*)node->name)
	_unserializeString(node);

  return PNEC_SUCCESS;
}

pnint
PNI10n::unserializeFromXML(xmlNode* root)
{
  for (root = root->children ; root != NULL; root = root->next)
	_unserializeNode(root);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////
};
