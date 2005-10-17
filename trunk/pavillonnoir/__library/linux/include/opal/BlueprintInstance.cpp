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

#include "BlueprintInstance.h"
#include "Solid.h"
#include "Joint.h"
#include "Motor.h"
#include "Sensor.h"

namespace opal
{
	BlueprintInstance::BlueprintInstance()
	{
	}

	BlueprintInstance::~BlueprintInstance()
	{
		mSolidMap.clear();
		mJointMap.clear();
		mMotorMap.clear();
		mSensorMap.clear();

		mSolidList.clear();
		mJointList.clear();
		mMotorList.clear();
		mSensorList.clear();
	}

	Solid* BlueprintInstance::getSolid(const std::string& name)const
	{
		std::map<std::string, Solid*>::const_iterator iter = 
			mSolidMap.find(name);
		if (mSolidMap.end() == iter)
		{
			return NULL;
		}
		else
		{
			return (*iter).second;
		}
	}

	Joint* BlueprintInstance::getJoint(const std::string& name)const
	{
		std::map<std::string, Joint*>::const_iterator iter = 
			mJointMap.find(name);
		if (mJointMap.end() == iter)
		{
			return NULL;
		}
		else
		{
			return (*iter).second;
		}
	}

	Motor* BlueprintInstance::getMotor(const std::string& name)const
	{
		std::map<std::string, Motor*>::const_iterator iter = 
			mMotorMap.find(name);
		if (mMotorMap.end() == iter)
		{
			return NULL;
		}
		else
		{
			return (*iter).second;
		}
	}

	Sensor* BlueprintInstance::getSensor(const std::string& name)const
	{
		std::map<std::string, Sensor*>::const_iterator iter = 
			mSensorMap.find(name);
		if (mSensorMap.end() == iter)
		{
			return NULL;
		}
		else
		{
			return (*iter).second;
		}
	}

	unsigned int BlueprintInstance::getNumSolids()const
	{
		return (int)(mSolidList.size());
	}

	unsigned int BlueprintInstance::getNumJoints()const
	{
		return (int)(mJointList.size());
	}

	unsigned int BlueprintInstance::getNumMotors()const
	{
		return (int)(mMotorList.size());
	}

	unsigned int BlueprintInstance::getNumSensors()const
	{
		return (int)(mSensorList.size());
	}

	Solid* BlueprintInstance::getSolid(unsigned int i)const
	{
		return mSolidList.at(i);
	}

	Joint* BlueprintInstance::getJoint(unsigned int i)const
	{
		return mJointList.at(i);
	}

	Motor* BlueprintInstance::getMotor(unsigned int i)const
	{
		return mMotorList.at(i);
	}

	Sensor* BlueprintInstance::getSensor(unsigned int i)const
	{
		return mSensorList.at(i);
	}

	void BlueprintInstance::internal_addSolid(Solid* s)
	{
		mSolidList.push_back(s);

		if (NULL == s)
		{
			return;
		}

		std::string name = s->getName();

		if (name.empty())
		{
			return;
		}

		mSolidMap[name] = s;
	}

	void BlueprintInstance::internal_addJoint(Joint* j)
	{
		mJointList.push_back(j);

		if (NULL == j)
		{
			return;
		}

		std::string name = j->getName();

		if (name.empty())
		{
			return;
		}

		mJointMap[name] = j;
	}

	void BlueprintInstance::internal_addMotor(Motor* m)
	{
		mMotorList.push_back(m);

		if (NULL == m)
		{
			return;
		}

		std::string name = m->getName();

		if (name.empty())
		{
			return;
		}

		mMotorMap[name] = m;
	}

	void BlueprintInstance::internal_addSensor(Sensor* s)
	{
		mSensorList.push_back(s);

		if (NULL == s)
		{
			return;
		}

		std::string name = s->getName();

		if (name.empty())
		{
			return;
		}

		mSensorMap[name] = s;
	}
}
