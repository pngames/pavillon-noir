/*
 * PNInfoPanel.hpp
 * 
 * Description :
 * PNInfoPanel declaration
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

#ifndef _PNINFOPANEL_HPP_
# define _PNINFOPANEL_HPP_

#include <SDL/SDL.h>
#include "myCEGUI.h"

#include "pnevent.h"

namespace PN{
  class PNInfoPanel
  {
	/*/////////////////////////////////////////////////////////////////////////////
	/                                   Properties                                /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
  private:
	int		  _panelState;
	int		  _updateFreq;
	int		  _updateFreqU;
	int		  _skipCount;
	bool	  _fpsVisible;
	bool	  _triVisible;
	bool	  _panelVisible;
	float	  _minFPS;
	float	  _maxFPS;
	float	  _FPS;

	int		  _nbTriBSP;
	int		  _nbTriOBJDYN;
	int		  _nbTriCEGUI;
	int		  _nbTriTOTAL;

	/*/////////////////////////////////////////////////////////////////////////////
	/                                    Methods                                  /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	void  runInfoPanel();
	void  showTRI(pnEventType type, PNObject* source, PNEventData* data);
	void  showFPS(pnEventType type, PNObject* source, PNEventData* data);
	void  setUpdateFreq(int upd);
	
  private:
	void  ShowHideAllFPS(bool showhide);
	void  ShowHideAllTri(bool showhide);
	void  hide(char* item);
	void  show(char* item);
	void  calculFPS();
	void  calculTRI();
	void  setTriBSP();
	void  setTriObjDyn();
	void  setTriCEGUI();
	bool  eventHandler(const CEGUI::EventArgs& e);

	/*/////////////////////////////////////////////////////////////////////////////
	/                           Constructors / Destructor                         /
	/////////////////////////////////////////////////////////////////////////////*/
  public:
	PNInfoPanel();
	~PNInfoPanel();
  private: 
  };
}
#endif /* _PNINFOPANEL_HPP_ */
