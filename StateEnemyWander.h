#ifndef STATEENEMYWANDER_H
#define STATEENEMYWANDER_H

#include "FSMState.h"

class Enemy;
class HealthAttribute;

class StateEnemyWander: public FSMState
{
public:

	// ctor
	StateEnemyWander(FSMAIControl* control, int type=FSM_ENEMY_WANDER) : 
	  FSMState(control, type)
	{
	}

	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

private:
	// the enemy's health
	HealthAttribute* m_pHealth;
};

NiSmartPointer(StateEnemyWander);

#endif
