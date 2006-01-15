/*
* PNEDSkybox.hpp
* 
* Description :
* PNEDSkybox declaration
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


#ifndef _PNEDSKYBOX_HPP_
# define _PNEDSKYBOX_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>
#include <fx.h>
#include <fx3d.h>

#include "pnevent.h"
#include "pnproperties.h"

#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DObject;
class PNPropertiesPanel;

namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

class PNEditor;
class PN3DMaterial;

class						PNEDSkybox : public FXGLShape, public PNConfigurableObject
{
  FXDECLARE_ABSTRACT(PNEDSkybox);

  PNEditor*			  		_ed;
  bool				  		_canDrag;
  PNPropertiesPanel*  		_grid;

  //////////////////////////////////////////////////////////////////////////
  
  static const std::string	_label;

  bool						_enabled;

  PN3DMaterial*				_top;
  PN3DMaterial*				_bottom;
  PN3DMaterial*				_left;
  PN3DMaterial*				_right;
  PN3DMaterial*				_front;
  PN3DMaterial*				_back;
public:

  PNEDSkybox();
  ~PNEDSkybox();

  void						setContext(PNPropertiesPanel* grid, PNEditor* ed);

  PNEditor*					getEd() {return _ed;}
  void						buildParams();

  virtual void				drawshape(FXGLViewer* viewer);

  void						setInObjView();
  void						selfRemove();

  long						onSelected(FXObject*,FXSelector,void*);
  long						onLeftBtnRelease(FXObject*,FXSelector,void*);

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
  void						reset();

  const std::string&		getName() {return _label;}
  const std::string&		getLabel() {return _label;}

  //////////////////////////////////////////////////////////////////////////
public:
  const std::string&		getRootNodeName() const;

public:
  pnint						unserializeFromXML(xmlNode* node);
  pnint						serializeInXML(xmlNode* root, pnbool isroot = false);
};
};
//////////////////////////////////////////////////////////////////////////
};

#endif /* _PNEDSKYBOX_HPP_ */
