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

#ifndef OPAL_POST_STEP_EVENT_HANDLER_H
#define OPAL_POST_STEP_EVENT_HANDLER_H

#include "Defines.h"
#include "EventHandler.h"

namespace opal
{
	/// A listener that gets notified when a simulation step has finished.
	class PostStepEventHandler : public EventHandler
	{
	public:
		OPAL_DECL PostStepEventHandler()
		{}

		OPAL_DECL virtual ~PostStepEventHandler()
		{}

		/// Called once for each pending CollisionEvent.  This is always 
		/// called at the end of a time step, so CollisionEvents always 
		/// get handled right away.
		OPAL_DECL virtual void OPAL_CALL handlePostStepEvent() = 0;

	protected:

	private:

	};
}

#endif

