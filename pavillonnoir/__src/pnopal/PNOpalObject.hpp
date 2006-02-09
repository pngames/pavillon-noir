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

#include "PNPoint3f.hpp"
#include "PNQuatf.hpp"

#include "PNPhysicalObject.hpp"
#include "IPNXMLSerializable.hpp"

namespace PN {
//////////////////////////////////////////////////////////////////////////

namespace PNOPAL_XML_DEF {
//////////////////////////////////////////////////////////////////////////

static const std::string		dataFilePath = "datafiles/";
static const std::string		modelFilePath = dataFilePath + "models/";
static const std::string		physicsFilePath = dataFilePath + "physics/";
static const std::string		opalFilePath = physicsFilePath + "opal/";

inline std::string				convertPath(const std::string& type, const std::string& path)
{
  std::string::size_type		index = path.rfind(type);

  if (index == std::string::npos)
	return path;

  return path.c_str() + index + type.size();
}

//////////////////////////////////////////////////////////////////////////
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

typedef enum {
  OPALBOX = 1,
  OPALSPHERE = 2
}		  opaltypes;

class							PNOpalObject : public PNPhysicalObject, public IPNXMLSerializable
{
private:
  /* pnengine */
  std::string					_file;
  PNPoint3f						_coord;
  PNQuatf						_orient;

  /* opal */
  opal::Blueprint				_blueprint;
  opal::BlueprintInstance		_blueprintInstance;
  opal::Solid*					_solid;
  opal::Simulator*				_sim;
  opal::Force					_force;

  /* motor */
  opal::SpringMotor*		  	_movementMotor;
  opal::SpringMotorData			_movementMotorData;

  /* sensor */
  opal::RaycastSensor*			_playerSensor;
  opal::AccelerationSensor*		_accelSensor;
  opal::AccelerationSensorData	_accelSensorData;

  /* rendering previously deprecated */
  pnfloat						_aabb[6];
  pndouble						_radius;
  PNPoint3f						_offset;
  PNPoint3f						_renderOffset;

public:
  PNOpalObject(opal::Simulator* sim);
  ~PNOpalObject();

  //////////////////////////////////////////////////////////////////////////
  // PNPhysicalObject

  const PNPoint3f&				getCoord();
  const PNQuatf&				getOrient();
  const PNPoint3f&				getOffset();
  const PNPoint3f&				getRenderOffset();
  opal::Solid*					getOpalSolid();
  opal::AccelerationSensor*		getAccelSensor();

  void							render();
  void							update();
  bool							isStatic();
  void							setStatic(bool state);
  void							setTransform(const PNPoint3f& coord, const PNQuatf& orient, pnfloat scale);
  void							addForce(const PNVector3f& vec, pnfloat magnitude, pnfloat duration, pnbool isLocal);

  //////////////////////////////////////////////////////////////////////////
  // PNOpalObject specific

  void							addTorque(const PNVector3f& axis, pnfloat magnitude, pnfloat duration, pnbool isLocal);
  void							setMovementMotor(pnfloat x, pnfloat y, pnfloat z, PNQuatf orient);
  void							destroyMovementMotor();

  //////////////////////////////////////////////////////////////////////////
  // PNOpalObject specific (debug)

  void							printAccel();
  opal::RaycastSensor*			getPlayerSensor();

protected:
  void							_createMeshEntity();
  pnint							_parseTypePnm(const boost::filesystem::path& file);
  pnint							_parseTypeOpal(const boost::filesystem::path& file);
  pnint							_parsePhysics(xmlNode* node);

  ///////////////////////////////////////////////////////////////////////////
  // IPNXMLSerializable

protected:
  pnint							_unserializeNode(xmlNode* node);

public:
  std::string*					getFile();
  pnint							unserializeFromXML(xmlNode* node);
};
}

#endif /*_PNOPALOBJECT_HPP_*/
