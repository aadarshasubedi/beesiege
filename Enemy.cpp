/**
 * Enemies 
 */

#include "Enemy.h"
#include "HealthAttribute.h"

//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(Enemy, GameCharacter);
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Enemy::Enemy(ResourceManager::ResourceType type) : GameCharacter(type)
					
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Enemy::~Enemy()
{

}

//------------------------------------------------------------------------ 
/** 
 * Does extra initializations
 * 
 * 
 * @return bool
 */
bool Enemy::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}
	
	// add a health attribute
	AddAttribute(GameCharacter::ATTR_HEALTH, NiNew HealthAttribute(this));
	return true;
}