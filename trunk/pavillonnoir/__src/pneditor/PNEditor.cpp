/*
 * PNEditor.cpp
 * 
 * Description :
 * PNEditor definition
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


////////////////////////////  DESCRIPTION /////////////////////////////////
/*
TODO decrire le fonctionnement de pneditor

PNPropertiesPanel
	list<PNConfigurableObject*> // objets 3D (PNGLShape) presents dans le panel
	PNPropertiesGrid
		list<PNPropertiesGridParameter*> // proprietes de l'objet
			PNConfigurableParameter*
		PNConfigurableObject // objet 3D courant (PNGLShape)
*/
//////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <fcntl.h>
#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif

#include <fx.h>
#include <fx3d.h>
#include <FXPNGIcon.h>
#include <boost/filesystem/operations.hpp>
#include <libxml/xmlreader.h>

#include "pndefs.h"
#include "pnxml.h"
#include "pneditorcommon.hpp"
#include "pnresources.h"
#include "pnplugins.h"
#include "PNPlugin.hpp"
#include "PNPluginManager.hpp"
#include "pnrender.h"

#include "PNGLShape.hpp"
#include "PNGLViewer.hpp"
#include "PNPropertiesPanel.hpp"
#include "PNConfigurableObject.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PN3DCamera.hpp"
#include "PNPropertiesGrid.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNWaypointObject.hpp"
#include "PNCharacter.hpp"
#include "PNEditor.hpp"

namespace fs = boost::filesystem;

namespace PN { namespace EDITOR
{

// Message Map PNEditor class
FXDEFMAP(PNEditor) PNEditorMap[] =
{
  //__Message_Type_____________ID________________________Message_Handler_____
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_ABOUT,			PNEditor::onCmdAbout),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_ABOUT_PNE,		PNEditor::onCmdAboutPNE),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_OPEN,			PNEditor::onCmdOpen),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_SAVE,			PNEditor::onCmdSave),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_SAVEAS,		PNEditor::onCmdSaveAs),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_EXPORT,		PNEditor::onCmdExport),

  FXMAPFUNC(SEL_UPDATE,		PNEditor::ID_QUERY_MODE,	PNEditor::onUpdMode),
  FXMAPFUNC(SEL_COMMAND,	FXWindow::ID_QUERY_MENU,	PNEditor::onQueryMenu),

  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_GENERAL,		PNEditor::onCmdGenView),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_OBJECTS,		PNEditor::onCmdObjView),

  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_SKYBOX,		PNEditor::onCmdSkyboxView),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_GROUND,		PNEditor::onCmdGroundView),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_STATIC,		PNEditor::onCmdStaticView),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_DYNAMIC,		PNEditor::onCmdDynView),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_WAYPOINTS,		PNEditor::onCmdWPView),
  // grid
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_GRID_OBJ_SEL,	PNEditor::onCmdGridObjSel),
  FXMAPFUNC(SEL_COMMAND,	PNEditor::ID_COPYOBJ,		PNEditor::onCmdCopyObj)
};

// Macro for the PNEditor class hierarchy implementation
FXIMPLEMENT(PNEditor,FXMainWindow,PNEditorMap,ARRAYNUMBER(PNEditorMap))

/*******************************************************************************/

