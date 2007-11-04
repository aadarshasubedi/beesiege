#ifndef STATEDEAD_H
#define STATEDEAD_H

#include "FSMState.h"
#include "FSMAIControl.h"

using namespace std;

class StateDead: public FSMState
{
public:
	StateDead(FSMAIControl* control, int type=FSM_DEAD)
	{ 
		m_type = type;
		m_control = control;
	}

	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	FSMState* CheckTransitions(int t);

	int m_type;
	FSMAIControl* m_control;
};

NiSmartPointer(StateDead);


#endif
