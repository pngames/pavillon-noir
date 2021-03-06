/*
* PNGLGoup.hpp
* 
* Description :
* PNGLGoup declaration
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

#ifndef _PNGLGROUP_HPP_
# define _PNGLGROUP_HPP_

#include <fx.h>
#include <fx3d.h>

#include "pndefs.h"

#include "PNEDSkyBox.hpp"

#include "PNConfigurableObject.hpp"

#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

class PNPropertiesPanel;
class PNGLShape;
class PNEditor;

class					PNGLGroup : public FXGLGroup, public PNConfigurableObject
{
  FXDECLARE(PNGLGroup);

  //////////////////////////////////////////////////////////////////////////

public:

  typedef enum
  {
	VIEW_NONE			= 0x000000,
	VIEW_GROUND			= 0x000001,
	VIEW_STATIC			= 0x000001 << 1,
	VIEW_DYNAMIC		= 0x000001 << 2,
	VIEW_SKYBOX			= 0x000001 << 3,

	VIEW_ALL			= VIEW_GROUND | VIEW_STATIC | VIEW_DYNAMIC | VIEW_SKYBOX,
  }						viewOption;

  //////////////////////////////////////////////////////////////////////////
private:

  pnuint				_view;

  pnfloat				_mpp;

  PNEDSkybox			_skybox;
  FXGLGroup				_groundGroup;	// Ground type objects
  FXGLGroup	  			_staticGroup;	// Static type objects
  FXGLGroup				_dynGroup;		// Dynamic type objects

  void					_updateView();
private:
  PNPropertiesPanel*	_grid;
  PNEditor*				_editor;

  //////////////////////////////////////////////////////////////////////////
  
public:
  PNGLGroup();
  ~PNGLGroup();

  void					clear();

  pnbool				contains(viewOption view);

  void					setOptionView(pnuint view);
  pnuint				getOptionView();

  void					enableOptionView(viewOption view, pnbool enable = true);
  void					addOptionView(viewOption view);
  void					deleteOptionView(viewOption view);

  //////////////////////////////////////////////////////////////////////////
  
  /// Append child object
  void					append(FXGLObject* obj);
  /// Append child group
  void					append(FXGLGroup* group);
  /// Remove child object
  void					remove(FXGLObject* obj);

  //////////////////////////////////////////////////////////////////////////
  
  void					init(PNEditor* editor, PNPropertiesPanel* panel);

  //////////////////////////////////////////////////////////////////////////

  const std::string&	getDTD() const;
  const std::string&	getDTDName() const;
  const std::string&	getRootNodeName() const;

private:
  pnint					_unserializeSkyBox(xmlNode* node);
  pnint					_unserializeEntity(xmlNode* node);
  pnint					_unserializeNode(xmlNode* node);

public:
  pnint					unserializeFromXML(xmlNode* node);
  pnint					serializeInXML(xmlNode* root, pnbool isroot = false);

  // ConfigurableObject /////////////////////////////////////////////////////

  std::string		  		_label;

protected:
  typedef std::vector<PNConfigurableParameter*> ParametersVector;
  ParametersVector			_params;
public:
  void						update(PNConfigurableParameter* p) { }
  int						getNbParameters() { return _params.size(); }
  PNConfigurableParameter*	getParameter(int idx) { return _params[idx]; }

  const std::string&		getName() { return _label; }
  const std::string&		getLabel() { return _label; }

  //bool						modified() { return _modified; }
  //void						setModified() { _modified = true; }
  //void						setUnmodified() { _modified = false; }
};

//////////////////////////////////////////////////////////////////////////
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNGLGROUP_HPP_*/
