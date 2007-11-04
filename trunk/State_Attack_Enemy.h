#ifndef STATEATTACKENEMY_H
#define STATEATTACKENEMY_H

#include "FSMState.h"
#include "FSMBeeAIControl.h"

using namespace std;

class StateAttackEnemy: public FSMState
{
public:
	StateAttackEnemy(FSMAIControl* control, int type=FSM_ATTACK_ENEMY)
	{ 
		m_type = type;
		m_control = control;
	}

	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	FSMState* CheckTransitions(int t);

	int m_type;
	FSMAIControl* m_control;
};

NiSmartPointer(StateAttackEnemy);

#endif
