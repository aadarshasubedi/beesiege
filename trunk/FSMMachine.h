#ifndef FSMMACHINE_H
#define FSMMACHINE_H

#include "FSMState.h"
#include "GameObj.h"
#include <vector>

using namespace std;

class FSMMachine: public GameObj
{
public:

	FSMMachine();

	virtual ~FSMMachine();

	virtual void UpdateMachine(int t);
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

};

NiSmartPointer(FSMMachine);

#endif
	
	
