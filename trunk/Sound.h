#ifndef SOUND_H_
#define SOUND_H_

#include <fmod.hpp>
#include "SoundDesc.h"
#include "CharacterAttribute.h"

class NxVec3;
class GameCharacter;

class Sound : public CharacterAttribute
{
	friend class SoundManager;
	NiDeclareRTTI;
public:

	// plays sound
	void Play();
	// pauses sound
	void Pause();
	// resumes sound
	void Resume();
	// stops sound
	void Stop();
	// updates the sound's 3d attributes
	void Update(float fTime);
private:
	// private Ctor / Dtor (to be used by SoundManager)
	Sound(GameCharacter *owner, 
			 SoundDescPtr spDesc, 
			 FMOD::Sound* sound);
	~Sound();
	// sound descriptor
	SoundDescPtr m_spDesc;
	// FMOD sound pointer
	FMOD::Sound* m_pFMODSound;
	// FMOD channel pointer
	FMOD::Channel* m_pFMODChannel;
};

NiSmartPointer(Sound);

#endif