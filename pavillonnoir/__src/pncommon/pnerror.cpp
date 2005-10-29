/*
 * pnerror.cpp
 * 
 * Description :
 * Error management utiliries definitions
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

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#ifdef WIN32
# include <Windows.h>
# define vsnprintf		_vsnprintf
#endif

#include "pndefs.h"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

void
pnerror(pnloglevel lvl, const pnchar* format, ...)
{
  assert(lvl >= 0 && lvl < PN_LOGLVL_NB && "level out of range");

  va_list	args;
  pnchar	buffer[1024];

  va_start(args, format);
  vsnprintf(buffer, 1023, format, args);
  va_end(args);

  switch (lvl)
  {
  case PN_LOGLVL_INFO:
	fprintf(stdout, "[Info: %s]\n", buffer);
	break ;
#ifdef DEBUG
  case PN_LOGLVL_DEBUG:
	fprintf(stdout, "[Info: %s]\n", buffer);
	break ;
#endif
  case PN_LOGLVL_TODO:
	fprintf(stderr, "[Todo: %s]\n", buffer);
	break ;
  case PN_LOGLVL_WARNING:
	fprintf(stderr, "[Warning: %s]\n", buffer);
	break ;
#ifndef WIN32
  case PN_LOGLVL_ERROR:
	fprintf(stderr, "[Error: %s]\n", buffer);
	break ;
  case PN_LOGLVL_CRITICAL:
	fprintf(stderr, "[Critical: %s]\n", buffer);
	break ;
#else
  case PN_LOGLVL_ERROR:
	MessageBox(NULL, (LPCTSTR)buffer, "Error", MB_OK | MB_ICONERROR);
	break ;
  case PN_LOGLVL_CRITICAL:
	MessageBox(NULL, (LPCTSTR)buffer, "Critical", MB_OK | MB_ICONSTOP);
	break ;
#endif
	default:
		;
  }
}

void
pnperror(pnloglevel lvl, const pnchar* format, ...)
{
#ifdef WIN32
  va_list		ap;
  DWORD			err;

  va_start(ap, format);

  LPVOID		lpMsgBuf;

  if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	NULL, (err = GetLastError()), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	(LPTSTR)&lpMsgBuf, 0,&ap))
  {
	va_end(ap);
	return ;
  }
  va_end(ap);

  pnerror(lvl, (const pnchar*)lpMsgBuf);

  LocalFree(lpMsgBuf);
#else
  perror(format);
#endif
}
//////////////////////////////////////////////////////////////////////////

const pnchar* tabErrors[]=
{
  "No error",
  "Undefined error",
  "Not implemented",

  "File not found",
  "Not a file",
  "Directory not found",
  "Not a directory",

  "Invalid file type",

  "Plugin corrupted",

  "Model loading failed",
  "Skeleton loading failed",

  "Failed to allocate parser context",
  "Failed to parse"
};

const pnchar*
pnGetErrorString(pnint code)
{
  assert(code >= 0 && code < PNEC_NB && "code out of range");

  return tabErrors[code];
}

//////////////////////////////////////////////////////////////////////////
};
