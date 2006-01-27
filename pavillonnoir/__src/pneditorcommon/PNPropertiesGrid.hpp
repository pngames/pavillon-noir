/*
 * PNPropertiesGrid.hpp
 * 
 * Description :
 * PNPropertiesGrid declaration
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


#ifndef _PN_PROPERTIESGRID_H_
# define _PN_PROPERTIESGRID_H_

#include <list>
#include <fx.h>

#include "pnproperties.h"
#include "pneditorcommon.h"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNEDAPI			PNPropertiesGrid : public FXMatrix
{
  FXDECLARE(PNPropertiesGrid)

public:
  typedef std::list<PNPropertiesGridParameter*>	PNPPList;
private:
  PNConfigurableObject*	_object;
  PNPPList				_params;

protected:
  PNPropertiesGrid(){}
  PNPropertiesGrid(const PNPropertiesGrid&){}

public:
  long					onUpdate(FXObject*, FXSelector, void*);
  long					onCmdListBox(FXObject*, FXSelector, void*);

  PNPropertiesGrid(FXComposite* p);
  virtual ~PNPropertiesGrid();

  void					create();
  void					update();
  PNPPList&				getParams() { return _params; }

  void					setObject(PNConfigurableObject* object);
  PNConfigurableObject*	getObject();

  //////////////////////////////////////////////////////////////////////////
  
  void					applyAll();
};

//////////////////////////////////////////////////////////////////////////
};

#endif /* _PNPROPERTIESGRID_H_ */
