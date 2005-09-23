/*
 * pnerror.h
 * 
 * Description :
 * Error management utiliries declarations
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

#ifndef _PNERROR_H_
# define _PNERROR_H_

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef enum
{
  PN_LOGLVL_INFO,			/// Just information printed for log
  PN_LOGLVL_DEBUG,			/// Printed in DEBUG mode for warn user
  PN_LOGLVL_TODO,			/// Printed for warn user
  PN_LOGLVL_WARNING,		/// Represent a warning
  PN_LOGLVL_ERROR,			/// En error
  PN_LOGLVL_CRITICAL,		/// A critical error (witch crash system)
  PN_LOGLVL_NB				/// Number of levels
} pnloglevel;

typedef enum
{
  PNEC_SUCCES,
  PNEC_ERROR,
  PNEC_NOT_IMPLEMENTED,

  PNEC_FILE_NOT_FOUND,
  PNEC_NOT_A_FILE,
  PNEC_DIRECTORY_NOT_FOUND,
  PNEC_NOT_A_DIRECTORY,

  PNEC_FILETYPE_INVALID,

  PNEC_PLUGIN_INVALID,

  PNEC_LOADING_MODEL,
  PNEC_LOADING_SKELETON,

  PNEC_ALLOC_PARSER_CONTEXT,
  PNEC_FAILED_TO_PARSE,

  PNEC_NOT_INITIALIZED,

  PNEC_NB
} pnerrorcode;


extern PNAPI void			pnerror(pnloglevel lvl, const pnchar* format, ...);
extern PNAPI void			pnperror(pnloglevel lvl, const pnchar* title, ...);

extern PNAPI const pnchar*	pnGetErrorString(pnint code);

//////////////////////////////////////////////////////////////////////////
};

#ifdef DEBUG
# define PNDEBUG_TODO(msg)	PN::pnerror(PN_LOGLVL_TODO, "file %s at line %i", __FILE__, __LINE__)
# define PNDEBUG_STEP		PN::pnerror(PN_LOGLVL_INFO, "file %s at line %i", __FILE__, __LINE__)
#else
# define PNDEBUG_TODO(msg)
# define PNDEBUG_STEP
#endif

#endif /*_PNERROR_H_*/
