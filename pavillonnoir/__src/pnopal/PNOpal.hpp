/*
 * PNOpal.hpp
 * 
 * Description :
 * PNOpal declaration
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

#ifndef _PNOPAL_HPP_
# define _PNOPAL_HPP_

#include <opal/opal.h>

#include "pndefs.h"
#include "pnmath.h"
#include "pnevent.h"

#include "PNPhysicsInterface.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef std::list<PN3DObject *> PN3DObjList;

class				PNOpal : public PNPhysicsInterface
{
private:
  opal::Simulator*	_sim;

  /* FIXME : previously deprecated */
  PN3DObjList		_list3DObj;

public:
  PNOpal();
  ~PNOpal();

  void				init();
  void				setPause(bool state);
  void				addForceToObj(pnuint nb, pnfloat x, pnfloat y, pnfloat z, pnfloat duration);

  //////////////////////////////////////////////////////////////////////////

  void				createSimulation();
  void				destroySimulation();
  void*				getSimulation();

  //////////////////////////////////////////////////////////////////////////

  PNPhysicalObject*	createPhysicalObjectBox(PN3DObject* object, bool isStatic);
  void				destroyPhysicalObject(PNPhysicalObject* physicalObject);
  void				destroyAllPhysicalObjects();
  void				setAllPhysicalObjectsStatic(bool state);

  //////////////////////////////////////////////////////////////////////////

  pnfloat			getElapsedTime();
  void				frameStarted(pnEventType type, PNObject* source, PNEventData* data);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNOPAL_HPP_*/
