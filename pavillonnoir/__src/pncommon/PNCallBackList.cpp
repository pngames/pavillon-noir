/*
 * PNCallBackList.cpp
 * 
 * Description :
 * PNCallBackList definition
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

//////////////////////////////////////////////////////////////////////////

#include "pnevent.h"

#include "PNCallBackList.hpp"

using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

void
PNCallBackList::addCallback(const EventCallback& callback)
{
  PNLOCK(this);

  _callbacks.insert(callback);
}

void
PNCallBackList::deleteCallback(const EventCallback& callback)
{
  PNLOCK(this);

  _callbacks.erase(callback);
}

//////////////////////////////////////////////////////////////////////////

void
PNCallBackList::sendEvent(pnevent* event)
{
  sendEvent(event->type, event->source, event->data);
}

void
PNCallBackList::sendEvent(pnEventType type, PNObject* source, PNEventData* data)
{
  CallbackSet tmp;

  PNLOCK_BEGIN(this);
  tmp = _callbacks;
  PNLOCK_END(this);

  for (CallbackSet::iterator it = tmp.begin(); it != tmp.end(); ++it)
  {
	//try
	{
	  (*it)(type, source, data);
	  //pnerror(PN_LOGLVL_DEBUG, "callback ended for %d\n", type);
	}
	/*catch (...)
	{
#ifdef DEBUG
	  pnerror(PN_LOGLVL_ERROR, "Event %s has crashed in a callback.", PNEventManager::getInstance()->getNameByType(type).c_str());
#endif
	}*/
  }
}

void
PNCallBackList::operator() (pnEventType type, PNObject* source, PNEventData* data)
{
  sendEvent(type, source, data);
}

//////////////////////////////////////////////////////////////////////////
}
