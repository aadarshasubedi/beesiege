/**
*	A state that makes a locust attack the closest bee / queen
*/
#include "StateLocustAttack.h"
#include "StateEnemyWander.h"
#include "FSMMachine.h"
#include "GameCharacter.h"
#include "GameManager.h"
#include "FSMEnemyAIControl.h"
#include "Seek.h"
#include "HealthAttribute.h"
#include <NiPhysX.h>
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateLocustAttack::Enter()
{
	if (m_pTarget)
	{
		m_control->GetAgent()->SetTarget(m_pTarget->GetActor());
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
	if (m_pTarget = controller->IsTargetAtProximity(200.0f))
	{
		m_control->GetAgent()->SetTarget(m_pTarget->GetActor());
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
*	Performs necessary operations when we the state is exited
*   
*/
void StateLocustAttack::Exit()
{
	m_pTarget = 0;
}
