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

#ifndef OPAL_INCLINE_SENSOR_DATA_H
#define OPAL_INCLINE_SENSOR_DATA_H

#include "Defines.h"
#include "SensorData.h"

namespace opal
{
	/// A data structure describing an InclineSensor.
	class InclineSensorData : public SensorData
	{
	public:
		OPAL_DECL InclineSensorData()
		: SensorData()
		{
			mType = INCLINE_SENSOR;
			axis = defaults::sensor::incline::axis;
		}

		/// Copy constructor.
		OPAL_DECL InclineSensorData(const InclineSensorData& data)
		{
			(*this) = data;
		}

		OPAL_DECL virtual ~InclineSensorData()
		{
		}

		/// Makes a deep copy.
		OPAL_DECL virtual void OPAL_CALL operator=(
			const InclineSensorData& data)
		{
			mType = data.mType;
			enabled = data.enabled;
			name = data.name;
			solid = data.solid;
			internal_solidIndex = data.internal_solidIndex;
			solidBlueprintRefName = data.solidBlueprintRefName;
			transform = data.transform;
			axis = data.axis;
		}

		/// The local rotation axis around which the angle of rotation will 
		/// be measured.
		Vec3r axis;

	protected:

	private:
	};
}

#endif
