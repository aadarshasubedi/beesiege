/**
* An EnemyBase is like a house for enemies. It spawns
* enemies over time and in order to stop it (or destroy it)
* you have to kill its boss.
*/

#include "EnemyBase.h"
#include "GameManager.h"
#include "Locust.h"
//-----------------------------------------------------------------------------
NiImplementRTTI(EnemyBase, GameObj3d);
//-----------------------------------------------------------------------------
/**
* Ctor
*/
EnemyBase::EnemyBase() : 
GameObj3d(ResourceManager::RES_MODEL_BASE),
m_fSpawnTimer(0.0f),
m_fSpawnTimerInitial(10.0f)
{
}
//-----------------------------------------------------------------------------
/**
* Dtor
*/
EnemyBase::~EnemyBase()
{
}
//------------------------------------------------------------------------
/** 
 * Updates the enemy base
 * 
 * @param fTime
 */
void EnemyBase::DoExtraUpdates(float fTime)
{
	SpawnEnemy();
}
//------------------------------------------------------------------------ 
/** 
 * Initializes the base's attributes 
 * 
 * 
 * @return bool
 */
bool EnemyBase::DoExtraInits()
{
	m_spNode->SetTranslate(0.0f, 250.0f, -200.0f);
	return true;
}
//------------------------------------------------------------------------ 
/** 
 * Spawns a new enemy  
 */
void EnemyBase::SpawnEnemy()
{
	float dt = GameManager::Get()->GetDeltaTime();
	m_fSpawnTimer -= dt;
	if (m_fSpawnTimer <= 0.0f)
	{
		// reset timer
		m_fSpawnTimer = m_fSpawnTimerInitial;
		// spawn enemy
		LocustPtr enemy = (Locust*)(GameObj3d*)GameManager::Get()->
			CreateObject3d(ResourceManager::RES_MODEL_LOCUST);
		if (enemy)
		{
			NiPoint3 pos = m_spNode->GetTranslate();
			enemy->GetActor()->setGlobalPosition(NxVec3(pos.x, pos.y, pos.z));
		}
	}
}