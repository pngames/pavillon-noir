/*
* PNLoadingProgressEventData.hpp
* 
* Description :
* PNLoadingProgressEventData declarations/definitions
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

#ifndef _PNLOADINGPROGRESSEVENTDATA_HPP_
# define _PNLOADINGPROGRESSEVENTDATA_HPP_

#include "pndefs.h"
#include "pnevent.h"

#include "PNEventData.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class			PNLoadingProgressEventData : public PNEventData
{
public:
  typedef enum
  {
	LSTATE_CMD_NONE,
	LSTATE_CMD_PUSH,
	LSTATE_CMD_POP
  }				lstate;
public:
  PNLoadingProgressEventData(){}

  lstate		cmd;
  std::string	item;
  float			progressVal;
};

//////////////////////////////////////////////////////////////////////////
};

#endif /*!_PNLOADINGPROGRESSEVENTDATA_HPP_*/
