#ifndef STATEPOWERUP_H
#define STATEPOWERUP_H

#include "FSMState.h"
#include "FSMQueenAIControl.h"

using namespace std;

class StatePowerUp: public FSMState
{
public:
	StatePowerUp(FSMAIControl* control,int type=FSM_POWERUP)
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

NiSmartPointer(StatePowerUp);


#endif