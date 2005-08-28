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

#ifndef OPAL_MESH_SHAPE_DATA_H
#define OPAL_MESH_SHAPE_DATA_H

#include "Defines.h"
#include "ShapeData.h"

namespace opal
{
	/// A data structure describing a mesh Shape.  The data pointers 
	/// for the vertex and face arrays must remain valid; no mesh data 
	/// is stored anywhere within OPAL.  It is critical that the size of 
	/// the data type used in these arrays (i.e. OPAL real) matches the 
	/// size of the data type expected by the underlying physics engine.
	class MeshShapeData : public ShapeData
	{
	public:
		OPAL_DECL MeshShapeData()
		: ShapeData()
		{
			mType = MESH_SHAPE;
			vertexArray[0] = NULL;
			numVertices = 0;
			faceArray = NULL;
			numFaces = 0;
		}

		/// Copy constructor.
		OPAL_DECL MeshShapeData(const MeshShapeData& data)
		{
			(*this) = data;
		}

		OPAL_DECL virtual ~MeshShapeData()
		{
		}

		/// Makes a shallow copy, simply copying data pointers.
		OPAL_DECL virtual void OPAL_CALL operator=(const MeshShapeData& data)
		{
			mType = data.mType;
			offset = data.offset;
			material = data.material;
			contactGroup = data.contactGroup;
			vertexArray[0] = data.vertexArray[0];
			numVertices = data.numVertices;
			faceArray = data.faceArray;
			numFaces = data.numFaces;
		}

		/// Pointer to a 2-dimensional array of vertices.  For example, 
		/// access the ith vertex like this: 
		/// vertexArray[i][0] = 3.0; // x
		/// vertexArray[i][1] = 2.0; // y
		/// vertexArray[i][2] = 5.0; // z
		real* vertexArray[3];

		/// The number of vertices in the mesh.
		int numVertices;

		/// Pointer to an array of indices into the vertex array.  The size 
		/// of this array = 3 * the number of faces since each face will 
		/// need 3 different indices, one for each vertex.
		int* faceArray;

		/// The number of faces/triangles in the mesh.
		int numFaces;

	protected:

	private:
	};
}

#endif
