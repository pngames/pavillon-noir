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

#ifndef OPAL_QUATERNION_H
#define OPAL_QUATERNION_H

#include "OpalMath.h"

namespace opal
{
	class Quaternion;
	inline Quaternion operator+(const Quaternion &q1, const Quaternion &q2);
	inline Quaternion operator-(const Quaternion &q1, const Quaternion &q2);
	inline Quaternion operator*(const Quaternion& q, real scalar);
	inline Quaternion operator*(real scalar, const Quaternion& q);

	/// Prints the Quaternion to the given output stream.
	inline std::ostream& operator<<(std::ostream& o, const Quaternion& q);

	class Quaternion
	{
	private:
		real mData[4];

	public:
		Quaternion()
		{
			mData[0] = 0;
			mData[1] = 0;
			mData[2] = 0;
			mData[3] = 0;
		}

		Quaternion(real w, real x, real y, real z)
		{
			mData[0] = w;
			mData[1] = x;
			mData[2] = y;
			mData[3] = z;
		}

		Quaternion(const Quaternion& src)
		{
			memcpy(mData, src.mData, 4 * sizeof(real));
		}

		inline void set(real w, real x, real y, real z	)
		{
			mData[0] = w;
			mData[1] = x;
			mData[2] = y;
			mData[3] = z;
		}

		inline real lengthSquared()const
		{
			return mData[0]*mData[0] + mData[1]*mData[1] + mData[2]*mData[2] + 
				mData[3]*mData[3];
		}

		inline real length()const
		{
			return sqrt(lengthSquared());
		}

		inline void normalize()
		{
			real len = length();
			assert(0 != len);
			real factor = 1 / len;
			(*this) = (*this) * factor;
		}

		void getAngleAxis(real& angle, Vec3r& axis)
		{
			real sqrLen = mData[1]*mData[1] + mData[2]*mData[2] + 
				mData[3]*mData[3];

			if(sqrLen > 0)
			{
				angle = 2 * acos(mData[0]);
				real invLen = 1 / sqrt(sqrLen);
				axis[0] = mData[1] * invLen;
				axis[1] = mData[2] * invLen;
				axis[2] = mData[3] * invLen;
			}
			else
			{
				angle = 0;
				axis[0] = 1;
				axis[1] = 0;
				axis[2] = 0;
			}

			// convert to degrees
			angle = radToDeg(angle);
		}

		real getRoll()const
		{
			return radToDeg(atan2(2*(mData[2]*mData[3] + mData[0]*mData[1]), 
				mData[0]*mData[0] - mData[1]*mData[1] - mData[2]*mData[2] + 
				mData[3]*mData[3]));
		}

		real getPitch()const
		{
			return radToDeg(asin(-2*(mData[1]*mData[3] - mData[0]*mData[2])));
		}

		real getYaw()const
		{
			return radToDeg(atan2(2*(mData[1]*mData[2] + mData[0]*mData[3]), 
				mData[0]*mData[0] + mData[1]*mData[1] - mData[2]*mData[2] - 
				mData[3]*mData[3]));
		}

		inline real & operator[](unsigned int i)
		{
			assert(i < 4);
			return mData[i];
		}

		inline const real & operator[](unsigned int i)const
		{
			assert(i < 4);
			return mData[i];
		}
	};

	inline Quaternion operator+(const Quaternion &q1, const Quaternion &q2)
	{
		return Quaternion(q1[0] + q2[0], q1[1] + q2[1], q1[2] + q2[2], q1[3] + 
			q2[3]);
	}

	inline Quaternion operator-(const Quaternion &q1, const Quaternion &q2)
	{
		return Quaternion(q1[0] - q2[0], q1[1] - q2[1], q1[2] - q2[2], q1[3] - 
			q2[3]);
	}

	inline Quaternion operator*(const Quaternion& q, real scalar)
	{
		return Quaternion(scalar * q[0], scalar * q[1], scalar * q[2], 
			scalar * q[3]);
	}

	inline Quaternion operator*(real scalar, const Quaternion& q)
	{
		return Quaternion(scalar * q[0], scalar * q[1], scalar * q[2], 
			scalar * q[3]);
	}

	inline std::ostream& operator<<(std::ostream& o, const Quaternion& q)
	{
		return o << "[" << q[0] << " " << q[1] << " " << q[2] << " " 
			<< q[3] << "]";
	}
}

#endif
