/**
*	A state that makes a locust attack the queen
*/
#include "StateDragonflyAttack.h"
#include "StateEnemyWander.h"
#include "FSMMachine.h"
#include "GameManager.h"
#include "FSMEnemyAIControl.h"
#include "Seek.h"
#include "HealthAttribute.h"
#include <NiPhysX.h>
#include "Enemy.h"
#include "Queen.h"
#include <math.h>
#include "ConfigurationManager.h"


//----------------------------------------------------------------------
/**
*	Ctor
*/
StateDragonflyAttack::StateDragonflyAttack(FSMAIControl* control, 
									 int type) : 
FSMState(control, type), m_pTarget(0), 
m_fDamageRadius(ConfigurationManager::Get()->dragonfly_damageRadius),
m_fDamage(ConfigurationManager::Get()->dragonfly_damage),
m_pTargetHealth(0), m_fAttackTimer(0.0f),  m_fcAttackTime(1.0f)
{
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateDragonflyAttack::Enter()
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
void StateDragonflyAttack::Update(float fTime)
{
	FSMEnemyAIControl* controller = (FSMEnemyAIControl*)m_control;
	NxVec3 pos = m_control->GetAgent()->GetActor()->getGlobalPosition();
	NxVec3 distance = m_pGameManager->GetQueen()->
		GetActor()->getGlobalPosition() - pos;
	if (distance.magnitude() >= m_fViewRadius)
	{
		m_pTarget = 0;
	}
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
FSMState* StateDragonflyAttack::CheckTransitions(float fTime)
{	
	FSMEnemyAIControl* controller = (FSMEnemyAIControl*)m_control;
	FSMState* nextState = controller->GetMachine()->GetCurrentState();
	if (IsOwnerDead())
	{
		controller->PlayDyingSound();
		// dead so record a 
		// kill for the player
		GameManager::Get()->RecordKill();
		if (GameManager::Get()->GetCurrentTarget() == m_control->GetOwner())
		{
			GameManager::Get()->SetCurrentTarget(0);
		}
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
void StateDragonflyAttack::SetTarget(GameCharacter* target)
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
void StateDragonflyAttack::Exit()
{
	m_pTarget = 0;
	m_pTargetHealth = 0;
}
//----------------------------------------------------------------------
/**
*	Damage current target
*   
*/
void StateDragonflyAttack::DamageTarget()
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