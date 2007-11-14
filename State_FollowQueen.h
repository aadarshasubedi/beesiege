#ifndef STATEFOLLOWQUEEN_H
#define STATEFOLLOWQUEEN_H

#include "FSMState.h"

class StateFollowQueen: public FSMState
{
public:
	StateFollowQueen(FSMAIControl* control, int type=FSM_FOLLOW_QUEEN) :
	  FSMState(control, type)
	  {}
	
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);
};

NiSmartPointer(StateFollowQueen);

#endif