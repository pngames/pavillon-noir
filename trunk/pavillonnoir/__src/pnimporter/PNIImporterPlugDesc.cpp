/*
 * PNIImporterPlugDesc.cpp
 * 
 * Description :
 * PNIImporterPlugDesc definition
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
#include "pnplugins.h"

#include "PNIModelImporter.hpp"
#include "PNISkeletonImporter.hpp"
#include "PNIMaterialImporter.hpp"
#include "PNIAnimationImporter.hpp"

#include "PNIImporterPlugDesc.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNIImporterPlugDesc::PNIImporterPlugDesc() :
_modelInterface(NULL), _materialInterface(NULL), _skeletonInterface(NULL), _animationInterface(NULL)
{ 
}

PNIImporterPlugDesc::~PNIImporterPlugDesc()
{
  if (_modelInterface != NULL)
	delete _modelInterface;
  if (_materialInterface != NULL)
	delete _materialInterface;
  if (_skeletonInterface != NULL)
	delete _skeletonInterface;
  if (_animationInterface != NULL)
	delete _animationInterface;
}

//////////////////////////////////////////////////////////////////////////

PNInterface*	PNIImporterPlugDesc::getInterface(pnuint id)
{
  switch (id)
  {
  	case 0:
  	  if (_modelInterface == NULL)
	    _modelInterface = new PNIModelImporter();
      return (PNInterface*)_modelInterface;
	case 1:
	  if (_materialInterface == NULL)
		_materialInterface = new PNIMaterialImporter();
	  return (PNInterface*)_materialInterface;
	case 2:
	  if (_skeletonInterface == NULL)
		_skeletonInterface = new PNISkeletonImporter();
	  return (PNInterface*)_skeletonInterface;
	case 3:
	  if (_animationInterface == NULL)
		_animationInterface = new PNIAnimationImporter();
	  return (PNInterface*)_animationInterface;
  }
  
  return NULL;
}

pnuint		PNIImporterPlugDesc::getNbInterface()
{
  return 4;
}

//////////////////////////////////////////////////////////////////////////

const pnchar*	PNIImporterPlugDesc::getName()
{
  return "PN3D Importer";
}

pnuint		PNIImporterPlugDesc::getVersion()
{
  return 001;
}

//////////////////////////////////////////////////////////////////////////
}
