/*
 * pnresources.h
 * 
 * Description :
 * Relative path for ressources
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

#ifndef _PNRESSOURCES_H_
# define _PNRESSOURCES_H_

#include <string>

namespace PN {
//////////////////////////////////////////////////////////////////////////
  namespace DEF
  {
	static const std::string	dataFilePath = "datafiles/";

	static const std::string	modelFilePath = dataFilePath + "models/";
	static const std::string	materialFilePath = dataFilePath + "materials/";
	static const std::string	texturesFilePath = dataFilePath + "textures/";
	static const std::string	skeletonFilePath = dataFilePath + "skeletons/";
	static const std::string	animationFilePath = dataFilePath + "animations/";
	static const std::string	physicsFilePath = dataFilePath + "physics/";

	static const std::string	objectFilePath = dataFilePath + "objects/";
	static const std::string	defaultObjFilePath = objectFilePath + "3ddynobject.pno";

	static const std::string	mapsFilePath = dataFilePath + "maps/";

	static const std::string	gamedefFilePath = dataFilePath + "gamedef/";

	static const std::string	musicFilePath = dataFilePath + "music/";
	static const std::string	soundsFilePath = dataFilePath + "sounds/";
	static const std::string	videosFilePath = dataFilePath + "videos/";

	static const std::string	confFilePath = dataFilePath + "configuration/";

	inline std::string			convertPath(const std::string& type, const std::string& path)
	{
	  std::string::size_type	  index = path.rfind(type);

	  if (index == std::string::npos)
		return path;

	  return path.c_str() + index + type.size();
	}
  }
//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNRESSOURCES_H_*/
