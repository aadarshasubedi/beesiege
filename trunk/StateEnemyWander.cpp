/**
*	A state that makes the owner attack an enemy
*/
#include "StateEnemyWander.h"
#include "FSMMachine.h"
#include "GameCharacter.h"
#include "GameManager.h"
#include "FSMEnemyAIControl.h"
#include "Wander.h"
#include "Arrival.h"
#include "BehaviorCombo.h"
#include "NiTPointerList.h"
#include "HealthAttribute.h"
#include <NiPhysX.h>
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateEnemyWander::Enter()
{
	m_control->GetAgent()->SetTarget(m_control->GetAgent()->GetActor()->getGlobalPosition());
	m_control->GetAgent()->GetController()->SetBehavior(NiNew Wander);
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
	FSMState* nextState = m_control->GetMachine()->GetCurrentState();
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
