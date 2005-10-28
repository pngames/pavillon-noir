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

namespace PN
{

class PNAPI			IPNXMLSerializable : public IPNSerializable
{
protected:
  static const std::string	_dtd;
  static const std::string	_dtdName;

  static const std::string	_rootNode;

  IPNXMLSerializable();
public:
  virtual ~IPNXMLSerializable() {}

  //////////////////////////////////////////////////////////////////////////
  
  virtual const std::string&  getDTD() const;
  virtual const std::string&  getDTDName() const;
  virtual const std::string&  getRootNodeName() const;

  //////////////////////////////////////////////////////////////////////////

  /// Parse XML root node
  virtual pnint		unserializeFromXML(xmlNode* node);
  /// Load object from XML file
  virtual pnint		unserializeFromFile(const boost::filesystem::path& file);

  /// Save object to file
  virtual pnint		serializeInXMLFile(const boost::filesystem::path& file);

  /// Save object into XML file
  virtual pnint		serializeInXML(xmlNode* node, pnbool root = false);
};

}

#endif /*!_IPNXMLSERIALIZATION_HPP_*/
