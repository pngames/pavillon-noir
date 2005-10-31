/*
 * PNGLRenderer.cpp
 * 
 * Description :
 * PNGLRenderer definition
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
#include <list>

#include <SDL/SDL.h>

#include "pndefs.h"
#include "pnevent.h"
#include "pnexception.h"
#include "PNGameEventData.hpp"
#include "pnresources.h"

#include "PNVideoEventData.hpp"
#include "PNGLRenderer.hpp"

#include "PNGLRendererObject.hpp"
#include "PNSDLEvent.hpp"
#include "PNGLRendererCamera.hpp"

#include "PNGameInterface.hpp"
#include "PNGUIConsole.hpp"

#include "PNMatrix4f.hpp"
#include "PNPoint.hpp"
#include "PNQuatf.hpp"
#include "PN3DModel.hpp"
#include "PNGLTexture.hpp"
#include "PNGLMaterial.hpp"

#include "PN3DGround.hpp"
#include "PNPhysicsInterface.hpp"
#include "PN3DCamera.hpp"

#include "PNWayPoint.hpp"
#include "PNCharacter.hpp"

//#include "PNGLRenderUpdateEventData.hpp"

#include "PNGLVideo.hpp"

#include <renderers/OpenGLGUIRenderer/openglrenderer.h>

using namespace PN;
using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

PNGLRenderer*  PNGLRenderer::getInstance()
{
  if (_instance == NULL)
	return new PNGLRenderer();

  return (PNGLRenderer*)_instance;
}

PNGLRenderer::PNGLRenderer()
{
  _guirenderer = NULL;

  //////////////////////////////////////////////////////////////////////////
  
  _converter[PN_TRIANGLES] = GL_TRIANGLES;
  _converter[PN_TRIANGLE_STRIP] = GL_TRIANGLE_STRIP;
  _converter[PN_TRIANGLE_FAN] = GL_TRIANGLE_FAN;
  _converter[PN_POINTS] = GL_POINTS;
  _converter[PN_LINES] = GL_LINES;
  _converter[PN_LINE_STRIP] = GL_LINE_STRIP;

  _converter[PN_T2F_N3F_V3F] = GL_T2F_N3F_V3F;
  _converter[PN_T2F_C4F_N3F_V3F] = GL_T2F_C4F_N3F_V3F;

  //////////////////////////////////////////////////////////////////////////
  
  PNEventManager::getInstance()->addCallback(PN_EVENT_VIDEO_START, EventCallback(this, &PNGLRenderer::_onPlayVideo));
}

PNGLRenderer::~PNGLRenderer()
{
  if (_guirenderer != NULL)
	delete _guirenderer;

  delete CEGUI::System::getSingletonPtr();
}

//////////////////////////////////////////////////////////////////////////

void		PNGLRenderer::_onPlayVideo(pnEventType type, PNObject* source, PNEventData* ed)
{
  PNVideoEventData*	videoEventData = (PNVideoEventData*)ed;

  PNGLVideo		video;
  
  video.unserializeFromFile(fs::path(videoEventData->path, fs::native));
  
  video.startAnimation();
}

//////////////////////////////////////////////////////////////////////////

GLenum		PNGLRenderer::convertFlag(pnrenderflag flag)
{
  return _converter[flag];
}

//////////////////////////////////////////////////////////////////////////

pnuint
PNGLRenderer::getTicks()
{
  return SDL_GetTicks();
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRenderer::enable(pnrenderflag flag)
{
  
}

void
PNGLRenderer::disable(pnrenderflag flag)
{
  
}

//////////////////////////////////////////////////////////////////////////

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

void
PNGLRenderer::init()
{
  // init DevIL libs we use
  ilInit();
  iluInit();
  ilutInit();
  ilutRenderer(ILUT_OPENGL);
  ilutEnable(ILUT_OPENGL_CONV);
}

void
PNGLRenderer::initRender(pnuint widht, pnuint height, pnuint bpp, pnchar* title, pnbool fullscreen)
{
  initSDL(widht, height, bpp, title, fullscreen);
  initGL(widht, height);
}

/*!
\brief
Sets the flags for the SDL window.
\param flags
Int pointer that contains SDL flags.
\param fullscreen
Bool specifies the fullscreen state of the SDL window.
*/
void
PNGLRenderer::setSDLFlags(int *flags, bool fullscreen)
{
  const SDL_VideoInfo *videoInfo;
  int 		videoFlags;

  videoInfo = SDL_GetVideoInfo();
  videoFlags  = SDL_OPENGL;
  videoFlags |= SDL_GL_DOUBLEBUFFER;
  videoFlags |= SDL_HWPALETTE;

  if (videoInfo->hw_available)
  {
	std::cout << "Surface stored in video memory" << std::endl;
	videoFlags |= SDL_HWSURFACE;
  }
  else
  {
	std::cout << "Surface stored in system memory" << std::endl;
	videoFlags |= SDL_SWSURFACE;
  }
  if (videoInfo->blit_hw)
  {
	std::cout << "Surface blit uses hardware acceleration" << std::endl;
	videoFlags |= SDL_HWACCEL;
  }

  if (fullscreen == true)
	videoFlags |= SDL_FULLSCREEN;
  
  *flags = videoFlags;
  return;
}

