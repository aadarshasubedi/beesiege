#ifndef STATEENEMYWANDER_H
#define STATEENEMYWANDER_H

#include "FSMState.h"

class Enemy;

class StateEnemyWander: public FSMState
{
public:

	// ctor
	StateEnemyWander(FSMAIControl* control, int type=FSM_ENEMY_WANDER);

	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

private:

	enum AIControlType
	{
		LOCUST_AI_CONTROL,
		DRAGONFLY_AI_CONTROL,
		BOSS_AI_CONTROL
	};

	AIControlType m_eType;
	// the enemy's view radius
	float m_fViewRadius;

	

};

NiSmartPointer(StateEnemyWander);

#endif
