#ifndef FSMMACHINE_H
#define FSMMACHINE_H

#include "FSMState.h"
#include <vector>

using namespace std;

class FSMMachine
{
public:
	FSMMachine(int type = FSM_MACH_NONE)
	{
		m_type = type;
	}

	virtual void UpdateMachine(int i);
	virtual void AddState(FSMState* state);
	virtual void SetDefaultState(FSMState* state)
	{ 
		m_defaultState = state;
	}
	virtual void SetGoalID(int goal)
	{
		m_goalId = goal;
	}
	virtual bool TransitionState(int goal);
	virtual void Reset();

	int m_type;

	std::vector<FSMState*> m_states;
	FSMState* m_currentState;
	FSMState* m_defaultState;
	FSMState* m_goalState;
	int m_goalId;

};

#endif
	
	
