/*
 * pcf_format.h
 * 
 * Description :
 * Configurable Objects files format
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

#ifndef _PCF_FORMAT_H_
# define _PCF_FORMAT_H_

#include <string>

#define PCF_EXT											"pcf"

static const std::string	PCF_XMLDTD_NAME				= "configuration";
static const std::string	PCF_XMLDTD					= PCF_XMLDTD_NAME + ".dtd";
static const std::string	PCF_XMLNODE_ROOT			= PCF_XMLDTD_NAME;

//////////////////////////////////////////////////////////////////////////

static const std::string	PCF_OBJECT_XMLDTD_NAME		= "configurable_object";
static const std::string	PCF_OBJECT_XMLDTD			= PCF_XMLDTD_NAME + ".dtd";
static const std::string	PCF_OBJECT_XMLNODE_ROOT		= PCF_XMLDTD_NAME;

#define						PCF_XMLPROP_NAME			(BAD_CAST "name")

//////////////////////////////////////////////////////////////////////////

static const std::string	PCF_PARAM_XMLDTD_NAME		= "parameter";
static const std::string	PCF_PARAM_XMLNODE_ROOT		= PCF_PARAM_XMLDTD_NAME;

#define						PCF_XMLPROP_NAME			(BAD_CAST "name")

//////////////////////////////////////////////////////////////////////////

static const std::string	PCF_PARAMV_XMLDTD_NAME		= "value";
static const std::string	PCF_PARAMV_XMLNODE_ROOT		= PCF_PARAMV_XMLDTD_NAME;

#define						PCF_XMLPROP_DATA			(BAD_CAST "data")

#endif /*_PCF_FORMAT_H_*/
