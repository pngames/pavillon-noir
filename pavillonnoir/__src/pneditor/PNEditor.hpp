/*
 * PNEditor.hpp
 * 
 * Description :
 * PNEditor declaration
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


#ifndef _PNEDITOR_HPP_
# define _PNEDITOR_HPP_

#include <string>
#include <boost/filesystem/path.hpp>

#include "pneditoricons.hpp"
#include "pndefs.h"

#include "PNGLShape.hpp"
#include "PNGLGroup.hpp"
#include "PNEDMapPanel.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

class PNIAGraph;
class PNWayPoint;
class PN3DSkeletonObject;
  
namespace EDITOR {
//////////////////////////////////////////////////////////////////////////

class PNEDSkyboxPanel;
class PNPropertiesPanel;
class PNGLViewer;

// Main Window
class PNEditor : public FXMainWindow
{
  std::string obj1str1;
  std::string obj1str2;
  std::string obj2str1;
  std::string obj2str2;
public:
  // We define additional ID's, starting from the last one used by the base class+1.
  // This way, we know the ID's are all unique for this particular target.
  enum
  {
	ID_ABOUT = PNEditor::ID_LAST,
	ID_ABOUT_PNE,
	ID_OPEN,
	ID_SAVE,
	ID_SAVEAS,
	ID_EXPORT,
	ID_QUERY_MODE,
	ID_GLVIEWER,

	// views
	ID_GENERAL,
	ID_OBJECTS,

	ID_SKYBOX,
	ID_WAYPOINTS,
	ID_GROUND,
	ID_STATIC,
	ID_DYNAMIC,

	ID_MULTISELECT,
	ID_UNSELECT,

	// grid
	ID_GRID_OBJ_SEL,

	// waypoints
	ID_WP_START,
	ID_WP_END,
	ID_COPYOBJ,
	ID_LAST
  };

  // enum defining the currently used view
  typedef enum
  {
	VIEW_GENERAL,
	VIEW_OBJECTS,
	VIEW_SOUNDS
  } pneditorState_t;

  FXDECLARE(PNEditor)
private:
  FXMenuBar*        menubar;				// Menu bar
  FXToolBar*        toolbar1;				// Tool bar
  FXDockBar*        dockbar;				// Dock bar
  FXToolBarShell*   dragshell1;				// Shell for floating menubar
  FXToolBarShell*   dragshell2;				// Shell for floating toolbar
  FXToolBarShell*   dragshell3;				// Shell for floating toolbar
  FXDockSite*       topdock;
  FXDockSite*       bottomdock;
  FXDockSite*       leftdock;
  FXDockSite*       rightdock;
  FXMDIClient*      mdiclient;				// MDI Client area
  FXStatusBar*      statusbar;				// Status bar

  PNGLGroup			_genScene;				// General Scene with all the objects
  FXGLGroup			_objScene;				// Show a particular object
  FXGLGroup*		soundGroup;				// Show sounds
  FXGLGroup*        wpGroup;				// WayPoints objects
  FXMenuPane*       mdimenu;				// MDI Window Menu
  FXGLVisual*       glvisual;				// Visual for OpenGL
  FXMenuPane*       filemenu;
  FXMenuPane*       helpmenu;
  PNGLViewer*		viewer;

/*  FXIcon            *nolighticon;
  FXIcon            *lighticon;
  FXIcon            *smoothlighticon;*/
  FXListBox*        waypointsListBox;
  FXQuatf			camOrient;

  PNPropertiesPanel*	objPanel;
  PNPropertiesPanel*	wpPanel;
  PNEDSkyboxPanel*		_skPanel;
  PNEDMapPanel*			_mapPanel;

  PNWayPoint*		_startWP;
  FXTabBook*		_panels;

  pneditorState_t	_state;
  std::string		_dir;
  bool				_wpenabled;

  // PN Objects
  PNIAGraph*		_graph;

