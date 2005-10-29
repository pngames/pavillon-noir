/*
 * pnt_format.h
 * 
 * Description :
 * Material files format
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

#ifndef _PNT_FORMAT_H_
# define _PNT_FORMAT_H_

#include "pndefs.h"
#include "pnmath.h"

#define PNT_EXT			"pnt"

#define	PNT_MAGIC		"PNT0001"
#define	PNT_MAGIC_SIZE	8

typedef	struct	pntHeader_s
{
  PN::pnchar	magic[PNT_MAGIC_SIZE];
  PN::pnuint	version;

  PN::pnpoint4f	ambient;
  PN::pnpoint4f	diffuse;
  PN::pnpoint4f	emissive;
  PN::pnpoint4f	specular;

  PN::pnfloat	opacity;
  PN::pnfloat	glossiness;

  PN::pnuint	nbMap;
  //-> list of pntMap_t
}				pntHeader_t;

typedef struct	pntMap_s
{
  PN::pnuint	lenght;
  //-> list of pnchar
}				pntMap_t;

#endif /*_PNT_FORMAT_H_*/
