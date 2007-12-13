#ifndef STATEDRAGONFLYATTACK_H
#define STATEDRAGONFLYATTACK_H

#include "FSMState.h"

class Enemy;
class GameCharacter;
class HealthAttribute;

class StateDragonflyAttack: public FSMState
{
public:

	// ctor
	StateDragonflyAttack(FSMAIControl* control, int type=FSM_ENEMY_DRAGONFLY_ATTACK);

	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);
	
	// setters / getters
	void SetTarget(GameCharacter* target);
	
private:
	
	// the dragonfly's target
	GameCharacter* m_pTarget;
	// the dragonfly's view radius
	float m_fViewRadius;
	// the dragonfly's damage radius
	float m_fDamageRadius;
	// the dragonfly's damage modifier
	float m_fDamage;
	// the target's health attribute
	HealthAttribute* m_pTargetHealth;
	// timer for delaying attacks
	float m_fAttackTimer; 
	const float m_fcAttackTime;

	// damage target
	void DamageTarget();
	
};

NiSmartPointer(StateDragonflyAttack);

#endif
