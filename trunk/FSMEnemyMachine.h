#ifndef FSMENEMYMACHINE_H
#define FSMENEMYMACHINE_H

#include "FSMMachine.h"

using namespace std;

class FSMEnemyMachine: public FSMMachine
{
public:
	FSMEnemyMachine(int type = FSM_MACH_ENEMY)
	{
		m_type = type;
	}

	void UpdateMachine(int i);
	void AddState(FSMState* state);
	void SetDefaultState(FSMState* state)
	{ 
		m_defaultState = state;
	}
	void SetGoalID(int goal)
	{
		m_goalId = goal;
	}
	bool TransitionState(int goal);
	void Reset();

};

#endif
	