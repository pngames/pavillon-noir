/*
 * pnp_format.h
 * 
 * Description :
 * Physical objects files format
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

#ifndef _PNP_FORMAT_H_
# define _PNP_FORMAT_H_

#include <string>

namespace PN {
//////////////////////////////////////////////////////////////////////////

#define PNP_EXT											"pnp"

static const std::string	PNP_XML_HEADER				=
"<?xml version=\"1.0\"?>\n"
"<!DOCTYPE physics SYSTEM \"physics.dtd\">\n";

static const std::string	PNP_XMLDTD_NAME				= "physics";
static const std::string	PNP_XMLDTD					= PNP_XMLDTD_NAME + ".dtd";

static const std::string	PNP_XMLNODE_ROOT			= "physics";
static const std::string	PNP_XMLNODE_MODEL			= "model";

static const std::string	PNP_XMLATTR_TYPEPNM			= "pnm";
static const std::string	PNP_XMLATTR_TYPEOPAL		= "opal";

#define						PNP_XMLPROP_TYPE			(BAD_CAST "type")
#define						PNP_XMLPROP_PATH			(BAD_CAST "path")

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNP_FORMAT_H_*/
