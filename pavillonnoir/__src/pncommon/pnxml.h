/*
 * pnxml.h
 * 
 * Description :
 * XML balise and parameters definines for map loading
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

#ifndef _PNXML_H_
# define _PNXML_H_

#include <string>

static const std::string	PNMAP_XMLDTD_NAME		= "entities";
static const std::string	PNMAP_XMLDTD			=  std::string("../") + PNMAP_XMLDTD_NAME + ".dtd";
static const std::string	PNMAP_XMLNODE_ROOT		= PNMAP_XMLDTD_NAME;

static const std::string	PNENTITY_XMLNODE_ROOT	= "entity";

// Chat
static const std::string	PNCHAT_XMLDTD_NAME		= "chat";
static const std::string	PNCHAT_XMLDTD			=  std::string("../") + PNCHAT_XMLDTD_NAME + ".dtd";
static const std::string	PNCHAT_XMLNODE_ROOT		= PNCHAT_XMLDTD_NAME;


// Markups

#define PNXML_LISTENTITIES_MKP		(const xmlChar *)PNMAP_XMLNODE_ROOT.c_str()
#define PNXML_ENTITY_MKP			(const xmlChar *)PNENTITY_XMLNODE_ROOT.c_str()
#define PNXML_ACTION_MKP			(const xmlChar *)"action"
#define PNXML_SCRIPT_MKP			(const xmlChar *)"script"
#define PNXML_GRAPH_MKP				(const xmlChar *)"graph"
#define PNXML_LISTWAYPOINTS_MKP		(const xmlChar *)"listwp"
#define	PNXML_WAYPOINT_MKP			(const xmlChar *)"wp"
#define PNXML_LISTLINKS_MKP			(const xmlChar *)"listlnk"
#define PNXML_LINK_MKP				(const xmlChar *)"lnk"
#define PNXML_LISTSOUNDS_MKP		(const xmlChar *)"listsounds"
#define PNXML_SOUND_MKP				(const xmlChar *)"sound"
// Chat
#define PNXML_CHAT_MKP				(const xmlChar *)"chat"
#define PNXML_BUDDY_MKP				(const xmlChar *)"buddy"
#define PNXML_DEPENDS_MKP			(const xmlChar *)"depends"
#define PNXML_PLAYER_MKP			(const xmlChar *)"player"


// Attributes

#define PNXML_ID_ATTR				(const xmlChar *)"id"
#define PNXML_MEPEPI_ATTR			(const xmlChar *)"mpp"
#define PNXML_COORDX_ATTR			(const xmlChar *)"x"
#define PNXML_COORDY_ATTR			(const xmlChar *)"y"
#define PNXML_COORDZ_ATTR			(const xmlChar *)"z"
#define PNXML_ROTX_ATTR				(const xmlChar *)"xx"
#define PNXML_ROTY_ATTR				(const xmlChar *)"yy"
#define PNXML_ROTZ_ATTR				(const xmlChar *)"zz"
#define PNXML_ROTW_ATTR				(const xmlChar *)"ww"
#define	PNXML_ENVTYPE_ATTR			(const xmlChar *)"envtype"
#define	PNXML_OBJTYPE_ATTR			(const xmlChar *)"objtype"
#define PNXML_LABEL_ATTR			(const xmlChar *)"label"
#define PNXML_MODELREFERENCE_ATTR	(const xmlChar *)"mdref"
#define PNXML_PATH_ATTR				(const xmlChar *)"path"
#define PNXML_FROMWP_ATTR			(const xmlChar *)"from"
#define PNXML_TOWP_ATTR				(const xmlChar *)"to"
#define	PNXML_COEF_ATTR				(const xmlChar *)"coef"
#define PNXML_REFERENCE_ATTR		(const xmlChar *)"ref"
#define PNXML_INTENSITY_ATTR		(const xmlChar *)"intensity"
#define PNXML_CLASS_ATTR			(const xmlChar *)"class"
// Chat
#define PNXML_BUDDYNAME_ATTR		(const xmlChar *)"name"
#define PNXML_SENTENCE_ATTR			(const xmlChar *)"sentence"
#define PNXML_ANSWER_ATTR			(const xmlChar *)"answer"
#define PNXML_QUIT_ATTR				(const xmlChar *)"quit"
#define PNXML_CHECKPOINT_ATTR		(const xmlChar *)"checkpoint"


// Values

#define PNXML_DYNAMIC_VAL			(const xmlChar *)"dynamic"
#define PNXML_GROUND_VAL			(const xmlChar *)"ground"
#define PNXML_STATIC_VAL			(const xmlChar *)"static"
#define PNXML_CHARACTER_VAL			(const xmlChar *)"character"
#define PNXML_OBJECT_VAL			(const xmlChar *)"object"
#define PNXML_TRUE_VAL				(const xmlChar *)"true"
#define PNXML_FALSE_VAL				(const xmlChar *)"false"
#define PNXML_IDBASE_VAL			(const xmlChar *)"id_"

// Scripts
#define PNXML_TYPE_ATTR				(const xmlChar *)"type"
#define PNXML_ACTIONCODE_MKP		(const xmlChar *)"action"
#define PNXML_SRC_ATTR				(const xmlChar *)"src"
#define PNXML_INITCODE_MKP			(const xmlChar *)"init"



//////////////////////////////////////////////////////////////////////////
// SKYBOX

static const std::string PNSKBOX_XMLNODE_ROOT	= "skybox";

#define PNXML_SKYBOX_MKP		(const xmlChar *)PNSKBOX_XMLNODE_ROOT.c_str()

#define PNXML_ENABLED_ATT		(const xmlChar *)"enabled"

//////////////////////////////////////////////////////////////////////////

// DTD Files
//#define PNXML_ENTITIES_DTD			(const xmlChar *)"../entities.dtd"
#define PNXML_WAYPOINTS_DTD			(const xmlChar *)"../waypoints.dtd"
#define PNXML_SOUNDS_DTD			(const xmlChar *)"../sounds.dtd"

#endif /* !_PNXML_H_ */
