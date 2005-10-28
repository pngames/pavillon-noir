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
#include "pnevent.h"

#include "PNEventManager.hpp"
#include "PNCallBackList.hpp"

namespace fs = boost::filesystem;
using namespace PN;

namespace PN {
//////////////////////////////////////////////////////////////////////////

void	PNCallBackList::addCallback(const EventCallback& callback)
{
  _callbacks.insert(callback);
}

void	PNCallBackList::deleteCallback(const EventCallback& callback)
{
  _callbacks.erase(callback);
}

//////////////////////////////////////////////////////////////////////////

void  PNCallBackList::sendEvent(pnevent* event)
{
  sendEvent(event->type, event->source, event->data);
}

void  PNCallBackList::sendEvent(pnEventType type, PNObject* source, PNEventData* data)
{
  for (CallbackSet::iterator i = _callbacks.begin(); i != _callbacks.end(); ++i)
	(*i)(type, source, data);
}

//////////////////////////////////////////////////////////////////////////

int		PNCallBackList::unserialize(const fs::path& file)
{
  return PNEC_NOT_IMPLEMENTED;
}

int		PNCallBackList::serialize(const fs::path& file)
{
  return PNEC_NOT_IMPLEMENTED;
}

//////////////////////////////////////////////////////////////////////////
}