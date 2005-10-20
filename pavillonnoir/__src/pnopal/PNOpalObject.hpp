/*
 * PNOpalObject.hpp
 * 
 * Description :
 * PNOpalObject
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

#ifndef _PNOPALOBJECT_HPP_
# define _PNOPALOBJECT_HPP_

#include <libxml/xmlreader.h>
#include <opal/opal.h>

#include "pndefs.h"
#include "pnmath.h"

#include "PNPoint.hpp"
#include "PNQuatf.hpp"
#include "PNPhysicalObject.hpp"

namespace PN {
  class PNOpalObject : public PNPhysicalObject
  {
  private:
	PNPoint				_coord;
	PNQuatf				_orient;
	opal::Solid*		_solid;
	opal::Simulator*	_sim;

  public:
	PNOpalObject(opal::Simulator* sim);
	~PNOpalObject();

	void				update(pnuint elapsed_time);
	void				render();

	//////////////////////////////////////////////////////////////////////////
	
  	const PNPoint&		getCoord();
	const PNQuatf&		getOrient();
	opal::Solid*		getOpalSolid();

	//////////////////////////////////////////////////////////////////////////

	void				setStatic(bool state);
	void				setCoord(const PNPoint& coord);
	void				setCoord(pnfloat x, pnfloat y, pnfloat z);
	void				setOrient(const PNQuatf& orient);
	void				setOrient(pnfloat x, pnfloat y, pnfloat z, pnfloat w);

	//////////////////////////////////////////////////////////////////////////

	void				setShape(const PNPoint& min, const PNPoint& max, physicalmaterial material);

	//////////////////////////////////////////////////////////////////////////
	
	void				addForce(pnfloat x, pnfloat y, pnfloat z, pnfloat duration);

	//////////////////////////////////////////////////////////////////////////

	pnint				unserializeFromXML(xmlNode* node);
  };
}

#endif /*_PNOPALOBJECT_HPP_*/
