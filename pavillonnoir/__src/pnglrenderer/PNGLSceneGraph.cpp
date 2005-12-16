/*
* PNGLSceneGraph.cpp
* 
* Description :
* PNGLSceneGraph definition
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
#include "pnevent.h"

#include "PNGameEventData.hpp"
#include "PN3DGround.hpp"
#include "PNRendererInterface.hpp"
#include "PNPhysicalObject.hpp"
#include "PNGLSkyBox.hpp"

#include "PNGLSceneGraph.hpp"

using namespace PN;
using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNGLSceneGraph*		PNGLSceneGraph::_instance = NULL;

PNGLSceneGraph*		PNGLSceneGraph::getInstance()
{
  if (_instance == NULL)
	return new PNGLSceneGraph();

  return _instance;
}

PNGLSceneGraph::PNGLSceneGraph()
{
  _inGame = false;

  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PNGLSceneGraph::_onMPStarted));
  PNEventManager::getInstance()->addCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PNGLSceneGraph::_onMPEnded));
}

PNGLSceneGraph::~PNGLSceneGraph()
{
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MP_STARTED, EventCallback(this, &PNGLSceneGraph::_onMPStarted));
  PNEventManager::getInstance()->deleteCallback(PN_EVENT_MP_ENDED, EventCallback(this, &PNGLSceneGraph::_onMPEnded));
}

//////////////////////////////////////////////////////////////////////////

void
PNGLSceneGraph::_onMPStarted(pnEventType type, PNObject* source, PNEventData* ed)
{
  _inGame = true;
}

void
PNGLSceneGraph::_onMPEnded(pnEventType type, PNObject* source, PNEventData* ed)
{
  _inGame = false;
}

//////////////////////////////////////////////////////////////////////////

void
PNGLSceneGraph::resizeGLWindow(pnint width, pnint height)
{
  _renderCam.resizeGLWindow(width, height);
}

void
PNGLSceneGraph::initFrame()
{

}

PNGLRendererCamera&
PNGLSceneGraph::getRenderCamera()
{
  return _renderCam;
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNGLSceneGraph::render(pnuint deltaTime, pnuint time)
{
  if (!_inGame)
	return PNEC_SUCCESS;

  PNGameUpdateEventData gameUpdateData((pnfloat)deltaTime, time);
  
  PNEventManager::getInstance()->sendEvent(PN_EVENT_GAME_UPDATE, 0, &gameUpdateData);
  PNEventManager::getInstance()->sendEvent(PN_EVENT_PU_START, 0, &gameUpdateData);

  ////////////////////////////////
  // Initialise render buffer

  glColor3f(1.0f, 1.0f, 1.0f);

  //////////////////////////////////////////////////////////////////////////

  _renderCam.update(deltaTime);

  ////////////////////////////////
  // PLACE RENDER CAMERA

  _renderCam.updateViewMatrix();

  //////////////////////////////////////////////////////////////////////////
  
  PNEventManager::getInstance()->sendEvent(PN_EVENT_RSU_STARTING, this, NULL);

  //////////////////////////////////////////////////////////////////////////

  if (PNGLSkyBox::getInstance()->isEnabled())
  {
	glPushMatrix();
	{
	  glTranslatef(_renderCam.getCoord().x, _renderCam.getCoord().y, _renderCam.getCoord().z);
	  PNGLSkyBox::getInstance()->render();
	}
	glPopMatrix();
  }

  /////////////////////////////////
  // RENDER PNGROUND

  PN3DGround::getInstance()->render(_renderCam);

  //////////////////////////////////////////////////////////////////////////
  // RENDER 3D OBJETCTS
  //////////////////////////////////////////////////////////////////////////
pnfloat scolor[4] = {1.0f, 1.0f, 1.0f, 0.3f};
PNPoint3f lpos(-200.0f, 9000.0f, 500.0f);
//glDisable(GL_LIGHTING);
PNRendererInterface::getInstance()->renderSphere(100.0, 20, 20, scolor, lpos);

  //glEnable(GL_LIGHTING);
  //glLightfv(GL_LIGHT0, GL_POSITION, Light1Pos);

  PNLOCK_BEGIN(&_renderCam);
  {
	const PN3DObjList& objectToRend = _renderCam.getListObj();

	for (PN3DObjList::const_iterator it = objectToRend.begin(); it != objectToRend.end(); ++it)
	{
	  glPushMatrix(); // Create temporary context for 3Dobject placement
	  {
		PN3DObject* obj = *it;

		static PNMatrix4f transMatrix;
		transMatrix.loadIdentity();

		PNLOCK_BEGIN(obj);
		{
		  const PNPoint3f&  pos = obj->getCoord();
		  const PNPoint3f&  offset = obj->getPhysicalObject() == NULL ? PNPoint3f::ZERO : obj->getPhysicalObject()->getOffset();
		  const PNQuatf&  orient = obj->getOrient();

		  transMatrix.setRotationQuaternion(orient);
		  transMatrix.setTranslation(pos);
		  transMatrix.addTranslation(offset);

		  glMultMatrixf(transMatrix.getMatrix());

		  glTranslatef(-offset.x, -offset.y, -offset.z);
		  obj->render();
		}
		PNLOCK_END(obj);
	  }
	  glPopMatrix(); // Return to root context
	}
  }
  PNLOCK_END(&_renderCam);

  //////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
  PNPoint3f	ax(PNPoint3f::ZERO);
  pnfloat	color[4] = {0.0f, 0.0f, 0.0f, 1.0f};

  ax.x = 100.0f;
  color[0] = 1.0f;

  PNRendererInterface::getInstance()->renderLink(PNPoint3f::ZERO, ax, color);
  ax.x = 0.0f;
  color[0] = 0.0f;

  ax.y = 100.0f;
  color[1] = 1.0f;
  PNRendererInterface::getInstance()->renderLink(PNPoint3f::ZERO, ax, color);
  ax.y = 0.0f;
  color[1] = 0.0f;

  ax.z = 100.0f;
  color[2] = 1.0f;
  PNRendererInterface::getInstance()->renderLink(PNPoint3f::ZERO, ax, color);
  ax.z = 0.0f;
  color[2] = 0.0f;
#endif

  //////////////////////////////////////////////////////////////////////////

  PNEventManager::getInstance()->sendEvent(PN_EVENT_RSU_ENDING, this, NULL);

  return PNEC_SUCCESS;
}

};
