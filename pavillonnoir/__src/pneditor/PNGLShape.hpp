/*
 * PNGLShape.hpp
 * 
 * Description :
 * PNGLShape declaration
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


#ifndef _PNGLSHAPE_HPP_
# define _PNGLSHAPE_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>
#include <fx.h>
#include <fx3d.h>

#include "pnevent.h"
#include "pnproperties.h"

typedef	enum
{
  PN_GROUND = 0,
  PN_STATIC,
  PN_DYNAMIC,
  NB_ENVTYPES
}		PNEnvType;

namespace PN
{
  class PN3DObject;
  class PNPropertiesPanel;
//////////////////////////////////////////////////////////////////////////
  namespace EDITOR
  {
	class PNEditor;
	class PNGLShape : public FXGLShape, public PNConfigurableObject
    {
	  FXDECLARE_ABSTRACT(PNGLShape);

	  PNEditor*			  		_ed;
	  PN3DObject*				_obj;
	  boost::filesystem::path	_temppath;
	  int				  		_id;
	  PNEnvType			  		_envType;
	  bool				  		_canDrag;
	  std::string		  		_label;
	  std::string		  		_classStr;
	  scriptMap			  		_scripts;
	  PNPropertiesPanel*  		_grid;
	protected:
	  PNGLShape();
    public:
      FXfloat			  		radius;   // Radius of sphere
      FXint				  		slices;   // Longitudinal subdivision
      FXint				  		stacks;   // Latitudinal subdivision

	  PNGLShape(PN3DObject* obj, PNPropertiesPanel* grid, PNEditor* ed, PNEnvType envType, std::string classStr = "PN3DObject", int id = 0, std::string label = "No label");

	  virtual ~PNGLShape();

	  PN3DObject*		  getObj() {return _obj;}
	  int				  getId() {return _id;}
	  PNEditor*			  getEd() {return _ed;}
	  PNEnvType			  getEnvType() {return _envType;}
	  scriptMap&		  getScripts() {return _scripts;}
	  std::string&		  getClassStr() {return _classStr;}
	  void				  setDragable() {_canDrag = TRUE;}
	  void				  setUndragable() {_canDrag = FALSE;}
	  void				  setPosNull();
	  void				  setPosFromObj();
	  void				  setMinMax();
	  void				  buildParams();

	  FXbool			  drag(FXGLViewer* viewer,FXint fx,FXint fy,FXint tx,FXint ty);
      virtual void		  drawshape(FXGLViewer* viewer);

	  void				  setInObjView();
	  void				  addScript(pnEventType type, const char* name);
	  void				  selfRemove();
	  void				  makeViewerCurrent();
	  void				  makeViewerNonCurrent();

	  long				  onSelected(FXObject*,FXSelector,void*);
	  long				  onLeftBtnRelease(FXObject*,FXSelector,void*);
	  long				  onDNDDrop(FXObject* obj,FXSelector sel,void* v);

	  //////////////////////////////////////////////////////////////////////////
	  // ConfigurableObject

	protected:
	  typedef std::vector<PNConfigurableParameter*> ParametersVector;
	  ParametersVector			_params;
	public:
	  void						update(PNConfigurableParameter* p);
	  void						updateOrient();
	  int						getNbParameters();
	  PNConfigurableParameter*	getParameter(int idx);

	  const std::string&		getLabel() {return _label;}
	};
  };
//////////////////////////////////////////////////////////////////////////
};

#endif /* _PNGLSHAPE_HPP_ */
