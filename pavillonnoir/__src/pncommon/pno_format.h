/*
 * pno_format.h
 * 
 * Description :
 * Object files format
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

#ifndef _PNO_FORMAT_H_
# define _PNO_FORMAT_H_

#include <string>

#define PNO_EXT											"pno"

static const std::string	PNO_XML_HEADER				=
"<?xml version=\"1.0\"?>\n"
"<!DOCTYPE object SYSTEM \"object.dtd\">\n";

static const std::string	PNO_XMLDTD_NAME				= "object";
static const std::string	PNO_XMLDTD					= PNO_XMLDTD_NAME + ".dtd";

static const std::string	PNO_XMLNODE_ROOT			= "object";
static const std::string	PNO_XMLNODE_MODEL			= "model";
static const std::string	PNO_XMLNODE_LISTMATERIALS	= "listmaterials";
static const std::string	PNO_XMLNODE_MATERIAL		= "material";
static const std::string	PNO_XMLNODE_SKELETON		= "skeleton";
static const std::string	PNO_XMLNODE_LISTANIMS		= "listanims";
static const std::string	PNO_XMLNODE_ANIM			= "anim";
static const std::string	PNO_XMLNODE_PHYSICS			= "physics";

#define						PNO_XMLPROP_PATH			(BAD_CAST "path")


//const string	PN3DObject::_modelNode = "model";
//const string	PN3DObject::_materialsNode = "listmaterials";

#endif /*_PNO_FORMAT_H_*/
