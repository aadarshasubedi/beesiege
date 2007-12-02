/**
*	A state that makes the owner attack an enemy
*/
#include "StateEnemyWander.h"
#include "StateLocustAttack.h"
#include "FSMMachine.h"
#include "GameCharacter.h"
#include "GameManager.h"
#include "FSMEnemyAIControl.h"
#include "Wander.h"
#include "Arrival.h"
#include "BehaviorCombo.h"
#include "NiTPointerList.h"
#include "HealthAttribute.h"
#include "Locust.h"
#include <NiPhysX.h>
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateEnemyWander::Enter()
{
	m_control->GetAgent()->SetTarget(m_control->GetAgent()->GetActor()->getGlobalPosition());
	m_control->GetAgent()->GetController()->SetBehavior(NiNew Wander);
	m_fViewRadius = ((Enemy*)m_control->GetOwner())->GetViewRadius();
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateEnemyWander::Update(float fTime)
{
	m_control->GetAgent()->Update();	
}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateEnemyWander::CheckTransitions(float fTime)
{	
	FSMEnemyAIControl* controller = (FSMEnemyAIControl*)m_control;
	FSMState* nextState = controller->GetMachine()->GetCurrentState();
	GameCharacter* targetAtProximity = 0;
	if (IsOwnerDead())
	{
		// dead so record a 
		// kill for the player
		GameManager::Get()->RecordKill();
		if (GameManager::Get()->GetCurrentTarget() == controller->GetOwner())
		{
			GameManager::Get()->SetCurrentTarget(0);
		}
	}
	else if (targetAtProximity = controller->IsTargetAtProximity(m_fViewRadius))
	{
		// if the owner is a locust then return StateLocustAttack
		if (NiIsKindOf(Locust, m_control->GetOwner()))
		{
			nextState = controller->GetMachine()->GetState(FSM_ENEMY_LOCUST_ATTACK);
			NIASSERT(nextState);
			((StateLocustAttack*)nextState)->SetTarget(targetAtProximity);
		}
		
	}
	

	return nextState;
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is exited
*   
*/
void StateEnemyWander::Exit()
{
	
}
