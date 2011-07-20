/*
 * pna_format.h
 * 
 * Description :
 * Animation files format
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

#ifndef	_PNA_FORMAT_H_
# define _PNA_FORMAT_H_

#include "pndefs.h"
#include "pnmath.h"

#define PNA_EXT			"pna"

#define	PNA_MAGIC		"PNA0001"
#define	PNA_MAGIC_SIZE	8

typedef	struct	pnaHeader_s
{
  PN::pnchar	magic[PNA_MAGIC_SIZE];
  PN::pnuint	version;

  PN::pnchar	name[32];

  PN::pnuint	frameRate;
  PN::pnuint	totalTime;

  PN::pnuint	nbBones;
  //-> list of pnaBones_t;
}				pnaHeader_t;

typedef struct	pnaBone_s
{
  PN::pnuint	id;

  PN::pnuint	nbRot;
  PN::pnuint	nbPos;

  //-> list of pnaKeyRot_t;
  //-> list of pnaKeyPos_t;
}				pnaBone_t;

typedef struct	pnaKeyRot_s
{
  PN::pnuint	time;
  PN::pnquatf	rot;
}				pnaKeyRot_t;

typedef struct	pnaKeyPos_s
{
  PN::pnuint	time;
  PN::pnpoint3f	pos;
}				pnaKeyPos_t;

#endif /*_PNA_FORMAT_H_*/
