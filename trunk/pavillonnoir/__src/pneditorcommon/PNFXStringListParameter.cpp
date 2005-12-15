/*
 * PNFXStringListParameter.cpp
 * 
 * Description :
 * PNFXStringListParameter definition
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
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "pneditorcommon.h"
#include "pnproperties.h"
#include "pnimport.h"

#include "PNFXStringListParameter.hpp"

#include "PNImportManager.hpp"
#include "PN3DAnimation.hpp"
#include "PN3DSkeletonObject.hpp"
#include "PN3DModel.hpp"
#include "PNWayPoint.hpp"
#include "PNIAGraph.hpp"
#include "PNPropertiesGrid.hpp"

using namespace std;
namespace fs = boost::filesystem;

namespace PN {
//////////////////////////////////////////////////////////////////////////

// Map
FXDEFMAP(PNFXStringListParameter) PNFXStringListParameterMap[]=
{
  FXMAPFUNC(SEL_COMMAND, PNFXStringListParameter::ID_LISTBOX_SEL, PNFXStringListParameter::onCmdListBox)
};

//////////////////////////////////////////////////////////////////////////
FXIMPLEMENT(PNFXStringListParameter, PNFXListParameter, PNFXStringListParameterMap, ARRAYNUMBER(PNFXStringListParameterMap))

PNFXStringListParameter::PNFXStringListParameter(FXComposite* p, PNConfigurableParameterList* param)
: PNFXListParameter(p, param)
{
  pnerror(PN_LOGLVL_DEBUG, "PNFXStringListParameter::PNFXStringListParameter(FXComposite* p, PNConfigurableParameter* param)");
  
  _labelsNumChars = 29;
  _numVisibleItems = 5;

  _buildList();
}

PNFXStringListParameter::~PNFXStringListParameter()
{
  
}
//////////////////////////////////////////////////////////////////////////

void
PNFXStringListParameter::create()
{
  PNFXListParameter::create();
}

/*
*	Builds StringList list for current parameter.
*/
void
PNFXStringListParameter::_buildList(void)
{
  std::list<std::string>* l = (std::list<std::string>*)_param->getElem();

  pnerror(PN_LOGLVL_DEBUG, "PNFXStringListParameter::buildList");
  _listBox->clearItems();

  if (l->size() == 0)
  {
	return;
  }

  for (std::list<std::string>::iterator it = l->begin(); it != l->end(); it++)
  {
	std::string s = (*it);
	if (_labelsNumChars != 0 && _labelsNumChars != 0 && s.size() > (pnuint)_labelsNumChars)
	{	
	  int before = (_labelsNumChars-5)/5*2;
	  int after = _labelsNumChars-5-before;
	  s = s.substr(0, before) + "[...]" + s.substr(s.size()-after, s.size());
	}
	_listBox->appendItem(s.c_str(), NULL, NULL);
  }

  if (_numVisibleItems != 0 && _numVisibleItems != 0) 
	_listBox->setNumVisible(_listBox->getNumItems() < _numVisibleItems ? _listBox->getNumItems() : _numVisibleItems);
  else
	_listBox->setNumVisible(_listBox->getNumItems());

  pnerror(PN_LOGLVL_DEBUG, "End of PNFXStringListParameter::buildList");
}

long
PNFXStringListParameter::onCmdListBox(FXObject*,FXSelector,void*)
{
  return 1;
}

/*
*	Updates StringList
*/
void
PNFXStringListParameter::_update(void)
{
}

void
PNFXStringListParameter::setLabelsNumChars(int numChars)
{
  _labelsNumChars = numChars;
}

void
PNFXStringListParameter::setNumVisibleItems(int numItems)
{
  _numVisibleItems = numItems;
}

std::string
PNFXStringListParameter::getStringValue()
{
  FXString fxstr = _listBox->getItemText(_listBox->getCurrentItem());
  std::string* str = new std::string(fxstr.text());

  return *str;
}

/*! Runs through the list and selects the given string.
*  \param	val	  the string to select in _listBox
*  \return true on success, false if val is not part of _listBox
*/
pnbool
PNFXStringListParameter::setStringValue(const std::string& val)
{
  int idx = _listBox->findItem(val.c_str());

  if (idx != -1)
  {
	_listBox->setCurrentItem(idx);
	return true;
  }

  return false;
}

bool
PNFXStringListParameter::_deleteObject(FXint index)
{
  return false;
}

bool
PNFXStringListParameter::_addNewObject(FXint index)
{
  return false;
}

//////////////////////////////////////////////////////////////////////////
};
