/*
* pnbasetypes.h
* 
* Description :
* Meta-include for base types based on PNObject
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

#ifndef _PNBASETYPES_H_
# define _PNBASETYPES_H_

namespace PN {
//////////////////////////////////////////////////////////////////////////

  // Streamable types; these are fixed size!
typedef char					pnchar;
typedef unsigned char			pnuchar;
typedef bool					pnbool;
typedef unsigned short			pnushort;
typedef short					pnshort;
typedef unsigned int			pnuint;
typedef unsigned int			pnwchar;
typedef int						pnint;
typedef float					pnfloat;
typedef double					pndouble;
#if defined(_MSC_VER) || (defined(__BCPLUSPLUS__)&& __BORLANDC__ > 0x500) || defined(__WATCOM_INT64__)
# define PN_LONG
typedef unsigned __int64		pnulong;
typedef __int64					pnlong;
#elif defined(__GNUG__) || defined(__GNUC__) || defined(__SUNPRO_CC) || defined(__MWERKS__) || defined(__SC__)
# define PN_LONG
typedef unsigned long long int	pnulong;
typedef long long int			pnlong;
#endif

// Integral types large enough to hold value of a pointer
#if defined(_MSC_VER)&& defined(_WIN64)
typedef __int64					pnival;
typedef unsigned __int64		pnuval;
#else
typedef long					pnival;
typedef unsigned long			pnuval;
#endif

// Time since January 1, 1970 (UTC)
typedef long					pntime;

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNBASETYPES_H_*/
