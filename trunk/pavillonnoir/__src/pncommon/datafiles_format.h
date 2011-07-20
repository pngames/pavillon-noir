/*
* datafiles_format.h
* 
* Description :
* Datafiles files format
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

#ifndef _DATAFILES_FORMAT_H_
# define _DATAFILES_FORMAT_H_

#include <string>

#define DATAFILES_XML_HEADER_EXT						"xml"

static const std::string	DATAFILES_XMLDTD_NAME		= "datafiles";
static const std::string	DATAFILES_XMLDTD			= DATAFILES_XMLDTD_NAME + ".dtd";
static const std::string	DATAFILES_XMLNODE_ROOT		= DATAFILES_XMLDTD_NAME;

static const std::string	DATAFILES_XMLNODE_DATAD		= "datadirectory";

#define						DATAFILES_XMLPROP_PATH		(BAD_CAST "path")

#define						DATAFILES_XMLPROP_ID		(BAD_CAST "id")

#endif /*_DATAFILES_FORMAT_H_*/
