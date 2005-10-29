/*
 * PNPropertiesPanel.hpp
 * 
 * Description :
 * PNPropertiesPanel declaration
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


#ifndef _PN_PROPERTIESPANEL_HPP_
# define _PN_PROPERTIESPANEL_HPP_

/////////////////////////////////////

#include <list>
#include <fx.h>

/////////////////////////////////////

#include "PNPropertiesGrid.hpp"
#include "PNConfigurableObject.hpp"
#include "PNEditor.hpp" // linux

/////////////////////////////////////

namespace PN
{
  class PNEditor;

  //////////////////////////////////////////////////////////////////////////

  class PNPropertiesPanel : public FXComposite, public PNEditorObject
  {
    FXDECLARE(PNPropertiesPanel)

  public:
	typedef	enum
	{
	  PN_PANELTYPE_3DOBJECTS,
	  PN_PANELTYPE_WAYPOINTS
	}		paneltype_t;

  private:
	// list of all the PNConfigurableObject in the panel
    std::list<PNConfigurableObject*>  _objectsList;
    FXGroupBox*                       _groupBox;   
	FXListBox*                        _objectsListBox;
	FXButton*						  _buttonAdd;
	FXButton*						  _buttonDelete;
	FXButton*						  _buttonSave;
	FXButton*						  _buttonReset;
  PNPropertiesGrid*                 _grid;
	EDITOR::PNEditor*				  _ed;
	
	// dialogbox
	FXDialogBox*					  _dbox;
	FXListBox*                        _envTypesListBox;
	FXListBox*                        _objTypesListBox;
	FXTextField*					  _fieldX;
	FXTextField*					  _fieldY;
	FXTextField*					  _fieldZ;
	FXTextField*					  _objLabel;
	FXTextField*					  _classLabel;
	FXTextField*					  _path;

	paneltype_t						  _type;
	pnint							  _idMax;

  protected:
    PNPropertiesPanel(){}

  public:
    long onCmdListBox(FXObject* obj, FXSelector sel, void* ptr);
	long onCmdAdd(FXObject* obj, FXSelector sel, void* ptr);
	long onCmdDelete(FXObject* obj, FXSelector sel, void* ptr);
	long onCmdSave(FXObject* obj, FXSelector sel, void* ptr);
	long onCmdReset(FXObject* obj, FXSelector sel, void* ptr);
	// dialogbox
	long onAccept(FXObject* obj, FXSelector sel, void* ptr);
	long onCancel(FXObject* obj, FXSelector sel, void* ptr);
	long onAddObject(FXObject* sender, FXSelector sel, void* ptr);

	void  addObject(PNConfigurableObject* object);
	void  setObject(PNConfigurableObject* object);
	PNConfigurableObject*	getObject();

    PNPropertiesPanel(FXComposite* p, paneltype_t t, EDITOR::PNEditor* ed);      
    virtual ~PNPropertiesPanel();

    void  create();
	void  update();
	void  clear();

  public:
	void  updateGrid();
	void  updateView();
	void  updateListBox();

	pnint getIdMax();
	void  incrementIdMax();

  protected:
	void updateGrid(PNConfigurableObject* co);
	void updateView(PNConfigurableObject* co);
   
  public:
    enum {
      // _objectsListBox selection changed
	  ID_LISTBOX_SEL = FXComposite::ID_LAST,
	  ID_ADD,
	  ID_DELETE,
	  ID_SAVE,
	  ID_RESET,
	  ID_ADDWP,
	  ID_CANCEL,
	  ID_ADDOBJECT,
	  ID_LAST
	};
  };

  //////////////////////////////////////////////////////////////////////////
};

#endif /* _PN_PROPERTIESPANEL_HPP_ */
