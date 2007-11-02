#ifndef FSMQUEENMACHINE_H
#define FSMQUEENMACHINE_H

#include "FSMMachine.h"
using namespace std;

class FSMQueenMachine: public FSMMachine
{
public:
	FSMQueenMachine(int type = FSM_MACH_QUEEN)
	{
		m_type = type;
	}

	void UpdateMachine(int i);
	void AddState(FSMState* state);
	void SetDefaultState(FSMState* state)
	{ 
		m_defaultState = state;
	}
	void SetGoalID(FSMState* state)
	{
		m_goalId = state;
	}
	bool TransitionState(FSMState* state);
	void Reset();

};

NiSmartPointer(FSMQueenMachine);

#endif