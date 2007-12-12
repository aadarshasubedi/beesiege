/**
 * Enemy: DragonFly
 */

#include "DragonFly.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "FSMEnemyAIControl.h"
#include "HealthAttribute.h"
#include "ConfigurationManager.h"
#include "Sound.h"
//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(DragonFly, Enemy);
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
DragonFly::DragonFly() : Enemy(ResourceManager::RES_MODEL_DRAGONFLY)
					
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
DragonFly::~DragonFly()
{

}
//------------------------------------------------------------------------ 
/** 
 * Does extra updates
 * 
 * @param fTime
 */
void DragonFly::DoExtraUpdates(float fTime)
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
bool DragonFly::DoExtraInits()
{
	if (!Enemy::DoExtraInits())
	{
		return false;
	}

	// add a controller
	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMEnemyAIControl(this));
	// set initial health
	HealthAttribute* health = (HealthAttribute*)GetAttribute(GameCharacter::ATTR_HEALTH);
	if (health) health->Reset(ConfigurationManager::Get()->dragonfly_initialHealth);

	m_fViewRadius = ConfigurationManager::Get()->dragonfly_viewRadius;

	SoundPtr sound = ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_LOCUST, this);
	if (sound)
	{
		AddAttribute(GameCharacter::ATTR_SOUND_DEFAULT, (CharacterAttribute*)sound);
		sound->Play();
	}

	AddAttribute(GameCharacter::ATTR_SOUND_1, (CharacterAttribute*) ResourceManager::Get()->GetSound(
		ResourceManager::RES_SOUND_LOCUST_DYING, this));

	m_pActor->setLinearDamping(5.0f);
	m_pActor->setAngularDamping(5.0f);

	return true;
}