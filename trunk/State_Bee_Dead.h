#ifndef STATEBEEDEAD_H
#define STATEBEEDEAD_H

#include "FSMState.h"
#include "FSMBeeAIControl.h"

using namespace std;

class StateBeeDead: public FSMState
{
public:
	StateBeeDead(FSMAIControl* control, int type=FSM_BEE_DEAD)
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

NiSmartPointer(StateBeeDead);


#endif