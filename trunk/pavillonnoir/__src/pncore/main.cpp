/*
 * main.cpp
 * 
 * Description :
 * Entry point of pncore
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

#include <iostream>
#include <stdio.h>
#include <string>

#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif

#include "myCEGUI.h"

#include "pndefs.h"
#include "pnevent.h"
#include "pnrender.h"
#include "pnresources.h"
#include "pni18n.h"

#include "PNFoxMainWindow.hpp"
#include "PNLoadPlugins.hpp"

#include "PNConsole.hpp"

#include "PNGUIMenuRoot.hpp"
#include "PNGUIStateManager.hpp"
#include "PNGUILoadingScreen.hpp"

#include "PNConf.hpp"

//////////////////////////////////////////////////////////////////////////

#include "PNQuatf.hpp"
#include "PNNormal3f.hpp"

using namespace PN;

//////////////////////////////////////////////////////////////////////////

int	  main(int argc, char* argv[])
{
  PNQuatf		quaty;
  quaty.fromDegrees(0.0f, 0.0f, 0.0f);

  std::cout << quaty  << std::endl;

  PNNormal3f  mod(-0.0189894, 2.6773e-006, 0.99982);

  std::cout << "mod: " << mod.getVector() << std::endl;

  pnfloat angle = mod.degreeRange2Pi(PNVector3f::UNIT_X, PNVector3f::NEGATIVE_UNIT_Z);

  std::cout << "angle: " << angle << std::endl;

  //////////////////////////////////////////////////////////////////////////
  
  std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;

  PNPoint3f  coordTarget(1.0f, 0.0f, 0.0f);
  PNPoint3f  coordCamera(0.0f, 0.0f, -1.0f);

  PNNormal3f	targetVector(coordTarget - coordCamera);

  pnfloat	norm = sqrtf(SQNBR(targetVector.getX()) + SQNBR(targetVector.getZ()));
  double	ps = (PNVector3f::NEGATIVE_UNIT_Z.x * targetVector.getX() / norm) + (PNVector3f::NEGATIVE_UNIT_Z.z * targetVector.getZ() / norm);
  double	pcy = (PNVector3f::NEGATIVE_UNIT_Z.x * targetVector.getX() / norm) - (PNVector3f::NEGATIVE_UNIT_Z.z * targetVector.getZ() / norm);

  pnfloat yangle = ABS(ps) > 1.0f ? 0.0f : acosf((float)ps);
  yangle = pcy > 0 ? -yangle : yangle;

  std::cout << RADIAN_TO_DEGREE_F(targetVector.radianRange2Pi(PNVector3f::NEGATIVE_UNIT_Z, PNVector3f::NEGATIVE_UNIT_X)) << std::endl;

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  
  /*char c;
  std::cout << "Appuyez sur une touche pour continuer" << std::endl;
  fread(&c, 1, 1, stdin);
  
  if (c == 'q')
    return 0;*/

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  chdir("../");

  char buf[512] = "";
  std::cout <<  getcwd(buf, 511) << std::endl;

  //////////////////////////////////////////////////////////////////////////
  // Initialize configuration
 
  PNI18n::getInstance()->unserializeFromPath("datafiles/i18n/default.xml");
  
  //////////////////////////////////////////////////////////////////////////
  // Load Plugins

  PNLoadPlugins* loadPlugins = new PNLoadPlugins();

  loadPlugins->addDefaultPlugin("pnglrenderer");
  loadPlugins->addDefaultPlugin("pnimporter");
  loadPlugins->addDefaultPlugin("pnsound");
  loadPlugins->addDefaultPlugin("pnscript");
  loadPlugins->addDefaultPlugin("pnopal");

  ////////////////////////////////////////
  // GUI
  bool					returnState = false;
  FXApp					gameWindowLauncher("Pavillon Noir","Pavillon Noir");

  gameWindowLauncher.init(argc, argv);

  PNFoxMainWindow		*mainWindow = new PNFoxMainWindow(&gameWindowLauncher, &returnState);
  gameWindowLauncher.create();
  mainWindow->show(PLACEMENT_SCREEN);
  gameWindowLauncher.run();
  
  if (returnState == true)
  {  	
	loadPlugins->launchPlugins();
	PNConsole::init();

	PNRendererInterface* ri = PNRendererInterface::getInstance();

	//////////////////////////////////////////////////////////////////////////

	ri->initRender();

	new CEGUI::System((CEGUI::Renderer*)ri->getGUIRenderer());
	ri->initGUI();
	
	PNGUILoadingScreen::getInstance();

	PNGUIStateManager::getInstance();
	if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::NONE && PNGUIStateManager::getInstance()->getSubState() == PNGUIStateManager::NONE)
	  PNGUIMenuRoot::getInstance()->startGUI();

	//////////////////////////////////////////////////////////////////////////
	///					Init of the event's manager						   ///
	//////////////////////////////////////////////////////////////////////////
	
	PNEventManager*		pneventmngr;
	
	pneventmngr = PNEventManager::getInstance();
	pneventmngr->init();

	//////////////////////////////////////////////////////////////////////////
	////                Starts rendering                                  ////
	//////////////////////////////////////////////////////////////////////////
	
	ri->run();
  }

  ////////////////////////////////////////

  return 0;
}
