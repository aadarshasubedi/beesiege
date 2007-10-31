#ifndef SOUNDDESC_H_
#define SOUNDDESC_H_

#include <string>
#include <fmod.hpp>
#include "GameObj.h"

class SoundDesc : public GameObj
{
private:
public:
	SoundDesc(const char* file);
	~SoundDesc();

	std::string filename;
	FMOD_MODE mode;
	float dopplerscale;
	float distancefactor;
	float rolloffscale;
};

NiSmartPointer(SoundDesc);
#endif