#ifndef STATEDEAD_H
#define STATEDEAD_H

#include "FSMState.h"
#include "FSMAIControl.h"

using namespace std;

class StateDead: public FSMState
{
public:
	StateDead(int type=FSM_DEAD)
	{ 
		m_type = type;
	}

	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	int CheckTransitions(int t);

	int m_type;
};


#endif
