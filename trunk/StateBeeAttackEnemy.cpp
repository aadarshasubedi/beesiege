/**
*	A state that makes the owner attack an enemy
*/
#include "StateBeeAttackEnemy.h"
#include "FSMMachine.h"
#include "Arrival.h"
#include "Seek.h"
#include "Cohesion.h"
#include "Separation.h"
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
#include "DamageAttribute.h"
#include <math.h>
#include <NiColor.h>
//----------------------------------------------------------------------
/**
*	Ctor
*/
StateBeeAttackEnemy::StateBeeAttackEnemy(FSMAIControl* control, int type) : 
	  FSMState(control, type), m_pTarget(0), m_fAttackTimer(0.0f),
	  m_fcAttackTime(1.0f), m_bIsAttackStrong(false), m_pOwnerDamage(0)
{
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateBeeAttackEnemy::Enter()
{
	m_pTarget = ((FSMBeeAIControl*)m_control)->m_pTargetEnemy;
	if (m_pTarget)
	{
		m_pTargetHealth = (HealthAttribute*)m_pTarget->GetAttribute(GameCharacter::ATTR_HEALTH);
		// if target just died then return
		NIASSERT(m_pTargetHealth);
		if (m_pTargetHealth)
		{
			if (m_pTargetHealth->GetHealth() <= 0.0f)
			{
				m_pTarget = 0;
				return;
			}
		}

		NxActor* target = m_pTarget->GetActor();
		m_control->GetAgent()->SetTarget(target);

		// create a behavior combo
		NiTPointerList<BehaviorPtr> lBehaviors;
		NiTPointerList<float> lCoefficients;
		SeparationPtr sep = NiNew Separation();
		CohesionPtr coh = NiNew Cohesion();
		AlignmentPtr ali = NiNew Alignment();
		lBehaviors.AddTail(NiNew Seek);
		lBehaviors.AddTail((Behavior*)sep);
		lBehaviors.AddTail((Behavior*)coh);
		lBehaviors.AddTail((Behavior*)ali);
		
		lCoefficients.AddTail(1.0f);
		lCoefficients.AddTail(1.5f);
		lCoefficients.AddTail(0.0f);
		lCoefficients.AddTail(0.8f);
		
		BehaviorComboPtr combo = NiNew BehaviorCombo(lBehaviors, lCoefficients);
		m_control->GetAgent()->GetController()->SetBehavior((Behavior*)combo);

		// add bee to the enemy's attacker list
		m_pTarget->AddAttacker(m_control->GetOwner(), m_control->GetAgent());
		GameManager::Get()->SetAgentGroup(&m_pTarget->GetAttackersAgents());
		// let the group behaviors know about the group they are in
		sep->SetNeighbors(&m_pTarget->GetAttackersAgents());
		coh->SetNeighbors(&m_pTarget->GetAttackersAgents());
		ali->SetNeighbors(&m_pTarget->GetAttackersAgents());
	}
	
	m_fAttackTimer = 0.0f;
	m_pOwnerDamage = (DamageAttribute*)m_control->GetOwner()->
		GetAttribute(GameCharacter::ATTR_DAMAGE);
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
		bool isAttackStrongNew = m_pTarget->IsAttackStrong();
		if (m_bIsAttackStrong != isAttackStrongNew)
		{
			m_bIsAttackStrong = isAttackStrongNew;
			// attack is strong so modify Cohesion coefficient (2) to make group
			// cohesive and make separation coefficient (1) zero so that they are not separated
			if (m_bIsAttackStrong)
			{
				((BehaviorCombo*)m_control->GetAgent()->GetController()->GetBehavior())
				->ModifyCoefficient(1, 0.0f);
				((BehaviorCombo*)m_control->GetAgent()->GetController()->GetBehavior())
				->ModifyCoefficient(2, 0.5f);
			}
			// else do the opposite
			else
			{
				((BehaviorCombo*)m_control->GetAgent()->GetController()->GetBehavior())
				->ModifyCoefficient(1, 1.5f);
				((BehaviorCombo*)m_control->GetAgent()->GetController()->GetBehavior())
				->ModifyCoefficient(2, 0.0f);
			}
		}
		
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
	if (IsOwnerDead())
	{
		return nextState;
	}
	else if (!m_pTarget)
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
	if (m_pTargetHealth)
	{
		if (m_pTargetHealth->GetHealth() <= 0.0f)
		{
			m_pTarget = 0;
			Bee* owner = (Bee*)m_control->GetOwner();
			if (owner->IsHighlighted())
			{
				owner->SetEmmitance(NiColor(0.0f, 0.0f, 0.0f));
				owner->SetHighlighted(false);
			}
		}
		else
		{
			if (!IsTargetInRadius(50.0f)) return;
			m_fAttackTimer -= GameManager::Get()->GetDeltaTime();
			if (m_fAttackTimer > 0.0f)
			{
				return;
			}

			if (rand()%100 > 50)
			{
				if (m_pOwnerDamage)
					m_pTargetHealth->ReduceHealth(m_pOwnerDamage->GetDamage());	
			}
			

			m_fAttackTimer = m_fcAttackTime;
		}			
	}
	else
	{
		Bee* owner = (Bee*)m_control->GetOwner();
		if (owner->IsHighlighted())
		{
			owner->SetEmmitance(NiColor(0.0f, 0.0f, 0.0f));
			owner->SetHighlighted(false);
		}
	}
}