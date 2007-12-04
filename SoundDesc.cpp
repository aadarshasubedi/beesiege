#include "SoundDesc.h"

//-------------------------------------------------------------------
SoundDesc::SoundDesc(const char* file, 
					 bool is3DSound, bool isLooping) :
						 filename(file),
						 mode(FMOD_HARDWARE),
					     dopplerscale(1.0f),
						 distancefactor(1.0f),
						 rolloffscale(1.0f),
						 is3D(is3DSound),
						 isLoop(isLooping)
{
	if (is3DSound)
	{
		mode = mode | FMOD_3D;
	}
	if (isLooping)
	{
		mode = mode | FMOD_LOOP_NORMAL;
	}

}
//-------------------------------------------------------------------
SoundDesc::~SoundDesc()
{
}
//-------------------------------------------------------------------