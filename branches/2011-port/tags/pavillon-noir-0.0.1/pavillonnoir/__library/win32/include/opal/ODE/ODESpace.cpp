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

#include "ODESpace.h"

namespace opal
{
	ODESpace::ODESpace()
	: Space()
	{
		// Create the Space without adding it to another Space.
		mSpaceID = dSimpleSpaceCreate(0);
		mParentSpaceID = NULL;
	}

	ODESpace::~ODESpace()
	{
	}

	void ODESpace::setParentSpace(Space* parentSpace)
	{
		dSpaceID tempSpaceID = 
			((ODESpace*)parentSpace)->internal_getSpaceID();

		// First remove this Space from its current parent Space, if one 
		// exists.
		if (NULL != mParentSpaceID)
		{
			dSpaceRemove(mParentSpaceID, (dGeomID)mSpaceID);
		}

		// Now add this Space into the new Space.
		dSpaceAdd(tempSpaceID, (dGeomID)mSpaceID);

		mParentSpaceID = tempSpaceID;
	}

	dSpaceID ODESpace::internal_getSpaceID()const
	{
		return mSpaceID;
	}
}
