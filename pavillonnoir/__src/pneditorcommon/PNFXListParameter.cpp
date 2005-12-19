/*
 * PNFXListParameter.cpp
 * 
 * Description :
 * PNFXListParameter definition
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

#include <sstream>
#include <list>

#include "pneditorcommon.h"
#include "pnproperties.h"
#include "pnimport.h"

#include "PNPropertiesGrid.hpp"

#include "PNFXListParameter.hpp"

using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXListParameter) PNFXListParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXListParameter::ID_DELETE, PNFXListParameter::onDelete),
  FXMAPFUNC(SEL_COMMAND, PNFXListParameter::ID_ADD, PNFXListParameter::onAdd),
  FXMAPFUNC(SEL_COMMAND, PNFXListParameter::ID_EDIT, PNFXListParameter::onEdit),
  FXMAPFUNC(SEL_COMMAND, PNFXListParameter::ID_LISTBOX_SEL, PNFXListParameter::onCmdListBox)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT_ABSTRACT(PNFXListParameter, FXHorizontalFrame, PNFXListParameterMap, ARRAYNUMBER(PNFXListParameterMap))

PNFXListParameter::PNFXListParameter(FXComposite* p, PNConfigurableParameterList* param)
: FXHorizontalFrame(p), PNPropertiesGridParameterList(param)
{
  _numVisibleItems = 5;

  _listBox = new FXListBox(this, this, ID_LISTBOX_SEL, LAYOUT_FILL_X | FRAME_SUNKEN | FRAME_THICK, 0, 0, 50, 0);

  _buttonAdd = new FXButton(this, "Add", NULL, this, ID_ADD, FRAME_RAISED | FRAME_THICK);
  _buttonDelete = new FXButton(this, "Delete", NULL, this, ID_DELETE, FRAME_RAISED | FRAME_THICK);
  _buttonEdit = new FXButton(this, "Edit", NULL, this, ID_EDIT,FRAME_RAISED | FRAME_THICK);
}

PNFXListParameter::~PNFXListParameter()
{
  delete _buttonAdd;
  delete _buttonDelete;
  delete _buttonEdit;
  delete _listBox;
}
//////////////////////////////////////////////////////////////////////////

void
PNFXListParameter::create()
{
  FXHorizontalFrame::create();

  _listBox->create();
  _buttonDelete->create();
  _buttonAdd->create();
  _buttonEdit->create();

  update();
}


//////////////////////////////////////////////////////////////////////////

template<class _ListElement>
void
PNFXListParameter::_deleteFromList(FXint index, std::list<_ListElement>& lst)
{
  std::list<_ListElement>::iterator	it = lst.begin();
  for (int i = 0; it != lst.end(); ++i, ++it)
  {
	if  (i == index)
	{
	  lst.erase(it);
	  break;
	}
  }
}

void
PNFXListParameter::_editElement(pnint& elem)
{
  FXint	val;

  FXInputDialog::getInteger(val, this, "Value", "Value");

  elem = val;
}

void
PNFXListParameter::_editElement(pnuint& elem)
{
  FXint	val;

  FXInputDialog::getInteger(val, this, "Value", "Value");

  elem = (pnuint)val;
}

void	
PNFXListParameter::_editElement(pnfloat& elem)
{
  FXdouble	val;

  FXInputDialog::getReal(val, this, "Value", "Value");

  elem = (pnfloat)val;
}

void
PNFXListParameter::_editElement(std::string& elem)
{
  FXString	val;

  FXInputDialog::getString(val, this, "Value", "Value");

  elem = val.text();
}

template<class _ListElement>
void
PNFXListParameter::_addInList(FXint index, std::list<_ListElement>& lst)
{
  std::list<_ListElement>::iterator	it = lst.begin();
  for (int i = 0; it != lst.end(); ++i, ++it)
  {
	if  (i == index)
	{
	  _ListElement	val;
	  _editElement(val);

	  lst.insert(it, val);

	  break;
	}
  }
}

template<class _ListElement>
void
PNFXListParameter::_editInList(FXint index, std::list<_ListElement>& lst)
{
  std::list<_ListElement>::iterator	it = lst.begin();
  for (int i = 0; it != lst.end(); ++i, ++it)
  {
	if  (i == index)
	{
	  _editElement(*it);
	  break;
	}
  }
}

template<class _ListElement>
void
PNFXListParameter::_updateList(std::list<_ListElement>& lst)
{
  _listBox->clearItems();

  for (std::list<_ListElement>::iterator it = lst.begin(); it != lst.end(); ++it)
  {
	std::ostringstream os;
	os << *it;

	_listBox->appendItem(os.str().c_str());
  }
}

bool
PNFXListParameter::_deleteObject(FXint index)
{
  switch (_param->getType())
  {
  case PN_LISTPARAMTYPE_INT:
  case PN_LISTPARAMTYPE_UINT:
	_deleteFromList(index, *((std::list<pnint>*)_param->getElem()));
  	break;
  case PN_LISTPARAMTYPE_REAL:
	_deleteFromList(index, *((std::list<pnfloat>*)_param->getElem()));
	break;
  case PN_LISTPARAMTYPE_STRING:
  case PN_LISTPARAMTYPE_FILE:
  case PN_LISTPARAMTYPE_DIR:
	_deleteFromList(index, *((std::list<std::string>*)_param->getElem()));
	break;
  default:
	return false;
  }

  return true;
}

bool
PNFXListParameter::_addNewObject(FXint index)
{
  switch (_param->getType())
  {
  case PN_LISTPARAMTYPE_INT:
  case PN_LISTPARAMTYPE_UINT:
	_addInList(index, *((std::list<pnint>*)_param->getElem()));
	break;
  case PN_LISTPARAMTYPE_REAL:
	_addInList(index, *((std::list<pnfloat>*)_param->getElem()));
	break;
  case PN_LISTPARAMTYPE_STRING:
  case PN_LISTPARAMTYPE_FILE:
  case PN_LISTPARAMTYPE_DIR:
	_addInList(index, *((std::list<std::string>*)_param->getElem()));
	break;
  default:
	return false;
  }

  return false;
}

bool
PNFXListParameter::_editObject(FXint index)
{
  return false;
}

void
PNFXListParameter::_update()
{
  switch (_param->getType())
  {
  case PN_LISTPARAMTYPE_INT:
  case PN_LISTPARAMTYPE_UINT:
	_updateList(*((std::list<pnint>*)_param->getElem()));
	break;
  case PN_LISTPARAMTYPE_REAL:
	_updateList(*((std::list<pnfloat>*)_param->getElem()));
	break;
  case PN_LISTPARAMTYPE_STRING:
  case PN_LISTPARAMTYPE_FILE:
  case PN_LISTPARAMTYPE_DIR:
	_updateList(*((std::list<std::string>*)_param->getElem()));
	break;
  default:
	return ;
  }
}

//////////////////////////////////////////////////////////////////////////

void
PNFXListParameter::update()
{
  FXHorizontalFrame::update();

  _update();

  if (_listBox->getNumItems() > 0)
	_listBox->setCurrentItem(getChoise());

  if (_numVisibleItems > 0)
	_listBox->setNumVisible(_listBox->getNumItems() < _numVisibleItems ? _listBox->getNumItems() : _numVisibleItems);
  else
	_listBox->setNumVisible(_listBox->getNumItems());

  if (_param->isEditable())
  {
	_buttonAdd->enable();
	_buttonDelete->enable();
	_buttonEdit->enable();
  }
  else
  {
	_buttonAdd->disable();
	_buttonDelete->disable();
	_buttonEdit->disable();
  }
}

/*
*	Deletes selected object.
*/
long
PNFXListParameter::onDelete(FXObject* obj, FXSelector sel, void* ptr)
{
  if (_listBox->getNumItems() == 0)
	return 1;

  //////////////////////////////////////////////////////////////////////////

  FXint	index = _listBox->getCurrentItem();

  if (_deleteObject(index))
  {
	if (index != 0 && index <= (FXint)getChoise())
	  setChoise(getChoise() - 1);

	sendParamModif();
	update();
  }

  return 1;
}

long
PNFXListParameter::onAdd(FXObject* obj, FXSelector sel, void* ptr)
{ 
  if (_listBox->getNumItems() == 0)
	return 1;

  //////////////////////////////////////////////////////////////////////////
  FXint	index = _listBox->getCurrentItem();

  if (_addNewObject(index))
  {
	if (index >= (FXint)getChoise())
	  setChoise(getChoise() + 1);

	sendParamModif();
	update();
  }

  return 1;
}

long
PNFXListParameter::onEdit(FXObject* obj, FXSelector sel, void* ptr)
{
  if (_listBox->getNumItems() == 0)
	return 1;

  //////////////////////////////////////////////////////////////////////////

  FXint	index = _listBox->getCurrentItem();

  if (_editObject(index))
  {
	if (index >= (FXint)getChoise())
	  setChoise(getChoise() + 1);

	sendParamModif();
	update();
  }

  return 1;
}

long
PNFXListParameter::onCmdListBox(FXObject* obj, FXSelector sel, void* ptr)
{
  FXint	index = _listBox->getCurrentItem();

  if (index != getChoise() && index > 0)
  {
	setChoise(index);
	sendParamModif();
  }

  return 1;
}

//////////////////////////////////////////////////////////////////////////
};
