/*
 * pnmath.h
 * 
 * Description :
 * Defines and types used for mathematics
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

#ifndef _PNMATH_H_
# define _PNMATH_H_

#include <math.h>

#ifndef PI
/// Pi
# define PI      			3.1415926535897932384626433832795028841971693993751058209749445923078164062862
#endif

/// Euler constant
#define EULER   			2.7182818284590452353602874713

/// Multiplier for degrees to radians
#define DTOR    			0.0174532925199432957692369077

/// Multiplier for radians to degrees
#define RTOD    			57.295779513082320876798154814

/*
** MACROS
*/

#ifndef DEGREE_TO_RADIAN
/// Convert degree to radian
# define DEGREE_TO_RADIAN(degree)	((degree) * DTOR)
#endif
#ifndef DEGREE_TO_RADIAN_F
/// Convert degree to radian
# define DEGREE_TO_RADIAN_F(degree)	((float)DEGREE_TO_RADIAN(degree))
#endif

#ifndef RADIAN_TO_DEGREE
/// Convert radian to degree
# define RADIAN_TO_DEGREE(radian)	((radian) * RTOD)
#endif
#ifndef RADIAN_TO_DEGREE_F
/// Convert radian to degree
# define RADIAN_TO_DEGREE_F(radian)	((float)RADIAN_TO_DEGREE(radian))
#endif

/// Epsilon
#define	PN_EPSILON	10E-5 /* 10E-6 */

/// Return largest number of a and b
#define PN_MAX(a,b)	(((a) > (b)) ? (a) : (b))
/// Return smallest number of a and b
#define PN_MIN(a,b)	(((a) < (b)) ? (a) : (b))

#ifndef ABS
/// Return absolute value
# define ABS(val)			(((val)>=0)?(val):-(val))
#endif

/// Square Number
#define SQNBR(val)			(val * val)

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef pnfloat				pnpoint2f[2];
typedef pnfloat				pnpoint3f[3];
typedef	pnfloat				pnpoint4f[4];
typedef pnint				pnpoint2i[2];
typedef pnint				pnpoint3i[3];
typedef	pnint				pnpoint4i[4];
typedef pnuint				pnpoint2ui[2];
typedef pnuint				pnpoint3ui[3];
typedef	pnuint				pnpoint4ui[4];

typedef pnpoint4f			pnquatf;

typedef pnfloat				pnmatrix3f[9];
typedef pnfloat				pnmatrix4f[16];

typedef pnfloat				pnsquare7f[7];

typedef struct				pnpoint2f_s
{
  pnfloat					x;
  pnfloat					y;
}							pnpoint2f_t;

typedef struct				pnpoint3f_s
{
  pnfloat					x;
  pnfloat					y;
  pnfloat					z;
}							pnpoint3f_t;

typedef struct				pncolor_s
{
  pnfloat					r;
  pnfloat					g;
  pnfloat					b;
  pnfloat					a;
}							pncolor_t;

const static pnpoint3f_t	DFLPOINT3F = {0.0f, 0.0f, 0.0f};
const static pnpoint2f_t	DFLPOINT2F = {0.0f, 0.0f};
const static pncolor_t		DFLCOLOR = {1.0f, 1.0f, 1.0f, 1.0f};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNMATH_H_*/
