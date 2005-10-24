/*
 * PNGUIMenuRoot.hpp
 * 
 * Description :
 * PNGUIMenuRoot declaration
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

#ifndef _PNGUIMENUROOT_HPP_
# define _PNGUIMENUROOT_HPP_

#include "myCEGUI.h"

#include "pndefs.h"
#include "pnplugins.h"
#include "pnrender.h"

namespace PN{
  class PNGUIMenuRoot
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  private:
	
	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	void  hideMenuRoot();
	void  showMenuRoot();
  private:
	bool  handleNew(const CEGUI::EventArgs& e);
	bool  handleQuit(const CEGUI::EventArgs& e);
	bool  handleLoad(const CEGUI::EventArgs& e);
	bool  handleCredits(const CEGUI::EventArgs& e);
	bool  handleOptions(const CEGUI::EventArgs& e);
	void  setupEventHandlers();

	//////////////////////////////////////////////////////////////////////////
	
	static void	 loadLevel(const std::string&, std::istream& i);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNGUIMenuRoot();
	~PNGUIMenuRoot();
  private:

  };
}

#endif /*_PNGUIMENUROOT_HPP_*/
