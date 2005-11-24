/*
 * PNIBone.cpp
 * 
 * Description :
 * PNIBone definition
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

#include "pndefs.h"
#include "pnmath.h"

#include "PN3DSkeletonAnimation.hpp"
#include "PN3DAnimation.hpp"

#include "pns_format.h"

#include "PNIBone.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNIBone::PNIBone(pnsBone_t& bone, PNIBone* parent) : 
_id(bone.id), _name(bone.name), 
_parent(parent), 
_mRelativ(bone.m_relative), _mCourse(bone.m_relative), _mICourse(bone.m_relative)
{
  _mICourse.invert();

  if (_parent != NULL)
  {
	_mICourse.postMultiply(_parent->_mICourse);
	_mCourse.preMultiply(_parent->_mCourse);
  }

  _mFinal = _mCourse;
  _mFinal.postMultiply(_mICourse);
}

pnuint
PNIBone::getId()
{
  return _id;
}

const std::string&
PNIBone::getName()
{
  return _name;
}

PNIBone*
PNIBone::getParent()
{
  return _parent;
}

const PNMatrixTR4f&
PNIBone::getCourse() const
{
  return _mCourse;
}

const PNMatrixTR4f&
PNIBone::getFinal() const
{
  return _mFinal;
}

//////////////////////////////////////////////////////////////////////////

const PNQuatf&
PNIBone::getOrientation()
{
  return _totalLastRot;
}

//////////////////////////////////////////////////////////////////////////

void
PNIBone::update(const AnimationSet& anims)
{
  PNMatrixTR4f	transform(_mRelativ);

  pnbool	rotUpdated = false;
  pnbool	posUpdated = false;

  pnfloat	weight = 0.0f;

  PNQuatf	lastRot;
  PNPoint3f	lastPos;

  for (AnimationSet::const_iterator  it = anims.begin(); it != anims.end(); ++it)
  {
	PN3DSkeletonAnimation*  anim = *it;

	//////////////////////////////////////////////////////////////////////////

	PNQuatf		rot;
	PNPoint3f		pos;

	if (anim != NULL && anim->anim != NULL)
	{
	  if (anim->anim->setRotation(_id, anim->step, rot))
	  {
		if (rotUpdated)
		  lastRot.slerp(lastRot, PNQuatf(rot), anim->weight / (weight + anim->weight));
		else
		  lastRot = rot;

		weight += anim->weight;
		rotUpdated = true;
	  }
	  if (anim->anim->setPosition(_id, anim->step, pos))
	  {
		if (posUpdated)
		{
		  lastPos.x = (lastPos.x * weight + pos.x * anim->weight) / (weight + anim->weight);
		  lastPos.y = (lastPos.y * weight + pos.y * anim->weight) / (weight + anim->weight);
		  lastPos.z = (lastPos.z * weight + pos.z * anim->weight) / (weight + anim->weight);
		}
		else
		  lastPos = pos;
		
		weight += anim->weight;
		posUpdated = true;
	  }
	}
  }

  _lastRot = lastRot;
  _lastPos = lastPos;

  if (rotUpdated)
	transform.setRotationQuaternion(_lastRot);
  if (posUpdated)
	transform.setTranslation(_lastPos);

  if (_parent == NULL)
	_mCourse = transform;
  else
  {
	_totalLastRot *= _parent->_totalLastRot;
	_mCourse = _parent->_mCourse;
	_mCourse.postMultiply(transform);
  }

  _mFinal = _mCourse;
  _mFinal.postMultiply(_mICourse);
}

void
PNIBone::update(pndouble rtime, const AnimationSet& anims)
{
  PNMatrixTR4f	transform(_mRelativ);

  pnbool	rotUpdated = false;
  pnbool	posUpdated = false;

  pnfloat	weight = 0.0f;

  PNQuatf	lastRot;
  PNPoint3f	lastPos;

  for (AnimationSet::const_iterator  it = anims.begin(); it != anims.end(); ++it)
  {
	PN3DSkeletonAnimation*  anim = *it;

	//////////////////////////////////////////////////////////////////////////

	PNQuatf		rot;
	PNPoint3f		pos;

	if (anim != NULL && anim->anim != NULL)
	{
	  if (anim->anim->setRotation(_id, rtime, lastRot, rot))
	  {
		if (rotUpdated)
		  lastRot.slerp(lastRot, PNQuatf(rot), anim->weight / (weight + anim->weight));
		else
		  lastRot = rot;

		weight += anim->weight;
		rotUpdated = true;
	  }

	  if (anim->anim->setPosition(_id, rtime, lastPos, pos))
	  {
		if (posUpdated)
		{
		  lastPos.x = (lastPos.x * weight + pos.x * anim->weight) / (weight + anim->weight);
		  lastPos.y = (lastPos.y * weight + pos.y * anim->weight) / (weight + anim->weight);
		  lastPos.z = (lastPos.z * weight + pos.z * anim->weight) / (weight + anim->weight);
		}
		else
		  lastPos = pos;

		weight += anim->weight;
		posUpdated = true;
	  }
	}
  }

  _lastRot = lastRot;
  _lastPos = lastPos;

  if (rotUpdated)
	transform.setRotationQuaternion(_lastRot);
  if (posUpdated)
	transform.setTranslation(_lastPos);

  if (_parent == NULL)
	_mCourse = transform;
  else
  {
	_mCourse = _parent->_mCourse;
	_mCourse.postMultiply(transform);
  }

  _mFinal = _mCourse;
  _mFinal.postMultiply(_mICourse);
}

void
PNIBone::reinit()
{
  if (_parent == NULL)
	_mCourse = _mRelativ;
  else
  {
	_mCourse = _parent->_mCourse;
	_mCourse.postMultiply(_mRelativ);
  }

  _mFinal = _mCourse;
  _mFinal.postMultiply(_mICourse);
}

//////////////////////////////////////////////////////////////////////////
}
