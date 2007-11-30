#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "GameObj3d.h"

class EnemyBase : public GameObj3d
{
	NiDeclareRTTI;

public:

	EnemyBase();
	virtual ~EnemyBase();

protected:

	float m_fSpawnTimer;
	float m_fSpawnTimerInitial;

	// extra updates and initializations
	virtual void DoExtraUpdates(float fTime);
	virtual bool DoExtraInits();

	void SpawnEnemy();
};

NiSmartPointer(EnemyBase);

#endif