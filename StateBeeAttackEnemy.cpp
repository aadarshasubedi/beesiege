/**
*	A state that makes the owner attack an enemy
*/
#include "StateBeeAttackEnemy.h"
#include "FSMMachine.h"
#include "Arrival.h"
#include "Seek.h"
#include "Cohesion.h"
#include "Alignment.h"
#include "Wander.h"
#include "BehaviorCombo.h"
#include "GameCharacter.h"
#include <NiColor.h>
#include "FSMBeeAIControl.h"
#include "Bee.h"
#include "Enemy.h"
#include "GameManager.h"
#include "HealthAttribute.h"
#include <math.h>
#include <NiColor.h>
//----------------------------------------------------------------------
/**
*	Ctor
*/
StateBeeAttackEnemy::StateBeeAttackEnemy(FSMAIControl* control, int type) : 
	  FSMState(control, type), m_pTarget(0), m_fAttackTimer(0.0f), m_fcAttackTime(1.0f)
{
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateBeeAttackEnemy::Enter()
{
	m_pOwnerHealth = (HealthAttribute*)m_control->GetOwner()->
		GetAttribute(GameCharacter::ATTR_HEALTH);

	m_pTarget = ((FSMBeeAIControl*)m_control)->m_pTargetEnemy;
	if (m_pTarget)
	{
		m_pTargetHealth = (HealthAttribute*)m_pTarget->GetAttribute(GameCharacter::ATTR_HEALTH);

		NxActor* target = m_pTarget->GetActor();
		m_control->GetAgent()->SetTarget(target);

		// create a behavior combo
		NiTPointerList<BehaviorPtr> lBehaviors;
		NiTPointerList<float> lCoefficients;
		lBehaviors.AddTail(NiNew Seek);
		lBehaviors.AddTail(NiNew Cohesion);
		lBehaviors.AddTail(NiNew Alignment);
		lBehaviors.AddTail(NiNew Wander);

		lCoefficients.AddTail(1.0f);
		lCoefficients.AddTail(0.5f);
		lCoefficients.AddTail(0.8f);
		lCoefficients.AddTail(0.2f);

		BehaviorComboPtr combo = NiNew BehaviorCombo(lBehaviors, lCoefficients);
		m_control->GetAgent()->GetController()->SetBehavior((Behavior*)combo);
		
	}
	
	m_fAttackTimer = 0.0f;
	m_control->GetOwner()->SetEmmitance(NiColor(0.0, 0.0, 0.0));
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateBeeAttackEnemy::Update(float fTime)
{
	m_control->GetAgent()->Update();

	if (m_pTarget)
	{
		m_control->GetAgent()->LookAt(m_pTarget->GetActor()->getGlobalPosition());
		DamageTarget();
	}
}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateBeeAttackEnemy::CheckTransitions(float fTime)
{	
	FSMState* nextState = m_control->GetMachine()->GetCurrentState();
	if (!m_pTarget)
	{
		((FSMBeeAIControl*)m_control)->m_pTargetEnemy = 0;
		nextState = m_control->GetMachine()->GetState(FSM_FOLLOW_QUEEN);
		NIASSERT(nextState);
	}
	return nextState;
	
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is exited
*   
*/
void StateBeeAttackEnemy::Exit()
{
	((Bee*)((FSMBeeAIControl*)m_control)->GetOwner())->SetAttack(0, false);
	m_pTarget = 0;
}
//----------------------------------------------------------------------
/**
*	Checks if the target is close enough to the owner
*   @param the desired radius
*/
bool StateBeeAttackEnemy::IsTargetInRadius(float radius)
{
	if (!m_pTarget) return false;

	NxVec3 distance = m_pTarget->GetActor()->getGlobalPosition() -
		m_control->GetAgent()->GetActor()->getGlobalPosition();


	return distance.magnitude() <= radius;
}
//----------------------------------------------------------------------
/**
*	Attempts to hit the target and if it does in decreases the target's
*	health
*   
*/
void StateBeeAttackEnemy::DamageTarget()
{
	if (!IsTargetInRadius(50.0f)) return;

	if (m_pTargetHealth)
	{
		if (m_pTargetHealth->GetHealth() <= 0.0f)
		{
			m_control->GetOwner()->SetEmmitance(NiColor(0.0, 0.0, 0.0));
			m_pTarget = 0;
		}
		else
		{
			m_fAttackTimer -= GameManager::Get()->GetDeltaTime();
			if (m_fAttackTimer > 0.0f)
			{
				return;
			}

			if (rand()%100 > 50)
			{
				m_control->GetOwner()->SetEmmitance(NiColor(1.0, 1.0, 0.0));
				m_pTargetHealth->ReduceHealth();	
			}
			else
			{
				m_control->GetOwner()->SetEmmitance(NiColor(0.0, 0.0, 1.0));
			}

			m_fAttackTimer = m_fcAttackTime;
		}			
	}
}