#ifndef STATEENEMYDEAD_H
#define STATEENEMYDEAD_H

#include "FSMState.h"
#include "FSMEnemyAIControl.h"

using namespace std;

class StateEnemyDead: public FSMState
{
public:
	StateEnemyDead(FSMAIControl* control, int type=FSM_ENEMY_DEAD) :
	  FSMState(control, type)
	{ 
	}

	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	FSMState* CheckTransitions(int t);

	int m_type;
	FSMAIControl* m_control;
};

NiSmartPointer(StateEnemyDead);


#endif