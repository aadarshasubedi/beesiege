#ifndef FSMMACHINE_H
#define FSMMACHINE_H

#include "FSMState.h"
#include <vector>

using namespace std;

class FSMMachine: public FSMState
{
public:
	FSMMachine(int type = FSM_MACH_NONE)
	{
		m_type = type;
	}

	virtual void UpdateMachine(int t) = 0;
	void AddState(FSMState* state);
	virtual void SetDefaultState(FSMState* state)
	{ 
		m_defaultState = state;
	}
	virtual void SetGoalID(FSMState* state)
	{
		m_goalState = state;
	}
	virtual bool TransitionState(FSMState* state);
	void Reset();
	FSMState* GetState(int stateId);

	int m_type;

	std::vector<FSMState*> m_states;
	FSMState* m_currentState;
	FSMState* m_defaultState;
	FSMState* m_goalState;
	//FSMState* m_goalState;

};

NiSmartPointer(FSMMachine);

#endif
	
	
