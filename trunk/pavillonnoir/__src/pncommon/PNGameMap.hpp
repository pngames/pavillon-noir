/*
 * PNGameMap.hpp
 * 
 * Description :
 * PNGameMap declaration
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

#ifndef _PNGAMEMAP_HPP
# define _PNGAMEMAP_HPP

#include <string>
#include <list>
#include <map>

#include "PNGameEventData.hpp"

#include "PNObject.hpp"
#include "IPNXMLSerializable.hpp"

typedef struct _xmlNode		xmlNode;

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNWayPoint;
class PNIAGraph;
class PN3DCamera;
class PN3DObject;

class PNAPI						PNGameMap : public PNObject, public IPNXMLSerializable
{
public:
  typedef std::map<std::string, PN3DObject *>	ObjMap;
protected:
  pnfloat						_mpp;
  ObjMap						_entityList;
  PN3DCamera*					_camera;
  PN3DObject*					_player;
  std::string			  		_wpFile;

  PNGameLoadStepsMapEventData	_eaLoadStep;

  pnint							_unserializeSkybox(xmlNode* node);
  pnint							_unserializeEntity(xmlNode* node);
  pnint							_unserializeNode(xmlNode* node);

  pnint							_serializeSkybox(xmlNode* node);
  pnint							_serializeEntity(xmlNode* node, PN3DObject* object);
public:
  PNGameMap();
  ~PNGameMap();

  //////////////////////////////////////////////////////////////////////////

protected:
  /// Load object from file
  virtual pnint					unserializeFromFile(const boost::filesystem::path& dir);
  /// Save object to file
  virtual pnint					serializeInFile(const boost::filesystem::path& file);

public:
  /// Parse XML root node
  virtual pnint					unserializeFromXML(xmlNode* node);
  /// Save object into XML file
  virtual pnint					serializeInXML(xmlNode* node, pnbool root = false);

  //////////////////////////////////////////////////////////////////////////

  const ObjMap&					getEntityList() const;
  pnfloat						getMpp();

  const PN3DObject*				getPlayer() {return _player;}
  //////////////////////////////////////////////////////////////////////////

  virtual void					executeScript(const std::string& ScriptName) {}

  //add an object to the gameMap
  virtual void					addToMap(const std::string& entityName,const std::string& id);
  virtual void					clear();
  
  const std::string&			getWpFile();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNGAMEMAP_HPP*/
