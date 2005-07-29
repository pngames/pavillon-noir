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

#ifndef OPAL_MATRIX44R_H
#define OPAL_MATRIX44R_H

#include "Quaternion.h"
#include "OpalMath.h"

namespace opal
{
	// Internally the matrix is column major order (openGL)
	// the accessors are (row, col), but the set(16 x real) function
	// is column, row order because then it is easier to write
	// the 16 real out.

	class Matrix44r;
	inline Matrix44r operator*(const Matrix44r & lhs, const Matrix44r & rhs);
	inline Vec3r operator*(const Matrix44r & m, const Vec3r &v);
	inline Matrix44r operator+(const Matrix44r & lhs, const Matrix44r & rhs);
	inline Matrix44r operator-(const Matrix44r & lhs, const Matrix44r & rhs);
	inline Point3r operator*(const Matrix44r & m, const Point3r &p);
	inline Rayr operator*(const Matrix44r & m, const Rayr &r);

	/// Inverts src, and puts the result into dest, and returns true.  
	/// If no valid inverse is found, returns false and leaves dest unchanged.
	inline bool inverse(Matrix44r & dest, const Matrix44r & src);

	/// Fast invert function for affine transformations only.
	inline void fastInverse(Matrix44r & dest, const Matrix44r & src);

	/// Prints the Matrix44r to the given output stream.
	inline std::ostream& operator<<(std::ostream& o, const Matrix44r& m);
	
	class Matrix44r
	{
	private:
		real mData[16];

	public:
		inline friend Matrix44r operator*(real scalar, Matrix44r m);

		Matrix44r()
		{
			makeIdentity();
		}

		Matrix44r(const Matrix44r & src)
		{
			memcpy(mData, src.mData, 16 * sizeof(real));
		}

		//Document this! set is row-column order so it's easier to read
		Matrix44r(real _00, real _10, real _20, real _30,
					real _01, real _11, real _21, real _31,
					real _02, real _12, real _22, real _32,
					real _03, real _13, real _23, real _33)
		{
			mData[0] = _00;
			mData[1] = _01;
			mData[2] = _02;
			mData[3] = _03;

			mData[4] = _10;
			mData[5] = _11;
			mData[6] = _12;
			mData[7] = _13;

			mData[8] =  _20;
			mData[9] =  _21;
			mData[10] = _22;
			mData[11] = _23;

			mData[12] = _30;
			mData[13] = _31;
			mData[14] = _32;
			mData[15] = _33;
		}

		//WARNING! this takes in a column-row order matrix
		Matrix44r(const real * data)
		{
			memcpy(mData, data, 16 * sizeof(real));
		}

		inline void setPosition(real x, real y, real z)
		{
			mData[12] = x;
			mData[13] = y;
			mData[14] = z;
		}

		inline Point3r getPosition()const
		{
			return Point3r(mData[12], mData[13], mData[14]);
		}

		inline Vec3r getTranslation()const
		{
			return Vec3r(mData[12], mData[13], mData[14]);
		}

		//Document this! set is row-column order so it's easier to read
		inline void set(real _00, real _10, real _20, real _30,
						real _01, real _11, real _21, real _31,
						real _02, real _12, real _22, real _32,
						real _03, real _13, real _23, real _33)
		{
			mData[0] = _00;
			mData[1] = _01;
			mData[2] = _02;
			mData[3] = _03;

			mData[4] = _10;
			mData[5] = _11;
			mData[6] = _12;
			mData[7] = _13;

			mData[8] =  _20;
			mData[9] =  _21;
			mData[10] = _22;
			mData[11] = _23;

			mData[12] = _30;
			mData[13] = _31;
			mData[14] = _32;
			mData[15] = _33;
		}

		//WARNING! this takes in a column-row order matrix
		inline void set(const real * data)
		{
			memcpy(mData, data, 16 * sizeof(real));
		}

		inline void makeZero()
		{
			memset(mData, 0, 16 * sizeof(real));
		}

