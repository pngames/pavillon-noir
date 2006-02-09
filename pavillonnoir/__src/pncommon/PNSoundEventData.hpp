/*
 * PNGameEventData.hpp
 * 
 * Description :
 * PNGameEventData declarations/definitions
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

#ifndef _PNSOUNDEVENTDATA_HPP_
# define _PNSOUNDEVENTDATA_HPP_

#include "pndefs.h"
#include "pnevent.h"
#include "PNEventData.hpp"
#include <string>

namespace PN
{
//////////////////////////////////////////////////////////////////////////
  
class PNSoundEventData : public PNEventData
{
public:
	////////////////////////////////////

	PNSoundEventData(std::string sound_name, std::string file_name = "", char loop=false ,float x = 0, float y = 0, float z = 0, float volume = 1.0) 
	{
		px = x; 
		py = z; 
		pz = z; 
		name = sound_name; 
		fname= file_name;
		looping = loop;
		sound_volume = volume;
	}

	PNSoundEventData(std::string sound_name,  float volume)
	{
		name = sound_name; 
		sound_volume = volume;
	}
	
	////////////////////////////////////

	std::string name;	/// Sound name
	std::string fname;	///	Sound File name
	char	looping;		/// Sound looping or not ( TRUE | FALSE)
	float	px;			/// Sound pos x
	float	py;			/// Sound pos y
	float	pz;			/// Sound pos z
	float	sound_volume; // Sound volume
};



//////////////////////////////////////////////////////////////////////////
};

#endif /*_PNSOUNDEVENTDATA_HPP_*/

