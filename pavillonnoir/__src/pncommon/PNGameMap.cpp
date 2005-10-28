/*
* PNGameMap.cpp
* 
* Description :
* PNGameMap definition
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

#include <boost/filesystem/operations.hpp>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnimport.h"
#include "pnresources.h"
#include "PN3DCamera.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PNPhysicsInterface.hpp"
#include "PNPhysicalObject.hpp"
#include "PN3DCamera.hpp"
#include "PNRendererInterface.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNCharacter.hpp"

#include "PNGameMap.hpp"


namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

#define STATIC_ENTITY (const char *)"true"
#define DYNAMIC_ENTITY (const char *)"false"
#define LISTENTITIES_MARKUP (const char *)"listentities"

PNGameMap::PNGameMap()
{
    PNPhysicsInterface::getInstance()->createSimulation();
}

PNGameMap::~PNGameMap()
{
    PNPhysicsInterface::getInstance()->destroySimulation();
}

const PNGameMap::ObjMap&
PNGameMap::getEntityList() const
{
    return _entityList;
}

int	  PNGameMap::_parseStaticEntity(xmlNode* node)
{
    for (xmlNodePtr current = node; current->next; current = current->next)
    {
        pnerror(PN_LOGLVL_DEBUG, "%s : %s", "PNGameMap - New static entity", xmlGetProp((xmlNodePtr)node, (const xmlChar *)"mdref"));
    }

    /* FIXME : creer le BSP via le module BSP */

    return PNEC_SUCCES;
}


int	  PNGameMap::_parseDynamicEntity(xmlNode* node)
{
    xmlNodePtr  current = node;
    std::string id;
    std::string className;

    /*pnerror(PN_LOGLVL_DEBUG, "PNGameMap - New dynamic entity : name %s, id %s, mdref %s", 
    current->name, 
    xmlGetProp(current, (const xmlChar *)"id"), 
    xmlGetProp(current, (const xmlChar *)"mdref"));*/

    //////////////////////////////////////////////////////////////////////////

    id = (char *)xmlGetProp(current, (const xmlChar *)"id");
    if (_entityList.find(id) != _entityList.end())
    {
        pnerror(PN_LOGLVL_ERROR, "An object with id: [%s] already exists", id.c_str());
        return PNEC_ERROR;
    }
    className = (char *)xmlGetProp(current, (const xmlChar *)"class");
    addToMap(className, id); //cree et stocke l'objet a la fois dans le script et le fw
    PN3DObject*  object = _entityList[id]; //recurepere l'instance du fw 

    //////////////////////////////////////////////////////////////////////////

	// create boost path
    fs::path  file(DEF::objectFilePath + (const char*)xmlGetProp(current, (const xmlChar *)"mdref"), fs::native);

	// set coordinates
    pnfloat x = (float)(atof((const char *)(xmlGetProp(current, (const xmlChar *)"x"))));
    pnfloat y = (float)(atof((const char *)(xmlGetProp(current, (const xmlChar *)"y"))));
    pnfloat z = (float)(atof((const char *)(xmlGetProp(current, (const xmlChar *)"z"))));
    object->setCoord(x, y, z);
    
	// set orientation
	pnfloat xx = (float)(atof((const char *)(xmlGetProp(current, (const xmlChar *)"xx"))));
    pnfloat yy = (float)(atof((const char *)(xmlGetProp(current, (const xmlChar *)"yy"))));
    pnfloat zz = (float)(atof((const char *)(xmlGetProp(current, (const xmlChar *)"zz"))));
    pnfloat ww = (float)(atof((const char *)(xmlGetProp(current, (const xmlChar *)"ww"))));
    object->setOrient(xx, yy, zz, ww);

	// load data files (model, squeleton, materials, physics, etc)
    pnint obj_error = object->unserializeFromFile(file);

	// check for errors
    if (obj_error != PNEC_SUCCES)
        pnerror(PN_LOGLVL_ERROR, "%s : %s", (const char*)xmlGetProp(current, (const xmlChar *)"mdref"), pnGetErrorString(obj_error));

	// enable/disable physical simulation on the object
	if (object->getPhysicalObject())
	{
	  bool isStatic = (!strcmp((const char*)xmlGetProp(current, (const xmlChar *)"envtype"), "dynamic"))?false:true;
	  object->getPhysicalObject()->setStatic(isStatic);
	  object->getPhysicalObject()->setCoord(object->getCoord());
	  object->getPhysicalObject()->setOrient(object->getOrient());
	}

    for (current = current->children; current != NULL; current = current->next)
    { 
        if (current->type != XML_ELEMENT_NODE)
            continue;
    }

    //  if (object->getObjType() == PN3DObject::OBJTYPE_CHARACTER)
    //	((PNCharacter*)object)->buildGraph(*_wpFile);

    return PNEC_SUCCES;
}

