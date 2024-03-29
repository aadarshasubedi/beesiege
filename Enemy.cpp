/**
 * Enemies 
 */

#include "Enemy.h"
#include "HealthAttribute.h"
#include "GameManager.h"
//----------------------------------------------------------------------
// implements RTTI
NiImplementRTTI(Enemy, GameCharacter);
//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Enemy::Enemy(ResourceManager::ResourceType type) :
GameCharacter(type), m_bIsAttackStrong(false), m_fViewRadius(0.0f),
m_bIsBaseAlive(true),m_pBase(0)
					
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Enemy::~Enemy()
{
	m_lAttackers.RemoveAll();
	m_lAttackerAgents.RemoveAll();
	GameManager::Get()->ResetAgentGroup();
}
//------------------------------------------------------------------------ 
/** 
 * Do extra updates
 */
void Enemy::DoExtraUpdates(float fTime)
{
	GameCharacter::DoExtraUpdates(fTime);
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