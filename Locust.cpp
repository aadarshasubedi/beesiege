/**
 * Enemy: Locust
 */

#include "Locust.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "FSMEnemyAIControl.h"
#include "HealthAttribute.h"
#include "ConfigurationManager.h"

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

	return true;
}