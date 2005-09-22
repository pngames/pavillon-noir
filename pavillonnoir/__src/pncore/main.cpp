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
#include <fx.h>

#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif

#include "myCEGUI.h"

#include "pndefs.h"
#include "pnevent.h"
#include "pnplugins.h"
#include "pnrender.h"
#include "pnevent.h"
#include "pnresources.h"
#include "pnmath.h"

#include "PNQuatf.hpp"

#include "PNFoxMainWindow.hpp"
#include "PNLoadPlugins.hpp"

#include "PNConsole.hpp"

#include "PNGUIMenuRoot.hpp"

#include "PNGameInterface.hpp"

#include "PN3DObject.hpp"
#include "PN3DModel.hpp"
#include "PN3DMaterial.hpp"

#include "PNSoundInterface.hpp"
#include "PNPhysicsInterface.hpp"

#include <fx3d.h>
#include <PNQuatf.hpp>

using namespace PN;
using namespace std;

int	  main(int argc, char* argv[])
{	
  PNQuatf		quaty;
  quaty.fromDegrees(0.0f, 90.0f, 0.0f);

  PNMatrixTR4f	mat;
  mat.loadIdentity();
  mat.setRotationQuaternion(quaty);

  std::cout << quaty * PNVector3f::NEGATIVE_UNIT_Z  << std::endl;
  std::cout << mat * PNVector3f::NEGATIVE_UNIT_Z  << std::endl;

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  
  /*FXQuatf	fxq;
  fxq.setRollPitchYaw(45.0f, 90.0f, 45.0f);

  quaty.setGetPitchYaw(x,y,z);

  cout << fxq.x << " " << fxq.y << " " << fxq.z << " " << fxq.w << endl;*/
 
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
  gameWindowLauncher.run();
  
  if (returnState == true)
  {  	
	loadPlugins->launchPlugins();
	PNConsole::init();

	PNRendererInterface* ri = PNRendererInterface::getInstance();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// PNSound Interface

	PNSoundInterface *si = PNSoundInterface::getInstance();

	if (si != NULL)
	{
	  si->setListenerOrientation(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	  si->setListenerPosition(0.0, 0.0, 0.0);

	  std::string zicPath = DEF::musicFilePath + "Honneur_PavillonNoir.ogg";
	  //std::string sound = DEF::soundsFilePath + "arrive.ogg";
	  //std::string sound2 = DEF::soundsFilePath + "redalert.ogg";
	  std::string click_menu = DEF::soundsFilePath + "menu_click.ogg";
		
	  //si->createNewSound("arrive", sound.c_str(), FALSE, 0.0, 0.0, 0.0);
	  //si->createNewSound("redalert", sound2.c_str(), FALSE, 0.0, 0.0, 0.0);
	  si->createNewSound("click", click_menu.c_str(), FALSE, 0.0, 0.0, 0.0);

	  if (si->createNewSound("theme", zicPath.c_str(), TRUE, 0.0, 0.0, 0.0) != 0)
	  {
		si->changeSoundVolume("theme", 0.0);	
		si->playSound("theme");
	  }
	}

	//////////////////////////////////////////////////////////////////////////

	ri->initRender(800, 600, 32, "Pavillon Noir", false);

	new CEGUI::System((CEGUI::Renderer*)ri->getGUIRenderer());
	ri->initGUI();

	PNGUIMenuRoot*	rootmenu = new PNGUIMenuRoot();
	//PNGUIConsole*	guiconsole = new PNGUIConsole();

	//////////////////////////////////////////////////////////////////////////
	///					Init of the event's manager						   ///
	//////////////////////////////////////////////////////////////////////////
	
	PNEventManager*		pneventmngr;
	
	pneventmngr = PNEventManager::getInstance();
	pneventmngr->init();

	//////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////
	////                Starts rendering                                  ////
	//////////////////////////////////////////////////////////////////////////
	
	ri->run();

	if (si != NULL)
	  delete si;
  }
  ////////////////////////////////////////
/*
  char c;

  std::cout << "Appuyez sur une touche pour continuer" << std::endl;
  fread(&c, 1, 1, stdin);
*/

  return 0;
}
