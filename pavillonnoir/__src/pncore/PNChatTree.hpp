/*
* PNChatTree.hpp
* 
* Description :
* PNChatTree declaration
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

#ifndef _PNCHATTREE_HPP_
# define _PNCHATTREE_HPP_

#include <string>
#include <list>
#include <iterator>


#include <libxml/xmlreader.h>

#include "IPNXMLSerializable.hpp"

namespace PN {
  //////////////////////////////////////////////////////////////////////////

  class 							PNChatTree : public IPNXMLSerializable
  {
	std::string						_id;
	std::string						_name;
	xmlNode*						_currentNode;
	typedef std::list<std::string>			ListResolvedDependencies;
	ListResolvedDependencies				_resolvedDependencies;
	xmlDocPtr						_doc;

	//////////////////////////////////////////////////////////////////////////
	
  public:
	PNChatTree();
	PNChatTree(ListResolvedDependencies& _resolvedDependencies);
	~PNChatTree();
	
	//////////////////////////////////////////////////////////////////////////

  private:
	bool							isAResolvedDep(std::string depID);
	bool							buddyIsAvailable(xmlNodePtr node);

  public:
	virtual pnint					unserializeFromFile(const boost::filesystem::path& file);
	virtual pnint					unserializeFromXML(xmlNode* node);

	void							setListDependencies(ListResolvedDependencies& deps);
	xmlNode*						getCurrentNode();  
	xmlNode*						getBuddyNode(xmlNode* currentNode);
	xmlNode*						getNodeFromId(xmlNode* root, std::string NodeId);
  };

  //////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNCHATTREE_HPP_*/

