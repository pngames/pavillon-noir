/*
 * PNFXAnimListParameter
 * 
 * Description :
 * PNFXAnimListParameter declaration
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


/////////////////////////////////////

#ifndef _PNFXAnimListPARAMETER_HPP_
# define _PNFXAnimListPARAMETER_HPP_

/////////////////////////////////////

#include "pnproperties.h"

#include "PN3DAnimation.hpp"
#include "PN3DSkeletonAnimation.hpp"

#include "PNFXListParameter.hpp"

/////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNIAGraph;

class PNEDAPI				PNFXAnimListParameter : public PNFXListParameter
{
  FXDECLARE(PNFXAnimListParameter);

  FXDialogBox*				_animDialBox;
  
  PN3DSkeletonAnimation*	_skanim;

protected:
  PNFXAnimListParameter() {}
  PNFXAnimListParameter(PNFXAnimListParameter&) {}
public:
  PNFXAnimListParameter(FXComposite* p, PNConfigurableParameterList* param);
  ~PNFXAnimListParameter();

  void						create();

  FXuint					showAnim(PNConfigurableObject* anim);
  PN3DAnimation*			openAnim(void);
protected:
  bool						_deleteObject(FXint index);
  bool						_addNewObject(FXint index);
  bool						_editObject(FXint index);

  void						_update();
  void						_update(pnuint index);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNFXAnimListPARAMETER_HPP_*/
