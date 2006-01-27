/*
 * PNFXLinksParameter.cpp
 * 
 * Description :
 * PNFXLinksParameter definition
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


#include "pneditorcommon.h"
#include "pnproperties.h"

#include "PNFXLinksParameter.hpp"

#include "PN3DObject.hpp"
#include "PN3DModel.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNPropertiesGrid.hpp"

using namespace std;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXLinksParameter) PNFXLinksParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND,PNFXLinksParameter::ID_LISTBOX_SEL,PNFXLinksParameter::onCmdListBox),
  FXMAPFUNC(SEL_COMMAND,PNFXLinksParameter::ID_DELETE,PNFXLinksParameter::onDelete),
  FXMAPFUNC(SEL_COMMAND,PNFXLinksParameter::ID_ADD,PNFXLinksParameter::onAdd),
  FXMAPFUNC(SEL_COMMAND,PNFXLinksParameter::ID_RADIO_SIMPLE,PNFXLinksParameter::onRadioSimple),
  FXMAPFUNC(SEL_COMMAND,PNFXLinksParameter::ID_RADIO_DOUBLE,PNFXLinksParameter::onRadioDouble),
  FXMAPFUNC(SEL_COMMAND,PNFXLinksParameter::ID_MAKELINK,PNFXLinksParameter::onAccept),
  FXMAPFUNC(SEL_COMMAND,PNFXLinksParameter::ID_CANCEL,PNFXLinksParameter::onCancel)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXLinksParameter,FXHorizontalFrame,PNFXLinksParameterMap,ARRAYNUMBER(PNFXLinksParameterMap))

/*
*	  Construct a PNFXLinksParameter : 
*		- all availables links for the selected waypoint are listed in a FXListBox
*		- the coefficient of the selected link is visible in a FXTextField (real values only)
*		- Two FXButtons ("Add" and "Delete") permit links list edition.
*	  on creation this widget retrieves waypoints graph to edit it.
*/
PNFXLinksParameter::PNFXLinksParameter(FXComposite* p, PNConfigurableParameter* param)
: FXHorizontalFrame(p),
PNPropertiesGridParameter(param)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXLinksParameter::PNFXLinksParameter(FXComposite* p, PNConfigurableParameter* param)");
  _parent = p;
  _graph = (PNIAGraph*)((PNWayPoint*)_param->getElem())->getGraph();
  _listbox = new FXListBox(this, this, ID_LISTBOX_SEL,LAYOUT_FILL_X | FRAME_SUNKEN | FRAME_THICK, 0,0,10,0);
  //	FXLabel* coefText = new FXLabel(this, "coef:"); // UNUSED
  new FXLabel(this, "coef:");
  _fieldCoef = new FXTextField(this, 8, NULL, 0, TEXTFIELD_REAL|FRAME_SUNKEN|FRAME_THICK|LAYOUT_SIDE_TOP);
  _buttonAdd = new FXButton(this, "Add", NULL, this, ID_ADD,FRAME_RAISED|FRAME_THICK);
  _buttonDelete = new FXButton(this, "Delete", NULL, this, ID_DELETE,FRAME_RAISED|FRAME_THICK);
}

PNFXLinksParameter::~PNFXLinksParameter()
{
  delete _listbox;
  delete _buttonAdd;
  delete _buttonDelete;
  delete _fieldCoef;
}
//////////////////////////////////////////////////////////////////////////

void	PNFXLinksParameter::create()
{
  FXHorizontalFrame::create();

  updateParam();
}

/*
*	Builds links list for current parameter.
*/
void	PNFXLinksParameter::buildList(void)
{

  LINKLIST& list = (LINKLIST&)((PNWayPoint*)_param->getElem())->getLinks();

  _listbox->clearItems();
  for (LINKLIST::iterator it = list.begin(); it != list.end(); it++)
  {
	PNWayPoint*			mynext = (*it)->next;
	//	  pnfloat*				coef = &((*it)->coef); // UNUSED
	FXString  str;

	str.format("%i", (int)mynext->getId());
	_listbox->appendItem(str,NULL,*it);
	_lnkMap[(int)mynext->getId()] = 1;
  }
}

/*
*	Updates ListBox selection.
*/
long	PNFXLinksParameter::onCmdListBox(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXLinksParameter::onCmdListBox");
  updateCoef();

  return 1;
}

/*
*	Deletes selected link.
*/
long	PNFXLinksParameter::onDelete(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXLinksParameter::onDelete");
  if (_listbox->getNumItems() != 0)
  {
	PNWayPoint* wp = (PNWayPoint*)_param->getElem();
	wayLink_t*	lnk = (wayLink_t*)_listbox->getItemData(_listbox->getCurrentItem());

	wp->deleteLink(lnk->next);
	update();
  }

  return 1;
}

