#ifndef STATELOCUSTATTACK_H
#define STATELOCUSTATTACK_H

#include "FSMState.h"

class Enemy;
class GameCharacter;

class StateLocustAttack: public FSMState
{
public:

	// ctor
	StateLocustAttack(FSMAIControl* control, int type=FSM_ENEMY_LOCUST_ATTACK) : 
	  FSMState(control, type), m_pTarget(0)
	{
	}

	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);
	
	// setters / getters
	void SetTarget(GameCharacter* target)
	{
		m_pTarget = target;
	}
private:
	
	GameCharacter* m_pTarget;
	
};

NiSmartPointer(StateLocustAttack);

#endif
