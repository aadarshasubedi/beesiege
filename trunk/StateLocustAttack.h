#ifndef STATELOCUSTATTACK_H
#define STATELOCUSTATTACK_H

#include "FSMState.h"

class Enemy;
class GameCharacter;
class HealthAttribute;

class StateLocustAttack: public FSMState
{
public:

	// ctor
	StateLocustAttack(FSMAIControl* control, int type=FSM_ENEMY_LOCUST_ATTACK);

	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);
	
	// setters / getters
	void SetTarget(GameCharacter* target);
	
private:
	
	// the locust's target
	GameCharacter* m_pTarget;
	// the locust's view radius
	float m_fViewRadius;
	// the locust's damage radius
	float m_fDamageRadius;
	// the locust's damage modifier
	float m_fDamage;
	// the target's health attribute
	HealthAttribute* m_pTargetHealth;
	// timer for delaying attacks
	float m_fAttackTimer; 
	const float m_fcAttackTime;

	// damage target
	void DamageTarget();
	
};

NiSmartPointer(StateLocustAttack);

#endif
