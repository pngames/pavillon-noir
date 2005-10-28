/*
 * PNEventManager.hpp
 * 
 * Description :
 * PNEventManager declaration
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

#ifndef _PNEVENTMANAGER_HPP_
# define _PNEVENTMANAGER_HPP_

#ifdef WIN32
# pragma warning( disable: 4275 )
#endif

#include <stack>
#include <boost/utility.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <iostream>

#include "PNCallBackList.hpp"
#include "PNObject.hpp"
#include "PNEventData.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNCallBackList;

/// An event
struct				pnevent
{
  /// Event type
  pnEventType		type;
  /// Sender of event
  PNObject*			source;
  /// Data of event
  PNEventData*  	data;

  /// Make event from sender \c s of type \c t and data \d
  pnevent(pnEventType t, PNObject* s, PNEventData* d)
  {
    type = t;
    source = s;
    data = d;
  }

  /// Destructor for pnevent
  ~pnevent()
  {
    if (data != NULL)
      delete data;
  }
};

/**
* \breaf Event Manager used for send messages to all modules without knowing the entry points
*
* The callback system takes "delegates":
*
* void staticFunction(const std::string&, std::istream&)
* {}
* 
* class MyClass
* {
*   static void staticMemberFunction(const std::string&, std::istream&);
*   void memberFunction(const std::string&, std::istream&);
* }
*
* void test()
* {
*  MyClass toto;
*
*  addCallback(type, staticFunction);
*  addCallback(type, MyClass::staticMemberFunction);
*  addCallback(type, PNConsole::Callback(&toto, &MyClass::memberFunction));
*
*  // same thing for deleteCallback
* }
*/
class PNAPI				PNEventManager : public PNObject
{
  friend void initEventManager();
private:
  /// Unique instance of events manager
  static PNEventManager*		_instance;

  /// Default constructor for PNEventManager
  PNEventManager();
  /// Destructor for PNEventManager
  ~PNEventManager();

  /// Entry point for events manager thread
  void	run();

  /// Mutex used for block where there is no event on the stack
  boost::mutex					_mutex;
  /// Mutex manager to wait verified condition
  boost::condition				_cond;

public:
  /// Return unique instance of events manager
  static  PNEventManager*		getInstance();

  //////////////////////////////////////////////////////////////////////////

private:
  /// Events stack type
  typedef std::stack<pnevent>	STACKEVENTS;
  /// Events stack
  STACKEVENTS					_events;
  /// Indicate if event manager running, used to stop it
  pnbool						_run;

  /// Map type to convert event type name to event type indentifier
  typedef std::map<std::string, pnEventType> eventEnumMap;
  /// Map type to convert event type identifier to event type name
  typedef std::map<pnEventType, std::string> eventNameMap;
  /// Map to convert event type name to event type indentifier
  eventNameMap					_eventNames;
  /// Map to convert event type identifier to event type name
  eventEnumMap					_eventEnums;
public:
  /// Load object from file
  pnint		unserialize(const boost::filesystem::path& file);
  /// Save object to file
  pnint		serialize(const boost::filesystem::path& file);

  //////////////////////////////////////////////////////////////////////////

  /// Run event manager in background task
  void		init();
  /// Stop event manager
  void		stop();

  //////////////////////////////////////////////////////////////////////////

  /// Add event of type \c type on stack (non blocking)
  void		addEvent(pnEventType type, PNObject* source, PNEventData* data);

  /// Send event directly (blocking)
  void		sendEvent(pnEventType type, PNObject* source, PNEventData* data);

  //////////////////////////////////////////////////////////////////////////
  
  /// Get the event name by type identifier
  const std::string&	getNameByType(pnEventType type);
  /// Get the event type identifier by name
  pnEventType			getTypeByName(const std::string& name);

  //////////////////////////////////////////////////////////////////////////

private:
  /// Table of callback list arranged by type
  PNCallBackList	_callbacktList[PN_NUMBER_EVENTS];
public:
  /// Attach new callback to events of type \c type
  void	addCallback(pnEventType type, const EventCallback& callback);
  /// Detach callback from events of type \c type
  void	deleteCallback(pnEventType type, const EventCallback& callback);
};

  //////////////////////////////////////////////////////////////////////////
}

#endif /*_PNEVENTMANAGER_HPP_*/