#ifndef STATEATTACKBEE_H
#define STATEATTACKBEE_H

#include "FSMState.h"
#include "FSMEnemyAIControl.h"

using namespace std;

class StateAttackBee: public FSMState
{
public:
	StateAttackBee(FSMAIControl* control, int type=FSM_ATTACK_BEE) :
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

NiSmartPointer(StateAttackBee);

#endif
