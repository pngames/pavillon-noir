/*
* PNGLSkyBox.hpp
* 
* Description :
* PNGLSkyBox declaration
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

#ifndef _PNGLSKYBOX_HPP_
# define _PNGLSKYBOX_HPP_

#include <GL/glew.h>

#include "PNSkyBox.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class				PNGLSkyBox : public PNSkyBox
{
private:
  static PNGLSkyBox*	_instance;

  PNGLSkyBox();
  ~PNGLSkyBox(void);
public:
  static PNGLSkyBox*	getInstance();

  pnbool				isEnabled();

  //////////////////////////////////////////////////////////////////////////

  /// Set the skyBox enabled or disabled
  void					setEnabled(pnbool enabled);

  /// Set the sky box properties
  void					set(PNRendererObject* skyBox);
  /// Set the sky box properties
  void					set(pnfloat* textCoords, PNRenderMaterial* skyBox);
  /// Set the sky box properties
  void					set(PNRenderMaterial* top, PNRenderMaterial* bottom, PNRenderMaterial* left, PNRenderMaterial* right, PNRenderMaterial* front, PNRenderMaterial* back);

  //////////////////////////////////////////////////////////////////////////
 
  void					render();

  //////////////////////////////////////////////////////////////////////////
private:
  pnbool				_enabled;

  PNRendererObject*		_skyObj;

  pnfloat*				_textCoords;
  PNRenderMaterial*		_skyBox;

  PNRenderMaterial*		_top;
  PNRenderMaterial*		_bottom;
  PNRenderMaterial*		_left;
  PNRenderMaterial*		_right;
  PNRenderMaterial*		_front;
  PNRenderMaterial*		_back;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* _PNGLSKYBOX_HPP_ */
