#include "SoundDesc.h"

//-------------------------------------------------------------------
SoundDesc::SoundDesc(const char* file) : filename(file),
						 mode(FMOD_DEFAULT),
					     dopplerscale(1.0f),
						 distancefactor(1.0f),
						 rolloffscale(1.0f)
{
}
//-------------------------------------------------------------------
SoundDesc::~SoundDesc()
{
}
//-------------------------------------------------------------------