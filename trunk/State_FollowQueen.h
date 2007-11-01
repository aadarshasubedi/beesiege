#ifndef STATEFOLLOWQUEEN_H
#define STATEFOLLOWQUEEN_H

#include "FSMState.h"
#include "FSMAIControl.h"

using namespace std;

class StateFollowQueen: public FSMState
{
public:
	StateFollowQueen(int type=FSM_FOLLOW_QUEEN)
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