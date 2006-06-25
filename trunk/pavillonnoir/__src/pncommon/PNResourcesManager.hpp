/*
* PNResourcesManager.hpp
* 
* Description :
* PNResourcesManager declaration
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

#ifndef _PNRESOURCES_H_
# define _PNRESOURCES_H_

#include <string>
#include <list>

#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

/// Resource manager for datafiles
class PNAPI						PNResourcesManager : public IPNXMLSerializable
{
private:
  static PNResourcesManager*	_instance;

  PNResourcesManager();
  ~PNResourcesManager();

public:
  static PNResourcesManager*	getInstance();

public:
  struct		datafile 
  {
	std::string	id;
	std::string	path;
  };

  typedef std::list<datafile>	DatafileList;

  void							setDefault(const std::string& id);
  const std::string&			getDefault();

  std::string					getDefault(pnResourceType rt);

  const std::string&			getRoot();

  //////////////////////////////////////////////////////////////////////////
  
  const DatafileList&			getDatafiles();

  std::string					getResourcePath(const std::string& id, pnResourceType rt);

  //////////////////////////////////////////////////////////////////////////
  
  std::string					findPath(const std::string& rt, const std::string& path);
  pnerrorcode					findPath(const std::string& rt, const std::string& path, std::string& outPath);

  std::string					findPath(pnResourceType rt, const std::string& path);
  pnerrorcode					findPath(pnResourceType rt, const std::string& path, std::string& outPath);

  pnbool						isExist(const std::string& datafile, pnResourceType rt, const std::string& path);

  std::string					convertPath(pnResourceType rt, const std::string& path);

  //////////////////////////////////////////////////////////////////////////
  
protected:
  /// Parse XML datafile node
  pnint							_parseDatadirectory(xmlNode* node);
  /// Parse XML datafiles internal node
  virtual pnint					_unserializeNode(xmlNode* node);

  //////////////////////////////////////////////////////////////////////////
  // PNXMLSERIALIZABLE
protected:
  virtual const std::string&	getDTD() const;
  virtual const std::string&	getDTDName() const;
  virtual const std::string&	getRootNodeName() const;

  //////////////////////////////////////////////////////////////////////////
  
private:

  std::string					_names[PNRT_NB];

  DatafileList					_datafiles;

  std::string					_root;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNRESOURCES_H_*/
