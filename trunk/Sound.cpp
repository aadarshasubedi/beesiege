#include "Sound.h"
#include "SoundManager.h"
#include <NxVec3.h>

//-------------------------------------------------------------------
Sound::Sound(SoundDescPtr spDesc, FMOD::Sound* sound) : m_spDesc(spDesc), 																
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
void Sound::Update(const NxVec3& pos, const NxVec3& vel)
{
	FMOD_VECTOR p;
	p.x = pos.x;
	p.y = pos.y;
	p.z = pos.z;

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