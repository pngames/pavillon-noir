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

#ifndef OPAL_THRUSTER_MOTOR_DATA_H
#define OPAL_THRUSTER_MOTOR_DATA_H

#include "Defines.h"
#include "MotorData.h"

namespace opal
{
	/// A data structure describing a ThrusterMotor.
	class ThrusterMotorData : public MotorData
	{
	public:
		OPAL_DECL ThrusterMotorData()
		: MotorData()
		{
			mType = THRUSTER_MOTOR;
			solid = NULL;
			internal_solidIndex = 0;
			solidBlueprintRefName = "";
			force.singleStep = true;
		}

		/// Copy constructor.
		OPAL_DECL ThrusterMotorData(const ThrusterMotorData& data)
		{
			(*this) = data;
		}

		OPAL_DECL virtual ~ThrusterMotorData()
		{
		}

		/// Makes a deep copy.
		OPAL_DECL virtual void OPAL_CALL operator=(
			const ThrusterMotorData& data)
		{
			mType = data.mType;
			enabled = data.enabled;
			name = data.name;
			solid = data.solid;
			internal_solidIndex = data.internal_solidIndex;
			solidBlueprintRefName = data.solidBlueprintRefName;
			force = data.force;
		}

		/// Pointer to the Solid.
		Solid* solid;

		/// Internal data used for Blueprint instantiation.
		int internal_solidIndex;

		/// String used for for intra-Blueprint references.
		std::string solidBlueprintRefName;

		/// The Force that gets applied to the Solid every time step.  
		Force force;

	protected:

	private:
	};
}

#endif