int	  PNGameMap::_parseListEntities(xmlNode* node)
{
    //  xmlChar*	  attr = NULL;
    xmlNodePtr  current = node;
    pnint error = PNEC_SUCCES;

    for (; current != NULL; current = current->next)
    {
        if (current->type != XML_ELEMENT_NODE)
            continue;
        //if ((attr = xmlGetProp((xmlNodePtr)current, (const xmlChar *)"static")) != NULL)
        //{
        //if (!strcmp((const char*)attr, STATIC_ENTITY))
        //	error = _parseStaticEntity(current);
        // if (!strcmp((const char*)attr, DYNAMIC_ENTITY))
        error = _parseDynamicEntity(current);
        //}
        //	else
        if (error != PNEC_SUCCES)
            break;
        pnerror(PN_LOGLVL_DEBUG, "PNGameMap - null static attr : %s", current->name);
    }
    return error;
}

int	PNGameMap::unserializeFromXML(xmlNode* node)
{
    //////////////////////////////////////////////////////////////////////////

    xmlNodePtr root = node;
    xmlNodePtr current;

    pnint	error = PNEC_SUCCES;

    //pnerror(PN_LOGLVL_DEBUG, "%s : %s", "PNGameMap - node name", root->name);

    //////////////////////////////////////////////////////////////////////////
    // LISTENTITIES

    if (!strcmp((const char*)root->name, LISTENTITIES_MARKUP))
    {
        for (current = root->children; current->type != XML_ELEMENT_NODE; current = current->next)
        {
            //if (current->type != XML_ELEMENT_NODE)
            //continue;
            if ((error = _parseListEntities(current)) != PNEC_SUCCES)
                return error;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // OTHERS

    return error;
}

pnint PNGameMap::unserializeFromFile(const fs::path& dir)
{
    _wpFile = new fs::path(dir.string() + "/waypoints.xml");

    //////////////////////////////////////////////////////////////////////////

    fs::path file(dir.string() + "/entities.xml");

    pnint error = IPNXMLSerializable::unserializeFromFile(file);

    //////////////////////////////////////////////////////////////////////////
    /*
    map<std::string, PNObject *>& my_list = this->getEntityList();
    map<std::string, PNObject *>::iterator it = my_list.begin();

    for (;it != my_list.end(); it++) 
    {
    pnerror(PN_LOGLVL_DEBUG, "EntityList : %s", it->first);
    }

    char c;
    std::cout << "Appuyez sur une touche pour continuer" << std::endl;
    fread(&c, 1, 1, stdin);
    */

    return error;
}

/*
std::map<std::string, PN3DObject *>& PNGameMap::getEntityList()
{
return _entityList;
}
*/

void PNGameMap::addToMap(const std::string& entityName,const std::string& id)
{
    PN3DSkeletonObject* entity = new PN3DSkeletonObject();
    _entityList[id] = entity;
}

void PNGameMap::clear()
{
   // for (ObjMap::iterator it  = _entityList.begin(); it !=  _entityList.end(); ++it)
   // {
   //     if (it->second != NULL)
   //        delete (it->second);
   // }
    _entityList.clear();
    PNImportManager::getInstance()->clean(); //fixeMe
    //PNPhysicsInterface::clean();
}

const std::string&	PNGameMap::getWpFile()
{
    return _wpFile->string();
}
