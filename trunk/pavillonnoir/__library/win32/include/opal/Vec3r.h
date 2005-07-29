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

#ifndef OPAL_VEC3R_H
#define OPAL_VEC3R_H

#include "OpalMath.h"

namespace opal
{
	class Vec3r;
	inline Vec3r operator+(const Vec3r &u, const Vec3r &v);
	inline Vec3r operator-(const Vec3r &u, const Vec3r &v);
	inline Vec3r operator*(const Vec3r &v, real scalar);
	inline Vec3r operator*(real scalar, const Vec3r &v);
	inline Vec3r operator/(const Vec3r &v, real scalar);
	inline Vec3r operator%(const Vec3r & a, const Vec3r & b);
	inline Vec3r operator-(const Vec3r &v);
	inline real dot(const Vec3r & u, const Vec3r & v);
	inline Vec3r cross(const Vec3r & u, const Vec3r& v);

	/// Returns the projection of 'v' onto 'u'.
	inline Vec3r project(const Vec3r& u, const Vec3r& v);

	/// Given that the vector 'u' is already a unit vector, returns the 
	/// projection of v onto u.
	inline Vec3r projectPreNorm(const Vec3r& u, const Vec3r& v);

	/// Returns a positive angle between 0 and 180 degrees.
	inline real angleBetween(const Vec3r& u, const Vec3r& v);

	/// Given that the vectors 'u' and 'v' are already normalized, returns 
	/// a positive angle between 0 and 180 degrees.
	inline real angleBetweenPreNorm(const Vec3r& u, const Vec3r& v);

	/// Returns true if the two vectors are roughly collinear (within some 
	/// epsilon).
	inline bool areCollinear(const Vec3r& u, const Vec3r& v);

	/// Prints the Vec3r to the given output stream.
	inline std::ostream& operator<<(std::ostream& o, const Vec3r& v);

	class Vec3r
	{
	private:
		real mData[3];

	public:
		Vec3r()
		{
			mData[0] = 0;
			mData[1] = 0;
			mData[2] = 0;
		}

		Vec3r(const Vec3r & src)
		{
			mData[0] = src.mData[0];
			mData[1] = src.mData[1];
			mData[2] = src.mData[2];
		}

		Vec3r(real x, real y, real z)
		{
			mData[0] = x;
			mData[1] = y;
			mData[2] = z;
		}

		Vec3r(const real * data)
		{
			mData[0] = data[0];
			mData[1] = data[1];
			mData[2] = data[2];
		}

		inline void set(real x, real y, real z)
		{
			mData[0] = x;
			mData[1] = y;
			mData[2] = z;
		}
		
		inline void set(real * data)
		{
			mData[0] = data[0];
			mData[1] = data[1];
			mData[2] = data[2];
		}

		inline real * getData()
		{
			return mData;
		}

		inline const real * getData()const
		{
			return mData;
		}

		inline real & operator[](unsigned int i)
		{
			assert(i < 3);
			return mData[i];
		}

		inline const real & operator[](unsigned int i)const
		{
			assert(i < 3);
			return mData[i];
		}

		inline real lengthSquared()const
		{
			return dot(*this, *this);
		}

		inline real length()const
		{
			return sqrt(dot(*this, *this)); 
		}

		inline void normalize()
		{
			real len = length();
			assert(0 != len);
			real factor = (real)1.0 / len;
			(*this) *= factor;
		}

		inline Vec3r unit()const
		{
			return (*this) / length();
		}

		inline void operator+=(const Vec3r & v)
		{
			mData[0] += v.mData[0];
			mData[1] += v.mData[1];
			mData[2] += v.mData[2];
		}

		inline void operator-=(const Vec3r & v)
		{
			mData[0] -= v.mData[0];
			mData[1] -= v.mData[1];
			mData[2] -= v.mData[2];
		}

		inline void operator*=(const Vec3r & v)
		{
			mData[0] *= v.mData[0];
			mData[1] *= v.mData[1];
			mData[2] *= v.mData[2];
		}

		inline void operator*=(real scalar)
		{
			mData[0] *= scalar;
			mData[1] *= scalar;
			mData[2] *= scalar;
		}

		inline void operator/=(real scalar)
		{
			mData[0] /= scalar;
			mData[1] /= scalar;
			mData[2] /= scalar;
		}

		inline void operator/=(const Vec3r & v)
		{
			mData[0] /= v.mData[0];
			mData[1] /= v.mData[1];
			mData[2] /= v.mData[2];
		}

		inline bool operator==(const Vec3r & v)
		{
			return(mData[0]==v.mData[0] && mData[1]==v.mData[1] && 
				v.mData[2]==mData[2]);
		}

		inline bool operator!=(const Vec3r & v)
		{
			return(mData[0]!=v.mData[0] && mData[1]!=v.mData[1] && 
				v.mData[2]!=mData[2]);
		}
	};

	inline Vec3r operator+(const Vec3r &u, const Vec3r &v)
	{
		return Vec3r(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
	}

	inline Vec3r operator-(const Vec3r &u, const Vec3r &v)
	{
		return Vec3r(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
	}

	inline Vec3r operator*(const Vec3r &v, real scalar)
	{
		return Vec3r(scalar * v[0], scalar * v[1], scalar * v[2]);
	}

	inline Vec3r operator*(real scalar, const Vec3r &v)
	{
		return Vec3r(scalar * v[0], scalar * v[1], scalar * v[2]);
	}

	inline Vec3r operator/(const Vec3r &v, real scalar)
	{
		return Vec3r(v[0] / scalar, v[1] / scalar,  v[2] / scalar);
	}

	inline Vec3r operator%(const Vec3r & a, const Vec3r & b)
	{
		return Vec3r((a[1]*b[2]) - (a[2]*b[1]), (a[2]*b[0]) - (a[0]*b[2]), 
			(a[0]*b[1]) - (a[1]*b[0]));
	}

	inline real dot(const Vec3r & u, const Vec3r & v)
	{
		return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
	}

	inline Vec3r cross(const Vec3r & u, const Vec3r & v)
	{
		return u%v;
	}

	inline Vec3r operator-(const Vec3r &v)
	{
		return v * -1;
	}

	inline Vec3r project(const Vec3r& u, const Vec3r& v)
	{
		Vec3r u2 = u;
		u2.normalize();
		return projectPreNorm(u2, v);
	}

	inline Vec3r projectPreNorm(const Vec3r& u, const Vec3r& v)
	{
		return dot(u, v) * u;
	}

	inline real angleBetween(const Vec3r& u, const Vec3r& v)
	{
		Vec3r u2 = u;
		u2.normalize();
		Vec3r v2 = v;
		v2.normalize();
		return angleBetweenPreNorm(u2, v2);
	}

	inline real angleBetweenPreNorm(const Vec3r& u, const Vec3r& v)
	{
		real val = dot(u, v);

		// Clamp to avoid rounding errors; acos will puke with values outside 
		// this range.
		if (val < -1)
		{
			val = -1;
		}
		else if (val > 1)
		{
			val = 1;
		}

		return radToDeg(acos(val));
	}

	inline bool areCollinear(const Vec3r& u, const Vec3r& v)
	{
		real value = 1 - dot(u, v);
		if (opal::abs(value) < globals::OPAL_EPSILON)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	inline std::ostream& operator<<(std::ostream& o, const Vec3r& v)
	{
		return o << "[" << v[0] << " " << v[1] << " " << v[2] << "]";
	}
}

#endif
