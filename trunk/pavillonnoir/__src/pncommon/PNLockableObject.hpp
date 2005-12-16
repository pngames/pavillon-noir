/*
* PNLockableObject.hpp
* 
* Description :
* PNLockableObject declaration
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

#ifndef _PNLOCKABLEOBJECT_HPP_
# define _PNLOCKABLEOBJECT_HPP_

#include <boost/thread/recursive_mutex.hpp>

#include "PNObject.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

/// Base object for all lockable classes of pncommon
class PNAPI					PNLockableObject : public PNObject
{
  /// lock object* (unlocked in and of the scope)
#define PNLOCK(obj)			boost::recursive_mutex::scoped_lock  sl((obj)->_mutex)
#define PNLOCK_BEGIN(obj)	{ PNLOCK(obj)
#define PNLOCK_END(obj)		}

#define PNLOCKP(obj)		if ((obj)->_pmutex != NULL) boost::recursive_mutex::scoped_lock  sl(*((obj)->_pmutex))
#define PNLOCKP_BEGIN(obj)	{ PNLOCKP(obj)
#define PNLOCKP_END(obj)	}

  //////////////////////////////////////////////////////////////////////////
public:
  boost::recursive_mutex	_mutex;

  void*						lock();
  static void				unlock(void *m);
public:
  virtual ~PNLockableObject() {}
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNOBJECT_HPP_*/
