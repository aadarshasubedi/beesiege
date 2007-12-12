/**
*	A state that makes the owner attack an enemy
*/
#include "StateEnemyWander.h"
#include "StateLocustAttack.h"
#include "StateDragonflyAttack.h"
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
#include "Dragonfly.h"
#include "Sound.h"
#include <NiPhysX.h>

//----------------------------------------------------------------------
/**
*	Ctor
*/
StateEnemyWander::StateEnemyWander(FSMAIControl* control, int type) : 
  FSMState(control, type)
{
	GameCharacter* owner = m_control->GetOwner();
	if (NiIsKindOf(Locust, owner))
	{
		m_eType = LOCUST_AI_CONTROL;
	}
	else if (NiIsKindOf(DragonFly, owner))
	{
		m_eType = DRAGONFLY_AI_CONTROL;
	}

}
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
		controller->PlayDyingSound();
		// dead so record a 
		// kill for the player
		GameManager::Get()->RecordKill();
		if (GameManager::Get()->GetCurrentTarget() == controller->GetOwner())
		{
			GameManager::Get()->SetCurrentTarget(0);
		}
	}
	else if (m_eType == LOCUST_AI_CONTROL)
	{
		if  (targetAtProximity = controller->IsTargetAtProximity(m_fViewRadius))
		{
			nextState = controller->GetMachine()->GetState(FSM_ENEMY_LOCUST_ATTACK);			
			((StateLocustAttack*)nextState)->SetTarget(targetAtProximity);						
		}
	}
	else if (m_eType == DRAGONFLY_AI_CONTROL)
	{
		NxVec3 pos = m_control->GetAgent()->GetActor()->getGlobalPosition();
		NxVec3 distance = m_pGameManager->GetQueen()->GetActor()->
								getGlobalPosition() - pos;
		if (distance.magnitude() < m_fViewRadius)
		{
			nextState = controller->GetMachine()->GetState(FSM_ENEMY_DRAGONFLY_ATTACK);			
			((StateDragonflyAttack*)nextState)->SetTarget(m_pGameManager->GetQueen());	
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
