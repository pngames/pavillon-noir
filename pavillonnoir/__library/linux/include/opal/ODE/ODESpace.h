/*************************************************************************
 *                                                                       *
 * Open Physics Abstraction Layer                                        *
 * Copyright (C) 2004-2005                                               *
 * Alan Fischer  alan.fischer@gmail.com                                  *
 * Andres Reinot  andres@reinot.com                                      *
 * Tyler Streeter  tylerstreeter@gmail.com                               *
 * All rights reserved.                                                  *
 * Web: opal.sourceforge.net                                             *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file license-LGPL.txt.                                          *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file license-BSD.txt.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * license-LGPL.txt and license-BSD.txt for more details.                *
 *                                                                       *
 *************************************************************************/

#ifndef OPAL_ODE_SPACE_H
#define OPAL_ODE_SPACE_H

#include <ode/ode.h>
#include "../Defines.h"
#include "../Space.h"

namespace opal
{
	/// The ODE implementation of the Space class.  
	class ODESpace : public Space
	{
	public:
		ODESpace();

		virtual ~ODESpace();

		virtual void OPAL_CALL setParentSpace(Space* parentSpace);

		/// Returns the ODE space ID.  
		virtual dSpaceID OPAL_CALL internal_getSpaceID()const;
		
	protected:
		/// The ODE space ID.  
		dSpaceID mSpaceID;

		/// The ODE space ID of this ODESpace's parent ODESpace.  
		dSpaceID mParentSpaceID;

	private:

	};
}

#endif

