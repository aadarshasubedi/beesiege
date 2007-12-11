#include "Sound.h"
#include "SoundManager.h"
#include "GameCharacter.h"
#include <NxVec3.h>


//-------------------------------------------------------------------
NiImplementRTTI(Sound,CharacterAttribute);
//-------------------------------------------------------------------
Sound::Sound(GameCharacter *owner, 
			 SoundDescPtr spDesc, 
			 FMOD::Sound* sound) : CharacterAttribute(owner),
								   m_spDesc(spDesc), 																
								   m_pFMODSound(sound),
								   m_pFMODChannel(0)
{
}
//-------------------------------------------------------------------
Sound::~Sound()
{
	m_spDesc = 0;
}
//-------------------------------------------------------------------
void Sound::Play()
{
	m_pFMODChannel = SoundManager::Get()->PlaySound(this);
}
//-------------------------------------------------------------------
void Sound::Pause()
{
	SoundManager::Get()->PauseSound(m_pFMODChannel);
}
//-------------------------------------------------------------------
void Sound::Resume()
{
	SoundManager::Get()->ResumeSound(m_pFMODChannel);
}
//-------------------------------------------------------------------
void Sound::Stop()
{
	SoundManager::Get()->StopSound(m_pFMODChannel);
}
//-------------------------------------------------------------------
void Sound::Update(float fTime)
{
	if (!m_spDesc->is3D) return;

 	NxActor* actor = GetOwner()->GetActor();
	if (!actor) return;

	NxVec3 pos = actor->getGlobalPosition() / 50.0f;
	FMOD_VECTOR p;
	p.x = pos.x;
	p.y = pos.y;
	p.z = pos.z;

	NxVec3 vel = actor->getLinearVelocity() / 50.0f;
	FMOD_VECTOR v;
	v.x = vel.x;
	v.y = vel.y;
	v.z = vel.z;
	if (m_pFMODChannel)
	{
		m_pFMODChannel->set3DAttributes(&p, &v);
	}
}
//-------------------------------------------------------------------