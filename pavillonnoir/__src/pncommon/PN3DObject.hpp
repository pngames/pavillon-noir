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

//////////////////////////////////////////////////////////////////////////

#include "pnmath.h"

#include "PNPoint3f.hpp"
#include "PNQuatf.hpp"
#include "PNVector3f.hpp"
#include "PNNormal3f.hpp"

//////////////////////////////////////////////////////////////////////////

#include "PNLockableObject.hpp"
#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DModel;
class PN3DMaterial;
class PNPhysicalObject;
class PNFace;

/// Base object for all object evolving in the scene
class PNAPI							PN3DObject : public PNLockableObject, public IPNXMLSerializable
{
protected:
  ///object identifier
  std::string						_id;
public:
  void								setId(const std::string& id);
  const std::string&				getId() const;


  ///////////////////////////////////////////////////////////////////////////
private:
  /// Rotation axis activated
  typedef enum
  {
	RACTIVATE_NONE					= 0x000000,			/// Activate none
	RACTIVATE_PITCH					= 0x000001,			/// Activate x axis rotations
	RACTIVATE_YAW					= 0x000001 << 1,	/// Activate y axis rotations
	RACTIVATE_ROLL					= 0x000001 << 2,	/// Activate z axis rotations
	RACTIVATE_ALL					= RACTIVATE_PITCH | RACTIVATE_YAW | RACTIVATE_ROLL,	/// Activate all axis rotations
  }									rotActivation;

  /// Return bit mask indicate in witch axis do the 3D object rotate
  pnuint							getRotActivation();
  /// Set bit mask indicate in witch axis do the 3D object rotate
  void								getRotActivation(pnuint mstate);

protected:
  /// Bit mask indicate in witch axis do the 3D object rotate
  pnuint							_rotActivation;
  
  //////////////////////////////////////////////////////////////////////////

public:
  /// Sub Objects to render
  typedef enum
  {
	RENDER_DIRECTIONS				= 0x000001,			/// Render 3D object axis
	RENDER_MODEL					= 0x000001 << 1,	/// Render 3D object model
	RENDER_MATERIALS				= 0x000001 << 2,	/// Render 3D object materials (need RENDER_MODEL)
	RENDER_PHYSICAL					= 0x000001 << 3,	/// Render 3D physical object
	RENDER_LAST						= 0x000001 << 4
  }									rendermode;

  /// Set render mode (model, materials) bit mask
  void								setRenderMode(pnuint mode);
  /// Return render mode bit mask
  pnint								getRenderMode() const;

  void								addRenderMode(pnuint mode);
  void								subRenderMode(pnuint mode);

  //////////////////////////////////////////////////////////////////////////
  
public:
  /// Translation and rotation states
  typedef enum
  {
	STATE_NONE,											/// Do nothing
	STATE_T_RIGHT					= 0x000001,			/// Translate to the right
	STATE_T_LEFT					= 0x000001 << 1,	/// Translate to the left
	STATE_T_TOP						= 0x000001 << 2,	/// Translate to the top
	STATE_T_BACK					= 0x000001 << 3,	/// Translate to the back
	STATE_T_FORWARD					= 0x000001 << 4,	/// Translate to the forward
	STATE_T_BACKWARD				= 0x000001 << 5,	/// Translate to the backward
	STATE_R_RIGHT					= 0x000001 << 6,	/// Rotate to the right
	STATE_R_LEFT					= 0x000001 << 7,	/// Rotate to the left
	STATE_R_TOP						= 0x000001 << 8,	/// Rotate to the top
	STATE_R_BACK					= 0x000001 << 9,	/// Rotate to the back
	STATE_R_FORWARD					= 0x000001 << 10,	/// Rotate to the forward
	STATE_R_BACKWARD				= 0x000001 << 11,	/// Rotate to the backward

	STATE_ALL_T						= STATE_T_RIGHT | STATE_T_LEFT | STATE_T_TOP | STATE_T_BACK | STATE_T_FORWARD | STATE_T_BACKWARD,
	STATE_ALL_R						= STATE_R_RIGHT | STATE_R_LEFT | STATE_R_TOP | STATE_R_BACK | STATE_R_FORWARD | STATE_R_BACKWARD
  }									movingState;

