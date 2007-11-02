/**
 * A game level. Contains enemies and other data
 */

#include "Level.h"
#include "GameManager.h"
//----------------------------------------------------------------------------- 
/** 
 * Ctor
 * 
 * @param name
 */
Level::Level(const char* name) : m_pName(name)
{
}
//----------------------------------------------------------------------------- 
/** 
 * Dtor
 * 
 */
Level::~Level()
{
	m_lEnemies.RemoveAll();
}
//----------------------------------------------------------------------------- 
/** 
 * Calls the GameManager to initilize an enemy and adds this 
 * enemy to its local enemy list as well as the object list of 
 * the GameManager 
 * 
 * @param enemy
 * @param pos
 * 
 * @return bool
 */
bool Level::AddEnemy(GameCharacterPtr enemy, const NxVec3& pos)
{
	// call GameManager to init the enemy
	bool bSuccess = GameManager::Get()->CreateEnemy(enemy);
	if (!bSuccess) return false;
	// set the position and target for the enemy
	enemy->GetAgent()->GetActor()->setGlobalPosition(pos);
	enemy->SetTempTargetPos(pos);
	// add the enemy to the enemy list
	m_lEnemies.AddTail(enemy);

	return true;
}
//-----------------------------------------------------------------------------