#ifndef STATEQUEENWANDER_H
#define STATEQUEENWANDER_H

#include "FSMState.h"
#include "FSMBeeAIControl.h"

using namespace std;

class StateQueenWander: public FSMState
{
public:
	StateQueenWander(FSMAIControl* control, int type=FSM_QUEEN_WANDER)
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

NiSmartPointer(StateQueenWander);

#endif