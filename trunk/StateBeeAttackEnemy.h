#ifndef STATEATTACKENEMY_H
#define STATEATTACKENEMY_H

#include "FSMState.h"

class Enemy;
class HealthAttribute;

class StateBeeAttackEnemy: public FSMState
{
public:
	StateBeeAttackEnemy(FSMAIControl* control, int type=FSM_ATTACK_ENEMY);
	void Enter();
	void Exit();
	void Update(float fTime);
	FSMState* CheckTransitions(float fTime);
private:
	
	Enemy* m_pTarget;
	HealthAttribute* m_pOwnerHealth;
	HealthAttribute* m_pTargetHealth;
	bool IsTargetInRadius(float radius);
	float m_fAttackTimer; 
	const float m_fcAttackTime;
	void DamageTarget();
};

NiSmartPointer(StateAttackEnemy);

#endif
