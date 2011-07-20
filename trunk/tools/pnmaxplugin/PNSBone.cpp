/*
 * PNSBone.cpp
 * 
 * Description :
 * PNSBone definition
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 *
 * This file is part of pnmaxplugin.
 *
 * pnmaxplugin is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * pnmaxplugin is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with pnmaxplugin; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "stdafx.h"

#include "PNSBone.hpp"
#include "PNMainWin.hpp"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

pnuint		PNSBone::_nbBones = 0;

//////////////////////////////////////////////////////////////////////////

IGameNode*	PNSBone::getNode()
{
  return _igNode;
}

PNSBone*	PNSBone::getParent()
{
  return _parent;
}

pnint		PNSBone::getId()
{
  return _id;
}

pnuint		PNSBone::getNbBones()
{
  return _nbBones;
}

void		PNSBone::setExported(bool export/* = true*/)
{
  _exported = export;
}

bool		PNSBone::isExported()
{
  return _exported;
}

//////////////////////////////////////////////////////////////////////////

PNSBone::PNSBone(PNSBone* parent/* = NULL*/, IGameNode* igNode/* = NULL*/)
: _parent(parent), _igNode(igNode), _id(-1), _exported(true)
{
  if (_parent != NULL)
  {
	_parent->push_back(this);
	_id = _nbBones;

	PNMainWin::WriteLine("_id: %i", _id);
  }

  _nbBones = _id + 1;
}

PNSBone::~PNSBone()
{
  for (iterator it = begin(); it != end(); ++it)
	delete *it;
}

//////////////////////////////////////////////////////////////////////////
};
