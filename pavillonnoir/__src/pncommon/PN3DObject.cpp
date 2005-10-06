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
 * 
 */
PN3DObject::PN3DObject()
{
  _id = "";
  _animId = -1;
  _running = false;
  _paused = false;
  _looping = false;

  _rotActivation = RACTIVATE_ALL;

  _renderMode = RENDER_MODEL | RENDER_MATERIALS;
  _movingState = 0;
  _movingMode = MMODE_FREE;

  _model = NULL;
  _physicalObject = NULL;

  //_coord = PNPoint::null;
  //  _angles.set(0.0f, 0.0f, 0.0f);
  _orient.set(0.0f, 0.0f, 0.0f, 1.0f);
  _direct.set(0.0f, 0.0f, 0.0f);
  _updateTranslation.set(0.0f, 0.0f, 0.0f);

  _frontDirection.setArray(PNVector3f::NEGATIVE_UNIT_Z);
  _rightDirection.setArray(PNVector3f::UNIT_X);
  _topDirection.setArray(PNVector3f::UNIT_Y);

  _target = NULL;
  _targetDistance = -1.0f;
  setTargetDirection(_frontDirection);

  _animTransTime = 0;
  _animSpeed = 1.0f;
  _movingSpeed = 1.0f;

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

  return PNEC_SUCCES;
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

  return PNEC_SUCCES;
}

pnint
PN3DObject::unserializeFromXML(xmlNode* root)
{
  PNLOCK(this);

  _model = NULL;
  _materials.clear();

  //////////////////////////////////////////////////////////////////////////

  pnint	error = PNEC_SUCCES;

  //////////////////////////////////////////////////////////////////////////
  // MODEL

  if ((error = _parseModel(root)) != PNEC_SUCCES)
	return error;

  //////////////////////////////////////////////////////////////////////////
  // others

  for (root = root->children ; root != NULL; root = root->next)
  {
	if (PNO_XMLNODE_LISTMATERIALS == (const char*)root->name)
	  _parseMaterials(root);
  }

  return PNEC_SUCCES;
}

/**
* @brief		Save PN3DObject to xml file
*
* @param file	File to save
*
* @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
*
* @see			pnGetErrorString
*/
pnint
PN3DObject::serializeInXML(std::ostream& o, bool header)
{
  PNLOCK(this);

  pnint err = PNEC_SUCCES;

  if (header)
	o << PNO_XML_HEADER;

  o << "<" << PNO_XMLNODE_ROOT << " " << PNO_XMLPROP_PATH << "=\"" << (_model == NULL ? "none" :_model->getFile()->leaf()) << "\">" << endl;

  if ((err = _serializeContent(o)) != PNEC_SUCCES)
	return err;

  o << "</" << PNO_XMLNODE_ROOT << ">" << endl;

  return err;
}

