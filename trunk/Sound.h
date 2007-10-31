#ifndef SOUND_H_
#define SOUND_H_

#include <fmod.hpp>
#include "SoundDesc.h"

class NxVec3;

class Sound : public GameObj
{
	friend class SoundManager;

public:
	
	void Play();
	void Pause();
	void Resume();
	void Stop();
	void Update(const NxVec3& pos, const NxVec3& vel);
private:
	
	Sound(SoundDescPtr spDesc, FMOD::Sound* sound);
	~Sound();

	SoundDescPtr m_spDesc;
	FMOD::Sound* m_pFMODSound;
	FMOD::Channel* m_pFMODChannel;
};

NiSmartPointer(Sound);

#endif