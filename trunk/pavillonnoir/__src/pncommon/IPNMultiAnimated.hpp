/*
* IPNMultiAnimated.hpp
* 
* Description :
* Interface for Multi-Animation support (play, pause, ...)
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

#ifndef _IPNMULTIANIMATED_HPP_
# define _IPNMULTIANIMATED_HPP_

#include <set>
#include <map>

#include "IPNAnimated.hpp"

namespace PN
{
  class PNAPI				IPNMultiAnimated : public IPNAnimated
  {
  public:
	class					IPNMAObject
	{
	public:
	  pnfloat				weight;
	public:
	  pnuint				timeStart;
	  pndouble				speed;

	  pnuint				current;
	public:
	  void*					data;
	};

	typedef std::map<pnint, IPNMAObject> IPNMAOMap;
  public:
	IPNMultiAnimated();
	virtual ~IPNMultiAnimated();

	/// Empty animation list to play
	virtual void			clearAnimationIds();
	/// Add animation to play by id
	virtual void			addAnimationId(pnint animId);
	/// Delete animation to play by id
	virtual void			delAnimationId(pnint animId);

	/// Set animation to play and the time used to make the transition between last animation and this
	virtual pnuint			startAnimation(pnint animation, pnuint transTime);
  protected:
	typedef std::set<pnint>	IntSet;

	IntSet					_animSet;
	IPNMAOMap				_animMap;
  };

}

#endif /*_IPNMULTIANIMATED_HPP_*/
