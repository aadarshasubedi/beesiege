#ifndef FSMBEEMACHINE_H
#define FSMBEEMACHINE_H

#include "FSMMachine.h"

using namespace std;

class FSMBeeMachine: public FSMMachine
{
public:
	FSMBeeMachine(int type = FSM_MACH_BEE)
	{
		m_type = type;
	}

	void UpdateMachine(int i);
	void SetDefaultState(FSMState* state)
	{ 
		m_defaultState = state;
	}
	void SetGoalID(FSMState* state)
	{
		m_goalState = state;
	}
	bool TransitionState(FSMState* state);

};

NiSmartPointer(FSMBeeMachine);

#endif
	