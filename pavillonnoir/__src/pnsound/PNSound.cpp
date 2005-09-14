/*
 * PNSound.cpp
 * 
 * Description :
 * PNSound and PNSoundManager definitions
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

#ifdef WIN32
# include <conio.h>
#endif

#include <sys/stat.h>
#include <math.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

#include "PNSound.hpp"
#define BUFFER_SIZE     32768
#define AL_FORMAT_VORBIS_EXT 0x10003



PNSound::PNSound(int new_ID)
{
  _id = new_ID;
  current_file = "DEFAULT";
}


PNSound::~PNSound()
{
  destroySound();
}


/*! Loads a wav sound file \"fname\" Boolean true defines if the sound is looping for ever or not (usefull for music) */
bool PNSound::loadSound(const pnchar *fname, char looping)
{
  ALboolean loop;
  if (looping)
	loop = AL_TRUE;
  else
	loop = AL_FALSE;;


  alGenSources(1, &_alSource);
  alGenBuffers(1, &_alSampleSet);

  loadOggFile(fname, _alBuffer, _alFormatBuffer, _alFreqBuffer);

  alBufferData(_alSampleSet, _alFormatBuffer, &_alBuffer[0], static_cast<ALsizei>(_alBuffer.size()), _alFreqBuffer);
  
  //////////////////////////////////////////////////////////////////////////
  //					   Old wav support
  //alutLoadWAVFile((ALbyte*)fname, &_alFormatBuffer, (void **) &_alBuffer,
  //(ALsizei*)&_alBufferLen, &_alFreqBuffer, &loop);
  //alBufferData(_alSampleSet, _alFormatBuffer, _alBuffer, _alBufferLen, _alFreqBuffer);
  //alutUnloadWAV(_alFormatBuffer, _alBuffer, _alBufferLen, _alFreqBuffer);	
  //////////////////////////////////////////////////////////////////////////

  alSourcei(_alSource, AL_BUFFER, _alSampleSet);

  //set le pitch
  alSourcef(_alSource,AL_PITCH,1.0f);
  //set le gain
  alSourcef(_alSource,AL_GAIN,1.0f);
  //set le looping
  alSourcei(_alSource, AL_LOOPING, loop);

  if (alGetError() != AL_NO_ERROR)
  {
	printf("OpenAl Error:\n");
	if (alGetError() == AL_INVALID_NAME)
	  printf("Invalid Name parameter\n");
	if (alGetError() == AL_INVALID_ENUM)
	  printf("Invalid enum \n");
	if (alGetError() == AL_INVALID_VALUE)
	  printf("Invalid parameter value\n");
	if (alGetError() == AL_INVALID_OPERATION)
	  printf("Illegal call\n");
	if (alGetError() == AL_OUT_OF_MEMORY)
	  printf("Unable to allocate memory\n");
	return false;	
  }
  return true; 
}


/*! Sets the position and speed of the sound */
void PNSound::setProperties(float x, float y, float z, float vx, float vy, float vz)
{
  alSource3f(_alSource,AL_POSITION,x,y,z);
  alSource3f(_alSource,AL_VELOCITY,vx,vy,vz);
}


/*! this function makes a sound source relative so all direction and velocity
parameters become relative to the source rather than the listener
useful for background music that you want to stay constant relative to the listener
no matter where they go */
void PNSound::setSourceRelative()
{
  alSourcei(_alSource,AL_SOURCE_RELATIVE,AL_TRUE);
  return;
}


/*! Plays a sound file */
void PNSound::playSound()
{
  alSourcePlay(_alSource);
  return;
}


/*! Stops a sound file */
void PNSound::stopSound()
{
  alSourceStop(_alSource);
  return;
}


/*! Pauses a sound file */
void PNSound::pauseSound()
{
  alSourcePause(_alSource);
  return;
}


/*! Changes sound volume */
void PNSound::changeSoundVolume(float value)
{
  alSourcef(_alSource, AL_GAIN, value);
  return;
}


/*! Destroys a sound */
void PNSound::destroySound()
{
  alDeleteSources(1,&_alSource);
  alDeleteBuffers(1,&_alSampleSet);
  return;
}


// This function loads a .ogg file into a memory buffer and returns
// the format and frequency.
void PNSound::loadOggFile(const pnchar *fileName, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
  int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
  int bitStream;
  long bytes;
  char array[BUFFER_SIZE];                // Local fixed size array
  FILE *f;

  // Open for binary reading
  f = fopen(fileName, "rb");

  if (f == NULL)
  {
	printf("Cannot open %s for reading...\n", fileName);
	return;
  }
  // end if

  vorbis_info *pInfo;
  OggVorbis_File oggFile;

  // Try opening the given file
  if (ov_open(f, &oggFile, NULL, 0) != 0)
  {
	printf("Error in %s for decoding...\n", fileName);
	return;
  }
  // end if

  // Get some information about the OGG file
  pInfo = ov_info(&oggFile, -1);

  // Check the number of channels... always use 16-bit samples
  if (pInfo->channels == 1)
	format = AL_FORMAT_MONO16;
  else
	format = AL_FORMAT_STEREO16;
  // end if

  // The frequency of the sampling rate
  freq = pInfo->rate;

  // Keep reading until all is read
  do
  {
	// Read up to a buffer's worth of decoded sound data
	bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

	if (bytes < 0)
	{
	  ov_clear(&oggFile);
	  printf("Error in %s while decoding...\n", fileName);
	  return;
	}
	// end if

	// Append to end of buffer
	buffer.insert(buffer.end(), array, array + bytes);
  }
  while (bytes > 0);

  // Clean up!
  ov_clear(&oggFile);
}