/*
*	Adds a new link by opening a dialog box containing Fox widgets
*	  - one FXListBox containing linkable waypoints only
*	  - two FXRadioButton to choose link type (SIMPLE/DOUBLE)
*	  - one FXTextField to set the coefficient (real values only)
*	  - two FXButton to validate/cancel link creation
*/
long	PNFXLinksParameter::onAdd(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXLinksParameter::onAdd");
  _dbox = new FXDialogBox(_parent,"Add Link",DECOR_TITLE|DECOR_BORDER|DECOR_RESIZE, 0,0,200,200);

  FXHorizontalFrame*	listAndCoef = new FXHorizontalFrame(_dbox);
  //	FXLabel*  labelWaypoint = new FXLabel(listAndCoef, "Waypoint:"); // UNUSED
  new FXLabel(listAndCoef, "Waypoint:");
  _lnkList = new FXListBox(listAndCoef, this, 0,LAYOUT_FILL_X | LAYOUT_CENTER_X | FRAME_SUNKEN | FRAME_THICK);
  //	FXLabel*  labelCoef = new FXLabel(listAndCoef, "Coef:"); // UNUSED
  new FXLabel(listAndCoef, "Coef:");
  _fieldAddCoef = new FXTextField(listAndCoef, 5, NULL, 0, LAYOUT_FILL_X | LAYOUT_CENTER_X | TEXTFIELD_REAL | FRAME_SUNKEN | FRAME_THICK);

  //FXHorizontalFrame*	  linkType = new FXHorizontalFrame(_dbox);
  FXGroupBox*	  linkType = new FXGroupBox(_dbox,"Link type",GROUPBOX_TITLE_CENTER|FRAME_RIDGE|LAYOUT_FILL_X);
  _simpleLnk = new FXRadioButton(linkType,"Simple", this, ID_RADIO_SIMPLE);
  _doubleLnk = new FXRadioButton(linkType,"Double", this, ID_RADIO_DOUBLE);

  FXHorizontalFrame*	  buttons = new FXHorizontalFrame(_dbox);
  new FXButton(buttons,"&Cancel",NULL,this,PNFXLinksParameter::ID_CANCEL,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
  new FXButton(buttons,"&Ok",NULL,this,PNFXLinksParameter::ID_MAKELINK,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);

  WPLIST& wplist = _graph->getWayPoints();
  for (WPLIST::iterator i = wplist.begin(); i != wplist.end(); i++)
  {
	FXString	str;
	pnint		id = (*i)->getId();
	str.format("%i", (*i)->getId());
	if (id != ((PNWayPoint*)_param->getElem())->getId() && (_lnkMap.find(id) == _lnkMap.end()))
	  _lnkList->appendItem(str,NULL,*i);
  }
  _doubleLnk->setCheck(TRUE);
  _fieldAddCoef->setText("1.0");
  _dbox->execute();
  update();

  return 1;
}

/*
*
*/
long	PNFXLinksParameter::onRadioSimple(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXLinksParameter::onRadioSimple()");
  _doubleLnk->setCheck(FALSE);

  return 1;
}

/*
*
*/
long	PNFXLinksParameter::onRadioDouble(FXObject* obj,FXSelector sel,void* ptr)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXLinksParameter::onRadioDouble()");
  _simpleLnk->setCheck(FALSE);

  return 1;
}

/*
*	Validates link creation :
*	  - adds the new link to the waypoints graph
*	  - closes current dialog box
*/
long	PNFXLinksParameter::onAccept(FXObject* obj,FXSelector sel,void* ptr)
{
  pnbool		lnktype;
  pnfloat		coef;
  PNWayPoint*	wp1 = (PNWayPoint*)_param->getElem();
  PNWayPoint*	wp2 = (PNWayPoint*)_lnkList->getItemData(_lnkList->getCurrentItem());

  lnktype = _simpleLnk->getCheck() == TRUE ? SINGLE : DOUBLE;
  coef = (pnfloat)atof(_fieldAddCoef->getText().text());
  _graph->makeLink(wp1->getId(), wp2->getId(), lnktype, coef);
  _dbox->getApp()->stopModal(_dbox, TRUE);
  _dbox->close();

  return 1;
}

long	PNFXLinksParameter::onCancel(FXObject* obj,FXSelector sel,void* ptr)
{
  _dbox->getApp()->stopModal(_dbox, TRUE);
  _dbox->close();
  return 1;
}

void
PNFXLinksParameter::updateParam()
{
  _listbox->clearItems();
  buildList();
  _param->getConfigurableObject()->update(_param);
  _listbox->setNumVisible(_listbox->getNumItems());
  _listbox->sortItems();
  updateCoef();
}

void
PNFXLinksParameter::apply()
{

}

/*
*	updates coef text field.
*/
void	PNFXLinksParameter::updateCoef(void)
{
  if (_listbox->getNumItems() != 0)
  {
	wayLink_t*	lnk = (wayLink_t*)_listbox->getItemData(_listbox->getCurrentItem());
	FXString	str;

	str.format("%f", lnk->coef);

	_fieldCoef->setText(str);
	_fieldCoef->setEditable(_param->isEditable());
  }
}

//////////////////////////////////////////////////////////////////////////
};
