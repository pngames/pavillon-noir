/*
 * PNCharacter.hpp
 * 
 * Description :
 * PNCharacter declaration
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

#ifndef _PNCHARACTER_HPP_
# define _PNCHARACTER_HPP_

#include <stack>
#include "PNPathFinding.hpp"
#include "PN3DSkeletonObject.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////
  
typedef			enum
{
  PN_IA_PASSIVE,
  PN_IA_TRAVELLING,
  PN_IA_FIGHTING,
  PN_IA_NBSTATES
}				pnIAState;

typedef			enum
{
  PN_CHARAC_PIRATE,
  PN_CHARAC_NAVY,
  PN_CHARAC_CIVILIAN
}				pnCharacType;

class PNWayPoint;

class PNAPI PNCharacter : public PN3DSkeletonObject
{
  pnbool								_hurry;
  pnIAState								_state;
  PNPathFinding							_pf;
  std::stack<pnIAState>					_pastStates;
  PN3DObject							_toReach;
  pnCharacType							_real;
  pnCharacType							_shown;

public:
  PNCharacter();
  virtual ~PNCharacter();

  /* Use given class to find path */
  void									buildGraph(boost::filesystem::path& file);

  /* IA main loop function */
  void									beSmart();

  /*
  ** functions to be accessed by callbacks to make character move via
  ** the PNPathFinding class. Set _state to TRAVELLING
  */
  void									moveTo(PNPoint &p);
  void									moveTo(PNWayPoint *wp);

  /* react to a sound event */
  void									hear();

  /* react to a sight event */
  void									see();

  /*
  **  Initiates the fighting mode via derivated class.
  **  Sets _state to FIGHTING
  */
  virtual void							startFight();

  /*
  **  if _state is FIGHTING, lets derivated class manage the actions of
  ** the character
  */
  virtual void							manageFight();

  /*
  **
  */
  pnCharacType							getCharacType();

  //////////////////////////////////////////////////////////////////////////
private:
  void									setState(pnIAState st);
  void									restoreState();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNCHARACTER_HPP_*/
