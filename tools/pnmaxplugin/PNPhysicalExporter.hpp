/*
* PNPhysicalExporter.hpp
* 
* Description :
* PNPhysicalExporter definition
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

#ifndef _PNPHYSICALEXPORTER_HPP_
# define _PNPHYSICALEXPORTER_HPP_

#ifdef _DEBUG
# define PNPHYSICALEXPORTER_CLASS_ID	Class_ID(0x719343da, 0x12a61c0c)
# define PNP_LONGDESC					"Physical exporter for Pavillon Noir 3D objects (debug)"
# define PNP_SHORTDESC					"Pavillon Noir Physical export (debug)"
#else
# define PNPHYSICALEXPORTER_CLASS_ID	Class_ID(0x655f206b, 0x1aea57b6)
# define PNP_LONGDESC					"Physical exporter for Pavillon Noir 3D objects"
# define PNP_SHORTDESC					"Pavillon Noir Physical export"
#endif

#include "PNExporter.hpp"

#include "pnp_format.h"

//////////////////////////////////////////////////////////////////////////

class				PNPhysicalExporter : public PNExporter
{
public:
	static HWND		hParams;

	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

	//Constructor/Destructor
	PNPhysicalExporter();
	~PNPhysicalExporter();
	//////////////////////////////////////////////////////////////////////////
public:
	virtual int		initExport();
	virtual int		initFiles(CString file);
	virtual int		export(CString path);

	virtual int		releaseExport();

	virtual int		exportHeader();
	virtual int		exportBody();

	virtual int		configure();
};

class				PNPhysicalExporterDesc : public ClassDesc2
{
	HINSTANCE		_hInstance;
public:
	void			SetInstance(HINSTANCE hInstance);
public:
	int 			IsPublic();
	void *			Create(BOOL loading = FALSE);
	const TCHAR *	ClassName();
	SClass_ID		SuperClassID();
	Class_ID		ClassID();
	const TCHAR* 	Category();

	const TCHAR*	InternalName();	// returns fixed parsable name (scripter-visible name)
	HINSTANCE		HInstance(); // returns owning module handle
};

#endif /*_PNPHYSICALEXPORTER_HPP_*/
