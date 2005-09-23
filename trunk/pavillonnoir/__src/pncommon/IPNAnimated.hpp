/*
 * IPNAnimated.hpp
 * 
 * Description :
 * Interface for Animation support (play, pause, ...)
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
 
#ifndef _IPNANIMATED_HPP_
# define _IPNANIMATED_HPP_

namespace PN
{

class PNAPI			IPNAnimated
{
public:
  IPNAnimated();
  virtual ~IPNAnimated();
	
  /// Set animation to play and the time used to make the transition between last animation and this
  virtual pnuint	startAnimation(pnint animation, pnuint transTime);
  /// Starting animation
  virtual pnuint	startAnimation();
  /// Stop current animation and reset position
  virtual void		stopAnimation();

  /// Pause current animation
  virtual void		pause();

  /// Set speed for current animation, ex: 2.0f = 2 times normal speed
  virtual void		setAnimSpeed(pndouble speed);
  /// Set the automatic looping of animation enable or disable
  virtual void		setEnableLoop(pnbool enabled);
	
protected:
  pnint				_startedEventType;
  pnint				_stopedEventType;
  pnint				_pausedEventType;

  /// Id of playing local animation
  pnint				_animId;

  /// Indicate if animation running
  pnbool			_running;
  /// Indicate if animation paused
  pnbool			_paused;
  /// Indicate if animation loop
  pnbool			_looping;

  /// Current time in animation
  pnuint			_animTimeCurrent;
  /// System time when animation started
  pnuint			_animTimeStart;
  /// Transition time between two animations
  pnuint			_animTransTime;
  /// System time when animation paused
  pnuint			_animTimePause;
  /// Animation speed
  pndouble			_animSpeed;
};

}

#endif /*_IPNANIMATED_HPP_*/
