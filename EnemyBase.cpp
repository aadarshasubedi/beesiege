/**
* An EnemyBase is like a house for enemies. It spawns
* enemies over time and in order to stop it (or destroy it)
* you have to kill its boss.
*/

#include "EnemyBase.h"
#include "GameManager.h"
#include "Locust.h"
#include "Dragonfly.h"
#include "Boss.h"
//-----------------------------------------------------------------------------
NiImplementRTTI(EnemyBase, GameObj3d);
//-----------------------------------------------------------------------------
/**
* Ctor
*/
EnemyBase::EnemyBase() : 
GameObj3d(ResourceManager::RES_MODEL_BASE),
m_fSpawnTimer(0.0f),
m_fSpawnTimerInitial(10.0f),
m_bSpawnedBoss(false),
m_bIsBossAlive(true),
m_uiSpawnedCount(0),
m_uicMaxSpawned(15),
m_uiSpawnedKilled(0),
m_uiMaxRemainingSpawned(14)
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
	m_spNode->SetTranslate(1000.0f, 250.0f, -200.0f);
	return true;
}
//------------------------------------------------------------------------ 
/** 
 * Spawns a new enemy  
 */
void EnemyBase::SpawnEnemy()
{
	if (m_uiSpawnedCount >= m_uicMaxSpawned)
		return;

	if (!m_bSpawnedBoss)
	{
		if (m_uiSpawnedKilled == 
			m_uicMaxSpawned - m_uiMaxRemainingSpawned)
		{
			BossPtr enemy = (Boss*)(GameObj3d*)GameManager::Get()->
			CreateObject3d(ResourceManager::RES_MODEL_BOSS);
			if (enemy)
			{
				NiPoint3 pos = m_spNode->GetTranslate();
				enemy->GetActor()->setGlobalPosition(NxVec3(pos.x, pos.y, pos.z));
				enemy->SetBase(this);
				m_bSpawnedBoss = true;
			}
		}
	}
	
	float dt = GameManager::Get()->GetDeltaTime();
	m_fSpawnTimer -= dt;
	if (m_fSpawnTimer <= 0.0f)
	{
		// reset timer
		m_fSpawnTimer = m_fSpawnTimerInitial;
		// spawn enemy
		if (rand()%100 > 50)
		{
			DragonFlyPtr enemy = (DragonFly*)(GameObj3d*)GameManager::Get()->
			CreateObject3d(ResourceManager::RES_MODEL_DRAGONFLY);
			if (enemy)
			{
				NiPoint3 pos = m_spNode->GetTranslate();
				enemy->GetActor()->setGlobalPosition(NxVec3(pos.x, pos.y, pos.z));
				enemy->SetBase(this);
				m_uiSpawnedCount++;
			}
		}
		else
		{
			LocustPtr enemy = (Locust*)(GameObj3d*)GameManager::Get()->
			CreateObject3d(ResourceManager::RES_MODEL_LOCUST);
			if (enemy)
			{
				NiPoint3 pos = m_spNode->GetTranslate();
				enemy->GetActor()->setGlobalPosition(NxVec3(pos.x, pos.y, pos.z));
				enemy->SetBase(this);
				m_uiSpawnedCount++;
			}
		}
	}
	
}
//------------------------------------------------------------------------ 
/** 
 * Resets enemy base 
 */
void EnemyBase::Reset()
{
	m_fSpawnTimer = 0.0f;
	m_bSpawnedBoss = false;
	m_bIsBossAlive = false;
	m_uiSpawnedCount = 0;
	m_uiSpawnedKilled = 0;
}