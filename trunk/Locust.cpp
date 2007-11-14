/**
 * Enemy: Locust
 */

#include "Locust.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "FSMEnemyAIControl.h"
#include "HealthAttribute.h"

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
	FSMEnemyAIControl* controller = (FSMEnemyAIControl*)GetAttribute(GameCharacter::ATTR_CONTROLLER);
	if (controller)
	{
		controller->Update(fTime);	
	}
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

	AddAttribute(GameCharacter::ATTR_CONTROLLER, NiNew FSMEnemyAIControl(this));
	HealthAttribute* health = (HealthAttribute*)GetAttribute(GameCharacter::ATTR_HEALTH);
	if (health) health->Reset(50.0f);

	return true;
}