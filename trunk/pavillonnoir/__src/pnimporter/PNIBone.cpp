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

#include "PNIBone.hpp"
#include "PN3DAnimation.hpp"

#include "pns_format.h"

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

void
PNIBone::update(pnuint time, PN3DAnimation* anim)
{
  PNMatrixTR4f	transform(_mRelativ);

  if (anim != NULL)
  {
	if (anim->setRotation(_id, time, _lastRot))
	  transform.setRotationQuaternion(_lastRot);
	if (anim->setPosition(_id, time, _lastPos))
	  transform.setTranslation(_lastPos);
  }

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
PNIBone::update(pndouble rtime, PN3DAnimation* anim)
{
  PNMatrixTR4f	transform(_mRelativ);

  if (anim != NULL)
  {
	if (anim->setRotation(_id, rtime, _lastRot, _lastRot))
	  transform.setRotationQuaternion(_lastRot);
	if (anim->setPosition(_id, rtime, _lastPos, _lastPos))
	  transform.setTranslation(_lastPos);
  }

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

//////////////////////////////////////////////////////////////////////////
}
