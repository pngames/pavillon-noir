/*
 * PNWPModel.cpp
 * 
 * Description :
 * PNWPModel definition
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

#include "PNWPModel.hpp"
#include "pnrender.h"
#include "PNRendererInterface.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

PNWPModel* PNWPModel::_instance = NULL;

PNWPModel::PNWPModel(void)
{
  _dflcolor[0] = 1.0f;
  _dflcolor[1] = 0.0f;
  _dflcolor[2] = 0.0f;
  _dflcolor[3] = 1.0f;
  _selectcolor[0] = 0.0f;
  _selectcolor[1] = 0.0f;
  _selectcolor[2] = 1.0f;
  _selectcolor[3] = 1.0f;
  _color = _dflcolor;
  _min.x = -15.0f;
  _min.y = -15.0f;
  _min.z = -15.0f;
  _max.x = 15.0f;
  _max.y = 15.0f;
  _max.z = 15.0f;
  _center.set(0.0f, 0.0f, 0.0f);
}

PNWPModel::~PNWPModel(void)
{

}

PNWPModel*
PNWPModel::getInstance()
{
  if (_instance == NULL)
	_instance = new PNWPModel;

  return _instance;
}

std::string*
PNWPModel::getFile()
{
  return NULL;
}

void
PNWPModel::render(std::vector<PN3DMaterial*>* mat, PN3DSkeleton* sk)
{
  PNRendererInterface* pnri = PNRendererInterface::getInstance();
  pnri->renderSphere(15.0f, 20, 20, _color);
}

void
PNWPModel::renderLink(const PNPoint3f&p1, const PNPoint3f&p2, const pnfloat* color,
					  pnuint direction, pnfloat thickness)
{
  PNRendererInterface* pnri = PNRendererInterface::getInstance();
  pnri->renderLink(p1, p2, color, direction, thickness);
}

void
PNWPModel::setSlctColor()
{
  _color = _selectcolor;
}

void
PNWPModel::setDflColor()
{
  _color = _dflcolor;
}

//////////////////////////////////////////////////////////////////////////
};

