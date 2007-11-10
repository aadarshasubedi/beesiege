#ifndef FSMSTATE_H
#define FSMSTATE_H

#include "FSM.h"
#include "GameObj.h"

class FSMAIControl;

class FSMState: public GameObj
{
	
public:
	FSMState(FSMAIControl* control, int type=FSM_STATE_NONE);
	virtual ~FSMState();
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