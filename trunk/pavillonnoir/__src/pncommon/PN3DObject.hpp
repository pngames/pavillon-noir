/*
 * PN3DObject.hpp
 * 
 * Description :
 * PN3DObject declaration
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 * This software has been written in EPITECH <http://www.epitech.net>
 * EPITECH is computer science school in Paris - FRANCE -
 * under the direction of flav <http://www.epita.fr/~flav>.
 * and Jerome Landrieu.
 *
 * This file is part of Pavillon Noir.
 *
 * Pavillon Noir is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Pavillon Noir is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Pavillon Noir; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef _PN3DOBJECT_HPP_
# define _PN3DOBJECT_HPP_

#include <vector>
#include <boost/thread/recursive_mutex.hpp>

#include "pnmath.h"

#include "PNObject.hpp"
#include "IPNAnimated.hpp"
#include "IPNXMLSerializable.hpp"

#include "PNPoint.hpp"
#include "PNQuatf.hpp"
#include "PNMatrixTR4f.hpp"
#include "PNVector3f.hpp"
#include "PNNormal3f.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DModel;
class PN3DMaterial;
class PNFace;
class PNPhysicalObject;

/// Base object for all object evolving in the scene
class PNAPI					PN3DObject : public PNObject, public IPNAnimated, public IPNXMLSerializable
{
public:
  boost::recursive_mutex	_mutex;

  /// lock 3dobject* (unlocked in and of the scope)
#define LOCK(obj)			boost::recursive_mutex::scoped_lock  sl(obj->_mutex)
#define LOCK_BEGIN(obj)		{ LOCK(obj)
#define LOCK_END(obj)		}

protected:
  ///object identifier
  std::string				_id;
public:
  inline void				setId(std::string id){_id = id;}
  inline std::string		getId(){return _id;}

  ///////////////////////////////////////////////////////////////////////////

private:
  /// Rotation axis activated
  typedef enum
  {
	RACTIVATE_NONE			= 0x000000,			/// Activate none
	RACTIVATE_PITCH			= 0x000001,			/// Activate x axis rotations
	RACTIVATE_YAW			= 0x000001 << 1,	/// Activate y axis rotations
	RACTIVATE_ROLL			= 0x000001 << 2,	/// Activate z axis rotations
	RACTIVATE_ALL			= RACTIVATE_PITCH | RACTIVATE_YAW | RACTIVATE_ROLL,	/// Activate all axis rotations
  }							rotActivation;

  /// Return bit mask indicate in witch axis do the 3D object rotate
  pnuint					getRotActivation();
  /// Set bit mask indicate in witch axis do the 3D object rotate
  void						getRotActivation(pnuint mstate);

protected:
  /// Bit mask indicate in witch axis do the 3D object rotate
  pnuint					_rotActivation;
  
  //////////////////////////////////////////////////////////////////////////

public:
  /// Sub Objects to render
  typedef enum
  {
	RENDER_MODEL			= 0x000001,			/// Render 3D object model
	RENDER_MATERIALS		= 0x000001 << 1,	/// Render 3D object materials (need RENDER_MODEL)
	RENDER_PHYSICAL			= 0x000001 << 2		/// Render 3D physical object
  }							rendermode;

  //////////////////////////////////////////////////////////////////////////
  
public:
  /// Translation and rotation states
  typedef enum
  {
	STATE_T_RIGHT			= 0x000001,			/// Translate to the right
	STATE_T_LEFT			= 0x000001 << 1,	/// Translate to the left
	STATE_T_TOP				= 0x000001 << 2,	/// Translate to the top
	STATE_T_BACK			= 0x000001 << 3,	/// Translate to the back
	STATE_T_FORWARD			= 0x000001 << 4,	/// Translate to the forward
	STATE_T_BACKWARD		= 0x000001 << 5,	/// Translate to the backward
	STATE_R_RIGHT			= 0x000001 << 6,	/// Rotate to the right
	STATE_R_LEFT			= 0x000001 << 7,	/// Rotate to the left
	STATE_R_TOP				= 0x000001 << 8,	/// Rotate to the top
	STATE_R_BACK			= 0x000001 << 9,	/// Rotate to the back
	STATE_R_FORWARD			= 0x000001 << 10,	/// Rotate to the forward
	STATE_R_BACKWARD		= 0x000001 << 11,	/// Rotate to the backward
  }							movingState;

  /// Return bit mask indicate in witch moving states is the 3D object
  pnuint					getMovingState() const;
  /// Set bit mask indicate in witch moving states is the 3D object
  void						setMovingState(pnuint mstate);
  /// add bit mask indicate in witch moving states is the 3D object
  void						addMovingState(pnuint mstate);
  /// sub bit mask indicate in witch moving states is the 3D object
  void						subMovingState(pnuint mstate);
  /// Get the moving speed of 3D object
  pnfloat					getMovingSpeed() const;
  /// Set the moving speed of 3D object
  void						setMovingSpeed(pnfloat mspeed);
protected:
  /// Bit mask indicate in witch moving states is the 3D object
  pnuint					_movingState;

  //////////////////////////////////////////////////////////////////////////

public:
  /// Displacment and view mode
  typedef enum
  {
	MMODE_FREE,				        /// 3D object move freely
    MMODE_DISTANCE_LOCKED,		    /// 3D object alway try to be in front of _target
    MMODE_DISTANCE_ABS_LOCKED,	    /// 3D object alway in front of _target
	MMODE_VIEW_LOCKED,		        /// 3D object alway try to be in front of _target
	MMODE_VIEW_ABS_LOCKED,	        /// 3D object alway in front of _target
    MMODE_VIEW_DISTANCE_LOCKED,		/// 3D object alway try to be in front of _target
    MMODE_VIEW_DISTANCE_ABS_LOCKED, /// 3D object alway in front of _target
	NB_MMODE				        /// number of moving modes in 3DObject
  }			  				        movingmode;

  /// Return displacement mode of 3D object (free, locked, ...)
  movingmode				getMovingMode() const;
  /// Set displacement mode of 3D object (free, locked, ...)
  void						setMovingMode(movingmode mmode);
protected:
  /// Displacement mode of 3D object (free, locked, ...)
  movingmode				_movingMode;

  //////////////////////////////////////////////////////////////////////////

public:
  /// Type of the 3d object
  typedef enum
  {
	OBJTYPE_3DOBJ,			/// Simple 3D object
	OBJTYPE_3DSKELETONOBJ,	/// 3D object with skeleton and skeleton animations
	OBJTYPE_WAYPOINT,		/// Way point used for IA graphs
	OBJTYPE_GROUND,			/// Ground partitioned for optimization and static
	OBJTYPE_CAMERA,			/// A camera
	OBJTYPE_CHARACTER,		/// Game character
	NB_OBJTYPE 
  }							objType;

protected:
  /// Type of the 3d object
  objType					_objType;

  //////////////////////////////////////////////////////////////////////////

public:
  /// Indicate witch direction is 3D object front
  PNNormal3f				_frontDirection;
  /// Indicate witch direction is 3D object right
  PNNormal3f				_rightDirection;
  /// Indicate witch direction is 3D object top
  PNNormal3f				_topDirection;

  /// Return 3d object front direction
  const PNNormal3f&			getFrontDirection() const;
  /// Return 3d object right direction
  const PNNormal3f&			getRightDirection() const;
  /// Return 3d object top direction
  const PNNormal3f&			getTopDirection() const;

  //////////////////////////////////////////////////////////////////////////
 
protected:
  /// Sub Objects to render
  pnuint					_renderMode;

  /// Translation and rotation speed
  pnfloat					_movingSpeed;
protected:
  /// Parse XML Model node
  pnint						_parseModel(xmlNode* node);
  /// Parse XML Materials node
  pnint						_parseMaterials(xmlNode* node);

  /// Write in model node content to out stream
  virtual pnint				_serializeContent(std::ostream& o);
public:
  /// List of materials associated with 3d object
  typedef std::vector<PN3DMaterial*>	VectorMaterial;
protected:
  /// Other 3DObject targeted used for locked displacement and other things like that
  PN3DObject*				_target;
  pnfloat					_targetDistance;
  PNNormal3f				_targetDirection;
  PNNormal3f				_rightTargetDirection;
protected:
  /// Represent object in graphic world
  PN3DModel*				_model;
  /// Materials list associated with this object
  VectorMaterial			_materials;

  /// Represent object in physic world
  PNPhysicalObject*			_physicalObject;

  /// Object position in 3D world
  PNPoint					_coord;
  /// Define object orientation
  PNQuatf					_orient;
  
  PNVector3f				_direct;

  /// Current update translation of 3d object
  PNVector3f				_updateTranslation;

public:
  /// Default constructor for PN3DObject.
  PN3DObject();
  /// Destructor for PN3DObject.
  virtual ~PN3DObject();

  //////////////////////////////////////////////////////////////////////////
  // PNObject

  /// Parse XML root node
  virtual pnint					unserializeFromXML(xmlNode* node);

  /// Save 3DObject into XML file
  virtual pnint					serializeInXML(std::ostream& o, bool header);

  //////////////////////////////////////////////////////////////////////////
  
public:
  /// Return 3D object coordinate in 3D scene
  virtual const PNPoint&		getCoord() const;
  /// Return 3D object x coordinate in 3D scene
  virtual pnfloat				getX() const;
  /// Return 3D object y coordinate in 3D scene
  virtual pnfloat				getY() const;
  /// Return 3D object z coordinate in 3D scene
  virtual pnfloat				getZ() const;

  /// Set 3D object coordinate in 3D scene
  virtual void					setCoord(const PNPoint& coord);
  /// Set 3D object coordinate in 3D scene
  virtual void					setCoord(pnfloat x, pnfloat y, pnfloat z);

  /// Return 3D object center coordinate relive to his coordinate
  virtual const PNPoint&		getCenter() const;

  /// Translate relative to object coordinate
  virtual void					move(PNPoint& coord);
  /// Translate on x relative to object coordinate
  virtual void					moveX(pnfloat x);
  /// Translate on y relative to object coordinate
  virtual void					moveY(pnfloat y);
  /// Translate on z relative to object coordinate
  virtual void					moveZ(pnfloat z);

  /// Return current update translation object
  virtual const PNVector3f&		getUpdateTranslation() const;
  /// Set current update translation object
  virtual void					setUpdateTranslation(const PNVector3f& translation);

  //////////////////////////////////////////////////////////////////////////

  /// Return 3D object orientation in quaternion
  virtual const PNQuatf&		getOrient() const;
  /// Set 3D object orientation in quaternion
  virtual void					setOrient(const PNQuatf& orient);
  /// Set 3D object orientation in quaternion
  virtual void					setOrient(pnfloat x, pnfloat y, pnfloat z, pnfloat w);

  /// Get moving direction of 3d object
  virtual const PNVector3f&		getDirect() const;
  /// Set moving direction of 3d object
  virtual void					setDirect(const PNVector3f& direct);
  /// Set moving direction of 3d object
  virtual void					setDirect(pnfloat x, pnfloat y, pnfloat z);

  /// Rotate around right normale (x)
  virtual void					rotatePitchRadians(pnfloat pitch);
  /// Rotate around top normale (y)
  virtual void					rotateYawRadians(pnfloat yaw);
  /// Rotate around front normale (z)
  virtual void					rotateRollRadians(pnfloat roll);
  /// Rotate relative to actual rotation
  virtual void					rotatePYRAxisRadians(const PNVector3f& axis, pnfloat phi);

  /// Rotate around X axis
  virtual void					rotateXRadians(pnfloat x);
  /// Rotate around Y axis
  virtual void					rotateYRadians(pnfloat y);
  /// Rotate around Z axis
  virtual void					rotateZRadians(pnfloat z);
  /// Rotate around "axis" axis
  virtual void					rotateAxisRadians(const PNVector3f& axis, pnfloat phi);

  //////////////////////////////////////////////////////////////////////////

  /// Return 3D object type
  virtual objType				getObjType() const;

  //////////////////////////////////////////////////////////////////////////
  
  /// Retrieve number of vertex owned by 3d object
  virtual pnuint				getNbVertexComputed();

  /// Fill buffer from step with vertices owned by 3d object
  virtual pnuint				computeVertex(pnfloat* buffer, pnuint step = 0);
  /// Fill buffer from step with normals owned by 3d object
  virtual pnuint				computeNormales(pnfloat* buffer, pnuint step = 0);
  /// Fill buffer from step with textures coordinates owned by 3d object
  virtual pnuint				computeTextCoord(pnfloat* buffer, pnuint step = 0);
  /// Fill buffer from step with colors owned by 3d object
  virtual pnuint				computeColors(pnfloat* buffer, pnuint step = 0);

  /// Retrieve number of face owned by 3d object
  virtual pnuint				getNbFacesComputed();

  /// Fill buffer from step with faces owned by 3d object
  virtual pnuint				computeFaces(PNFace* faces, pnuint step = 0);

  //////////////////////////////////////////////////////////////////////////
  
  /// Set 3d object target and 3D object distance
  void							setTarget(PN3DObject* obj, pnfloat distance = -1.0f);
  /// Set Distance to the target
  void							setTargetDistance(pnfloat distance);
  /// Set direction in witch 3D object look the target
  void							setTargetDirection(const PNNormal3f& vec);
  /// Retrieve 3d object target
  PN3DObject					*getTarget() const;

  //////////////////////////////////////////////////////////////////////////

  /// Retrieve model of 3d object
  PN3DModel*					get3DModel() const;
  /// Set the model of 3d object
  void							set3DModel(PN3DModel* model);

  /// Retrieve materials list of 3d object
  const VectorMaterial&			getMaterials() const;

  /// Retrieve physical object of 3d object
  PNPhysicalObject*				getPhysicalObject() const;
  /// Set the physical object of 3d object
  bool							setPhysicalObject(PNPhysicalObject* physicalObject);

  //////////////////////////////////////////////////////////////////////////

  /// Set render mode (model, materials) bit mask
  void							setRenderMode(pnuint mode);
  /// Return render mode bit mask
  pnint							getRenderMode() const;

  /// Update object informations
  virtual void					update(pnuint deltaTime);
  /// Update object position
  virtual void					updateTranslation(float step);
  /// Update object orientation
  virtual void					updateRotation(float step);

  /// Render object using PNRendererInterface
  virtual void					render();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PN3DOBJECT_HPP_*/
