#ifndef FSMMACHINE_H
#define FSMMACHINE_H

#include "FSMState.h"
#include <vector>

using namespace std;

class FSMMachine: public GameObj
{
public:
	FSMMachine(int type = FSM_MACH_NONE)
	{
		m_type = type;
	}

	virtual void UpdateMachine(int t) = 0;
	virtual void AddState(FSMState* state) = 0;
	virtual void SetDefaultState(FSMState* state)
	{ 
		m_defaultState = state;
	}
	virtual void SetGoalID(FSMState* state)
	{
		m_goalId = state;
	}
	virtual bool TransitionState(FSMState* state);
	virtual void Reset() = 0;

	int m_type;

	std::vector<FSMState*> m_states;
	FSMState* m_currentState;
	FSMState* m_defaultState;
	FSMState* m_goalState;
	FSMState* m_goalId;

};

NiSmartPointer(FSMMachine);

#endif
	
	
