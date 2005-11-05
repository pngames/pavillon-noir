/*
 * pndefs.h
 * 
 * Description :
 * Defines and types used in all pncommon interfaces
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

#ifndef _PNDEFS_H_
# define _PNDEFS_H_

/********************************  Definitions ********************************/

// Truth values
#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif
#ifndef MAYBE
# define MAYBE 2
#endif
#ifndef NULL
# define NULL 0
#endif

// Path separator
#ifdef WIN32
# define PATHSEP '\\'
# define PATHSEPSTRING "\\"
# define PATHLISTSEP ';'
# define PATHLISTSEPSTRING ";"
# define ISPATHSEP(c) ((c)=='/' || (c)=='\\')
#else
# define PATHSEP '/'
# define PATHSEPSTRING "/"
# define PATHLISTSEP ':'
# define PATHLISTSEPSTRING ":"
# define ISPATHSEP(c) ((c)=='/')
#endif

// End Of Line
#ifdef WIN32
# define EOLSTRING "\r\n"
#else
# define EOLSTRING "\n"
#endif

// For Windows
#ifdef _DEBUG
# ifndef DEBUG
#  define DEBUG
# endif
#endif
#ifdef _NDEBUG
# ifndef NDEBUG
#  define NDEBUG
# endif
#endif


// Shared library support
#ifdef WIN32
# pragma warning( disable: 4251 4275 )
# define PNEXPORT	__declspec(dllexport)
# define PNIMPORT	__declspec(dllimport)
#else
# define PNEXPORT	
# define PNIMPORT	
#endif

#define PNPLUGEXPORT extern "C" PNEXPORT

#ifdef PNCOMMON_EXPORTS
# define PNAPI PNEXPORT
#else
# define PNAPI PNIMPORT
#endif

// Callback
#ifdef WIN32
# ifndef CALLBACK
#  define CALLBACK __stdcall
# endif
#endif


// Checking printf and scanf format strings
#if defined(_CC_GNU_) || defined(__GNUG__) || defined(__GNUC__)
# define PN_PRINTF(fmt,arg) __attribute__((format(printf,fmt,arg)))
# define PN_SCANF(fmt,arg)  __attribute__((format(scanf,fmt,arg)))
#else
# define PN_PRINTF(fmt,arg)
# define PN_SCANF(fmt,arg)
#endif

// Raw event type
#ifndef WIN32
union _XEvent;
#else
struct tagMSG;
#endif

#define PNFORMAT_STR_LEN		32

namespace PN {

	/*********************************  Typedefs **********************************/

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


	// Handle to something in server
#ifndef WIN32
	typedef unsigned long			pnid;
#else
	typedef void*					pnid;
#endif

	// Time since January 1, 1970 (UTC)
	typedef long					pntime;

	/**********************************  Macros ***********************************/

	/// Clamp value x to range [lo..hi]
#define PNCLAMP(lo,x,hi) ((x)<(lo)?(lo):((x)>(hi)?(hi):(x)))

	/// Swap a pair of numbers
#define PNSWAP(a,b,t) ((t)=(a),(a)=(b),(b)=(t))

	/// Linear interpolation between a and b, where 0<=f<=1
#define PNLERP(a,b,f) ((a)+((b)-(a))*(f))

	/// Offset of member in a structure
#define PNSTRUCTOFFSET(str,member) (((char*)(&(((str*)0)->member)))-((char*)0))

	/// Number of elements in a static array
#define PNARRAYNUMBER(array) (sizeof(array)/sizeof(array[0]))

	/// Container class of a member class
#define PNCONTAINER(ptr,str,mem) ((str*)(((char*)(ptr))-STRUCTOFFSET(str,mem)))

	/// Make int out of two shorts
#define PNMKUINT(l,h) ((((pnuint)(l))&0xffff) | (((pnuint)(h))<<16))

	/// Reverse bits in byte
#define PNBITREVERSE(b) (((b&0x01)<<7)|((b&0x02)<<5)|((b&0x04)<<3)|((b&0x08)<<1)|((b&0x10)>>1)|((b&0x20)>>3)|((b&0x40)>>5)|((b&0x80)>>7))
}

#ifdef WIN32
# define chdir(path)		_chdir(path)
# define getcwd(buf, nb)	_getcwd(buf, nb)
#endif

//////////////////////////////////////////////////////////////////////////

#include "pnerror.h"

#endif