public:
  FXIcon*           fileopenicon;
  FXIcon*           filesaveasicon;
  FXIcon*           filesaveicon;
  FXIcon*           exiticon;
  FXIcon*           infoicon;
  FXIcon*           helpicon;

  FXIcon*           appicon;
  FXIcon*           winappicon;
  FXIcon*           cameraicon;

  FXIcon*           generalicon;
  FXIcon*           objectsicon;
  FXIcon*           skyboxicon;
  FXIcon*           groundicon;
  FXIcon*           staticicon;
  FXIcon*           dynicon;
  FXIcon*           waypointsicon;
  FXIcon*           unselecticon;
  FXIcon*           reseticon;

  FXIcon*           addicon;
  FXIcon*           removeicon;
  FXIcon*           editicon; // unused

  FXIcon*           okicon;
  FXIcon*           cancelicon;
  FXIcon*           browseicon;

protected:
  PNEditor() {}
public:
  PNEDSkyboxPanel*	getSKPanel() { return _skPanel; }

  // Message handlers
  long onCmdOpen(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdSave(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdSaveAs(FXObject* obj, FXSelector sel, void* ptr);

  long onCmdAbout(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdAboutPNE(FXObject* obj, FXSelector sel, void* ptr);

  long onUpdMode(FXObject* obj, FXSelector sel, void* ptr);
  long onQueryMenu(FXObject* obj, FXSelector sel, void* ptr);

  long onCmdExport(FXObject* obj, FXSelector sel, void* ptr);

  // view messages handlers
  long onCmdGenView(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdObjView(FXObject* obj, FXSelector sel, void* ptr);

  long onCmdSkyboxView(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdGroundView(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdStaticView(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdDynView(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdWPView(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdUnselect(FXObject* obj, FXSelector sel, void* ptr);
  long onCmdMultiSelect(FXObject* obj, FXSelector sel, void* ptr);

  // grid messages handlers
  long onCmdGridObjSel(FXObject* obj, FXSelector sel, void* ptr);

  // Copies an object in the same view
  long onCmdCopyObj(FXObject* obj, FXSelector sel, void* ptr);

  PNGLViewer* getViewer() {return viewer;}

  // panels
  PNPropertiesPanel*	getObjPanel() { return objPanel; }
  PNPropertiesPanel*	getWpPanel() { return wpPanel; }
  void					setCurrentTab(int idx) { if(_panels->getCurrent()!=idx)_panels->setCurrent(idx); }

  // Loading
  /*int	  _loadEntities(const boost::filesystem::path& file);
  int	  _parse(void* node);
  int	  _parseListEntities(void* node);
  int	  _parseEntity(void* node);
  int	  _parseActions(void* node, PNGLShape* shape);
  int	  _parseID(std::string id);*/

  // Builds WPGroup whith _graph contents
  void	  buildWPGroup();

  // Sets given object in the objView if it is the current view
  void	  setInObjView(FXGLObject* obj);

  // Redraws current scene
  void	  redraw();

  // Deletes given WayPoint from the AI Graph
  void	  deleteWP(PNWayPoint* wp);

  // Removes given PNGLShape fron the General Scene
  void	  removeShape(FXGLShape* s);

  // Adds a Waypoint at the given position
  void	  addWayPoint(pnfloat x, pnfloat y, pnfloat z);

  // Adds a 3D Object
  void	  add3DObject(PN3DObject* o, PNPropertiesPanel* p, pnint id, PNEnvType t, std::string classStr, std::string label);

  // Sets OpenGL context
  void	  makeViewerCurrent();

  // Unsets OpenGL context
  void	  makeViewerNonCurrent();

  void	  fitToBounds();

  // access to ground elements for space partitionning
  //FXGLGroup*        getGroundGroup() { return groundGroup; }


  // PNEditor constructor
  PNEditor(FXApp* a);

  PNIAGraph*		getGraph() {return _graph;}

  // Initialize
  virtual void create();

  // Update
  virtual void update();

  // PNEditor destructor
  virtual ~PNEditor();
};

};

};

/*******************************************************************************/

#endif //_PNEDITOR_HPP_
