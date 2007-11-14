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
bool Level::AddEnemy(EnemyPtr enemy, const NxVec3& pos)
{

	// call GameManager to init the enemy
	enemy = (Enemy*)(GameObj3d*)GameManager::Get()->CreateObject3d(enemy->GetType());
	if (!enemy) return false;
	// set the position for the enemy
	enemy->GetActor()->setGlobalPosition(pos);
	
	// add the enemy to the enemy list
	m_lEnemies.AddTail(enemy);

	return true;
}
//-----------------------------------------------------------------------------