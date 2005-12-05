/*
 * PN3DObjectExporter.cpp
 * 
 * Description :
 * PN3DObjectExporter definition
 *
 * Copyright (C) 2005 PAVILLON-NOIR TEAM, http://pavillon-noir.org
 *
 * This file is part of pnmaxplugin.
 *
 * pnmaxplugin is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * pnmaxplugin is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with pnmaxplugin; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "stdafx.h"

#include "PN3DObjectExporter.hpp"
#include "pnmaxplugin.h"

#include "PNMainWin.hpp"
#include "PNObjectWindow.hpp"

#include "pnmaxplugin.h"

#include "pno_format.h"

//////////////////////////////////////////////////////////////////////////

void			PN3DObjectExporterDesc::SetInstance(HINSTANCE hInstance)
{
  _hInstance = hInstance;
}

int 			PN3DObjectExporterDesc::IsPublic()
{
  return TRUE;
}

void *			PN3DObjectExporterDesc::Create(BOOL loading)
{
  return new PN3DObjectExporter();
}

const TCHAR *	PN3DObjectExporterDesc::ClassName()
{
  return theApp.GetString(IDS_CLASS_NAME);
}

SClass_ID		PN3DObjectExporterDesc::SuperClassID()
{
  return SCENE_EXPORT_CLASS_ID;
}

Class_ID		PN3DObjectExporterDesc::ClassID()
{
  return PN3DOBJECEXPORTER_CLASS_ID;
}

// The Skin modifier checks the category to decide whether the modifier is a Skin Gizmo.  This 
// must not be changed
const TCHAR* 	PN3DObjectExporterDesc::Category()
{
  return _T("Game Utilities");
}

const TCHAR*	PN3DObjectExporterDesc::InternalName()
{
  return _T("PN3DObjectExporter");
}

HINSTANCE		PN3DObjectExporterDesc::HInstance()
{
  return _hInstance;
}

//////////////////////////////////////////////////////////////////////////
//--- pnmaxplugin -------------------------------------------------------

PN3DObjectExporter::PN3DObjectExporter()
{
  _ext = PNO_EXT;
  _longDesc = PNO_LONGDESC;
  _shortDesc = PNO_SHORTDESC;

  _hasModel = true;
  _hasMaterials = true;
  _hasSkeleton = true;
  _hasAnimation = true;

  _owin = NULL;

  DefaultDirection = true;
  Front.Set(0.0f, 1.0f, 0.0f);
  Right.Set(1.0f, 0.0f, 0.0f);
  Top.Set(0.0f, 0.0f, 1.0f);
}

PN3DObjectExporter::~PN3DObjectExporter() 
{

}

void PN3DObjectExporter::ShowAbout(HWND hWnd)
{			
  // Optional
}

//////////////////////////////////////////////////////////////////////////

int PN3DObjectExporter::initExport()
{
  _hasModel = theApp.getIntOption("pno", "hasModel", TRUE) == TRUE;
  _saveModel = theApp.getIntOption("pno", "saveModel", TRUE) == TRUE;

  _hasMaterials = theApp.getIntOption("pno", "hasMaterials", TRUE) == TRUE;
  _saveMaterials = theApp.getIntOption("pno", "saveMaterials", TRUE) == TRUE;

  _hasSkeleton = theApp.getIntOption("pno", "hasSkeleton", TRUE) == TRUE;
  _saveSkeleton = theApp.getIntOption("pno", "saveSkeleton", TRUE) == TRUE;

  _hasAnimation = theApp.getIntOption("pno", "hasAnimation", TRUE) == TRUE;
  _saveAnimation = theApp.getIntOption("pno", "saveAnimation", TRUE) == TRUE;

  _hasPhysics = theApp.getIntOption("pno", "hasPhysics", TRUE) == TRUE;
  _savePhysics = theApp.getIntOption("pno", "savePhysics", TRUE) == TRUE;

  _modelExporter.setIgameScene(_igameScene);
  _modelExporter.initExport();

  _materialsExporter.setIgameScene(_igameScene);
  _materialsExporter.initExport();

  _skeletonExporter.setIgameScene(_igameScene);
  _skeletonExporter.initExport();

  _animationExporter.setIgameScene(_igameScene);
  _animationExporter.initExport();

  _physicalExporter.setIgameScene(_igameScene);
  _physicalExporter.initExport();

  return TRUE;
}

int PN3DObjectExporter::initFiles(CString file)
{
  _initFile.SetFilePath(file);

  _owin = new PNObjectWindow(this);
  _owin->DoModal();

  return TRUE;
}

int	PN3DObjectExporter::releaseExport()
{
  _modelExporter.releaseExport();
  _materialsExporter.releaseExport();
  _skeletonExporter.releaseExport();
  _animationExporter.releaseExport();
  _physicalExporter.releaseExport();

  delete _owin;

  theApp.setIntOption("pno", "hasModel", _hasModel);
  theApp.setIntOption("pno", "saveModel", _saveModel);

  theApp.setIntOption("pno", "hasMaterials", _hasMaterials);
  theApp.setIntOption("pno", "saveMaterials", _saveMaterials);

  theApp.setIntOption("pno", "hasSkeleton", _hasSkeleton);
  theApp.setIntOption("pno", "saveSkeleton", _saveSkeleton);

  theApp.setIntOption("pno", "hasAnimation", _hasAnimation);
  theApp.setIntOption("pno", "saveAnimation", _saveAnimation);

  theApp.setIntOption("pno", "hasPhysics", _hasPhysics);
  theApp.setIntOption("pno", "savePhysics", _savePhysics);

  return TRUE;
}

int PN3DObjectExporter::exportHeader()
{
  PNMainWin::WriteLine("PN3DObjectExporter::exportHeader()");

  _file->Write(PNO_XML_HEADER.c_str(), (UINT)PNO_XML_HEADER.size());

  return TRUE;
}

int PN3DObjectExporter::exportBody()
{
  PNMainWin::WriteLine("PN3DObjectExporter::exportBody()");

  std::ostringstream	objString;

  objString << "<" << PNO_XMLNODE_ROOT;

  if (!DefaultDirection)
  {
	Point3	pnFront = -Top;
	Point3	pnRight = Right;
	Point3	pnTop = Front;

	objString
	  << " " << PNO_XMLPROP_FRONT << "=\"" << pnFront.x << " " << pnFront.y << " " << pnFront.z << "\""
	  << " " << PNO_XMLPROP_RIGHT << "=\"" << pnRight.x << " " << pnRight.y << " " << pnRight.z << "\""
	  << " " << PNO_XMLPROP_TOP << "=\"" << pnTop.x << " " << pnTop.y << " " << pnTop.z << "\"";
  }

  objString << ">\n";

  if (_owin->hasModel())
  {
	PNMainWin::WriteLine(_owin->getModelFullPath());
	if (_saveModel)
	  _modelExporter.export(_owin->getModelFullPath());

	objString << "  " << "<" << PNO_XMLNODE_MODEL << " " << PNO_XMLPROP_PATH << "=\"" << _owin->getModelFile().GetString() << "\" />\n";
  }

  if (_owin->hasMaterials())
  {
	PNMainWin::WriteLine(_owin->getMaterialsFullPath());
	if (_saveMaterials)
	  _materialsExporter.export(_owin->getMaterialsFullPath());

	objString << "  " << "<" << PNO_XMLNODE_LISTMATERIALS << ">\n";
	for (int i = 0 ; i < _owin->getNbMaterials(); i++)
	  objString << "    " << "<" << PNO_XMLNODE_MATERIAL << " " << PNO_XMLPROP_PATH << "=\"" << _owin->getMaterialFile(i) << "\" />\n";
	objString << "  " << "</" << PNO_XMLNODE_LISTMATERIALS << ">\n";
  }

  if (_owin->hasSkeleton())
  {
	PNMainWin::WriteLine(_owin->getSkeletonFullPath());
	if (_saveSkeleton)
	  _skeletonExporter.export(_owin->getSkeletonFullPath());

	objString << "  " << "<" << PNO_XMLNODE_SKELETON << " " << PNO_XMLPROP_PATH << "=\"" << _owin->getSkeletonFile().GetString() << "\" />\n";
  }

  if (_owin->hasAnimation())
  {
	PNMainWin::WriteLine(_owin->getAnimationFullPath());
	if (_saveAnimation)
	  _animationExporter.export(_owin->getAnimationFullPath());

	objString << "  " << "<" << PNO_XMLNODE_LISTANIMS << ">\n";
	objString << "    " << "<" << PNOA_XMLNODE_ROOT << " " << PNO_XMLPROP_PATH << "=\"" << _owin->getAnimationFile().GetString() << "\" />\n";
	objString << "  " << "</" << PNO_XMLNODE_LISTANIMS << ">\n";
  }

  if (_owin->hasPhysics())
  {
	PNMainWin::WriteLine(_owin->getPhysicalFullPath());
	if (_savePhysics)
	  _physicalExporter.export(_owin->getPhysicalFullPath());

	objString << "  " << "<" << PNO_XMLNODE_PHYSICS << " " << PNO_XMLPROP_PATH << "=\"" << _owin->getPhysicalFullPath().GetString() << "\" />\n";
  }

  objString << "</" << PNO_XMLNODE_ROOT << ">\n";

  _file->Write(objString.str().c_str(), (UINT)objString.str().size());

  return TRUE;
}

int PN3DObjectExporter::configure()
{
  _owin->DoModal();

  return TRUE;
}
