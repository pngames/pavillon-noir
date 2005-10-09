/*
 * PN3DCamera.hpp
 * 
 * Description :
 * PN3DCamera declaration
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

#ifndef _PN3DCAMERA_HPP_
# define _PN3DCAMERA_HPP_

#include <list>

#include "pnevent.h"

#include "PN3DObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef std::list<PN3DObject *> PN3DObjList;

/// Camera implementation
class PNAPI					PN3DCamera : public PN3DObject
{
public:
  /// Default constructor for PN3DCamera.
  PN3DCamera();
  /// Construct camera targeting 3d object
  PN3DCamera(PN3DObject* object);
  /// Destructor for PN3DObject.
  ~PN3DCamera();

  //////////////////////////////////////////////////////////////////////////

public:
  /// Displacement and view mode
  typedef enum
  {
	MMODE_SUBJECTIV			= PN3DObject::NB_MMODE,	/// Camera view integrated in the target
	NB_MMODE										/// number of moving modes in 3DObject
  }							pnmovingmode;

  //////////////////////////////////////////////////////////////////////////

  /// Return unique rendering camera
  static PN3DCamera*		getRenderCam();

  /// Return list of 3d objects in camera frustrum
  const PN3DObjList&		getListObj();
protected:
  PN3DObjList				_list3DObj;
  pnbool					_is3DObjVisible(PN3DObject* obj);
  void					  	_updateFrustrum(pnEventType type, PNObject* source, PNEventData* ed);

  void						_onMPStarted(pnEventType type, PNObject* source, PNEventData* ed);
  void						_onMPEnded(pnEventType type, PNObject* source, PNEventData* ed);

  //////////////////////////////////////////////////////////////////////////

  pnfloat					_viewFar;
  pnfloat					_viewNear;
  pnfloat					_viewFov;
  pnfloat					_viewRadFov;

  //////////////////////////////////////////////////////////////////////////

  /// Unique rendering camera
  static PN3DCamera*		_playerCamera;
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PN3DGROUND_HPP_*/