// Construct a PNEditor
PNEditor::PNEditor(FXApp* a)
: FXMainWindow(a, "Pavillon Noir", NULL, NULL, DECOR_ALL, 0, 0, 800, 600)
{
  _graph = NULL;
  wpGroup = NULL;
  soundGroup = NULL;
  _state = VIEW_GENERAL;
  _wpenabled = false;
  appicon = new FXPNGIcon(getApp(), pnicon16);
  setIcon(appicon);

  // Make status bar
  statusbar = new FXStatusBar(this, LAYOUT_SIDE_BOTTOM  |  LAYOUT_FILL_X  |  
	STATUSBAR_WITH_DRAGCORNER);

  // Site where to dock
  topdock = new FXDockSite(this, LAYOUT_SIDE_TOP  |  LAYOUT_FILL_X);
  bottomdock = new FXDockSite(this, LAYOUT_SIDE_BOTTOM  |  LAYOUT_FILL_X);
  leftdock = new FXDockSite(this, LAYOUT_SIDE_LEFT  |  LAYOUT_FILL_Y);
  rightdock = new FXDockSite(this, LAYOUT_SIDE_RIGHT  |  LAYOUT_FILL_Y);

  // Menubar 1
  dragshell1 = new FXToolBarShell(this, FRAME_RAISED);
  menubar = new FXMenuBar(topdock, dragshell1, LAYOUT_DOCK_SAME  |  
	LAYOUT_SIDE_TOP  |  LAYOUT_FILL_Y  |  FRAME_RAISED);

  // Tool bar 2
  dragshell2 = new FXToolBarShell(this, FRAME_RAISED);
  toolbar1 = new FXToolBar(topdock, dragshell2, LAYOUT_DOCK_SAME  |  
	LAYOUT_SIDE_TOP  |  FRAME_RAISED);

  glvisual = new FXGLVisual(getApp(), VISUAL_DOUBLEBUFFER);

  viewer = new PNGLViewer(this, glvisual, this, ID_GLVIEWER, 
	LAYOUT_FILL_X  |  LAYOUT_FILL_Y  |  LAYOUT_TOP  |  LAYOUT_LEFT);
  viewer->setProjection(FXGLViewer::PERSPECTIVE);

  // Tool bar 4
  dragshell3 = new FXToolBarShell(this, FRAME_RAISED  |  FRAME_THICK);
  dockbar = new FXDockBar(rightdock, dragshell3, LAYOUT_FILL_Y  |  LAYOUT_SIDE_RIGHT, 
	0, 0, 0, 0, 2, 2, 2, 2, 2, 2);

  // Only dock left and right
  dockbar->allowedSides(FXDockBar::ALLOW_LEFT  |  FXDockBar::ALLOW_RIGHT);


  //
  // Tab book with switchable panels
  //
  _panels = new FXTabBook(dockbar, NULL, 0, LAYOUT_FILL_Y, 0, 0, 0, 0, 0, 0, 0, 0);

  // Angles
  new FXTabItem(_panels, "Angles\tCamera Angles\tSwitch to camera angles panel.");
  FXMatrix *angles = new FXMatrix(_panels, 3, FRAME_THICK  |  FRAME_RAISED  |  MATRIX_BY_COLUMNS
	|  LAYOUT_FILL_Y  |  LAYOUT_TOP  |  LAYOUT_LEFT, 
	0, 0, 0, 0, 10, 10, 10, 10);
  new FXLabel(angles, "X:");
  new FXTextField(angles, 6, viewer, FXGLViewer::ID_ROLL, 
	TEXTFIELD_INTEGER  |  JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  FXDial* x_dial = new FXDial(angles, viewer, FXGLViewer::ID_DIAL_X, 
	FRAME_SUNKEN  |  FRAME_THICK  |  DIAL_CYCLIC  |  
	DIAL_HORIZONTAL  |  LAYOUT_FIX_WIDTH  |  LAYOUT_FIX_HEIGHT  |  
	LAYOUT_CENTER_Y, 0, 0, 160, 14, 0, 0, 0, 0);
  x_dial->setTipText("Rotate about X");
  x_dial->setNotchOffset(900);

  new FXLabel(angles,"Y:");
  new FXTextField(angles, 6, viewer, FXGLViewer::ID_PITCH, 
	TEXTFIELD_INTEGER  |  JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  FXDial* y_dial = new FXDial(angles, viewer, FXGLViewer::ID_DIAL_Y, 
	FRAME_SUNKEN  |  FRAME_THICK  |  DIAL_CYCLIC  |  
	DIAL_HORIZONTAL  |  LAYOUT_FIX_WIDTH  |  LAYOUT_FIX_HEIGHT  |  
	LAYOUT_CENTER_Y, 0, 0, 160, 14, 0, 0, 0, 0);
  y_dial->setTipText("Rotate about Y");
  y_dial->setNotchOffset(900);

  new FXLabel(angles, "Z:");
  new FXTextField(angles, 6, viewer, FXGLViewer::ID_YAW, 
	TEXTFIELD_INTEGER  |  JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  FXDial* z_dial = new FXDial(angles, viewer, FXGLViewer::ID_DIAL_Z, 
	FRAME_SUNKEN  |  FRAME_THICK  |  DIAL_CYCLIC  |  
	DIAL_HORIZONTAL  |  LAYOUT_FIX_WIDTH  |  LAYOUT_FIX_HEIGHT 
	|  LAYOUT_CENTER_Y, 0, 0, 160, 14, 0, 0, 0, 0);
  z_dial->setTipText("Rotate about Z");
  z_dial->setNotchOffset(900);

  new FXLabel(angles, "FOV:");
  FXTextField* fov = new FXTextField(angles, 5, viewer, FXGLViewer::ID_FOV, 
	JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  new FXFrame(angles, 0);
  fov->setTipText("Field of view");

  new FXLabel(angles, "Zoom:");
  FXTextField* zz = new FXTextField(angles, 5, viewer, FXGLViewer::ID_ZOOM, 
	JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  new FXFrame(angles, 0);
  zz->setTipText("Zooming");

  new FXLabel(angles,"Scale X:");
  new FXTextField(angles, 5, viewer, FXGLViewer::ID_SCALE_X, 
	JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  new FXFrame(angles, 0);
  new FXLabel(angles, "Scale Y:");
  new FXTextField(angles, 5, viewer, FXGLViewer::ID_SCALE_Y, 
	JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  new FXFrame(angles, 0);
  new FXLabel(angles, "Scale Z:");
  new FXTextField(angles, 5, viewer, FXGLViewer::ID_SCALE_Z,
	JUSTIFY_RIGHT  |  FRAME_SUNKEN  |  FRAME_THICK);
  new FXFrame(angles, 0);

  // 3D Objects
  new FXTabItem(_panels,"3D Objects\t3D Objects\tEdit 3D Objects.");
  FXVerticalFrame *settingsObj = new FXVerticalFrame(_panels, FRAME_THICK  |  
	FRAME_RAISED  | LAYOUT_FILL_Y  
	|  LAYOUT_CENTER_X  |  LAYOUT_TOP 
	|  LAYOUT_LEFT, 0, 0, 0, 0, 
	10, 10, 10, 10);

  objPanel = new PNPropertiesPanel(settingsObj, PNPropertiesPanel::PN_PANELTYPE_3DOBJECTS, this);

  // Waypoints
  new FXTabItem(_panels,"WayPoints\tWayPoints\tManipulate waypoints.");
  FXVerticalFrame *settingsWP = new FXVerticalFrame(_panels, FRAME_THICK  |  
	FRAME_RAISED  | LAYOUT_FILL_Y  
	|  LAYOUT_CENTER_X  |  LAYOUT_TOP 
	|  LAYOUT_LEFT, 0, 0, 0, 0, 
	10, 10, 10, 10);

  wpPanel = new PNPropertiesPanel(settingsWP, PNPropertiesPanel::PN_PANELTYPE_WAYPOINTS, this);

  // Menus

  // Icons
  fileopenicon = new FXGIFIcon(getApp(), fileopen);
  filesaveicon = new FXGIFIcon(getApp(), filesave);
  filesaveasicon = new FXGIFIcon(getApp(), filesaveas, 0, IMAGE_ALPHAGUESS);

  generalicon = new FXBMPIcon(getApp(), _general);
  objectsicon = new FXBMPIcon(getApp(), _3DObjects);

  waypointsicon = new FXBMPIcon(getApp(), _waypoints);
  groundicon = new FXBMPIcon(getApp(), groundIcon);
  staticicon = new FXBMPIcon(getApp(), staticIcon);
  dynicon = new FXBMPIcon(getApp(), dynamicIcon);

/*  nolighticon=new FXGIFIcon(getApp(),nolight);
  lighticon=new FXGIFIcon(getApp(),light);
  smoothlighticon=new FXGIFIcon(getApp(),smoothlight);*/

  filemenu = new FXMenuPane(this);
  new FXMenuTitle(menubar, "&File", NULL, filemenu);
  //  new FXMenuCommand(filemenu, "&New...\tCtl-N\tCreate new document.", filenewicon);
  new FXMenuCommand(filemenu, "&Open...\tCtl-O\tOpen document file.", fileopenicon, this, ID_OPEN);
  new FXMenuCommand(filemenu, "&Save\tCtl-S\tSave document.", filesaveicon, this, ID_SAVE);
  new FXMenuCommand(filemenu, "Save &As...\t\tSave document to another file.", filesaveasicon, this, ID_SAVEAS);
  new FXMenuCommand(filemenu, "&Dump...\t\tDump widgets.", NULL, getApp(), FXApp::ID_DUMP);
  new FXMenuCommand(filemenu, "&Export...\t\tExport Space Partioning.", NULL, this, ID_EXPORT);
  new FXMenuCommand(filemenu, "&Quit\tCtl-Q\tQuit the application.", NULL, getApp(), FXApp::ID_QUIT);
  
  // File manipulation
  new FXButton(toolbar1, "\tOpen\tOpen document file.", fileopenicon, this, 
	ID_OPEN, BUTTON_TOOLBAR | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);
  new FXButton(toolbar1, "\tSave\tSave document.", filesaveicon, this, ID_SAVE, 
	BUTTON_TOOLBAR | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);
  new FXButton(toolbar1, "\tSave As\tSave document to another file.", 
	filesaveasicon, this, ID_SAVEAS, BUTTON_TOOLBAR | FRAME_RAISED | 
	LAYOUT_TOP | LAYOUT_LEFT);

  new FXSeparator(toolbar1, SEPARATOR_GROOVE);

  new FXButton(toolbar1, "\tGeneral\tGeneral View.", generalicon, this, ID_GENERAL, 
	BUTTON_NORMAL | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);
  new FXButton(toolbar1, "\tObjects\tObjects View.", objectsicon, this, ID_OBJECTS, 
	BUTTON_NORMAL | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);

  new FXSeparator(toolbar1, SEPARATOR_GROOVE);

  new FXToggleButton(toolbar1, 
	"\tSkybox\tHide Skybox",
	"\tSkybox\tShow Skybox", groundicon, groundicon, this,
	ID_SKYBOX, BUTTON_NORMAL | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);

  new FXToggleButton(toolbar1, 
	"\tGround\tHide Ground Objects",
	"\tGround\tShow Ground Objects", groundicon, groundicon, this,
	ID_GROUND, BUTTON_NORMAL | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);

  new FXToggleButton(toolbar1, 
	"\tStatic\tHide Static Objects",
	"\tStatic\tShow Static Objects", staticicon, staticicon, this,
	ID_STATIC, BUTTON_NORMAL | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);

  new FXToggleButton(toolbar1,
	"\tDynamic\tHide Dynamic Objects",
	"\tDynamic\tShow Dynamic Objects", dynicon, dynicon, this,
	ID_DYNAMIC, BUTTON_NORMAL | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);

  new FXToggleButton(toolbar1, 
	"\tWaypoints\tShow Waypoints",
	"\tWaypoints\tHide Waypoints", waypointsicon, waypointsicon, this,
	ID_WAYPOINTS, BUTTON_NORMAL | FRAME_RAISED | LAYOUT_TOP | LAYOUT_LEFT);

  new FXSeparator(toolbar1, SEPARATOR_GROOVE);

/*  new FXButton(toolbar1,"\tNo shading\tTurn light sources off.",nolighticon,this,FXGLShape::ID_SHADEOFF,BUTTON_AUTOGRAY|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);
  new FXButton(toolbar1,"\tFlat shading\tTurn on faceted (flat) shading.",lighticon,this,FXGLShape::ID_SHADEON,BUTTON_AUTOGRAY|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);
  new FXButton(toolbar1,"\tSmooth shading\tTurn on smooth shading.",smoothlighticon,this,FXGLShape::ID_SHADESMOOTH,BUTTON_AUTOGRAY|BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);
  new FXSeparator(toolbar1,SEPARATOR_GROOVE);
  new FXToggleButton(toolbar1,"\tToggle Light\tToggle light source.",NULL,nolighticon,lighticon,NULL,0,BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);*/



  helpmenu = new FXMenuPane(this);
  new FXMenuTitle(menubar, "&Help", NULL, helpmenu);
  new FXMenuCommand(helpmenu, "&About FOX...\t\tDisplay FOX about panel.", 
	NULL, this, ID_ABOUT, 0);
  new FXMenuCommand(helpmenu, "&About PNE...\t\tDisplay PNE about panel.", 
	NULL, this, ID_ABOUT_PNE, 0);

  // The status bar shows our mode
  statusbar->getStatusLine()->setTarget(this);
  statusbar->getStatusLine()->setSelector(ID_QUERY_MODE);

  /*groundGroup = new FXGLGroup();
  staticGroup = new FXGLGroup();
  dynGroup = new FXGLGroup();*/
  viewer->setScene(&_genScene);
  viewer->setFieldOfView(120.0f);

  //////////////////////////////////////////////////////////////////////////
  
  _genScene.setOptionView(PNGLGroup::VIEW_ALL);

  _genScene.setPropertiesPanel(objPanel);
  _genScene.setEditor(this);
}

// Destructor
PNEditor::~PNEditor()
{
  delete appicon;
  delete statusbar;
  delete filemenu;
//  delete waypointsListBox;
  delete menubar;
  delete toolbar1;
  delete glvisual;
  delete dockbar;
  delete topdock;
  delete bottomdock;
  delete leftdock;
  delete rightdock;
  delete dragshell1;
  delete dragshell2;
  delete dragshell3;
  delete viewer;
}

// Create and initialize
void PNEditor::create()
{
  FXMainWindow::create();
  dragshell1->create();
  dragshell2->create();
  dragshell3->create();
  show(PLACEMENT_SCREEN);
}


void
PNEditor::update()
{
  pnerror(PN_LOGLVL_DEBUG, "void PNEditor::update()");
  objPanel->updateGrid();
  wpPanel->updateGrid();
}

// About
long PNEditor::onCmdAbout(FXObject*, FXSelector, void*)
{
  FXMessageBox::information(this, MBOX_OK, "About FOX", "FOX OpenGL Example.\nCopyright (C) 1998, 2005 Jeroen van der Zijp");
  return 1;
}

// About PNE
long PNEditor::onCmdAboutPNE(FXObject*, FXSelector, void*)
{
  FXMessageBox::information(this, MBOX_OK, "About PNE", "Pavillon Noir Editor.\nhttp://www.pavillon-noir.org\nCopyright (C) 2005 Pavillon Noir Team");
  return 1;
}

// Open
long PNEditor::onCmdOpen(FXObject*, FXSelector, void*)
{
  FXDirDialog open(this, "Choose level directory to edit");
  
  if (open.execute())
  {
    _genScene.clear();

	if (wpPanel != NULL)
	  wpPanel->clear();
	if (objPanel != NULL)
	  objPanel->clear();

	_dir = open.getDirectory().text();
	_dir += PATHSEP;
	fxmessage("File = %s\n", _dir.c_str());

	boost::filesystem::path entpath(_dir + "entities.xml", boost::filesystem::no_check);

	viewer->makeCurrent();
	_genScene.unserializeFromFile(entpath);
	viewer->makeNonCurrent();

	_genScene.setOptionView(PNGLGroup::VIEW_ALL);
	fitToBounds();

	// Waypoints
	if (_graph != NULL)
	{
	  delete _graph;
	  delete wpGroup;
	}

	wpGroup = new FXGLGroup();
	_graph = new PNIAGraph();
	boost::filesystem::path wppath(_dir + "waypoints.xml", boost::filesystem::no_check);
	_graph->unserializeFromFile(wppath);
	fxmessage("%d Waypoints in %s\n", _graph->getNbWayPoints(), wppath.string().c_str());
	buildWPGroup();
	if (_wpenabled)
	  _genScene.append(wpGroup);
  }

  return 1;
}

void
PNEditor::buildWPGroup()
{
  WPLIST& wpl = _graph->getWayPoints();
  char		  buf[512];

  if (wpGroup != NULL)
  {
	FXObjectList&  l = wpGroup->getList();
	for (int i = 0; i < l.no(); i++)
	  delete l[i];
	wpGroup->clear();
  }
  else
	wpGroup = new FXGLGroup;
  for (WPLIST::iterator i =  wpl.begin(); i != wpl.end(); i++)
  {
    pnint		  wpid = (*i)->getId();

	sprintf(buf, "WayPoint #%d", wpid);
    wpGroup->append(new PNGLShape(*i, wpPanel, this, PN_STATIC, "PNWayPoint", wpid, buf));
  }
}

long PNEditor::onCmdSave(FXObject* sender, FXSelector, void*)
{
  if (_graph == NULL)
  {
	FXDirDialog open(this, "Choose level directory to save your work");
	if (open.execute())
	{
	  wpGroup = new FXGLGroup;
	  _graph = new PNIAGraph;
	  _dir = open.getDirectory().text();
	  _dir += PATHSEP;
	}
	else
	{
	  return 1;
	}
  }
  
  _genScene.serializeInFile(fs::path((_dir + "entities.xml").c_str(), fs::native));

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  // Waypoints

  boost::filesystem::path wppath(_dir + "waypoints.xml", boost::filesystem::no_check);

  pnerror(PN_LOGLVL_DEBUG, "Saving waypoints in %s", wppath.string().c_str());
  _graph->serializeInFile(wppath);

  //////////////////////////////////////////////////////////////////////////
  
  _genScene.clear();
  _genScene.setOptionView(PNGLGroup::VIEW_ALL);
  _wpenabled = false;

  return 1;
}

long PNEditor::onCmdSaveAs(FXObject* sender, FXSelector sel, void* param)
{
  FXDirDialog open(this, "Choose level directory to save your work");

  if (open.execute())
  {
	if (_graph == NULL)
	{
	  wpGroup = new FXGLGroup;
	  _graph = new PNIAGraph;
	}

	_dir = open.getDirectory().text();
	_dir += PATHSEP;
	onCmdSave(sender, sel, param);
  }

  return 1;
}

long PNEditor::onCmdExport(FXObject* sender, FXSelector sel, void* param)
{
  FXDirDialog dd(this, "Choose level directory to save your work");
  if (dd.execute())
  {
	// ramene ton code ici ! vla comment obtenir le char * avec le nom du fichier
	dd.getDirectory().text();
  }
  return 1;
}
// Views
long PNEditor::onCmdGenView(FXObject* sender, FXSelector, void*)
{
  FXRangef	b;
  PNGLShape	*s;

  if (_state == VIEW_OBJECTS)
  {
	s = (PNGLShape*)_objScene.getList()[0];
	s->setPosFromObj();
	s->setDragable();
	viewer->setOrientation(camOrient);
  }

  viewer->setScene(&_genScene);
  _genScene.bounds(b);
  viewer->fitToBounds(b);
  _state = VIEW_GENERAL;
  return 1;
}

long PNEditor::onCmdObjView(FXObject*, FXSelector, void*)
{
  FXRangef	b;
  PNGLShape	*s;

  if ((s = (PNGLShape*)viewer->getSelection()) != NULL)
  {
	FXQuatf nullCam(0.0f, 0.0f, 0.0f, 1.0f);
	const FXQuatf& tmp = viewer->getOrientation();

	s->setUndragable();
	s->setPosNull();

	_objScene.clear();
	_objScene.append(s);
	camOrient = tmp;
	viewer->setOrientation(nullCam);
	viewer->setScene(&_objScene);

	s->bounds(b);
	viewer->fitToBounds(b);

	_state = VIEW_OBJECTS;
  }
  return 1;
}

long
PNEditor::onCmdSkyboxView(FXObject* obj, FXSelector sel, void* ptr)
{
  _genScene.enableOptionView(PNGLGroup::VIEW_SKYBOX, !_genScene.contains(PNGLGroup::VIEW_SKYBOX));

  fitToBounds();

  return 1;
}

long PNEditor::onCmdGroundView(FXObject* sender, FXSelector, void*)
{
  _genScene.enableOptionView(PNGLGroup::VIEW_GROUND, !_genScene.contains(PNGLGroup::VIEW_GROUND));

  fitToBounds();

  return 1;
}

long PNEditor::onCmdStaticView(FXObject* sender, FXSelector, void*)
{
  _genScene.enableOptionView(PNGLGroup::VIEW_STATIC, !_genScene.contains(PNGLGroup::VIEW_STATIC));

  fitToBounds();

  return 1;
}

long PNEditor::onCmdDynView(FXObject* sender, FXSelector, void*)
{
  _genScene.enableOptionView(PNGLGroup::VIEW_DYNAMIC, !_genScene.contains(PNGLGroup::VIEW_DYNAMIC));

  fitToBounds();

  return 1;
}

long PNEditor::onCmdWPView(FXObject* sender, FXSelector, void*)
{
  if (wpGroup != NULL)
  {
	if (!_wpenabled)
	{
	  _genScene.append(wpGroup);
	  _wpenabled = true;
	}
	else
	{
	  _genScene.remove(wpGroup);
	  _wpenabled = false;
	}
	if (_state == VIEW_GENERAL)
	{
	  FXRangef	b;
	  viewer->setScene(&_genScene);
	  _genScene.bounds(b);
	  viewer->fitToBounds(b);
	}
  }
  else
  {
	FXToggleButton* b = (FXToggleButton*)sender;
	b->setState(FALSE);
  }
  return 1;
}

long PNEditor::onCmdGridObjSel(FXObject* obj, FXSelector sel, void* ptr)
{
  wpPanel->update();
  objPanel->update();
  return 1;
}

long PNEditor::onCmdCopyObj(FXObject* obj, FXSelector sel, void* ptr)
{
  PNGLShape* s = (PNGLShape*)viewer->getSelection();
  PN3DObject* orig = s->getObj();
  PN3DObject* cp = new PN3DObject();

  viewer->makeCurrent();
  cp->unserializeFromFile(*orig->getFile()); //FIXME
  viewer->makeNonCurrent();

  cp->setCoord(orig->getCoord());
  cp->setOrient(orig->getOrient());

  add3DObject(cp, objPanel, objPanel->getIdMax(), s->getEnvType(), s->getClassStr(), s->getLabel());
  objPanel->incrementIdMax();
  return 1;
}

// Statusbar wanted to know about mode
// We fake it here for the purpose of demonstration...
long PNEditor::onUpdMode(FXObject* sender, FXSelector, void*)
{
  FXStatusLine *statusline = (FXStatusLine*)sender;
  statusline->setText("Ready.");
  return 1;
}

/*
*  When the user right-clicks in the GLViewer background,  the viewer first sends
*  a SEL_COMMAND message with identifier FXWindow::ID_QUERY_MENU to the selected
*  GLObject (if any). If that message isn't handled,  it tries to send it to the
*  GLViewer's target (which in our case is the main window).
*/

long PNEditor::onQueryMenu(FXObject* sender, FXSelector, void* ptr)
{
  FXEvent *event = (FXEvent*)ptr;
  FXMenuPane pane(this);
//  PNGLShape*  s = (PNGLShape*)viewer->getSelection(); // UNUSED

  // waypoints control
//  new FXMenuCommand(&pane,"&Add waypoint", NULL, sender, PNEditor::ID_WP_ADD);
//  new FXMenuSeparator(&pane);
  new FXMenuRadio(&pane, "Parallel\t\tSwitch to parallel projection.", 
  								sender, FXGLViewer::ID_PARALLEL);
  new FXMenuRadio(&pane, "Perspective\t\tSwitch to perspective projection.", 
  								sender, FXGLViewer::ID_PERSPECTIVE);
  new FXMenuSeparator(&pane);
  new FXMenuRadio(&pane, "&Front\t\tFront view.", sender, FXGLViewer::ID_FRONT);
  new FXMenuRadio(&pane, "&Back\t\tBack view.", sender, FXGLViewer::ID_BACK);
  new FXMenuRadio(&pane, "&Left\t\tLeft view.", sender, FXGLViewer::ID_LEFT);
  new FXMenuRadio(&pane, "&Right\t\tRight view.", sender, FXGLViewer::ID_RIGHT);
  new FXMenuRadio(&pane, "&Top\t\tTop view.", sender, FXGLViewer::ID_TOP);
  new FXMenuRadio(&pane, "&Bottom\t\tBottom view.", sender, FXGLViewer::ID_BOTTOM);
  new FXMenuSeparator(&pane);
  new FXMenuCommand(&pane, "F&it\t\tFit to view.", NULL, sender, 
  									FXGLViewer::ID_FITVIEW);
  new FXMenuCommand(&pane, "R&eset\t\tReset all viewing parameters", 
  									NULL, sender, FXGLViewer::ID_RESETVIEW);
  if (viewer->getSelection() != NULL)
  {
	new FXMenuCommand(&pane, "&Copy object\t\tCopies current object", 
	  NULL, this, ID_COPYOBJ);
  }
  new FXMenuSeparator(&pane);

  pane.create();
  pane.popup(NULL, event->root_x, event->root_y);
  getApp()->runModalWhileShown(&pane);
  return 1;
}

void
PNEditor::setInObjView(FXGLObject* obj)
{
  if (_state == VIEW_OBJECTS)
  {
	FXRangef	b;
	PNGLShape	*s;
	FXQuatf nullCam(0.0f, 0.0f, 0.0f, 1.0f);

	s = (PNGLShape*)_objScene.getList()[0];
    s->setPosFromObj();
    s->setDragable();

	s = (PNGLShape*)obj;
    s->setUndragable();
    s->setPosNull();
    _objScene.clear();
    _objScene.append(s);
	viewer->setOrientation(nullCam);
	viewer->setScene(&_objScene);

	fitToBounds();
  }

  viewer->setSelection(obj);
}

void
PNEditor::redraw()
{
  if (_state == VIEW_OBJECTS)
	viewer->setScene(&_objScene);
  else
	viewer->setScene(&_genScene);
}

void
PNEditor::deleteWP(PNWayPoint* wp)
{
  _graph->deleteWayPoint(wp);
  buildWPGroup();
}

void
PNEditor::removeShape(FXGLShape* s)
{
  _genScene.remove(s);

  if (((PNGLShape*)s)->getObj()->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	wpGroup->remove(s);

  viewer->setSelection(NULL);

  fitToBounds();
}

void
PNEditor::addWayPoint(pnfloat x, pnfloat y, pnfloat z)
{
  if (_graph == NULL)
	_graph = new PNIAGraph;
  _graph->addWayPoint(x, y, z);
  if (_wpenabled == true)
  {
	buildWPGroup();
	_genScene.remove(wpGroup);
	_wpenabled = false;
	onCmdWPView(NULL, 0, NULL);
  }
  else
	buildWPGroup();
}

void	  PNEditor::add3DObject(PN3DObject* o, PNPropertiesPanel* p, pnint id, PNEnvType t, std::string classStr, std::string label)
{
  PNGLShape*  s = new PNGLShape(o, p, this, t, classStr, id, label);
  
  _genScene.append(s);

  objPanel->setObject((PNConfigurableObject*)s);

  fitToBounds();
}

void PNEditor::makeViewerCurrent()
{
  viewer->makeCurrent();
}

void PNEditor::makeViewerNonCurrent()
{
  viewer->makeNonCurrent();
}

void	PNEditor::fitToBounds()
{
  FXRangef	b;

  switch (_state)
  {
  case VIEW_GENERAL:
	viewer->setScene(&_genScene);
	_genScene.bounds(b);
  	break;
  case VIEW_OBJECTS:
	viewer->setScene(&_objScene);
	_objScene.bounds(b);
	break;
  default:
    break;
  }

  viewer->fitToBounds(b);
}

//////////////////////////////////////////////////////////////////////////
}
};

// Here we begin
int main(int argc, char *argv[])
{
  PN::PNPluginManager*	plugMan = PN::PNPluginManager::getInstance();

  chdir("../");

  char buf[512] = "";
  fxmessage("now in : %s\n", getcwd(buf, 511));

  plugMan->addDefaultPlugin("pnglrenderer");
  plugMan->addDefaultPlugin("pnimporter");
  plugMan->addDefaultPlugin("pnexporter");

  for (PN::PNPluginManager::iterator i = plugMan->begin(); i != plugMan->end(); i++)
  {
	PN::PNPlugDesc *desc = (*i)->getPlugDesc();
	for (PN::pnuint i = 0; i < desc->getNbInterface(); i++)
	{
	  desc->getInterface(i)->init();
	}
  }
  // Make application
  FXApp application("Editeur Pavillon Noir", "PN");

  // Open the display
  application.init(argc, argv);

  // Make window
  new PN::EDITOR::PNEditor(&application);

  // Create the application's windows
  application.create();

  // Run the application
  return application.run();
}