/*!
\brief
Init all main parameters of SDL.
\param width
Int describes width of the SDL window.
\param height
Int describes height of the SDL window.
\param bpp
Int describes bits per pixel of the SDL window.
\param title
String describes the SDL window title.
\param fullscreen
Bool specifies the fullscreen state of the SDL window. 
*/
void
PNGLRenderer::initSDL(int widht, int height, int bpp, char* title, bool fullscreen)
{
  std::cout << "--== SDL init start ==--" << std::endl;
	  
  SDL_Surface		*screen = NULL;
  int				videoFlags;

  SDL_Init(SDL_INIT_VIDEO);
  setSDLFlags(&videoFlags, fullscreen);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  screen = SDL_SetVideoMode(widht, height, bpp, videoFlags);
  SDL_WM_SetCaption(title, NULL);
  SDL_EnableUNICODE(1);
 // SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
  
  std::cout << "--== SDL init end ==--" << std::endl;
  return;
}

void
PNGLRenderer::initGL(GLsizei width, GLsizei height)
{
  std::cout << "--== OpenGL init start ==--" << std::endl;
  
  // Initialize GL context
  glRenderMode(GL_RENDER);

  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDepthRange(0.0,1.0);
  glClearDepth(1.0);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  //glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  //////////////////////////////////////////////////////////////////////////
  
  float Light1Dif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  float Light1Spec[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  float Light1Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);
  glLightfv(GL_LIGHT0, GL_AMBIENT, Light1Amb);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  //////////////////////////////////////////////////////////////////////////
  
  _scene.resizeGLWindow(width, height);
  
  std::cout << "--== OpenGL init end ==--" << std::endl;
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRenderer::run()
{
  _isProgramLooping = true;

  pnuint		lastLoopDate = getTicks();
  pnuint		deltaTime;
  pnuint		currentLoopDate = getTicks();
  SDL_Event		event;

 
  PNSDLEvent*	sdlEvent = new PNSDLEvent();

  //float Light1Pos[4] = {0.0f, 0.0f, 40.0f, 1.0f};

  while (_isProgramLooping)												
  {
    //timer
    currentLoopDate = getTicks();
    deltaTime = currentLoopDate - lastLoopDate;
    lastLoopDate = currentLoopDate;

	while (SDL_PollEvent(&event))
	  sdlEvent->pnSdlEvent(&event);

	sdlEvent->pninjectTimePulse();
	////////////////////////////////////////////
	if (_isProgramLooping == true)
	{
	  //////////////////////////////////////////////////////////////////////////
	  // INIT
	  //////////////////////////////////////////////////////////////////////////
	  
	  // Reset matrices
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();

	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	  PNEventManager::getInstance()->sendEvent(PN_EVENT_RU_STARTING, this, NULL);

	  //////////////////////////////////////////////////////////////////////////
	  // RENDER SCENE
	  //////////////////////////////////////////////////////////////////////////

	  _scene.render(deltaTime);

	  //////////////////////////////////////////////////////////////////////////
	  // END
	  //////////////////////////////////////////////////////////////////////////

	  PNEventManager::getInstance()->sendEvent(PN_EVENT_RU_ENDING, this, NULL);

	  //////////////////////////////////////////////////////////////////////////
	  // APPLY
	  //////////////////////////////////////////////////////////////////////////

	  glFlush(); // force lexecution des commande opengl avant le rendu
	  SDL_GL_SwapBuffers(); // inverser le buffer decriture et le buffer de rendu
	}
  }

  delete sdlEvent;
}

void
PNGLRenderer::updateGUI(pnEventType type, PNObject* source, PNEventData* data)
{
  //////////////////////////////////
  // CEGUI
   PNEventManager::getInstance()->sendEvent(PN_EVENT_UPDATE_GUI,0, NULL);

  //DRAW fps/tri info panel
  _infoPanel->runInfoPanel();

  //DRAW CE GUI HERE
  CEGUI::System::getSingleton().renderGUI();
}

void
PNGLRenderer::endRendering()
{
  _isProgramLooping = false;
  SDL_Quit();
}

//////////////////////////////////////////////////////////////////////////

PNRendererObject*
PNGLRenderer::newObj()
{
  return new PNGLRendererObject(*this);
}

PNRendererObject*
PNGLRenderer::newObj(void *interleave, pnuint size, pnrenderflag format,
					 pnuint  *index, pnuint nbIndex, pnrenderflag mode)
{
  PNGLRendererObject *my_obj = (PNGLRendererObject*)newObj();

  my_obj->setMode(mode);

  my_obj->setInterleaveArray(interleave, size, format);

  if (index != NULL)
	my_obj->setIndexBuffer(index, nbIndex);

  return my_obj;
}

PNRendererObject*
PNGLRenderer::newObj(pnfloat *vertices, pnfloat *normals, 
					 pnfloat *colors, 	pnfloat *textures, pnuint nbVerts,
					 pnuint  *index, pnuint nbIndex, pnrenderflag mode)
{
  PNGLRendererObject *my_obj = (PNGLRendererObject*)newObj();

  my_obj->setMode(mode);

  if (nbVerts != 0)
  {
	my_obj->setNbVerts(nbVerts);
	my_obj->setBuffer(PN_VARRAY, vertices);
	my_obj->setBuffer(PN_NARRAY, normals);
	my_obj->setBuffer(PN_CARRAY, colors);
	my_obj->setBuffer(PN_TCARRAY, textures);
  }

  if (index != NULL)
	my_obj->setIndexBuffer(index, nbIndex);

  return my_obj;
}

void
PNGLRenderer::deleteObj(PNRendererObject* obj)
{
  if (obj != NULL)
	delete (PNGLRendererObject*)obj;
}

//////////////////////////////////////////////////////////////////////////

/// Set the skyBox enabled or disabled
void
PNGLRenderer::setSkyBoxEnabled(pnbool enabled)
{
  throw PNException("Not implemented.");
}

/// Set the sky box properties
void
PNGLRenderer::setSkyBox(PNRendererObject* skyBox)
{
  throw PNException("Not implemented.");
}

/// Set the sky box properties
void
PNGLRenderer::setSkyBox(pnfloat* textCoords, PNRenderMaterial* skyBox)
{
  throw PNException("Not implemented.");
}

/// Set the sky box properties
void
PNGLRenderer::setSkyBox(PNRenderMaterial* top, PNRenderMaterial* bottom, PNRenderMaterial* left, PNRenderMaterial* right, PNRenderMaterial* front, PNRenderMaterial* back)
{
  throw PNException("Not implemented.");
}

//////////////////////////////////////////////////////////////////////////

PNRenderMaterial*
PNGLRenderer::newMaterial()
{
  return new PNGLMaterial();
}

void
PNGLRenderer::deleteMaterial(PNRenderMaterial* material)
{
  if (material != NULL)
	delete (PNGLMaterial*)material;
}

//////////////////////////////////////////////////////////////////////////

PNGLTexture*
PNGLRenderer::newTexture(void)
{
  return new PNGLTexture();
}

void
PNGLRenderer::deleteTexture(PNGLTexture* texture)
{
  if (texture != NULL)
  {
	delete texture;
  }
}

//////////////////////////////////////////////////////////////////////////

void
PNGLRenderer::renderSphere(pndouble radius, pnint slices, pnint stacks, const pnfloat* color)
{
  glColor4fv(color);
  glMaterialfv(GL_FRONT,  GL_DIFFUSE, color);

  GLUquadricObj* quad = gluNewQuadric();
  gluQuadricDrawStyle(quad, (GLenum)GLU_FILL);
  gluSphere(quad, radius, slices, stacks);
  gluDeleteQuadric(quad);
}

void
PNGLRenderer::renderBox(pnuint width, pnuint height, pnuint depth, const pnfloat* color)
{
  glColor4fv(color);
  glMaterialfv(GL_FRONT,  GL_DIFFUSE, color);

  pnfloat xmin =-0.5f * width;
  pnfloat xmax = 0.5f * width;
  pnfloat ymin =-0.5f * height;
  pnfloat ymax = 0.5f * height;
  pnfloat zmin =-0.5f * depth;
  pnfloat zmax = 0.5f * depth;

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(xmin, ymin, zmin);
	glVertex3f(xmin, ymax, zmin);
	glVertex3f(xmax, ymin, zmin);
	glVertex3f(xmax, ymax, zmin);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(xmax, ymin, zmin);
	glVertex3f(xmax, ymax, zmin);
	glVertex3f(xmax, ymin, zmax);
	glVertex3f(xmax, ymax, zmax);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(xmax, ymin, zmax);
	glVertex3f(xmax, ymax, zmax);
	glVertex3f(xmin, ymin, zmax);
	glVertex3f(xmin, ymax, zmax);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(xmin, ymin, zmax);
	glVertex3f(xmin, ymax, zmax);
	glVertex3f(xmin, ymin, zmin);
	glVertex3f(xmin, ymax, zmin);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(xmin, ymax, zmin);
	glVertex3f(xmin, ymax, zmax);
	glVertex3f(xmax, ymax, zmin);
	glVertex3f(xmax, ymax, zmax);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  {
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(xmin, ymin, zmax);
	glVertex3f(xmin, ymin, zmin);
	glVertex3f(xmax, ymin, zmax);
	glVertex3f(xmax, ymin, zmin);
  }
  glEnd();
}

void
PNGLRenderer::renderLink(const PNPoint& p1, const PNPoint& p2, const pnfloat* color, pnuint direction, pnfloat thickness)
{
  glPushAttrib(GL_CURRENT_BIT|GL_ENABLE_BIT|GL_LINE_BIT|GL_LIGHTING);
  glDisable(GL_LIGHTING);

  glBegin(GL_LINE_STRIP);
  {
	glColor4fv(color);
	glVertex3fv(p1);
	glVertex3fv(p2);

	// draw righ arrow
	// draw left arrow
  }
  glEnd();

  glPopAttrib();
}

//////////////////////////////////////////////////////////////////////////
// GUI

guiType
PNGLRenderer::getGUIType()
{
  return PN_GUI_CEGUI;
}

void*
PNGLRenderer::getGUIRenderer()
{
  if (_guirenderer == NULL)
	_guirenderer = new CEGUI::OpenGLRenderer(0, (int)_scene.getRenderCamera().getWidth(), (int)_scene.getRenderCamera().getHeight());

  return (_guirenderer);
}

/*!
\brief
Init CEGUI stuff.
*/
void
PNGLRenderer::initGUI()
{
  try
  {
	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Insane);
	CEGUI::SchemeManager::getSingleton().loadScheme("./datafiles/schemes/TaharezLook.scheme");
	CEGUI::SchemeManager::getSingleton().loadScheme("./datafiles/schemes/WindowsLook.scheme");
	CEGUI::SchemeManager::getSingleton().loadScheme("./datafiles/schemes/VanillaSkin.scheme");
	
	CEGUI::System::getSingleton().setTooltip("Vanilla/Tooltip");

	CEGUI::System::getSingleton().setDefaultMouseCursor("Vanilla-Images", "MouseArrow");
	//CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

	CEGUI::FontManager::getSingleton().createFont("./datafiles/fonts/verase-12.font");
	CEGUI::FontManager::getSingleton().createFont("./datafiles/fonts/verase-10.font");
	CEGUI::FontManager::getSingleton().createFont("./datafiles/fonts/verase-8.font");
	CEGUI::FontManager::getSingleton().createFont("./datafiles/fonts/verasebd-12.font");
	CEGUI::FontManager::getSingleton().createFont("./datafiles/fonts/verasebd-8.font");

	CEGUI::Window*	rootSheet =  CEGUI::WindowManager::getSingleton().createWindow((CEGUI::utf8*)"DefaultWindow", (CEGUI::utf8*)"rootSheet");
	rootSheet->setMetricsMode(CEGUI::Absolute);
	rootSheet->setPosition(CEGUI::Point(0, 0));
	rootSheet->setSize(CEGUI::Size(_scene.getRenderCamera().getWidth(), _scene.getRenderCamera().getHeight()));
	CEGUI::System::getSingleton().setGUISheet(rootSheet);
	rootSheet->activate();

	CEGUI::System::getSingleton().setDefaultFont((CEGUI::utf8*)"VeraSe-12");

	//init console
	PNGUIConsole::getInstance();

	PNEventManager::getInstance()->addCallback(PN_EVENT_RU_ENDING, EventCallback(this, &PNGLRenderer::updateGUI));
	_infoPanel = new PNInfoPanel();
  }
  catch (CEGUI::Exception)
  {
	std::cout << "CEGUI init problem, configuration files are missing" << std::endl;
  }  

  return;
}
//////////////////////////////////////////////////////////////////////////


};