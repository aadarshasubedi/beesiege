#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <fmod.hpp>
#include "SingletonObj.h"
#include <NxVec3.h>

class Sound;
NiSmartPointer(Sound);
class SoundDesc;
NiSmartPointer(SoundDesc);
class GameCharacter;

// Singleton Class
class SoundManager : public SingletonObj<SoundManager>
{
	// classes that need access to the private members
	// of the sound manager
	friend SingletonObj<SoundManager>;
	friend class ResourceManager;
public:

	// plays a sound
	FMOD::Channel* PlaySound(Sound* s);
	// resumes a sound at a given channel
	void ResumeSound(FMOD::Channel* ch);
	// pauses a sound at a given channel
	void PauseSound(FMOD::Channel* ch);
	// stops a sound at a given channel
	void StopSound(FMOD::Channel* ch);
	// default update
	void Update();
	// 3D sound update
	void Update(const NxVec3& listenerPos,
			    const NxVec3& listenerVel,
			    const NxVec3& listenerUp,
			    const NxVec3& listenerForward);

private:
	// private ctor / dtor
	SoundManager();
	~SoundManager();
	// initializes the manager (to be called by ResourceManager)
	bool Init();
	// creates a sound
	SoundPtr CreateSound(SoundDescPtr spDesc, GameCharacter* owner);
	// a static pointer to the FMOD sound system
	static FMOD::System* m_pSystem;
	// max channels
	const UINT m_uiMaxChannels;	
	// was the manager initialized
	bool m_bInitialized;

};

#endif