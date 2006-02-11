/*
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
/********************************************************************
	created:	2005/02/16
	created:	16:2:2005   13:31
	filename: 	d:\pavillonnoir\svn\__dev\pavillonnoir\__src\pncommon\pns_format.h
	file path:	d:\pavillonnoir\svn\__dev\pavillonnoir\__src\pncommon
	file base:	pns_format
	file ext:	h
	author:		Thomas Mortagne
	
	purpose:	
*********************************************************************/

#ifndef _PNS_FORMAT_H_
# define _PNS_FORMAT_H_

#include "pnbasetypes.h"
#include "pnmath.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

#define PNS_EXT			"pns"

#define	PNS_MAGIC		"PNS0001"
#define	PNS_MAGIC_SIZE	8

typedef	struct			pnsHeader_s
{
  pnchar				magic[PNS_MAGIC_SIZE];
  pnuint				version;

  pnuint				nbBones;

  //-> list of pnsBone_t
}						pnsHeader_t;

typedef struct			pnsBone_s
{
  pnuint				id;
  pnchar				name[32];

  pnint					parent;

  pnmatrix4f			m_relative;
}						pnsBone_t;

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNS_FORMAT_H_*/
