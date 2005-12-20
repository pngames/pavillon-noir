/*
* i10n_format.h
* 
* Description :
* Internationalization files format
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

#ifndef _I18N_FORMAT_H_
# define _I18N_FORMAT_H_

#include <string>

namespace PN {
//////////////////////////////////////////////////////////////////////////

#define I18N_EXT										"xml"

static const std::string	PNI18N_XMLDTD_NAME			= "i18n";
static const std::string	PNI18N_XMLDTD				= PNI18N_XMLDTD_NAME + ".dtd";
static const std::string	PNI18N_XMLNODE_ROOT			= PNI18N_XMLDTD;

static const std::string	PNI18N_XMLNODE_STRING		= "string";

#define						PNI18N_XMLPROP_KEY			(BAD_CAST "key")
#define						PNI18N_XMLPROP_VALUE		(BAD_CAST "value")
#define						PNI18N_XMLPROP_LOCALE		(BAD_CAST "locale")

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_I18N_FORMAT_H_*/
