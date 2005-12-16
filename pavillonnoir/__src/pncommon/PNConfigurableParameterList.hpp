/*
 * PNConfigurableParameterList.hpp
 * 
 * Description :
 * PNConfigurableParameterList declaration
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

#ifndef _PNCONFIGURABLEPARAMETERLIST_HPP_
# define _PNCONFIGURABLEPARAMETERLIST_HPP_

#include "PNConfigurableParameter.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

typedef enum
{
  PN_LISTPARAMTYPE_INT = PN_NB_PARAMTYPE,	// based on std:list<pnint>
  PN_LISTPARAMTYPE_UINT,					// based on std:list<pnuint>
  PN_LISTPARAMTYPE_REAL,					// based on std:list<pnfloat>
  PN_LISTPARAMTYPE_STRING,					// based on std:list<std::string>
  PN_LISTPARAMTYPE_FILE,					// based on std:list<std::string>
  PN_LISTPARAMTYPE_DIR,						// based on std:list<std::string>

  PN_LISTPARAMTYPE_LPPNOBJECT,				// based on std:list<PNObject*>
  PN_LISTPARAMTYPE_VPPNOBJECT,			  	// based on std:vector<PNObject*>

  PN_LISTPARAMTYPE_LINK,
  PN_LISTPARAMTYPE_MATERIAL,				// based on PN3DObject:VectorMaterial
  PN_LISTPARAMTYPE_ANIM,					// based on PN3DSkeletonObject:AnimationVector

  PN_NB_LISTPARAMTYPE						// number of parameters
} pnlistparamtype;

//////////////////////////////////////////////////////////////////////////

class PNAPI				PNConfigurableParameterList : public PNConfigurableParameter
{
protected:
  pnbool				_choosable;
  pnuint				_choise;

public:
  PNConfigurableParameterList(PNConfigurableObject* p, pnlistparamtype type, void* elem, const std::string& label, const std::string& altText, pnbool choosable = true, pnbool editable = true, void* max = NULL, void* min = NULL);
  virtual ~PNConfigurableParameterList();

  pnbool				isChoosable();
  void					setChoosable(pnbool choosable);

  void					setChoise(pnuint choise);
  pnuint				getChoise();

  pnint					getElementList(pnint def);
  pnuint				getElementList(pnuint def);
  pnfloat				getElementList(pnfloat def);
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNCONFIGURABLEPARAMETERLIST_HPP_*/