  /// Return bit mask indicate in witch moving states is the 3D object
  pnuint							getMovingState() const;
  /// Set bit mask indicate in witch moving states is the 3D object
  void								setMovingState(pnuint mstate);
  /// add bit mask indicate in witch moving states is the 3D object
  void								addMovingState(pnuint mstate);
  /// sub bit mask indicate in witch moving states is the 3D object
  void								subMovingState(pnuint mstate);
  /// test bit mask indicate in witch moving states is the 3D object
  pnbool							testMovingState(pnuint mstate);
  /// Get the moving speed of 3D object
  pnfloat							getMovingSpeed() const;
  /// Set the moving speed of 3D object
  void								setMovingSpeed(pnfloat mspeed);
  /// Get the rotating Yaw speed of 3D object
  pnfloat							getRotatingYawSpeed() const;
  /// Set the rotating Yaw speed of 3D object
  void								setRotatingYawSpeed(pnfloat speed);
  /// Get the rotating Pitch speed of 3D object
  pnfloat							getRotatingPitchSpeed() const;
  /// Set the rotating Pitch speed of 3D object
  void								setRotatingPitchSpeed(pnfloat speed);
  /// Get the rotating Roll speed of 3D object
  pnfloat							getRotatingRollSpeed() const;
  /// Set the rotating Roll of 3D object
  void								setRotatingRollSpeed(pnfloat speed);
protected:
  /// Bit mask indicate in witch moving states is the 3D object
  pnuint							_movingState;

  //////////////////////////////////////////////////////////////////////////

public:
  /// Displacement and view mode
  typedef enum
  {
	TMODE_FREE						= 0x000000,	  		/// 3D object move freely

	TMODE_POSITION_LOCKED			= 0x000001 << 0,	/// 3D object alway try to be in same relative position from target
	TMODE_POSITION_ABS_LOCKED		= 0x000001 << 1,	/// 3D object alway in same relative position from target
    TMODE_DISTANCE_LOCKED			= 0x000001 << 2,	/// 3D object alway try to be at _targetDistance distance from the target
    TMODE_DISTANCE_ABS_LOCKED		= 0x000001 << 3,	/// 3D object alway at _targetDistance distance from the target

	TMODE_ORIENTATION_LOCKED		= 0x000001 << 4,	/// 3D object alway try to be in _targetOrientation orientation
	TMODE_ORIENTATION_ABS_LOCKED	= 0x000001 << 5,	/// 3D object alway in _targetOrientation orientation
	TMODE_VIEW_LOCKED				= 0x000001 << 6,	/// 3D object alway try to be in _targetDirection alignment of _target
	TMODE_VIEW_ABS_LOCKED			= 0x000001 << 7,	/// 3D object alway in _targetDirection alignment of _target

    TMODE_VIEW_DISTANCE_LOCKED		= TMODE_DISTANCE_LOCKED | TMODE_VIEW_LOCKED,			/// TMODE_DISTANCE_LOCKED + TMODE_VIEW_LOCKED
    TMODE_VIEW_DISTANCE_ABS_LOCKED	= TMODE_VIEW_ABS_LOCKED | TMODE_DISTANCE_ABS_LOCKED,	/// TMODE_DISTANCE_ABS_LOCKED + TMODE_VIEW_ABS_LOCKED
  }		  							targetmode;