/**
* @brief		Save PN3DObject content to xml file
*
* @return		One of \c PN::pnerrorcode, \c PN::PNEC_SUCCES if succed
*
* @see			pnGetErrorString
*/
pnint
PN3DObject::_serializeContent(std::ostream& o)
{
  o << "  " << "<" << PNO_XMLNODE_LISTMATERIALS << ">" << endl;

  for (VectorMaterial::iterator it = _materials.begin(); it != _materials.end(); ++it)
	if (*it != NULL && ((PN3DMaterial*)*it)->getFile() != NULL)
	  o << "    " << "<" << PNO_XMLNODE_MATERIAL << " " << PNO_XMLPROP_PATH << "=\"" << ((PN3DMaterial*)*it)->getFile()->leaf() << "\" />" << endl;

  o << "  " << "</" << PNO_XMLNODE_LISTMATERIALS << ">" << endl;

  return PNEC_SUCCES;
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

const PNVector3f&
PN3DObject::getDirect() const
{
  return _direct;
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

/*void
PN3DObject::rotate(pnfloat& angles)
{
  _angles += angles;
}*/

void
PN3DObject::rotatePitchRadians(pnfloat pitch)
{
  if (_rotActivation & RACTIVATE_PITCH)
	rotatePYRAxisRadians(getRightDirection().getVector(), pitch * _movingSpeed);
}

void
PN3DObject::rotateYawRadians(pnfloat yaw)
{
  if (_rotActivation & RACTIVATE_YAW)
	rotatePYRAxisRadians(getTopDirection().getVector(), yaw * _movingSpeed);
}

void
PN3DObject::rotateRollRadians(pnfloat roll)
{
  if (_rotActivation & RACTIVATE_ROLL)
	rotatePYRAxisRadians(getFrontDirection().getVector(), roll * _movingSpeed);
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
  rotateAxisRadians(PNVector3f::UNIT_X, x * _movingSpeed * _movingSpeed);
}

void
PN3DObject::rotateYRadians(pnfloat y)
{
  rotateAxisRadians(PNVector3f::UNIT_Y, y * _movingSpeed * _movingSpeed);
}

void
PN3DObject::rotateZRadians(pnfloat z)
{
  rotateAxisRadians(PNVector3f::UNIT_Z, z * _movingSpeed * _movingSpeed);
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

  _movingState = _movingState | mstate;
}

void
PN3DObject::subMovingState(pnuint mstate)
{
  PNLOCK(this);

  _movingState = _movingState ^ mstate;
}

pnfloat
PN3DObject::getMovingSpeed() const
{
  return _movingSpeed;
}

void
PN3DObject::setMovingSpeed(pnfloat mspeed)
{
  PNLOCK(this);

  _movingSpeed = mspeed;
}

//////////////////////////////////////////////////////////////////////////

PN3DObject::movingmode
PN3DObject::getMovingMode() const
{
  return _movingMode;
}

void
PN3DObject::setMovingMode(PN3DObject::movingmode mmode)
{
  PNLOCK(this);

  _movingMode = mmode;
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
PN3DObject::setTarget(PN3DObject* obj, pnfloat distance)
{
  PNLOCK(this);

  _target = obj;
  setTargetDistance(distance);
}

void
PN3DObject::setTargetDistance(pnfloat distance)
{
  PNLOCK(this);

  _targetDistance = distance;
}

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

PN3DObject*
PN3DObject::getTarget() const
{
  return _target;
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
  // FIXME : make a test on the value returned by PNPhysicsInterface
  return true;
}

//////////////////////////////////////////////////////////////////////////

void
PN3DObject::setDirect(const PNVector3f &direct)
{
  PNLOCK(this);

  _direct = direct;
}

void
PN3DObject::setDirect(pnfloat x, pnfloat y, pnfloat z)
{
  PNLOCK(this);

  _direct.x = x;
  _direct.y = y;
  _direct.x = x;
}

//////////////////////////////////////////////////////////////////////////

/**
 * Updates the current translation of the object
 * regarding the spent time and its state. This method has
 * no side effect.
 */
void
PN3DObject::updateTranslation(pnfloat step)
{
  PNLOCK(this);

  _updateTranslation.setNull();

  if (_movingState == 0)
	return;

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

  //std::cout << _translation << " --> ";

  _updateTranslation = _orient * _updateTranslation;

  //////////////////////////////////////////////////////////////////////////
  // targetDistance

  if (_targetDistance > 0.0f &&
	  (_movingMode == MMODE_DISTANCE_ABS_LOCKED || _movingMode == MMODE_DISTANCE_LOCKED))
  {
	PNVector3f	targetVector = _target->getCoord();
	targetVector -= _coord;

	pnfloat norm = targetVector.getNorm();
	targetVector.setNorm(norm - _targetDistance);

	_updateTranslation += targetVector;
  }

  return;
}

void
PN3DObject::updateRotation(pnfloat step)
{
  PNLOCK(this);

  pnfloat	phi = (pnfloat)DEGREE_TO_RADIAN(step/10);

  if (_movingMode == MMODE_VIEW_ABS_LOCKED || _movingMode == MMODE_VIEW_LOCKED)
  {
	PNVector3f	targetVector = _target->getCoord();
	targetVector -= _coord;

	pnfloat	norm = sqrtf(SQNBR(targetVector.x) + SQNBR(targetVector.z));
	double	ps = (_targetDirection.getX() * targetVector.x / norm) + (_targetDirection.getZ() * targetVector.z / norm);
	double	pcy = (_targetDirection.getX() * targetVector.z / norm) - (_targetDirection.getZ() * targetVector.x / norm);

	pnfloat yangle = acosf((float)ps);
	yangle = pcy > 0 ? -yangle : yangle;

	//////////////////////////////////////////////////////////////////////////
	
	targetVector = PNQuatf(PNVector3f::UNIT_Y, -yangle) * targetVector;

	norm = targetVector.getNorm();
	ps = (_targetDirection.getX() * targetVector.x / norm ) + (_targetDirection.getY() * targetVector.y / norm) + (_targetDirection.getZ() * targetVector.z / norm);

	PNVector3f	pc;
	pc.crossProduct(_targetDirection.getVector(), targetVector);

	pnfloat xangle = acosf((float)ABS(ps));
	if (pc.scalarProduct(_rightTargetDirection.getVector()) < 0)
	  xangle = -xangle;

	_orient.fromAxisRadians(_rightTargetDirection.getVector(), xangle);
	_orient = PNQuatf(PNVector3f::UNIT_Y, yangle) * _orient;

	return ;
  }
  else if (_movingMode == MMODE_VIEW_LOCKED)
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

	return ;
  }

  PNVector3f  axis(PNVector3f::ZERO);

  if (_movingState & STATE_R_TOP)
	axis.x += phi;
  if (_movingState & STATE_R_BACK)
	axis.x -= phi;
  if (_movingState & STATE_R_RIGHT)
	axis.y -= phi;
  if (_movingState & STATE_R_LEFT)
	axis.y += phi;
  if (_movingState & STATE_R_FORWARD)
	axis.z += phi;
  if (_movingState & STATE_R_BACKWARD)
	axis.z -= phi;

  if (axis.x != 0)
	rotatePitchRadians(axis.x);
  if (axis.y != 0)
	rotateYawRadians(axis.y);
  if (axis.z != 0)
	rotateRollRadians(axis.z);

  return ;
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

  pnfloat  step = deltaTime * _movingSpeed;
  _animTimeCurrent = tick;

  updateTranslation(step);

  _coord += _updateTranslation;

  updateRotation(step);
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
}

//////////////////////////////////////////////////////////////////////////
}
