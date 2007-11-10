#ifndef STATEFOLLOWQUEEN_H
#define STATEFOLLOWQUEEN_H

#include "FSMState.h"
#include "FSMBeeAIControl.h"

using namespace std;

class StateFollowQueen: public FSMState
{
public:
	StateFollowQueen(FSMAIControl* control, int type=FSM_FOLLOW_QUEEN) :
	  FSMState(control, type)
	  {}
	
	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	FSMState* CheckTransitions(int t);
};

NiSmartPointer(StateFollowQueen);

#endif