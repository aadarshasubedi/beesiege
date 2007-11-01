#ifndef FSMSTATE_H
#define FSMSTATE_H

#include "FSM.h"
#include "FSMAIControl.h"

using namespace std;

class FSMState
{
	
public:
	FSMState(int type=FSM_STATE_NONE)
	{ 
		m_type = type;
	}

	virtual void Enter();                 
	virtual void Exit();                  
	virtual void Update(int i);
	virtual void Init();
	virtual int CheckTransitions(int t);
	int m_type;
};

#endif