		inline void makeIdentity()
		{
			mData[0] = 1;
			mData[1] = 0;
			mData[2] = 0;
			mData[3] = 0;

			mData[4] = 0;
			mData[5] = 1;
			mData[6] = 0;
			mData[7] = 0;

			mData[8] =  0;
			mData[9] =  0;
			mData[10] = 1;
			mData[11] = 0;

			mData[12] = 0;
			mData[13] = 0;
			mData[14] = 0;
			mData[15] = 1;	
		}
		
		inline void makeScale(real s)
		{
			set(s,0,0,0, 0,s,0,0, 0,0,s,0, 0,0,0,1);
		}

		inline void makeScale(real x, real y, real z)
		{
			set(x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1);
		}

		inline void makeRotation(real theta, real x, real y, real z)
		{
			Vec3r axis(x, y, z);
			axis.normalize();
			x = axis[0];
			y = axis[1];
			z = axis[2];

			// source: http://www.euclideanspace.com/maths/geometry/rotations/
			// conversions/angleToMatrix/
			theta = degToRad(theta);
			real c = cos(theta);
			real s = sin(theta);
			real t = (real)1.0 - c;
			
			(*this)(0,0) = c + x*x*t;
			(*this)(1,1) = c + y*y*t;
			(*this)(2,2) = c + z*z*t;

			real tmp1 = x*y*t;
			real tmp2 = z*s;
			(*this)(1,0) = tmp1 + tmp2;
			(*this)(0,1) = tmp1 - tmp2;

			tmp1 = x*z*t;
			tmp2 = y*s;
			(*this)(2,0) = tmp1 - tmp2;
			(*this)(0,2) = tmp1 + tmp2;

			tmp1 = y*z*t;
			tmp2 = x*s;
			(*this)(2,1) = tmp1 + tmp2;
			(*this)(1,2) = tmp1 - tmp2;

			(*this)(0,3) = 0;
			(*this)(1,3) = 0;
			(*this)(2,3) = 0;

			(*this)(3,0) = 0;
			(*this)(3,1) = 0;
			(*this)(3,2) = 0;
			(*this)(3,3) = 1;
		}

		inline void setRotation(real theta, real x, real y, real z)
		{
			opal::Point3r p = getPosition();
			makeRotation(theta, x, y, z);
			(*this)(0,3) = p[0];
			(*this)(1,3) = p[1];
			(*this)(2,3) = p[2];
		}

		inline void makeTranslation(real x, real y, real z)
		{
			set(1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1);
		}

		//post multiply transformations, openGL style, for convenience
		inline void scale(real s)
		{
			Matrix44r m(s,0,0,0, 0,s,0,0, 0,0,s,0, 0,0,0,1);
			(*this) = (*this) * m;
		}

		inline void scale(real x, real y, real z)
		{
			Matrix44r m(x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1);
			(*this) = (*this) * m;
		}

		// The following function is from
		// http://www.euclideanspace.com/maths/geometry/rotations/
		// conversions/matrixToQuaternion/
		inline Quaternion getQuaternion() const
		{
			Quaternion q;
			real trace = (*this)(0,0) + (*this)(1,1) + (*this)(2,2) + 1.0f;

			if(trace > globals::OPAL_EPSILON)
			{
				real s = 0.5f / sqrt(trace);
				q[0] = 0.25f / s;
				q[1] = ((*this)(2,1) - (*this)(1,2)) * s;
				q[2] = ((*this)(0,2) - (*this)(2,0)) * s;
				q[3] = ((*this)(1,0) - (*this)(0,1)) * s;
			}
			else
			{
				if((*this)(0,0) > (*this)(1,1) && (*this)(0,0) > (*this)(2,2))
				{
					real s = 2.0f * sqrtf(1.0f + (*this)(0,0) - (*this)(1,1) - 
						(*this)(2,2));
					q[1] = 0.25f * s;
					q[2] = ((*this)(0,1) + (*this)(1,0)) / s;
					q[3] = ((*this)(0,2) + (*this)(2,0)) / s;
					q[0] = ((*this)(1,2) - (*this)(2,1)) / s;
				}
				else if ((*this)(1,1) > (*this)(2,2))
				{
					real s = 2.0f * sqrtf(1.0f + (*this)(1,1) - (*this)(0,0) - 
						(*this)(2,2));
					q[1] = ((*this)(0,1) + (*this)(1,0)) / s;
					q[2] = 0.25f * s;
					q[3] = ((*this)(1,2) + (*this)(2,1)) / s;
					q[0] = ((*this)(0,2) - (*this)(2,0)) / s;
				}
				else
				{
					real s = 2.0f * sqrtf(1.0f + (*this)(2,2) - (*this)(0,0) - 
						(*this)(1,1));
					q[1] = ((*this)(0,2) + (*this)(2,0)) / s;
					q[2] = ((*this)(1,2) + (*this)(2,1)) / s;
					q[3] = 0.25f * s;
					q[0] = ((*this)(0,1) - (*this)(1,0)) / s;
				}
			}

			return q;
		}

