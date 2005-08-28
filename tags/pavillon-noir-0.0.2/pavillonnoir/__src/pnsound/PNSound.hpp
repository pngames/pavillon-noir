/*
 * PNSound.h
 * 
 * Description :
 * PNSound and PNSoundManager declarations
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

#ifndef _PNSOUND_HPP_
#define _PNSOUND_HPP_

#include <string>
#include <vector>
#include <AL/al.h>
#include <AL/alut.h>
#include "pndefs.h"

using namespace PN;

class PNSound
{
public:
	PNSound() {};
	PNSound(int new_ID);
	~PNSound();

	bool loadSound(const pnchar *fname, char looping);
	void loadOggFile(const pnchar *fileName, std::vector<char> &buffer, ALenum &format, ALsizei &freq);
	//void loadSoundFromFile(const pnchar* inSoundFile );
	
	void setProperties(float x, float y, float z, float vx, float vy, float vz);
	void setSourceRelative();
	
	void playSound();
	void stopSound();
	void pauseSound();
	void changeSoundVolume(float value);
	void destroySound();
	
	int	 getId() {return _id;};

	std::string		current_file;

private:
	int				_id;
	std::vector <char> _alBuffer;
	//char*			_alBuffer;
	ALenum			_alFormatBuffer;
	ALsizei			_alFreqBuffer;
	long			_alBufferLen;
	ALboolean		_alLoop;
	unsigned int	_alSource;
	unsigned int	_alSampleSet;
};

#endif
