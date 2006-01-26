/*
 * IPNXMLSerializable.hpp
 * 
 * Description :
 * Base interface for serialization support
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
 
#ifndef _IPNXMLSERIALIZATION_HPP_
# define _IPNXMLSERIALIZATION_HPP_

#include "IPNSerializable.hpp"

typedef struct _xmlNode		xmlNode;
typedef struct _xmlAttr		xmlAttr;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNPoint3f;

class PNAPI						IPNXMLSerializable : public IPNSerializable
{
private:
  static const std::string		_dtd;
  static const std::string		_dtdName;

  static const std::string		_rootNode;

protected:
  pnbool						_serializeInXML;

  IPNXMLSerializable();
  virtual ~IPNXMLSerializable() {}

  //////////////////////////////////////////////////////////////////////////
  
public:
  
  virtual const std::string&	getDTD() const;
  virtual const std::string&	getDTDName() const;
  virtual const std::string&	getRootNodeName() const;

  //////////////////////////////////////////////////////////////////////////

protected:
  /// Load object from XML file
  virtual pnint					unserializeFromFile(const boost::filesystem::path& file);
  /// Save object to file
  virtual pnint					serializeInFile(const boost::filesystem::path& file);

protected:
  virtual pnint					_unserializeNode(xmlNode* node);
  virtual pnint					_serializeContent(xmlNode* node);

public:
  /// Parse XML root node
  virtual pnint					unserializeFromXML(xmlNode* node);
  /// Save object into XML file
  virtual pnint					serializeInXML(xmlNode* node, pnbool root = false);
};

namespace XMLUtils
{
  PNAPI pnuint					xmlGetNbChilds(xmlNode* node);

  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const pnuchar* name, pnbool value);
  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const char* name, pnbool value);
  PNAPI pnbool					xmlGetProp(xmlNode* node, const pnuchar* name, pnbool def);
  PNAPI pnbool					xmlGetProp(xmlNode* node, const char* name, pnbool def);

  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const pnuchar *name, pnint value);
  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const char *name, pnint value);
  PNAPI pnint					xmlGetProp(xmlNode* node, const pnuchar* name, pnint def);
  PNAPI pnint					xmlGetProp(xmlNode* node, const char* name, pnint def);

  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const pnuchar *name, pnuint value);
  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const char *name, pnuint value);
  PNAPI pnuint					xmlGetProp(xmlNode* node, const pnuchar* name, pnuint def);
  PNAPI pnuint					xmlGetProp(xmlNode* node, const char* name, pnuint def);

  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const pnuchar *name, pnfloat value);
  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const char *name, pnfloat value);
  PNAPI pnfloat					xmlGetProp(xmlNode* node, const pnuchar* name, pnfloat def);
  PNAPI pnfloat					xmlGetProp(xmlNode* node, const char* name, pnfloat def);

  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const pnuchar *name, const PNPoint3f& value);
  PNAPI xmlAttr*				xmlNewProp(xmlNode* node, const char *name, const PNPoint3f& value);
  PNAPI PNPoint3f				xmlGetProp(xmlNode* node, const pnuchar* name, const PNPoint3f& def);
  PNAPI PNPoint3f				xmlGetProp(xmlNode* node, const char* name, const PNPoint3f& def);
}

//////////////////////////////////////////////////////////////////////////
}

#endif /*!_IPNXMLSERIALIZATION_HPP_*/


