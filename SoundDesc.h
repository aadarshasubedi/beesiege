#ifndef SOUNDDESC_H_
#define SOUNDDESC_H_

#include <string>
#include <fmod.hpp>
#include "GameObj.h"

class SoundDesc : public GameObj
{

public:
	// ctor / dtor
	SoundDesc(const char* file);
	~SoundDesc();

	// the filename of the sound
	std::string filename;
	// FMOD settings
	FMOD_MODE mode;
	float dopplerscale;
	float distancefactor;
	float rolloffscale;
};

NiSmartPointer(SoundDesc);
#endif