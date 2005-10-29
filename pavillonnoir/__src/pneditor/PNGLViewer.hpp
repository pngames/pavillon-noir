/*
 * PNGLViewer.hpp
 * 
 * Description :
 * PNGLViewer declaration
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


#ifndef _PNGLVIEWER_HPP_
# define _PNGLVIEWER_HPP_

/////////////////////////////////////

#include <fx.h>
#include <fx3d.h>

/////////////////////////////////////

#include "PNEditor.hpp"
#include "PNGLContext.hpp"

/////////////////////////////////////

/*
 *	This class extends FXGLViewer to allow us to catch some events and add features.
 */

namespace PN
{

  //////////////////////////////////////////////////////////////////////////
  
  namespace EDITOR
  {

	//////////////////////////////////////////////////////////////////////////
	
	class PNGLViewer : public FXGLViewer, public PNGLContext
	{
  
	  FXDECLARE(PNGLViewer);

	  FXComposite*	_parent;
	  PNEditor*		_ed;

	protected:
	  PNGLViewer() {}
	  ~PNGLViewer() {}

	public:

	  /// Construct GL viewer widget
	  PNGLViewer(FXComposite* p,FXGLVisual *vis,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

	  /// Construct GL viewer widget sharing display list with another GL viewer
	  PNGLViewer(FXComposite* p,FXGLVisual *vis,FXGLViewer* sharegroup,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=0,FXint x=0,FXint y=0,FXint w=0,FXint h=0);

	  /// Create all of the server-side resources for this window
	  virtual void create();

	  long onLeftBtnRelease(FXObject* obj,FXSelector sel,void* ptr);
	  long onKeyPress(FXObject* obj,FXSelector sel,void* ptr);

	  void	makeViewerCurrent();
	  void	makeViewerNonCurrent();
	};

	//////////////////////////////////////////////////////////////////////////
	
  };

  //////////////////////////////////////////////////////////////////////////
  
};


#endif /* _PNGLVIEWER_HPP_ */
