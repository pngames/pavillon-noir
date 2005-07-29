/*
 * PNVRef.hpp
 * 
 * Description :
 * Virtual reference [not used]
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

#ifdef _PNVREF_HPP_
//#ifndef _PNVREF_HPP_
# define _PNVREF_HPP_

#include <assert.h>

using namespace PN;

template<class T>
class	PNVRef
{
protected:
  T*	_obj;

public:
  PNVRef() : _obj(NULL) {}
  PNVRef(const PNVRef<T>& vobj) : _obj(vobj._obj) {}
  PNVRef(T* obj) : _obj(obj) {}

  PNVRef<T>&	operator=(const PNVRef<T>& vobj)
  {
	if (_obj != 0) _obj->release();
	_obj = vobj._obj;
	if (_obj != 0) _obj->addRef();

	return*this;
  }

  PNVRef<T>&	operator=(T* obj)
  {
	if (_obj != 0) _obj->release();
	_obj = obj;
	if (_obj != 0) _obj->addRef();

	return*this;
  }

  //////////////////////////////////////////////////////////////////////////

  inline T&		operator*() const
  {
	assert(_obj != NULL&& "Tried to* on a NULL PNVRef");

	return*_obj;
  }

  inline T*		operator->() const
  {
	assert(_obj != NULL&& "Tried to -> on a NULL PNVRef");

	return _obj;
  }

  //////////////////////////////////////////////////////////////////////////
  
  inline pnbool operator ==(const PNVRef<T>& vobj) const
  {
	return (_obj == vobj.obj);
  }
  inline pnbool operator ==(const T* obj) const
  {
	return (_obj == obj);
  }

  //////////////////////////////////////////////////////////////////////////

  ~PNVRef()
  {
	if (_obj) _obj->release();
  }
};

#endif /*_PNVREF_HPP_*/
