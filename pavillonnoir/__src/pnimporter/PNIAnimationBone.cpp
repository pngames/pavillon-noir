/*
 * PNIAnimationBone.cpp
 * 
 * Description :
 * PNIAnimationBone definition
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

#include <assert.h>

#include "pndefs.h"
#include "pnmath.h"

#include "PNIAnimationBone.hpp"
#include "PNMatrixTR4f.hpp"

#include "pna_format.h"

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNIAnimationBone::PNIAnimationBone(std::istream& i)
{
  unserialize(i);
}

pnuint		PNIAnimationBone::getId()
{
  return _id;
}
//////////////////////////////////////////////////////////////////////////

pnint		PNIAnimationBone::unserialize(std::istream& i)
{
  pnaBone_t	bone;

  i.read((char*)&bone, sizeof(bone));

  //////////////////////////////////////////////////////////////////////////

  _id = bone.id;

  //////////////////////////////////////////////////////////////////////////
  // ROTATION

  _rotations.resize(bone.nbRot);

  pnaKeyRot_t arot;

  for (RotationVector::iterator it = _rotations.begin(); it != _rotations.end(); ++it)
  {
	pniRotationKey_t&	rot = *it;
	i.read((char*)&arot, sizeof(arot));

	rot.time = arot.time;
	rot.rot = arot.rot;
  }

  //////////////////////////////////////////////////////////////////////////
  // POSITION

  _positions.resize(bone.nbPos);

  pnaKeyPos_t apos;

  for (PositionVector::iterator it = _positions.begin(); it != _positions.end(); ++it)
  {
	pniPositionKey_t&	pos = *it;
	i.read((char*)&apos, sizeof(apos));

	pos.time = apos.time;
	pos.pos = apos.pos;
  }

  return PNEC_SUCCES;
}

//////////////////////////////////////////////////////////////////////////

pnuint		PNIAnimationBone::setTransformation(pnuint time, PNMatrixTR4f& transform)
{
  pnfloat	timeDelta;
  pnfloat	interpValue;

  if (_rotations.size() > 0)
  {
	RotationVector::iterator	rit;

	for (rit = _rotations.begin(); rit != _rotations.end() && rit->time < time; ++rit);

	if (rit == _rotations.begin())
	  transform.setRotationQuaternion(rit->rot);
	else if (rit == _rotations.end())
	{
	  --rit;
	  transform.setRotationQuaternion(rit->rot);
	}
	else
	{
	  const pniRotationKey_t&	curFrame = *rit;
	  --rit;
	  const pniRotationKey_t&	prevFrame = *rit;

	  timeDelta = (pnfloat) (curFrame.time - prevFrame.time);
	  interpValue = (pnfloat) ((time - prevFrame.time)) / timeDelta;

	  assert(interpValue >= 0 && interpValue <= 1);

	  PNQuatf	qPrev(prevFrame.rot);
	  PNQuatf	qCur(curFrame.rot);
	  PNQuatf	qFinal(qPrev, qCur, interpValue);

	  transform.setRotationQuaternion(qFinal);
	}
  }

  if (_positions.size() > 0)
  {
	PositionVector::iterator	pit;

	for (pit = _positions.begin(); pit != _positions.end() && pit->time < time; ++pit);

	PNPoint		transPos;

	if (pit == _positions.begin())
	  transPos = pit->pos;
	else if (pit == _positions.end())
	  {
		--pit;
		transPos = pit->pos;
	  }
	else
	{
	  const pniPositionKey_t& curFrame = *pit;
	  --pit;
	  const pniPositionKey_t& prevFrame = *pit;

	  timeDelta = (pnfloat) (curFrame.time - prevFrame.time);
	  interpValue = (pnfloat) ((time - prevFrame.time) / timeDelta);

	  transPos.x = prevFrame.pos.x + (curFrame.pos.x - prevFrame.pos.x) * interpValue;
	  transPos.y = prevFrame.pos.y + (curFrame.pos.y - prevFrame.pos.y) * interpValue;
	  transPos.z = prevFrame.pos.z + (curFrame.pos.z - prevFrame.pos.z) * interpValue;
	}

	transform.setTranslation(transPos);
  }

  return PNEC_SUCCES;
}

pnbool		PNIAnimationBone::setRotation(pnuint time, PNQuatf& rot)
{
  if (_rotations.size() <= 0)
	return false;

  RotationVector::iterator	rit;

  for (rit = _rotations.begin(); rit != _rotations.end() && rit->time < time; ++rit);

  if (rit == _rotations.begin())
  {
	rot = rit->rot;
  }
  else if (rit == _rotations.end())
  {
	--rit;
	rot = rit->rot;
  }
  else
  {
	const pniRotationKey_t&	curFrame = *rit;
	--rit;
	const pniRotationKey_t&	prevFrame = *rit;

	pnfloat	timeDelta = (pnfloat) (curFrame.time - prevFrame.time);
	pnfloat	interpValue = (pnfloat) ((time - prevFrame.time)) / timeDelta;

	assert(interpValue >= 0 && interpValue <= 1);

	PNQuatf	qPrev(prevFrame.rot);
	PNQuatf	qCur(curFrame.rot);
	PNQuatf	qFinal(qPrev, qCur, interpValue);

	rot = qFinal;
  }

  return true;
}

pnbool		PNIAnimationBone::setRotation(pndouble rtime, const PNQuatf& lastRot, PNQuatf& rot)
{
  if (_rotations.size() <= 0)
	return false;

  PNQuatf	qFinal(lastRot, _rotations.begin()->rot, (pnfloat)rtime);

  rot = qFinal;

  return true;
}

pnbool		PNIAnimationBone::setPosition(pnuint time, PNPoint& pos)
{
  if (_positions.size() <= 0)
	return false;

  PositionVector::iterator	pit;

  for (pit = _positions.begin(); pit != _positions.end() && pit->time < time; ++pit);

  if (pit == _positions.begin())
	pos = pit->pos;
  else if (pit == _positions.end())
  {
	--pit;
	pos = pit->pos;
  }
  else
  {
	const pniPositionKey_t& curFrame = *pit;
	--pit;
	const pniPositionKey_t& prevFrame = *pit;

	pnfloat	timeDelta = (pnfloat) (curFrame.time - prevFrame.time);
	pnfloat	interpValue = (pnfloat) ((time - prevFrame.time) / timeDelta);

	pos.x = prevFrame.pos.x + (curFrame.pos.x - prevFrame.pos.x) * interpValue;
	pos.y = prevFrame.pos.y + (curFrame.pos.y - prevFrame.pos.y) * interpValue;
	pos.z = prevFrame.pos.z + (curFrame.pos.z - prevFrame.pos.z) * interpValue;
  }

  return true;
}

pnbool		PNIAnimationBone::setPosition(pndouble rtime, const PNPoint& lastPos, PNPoint& pos)
{
  if (_positions.size() <= 0)
	return false;

  pos.x = (pnfloat)(lastPos.x + (pos.x - lastPos.x) * rtime);
  pos.y = (pnfloat)(lastPos.y + (pos.y - lastPos.y) * rtime);
  pos.z = (pnfloat)(lastPos.z + (pos.z - lastPos.z) * rtime);

  return true;
}

//////////////////////////////////////////////////////////////////////////
};
