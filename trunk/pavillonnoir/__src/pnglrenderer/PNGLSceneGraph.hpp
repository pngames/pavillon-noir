/*
* PNGLSceneGraph.hpp
* 
* Description :
* PNGLSceneGraph declaration
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

#ifndef _PNGLSCENEGRAPH_HPP_
# define _PNGLSCENEGRAPH_HPP_

#include <GL/glew.h>

#include "PNGLRendererCamera.hpp"

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class		PNGLSceneGraph : public PNObject
{
  friend class PNGLRenderer;

  static PNGLSceneGraph*	_instance;

  PNGLSceneGraph();
  ~PNGLSceneGraph(void);
private:
  PNGLRendererCamera		_renderCam;

  pnuint                    _lastRenderTime;

  pnbool					_inGame;

  pnuint					_lastLoopDate;

  void						_onMPStarted(pnEventType type, PNObject* source, PNEventData* ed);
  void						_onMPEnded(pnEventType type, PNObject* source, PNEventData* ed);
public:
  static PNGLSceneGraph*	getInstance();

  void						resizeGLWindow(pnint width, pnint height);
  void						initFrame();
  PNGLRendererCamera&		getRenderCamera();

  pnuint					render(pnuint deltaTime);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* _PNGLSCENEGRAPH_HPP_ */
