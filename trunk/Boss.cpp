/**
 * Enemy: Boss
 */

#include "Boss.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "FSMEnemyAIControl.h"
#include "HealthAttribute.h"
#include "ConfigurationManager.h"
#include "Sound.h"
//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(Boss, Enemy);
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Boss::Boss() : Enemy(ResourceManager::RES_MODEL_BOSS)
					
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Boss::~Boss()
{
	int a=1;
}
//------------------------------------------------------------------------ 
/** 
 * Does extra updates
 * 
 * @param fTime
 */
void Boss::DoExtraUpdates(float fTime)
{
	Enemy::DoExtraUpdates(fTime);
}
//------------------------------------------------------------------------ 
/** 
 * Does extra initializations
 * 
 * 
 * @return bool
 */
bool Boss::DoExtraInits()
{
	if (!Enemy::DoExtraInits())
	{
		return false;
	}

	m_fViewRadius = ConfigurationManager::Get()->boss_viewRadius;

	// add a controller
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMEnemyAIControl(this));
	// set initial health
	HealthAttribute* health = (HealthAttribute*)GetAttribute(GameCharacter::ATTR_HEALTH);
	m_fMaxHealth = ConfigurationManager::Get()->boss_initialHealth;
	if (health)
		health->Reset(m_fMaxHealth);
	
	SoundPtr sound = ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_LOCUST, this);
	if (sound)
	{
		AddAttribute(GameCharacter::ATTR_SOUND_DEFAULT, (CharacterAttribute*)sound);
		sound->Play();
	}

	AddAttribute(GameCharacter::ATTR_SOUND_1, (CharacterAttribute*) ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_LOCUST_DYING, this));

	m_pActor->setLinearDamping(8.0f);
	m_pActor->setAngularDamping(8.0f);

	return true;
}