  /// Return displacement mode of 3D object (free, locked, ...)
  pnuint							getTargetMode() const;
  /// Set displacement mode of 3D object (free, locked, ...)
  void								setTargetMode(pnuint tmode);
  /// Add bit mask indicate in witch moving mode is the 3D object
  void								addTargetMode(pnuint tmode);
  /// Sub bit mask indicate in witch moving mode is the 3D object
  void								subTargetMode(pnuint tmode);
protected:
  /// Displacement mode of 3D object (free, locked, ...)
  pnuint							_targetMode;
protected:
  /// Other 3DObject targeted used for locked displacement and other things like that

  /// Object to follow
  PN3DObject*						_positionTarget;
  /// Object bone to follow
  std::string						_positionBoneTarget;
  /// Object to look
  PN3DObject*						_viewTarget;
  /// Object bone to look
  std::string						_viewBoneTarget;

  /// _positionTarget relative position
  PNPoint3f							_targetPosition;
  /// _positionTarget relative distance
  pnfloat							_targetDistance;
  /// _viewTarget relative orientation
  PNQuatf							_targetOrientation;
  /// _viewTarget front direction
  PNNormal3f						_targetDirection;
  /// _viewTarget right direction
  PNNormal3f						_rightTargetDirection;

  //////////////////////////////////////////////////////////////////////////

public:
  /// Set 3d object target and 3D object distance
  void								setTarget(PN3DObject* obj);
  
  /// Retrieve 3d object position target
  PN3DObject*						getPositionTarget() const;
  /// Retrieve 3d object position target bone
  const std::string&				getPositionBoneTarget() const;
  /// Retrieve 3d object position coordinate
  PNPoint3f							getPositionTargetCoord() const;
  /// Retrieve 3d object position orientation
  PNQuatf							getPositionTargetOrient() const;

  /// Change 3d object position target
  void								setPositionTarget(PN3DObject* ptarget);
  /// Change 3d object position target bone
  void								setPositionBoneTarget(const std::string& pbtarget);

  /// Retrieve 3d object view target
  PN3DObject*						getViewTarget() const;
  /// Retrieve 3d object view target bone
  const std::string&				getViewBoneTarget() const;
  /// Retrieve 3d object position coordinate
  virtual PNPoint3f					getViewTargetCoord() const;
  /// Retrieve 3d object position orientation
  virtual PNQuatf					getViewTargetOrient() const;

  /// Change 3d object view target
  void								setViewTarget(PN3DObject* vtarget);
  /// Change 3d object view target bone
  void								setViewBoneTarget(const std::string& vbtarget);

  /// Set Position depending on the target
  void								setTargetPosition(pnfloat x, pnfloat y, pnfloat z);
  /// Set Distance to the target
  void								setTargetDistance(pnfloat distance);
  /// Set Direction in witch 3D object look to the target
  void								setTargetDirection(const PNNormal3f& vec);
  /// Set Orientation depending on the target
  void								setTargetOrientation(const PNQuatf& quat);
  // Sets View & Orient Target to NULL
  void								unsetTarget();
  //////////////////////////////////////////////////////////////////////////

public:
  /// Type of the 3d object
  typedef enum
  {
	OBJTYPE_3DOBJ,					/// Simple 3D object
	OBJTYPE_3DSKELETONOBJ,			/// 3D object with skeleton and skeleton animations
	OBJTYPE_WAYPOINT,				/// Way point used for IA graphs
	OBJTYPE_GROUND,					/// Ground partitioned for optimization and static
	OBJTYPE_CAMERA,					/// A camera
	OBJTYPE_CHARACTER,				/// Game character
	NB_OBJTYPE 
  }									objType;

protected:
  /// Type of the 3d object
  objType							_objType;

  //////////////////////////////////////////////////////////////////////////

public:
  /// Indicate witch direction is 3D object front
  PNNormal3f						_frontDirection;
  /// Indicate witch direction is 3D object right
  PNNormal3f						_rightDirection;
  /// Indicate witch direction is 3D object top
  PNNormal3f						_topDirection;

  /// Return 3d object front direction
  const PNNormal3f&					getFrontDirection() const;
  /// Return 3d object right direction
  const PNNormal3f&					getRightDirection() const;
  /// Return 3d object top direction
  const PNNormal3f&					getTopDirection() const;

