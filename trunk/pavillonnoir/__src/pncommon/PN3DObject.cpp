/*
 * PN3DObject.cpp
 *
 * Description :
 * PN3DObject definition
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

#include <boost/filesystem/operations.hpp>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnmath.h"
#include "pnimport.h"
#include "pnrender.h"
#include "pnevent.h"
#include "pnresources.h"

#include "PN3DModel.hpp"
#include "PN3DMaterial.hpp"
#include "PN3DObject.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PN3DSkeleton.hpp"
#include "PNPhysicalObject.hpp"

#include "pno_format.h"

namespace fs = boost::filesystem;
using namespace PN;
using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

/*!
 * \brief
 * Default constructor for PN3DObject.
 * 
 * \see
 */
PN3DObject::PN3DObject()
{
  _id = "";

  _rotActivation = RACTIVATE_ALL;

  _model = NULL;
  _physicalObject = NULL;

  _orient.loadIdentity();
  _updateTranslation.setNull();

  _frontDirection.setArray(PNVector3f::NEGATIVE_UNIT_Z);
  _rightDirection.setArray(PNVector3f::UNIT_X);
  _topDirection.setArray(PNVector3f::UNIT_Y);

  _renderMode = RENDER_MODEL | RENDER_MATERIALS;
  _movingState = STATE_NONE;

  setTargetMode(TMODE_FREE);
  setTarget(NULL);

  setTargetPosition(0.0f, 0.0f, 0.0f);
  setTargetDistance(-1.0f);
  setTargetDirection(_frontDirection);
  _targetOrientation.loadIdentity();

  _movingSpeed = 1.0f;
  _rotatingYawSpeed = 1.0f;
  _rotatingPitchSpeed = 1.0f;
  _rotatingRollSpeed = 1.0f;

  _objType = OBJTYPE_3DOBJ;

  _startedEventType = PN_EVENT_OA_STARTED;
  _stopedEventType = PN_EVENT_OA_ENDED;
  _pausedEventType = PN_EVENT_OA_PAUSED;
}

/*!
* \brief
* Destructor for PN3DObject.
*
* \see
* 
*/
PN3DObject::~PN3DObject()
{  
}

//////////////////////////////////////////////////////////////////////////

void*
PN3DObject::lock()
{
  return new boost::recursive_mutex::scoped_lock(_mutex);
}

void
PN3DObject::unlock(void *m)
{
  boost::recursive_mutex::scoped_lock*	locker = (boost::recursive_mutex::scoped_lock*)m;

  delete locker;
}

//////////////////////////////////////////////////////////////////////////

pnint
PN3DObject::_parseMaterials(xmlNode* parent)
{
  _materials.clear();

  for (xmlNodePtr  node = parent->children; node != NULL; node = node->next)
  {
	if (node->type != XML_ELEMENT_NODE)
	  continue;

	xmlChar*		attr = xmlGetProp(node, (const xmlChar *)PNO_XMLPROP_PATH);

	PN3DMaterial*		material = NULL;

	if (attr != NULL)
	{
	  fs::path	  p(DEF::materialFilePath + (const char*)attr, fs::native);

	  material = (PN3DMaterial*)PNImportManager::getInstance()->import(p, PN_IMPORT_MATERIAL);
	}

	_materials.push_back(material);
  }

  return PNEC_SUCCESS;
}

pnint
PN3DObject::_parseModel(xmlNode* node)
{
  xmlChar*	  attr = NULL;

  _model = NULL;

  if ((attr = xmlGetProp(node, (const xmlChar *)PNO_XMLPROP_PATH)) != NULL)
  {
	fs::path p(DEF::modelFilePath + (const char*)attr, fs::native);

	if (fs::exists(p))
	  _model = (PN3DModel*)PNImportManager::getInstance()->import(p, PN_IMPORT_3DMODEL);

	if (_model == NULL)
	  return PNEC_LOADING_MODEL;
  }

  return PNEC_SUCCESS;
}

