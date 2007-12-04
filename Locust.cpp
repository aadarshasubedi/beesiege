/**
 * Enemy: Locust
 */

#include "Locust.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "FSMEnemyAIControl.h"
#include "HealthAttribute.h"
#include "ConfigurationManager.h"
#include "Sound.h"
//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(Locust, Enemy);
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Locust::Locust() : Enemy(ResourceManager::RES_MODEL_LOCUST)
					
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Locust::~Locust()
{

}
//------------------------------------------------------------------------ 
/** 
 * Does extra updates
 * 
 * @param fTime
 */
void Locust::DoExtraUpdates(float fTime)
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
bool Locust::DoExtraInits()
{
	if (!Enemy::DoExtraInits())
	{
		return false;
	}

	// add a controller
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMEnemyAIControl(this));
	// set initial health
	HealthAttribute* health = (HealthAttribute*)GetAttribute(GameCharacter::ATTR_HEALTH);
	if (health) health->Reset(ConfigurationManager::Get()->locust_initialHealth);

	m_fViewRadius = ConfigurationManager::Get()->locust_viewRadius;

	SoundPtr sound = ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_LOCUST, this);
	if (sound)
	{
		AddAttribute(GameCharacter::ATTR_SOUND_DEFAULT, (CharacterAttribute*)sound);
		sound->Play();
	}

	AddAttribute(GameCharacter::ATTR_SOUND_1, (CharacterAttribute*) ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_LOCUST_DYING, this));

	return true;
}