  //////////////////////////////////////////////////////////////////////////
 
protected:
  /// Sub Objects to render
  pnuint							_renderMode;

  /// Translation and rotation speed
  pnfloat							_movingSpeed;
  pnfloat							_rotatingYawSpeed;
  pnfloat							_rotatingPitchSpeed;
  pnfloat							_rotatingRollSpeed;
public:
  /// List of materials associated with 3d object
  typedef std::vector<PN3DMaterial*>	VectorMaterial;
protected:
  /// Represent object in graphic world
  PN3DModel*						_model;
  /// Materials list associated with this object
  VectorMaterial					_materials;

  /// Represent object in physic world
  PNPhysicalObject*					_physicalObject;

  /// Object position in 3D world
  PNPoint3f							_coord;
  /// Define object orientation
  PNQuatf							_orient;

  /// Current update translation of 3d object
  PNVector3f						_updateTranslation;
  /// Last update translation of 3d object
  PNVector3f						_lastUpdateTranslation;

public:
  /// Default constructor for PN3DObject.
  PN3DObject();
  /// Destructor for PN3DObject.
  virtual ~PN3DObject();

protected:
  /// Parse XML Model node
  pnint								_parseModel(xmlNode* node);
  /// Parse XML Materials node
  pnint								_parseMaterials(xmlNode* node);
  /// Parse XML Physics node
  pnint								_parsePhysics(xmlNode* node);
  /// Parse XML PNO internal node
  virtual pnint						_unserializeNode(xmlNode* node);

  /// Write in model node content to out stream
  virtual pnint						_serializeContent(xmlNode* node);

  //////////////////////////////////////////////////////////////////////////
  // PNXMLSERIALIZABLE

  virtual const std::string&		getDTD() const;
  virtual const std::string&		getDTDName() const;
  virtual const std::string&		getRootNodeName() const;

public:
  /// Parse XML root node
  virtual pnint						unserializeFromXML(xmlNode* node);

  /// Save 3DObject into XML file
  virtual pnint						serializeInXML(xmlNode* node, pnbool isroot = false);

  //////////////////////////////////////////////////////////////////////////
  
public:
  /// Return 3D object coordinate in 3D scene
  virtual const PNPoint3f&			getCoord() const;
  /// Return 3D object x coordinate in 3D scene
  virtual pnfloat					getX() const;
  /// Return 3D object y coordinate in 3D scene
  virtual pnfloat					getY() const;
  /// Return 3D object z coordinate in 3D scene
  virtual pnfloat					getZ() const;

  /// Set 3D object coordinate in 3D scene
  virtual void						setCoord(const PNPoint3f& coord);
  /// Set 3D object coordinate in 3D scene
  virtual void						setCoord(pnfloat x, pnfloat y, pnfloat z);

  /// Translate relative to object coordinate
  virtual void						move(PNPoint3f& coord);
  /// Translate on x relative to object coordinate
  virtual void						moveX(pnfloat x);
  /// Translate on y relative to object coordinate
  virtual void						moveY(pnfloat y);
  /// Translate on z relative to object coordinate
  virtual void						moveZ(pnfloat z);

  /// Return current update translation object
  virtual const PNVector3f&			getUpdateTranslation() const;
  /// Set current update translation object
  virtual void						setUpdateTranslation(const PNVector3f& translation);
  /// Return last update translation object
  virtual const PNVector3f&		getLastUpdateTranslation() const;

  //////////////////////////////////////////////////////////////////////////
  
  /// Return 3D object center coordinate relative to his coordinate
  const PNPoint3f&					getCenter() const;

  /// Return 3D object radius relative to his coordinate
  pnfloat							getRadius() const;

  //////////////////////////////////////////////////////////////////////////

