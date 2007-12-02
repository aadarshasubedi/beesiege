#ifndef STATEATTACKENEMY_H
#define STATEATTACKENEMY_H

#include "FSMState.h"

class Enemy;
class HealthAttribute;
class DamageAttribute;

class StateBeeAttackEnemy: public FSMState
{
public:
	// ctor
	StateBeeAttackEnemy(FSMAIControl* control, int type=FSM_ATTACK_ENEMY);
	
	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);

private:

	// the bee's target
	Enemy* m_pTarget;
	// the enemy's health
	HealthAttribute* m_pTargetHealth;
	// timer for delaying attacks
	float m_fAttackTimer; 
	const float m_fcAttackTime;
	// attack strength
	bool m_bIsAttackStrong;
	// the bee's damage attribute
	DamageAttribute* m_pOwnerDamage;
	// the bee's damage radius
	float m_fDamageRadius;

	// returns true if the target is in radius
	bool IsTargetInRadius(float radius);
	// randomly inflicts damage on the enemy
	void DamageTarget();
};

NiSmartPointer(StateAttackEnemy);

#endif
