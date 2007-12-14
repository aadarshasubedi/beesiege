#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "GameObj3d.h"

class EnemyBase : public GameObj3d
{
	NiDeclareRTTI;

public:

	EnemyBase();
	virtual ~EnemyBase();

	void SetBossAlive (bool value);

	const bool IsBossAlive() const
	{
		return m_bIsBossAlive;
	}

	const unsigned int GetSpawnedCount() const
	{
		return m_uiSpawnedCount;
	}

	void IncreaseKilled()
	{
		m_uiSpawnedKilled++;
	}

	void Reset();

protected:

	float m_fSpawnTimer;
	float m_fSpawnTimerInitial;

	// did we spawn the boss yet
	bool m_bSpawnedBoss;
	// is the enemy's boss alive
	bool m_bIsBossAlive;
	// how many enemies did we spawn
	unsigned int m_uiSpawnedCount;
	// max enemies to be spawned
	const unsigned int m_uicMaxSpawned;
	// count of spawned enemies that were kiiled
	unsigned int m_uiSpawnedKilled;
	// count of enemies remaining for boss to come out
	const unsigned int m_uiMaxRemainingSpawned;

	// extra updates and initializations
	virtual void DoExtraUpdates(float fTime);
	virtual bool DoExtraInits();

	void SpawnEnemy();
};

NiSmartPointer(EnemyBase);

#endif