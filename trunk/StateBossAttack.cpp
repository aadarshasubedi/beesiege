/**
*	A state that makes a boss attack
*/
#include "StateBossAttack.h"
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
#include "Boss.h"
#include "EnemyBase.h"

//----------------------------------------------------------------------
/**
*	Ctor
*/
StateBossAttack::StateBossAttack(FSMAIControl* control, 
									 int type) : 
FSMState(control, type), m_pTarget(0), 
m_fDamageRadius(ConfigurationManager::Get()->boss_damageRadius),
m_fDamage(ConfigurationManager::Get()->boss_damage),
m_pTargetHealth(0), m_fAttackTimer(0.0f),  m_fcAttackTime(1.0f),
m_fcAttackQueenTime(4.0f), m_fAttackQueenTimer(m_fcAttackQueenTime),
m_fcAttackBeeTime(4.0f), m_fAttackBeeTimer(m_fcAttackBeeTime),
m_fcRetreatTime(4.0f), m_fRetreatTimer(m_fcRetreatTime)
{
	m_fViewRadius = ((Enemy*)m_control->GetOwner())->GetViewRadius();
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateBossAttack::Enter()
{
	if (!m_pTarget)
	{
		m_pTarget = ((FSMEnemyAIControl*)m_control)->
			IsBeeAtProximity(m_fViewRadius);
	}

	if (m_pTarget)
	{
		m_pTargetHealth = (HealthAttribute*)m_pTarget->GetAttribute(
			GameCharacter::ATTR_HEALTH);
		m_control->GetAgent()->SetTarget(m_pTarget->GetActor());		
	}
	
	m_control->GetAgent()->GetController()->SetBehavior(NiNew Seek);

	m_eCurAttack = ATTACK_BEE;
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateBossAttack::Update(float fTime)
{
	// if boss is attacking a bee decrease timer
	// to attack queen
	if (m_eCurAttack == ATTACK_BEE)
	{
		m_fAttackQueenTimer -= m_pGameManager->GetDeltaTime();
		if (m_fAttackQueenTimer <= 0.0f)
		{
			m_fAttackQueenTimer = m_fcAttackQueenTime;
			SetTarget((GameCharacter*)m_pGameManager->GetQueen());
			m_eCurAttack = ATTACK_QUEEN;
		}
		else
		{
			if (m_pTargetHealth)
			{
				if (m_pTargetHealth->GetHealth() <= 0.0f)
				{
					SetTarget(((FSMEnemyAIControl*)m_control)->
					IsBeeAtProximity(m_fViewRadius));
				}
			}
		}
	}
	// if boss is attacking the queen decrease timer
	// to retreat to base
	else if (m_eCurAttack == ATTACK_QUEEN)
	{
		m_fRetreatTimer -= m_pGameManager->GetDeltaTime();
		if (m_fRetreatTimer <= 0.0f)
		{
			m_fRetreatTimer = m_fcRetreatTime;
			m_pTarget = 0;
			m_eCurAttack = ATTACK_RETREAT;
		}
		else
		{
			if (m_pTargetHealth)
			{
				if (m_pTargetHealth->GetHealth() <= 0.0f)
				{
					m_pTarget = 0;
					m_pTargetHealth = 0;
					m_eCurAttack = ATTACK_RETREAT;
				}
			}
		}
	}
	// if boss is retreating decrease timer
	// to attack a bee
	else if (m_eCurAttack == ATTACK_RETREAT)
	{
		m_fAttackBeeTimer -= m_pGameManager->GetDeltaTime();
		if (m_fAttackBeeTimer <= 0.0f)
		{
			m_fAttackBeeTimer = m_fcAttackBeeTime;
			SetTarget(((FSMEnemyAIControl*)m_control)->
					IsBeeAtProximity(m_fViewRadius));
			m_eCurAttack = ATTACK_BEE;
		}
	}
	
	if (m_pTarget)
	{		
		m_control->GetAgent()->SetTarget(m_pTarget->GetActor());
		DamageTarget();
	}
	else
	{
		m_control->GetAgent()->SetTarget((NxActor*)0);
	}

	m_control->GetAgent()->Update();	
}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateBossAttack::CheckTransitions(float fTime)
{	
	FSMEnemyAIControl* controller = (FSMEnemyAIControl*)m_control;
	FSMState* nextState = controller->GetMachine()->GetCurrentState();
	
	if (IsOwnerDead())
	{
		controller->PlayDyingSound();
		// dead so record a 
		// kill for the player
		GameManager::Get()->RecordKill();
		((Boss*)controller->GetOwner())->GetBase()->IncreaseKilled();

		if (m_pGameManager->GetCurrentTarget() == m_control->GetOwner())
		{
			m_pGameManager->SetCurrentTarget(0);
		}

		// notify base that the boss is dead
		((Boss*)m_control->GetOwner())->GetBase()->SetBossAlive(false);
	}
	
	return nextState;
}
//----------------------------------------------------------------------
/**
* Set the target
* @param the target
*/
void StateBossAttack::SetTarget(GameCharacter* target)
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
void StateBossAttack::Exit()
{
	m_pTarget = 0;
	m_pTargetHealth = 0;
}
//----------------------------------------------------------------------
/**
*	Damage current target
*   
*/
void StateBossAttack::DamageTarget()
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
		}
		
		m_fAttackTimer = m_fcAttackTime;
		
	}
}