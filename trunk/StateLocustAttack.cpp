/**
*	A state that makes a locust attack the closest bee / queen
*/
#include "StateLocustAttack.h"
#include "StateEnemyWander.h"
#include "FSMMachine.h"
#include "GameManager.h"
#include "FSMEnemyAIControl.h"
#include "Seek.h"
#include "HealthAttribute.h"
#include <NiPhysX.h>
#include "Enemy.h"
#include <math.h>
#include "ConfigurationManager.h"
#include "EnemyBase.h"

//----------------------------------------------------------------------
/**
*	Ctor
*/
StateLocustAttack::StateLocustAttack(FSMAIControl* control, 
									 int type) : 
FSMState(control, type), m_pTarget(0), 
m_fDamageRadius(ConfigurationManager::Get()->locust_damageRadius),
m_fDamage(ConfigurationManager::Get()->locust_damage),
m_pTargetHealth(0), m_fAttackTimer(0.0f),  m_fcAttackTime(1.0f)
{
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateLocustAttack::Enter()
{
	if (m_pTarget)
	{
		if (!m_pTargetHealth)
		{
			m_pTargetHealth = (HealthAttribute*)m_pTarget->GetAttribute(
			GameCharacter::ATTR_HEALTH);
		}
		m_control->GetAgent()->SetTarget(m_pTarget->GetActor());
		m_fViewRadius = ((Enemy*)m_control->GetOwner())->GetViewRadius();
	}
	else
	{
		m_control->GetAgent()->SetTarget(m_control->GetAgent()->GetActor()->getGlobalPosition());
	}
	
	m_control->GetAgent()->GetController()->SetBehavior(NiNew Seek);
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateLocustAttack::Update(float fTime)
{
	FSMEnemyAIControl* controller = (FSMEnemyAIControl*)m_control;
	SetTarget(controller->IsTargetAtProximity(m_fViewRadius));
	if (m_pTarget)
	{		
		m_control->GetAgent()->SetTarget(m_pTarget->GetActor());
		DamageTarget();
	}
	m_control->GetAgent()->Update();	
}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateLocustAttack::CheckTransitions(float fTime)
{	
	FSMEnemyAIControl* controller = (FSMEnemyAIControl*)m_control;
	FSMState* nextState = controller->GetMachine()->GetCurrentState();
	if (IsOwnerDead())
	{
		controller->PlayDyingSound();
		// dead so record a 
		// kill for the player
		GameManager::Get()->RecordKill();
		((Enemy*)controller->GetOwner())->GetBase()->IncreaseKilled();
		if (GameManager::Get()->GetCurrentTarget() == m_control->GetOwner())
		{
			GameManager::Get()->SetCurrentTarget(0);
		}
	}
	// if the boss of the enemy's base is dead then die 
	else if (!((Enemy*)controller->GetOwner())->GetBase()->IsBossAlive())
	{
		controller->GetOwner()->SetActive(false);
		controller->PlayDyingSound();
		// dead so record a 
		// kill for the player
		m_pGameManager->RecordKill();
		if (m_pGameManager->GetCurrentTarget() == controller->GetOwner())
		{
			m_pGameManager->SetCurrentTarget(0);
		}

		((Enemy*)controller->GetOwner())->GetBase()->IncreaseKilled();
	}
	else if (!m_pTarget)
	{
		nextState = m_control->GetMachine()->GetState(FSM_ENEMY_WANDER);
	}

	return nextState;
}
//----------------------------------------------------------------------
/**
* Set the target
* @param the target
*/
void StateLocustAttack::SetTarget(GameCharacter* target)
{
	m_pTarget = target;
	if (m_pTarget)
		m_pTargetHealth = (HealthAttribute*)m_pTarget->GetAttribute(
			GameCharacter::ATTR_HEALTH);
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is exited
*   
*/
void StateLocustAttack::Exit()
{
	m_pTarget = 0;
	m_pTargetHealth = 0;
}
//----------------------------------------------------------------------
/**
*	Damage current target
*   
*/
void StateLocustAttack::DamageTarget()
{
	if (!m_pTargetHealth) return;
			
	NxVec3 curPos    = m_control->GetOwner()->GetActor()->getGlobalPosition();
	NxVec3 targetPos = m_pTarget->GetActor()->getGlobalPosition();
	float distance = NxVec3(targetPos - curPos).magnitude();
	if (distance <= m_fDamageRadius)
	{
		m_fAttackTimer -= GameManager::Get()->GetDeltaTime();
		if (m_fAttackTimer > 0.0f)
		{
			return;
		}
		if (rand()%100 > 50)
		{
			m_pTargetHealth->ReduceHealth(m_fDamage);		
			if (m_pTargetHealth->GetHealth() <= 0.0f)
			{
				//m_pTarget->SetActive(false);
				m_pTarget = 0;
				m_pTargetHealth = 0;
			}
		}
		
		m_fAttackTimer = m_fcAttackTime;
		
	}
}