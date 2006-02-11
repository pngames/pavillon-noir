/*
* pnchatxml.h
* 
* Description :
* Chat related XML balises and parameters definines.
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

#ifndef _PNCHATXML_H_
# define _PNCHATXML_H_

#include <string>


// DTD

#define PNCHATXML_DTD			(const xmlChar *)"../../chats.dtd"

static const std::string	PNCHAT_XMLDTD_NAME		= "chat";
static const std::string	PNCHAT_XMLDTD			=  std::string("../") + PNCHAT_XMLDTD_NAME + ".dtd";
static const std::string	PNCHAT_XMLNODE_ROOT		= PNCHAT_XMLDTD_NAME;


// Markups

#define PNCHATXML_ROOT_MKP				(const xmlChar *)"chat"
#define PNCHATXML_BUDDY_MKP				(const xmlChar *)"buddy"
#define PNCHATXML_DEPENDS_MKP			(const xmlChar *)"depends"
#define PNCHATXML_PLAYER_MKP			(const xmlChar *)"player"


// Attributes

#define PNCHATXML_BUDDYNAME_ATTR		(const xmlChar *)"name"
#define PNCHATXML_SENTENCE_ATTR			(const xmlChar *)"sentence"
#define PNCHATXML_ANSWER_ATTR			(const xmlChar *)"response"
#define PNCHATXML_QUIT_ATTR				(const xmlChar *)"quit"
#define PNCHATXML_CHECKPOINT_ATTR		(const xmlChar *)"checkpoint"
#define PNCHATXML_ID_ATTR				(const xmlChar *)"id"


// Values

#define PNCHATXML_TRUE_VAL				(const xmlChar *)"true"
#define PNCHATXML_FALSE_VAL				(const xmlChar *)"false"


#endif /* ! _PNCHATXML_H_ */