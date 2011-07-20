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
#include "pnresources.h"

#include "PNGUIGame.hpp"
#include "PNGUIStateManager.hpp"
#include "PNGUIDeath.hpp"

using namespace PN;

#define FADE_TIME                   1000

namespace PN
{
   PNGUIDeath* PNGUIDeath::_instance = NULL;

  PNGUIDeath::PNGUIDeath()
  {
	_pnDeath = CEGUI::WindowManager::getSingleton().loadWindowLayout(PNResourcesManager::getInstance()->findPath(PNRT_layout, "PNGUIDeath.layout"));
	_pnDeath->hide();
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(_pnDeath);
	//_pnStatText = (CEGUI::StaticText*)CEGUI::WindowManager::getSingleton().getWindow("PNGUIDeath/BackMenuText");
	_pnStatText = CEGUI::WindowManager::getSingleton().getWindow("PNGUIDeath/BackMenuText");
	_pnStatText->hide();
	
	//_deathImage = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"TaharezLook/StaticImage", "DeathImages/DeathScreen");
	_deathImage = CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"TaharezLook/StaticImage", "DeathImages/DeathScreen");
	_deathImage->setImage("DeathImages", "DeathImages/DeathScreen");
	_deathWnd = (CEGUI::Window*)( CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "death_wnd"));

	_deathWnd->addChildWindow(_deathImage);

	_pnDeath->addChildWindow(_deathWnd);

	_deathImage->setBackgroundEnabled( false );
	_deathImage->setFrameEnabled( false );
	
	_fadeTimer = 0;
	_pnDeath->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::Event::Subscriber(&PNGUIDeath::eventKeyPressedHandler, this));
  }

  PNGUIDeath::~PNGUIDeath()
  {
	_pnDeath->destroy();
  }

  PNGUIDeath* PNGUIDeath::getInstance()
  {
	if (_instance == NULL)
	  _instance = new PNGUIDeath();
	return _instance;
  }


  void PNGUIDeath::startGUI()
  {
	if (PNGUIStateManager::getInstance()->getMainState() == PNGUIStateManager::INGAME && 
	  PNGUIStateManager::getInstance()->getSubState() == PNGUIStateManager::NONE)
	{
	  PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_PAUSE, NULL, NULL);
	  PNGUIStateManager::getInstance()->setSubState(PNGUIStateManager::DEAD_WINDOW);
	  
	  _deathWnd->setPosition( CEGUI::Point( 0.5f, 0.5f ) );
	  _deathImage->setSize( CEGUI::Size( 1.0f, 1.0f ) );
	  _deathImage->setPosition( CEGUI::Point( 0.0f, 0.0f ) );

	  _pnStatText->hide();
	  _pnDeath->show();
	  _winState = winFadeIn;
	  PNEventManager::getInstance()->addCallback(PN_EVENT_UPDATE_GUI, EventCallback(this, &PNGUIDeath::update));
	}
  }

  void PNGUIDeath::animFinished()
  {
	PNEventManager::getInstance()->deleteCallback(PN_EVENT_UPDATE_GUI, EventCallback(this, &PNGUIDeath::update));
	
	_pnStatText->show();
	_pnDeath->moveToFront();

	
  }

  bool PNGUIDeath::eventKeyPressedHandler(const CEGUI::EventArgs& e)
  {
	//dechargement map et retour au menu principal (faire statut dans la classe correspondante)
	_pnDeath->hide();
	_winState = winHidden;
	PNEventManager::getInstance()->sendEvent(PN_EVENT_MP_UNPAUSE, NULL, NULL);
	PNGUIStateManager::getInstance()->LoadManager(NULL, PNGUIStateManager::MENUROOT);
	
	return true;
  }

  float PNGUIDeath::max(float a, float b) { 
     return (a < b) ? b : a; 
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
		  animFinished();
		  return;
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

		float fadefac = _fadeTimer / FADE_TIME;
		float tmpVal = 0.5f - fadefac * 0.5f;
		if (tmpVal > 0)
		{
		  CEGUI::Point pos = CEGUI::Point( tmpVal, tmpVal );
		  std::cout << pos.d_x << "  " << pos.d_y << std::endl;
			_deathWnd->setPosition( pos );
		  CEGUI::Size sizeTmp( fadefac,  fadefac ); 
		  
		  _deathWnd->setSize( sizeTmp );
		  _deathWnd->setAlpha( max( 0.2f, fadefac ) );
		}
		

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