  /// Return 3D object orientation in quaternion
  virtual const PNQuatf&			getOrient() const;
  /// Set 3D object orientation in quaternion
  virtual void						setOrient(const PNQuatf& orient);
  /// Set 3D object orientation in quaternion
  virtual void						setOrient(pnfloat x, pnfloat y, pnfloat z, pnfloat w);

  /// Rotate around right normale (x)
  virtual void						rotatePitchRadians(pnfloat pitch);
  /// Rotate around top normale (y)
  virtual void						rotateYawRadians(pnfloat yaw);
  /// Rotate around front normale (z)
  virtual void						rotateRollRadians(pnfloat roll);
  /// Rotate relative to actual rotation
  virtual void						rotatePYRAxisRadians(const PNVector3f& axis, pnfloat phi);

  /// Rotate around X axis
  virtual void						rotateXRadians(pnfloat x);
  /// Rotate around Y axis
  virtual void						rotateYRadians(pnfloat y);
  /// Rotate around Z axis
  virtual void						rotateZRadians(pnfloat z);
  /// Rotate around "axis" axis
  virtual void						rotateAxisRadians(const PNVector3f& axis, pnfloat phi);

  //////////////////////////////////////////////////////////////////////////

  /// Return 3D object type
  virtual objType					getObjType() const;

  //////////////////////////////////////////////////////////////////////////
  
  /// Retrieve number of vertex owned by 3d object
  virtual pnuint					getNbVertexComputed();

  /// Fill buffer from step with vertices owned by 3d object
  virtual pnuint					computeVertex(pnfloat* buffer, pnuint step = 0);
  /// Fill buffer from step with normals owned by 3d object
  virtual pnuint					computeNormales(pnfloat* buffer, pnuint step = 0);
  /// Fill buffer from step with textures coordinates owned by 3d object
  virtual pnuint					computeTextCoord(pnfloat* buffer, pnuint step = 0);
  /// Fill buffer from step with colors owned by 3d object
  virtual pnuint					computeColors(pnfloat* buffer, pnuint step = 0);

  /// Retrieve number of face owned by 3d object
  virtual pnuint					getNbFacesComputed();

  /// Fill buffer from step with faces owned by 3d object
  virtual pnuint					computeFaces(PNFace* faces, pnuint step = 0);

  //////////////////////////////////////////////////////////////////////////
  /// Get minimum x y z coordinate
  const PNPoint3f&					getMin() const;
  /// Get maximum x y z coordinate
  const PNPoint3f&					getMax() const;

  //////////////////////////////////////////////////////////////////////////
  // Visible wrapper

  void								setVisible(pnbool visible);
  bool								isVisible() const;

  //////////////////////////////////////////////////////////////////////////

  /// Retrieve model of 3d object
  PN3DModel*						get3DModel() const;
  /// Set the model of 3d object
  void								set3DModel(PN3DModel* model);

  /// Retrieve materials list of 3d object
  const VectorMaterial&				getMaterials() const;

  /// Retrieve physical object of 3d object
  PNPhysicalObject*					getPhysicalObject() const;
  /// Set the physical object of 3d object
  bool								setPhysicalObject(PNPhysicalObject* physicalObject);

  //////////////////////////////////////////////////////////////////////////

protected:
  pnbool							_updated;
  pnbool							_positionTargetUpdated;
  pnbool							_viewTargetUpdated;

public:
  void								prepareUpdate();

  pnbool							isUpdated();
  void								setUpdated();

  pnbool							isPositionTargetUpdated();
  void								setPositionTargetUpdated(pnbool updated);
  pnbool							isViewTargetUpdated();
  void								setViewTargetUpdated(pnbool updated);

  /// Update object informations
  virtual void						update(pnuint deltaTime);
  /// Update object position
  virtual void						updateTranslation(float step);
  /// Update object orientation
  virtual void						updateRotation(float step);

  /// Render object using PNRendererInterface
  virtual void						render();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PN3DOBJECT_HPP_*/

