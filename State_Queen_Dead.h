#ifndef STATEQUEENDEAD_H
#define STATEQUEENDEAD_H

#include "FSMState.h"
#include "FSMQueenAIControl.h"

using namespace std;

class StateQueenDead: public FSMState
{
public:
	StateQueenDead(FSMAIControl* control, int type=FSM_QUEEN_DEAD) :
	  FSMState(control, type)
	{ 
	}

	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	FSMState* CheckTransitions(int t);

	int m_type;
	FSMAIControl* m_control;
};

NiSmartPointer(StateQueenDead);


#endif