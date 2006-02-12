/*
 * PNI3DMaterial.cpp
 * 
 * Description :
 * PNI3DMaterial definition
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

#include <iostream>

#include "pndefs.h"
#include "pnplugins.h"
#include "pnrender.h"
#include "pnresources.h"

#include "PNI3DMaterial.hpp"

using namespace PN;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNI3DMaterial::PNI3DMaterial()
{
  _renderMaterial = NULL;
}

PNI3DMaterial::~PNI3DMaterial()
{
  if (_renderMaterial != NULL)
	PNRendererInterface::getInstance()->deleteMaterial(_renderMaterial);
}

//////////////////////////////////////////////////////////////////////////

std::string*
PNI3DMaterial::getFile()
{
  return IPNSerializable::getPath();
}

//////////////////////////////////////////////////////////////////////////

int
PNI3DMaterial::_parse(std::istream& istm)
{
  istm.read((char*)&_header, sizeof(_header));

  if (strncmp(_header.magic, PNT_MAGIC, PNT_MAGIC_SIZE) != 0)
	return PNEC_FILETYPE_INVALID;

  //////////////////////////////////////////////////////////////////////////

  /*std::cout << "magic : " << _header.magic << std::endl;
  std::cout << "version : " << _header.version << std::endl;

  std::cout << "ambient : r=" << _header.ambient[0] << " g=" << _header.ambient[1] << " b=" << _header.ambient[2] << " a=" << _header.ambient[3] << std::endl;
  std::cout << "diffuse : r" << _header.diffuse[0] << " g=" << _header.diffuse[1] << " b=" << _header.diffuse[2] << " a=" << _header.diffuse[3] << std::endl;
  std::cout << "emissive : r" << _header.emissive[0] << " g=" << _header.emissive[1] << " b=" << _header.emissive[2] << " a=" << _header.emissive[3] << std::endl;
  std::cout << "specular : r" << _header.specular[0] << " g=" << _header.specular[1] << " b=" << _header.specular[2] << " a=" << _header.specular[3] << std::endl;

  std::cout << "opacity : " << _header.opacity << std::endl;
  std::cout << "glossiness : " << _header.glossiness << std::endl;

  std::cout << "nbMap : " << _header.nbMap << std::endl;*/

  if (_header.nbMap == 0)
  {
	_texture.clear();
	return PNEC_SUCCESS;
  }

  pntMap_t  map;
  istm.read((char*)&map, sizeof(map));

  if (map.lenght > 0)
  {
	char buff[1024];

	istm.read(buff, map.lenght);
	_texture = buff;
  }

  return PNEC_SUCCESS;
}

pnint
PNI3DMaterial::unserializeFromStream(std::istream& istm)
{
  int err = _parse(istm);

  if (err != PNEC_SUCCESS)
  {
	pnerror(PN_LOGLVL_ERROR, "%s : %s", _path.c_str(), pnGetErrorString(err));
	return err;
  }

  _renderMaterial = PNRendererInterface::getInstance()->newMaterial();

  _renderMaterial->setAmbient(_header.ambient);
  _renderMaterial->setDiffuse(_header.diffuse);
  _renderMaterial->setEmissive(_header.emissive);
  _renderMaterial->setSpecular(_header.specular);

  _renderMaterial->setOpacity(_header.opacity);
  _renderMaterial->setGlossiness(_header.glossiness);

  if (_texture.size() > 0)
  {
  	//std::cout << _texture << std::endl;
  	
	err = _renderMaterial->setTexture(DEF::texturesFilePath + _texture);
  }

  return err;
}

//////////////////////////////////////////////////////////////////////////

PNRenderMaterial*
PNI3DMaterial::getRenderMaterial()
{
  return _renderMaterial;
}

//////////////////////////////////////////////////////////////////////////
};