pnint
PN3DObject::_parsePhysics(xmlNode* node)
{
  xmlChar*	  attr = NULL;

  _physicalObject = NULL;

  if ((attr = xmlGetProp(node, (const xmlChar *)PNO_XMLPROP_PATH)) != NULL)
  {
	fs::path p(DEF::physicsFilePath + (const char*)attr, fs::native);

	if (fs::exists(p))
	  _physicalObject = (PNPhysicalObject*)PNImportManager::getInstance()->import(p, PN_IMPORT_PHYSICS, true);

	if (_physicalObject == NULL)
	  return PNEC_LOADING_PHYSICS;
  }

  return PNEC_SUCCESS;
}

pnint
PN3DObject::_unserializeNode(xmlNode* node)
{
  if (PNO_XMLNODE_LISTMATERIALS == (const char*)node->name)
	_parseMaterials(node);
  else if (PNO_XMLNODE_MODEL == (const char*)node->name)
	_parseModel(node);
  else if (PNO_XMLNODE_PHYSICS == (const char*)node->name)
	_parsePhysics(node);

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

const std::string&
PN3DObject::getDTD() const
{
  return PNO_XMLDTD;
}

const std::string&
PN3DObject::getDTDName() const
{
  return PNO_XMLDTD_NAME;
}

const std::string&
PN3DObject::getRootNodeName() const
{
  return PNO_XMLNODE_ROOT;
}

pnint
PN3DObject::unserializeFromXML(xmlNode* root)
{
  PNLOCK(this);

  _model = NULL;
  _materials.clear();

  //////////////////////////////////////////////////////////////////////////

  for (root = root->children ; root != NULL; root = root->next)
	_unserializeNode(root);

  return PNEC_SUCCESS;
}

pnint
PN3DObject::serializeInXML(xmlNode* node, pnbool isroot)
{
  xmlNode* root = node;

  if (isroot == false)
	root = xmlNewChild(node, NULL, BAD_CAST getRootNodeName().c_str(), NULL);

  _serializeContent(root);

  return PNEC_SUCCESS;
}

/**
* @brief		Save PN3DObject content to XML file
*
* @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCESS if succeed
*
* @see			pnGetErrorString
*/
pnint
PN3DObject::_serializeContent(xmlNode* root)
{
  xmlNode* node = NULL;

  if (_model != NULL && _model->getFile() != NULL)
  {
	node = xmlNewChild(root, NULL, BAD_CAST PNO_XMLNODE_MODEL.c_str(), NULL);
	xmlNewProp(node, BAD_CAST PNO_XMLPROP_PATH, BAD_CAST DEF::convertPath(DEF::modelFilePath, _model->getFile()->string()).c_str());
  }

  if (_materials.size() > 0)
  {
	root = xmlNewChild(root, NULL, BAD_CAST PNO_XMLNODE_LISTMATERIALS.c_str(), NULL);

	for (VectorMaterial::iterator it = _materials.begin(); it != _materials.end(); ++it)
	  if (*it != NULL && ((PN3DMaterial*)*it)->getFile() != NULL)
	  {
		node = xmlNewChild(root, NULL, BAD_CAST PNO_XMLNODE_MATERIAL.c_str(), NULL);
		xmlNewProp(node, BAD_CAST PNO_XMLPROP_PATH, BAD_CAST DEF::convertPath(DEF::materialFilePath, ((PN3DMaterial*)*it)->getFile()->string()).c_str());
	  }
  }

  return PNEC_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

const PNNormal3f&
PN3DObject::getFrontDirection() const
{
  return _frontDirection;
}

const PNNormal3f&
PN3DObject::getRightDirection() const
{
  return _rightDirection;
}

const PNNormal3f&
PN3DObject::getTopDirection() const
{
  return _topDirection;
}

//////////////////////////////////////////////////////////////////////////

const PNPoint&
PN3DObject::getCoord() const
{
  return _coord;
}

const PNPoint&
PN3DObject::getCenter() const
{
  return _model != NULL ? _model->getCenter() : PNPoint::ZERO;
}

const PNQuatf&
PN3DObject::getOrient() const
{
  return _orient;
}

const PNVector3f &
PN3DObject::getUpdateTranslation() const
{
  return _updateTranslation;
}

void
PN3DObject::setUpdateTranslation(const PNVector3f& translation)
{
  PNLOCK(this);

  _updateTranslation = translation;
}

pnfloat
PN3DObject::getX() const
{
  return _coord.x;
}

pnfloat
PN3DObject::getY() const
{
  return _coord.y;
}

pnfloat
PN3DObject::getZ() const
{
  return _coord.z;
}

PN3DObject::objType
PN3DObject::getObjType() const
{
  return _objType;
}

void
PN3DObject::setCoord(const PNPoint& coord)
{
  PNLOCK(this);

  _coord = coord;
}

void
PN3DObject::setCoord(pnfloat x, pnfloat y, pnfloat z)
{
  PNLOCK(this);

  _coord.x = x;
  _coord.y = y;
  _coord.z = z;
}

void
PN3DObject::setOrient(const PNQuatf& orient)
{
  PNLOCK(this);

  _orient = orient;
}

void
PN3DObject::setOrient(pnfloat x, pnfloat y, pnfloat z, pnfloat w)
{
  PNLOCK(this);

  _orient.x = x;
  _orient.y = y;
  _orient.z = z;
  _orient.w = w;
}

void
PN3DObject::move(PNPoint& coord)
{
  PNLOCK(this);

  _coord += coord;
}

void
PN3DObject::moveX(pnfloat x)
{
  PNLOCK(this);

  _coord.x += x;
}

void
PN3DObject::moveY(pnfloat y)
{
  PNLOCK(this);

  _coord.y += y;
}

void
PN3DObject::moveZ(pnfloat z)
{
  PNLOCK(this);

  _coord.z += z;
}

void
PN3DObject::rotatePitchRadians(pnfloat pitch)
{
  if (_rotActivation & RACTIVATE_PITCH)
	rotatePYRAxisRadians(getRightDirection().getVector(), pitch * _rotatingPitchSpeed);
}

void
PN3DObject::rotateYawRadians(pnfloat yaw)
{
  if (_rotActivation & RACTIVATE_YAW)
	rotatePYRAxisRadians(getTopDirection().getVector(), yaw * _rotatingYawSpeed);
}

void
PN3DObject::rotateRollRadians(pnfloat roll)
{
  if (_rotActivation & RACTIVATE_ROLL)
	rotatePYRAxisRadians(getFrontDirection().getVector(), roll * _rotatingRollSpeed);
}

void
PN3DObject::rotatePYRAxisRadians(const PNVector3f& axis, pnfloat phi)
{
  PNLOCK(this);

  PNQuatf rot(_orient * axis, phi);

  _orient = rot * _orient;
}

void
PN3DObject::rotateXRadians(pnfloat x)
{
  rotateAxisRadians(PNVector3f::UNIT_X, x * _rotatingPitchSpeed * _rotatingPitchSpeed);
}

void
PN3DObject::rotateYRadians(pnfloat y)
{
  rotateAxisRadians(PNVector3f::UNIT_Y, y * _rotatingYawSpeed * _rotatingYawSpeed);
}

void
PN3DObject::rotateZRadians(pnfloat z)
{
  rotateAxisRadians(PNVector3f::UNIT_Z, z * _rotatingRollSpeed * _rotatingRollSpeed);
}

void
PN3DObject::rotateAxisRadians(const PNVector3f& axis, pnfloat phi)
{
  PNLOCK(this);

  _orient = PNQuatf(axis, phi) * _orient;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PN3DObject::getMovingState() const
{
  return _movingState;
}

void
PN3DObject::setMovingState(pnuint mstate)
{
  PNLOCK(this);

  _movingState = mstate;
}

void
PN3DObject::addMovingState(pnuint mstate)
{
  PNLOCK(this);

  _movingState |= mstate;
}

void
PN3DObject::subMovingState(pnuint mstate)
{
  PNLOCK(this);

  _movingState &= ~mstate;
}

pnfloat
PN3DObject::getMovingSpeed() const
{
  return _movingSpeed;
}

void
PN3DObject::setMovingSpeed(pnfloat speed)
{
  PNLOCK(this);

  _movingSpeed = speed;
}

void
PN3DObject::setRotatingYawSpeed(pnfloat speed)
{
  PNLOCK(this);

  _rotatingYawSpeed = speed;
}

pnfloat
PN3DObject::getRotatingYawSpeed() const 
{
  return _rotatingYawSpeed;
}

void
PN3DObject::setRotatingPitchSpeed(pnfloat speed)
{
  PNLOCK(this);

  _rotatingPitchSpeed = speed;
}

pnfloat
PN3DObject::getRotatingPitchSpeed() const
{
  return _rotatingPitchSpeed;
}

void
PN3DObject::setRotatingRollSpeed(pnfloat speed)
{
  PNLOCK(this);

  _rotatingRollSpeed = speed;
}

pnfloat
PN3DObject::getRotatingRollSpeed() const
{
  return  _rotatingRollSpeed;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PN3DObject::getTargetMode() const
{
  return _targetMode;
}

void
PN3DObject::setTargetMode(pnuint tmode)
{
  PNLOCK(this);

  _targetMode = tmode;
}

/// Add bit mask indicate in witch moving mode is the 3D object
void
PN3DObject::addTargetMode(pnuint tmode)
{
  PNLOCK(this);

  _targetMode |= tmode;
}

/// Sub bit mask indicate in witch moving mode is the 3D object
void
PN3DObject::subTargetMode(pnuint tmode)
{
  PNLOCK(this);

  _targetMode &= ~tmode;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PN3DObject::getNbVertexComputed()
{
  PNLOCK(this);

  return _model->getNbVertexComputed();
}

pnuint
PN3DObject::computeVertex(pnfloat* buffer, pnuint step)
{
  PNLOCK(this);

  return _model->computeVertex(buffer, step);
}

pnuint
PN3DObject::computeNormales(pnfloat* buffer, pnuint step)
{
  PNLOCK(this);

  return _model->computeNormales(buffer, step);
}

pnuint
PN3DObject::computeTextCoord(pnfloat* buffer, pnuint step)
{
  PNLOCK(this);

  return _model->computeTextCoord(buffer, step);
}

pnuint
PN3DObject::computeColors(pnfloat* buffer, pnuint step)
{
  PNLOCK(this);

  return _model->computeColors(buffer, step);
}

pnuint
PN3DObject::getNbFacesComputed()
{
  PNLOCK(this);

  return _model->getNbFacesComputed();
}

pnuint
PN3DObject::computeFaces(PNFace* faces, pnuint step)
{
  PNLOCK(this);

  return _model->computeFaces(_materials, faces, step);
}

//////////////////////////////////////////////////////////////////////////

void
PN3DObject::setTarget(PN3DObject* obj)
{
  PNLOCK(this);

  setPositionTarget(obj);
  setViewTarget(obj);

  if (obj == NULL)
	setTargetMode(TMODE_FREE);
}

/// Retrieve 3d object position target
PN3DObject*
PN3DObject::getPositionTarget() const
{
  return _positionTarget;
}

/// Retrieve 3d object position target bone
const std::string&
PN3DObject::getPositionBoneTarget() const
{
  return _positionBoneTarget;
}

/// Retrieve 3d object position coordinate
PNPoint
PN3DObject::getPositionTargetCoord() const
{
  PNPoint coord  = _positionTarget->getCoord();

  if (_positionBoneTarget.empty())
	return coord;

  PN3DSkeletonObject* skobj = (PN3DSkeletonObject*)_positionTarget;

  const pnfloat*	  bcoord = skobj->getSkeleton()->getBoneCoords(_positionBoneTarget);

  if (bcoord == NULL)
	return coord;

  return coord + skobj->getOrient().multiply(bcoord);
}

/// Retrieve 3d object position orientation
PNQuatf
PN3DObject::getPositionTargetOrient() const
{
  PNQuatf orient = _positionTarget->getOrient();

  if (_positionBoneTarget.empty())
	return orient;

  PN3DSkeletonObject* skobj = (PN3DSkeletonObject*)_positionTarget;

  const PNQuatf*	  borient = skobj->getSkeleton()->getBoneOrientation(_positionBoneTarget);

  if (borient == NULL)
	return orient;

  return orient * *borient;
}

/// Change 3d object position target
void
PN3DObject::setPositionTarget(PN3DObject* ptarget)
{
  PNLOCK(this);

  _positionTarget = ptarget;

  if (_positionTarget == NULL || _positionTarget->getObjType() != PN3DObject::OBJTYPE_3DSKELETONOBJ)
	_positionBoneTarget.clear();
}

/// Change 3d object position target bone
void
PN3DObject::setPositionBoneTarget(const std::string& pbtarget)
{
  PNLOCK(this);

  if (_positionTarget->getObjType() == PN3DObject::OBJTYPE_3DSKELETONOBJ)
	_positionBoneTarget = pbtarget;
  else
	_positionBoneTarget.clear();
}

/// Retrieve 3d object view target
PN3DObject*
PN3DObject::getViewTarget() const
{
  return _viewTarget;
}

/// Retrieve 3d object view target bone
const std::string&
PN3DObject::getViewBoneTarget() const
{
  return _viewBoneTarget;
}

/// Retrieve 3d object position coordinate
PNPoint
PN3DObject::getViewTargetCoord() const
{
  PNPoint coord  = _viewTarget->getCoord();

  if (_viewBoneTarget.empty())
	return coord;

  PN3DSkeletonObject* skobj = (PN3DSkeletonObject*)_viewTarget;

  const pnfloat*	  bcoord = skobj->getSkeleton()->getBoneCoords(_viewBoneTarget);

  if (bcoord == NULL)
	return coord;

  return coord + skobj->getOrient().multiply(bcoord);
}

/// Retrieve 3d object position orientation
PNQuatf
PN3DObject::getViewTargetOrient() const
{
  PNQuatf orient = _viewTarget->getOrient();

  if (_viewBoneTarget.empty())
	return orient;

  PN3DSkeletonObject* skobj = (PN3DSkeletonObject*)_viewTarget;

  const PNQuatf*	  borient = skobj->getSkeleton()->getBoneOrientation(_viewBoneTarget);

  if (borient == NULL)
	return orient;

  return orient * *borient;
}

/// Change 3d object view target
void
PN3DObject::setViewTarget(PN3DObject* vtarget)
{
  PNLOCK(this);

  _viewTarget = vtarget;

  if (_viewTarget == NULL || _viewTarget->getObjType() != PN3DObject::OBJTYPE_3DSKELETONOBJ)
	_positionBoneTarget.clear();
}

/// Change 3d object view target bone
void
PN3DObject::setViewBoneTarget(const std::string& vbtarget)
{
  PNLOCK(this);

  if (_viewTarget->getObjType() == PN3DObject::OBJTYPE_3DSKELETONOBJ)
	_viewBoneTarget = vbtarget;
  else
	_viewBoneTarget.clear();
}

/// Set Position depending on the target
void
PN3DObject::setTargetPosition(pnfloat x, pnfloat y, pnfloat z)
{
  PNLOCK(this);

  _targetPosition.x = x;
  _targetPosition.y = y;
  _targetPosition.z = z;
}

/// Set Distance to the target
void
PN3DObject::setTargetDistance(pnfloat distance)
{
  PNLOCK(this);

  _targetDistance = distance;
}

/// Set Direction in witch 3D object look to the target
void
PN3DObject::setTargetDirection(const PNNormal3f& n)
{
  PNLOCK(this);

  _targetDirection = n;

  PNVector3f  vec;
  vec.crossProduct(_targetDirection.getVector(), PNVector3f::UNIT_Y);
  _rightTargetDirection.setCrd(vec.x,vec.y, vec.z);
  //_rightTargetDirection.crossProduct(PNVector3f::UNIT_Y, _targetDirection);
}

/// Set Orientation depending on the target
void
PN3DObject::setTargetOrientation(const PNQuatf& quat)
{
  PNLOCK(this);

  _targetOrientation = quat;
}
//////////////////////////////////////////////////////////////////////////
/// Get minimum x y z coordinate
const PNPoint&	PN3DObject::getMin() const 
{
  return _model->getMin();
}
/// Get maximum x y z coordinate
const PNPoint&	PN3DObject::getMax() const
{
  return  _model->getMax();
}

//////////////////////////////////////////////////////////////////////////

PN3DModel*
PN3DObject::get3DModel() const
{
  return _model;
}

void
PN3DObject::set3DModel(PN3DModel* model)
{
  PNLOCK(this);

  _model = model;
}

const PN3DObject::VectorMaterial&
PN3DObject::getMaterials() const
{
  return _materials;
}

PNPhysicalObject* 
PN3DObject::getPhysicalObject() const
{
  return _physicalObject;
}

bool 
PN3DObject::setPhysicalObject(PNPhysicalObject* physical_object)
{
  PNLOCK(this);

  _physicalObject = physical_object;
  return true;
}


//////////////////////////////////////////////////////////////////////////

/**
* Updates the current translation of the object
* regarding the spent time and its state. This method has
* no side effect.
*/
void
PN3DObject::updateTranslation(pnfloat deltaTime)
{
  PNLOCK(this);

  pnfloat step = deltaTime * _movingSpeed;

  _updateTranslation.setNull();

  //////////////////////////////////////////////////////////////////////////
  // targetPosition

  if (_targetMode & (TMODE_POSITION_ABS_LOCKED | TMODE_POSITION_ABS_LOCKED))
  {
	_updateTranslation = getPositionTargetCoord();
	_updateTranslation += getPositionTargetOrient() * _targetPosition;
	_updateTranslation -= getCoord();

	return ;
  }

  //////////////////////////////////////////////////////////////////////////
  // NORMAL

  if (_movingState != 0)
  {
	if (_movingState & STATE_T_RIGHT)
	  _updateTranslation += getRightDirection().getVector();
	if (_movingState & STATE_T_LEFT)
	  _updateTranslation -= getRightDirection().getVector();
	if (_movingState & STATE_T_TOP)
	  _updateTranslation += getTopDirection().getVector();
	if (_movingState & STATE_T_BACK)
	  _updateTranslation -= getTopDirection().getVector();
	if (_movingState & STATE_T_FORWARD)
	  _updateTranslation += getFrontDirection().getVector();
	if (_movingState & STATE_T_BACKWARD)
	  _updateTranslation -= getFrontDirection().getVector();

	_updateTranslation *= step;
  }

  //std::cout << _translation << " --> ";

  _updateTranslation = _orient * _updateTranslation;

  //////////////////////////////////////////////////////////////////////////
  // targetDistance

  if (_targetDistance > 0.0f &&
	(_targetMode & (TMODE_DISTANCE_ABS_LOCKED | TMODE_DISTANCE_LOCKED)))
  {
	PNVector3f	targetVector = _positionTarget->getCoord();
	targetVector -= _coord;

	pnfloat norm = targetVector.getNorm();
	targetVector.setNorm(norm - _targetDistance);

	_updateTranslation += targetVector;
  }

  return;
}

void
PN3DObject::updateRotation(pnfloat deltaTime)
{
  PNLOCK(this);

  pnfloat	xphi = (pnfloat)DEGREE_TO_RADIAN((_rotatingPitchSpeed));
  pnfloat	yphi = (pnfloat)DEGREE_TO_RADIAN((_rotatingYawSpeed));
  pnfloat	zphi = (pnfloat)DEGREE_TO_RADIAN((_rotatingRollSpeed));

  if (_targetMode & (TMODE_ORIENTATION_ABS_LOCKED | TMODE_ORIENTATION_LOCKED))
  {
	_orient = getViewTargetOrient() * _targetOrientation;
  }
  else if (_targetMode & (TMODE_VIEW_ABS_LOCKED | TMODE_VIEW_LOCKED))
  {
	PNVector3f	targetVector = getViewTargetCoord();
	targetVector -= _coord;

	pnfloat	norm = sqrtf(SQNBR(targetVector.x) + SQNBR(targetVector.z));
	double	ps = (_targetDirection.getX() * targetVector.x / norm) + (_targetDirection.getZ() * targetVector.z / norm);
	double	pcy = (_targetDirection.getX() * targetVector.z / norm) - (_targetDirection.getZ() * targetVector.x / norm);

	// The test is for handle precision problems
	pnfloat yangle = ABS(ps) >= 1.0f ? 0.0f : acosf((float)ps);
	yangle = pcy > 0 ? -yangle : yangle;

	//////////////////////////////////////////////////////////////////////////

	targetVector = PNQuatf(PNVector3f::UNIT_Y, -yangle) * targetVector;

	norm = targetVector.getNorm();
	ps = (_targetDirection.getX() * targetVector.x / norm ) + (_targetDirection.getY() * targetVector.y / norm) + (_targetDirection.getZ() * targetVector.z / norm);

	PNVector3f	pc;
	pc.crossProduct(_targetDirection.getVector(), targetVector);

	// The test is for handle precision problems
	pnfloat xangle = ABS(ps) >= 1.0f ? 0.0f : acosf((float)ABS(ps));
	if (pc.scalarProduct(_rightTargetDirection.getVector()) < 0)
	  xangle = -xangle;

	_orient.fromAxisRadians(_rightTargetDirection.getVector(), xangle);
	_orient = PNQuatf(PNVector3f::UNIT_Y, yangle) * _orient;
  }
  else if (_targetMode & TMODE_VIEW_LOCKED)
  {
	/*PNVector3f	targetVector = _target->getCoord();
	targetVector -= _coord;

	pnfloat	norm = sqrtf(SQNBR(targetVector.x) + SQNBR(targetVector.z));
	double	ps = (_targetDirection.x * targetVector.x / norm) + (_targetDirection.z * targetVector.z / norm);

	pnfloat yangle = (pnfloat)acos(ps);
	yangle = targetVector.x > 0 ? -yangle : yangle;

	//////////////////////////////////////////////////////////////////////////

	targetVector = PNQuatf(PNVector3f::UNIT_Y, -yangle) * targetVector;

	norm = sqrtf(SQNBR(targetVector.y) + SQNBR(targetVector.z));
	ps = (_targetDirection.y * targetVector.y / norm) + (_targetDirection.z * targetVector.z / norm);

	pnfloat xangle = (pnfloat)acos(ABS(ps));
	xangle = targetVector.y > 0 ? xangle : -xangle;

	_orient.fromAxisRadians(PNVector3f::UNIT_X, xangle);
	_orient = PNQuatf(PNVector3f::UNIT_Y, yangle) * _orient;*/
  }
  else
  {
	PNVector3f  axis(PNVector3f::ZERO);

	if (_movingState & STATE_R_TOP)
	  axis.x += xphi;
	if (_movingState & STATE_R_BACK)
	  axis.x -= xphi;
	if (_movingState & STATE_R_RIGHT)
	  axis.y -= yphi;
	if (_movingState & STATE_R_LEFT)
	  axis.y += yphi;
	if (_movingState & STATE_R_FORWARD)
	  axis.z += zphi;
	if (_movingState & STATE_R_BACKWARD)
	  axis.z -= zphi;

	if (axis.x != 0)
	  rotatePitchRadians(axis.x);
	if (axis.y != 0)
	  rotateYawRadians(axis.y);
	if (axis.z != 0)
	  rotateRollRadians(axis.z);
  }
}

/**
* updates the position of the object regarding
* its translation vector.
*/
void
PN3DObject::update(pnuint deltaTime)
{
  PNLOCK(this);

  pnuint  tick = PNRendererInterface::getInstance()->getTicks();

  //pnfloat  step = deltaTime * _movingSpeed;
  _animTimeCurrent = tick;

  updateTranslation((pnfloat)deltaTime);

  _coord += _updateTranslation;

  updateRotation((pnfloat)deltaTime);
}

//////////////////////////////////////////////////////////////////////////

/**
* \brief		Set render mode (skeleton, model, materials) bit mask
*
* \param mode	Bit mask represent things to rend
*/
void
PN3DObject::setRenderMode(pnuint mode)
{
  PNLOCK(this);

  _renderMode = mode;
}

pnint
PN3DObject::getRenderMode() const
{
  return _renderMode;
}

void
PN3DObject::render()
{
  PNLOCK(this);

  if (_model != NULL && _renderMode & RENDER_MODEL)
  {
	if (_renderMode & RENDER_MATERIALS && _materials.size() > 0)
	  _model->render(_materials);
	else
	  _model->render();
  }

  if (_physicalObject != NULL && _renderMode & RENDER_PHYSICAL)
	_physicalObject->render();
}

//////////////////////////////////////////////////////////////////////////
}
