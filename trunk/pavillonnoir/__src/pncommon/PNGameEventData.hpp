/*
 * PNGameEventData.hpp
 * 
 * Description :
 * PNGameEventData declarations/definitions
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

#ifndef _PNGAMEEVENTDATA_HPP_
# define _PNGAMEEVENTDATA_HPP_

#include "pndefs.h"
#include "pnevent.h"
#include "PNEventData.hpp"
#include "PNPoint3f.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////
  
class			PNGameUpdateEventData : public PNEventData
{
public:
  float			deltaTime;
  pnuint		time;

  PNGameUpdateEventData(){}
  PNGameUpdateEventData(float deltatime, pnuint time): deltaTime(deltatime), time(time) {}
};

class			PNGameLoadMapEventData : public PNEventData
{
public:
  PNGameLoadMapEventData(){}
  PNGameLoadMapEventData(std::string map): mapName(map){}
  std::string	mapName;
};

class			PNGameLifeValEventData : public PNEventData
{
public:
  int	lifeVal;
};

class			PNGameLoadGameEventData : public PNEventData
{
public:
  std::string	gameName;
};

class			PNGameSaveGameEventData : public PNEventData
{
public:
  std::string	gameName;
};


class			PNGameActionEventData : public PNEventData
{
public:
	std::string action;
	std::string targetId;
	std::string sourceId;
	double		value;

	PNGameActionEventData(std::string anAction, std::string aTargetId, std::string aSourceId, double aValue):
			action(anAction),
			targetId(aTargetId),
            sourceId(aSourceId),
			value(aValue) {}
};

class			PNGameMouseMoveEventData : public PNEventData
{
public:
	PNPoint3f	coords;

	PNGameMouseMoveEventData(PNPoint3f someCoords): coords(someCoords) {}
};

class			PNGameAIEventData : public PNGameActionEventData
{
public:
  std::string	AITarget;

  PNGameAIEventData(std::string anAction, std::string atargetId, std::string aSourceId ,double aValue, std::string anAITarget):
           PNGameActionEventData(anAction, atargetId, aSourceId, aValue),
           AITarget(anAITarget){}

};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNGAMEEVENTDATA_HPP_*/

