#ifndef STATEBOSSATTACK_H
#define STATEBOSSATTACK_H

#include "FSMState.h"

class Enemy;
class GameCharacter;
class HealthAttribute;

class StateBossAttack: public FSMState
{
public:

	// ctor
	StateBossAttack(FSMAIControl* control, int type=FSM_ENEMY_BOSS_ATTACK);

	// see base class
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);
	
	// setters / getters
	void SetTarget(GameCharacter* target);
	
private:
	
	enum AttackCycle
	{
		ATTACK_BEE,
		ATTACK_QUEEN,
		ATTACK_RETREAT
	};

	// the boss' target
	GameCharacter* m_pTarget;
	// the boss' view radius
	float m_fViewRadius;
	// the boss' damage radius
	float m_fDamageRadius;
	// the boss' damage modifier
	float m_fDamage;
	// the target's health attribute
	HealthAttribute* m_pTargetHealth;
	// timer for delaying attacks
	float m_fAttackTimer; 
	const float m_fcAttackTime;
	// timer to attack queen
	const float m_fcAttackQueenTime;
	float m_fAttackQueenTimer; 
	// timer to attack bee
	const float m_fcAttackBeeTime;
	float m_fAttackBeeTimer; 
	// timer to retreat
	const float m_fcRetreatTime;
	float m_fRetreatTimer; 
	// current attack state
	AttackCycle m_eCurAttack;

	// damage target
	void DamageTarget();
	
};

NiSmartPointer(StateBossAttack);

#endif
