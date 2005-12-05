/*
 * PNConfigurableParameter.hpp
 * 
 * Description :
 * PNConfigurableParameter declaration
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

#ifndef _PNCONFIGURABLEPARAMETER_HPP_
# define _PNCONFIGURABLEPARAMETER_HPP_

#include <string>

namespace PN
{
//////////////////////////////////////////////////////////////////////////	

typedef enum
{
  PN_PARAMTYPE_INT,				// based on int
  PN_PARAMTYPE_REAL,			// based on float
  PN_PARAMTYPE_STRING,			// based on std::string
  PN_PARAMTYPE_ACTIVESTRING,	
  PN_PARAMTYPE_FILE,			// based on boost:filesystem:path
  PN_PARAMTYPE_DIR,				// based on boost:filesystem:path
  PN_PARAMTYPE_LINK,
  PN_PARAMTYPE_DIALX,
  PN_PARAMTYPE_DIALY,
  PN_PARAMTYPE_DIALZ,
  PN_PARAMTYPE_BOOLEAN,			// based on bool
  PN_PARAMTYPE_EVENTBOX,

  PN_PARAMTYPE_INTLIST,			// based on std:list<int>
  PN_PARAMTYPE_REALLIST,		// based on std:list<float>
  PN_PARAMTYPE_STRINGLIST,		// based on std:list<std::string>
  PN_PARAMTYPE_FILELIST,		// based on std:list<boost:filesystem:path>
  PN_PARAMTYPE_DIRLIST,			// based on std:list<boost:filesystem:path>
  PN_PARAMTYPE_LINKLIST,
  PN_PARAMTYPE_MATERIAL,		// based on PNMaterial*
  PN_PARAMTYPE_MATERIALLIST,	// based on PN3DObject:VectorMaterial
  PN_PARAMTYPE_ANIMLIST,		// based on PN3DSkeletonObject:AnimationVector
  PN_PARAMTYPE_SCRIPTLIST
} pnparamtype;

//////////////////////////////////////////////////////////////////////////

class PNConfigurableObject;

class PNAPI				PNConfigurableParameter
{
protected:
  PNConfigurableObject*	_p;
  pnparamtype			_type;

  void*					_elem;
  void*					_max;
  void*					_min;

  std::string			_label;
  std::string			_altText;
  bool					_editable;

public:
  PNConfigurableParameter(PNConfigurableObject* p, pnparamtype type, void* elem, const std::string& label, const std::string& altText, bool editable = true, void* max = NULL, void* min = NULL);
  virtual ~PNConfigurableParameter();

  pnparamtype			getType();

  void*					getElem();
  void*					getMax();
  void*					getMin();

  const std::string&	getLabel();
  const std::string&	getAltText();
  bool					isEditable();
  PNConfigurableObject*	getConfigurableObject();

  // for tests only
  void					dump();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNCONFIGURABLEPARAMETER_HPP_*/
