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

#include "Solid.h"

namespace opal
{
	Solid::Solid()
	{
		// "mData" is initialized in its own constructor.
		setCollisionEventHandler(NULL);
		setUserData(NULL);
	}

	Solid::~Solid()
	{
		mForceList.clear();
	}

	void Solid::internal_destroy()
	{
		delete this;
	}

	const SolidData& Solid::getData()const
	{
		return mData;
	}

	void Solid::setName(const std::string& name)
	{
		mData.name = name;
	}

	const std::string& Solid::getName()const
	{
		return mData.name;
	}

	bool Solid::isEnabled()const
	{
		return mData.enabled;
	}

	void Solid::setEnabled(bool e)
	{
		mData.enabled = e;
	}

	bool Solid::isStatic()const
	{
		return mData.isStatic;
	}

	void Solid::setSleepiness(real s)
	{
		assert(s >= 0.0 && s <= 1.0);
		mData.sleepiness = s;
	}

	real Solid::getSleepiness()const
	{
		return mData.sleepiness;
	}

	void Solid::setLinearDamping(real ld)
	{
		assert(ld >= 0.0);
		mData.linearDamping = ld;
	}

	real Solid::getLinearDamping()const
	{
		return mData.linearDamping;
	}

	void Solid::setAngularDamping(real ad)
	{
		assert(ad >= 0.0);
		mData.angularDamping = ad;
	}

	real Solid::getAngularDamping()const
	{
		return mData.angularDamping;
	}

	void Solid::setUserData(void* data)
	{
		mUserData = data;
	}

	void* Solid::getUserData()
	{
		return mUserData;
	}

	void Solid::setTransform(const Matrix44r& t)
	{	
		mData.transform = t;
		internal_updateEngineTransform();
	}

	const Matrix44r& Solid::getTransform()const
	{
		return mData.transform;
	}

	void Solid::setPosition(real x, real y, real z)
	{
		mData.transform.setPosition(x, y, z);
		internal_updateEngineTransform();
	}

	void Solid::setPosition(const Point3r & p)
	{
		setPosition(p[0], p[1], p[2]);
	}

	Point3r Solid::getPosition()const
	{
		return mData.transform.getPosition();
	}

	Vec3r Solid::getEulerXYZ()const
	{
		return mData.transform.getEulerXYZ();
	}

	Quaternion Solid::getQuaternion()const
	{
		return mData.transform.getQuaternion();
	}

	//void Solid::addPlane(const Point3r& point, const Vec3r& normal, const Material& m)
	//{
	//	Point3r origin(0, 0, 0);
	//	Vec3r n = normal;
	//	n.normalize();
	//	Vec3r v = point - origin;
	//
	//	real angle = 0;
	//	if (0 != v.length())
	//	{
	//		v.normalize();
	//		angle = acos(dot(n,v)); // note: this only works when the two vectors are normalized
	//	}
	//
	//	real length = distance(point, origin);
	//	real D = length * cos(angle);
	//	real abcd[4] = {n[0], n[1], n[2], D};
	//	addPlane(abcd, m);
	//}

	void Solid::addForce(const Force& f)
	{
		if (mData.enabled && !mData.isStatic && 
			f.vec.lengthSquared() > globals::OPAL_EPSILON )
		{
			mForceList.push_back(f);
		}
	}

	void Solid::internal_applyForces(real stepSize)
	{
		if (mData.isStatic)
		{
			return;
		}

		// If there are Forces to apply and the Solid is asleep, wake it up.
		if(!mForceList.empty() && isSleeping())
		{
			setSleeping(false);
		}

		std::vector<Force>::iterator forceIter;
		for (forceIter = mForceList.begin(); forceIter != mForceList.end();)
		{
			if (true == (*forceIter).singleStep)
			{
				(*forceIter).duration = stepSize;
			}
			else if ((*forceIter).duration < stepSize)
			{
				// Scale the size of the force/torque.
				(*forceIter).vec *= ((*forceIter).duration / stepSize);
			}

			// Apply the actual force/torque.
			applyForce(*forceIter);

			// The following is ok for all cases (even when duration is 
			// < mStepSize).
			(*forceIter).duration -= stepSize;

			if ((*forceIter).duration <= 0)
			{
				// Delete this force.
				(*forceIter) = mForceList.back();
				mForceList.pop_back();
			}
			else
			{
				++forceIter;
			}
		}
	}

	void Solid::setCollisionEventHandler(CollisionEventHandler* eventHandler)
	{
		mCollisionEventHandler = eventHandler;
	}

	CollisionEventHandler* Solid::getCollisionEventHandler()const
	{
		return mCollisionEventHandler;
	}

	void Solid::internal_updateSleeping()
	{
		mData.sleeping = isSleeping();
	}

	//// TODO: Quickly spinning solids should be set as fast rotating solids to 
	//// improve simulation accuracy.
	//void Solid::setFastRotation(bool fast)
	//{
	//}

	//bool Solid::getFastRotation()const
	//{
	//	return false;
	//}

	//void Solid::setFastRotationAxis(Vec3r axis)
	//{
	//}
}
