/*
 * PNOpalObject.hpp
 * 
 * Description :
 * PNOpalObject
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

#ifndef _PNOPALOBJECT_HPP_
# define _PNOPALOBJECT_HPP_

#include <boost/filesystem/path.hpp>
#include <libxml/xmlreader.h>
#include <opal/opal.h>

#include "pndefs.h"
#include "pnmath.h"
#include "pnrender.h"

#include "PNPoint.hpp"
#include "PNQuatf.hpp"
#include "PNPhysicalObject.hpp"

namespace PN {

  namespace PNOPAL_XML_DEF {
	static const std::string	dataFilePath = "datafiles/";
	static const std::string	modelFilePath = dataFilePath + "models/";
	static const std::string	physicsFilePath = dataFilePath + "physics/";
	static const std::string	opalFilePath = physicsFilePath + "opal/";

	inline std::string			convertPath(const std::string& type, const std::string& path)
	{
	  std::string::size_type	  index = path.rfind(type);

	  if (index == std::string::npos)
		return path;

	  return path.c_str() + index + type.size();
	}
  }

  typedef enum {
	OPALBOX = 1,
	OPALSPHERE = 2
  }		  opaltypes;

  class PNOpalObject : public PNPhysicalObject
  {
  private:
	/* pnengine */
	std::string				  _file;
	PNPoint					  _coord;
	PNQuatf					  _orient;

	/* opal */
	opal::Blueprint				  _blueprint;
	opal::BlueprintInstance		  _blueprintInstance;
	opal::Solid*				  _solid;
	opal::Simulator*			  _sim;
	opal::Force					  _force;
	opal::SpringMotor*		  	  _movementMotor;
	opal::SpringMotorData		  _movementMotorData;
	opal::AccelerationSensor*	  _accelSensor;
	opal::AccelerationSensorData  _accelSensorData;

	/* deprecated trimeshes data (or not at all) */
	pnpoint3f*				  _vertBuffer;
	pnpoint2ui*				  _idBuffer;
	PNRendererObject*		  _robject;

	/* rendering previously deprecated */
	pnfloat					  _aabb[6];
	pndouble				  _radius;
	PNPoint					  _offset;
	opaltypes			  _type;

  public:
	PNOpalObject(opal::Simulator* sim);
	~PNOpalObject();

	//////////////////////////////////////////////////////////////////////////
	// PNPhysicalObject

	void				update(pnuint elapsed_time);
	void				render();

  	const PNPoint&		getCoord();
	const PNQuatf&		getOrient();
	const PNPoint&		getOffset();
	opal::Solid*		getOpalSolid();
	opal::AccelerationSensor* getAccelSensor();
	
	void				setStatic(bool state);
	bool				isStatic();
	void				setCoord(const PNPoint& coord);
	void				setCoord(pnfloat x, pnfloat y, pnfloat z);
	void				setOrient(const PNQuatf& orient);
	void				setOrient(pnfloat x, pnfloat y, pnfloat z, pnfloat w);
	void				setTransform(const PNPoint& coord, const PNQuatf& orient);

	void				addForce(pnfloat x, pnfloat y, pnfloat z, pnfloat duration);
	void				setMovementMotor(pnfloat x, pnfloat y, pnfloat z, PNQuatf orient);
	void				destroyMovementMotor();

	///////////////////////////////////////////////////////////////////////////
	// IPNXMLSerializable

  protected:
	pnint				_parseTypePnm(const boost::filesystem::path& file);
	pnint				_parseTypeOpal(const boost::filesystem::path& file);
	pnint				_parseModel(xmlNode* node);
	pnint				_unserializeNode(xmlNode* node);
	
  public:
	pnint				unserializeFromXML(xmlNode* node);
  };
}

#endif /*_PNOPALOBJECT_HPP_*/
