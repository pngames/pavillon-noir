/*
* IPNLoadingProgess.cpp
* 
* Description :
* IPNLoadingProgess definition
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

#include "PNGameEventData.hpp"

#include "IPNLoadingProgess.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

IPNLoadingProgess::IPNLoadingProgess()
{
  reinit();
}

IPNLoadingProgess::~IPNLoadingProgess()
{
  for (EventList::iterator it; it != _events.end(); ++it)
	PNEventManager::getInstance()->deleteCallback(*it, EventCallback(this, &IPNLoadingProgess::stepLoad));
}

//////////////////////////////////////////////////////////////////////////

void
IPNLoadingProgess::reinit()
{
  _stepMultiplier = 1.0f;

  while (!_stepStack.empty())
	_stepStack.pop();

  _label = "";
  _step = 0.0f;
  _oldStep = 0.0f;
}

void
IPNLoadingProgess::addCallback(pnEventType type)
{
  PNEventManager::getInstance()->addCallback(type, EventCallback(this, &IPNLoadingProgess::stepLoad));

  _events.push_back(type);
}

//////////////////////////////////////////////////////////////////////////

void
IPNLoadingProgess::stepLoad(pnEventType type, PNObject* source, PNEventData* data)
{
  PNGameLoadStepsMapEventData* stepData = (PNGameLoadStepsMapEventData*)data;

  //////////////////////////////////////////////////////////////////////////
  
  switch (stepData->cmd)
  {
  case PNGameLoadStepsMapEventData::LSTATE_CMD_PUSH:
	_oldStep = _step;

	_stepStack.push(stepData->progressVal);
	_stepMultiplier *= _stepStack.top();
	break;
  case PNGameLoadStepsMapEventData::LSTATE_CMD_POP:
	if (!_stepStack.empty())
	{
	  _oldStep -= _stepMultiplier;

	  _stepMultiplier /= _stepStack.top();
	  _stepStack.pop();
	}
	break;
  default:
	_step = _oldStep + (stepData->progressVal * _stepMultiplier);
	break;
  }

  _label = stepData->item;
}

//////////////////////////////////////////////////////////////////////////
};
