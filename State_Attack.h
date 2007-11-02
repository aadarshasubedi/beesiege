#ifndef STATEATTACK_H
#define STATEATTACK_H

#include "FSMState.h"
#include "FSMAIControl.h"

using namespace std;

class StateAttack: public FSMState
{
public:
	StateAttack(int type=FSM_ATTACK)
	{ 
		m_type = type;
	}

	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	FSMState* CheckTransitions(int t);

	int m_type;
};

NiSmartPointer(StateAttack);

#endif

