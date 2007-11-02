#ifndef STATEIDLE_H
#define STATEIDLE_H

#include "FSMState.h"
#include "FSMAIControl.h"

using namespace std;

class StateIdle: public FSMState
{
public:
	StateIdle(int type=FSM_IDLE)
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

NiSmartPointer(StateIdle);

#endif
