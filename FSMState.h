#ifndef FSMSTATE_H
#define FSMSTATE_H

#include "FSM.h"
#include "FSMAIControl.h"

using namespace std;

class FSMState: public GameObj
{
	
public:
	FSMState() {}
	FSMState(FSMAIControl* control, int type=FSM_STATE_NONE)
	{ 
		m_type = type;
		m_control = control;
	}

	virtual void Enter();                 
	virtual void Exit();                  
	virtual void Update(int t);
	virtual void Init();
	virtual FSMState* CheckTransitions(int t);
	int m_type;
	FSMAIControl* m_control;
};

NiSmartPointer(FSMState);

#endif