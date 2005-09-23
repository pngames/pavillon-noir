/*
 * PNPropertiesPanel.cpp
 * 
 * Description :
 * PNPropertiesPanel definition
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


#include <fxkeys.h>
#ifdef WIN32
# include <direct.h>
#else
# include <unistd.h>
#endif

#include <iostream>
#include <libxml/xmlreader.h>

/////////////////////////////////////

#include "pnresources.h"
#include "pnxml.h"

/////////////////////////////////////

#include "pneditorcommon.hpp"
#include "PNGLShape.hpp"
#include "PNEditor.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PNWayPoint.hpp"
#include "PNCharacter.hpp"
#include "PNPropertiesPanel.hpp"

/////////////////////////////////////

namespace PN
{

  // Map
  FXDEFMAP(PNPropertiesPanel) PNPropertiesPanelMap[]={
    FXMAPFUNC(SEL_COMMAND,PNPropertiesPanel::ID_LISTBOX_SEL,PNPropertiesPanel::onCmdListBox),
    FXMAPFUNC(SEL_COMMAND,PNPropertiesPanel::ID_ADD,PNPropertiesPanel::onCmdAdd),
	FXMAPFUNC(SEL_COMMAND,PNPropertiesPanel::ID_DELETE,PNPropertiesPanel::onCmdDelete),
	FXMAPFUNC(SEL_COMMAND,PNPropertiesPanel::ID_SAVE,PNPropertiesPanel::onCmdSave),
	FXMAPFUNC(SEL_COMMAND,PNPropertiesPanel::ID_ADDWP,PNPropertiesPanel::onAccept),
	FXMAPFUNC(SEL_COMMAND,PNPropertiesPanel::ID_CANCEL,PNPropertiesPanel::onCancel),
	FXMAPFUNC(SEL_COMMAND,PNPropertiesPanel::ID_ADDOBJECT,PNPropertiesPanel::onAddObject)
  };


  //////////////////////////////////////////////////////////////////////////
  

  FXIMPLEMENT(PNPropertiesPanel,FXComposite,PNPropertiesPanelMap,ARRAYNUMBER(PNPropertiesPanelMap))

  /*!	\brief Default constructor for PNPropertiesPanel.
   *	Initialize a new PNPropertiesPanel. A PNPropertiesPanel is made of a listbox containing 
   *	the objects, two buttons to add/delete these objects and a grid providing access to the 
   *	properties of the object selected in the listbox.
   *	\param	  p		Fox FXComposite parent object.
   *	\param	  t		Type (paneltype_t) of the informations to display.
   *	\param	  ed	Instance of PNEditor.
   */
	PNPropertiesPanel::PNPropertiesPanel(FXComposite* p, paneltype_t t, EDITOR::PNEditor* ed)
  {
	FXVerticalFrame*	panel = new FXVerticalFrame(p, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	FXHorizontalFrame*	command = new FXHorizontalFrame(panel, LAYOUT_FILL_X);
	FXString			text;

	if (t == PN_PANELTYPE_3DOBJECTS)
	  text = "3D Objects";
	else if (t == PN_PANELTYPE_WAYPOINTS)
	  text = "WayPoints";
	_ed = ed;
	_type = t;
	_idMax = 0;
	_objectsListBox = new FXListBox(command, this, ID_LISTBOX_SEL,LAYOUT_FILL_X | FRAME_SUNKEN | FRAME_THICK);
	_buttonAdd = new FXButton(command, "&Add", NULL, this, ID_ADD, FRAME_SUNKEN | FRAME_THICK);
	_buttonDelete = new FXButton(command, "Delete", NULL, this, ID_DELETE, FRAME_SUNKEN | FRAME_THICK);
	_buttonSave = new FXButton(command, "Save", NULL, this, ID_SAVE, FRAME_SUNKEN | FRAME_THICK);
    _groupBox = new FXGroupBox(panel, text, LAYOUT_FILL_X | LAYOUT_FILL_Y | FRAME_GROOVE);
    _grid = new PNPropertiesGrid(_groupBox, (PNEditorObject*)this);
  }

  /*! \brief Default destructor for PNPropertiesPanel.
   */
  PNPropertiesPanel::~PNPropertiesPanel()
  {
  }

  
  // fox ///////////////////////////////////////////////////////////////////

  /*! */
  void  PNPropertiesPanel::create()
  {
    FXComposite::create();
    _groupBox->create();
    _grid->create();
	return;
  }


  // object manipulation ////////////////////////////////////////////////////////////////////////

  /*! \brief Adds an object at the end of the list.
   *  The given object is pushed at the end of the objects list and append to the listbox. 
   *  It is also automatically selected and its properties are displayed in the grid.
   *  \param	object	  The PNConfigurableObject to add.
   */
  void  PNPropertiesPanel::addObject(PNConfigurableObject* object)
  {
    _objectsList.push_back(object);
    _objectsListBox->appendItem(object->getLabel().c_str(), NULL, object);
	_objectsListBox->setNumVisible(_objectsListBox->getNumItems() < 10 ? _objectsListBox->getNumItems() : 10);
    updateGrid((PNConfigurableObject*)_objectsListBox->getItemData(_objectsListBox->getCurrentItem()));
	EDITOR::PNGLShape* s = (EDITOR::PNGLShape*)object;
	if (s->getId() > _idMax)
	  _idMax = s->getId();
	return;
  }

  /*! Sets the current selection to object and displays its properties.
   *  If the given object is not present in the current listbox the default action is to 
   *  update the grid's content.
   *  \param	object	  The PNConfigurableObject to select in the listbox.
   */
  void  PNPropertiesPanel::setObject(PNConfigurableObject* object)
  { 
	int idx = _objectsListBox->findItemByData(object);
	if (idx != _objectsListBox->getCurrentItem())
	{
	  _objectsListBox->setCurrentItem(idx);
	  updateGrid(object);
	}
	else
	{
	  updateGrid();
	}
	return;
  }

  /*! Returns the current object.
   *  \return	Data (PNConfigurableObject) associated to the current selection in listbox.
   */
  PNConfigurableObject*	PNPropertiesPanel::getObject()
  { 
	return (PNConfigurableObject*)_objectsListBox->getItemData(_objectsListBox->getCurrentItem());
  }

  /*! Resets the panel.
  */
  void			PNPropertiesPanel::clear()
  {
	_objectsList.clear();
	if (_objectsListBox != NULL)
	  _objectsListBox->clearItems();
  }

  // update ////////////////////////////////////////////////////////////////
  
  /*! Updates the panel.
   *  This is a FULL update, i.e. this method updates:
   *	- the listbox, text labels are updated if necessary.
   *	- the grid, the current grid is deleted and a new one based on the listbox selection 
   *	is created.
   *	- the shape of the select object in the view.
   */
  void  PNPropertiesPanel::update()
  {	
	pnerror(PN_LOGLVL_DEBUG, "void  PNPropertiesPanel::update()");
	if (_objectsListBox->getNumItems() > 0)
	{
      updateListBox();
	  if (_grid != NULL)
	  {
		delete _grid;
		_grid = new PNPropertiesGrid(_groupBox, (PNEditorObject*)this);
	  }

	  PNConfigurableObject* co = (PNConfigurableObject*)_objectsListBox->getItemData(_objectsListBox->getCurrentItem());
	  updateGrid(co);
	  updateView(co);
	}
	
	return;
  }

  /*! Updates text labels in listbox if necessary.
   *  For each item in _objectListBox, update the listbox entry text if its label has been changed.
   */
  void	PNPropertiesPanel::updateListBox()
  {
	for (int i = 0; i < _objectsListBox->getNumItems(); i++)
	{
	  PNConfigurableObject* co = (PNConfigurableObject*)_objectsListBox->getItemData(i);
	  if (co->getLabel().c_str() != _objectsListBox->getItemText(i).text())
		_objectsListBox->setItemText(i, co->getLabel().c_str());
	}
	return;
  }

  /*! Updates the grid in the panel.
   */
  void  PNPropertiesPanel::updateGrid()
  {
	  _grid->update();
	  return;
  }

  /*! Updates the grid.
   *  \param	co	  Object to select in grid.
   */
  void  PNPropertiesPanel::updateGrid(PNConfigurableObject* co)
  {  
	  _groupBox->setText(co->getLabel().c_str());
	  _grid->setObject(co);
	  return;
  }

  /*! Updates the current object in the view.
   */
  void  PNPropertiesPanel::updateView()
  {
	if (_objectsListBox->getNumItems()>0)
	{
	  PNConfigurableObject* co = (PNConfigurableObject*)_objectsListBox->getItemData(_objectsListBox->getCurrentItem());
	  updateView(co);
	}
    return;
  }

  /*! Updates the given object in the view.
   *  \param	co	  Object to select and update in view.
   */
  void  PNPropertiesPanel::updateView(PNConfigurableObject* co)
  {
	// BUG : si on supprime tous les elements de la scene l'update 
	// plante = plus de shape pour setter la vue
	EDITOR::PNGLShape*	shape = (EDITOR::PNGLShape*)co;
	shape->setInObjView();
	return;
  }


  // events ////////////////////////////////////////////////////////////////

  
  /*! Updates widget on listbox selection change.
   */
  long          PNPropertiesPanel::onCmdListBox(FXObject* obj, FXSelector sel, void* ptr)
  {
	update();
	return 1;
  }
  
  /*! Deletes selected object.
   */
  long          PNPropertiesPanel::onCmdDelete(FXObject* obj, FXSelector sel, void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNPropertiesPanel::onCmdDelete(FXObject* obj, FXSelector sel, void* ptr)");
	if (_objectsListBox->getNumItems() > 0)
	{
	  FXint					index = _objectsListBox->getCurrentItem();
	  PNConfigurableObject* co = (PNConfigurableObject*)_objectsListBox->getItemData(index);
	  EDITOR::PNGLShape*	s = (EDITOR::PNGLShape*)co;

	  if (s->getObj()->getObjType() == PN3DObject::OBJTYPE_WAYPOINT)
	  {
		_objectsList.clear();
		_objectsListBox->clearItems();
	  }
	  else
	  {
		_objectsList.remove(co);
		_objectsListBox->removeItem(index);
	  }
	  s->selfRemove();
	  delete s;
	  _objectsListBox->setNumVisible(_objectsListBox->getNumItems() < 10 ? _objectsListBox->getNumItems() : 10);
	  update();
	}
	return 1;
  }

  /*! Saves current element (pno).
   */
  long          PNPropertiesPanel::onCmdSave(FXObject* obj, FXSelector sel, void* ptr)
  {
	pnerror(PN_LOGLVL_DEBUG, "PNPropertiesPanel::onCmdValidate(FXObject* obj, FXSelector sel, void* ptr)");
	if (_objectsListBox->getNumItems() != 0)
	{
	  PNConfigurableObject*	co = (PNConfigurableObject*)_objectsListBox->getItemData(_objectsListBox->getCurrentItem());
	  PN3DObject*			obj = ((EDITOR::PNGLShape*)co)->getObj();
	  FXFileDialog			open(_grid, "Choose file to save the PN Object", SELECTFILE_MULTIPLE);
	  open.setPatternList("Pavillon-Noir Objects (*.pno)");

	  if (open.execute())
	  {
		char buf[512] = "";
		getcwd(buf, 512);

		FXString strbuf(buf);
		strbuf = strbuf.substitute('\\', '/');

		FXString str = open.getFilename();

		pnerror(PN_LOGLVL_DEBUG, "strbuf=%s, str=%s", strbuf.text(), str.substitute('\\','/').text());
		if ( str.substitute('\\','/').find(strbuf.text(), 0) == -1)
		{
		  FXMessageBox dbox(this, "File Error", "403");
		  dbox.execute();
		}
		else
		{
		  obj->setFile(str.replace(0, strlen(buf) + 1, "").substitute('\\', '/').text());
		  obj->serialize();
		}
	  }
	}
	return 1;
  }

  /*! Opens a dialog box to add a new object.
   *  FIXME : describe _dbox content
   */
  long          PNPropertiesPanel::onCmdAdd(FXObject* obj, FXSelector sel, void* ptr)
  {
	// TODO : use radio buttons instead of listboxes ?

	pnerror(PN_LOGLVL_DEBUG, "PNPropertiesPanel::onCmdAdd(FXObject* obj, FXSelector sel, void* ptr)");
	_dbox = new FXDialogBox(_grid, "Add Object",DECOR_TITLE|DECOR_BORDER);
	
	FXVerticalFrame* vFrame = new FXVerticalFrame(_dbox,LAYOUT_FILL_X | LAYOUT_FILL_Y);

	// On the first line the coords
	FXGroupBox* gBoxCoords = new FXGroupBox(vFrame, "Coords", LAYOUT_FILL_X | LAYOUT_FILL_Y | FRAME_GROOVE);
	FXMatrix* matrixCoords = new FXMatrix(gBoxCoords, 6, MATRIX_BY_COLUMNS|LAYOUT_FILL_X|LAYOUT_CENTER_Y);

/*	FXLabel*  labelX = */new FXLabel(matrixCoords, "X:");
	_fieldX = new FXTextField(matrixCoords, 7, NULL, 0, LAYOUT_FILL_X | LAYOUT_RIGHT | TEXTFIELD_REAL | FRAME_SUNKEN | FRAME_THICK);
	_fieldX->setText("0.0");

/*	FXLabel*  labelY = */new FXLabel(matrixCoords, "Y:");
	_fieldY = new FXTextField(matrixCoords, 7, NULL, 0, LAYOUT_FILL_X | LAYOUT_RIGHT | TEXTFIELD_REAL | FRAME_SUNKEN | FRAME_THICK);
	_fieldY->setText("0.0");

/*	FXLabel*  labelZ = */new FXLabel(matrixCoords, "Z:");
	_fieldZ = new FXTextField(matrixCoords, 7, NULL, 0, LAYOUT_FILL_X | LAYOUT_RIGHT | TEXTFIELD_REAL | FRAME_SUNKEN | FRAME_THICK);
	_fieldZ->setText("0.0");

	// Then if the object is a 3DObject (not a waypoint) other properties
	
	if (_type == PN_PANELTYPE_3DOBJECTS)
	{
	  new FXLabel(vFrame, "voir commentaires dans le code :)", NULL, LAYOUT_CENTER_X);

	  new FXHorizontalSeparator(vFrame, LAYOUT_FILL_X);
	  FXGroupBox* gBoxProperties = new FXGroupBox(vFrame, "Properties", LAYOUT_FILL_X | LAYOUT_FILL_Y | FRAME_GROOVE);
	  FXMatrix* matrixProperties = new FXMatrix(gBoxProperties, 4, MATRIX_BY_COLUMNS|LAYOUT_FILL_X);

	  new FXLabel(matrixProperties, "Env Type:");
	  _envTypesListBox = new FXListBox(matrixProperties, this, 0, /*LAYOUT_RTL |*/ FRAME_SUNKEN | FRAME_THICK); // commentaires = pb sous LINUX
	  _envTypesListBox->appendItem((char *)PNXML_DYNAMIC_VAL, NULL, NULL);
	  _envTypesListBox->appendItem((char *)PNXML_STATIC_VAL, NULL, NULL);
	  _envTypesListBox->appendItem((char *)PNXML_GROUND_VAL, NULL, NULL);
	  _envTypesListBox->setNumVisible(_envTypesListBox->getNumItems());
  
	  new FXLabel(matrixProperties, "Obj Type:");
	  _objTypesListBox = new FXListBox(matrixProperties, this, 0, /*LAYOUT_RTL |*/ FRAME_SUNKEN | FRAME_THICK); // commentaires = pb sous LINUX
	  _objTypesListBox->appendItem((char *)PNXML_OBJECT_VAL, NULL, NULL);
	  _objTypesListBox->appendItem((char *)PNXML_DYNAMIC_VAL, NULL, NULL);
	  _objTypesListBox->appendItem((char *)PNXML_CHARACTER_VAL, NULL, NULL);
	  _objTypesListBox->setNumVisible(_objTypesListBox->getNumItems());

	  FXMatrix* matrix2 = new FXMatrix(gBoxProperties, 2, MATRIX_BY_COLUMNS|LAYOUT_FILL_X);

	  new FXLabel(matrix2, "Class:");
	  _classLabel = new FXTextField(matrix2, 20, NULL, 0, LAYOUT_FILL_X | LAYOUT_CENTER_X | LAYOUT_RIGHT | FRAME_SUNKEN | FRAME_THICK);
	  _classLabel->setText("PN3DObject");

	  new FXLabel(matrix2, "Label:");
	  _objLabel = new FXTextField(matrix2, 20, NULL, 0, LAYOUT_FILL_X | LAYOUT_CENTER_X | LAYOUT_RIGHT |FRAME_SUNKEN | FRAME_THICK);
	  _objLabel->setText("New Object");
	  
	  new FXHorizontalSeparator(vFrame, LAYOUT_FILL_X);

	  FXHorizontalFrame* hFramePath = new FXHorizontalFrame(vFrame,LAYOUT_FILL_X | LAYOUT_FILL_Y);
	  _path = new FXTextField(hFramePath, 30, NULL, 0, LAYOUT_FILL_X | LAYOUT_LEFT | TEXTFIELD_READONLY | FRAME_SUNKEN | FRAME_THICK);
	  _path->setText(PN::DEF::defaultObjFilePath.c_str());
/*	  FXButton* browse = */new FXButton(hFramePath, "&Browse", NULL, this, ID_ADDOBJECT, BUTTON_DEFAULT|FRAME_RAISED|LAYOUT_FILL_X|FRAME_THICK);

	  // gros hack rapide pour jv : recopie des coordonnees de l'objet selectionne dans la liste box //
	  if (_objectsListBox->getNumItems() != 0)
	  {
		PNConfigurableObject*	co = (PNConfigurableObject*)_objectsListBox->getItemData(_objectsListBox->getCurrentItem());
		PN3DObject*			obj = ((EDITOR::PNGLShape*)co)->getObj();
		
		FXString  str;
		str.format("%f", obj->getCoord().x); _fieldX->setText(str); str.clear();
		str.format("%f", obj->getCoord().y); _fieldY->setText(str); str.clear();
		str.format("%f", obj->getCoord().z); _fieldZ->setText(str); str.clear();
	  }
	}

	new FXHorizontalSeparator(vFrame, LAYOUT_FILL_X);

	FXHorizontalFrame*	buttons = new FXHorizontalFrame(vFrame,LAYOUT_FILL_X|LAYOUT_FILL_Y);
	new FXButton(buttons,"&Ok",NULL,this,PNPropertiesPanel::ID_ADDWP,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);
	new FXButton(buttons,"&Cancel",NULL,this,PNPropertiesPanel::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|LAYOUT_CENTER_Y|FRAME_RAISED|FRAME_THICK,10,10,0,0, 20,20);
	
	_dbox->execute();
	update();

	return 1;
  }

  /*! Validates new element creation.
   *  Validates new element creation, closes dialog box, gives focus back to the main window.
   */
  long          PNPropertiesPanel::onAccept(FXObject* obj, FXSelector sel, void* ptr)
  {
	pnfloat		x,y,z;

	x = (pnfloat)atof(_fieldX->getText().text());
	y = (pnfloat)atof(_fieldY->getText().text());
	z = (pnfloat)atof(_fieldZ->getText().text());

	if (_type == PN_PANELTYPE_3DOBJECTS)
	{
	  PN3DObject *obj = new PN3DSkeletonObject;
	  PNEnvType t;

	  if (_objTypesListBox->getItemText(_objTypesListBox->getCurrentItem()) == (char *)PNXML_OBJECT_VAL)
		obj = new PN3DObject;
	  else if (_objTypesListBox->getItemText(_objTypesListBox->getCurrentItem()) == (char *)PNXML_DYNAMIC_VAL)
		obj = new PN3DSkeletonObject;
	  else if (_objTypesListBox->getItemText(_objTypesListBox->getCurrentItem()) == (char *)PNXML_CHARACTER_VAL)
		obj = new PNCharacter;

	  boost::filesystem::path p(_path->getText().text(), boost::filesystem::no_check);
	  _ed->makeViewerCurrent();
	  obj->unserializeFromFile(p);
	  _ed->makeViewerNonCurrent();

	  obj->setCoord(x, y, z);
	  if (_envTypesListBox->getItemText(_envTypesListBox->getCurrentItem()) == (char *)PNXML_GROUND_VAL)
		t = PN_GROUND;
	  else if (_envTypesListBox->getItemText(_envTypesListBox->getCurrentItem()) == (char *)PNXML_STATIC_VAL)
		t = PN_STATIC;
	  else if (_envTypesListBox->getItemText(_envTypesListBox->getCurrentItem()) == (char *)PNXML_DYNAMIC_VAL)
		t = PN_DYNAMIC;
	  _ed->add3DObject(obj, this, _idMax, t, _classLabel->getText().text(), _objLabel->getText().text());
	  _idMax++;
	  _dbox->getApp()->stopModal(_dbox, TRUE);
	  _dbox->close();
	}
	else if (_type == PN_PANELTYPE_WAYPOINTS)
	{
	  _objectsListBox->clearItems();
	  _ed->addWayPoint(x,y,z);
	  _dbox->getApp()->stopModal(_dbox, TRUE);
	  _dbox->close();
	}
	return 1;
  }

  /*! Cancel event, closes dialog box.
   *  Closes dialog box, gives focus back to the main window.
   */
  long          PNPropertiesPanel::onCancel(FXObject* obj, FXSelector sel, void* ptr)
  {
	_dbox->getApp()->stopModal(_dbox, TRUE);
	_dbox->close();
	return 1;
  }

  long			PNPropertiesPanel::onAddObject(FXObject* sender, FXSelector sel, void* ptr)
  {
	FXFileDialog			open(_grid, "Choose file to save the PN Object", SELECTFILE_MULTIPLE);
	open.setPatternList("Pavillon-Noir Objects (*.pno)");

	if (open.execute())
	{
	  char buf[512] = "";
	  getcwd(buf, 512);

	  FXString strbuf(buf);
	  strbuf = strbuf.substitute('\\', '/');

	  FXString str = open.getFilename();

	  pnerror(PN_LOGLVL_DEBUG, "strbuf=%s, str=%s", strbuf.text(), str.substitute('\\','/').text());
	  if ( str.substitute('\\','/').find(strbuf.text(), 0) == -1)
	  {
		FXMessageBox dbox(this, "File Error", "403");
		dbox.execute();
	  }
	  else
	  {
		_path->setText(str.replace(0, strlen(buf) + 1, "").substitute('\\', '/').text());
	  }
	}
	return 1;
  }

  pnint			PNPropertiesPanel::getIdMax()
  {
	return _idMax;
  }

  void			PNPropertiesPanel::incrementIdMax()
  {
	_idMax++;
  }

};
