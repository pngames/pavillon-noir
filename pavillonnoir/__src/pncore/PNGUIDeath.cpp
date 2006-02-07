/*
* PNGUIDeath.cpp
* 
* Description :
* PNGUIDeath declaration
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


#include "pndefs.h"
#include "pnrender.h"
#include "PNGUIGame.hpp"
#include "PNGUIStateManager.hpp"
#include "PNGUIDeath.hpp"

using namespace PN;

#define FADE_TIME                   300

namespace PN
{
   PNGUIDeath* PNGUIDeath::_instance = NULL;

  PNGUIDeath::PNGUIDeath()
  {
	_pnDeath = CEGUI::WindowManager::getSingleton().loadWindowLayout("./datafiles/layouts/PNGUIDeath.layout");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_pnDeath);

	if (CEGUI::ImagesetManager::getSingleton().isImagesetPresent("DeathImages") == false)
	  CEGUI::ImagesetManager::getSingleton().createImageset("./datafiles/imagesets/DeathScreen.imageset");
	
	_deathImage = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"TaharezLook/StaticImage", "DeathImages/DeathScreen");
	_deathWnd = (CEGUI::Window*)( CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "death_wnd" ) );
//	_deathWnd->addChildWindow(_deathImage);

	_deathWnd->setPosition( CEGUI::Point( 0.5f, 0.5f ) );
	//_deathWnd->setSize(CEGUI::Size ( 0.5f,  0.5f)); 

//	_deathWnd->hide();
	//_rootWin->addChildWindow(_deathWnd);

	
	_deathImage->setSize( CEGUI::Size( 1.0f, 1.0f ) );
	_deathImage->setPosition( CEGUI::Point( 0, 0 ) );
	_deathImage->setBackgroundEnabled( false );
	_deathImage->setFrameEnabled( false );
	
	_fadeTimer = 0;
  }

  PNGUIDeath::~PNGUIDeath()
  {

  }

  PNGUIDeath* PNGUIDeath::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIDeath();
	return _instance;
  }


  void PNGUIDeath::show()
  {
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_deathImage);
	_deathWnd->show();
	_deathWnd->moveToFront();
	_deathWnd->activate();
	_winState = winFadeIn;
	//PNEventManager::getInstance()->addCallback(PN_EVENT_UPDATE_GUI, EventCallback(this, &PNGUIDeath::update));
	
	
  }

  void PNGUIDeath::hide()
  {
	PNEventManager::getInstance()->deleteCallback(PN_EVENT_UPDATE_GUI, EventCallback(this, &PNGUIDeath::update));
	_winState = winHidden;

	//dechargement map et retour au menu principal (faire statut dans la classe correspondante)
  }

  void PNGUIDeath::update(pnEventType type, PNObject* source, PNEventData* data)
  {

	float deltaTime = PNRendererInterface::getInstance()->getCurrentDelta();

	switch( _winState )
	{
	case winFadeIn:
	  {
		/*if (_consoleVisibility == false)
		  _pnConsole->show();*/
		if ( _fadeTimer > FADE_TIME )
		{
		  _fadeTimer = 0;
		  _winState = winVisible;
		 /*

		  CEGUI::Size sizeTmp( 1.0, 1.0); 
		  _pnConsole->setSize(sizeTmp);

		  _pnConsole->setAlpha( _frameAlphaValue );

		  _editBox->activate();
		  _cursorVisibility = CEGUI::MouseCursor::getSingleton().isVisible();
		  if (_cursorVisibility == false) 
			CEGUI::MouseCursor::getSingleton().show();
		  break;*/
		}
//		_consoleVisibility = true;
		_fadeTimer += deltaTime;

		float fadefac = _fadeTimer / FADE_TIME/100;

		CEGUI::Point pos = CEGUI::Point( 0.5f - fadefac * 0.5f, 0.5f - fadefac * 0.5f );
		_deathWnd->setPosition( pos );
		CEGUI::Size sizeTmp( fadefac,  fadefac ); 
		_deathWnd->setSize( sizeTmp );
		_deathWnd->setAlpha( std::max( 0.2f, fadefac ) );



/*
		float tempAlpha = fadefac * _frameAlphaValue;

		if (tempAlpha > _frameAlphaValue)
		  _pnConsole->setAlpha( _frameAlphaValue );
		else
		  _pnConsole->setAlpha(tempAlpha);

		CEGUI::Size sizeTmp( fadefac,  fadefac ); 
		_pnConsole->setSize( sizeTmp );


		

		_introTimer += deltaTime;
		if ( _introTimer > INTRO_FADEIN_TIME )
		  return;

		// fade-in the intro image
		float imgSize = _introTimer / float( INTRO_FADEIN_TIME );
		CEGUI::Point pos = CEGUI::Point( 0.5f - imgSize * 0.5f, 0.5f - imgSize * 0.5f );
		_p_wndIntro->setPosition( pos );
		_intoImageSize = CEGUI::Size( imgSize, imgSize );
		_p_wndIntro->setSize( _intoImageSize );
		_p_wndIntro->setAlpha( std::max( 0.2f, imgSize ) );*/
	  }
	  break;

	

	default:
	  break;

	}


  }
}