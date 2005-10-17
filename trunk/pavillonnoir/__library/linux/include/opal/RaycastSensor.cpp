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

#include "RaycastSensor.h"
#include "Simulator.h"

namespace opal
{
	RaycastSensor::RaycastSensor(Simulator* s)
	{
		// "mData" is initialized in its own constructor.
		mSim = s;
	}

	RaycastSensor::~RaycastSensor()
	{
	}

	void RaycastSensor::init(const RaycastSensorData& data)
	{
		Sensor::init();
		mData = data;
	}

	const RaycastSensorData& RaycastSensor::getData()const
	{
		return mData;
	}

	const RaycastResult& RaycastSensor::fireRay()
	{
		return fireRay(mData.ray.getLength());
	}

	const RaycastResult& RaycastSensor::fireRay(real length)
	{
		if (mData.enabled)
		{
			Rayr ray = mData.ray;

			// If the Sensor is attached to a Solid, we need to transform 
			// the ray relative to that Solid's transform.
			if (mData.solid)
			{
				ray = mData.solid->getTransform() * ray;
			}

			// Use the Sensor's transform on the ray.
			ray = mData.transform * ray;

			// If this is attached to a Solid, the Simulator raycast function 
			// will automatically ignore intersections between the ray and 
			// that Solid.

			return mSim->internal_fireRay(ray, length, mData.solid, 
				mData.contactGroup);
		}
		else
		{
			static RaycastResult junkResult;
			return junkResult;
		}
	}

	void RaycastSensor::setEnabled(bool e)
	{
		//if (!mInitCalled)
		//{
		//	return;
		//}

		mData.enabled = e;
	}

	bool RaycastSensor::isEnabled()const
	{
		return mData.enabled;
	}

	void RaycastSensor::setRay(const Rayr& r)
	{
		mData.ray = r;
	}

	const Rayr& RaycastSensor::getRay()const
	{
		return mData.ray;
	}

	SensorType RaycastSensor::getType()const
	{
		return mData.getType();
	}

	void RaycastSensor::setTransform(const Matrix44r& t)
	{
		mData.transform = t;
	}

	const Matrix44r& RaycastSensor::getTransform()const
	{
		return mData.transform;
	}

	void RaycastSensor::setName(const std::string& name)
	{
		mData.name = name;
	}

	const std::string& RaycastSensor::getName()const
	{
		return mData.name;
	}

	void RaycastSensor::internal_update()
	{
		if (mData.enabled && mData.solid)
		{
			// Do nothing.
		}
	}

	bool RaycastSensor::internal_dependsOnSolid(Solid* s)
	{
		if (s == mData.solid)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
