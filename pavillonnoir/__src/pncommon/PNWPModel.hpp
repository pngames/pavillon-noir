/*
 * PNWPModel.hpp
 * 
 * Description :
 * PNWPModel declaration
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

#ifndef _PNWPMODEL_HPP_
# define _PNWPMODEL_HPP_

#include <string>

#include "PN3DModel.hpp"
#include "pnmath.h"

#include "PNPoint3f.hpp"

namespace PN
{
//////////////////////////////////////////////////////////////////////////

class PNAPI					PNWPModel : public PN3DModel
{
private:
  static PNWPModel*			_instance;

  pnpoint4f					_selectcolor;
  pnpoint4f					_dflcolor;
  pnfloat*					_color;

  PNPoint3f					_min;
  PNPoint3f					_max;
  PNPoint3f					_center;

  PNWPModel(void);
  ~PNWPModel(void);

public:
  static PNWPModel*			getInstance();

  std::string*				getFile();

  void						render(std::vector<PN3DMaterial*>* mat, PN3DSkeleton* sk = NULL);
  
  void						renderLink(const PNPoint3f&p1, const PNPoint3f&p2, const pnfloat* color,
								pnuint direction = 0, pnfloat thickness = 1);

  void						setSlctColor();
  void						setDflColor();

  //////////////////////////////////////////////////////////////////////////

  pnuint					getNbSupportedBones() const {return 0;}
  pnuint					getNbSupportedMaterials() const {return 0;}

  pnuint					getNbVerts() const {return 400;}
  pnuint					getNbFaces() const {return 400;}

  //////////////////////////////////////////////////////////////////////////

  pnuint					getNbVertexComputed() {return 0;};

  pnuint					computeVertex(pnfloat* buffer, pnuint step = 0) {return 0;}
  pnuint					computeNormales(pnfloat* buffer, pnuint step = 0) {return 0;}
  pnuint					computeTextCoord(pnfloat* buffer, pnuint step = 0) {return 0;}
  pnuint					computeColors(pnfloat* buffer, pnuint step = 0) {return 0;}

  pnuint					getNbFacesComputed() {return 0;}

  pnuint					computeFaces(std::vector<PN3DMaterial*>& mat, PNFace* faces, pnuint step = 0) {return 0;}

  //////////////////////////////////////////////////////////////////////////

  const PNPoint3f&			getMin() const {return _min;}
  const PNPoint3f&			getMax() const {return _max;}
  const PNPoint3f&			getCenter() const {return _center;}
  pnfloat					getRadius() const {return -1;}
};

//////////////////////////////////////////////////////////////////////////
};
#endif /* !_PNWPMODEL_HPP_ */

