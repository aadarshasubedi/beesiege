#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <fmod.hpp>
#include "SingletonObj.h"
#include <NxVec3.h>

class Sound;
NiSmartPointer(Sound);
class SoundDesc;
NiSmartPointer(SoundDesc);

class SoundManager : public SingletonObj<SoundManager>
{
	friend SingletonObj<SoundManager>;
	friend class ResourceManager;
public:

	FMOD::Channel* PlaySound(Sound* s);
	void ResumeSound(FMOD::Channel* ch);
	void PauseSound(FMOD::Channel* ch);
	void StopSound(FMOD::Channel* ch);

	void Update();
	void Update(const NxVec3& listenerPos,
			    const NxVec3& listenerVel,
			    const NxVec3& listenerUp,
			    const NxVec3& listenerForward);

private:

	SoundManager();
	~SoundManager();
	bool Init();
	
	Sound* CreateSound(SoundDescPtr spDesc);

	static FMOD::System* m_pSystem;
	const UINT m_uiMaxChannels;	
	bool m_bInitialized;

};

#endif