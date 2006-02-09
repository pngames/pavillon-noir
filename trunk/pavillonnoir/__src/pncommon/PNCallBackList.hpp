/*
 * PNCallBackList.hpp
 * 
 * Description :
 * PNCallBackList declaration
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

#ifndef _PNCALLBACKLIST_HPP_
# define _PNCALLBACKLIST_HPP_

#include <set>
#include <boost/thread/recursive_mutex.hpp>

#include "PNLockableObject.hpp"
#include "IPNSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNEventData;
struct pnevent;

/// Callback manager for one event type
class PNAPI					PNCallBackList: public PNLockableObject, public IPNSerializable
{
private:
  /// Event callbacks list type
  typedef std::set<EventCallback>	CallbackSet;
  /// Event callbacks list
  CallbackSet				_callbacks;
public:
  /// Attach new callback. If callback allready exist inti the list, do nothing
  virtual void				addCallback(const EventCallback& callback);
  /// Detach callback
  virtual void				deleteCallback(const EventCallback& callback);

  //////////////////////////////////////////////////////////////////////////

  /// Call all callback with these arguments
  virtual void				sendEvent(pnevent* event);
  /// Call all callback with these arguments
  virtual void				sendEvent(pnEventType type, PNObject* source, PNEventData* data);
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PNCALLBACKLIST_HPP_*/