		inline Vec3r getEulerXYZ()const
		{
			Vec3r angles;

			angles[1] = asin((*this)(0,2));
			if(angles[1] < globals::OPAL_HALF_PI)
			{
				if(angles[1] > -globals::OPAL_HALF_PI)
				{
					angles[0] = atan2(-(*this)(1,2), (*this)(2,2));
					angles[2] = atan2(-(*this)(0,1), (*this)(0,0));
				}
				else
				{
					// This is not a unique solution.
					real value = atan2((*this)(1,0), (*this)(1,1));
					angles[2] = 0;
					angles[0] = angles[2] - value;
				}
			}
			else
			{
				// This is not a unique solution.
				real value = atan2((*this)(1,0), (*this)(1,1));
				angles[2] = 0;
				angles[0] = value - angles[2];
			}

			// convert to degrees
			angles[0] = radToDeg(angles[0]);
			angles[1] = radToDeg(angles[1]);
			angles[2] = radToDeg(angles[2]);

			return angles;
		}

		//post multiply transformations, openGL style, for convenience
		inline void preScale(real s)
		{
			Matrix44r m(s,0,0,0, 0,s,0,0, 0,0,s,0, 0,0,0,1);
			(*this) = m * (*this);
		}

		inline void preScale(real x, real y, real z)
		{
			Matrix44r m(x,0,0,0, 0,y,0,0, 0,0,z,0, 0,0,0,1);
			(*this) = m * (*this);
		}


		inline void rotate(real theta, real x, real y, real z)
		{
			Matrix44r m;
			m.makeRotation(theta, x, y, z);
			(*this) = (*this) * m;
		}

		inline void preRotate(real theta, real x, real y, real z)
		{
			Matrix44r m;
			m.makeRotation(theta, x, y, z);
			(*this) = m * (*this);
		}

		inline void translate(real x, real y, real z)
		{
			Matrix44r m(1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1);
			(*this) = (*this) * m;
		}

		inline void preTranslate(real x, real y, real z)
		{
			Matrix44r m(1,0,0,x, 0,1,0,y, 0,0,1,z, 0,0,0,1);
			(*this) = m * (*this);
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
			return mData[i];
		}

		inline const real & operator[](unsigned int i)const
		{
			return mData[i];
		}

		inline real & operator()(unsigned int row, unsigned int col)
		{
			return mData[ 4 * col + row ];
		}

		inline const real & operator()(unsigned int row, unsigned int col)const
		{
			return mData[ 4 * col + row ];
		}

		inline void operator*=(const Matrix44r &m)
		{
			(*this) = (*this) * m;
		}

		inline bool operator==(const Matrix44r & m)const
		{
			for(int i = 0; i<16; ++i)
			{
				if(mData[i] != m[i]) return false;
			}

			return true;
		}

		inline bool operator!=(const Matrix44r & m)const
		{
			for(int i = 0; i<16; ++i)
			{
				if(mData[i] != m[i]) return true;
			}

			return false;
		}

		inline void swap(real & a, real & b)
		{
			real temp = a;
			a = b;
			b = temp;
		}

