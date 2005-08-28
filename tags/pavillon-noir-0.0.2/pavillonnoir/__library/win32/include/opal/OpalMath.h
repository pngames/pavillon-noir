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

#ifndef OPAL_OPAL_MATH_H
#define OPAL_OPAL_MATH_H

#include <math.h>

namespace opal
{
	typedef float real;

	namespace globals
	{
		const real OPAL_PI = (real)3.14159265358979323846;
		const real OPAL_HALF_PI = (real)1.57079632679489661923;
		const real OPAL_ONE_THIRD = (real)0.33333333333333333333;
		const real OPAL_EPSILON = (real)0.000001;
	}

	/// Converts a value from degrees to radians.
	inline real degToRad(real deg)
	{
		const real d2r = globals::OPAL_PI/(real)180.0;
		return (d2r * deg);
	}

	/// Converts a value from radians to degrees.
	inline real radToDeg(real rad)
	{
		const real r2d = (real)180.0/globals::OPAL_PI;
		return (r2d * rad);
	}

	/// Returns the absolute value of a real number.
	inline real abs(real value)
	{
		return fabs(value);
	}
}

#include "Point3r.h"
#include "Vec3r.h"
#include "Rayr.h"
#include "Matrix44r.h"
#include "Quaternion.h"

#endif

