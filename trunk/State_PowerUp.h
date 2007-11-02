#ifndef STATEPOWERUP_H
#define STATEPOWERUP_H

#include "FSMState.h"
#include "FSMAIControl.h"

using namespace std;

class StatePowerUp: public FSMState
{
public:
	StatePowerUp(int type=FSM_POWERUP)
	{ 
		m_type = type;
	}

	void Enter();
	void Exit();
	void Update(int i);
	void Init();
	FSMState* CheckTransitions(int t);

	int m_type;
};

NiSmartPointer(StatePowerUp);


#endif