		inline void transpose()
		{
			swap(mData[1], mData[4]);
			swap(mData[2], mData[8]);
			swap(mData[3], mData[12]);

			swap(mData[6], mData[9]);
			swap(mData[7], mData[13]);
			swap(mData[11], mData[14]);
		}
		
		inline real determinant()const
		{
			real det1 = (*this)(1,2) * (*this)(2,3) - (*this)(2,2) * 
				(*this)(1,3);
			real det2 = (*this)(1,1) * (*this)(2,3) - (*this)(2,1) * 
				(*this)(1,3);
			real det3 = (*this)(1,1) * (*this)(2,2) - (*this)(2,1) * 
				(*this)(1,2);
			real det4 = (*this)(1,0) * (*this)(2,3) - (*this)(2,0) * 
				(*this)(1,3);
			real det5 = (*this)(1,0) * (*this)(2,2) - (*this)(2,0) * 
				(*this)(1,2);
			real det6 = (*this)(1,0) * (*this)(2,1) - (*this)(2,0) * 
				(*this)(1,1);

			return -(*this)(3,0) * ((*this)(0,1) * det1 - (*this)(0,2) * 
				det2 + (*this)(0,3) * det3) + (*this)(3,1) * ((*this)(0,0) * 
				det1 - (*this)(0,2) * det4 + (*this)(0,3) * det5) - 
				(*this)(3,2) * ((*this)(0,0) * det2 - (*this)(0,1) * det4 + 
				(*this)(0,3) * det6) + (*this)(3,3) * ((*this)(0,0) * det3 - 
				(*this)(0,1) * det5 + (*this)(0,2) * det6);
		}
		
		inline bool invert()
		{
			return inverse(*this, *this);
		}
		
		inline void fastInvert()
		{
			fastInverse(*this, *this);
		}

		inline Vec3r getForward()const
		{
			return (*this) * Vec3r(0, 0, -1);
		}

		inline Vec3r getUp()const
		{
			return (*this) * Vec3r(0, 1, 0);
		}

		inline Vec3r getRight()const
		{
			return (*this) * Vec3r(1, 0, 0);
		}
	};

	inline bool inverse(Matrix44r & dest, const Matrix44r & src)
	{
		std::cerr << "opal::Matrix44r inverse is hella busted! use \
					 fastInverse for affine transforms" << std::endl;
		real det = src.determinant();
		if(opal::abs(det < globals::OPAL_EPSILON)) return false;
		dest = ((real)1.0 / det) * src;
		return true;
	}

	inline void fastInverse(Matrix44r & result, const Matrix44r & source)
	{
		// source: stolen straight from GMTL
		// in case &dest is == &source... :(
		Matrix44r src = source;

		// The rotational part of the matrix is simply the transpose of the
		// original matrix.
		for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
		{
			result(x,y) = src(y,x);
		}

		real l0 = Vec3r(result(0, 0), result(0, 1), 
			result(0, 2)).lengthSquared();
		real l1 = Vec3r(result(1, 0), result(1, 1), 
			result(1, 2)).lengthSquared();
		real l2 = Vec3r(result(2, 0), result(2, 1), 
			result(2, 2)).lengthSquared();

		if(opal::abs(l0) > globals::OPAL_EPSILON) l0 = 1.0f / l0;
		if(opal::abs(l1) > globals::OPAL_EPSILON) l1 = 1.0f / l1;
		if(opal::abs(l2) > globals::OPAL_EPSILON) l2 = 1.0f / l2;

		// apply the inverse scale to the 3x3
		// for each axis: normalize it (1/length), and then mult by inverse 
		// scale (1/length)
		result(0, 0) *= l0;
		result(0, 1) *= l0;
		result(0, 2) *= l0;
		result(1, 0) *= l1;
		result(1, 1) *= l1;
		result(1, 2) *= l1;
		result(2, 0) *= l2;
		result(2, 1) *= l2;
		result(2, 2) *= l2;

		// The right column vector of the matrix should always be [ 0 0 0 s ]
		// this represents some shear values
		result(3, 0) = result(3, 1) = result(3, 2) = 0;
         
		// The translation components of the original matrix.
		const real& tx = src(0, 3);
		const real& ty = src(1, 3);
		const real& tz = src(2, 3);

		// invert scale.
		const real tw = (opal::abs(src(3, 3)) > globals::OPAL_EPSILON) 
			? 1.0f / src(3, 3) : 0.0f;

		// handle uniform scale in Nx4 matrices
		result(0, 3) = -(result(0, 0) * tx + result(0, 1) * ty + 
			result(0, 2) * tz) * tw;
		result(1, 3) = -(result(1, 0) * tx + result(1, 1) * ty + 
			result(1, 2) * tz) * tw;
		result(2, 3) = -(result(2, 0) * tx + result(2, 1) * ty + 
			result(2, 2) * tz) * tw;
		result(3, 3) = tw;
	}
	
