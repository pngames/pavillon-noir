/*
 * PNExporter.hpp
 * 
 * Description :
 * PNExporter declaration
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

#pragma once

#include "PNMainWin.hpp"

//////////////////////////////////////////////////////////////////////////

namespace PN {
//////////////////////////////////////////////////////////////////////////

const static pnpoint3f	_defaultVertex = {0.0f, 0.0f, 0.0f};
const static pnpoint3f	_defaultNormale = {0.0f, 0.0f, 0.0f};
const static pnpoint2f	_defaultTexCoord = {0.0f, 0.0f};
const static pncolor_t	_defaultColor = {1.0f, 1.0f, 1.0f, 1.0f};

//////////////////////////////////////////////////////////////////////////

class					PNExporter : public SceneExport
{
protected:
  CString				_ext;
  CString				_shortDesc;
  CString				_longDesc;
protected:
  IGameScene*			_igameScene;
  CFile	*				_file;

  //CString				_path;
  CString				_directory;
public:
  CFile*				getFile() {return _file;}
  void					setIgameScene(IGameScene* igameScene) {_igameScene = igameScene;}
public:
  PNExporter() {}
  virtual ~PNExporter(void) {}

  virtual int			export(CString path);

  virtual int			initExport()=0;
  virtual int			initFiles(CString file);
  virtual int			releaseExport()=0;

  virtual int			exportHeader()=0;
  virtual int			exportBody()=0;

  virtual int			configure()=0;

  virtual int			DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);

  //////////////////////////////////////////////////////////////////////////
  
  virtual int			ExtCount();					// Number of extensions supported
  virtual const TCHAR*	Ext(int n);					// Extension #n (i.e. "3DS")
  virtual const TCHAR*	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
  virtual const TCHAR*	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
  virtual const TCHAR*	AuthorName();				// ASCII Author name
  virtual const TCHAR*	CopyrightMessage();			// ASCII Copyright message
  virtual const TCHAR*	OtherMessage1();			// Other message #1
  virtual const TCHAR*	OtherMessage2();			// Other message #2
  virtual unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)

  virtual BOOL			SupportsOptions(int ext, DWORD options);

  //////////////////////////////////////////////////////////////////////////

  static CString		transformToSystem(CString str);
  static CString		transformToUTF8(CString str);

protected:
  void					_getPoint3Property(IGameProperty* prop, PN::pnfloat* point, const PN::pnfloat* def = _defaultVertex);
  float					_getFloatProperty(IGameProperty* prop, PN::pnfloat def = -1.0f);
};

//////////////////////////////////////////////////////////////////////////
};
