#ifndef STATEFOLLOWQUEEN_H
#define STATEFOLLOWQUEEN_H

#include "FSMState.h"

class StateFollowQueen: public FSMState
{
public:
	// ctor
	StateFollowQueen(FSMAIControl* control, int type=FSM_FOLLOW_QUEEN) :
	  FSMState(control, type)
	  {}
	
	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

private:

	enum AIControlType
	{
		BEE_AI_CONTROL,
		HEALER_BEE_AI_CONTROL,
		HONEY_BEE_AI_CONTROL
	};

	AIControlType m_eType;
};

NiSmartPointer(StateFollowQueen);

#endif