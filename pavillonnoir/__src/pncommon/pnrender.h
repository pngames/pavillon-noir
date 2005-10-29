/*
 * pnrender.h
 * 
 * Description :
 * Meta-include for rendering management
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

#ifndef _PNRENDER_H_
# define _PNRENDER_H_

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef enum
{
  PN_TRIANGLES,			/// Draw triangles (see opengl definitions)
  PN_TRIANGLE_STRIP,	/// Draw triangles strip (see opengl definitions)
  PN_TRIANGLE_FAN,		/// Draw triangles fan (see opengl definitions)
  PN_POINTS,			/// Draw points
  PN_LINES,				/// Draw lines (see opengl definitions)
  PN_LINE_STRIP,		/// Draw lines strop (see opengl definitions)

  PN_T2F_N3F_V3F,		/// Interleaved buffer based on (in float) : 2 text coords, 3 normals coords ans 3 vertex coords
  PN_T2F_C4F_N3F_V3F	/// Interleaved buffer based on (in float) : 2 text coords, 4 colors values, 3 normals coords ans 3 vertex coords
} pnrenderflag;

//////////////////////////////////////////////////////////////////////////
}

#include "PNRenderMaterial.hpp"
#include "PNRendererObject.hpp"
#include "PNRendererInterface.hpp"

#endif /*_PNRENDER_H_*/
