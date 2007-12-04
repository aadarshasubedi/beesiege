/**
 * Creates and plays sounds, using FMOD. Singleton class.
 */
#include "SoundDesc.h"
#include "Sound.h"
#include "SoundManager.h"
#include "GameCharacter.h"
using namespace std;

//---------------------------------------------------------------------------------- 
/** 
 * Initialize FMOD system to zero
 * 
 */
FMOD::System* SoundManager::m_pSystem = 0;
//---------------------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 */
SoundManager::SoundManager() : m_uiMaxChannels(1000), 
					   m_bInitialized(false)
{
}
//---------------------------------------------------------------------------------- 
/** 
 * Dtor
 * 
 */
SoundManager::~SoundManager()
{
	m_pSystem->release();
	m_pSystem = 0;
}
//---------------------------------------------------------------------------------- 
/** 
 * Initializes the manager
 * 
 * 
 * @return bool
 */
bool SoundManager::Init()
{
	// Create the main system object.
	FMOD_RESULT result = FMOD::System_Create(&m_pSystem);		
	if (result != FMOD_OK)
	{
		NiMessageBox("FMOD Error Create System", "Error");
		return false;
	}

	// Initialize FMOD.
	result = m_pSystem->init(m_uiMaxChannels, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);	
	
	if (result != FMOD_OK)
	{
		NiMessageBox("FMOD Error Init", "Error");
		return false;
		return false;
	}
	
	m_bInitialized = true;
	return true;
}
//---------------------------------------------------------------------------------- 
/** 
 * Updates FMOD
 * 
 */
void SoundManager::Update()
{
	if (!m_bInitialized) return;
	m_pSystem->update();
}
//---------------------------------------------------------------------------------- 
/** 
 * Updates FMOD and 3d listener attributes
 * 
 * @param listenerPos
 * @param listenerVel
 * @param listenerUp
 * @param listenerForward
 */
void SoundManager::Update(const NxVec3& listenerPos,
					  const NxVec3& listenerVel,
					  const NxVec3& listenerUp,
					  const NxVec3& listenerForward)
{
	if (!m_bInitialized) return;

	FMOD_VECTOR pos;
	pos.x = listenerPos.x; pos.y = listenerPos.y; pos.z = listenerPos.z;
	FMOD_VECTOR vel;
	vel.x = listenerVel.x; vel.y = listenerVel.y; vel.z = listenerVel.z;
	FMOD_VECTOR up;
	up.x = listenerUp.x; up.y = listenerUp.y; up.z = listenerUp.z;
	FMOD_VECTOR forw;
	forw.x = listenerForward.x; forw.y = listenerForward.y; forw.z = listenerForward.z;
	m_pSystem->set3DListenerAttributes(0, &pos, &vel, &forw, &up);
	m_pSystem->update();
}
//---------------------------------------------------------------------------------- 
/** 
 * Creates a sound
 * 
 * @param spDesc
 * 
 * @return Sound*
 */
SoundPtr SoundManager::CreateSound(SoundDescPtr spDesc, GameCharacter* owner)
{
	if (!m_bInitialized) return 0;
	
	FMOD::Sound *fmodSound;
	FMOD_RESULT result = m_pSystem->createStream(spDesc->filename.c_str(), spDesc->mode, 0, &fmodSound);
	if (result != FMOD_OK)
	{
		string err("FMOD Error Creating Sound: " + spDesc->filename);
		NiMessageBox(err.c_str(), "Error");
		return 0;
	}

	SoundPtr sound = NiNew Sound(owner, spDesc, fmodSound);
	return sound;
}
//---------------------------------------------------------------------------------- 
/** 
 * Plays a sound
 * 
 * @param s: the sound
 * 
 * @return FMOD::Channel*
 */
FMOD::Channel* SoundManager::PlaySound(Sound* s)
{
	if (!m_bInitialized) return 0;
	FMOD::Channel* channel;
	FMOD_RESULT result = m_pSystem->playSound(FMOD_CHANNEL_FREE, s->m_pFMODSound, false, &channel);
	
	if (result != FMOD_OK)
	{
		string err("FMOD Error Playing Sound");
		NiMessageBox(err.c_str(), "Error");
		return 0;
	}
	return channel;

	return 0;
}
//---------------------------------------------------------------------------------- 
/** 
 * Resumes a sound
 * 
 * @param channel: the channel
 */
void SoundManager::ResumeSound(FMOD::Channel* ch)
{
	if (!m_bInitialized) return;
	if (ch)
	{
		ch->setPaused(false);
	}
}
//----------------------------------------------------------------------------------
/** Pauses a sound 
 * 
 * @param channel: the channel
 */
void SoundManager::PauseSound(FMOD::Channel* ch)
{
	if (!m_bInitialized) return;
	if (ch)
	{
		ch->setPaused(true);
	}
	
}
//----------------------------------------------------------------------------------
/** Stops a sound 
 * 
 * @param channel: the channel
 */
void SoundManager::StopSound(FMOD::Channel* ch)
{
	if (!m_bInitialized) return;
	if (ch)
	{
		ch->stop();
	}
}