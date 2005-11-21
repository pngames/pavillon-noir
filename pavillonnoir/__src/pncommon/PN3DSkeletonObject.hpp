/*
 * PN3DSkeletonObject.hpp
 * 
 * Description :
 * PN3DSkeletonObject declaration
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

#ifndef _PN3DSKELETONBJECT_HPP_
# define _PN3DSKELETONBJECT_HPP_

#include <vector>

#include "PN3DObject.hpp"
#include "IPNAnimated.hpp"
#include "PN3DSkeletonAnimation.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PN3DSkeleton;
class PN3DAnimation;

/// 3D object containing skeleton and animation to work with
class PNAPI					PN3DSkeletonObject : public PN3DObject, public IPNAnimated
{
public:
  /// Sub Objects to render
  typedef enum
  {
	RENDER_SKELETON			= PN3DObject::RENDER_LAST,
	RENDER_LAST				= RENDER_SKELETON << 1
  }							rendermode;

protected:
  /// Parse XML Animations node
  int						_parseAnimations(xmlNode* node);
  /// Parse XML Skeleton node
  int						_parseSkeleton(xmlNode* node);
  /// Parse XML PNO internal node
  virtual pnint				_unserializeNode(xmlNode* node);

  /// Write in model node content to out stream
  virtual pnint				_serializeContent(xmlNode* node);
public:
  /// List of animations associated with 3d object
  typedef std::vector<PN3DSkeletonAnimation>	AnimationVector;
private:
  /// Skeleton of this 3d object
  PN3DSkeleton*				_skeleton;
  /// Animations list associated with this object
  AnimationVector			_anims;
  AnimationSet				_animsToPlay;
public:
  /// Default constructor for PN3DSkeletonObject.
  PN3DSkeletonObject();
  /// Destructor for PN3DSkeletonObject.
  virtual ~PN3DSkeletonObject();

  //////////////////////////////////////////////////////////////////////////

  /// Update skeleton object informations
  virtual void				update(pnuint deltatTime);

  /// Render object using PNRendererInterface
  virtual void				render();

  //////////////////////////////////////////////////////////////////////////

  /// Retrieve animation list of skeleton object
  AnimationVector&			getAnimations();

  /// Retrieve skeleton of skeleton object
  PN3DSkeleton*				getSkeleton();

  //////////////////////////////////////////////////////////////////////////
  
public:
  void						stopAnimation();
  void						stopAnimation(pnuint animId);

  pnuint					startAnimation();
  pnuint					startAnimation(pnuint animId);

  void						setAnimSpeed(pnfloat speed);
  void						setAnimSpeed(pnint animId, pnfloat speed);

  void						setAnimWeight(pnfloat weight);
  void						setAnimWeight(pnint animId, pnfloat weight);

  //////////////////////////////////////////////////////////////////////////

  /// Set animation to play and the time used to make the transition between last animation and this
  virtual pnuint			startAnimation(pnint animation, pnuint transTime);

  /// Empty animation list to play
  void						clearAnimationIds();

  //////////////////////////////////////////////////////////////////////////
  
  /// Parse XML root node
  virtual pnint				unserializeFromXML(xmlNode* node);
};

//////////////////////////////////////////////////////////////////////////
}

#endif /*_PN3DSKELETONBJECT_HPP_*/
