#ifndef STATEIDLE_H
#define STATEIDLE_H

#include "FSMState.h"
#include "FSMEnemyAIControl.h"

using namespace std;

class StateIdle: public FSMState
{
public:
	StateIdle(FSMAIControl* control, int type=FSM_IDLE) :
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

NiSmartPointer(StateIdle);

#endif
