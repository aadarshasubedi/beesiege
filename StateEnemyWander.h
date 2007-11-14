#ifndef STATEENEMYWANDER_H
#define STATEENEMYWANDER_H

#include "FSMState.h"

class Enemy;
class HealthAttribute;

class StateEnemyWander: public FSMState
{
public:
	StateEnemyWander(FSMAIControl* control, int type=FSM_ENEMY_WANDER) : 
	  FSMState(control, type)
	{
	}

	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);
private:
	
	HealthAttribute* m_pHealth;
};

NiSmartPointer(StateEnemyWander);

#endif
