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

#ifndef OPAL_POINT3R_H
#define OPAL_POINT3R_H

#include "OpalMath.h"
#include "Vec3r.h"

namespace opal
{
	class Point3r;
	inline Point3r operator+(const Point3r &u, const Vec3r &v);
	inline Point3r operator-(const Point3r &u, const Vec3r &v);
	inline Vec3r operator-(const Point3r &u, const Point3r &v);
	inline Point3r operator*(const Point3r &v, real scalar);
	inline Point3r operator*(real scalar, const Point3r &v);
	inline Point3r operator/(const Point3r &v, real scalar);
	inline Point3r operator-(const Point3r &p);

	/// Returns the Euclidean distance between two points.
	inline real distance(const Point3r& p1, const Point3r& p2);

	/// Prints the Point3r to the given output stream.
	inline std::ostream& operator<<(std::ostream& o, const Point3r& p);

	class Point3r
	{
	private:
		real mData[3];

	public:
		Point3r()
		{
			mData[0] = 0;
			mData[1] = 0;
			mData[2] = 0;
		}

		Point3r(const Point3r & src)
		{
			mData[0] = src.mData[0];
			mData[1] = src.mData[1];
			mData[2] = src.mData[2];
		}

		Point3r(real x, real y, real z)
		{
			mData[0] = x;
			mData[1] = y;
			mData[2] = z;
		}

		Point3r(const real * data)
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

		inline void operator+=(const Vec3r & v)
		{
			mData[0] += v[0];
			mData[1] += v[1];
			mData[2] += v[2];
		}

		inline void operator-=(const Vec3r & v)
		{
			mData[0] -= v[0];
			mData[1] -= v[1];
			mData[2] -= v[2];
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

		inline bool operator==(const Point3r & v)
		{
			return (mData[0]==v.mData[0] && mData[1]==v.mData[1] && 
				v.mData[2]==mData[2]);
		}

		inline bool operator!=(const Point3r & v)
		{
			return (mData[0]!=v.mData[0] && mData[1]!=v.mData[1] && 
				v.mData[2]!=mData[2]);
		}
	};

	inline Point3r operator+(const Point3r &u, const Vec3r &v)
	{
		return Point3r(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
	}

	inline Point3r operator-(const Point3r &u, const Vec3r &v)
	{
		return Point3r(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
	}

	inline Vec3r operator-(const Point3r &u, const Point3r &v)
	{
		return Vec3r(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
	}

	inline Point3r operator*(const Point3r &v, real scalar)
	{
		return Point3r(scalar * v[0], scalar * v[1], scalar * v[2]);
	}

	inline Point3r operator*(real scalar, const Point3r &v)
	{
		return Point3r(scalar * v[0], scalar * v[1], scalar * v[2]);
	}

	inline Point3r operator/(const Point3r &v, real scalar)
	{
		return Point3r(v[0] / scalar, v[1] / scalar,  v[2] / scalar);
	}

	inline real distance(const Point3r& p1, const Point3r& p2)
	{
		return sqrt(pow((p2[0] - p1[0]), 2) + pow((p2[1] - p1[1]), 2) + 
			pow((p2[2] - p1[2]), 2));
	}

	inline Point3r operator-(const Point3r &p)
	{
		return p * -1;
	}

	inline std::ostream& operator<<(std::ostream& o, const Point3r& p)
	{
		return o << "[" << p[0] << " " << p[1] << " " << p[2] << "]";
	}
}

#endif