	inline Matrix44r operator*(real scalar, Matrix44r m)
	{
		for(unsigned int i = 0; i<16; ++i)
		{
			m.mData[i] *= scalar;
		}

		return m;
	}

	inline Matrix44r operator*(const Matrix44r & lhs, const Matrix44r & rhs)
	{
		Matrix44r res; // prevent aliasing
		res.makeZero();

		// source: p. 150 Numerical Analysis (second ed.)
		// if A is m x p, and B is p x n, then AB is m x n
		// (AB)ij = [k = 1 to p] (a)ik (b)kj (where:  1 <= i <= m, 1 <= j <= n)
		for (unsigned int i = 0; i < 4; ++i)	// 1 <= i <= m
		for (unsigned int j = 0; j < 4; ++j)	// 1 <= j <= n
		for (unsigned int k = 0; k < 4; ++k)	// [k = 1 to p]
			res(i, j) += lhs(i, k) * rhs(k, j);
		return res;
	}

	inline Vec3r operator*(const Matrix44r & m, const Vec3r &v)
	{	
		return Vec3r(	m(0,0) * v[0] + m(0,1) * v[1] + m(0,2) * v[2],
						m(1,0) * v[0] + m(1,1) * v[1] + m(1,2) * v[2],
						m(2,0) * v[0] + m(2,1) * v[1] + m(2,2) * v[2]	);
	}

	inline Point3r operator*(const Matrix44r & m, const Point3r &p)
	{
		return Point3r(
			m(0,0) * p[0] + m(0,1) * p[1] + m(0,2) * p[2] + m(0,3),
			m(1,0) * p[0] + m(1,1) * p[1] + m(1,2) * p[2] + m(1,3),
			m(2,0) * p[0] + m(2,1) * p[1] + m(2,2) * p[2] + m(2,3));
	}

	inline Matrix44r operator+(const Matrix44r & lhs, const Matrix44r & rhs)
	{
		Matrix44r res;
		for (unsigned int i=0; i<16; ++i)
		{
			res[i] = lhs[i] + rhs[i];
		}
		return res;
	}

	inline Matrix44r operator-(const Matrix44r & lhs, const Matrix44r & rhs)
	{
		Matrix44r res;
		for (unsigned int i=0; i<16; ++i)
		{
			res[i] = lhs[i] - rhs[i];
		}
		return res;
	}

	inline Rayr operator*(const Matrix44r & m, const Rayr & r)
	{
		Rayr ray(m * r.getOrigin(), m * r.getDir());
		return ray;
	}

	inline std::ostream& operator<<(std::ostream& o, const Matrix44r& m)
	{
		return o 
			<< "[" << m[0] << " " << m[1] << " " << m[2] << " " << m[3] 
			<< "]" << std::endl 
			<< "[" << m[4] << " " << m[5] << " " << m[6] << " " << m[7] 
			<< "]" << std::endl 
			<< "[" << m[8] << " " << m[9] << " " << m[10] << " " << m[11] 
			<< "]" << std::endl 
			<< "[" << m[12] << " " << m[13] << " " << m[14] << " " << m[15] 
			<< "]";
	}
}

#endif
