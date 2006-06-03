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

#include "pnevent.h"

#include "pnproperties.h"
#include "PNPhysicsInterface.hpp"
#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef std::list<PN3DObject *> PN3DObjList;

class PNOpalCommonEventHandler;
class PNOpalObject;

class						PNOpal : public PNPhysicsInterface
{
private:
  opal::Simulator*			_sim;
  bool						_break;
  pnfloat					_lastTicks;
  PNOpalCommonEventHandler* _eventHandler;
  std::string		  		_label;

public:
  PNOpal();
  ~PNOpal();

  //////////////////////////////////////////////////////////////////////////
  // PNPhysicalInterface

  void						init();
  void						setPause(bool state);

  void						createSimulation();
  void						destroySimulation();
  void*					 	getSimulation();

 //////////////////////////////////////////////////////////////////////////

  void						setAllPhysicalObjectsStatic(bool state);

  //////////////////////////////////////////////////////////////////////////
  // Events
  
  void*						getEventHandler();

private:
  void						_onFrame(pnEventType type, PNObject* source, PNEventData* data);
  void						_onMapLoad(pnEventType type, PNObject* source, PNEventData* data);
  void						_onMapLoaded(pnEventType type, PNObject* source, PNEventData* data);
  void						_onMapUnload(pnEventType type, PNObject* source, PNEventData* data);

  //////////////////////////////////////////////////////////////////////////
  // PNConfigurableObject & PNConfPanel

/*protected:
  typedef std::vector<PNConfigurableParameter*> ParametersVector;
  ParametersVector			_params;
public:

  void						update(PNConfigurableParameter* p) {}
  int						getNbParameters() { return _params.size(); }
  PNConfigurableParameter*	getParameter(int idx) { return _params[idx]; }

  void						setModified() {}
  void						setUnmodified() {}
  const std::string&	    getLabel() { return _label; }
*/

  //////////////////////////////////////////////////////////////////////////
  // Internal

protected:
  void						preComputeCharactersForces(PN3DObject* pnObject, PNOpalObject* physicalObject);
  pnfloat					getElapsedTime();
  void						opal2pn();
  void						pn2opal();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNOPAL_HPP_*/
