/**
*	A state that makes the owner attack an enemy
*/
#include "StateEnemyWander.h"
#include "StateLocustAttack.h"
#include "StateDragonflyAttack.h"
#include "StateBossAttack.h"
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
#include "Boss.h"
#include "EnemyBase.h"
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
	else if (NiIsKindOf(Boss, owner))
	{
		m_eType = BOSS_AI_CONTROL;
	}

	m_fViewRadius = ((Enemy*)m_control->GetOwner())->GetViewRadius();
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateEnemyWander::Enter()
{
	if (m_eType == BOSS_AI_CONTROL)
	{
		NiPoint3 basePos = ((Boss*)(m_control->GetOwner()))->
			GetBase()->GetNode()->GetTranslate();

		m_control->GetAgent()->SetTarget((NxActor*)0);
		m_control->GetAgent()->SetTarget(NxVec3(basePos.x, basePos.y, basePos.z));
		
		NiTPointerList<BehaviorPtr> behaviors;
		behaviors.AddTail(NiNew Wander);
		behaviors.AddTail(NiNew Arrival);
		NiTPointerList<float> coef;
		coef.AddTail(0.5);
		coef.AddTail(1.0);

		m_control->GetAgent()->GetController()->
			SetBehavior(NiNew BehaviorCombo(behaviors,coef));
	}
	else
	{
		m_control->GetAgent()->SetTarget(m_control->GetAgent()->
			GetActor()->getGlobalPosition());
		m_control->GetAgent()->GetController()->SetBehavior(NiNew Wander);
		
	}
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
		m_pGameManager->RecordKill();
		if (m_pGameManager->GetCurrentTarget() == controller->GetOwner())
		{
			m_pGameManager->SetCurrentTarget(0);
		}

		((Enemy*)controller->GetOwner())->GetBase()->IncreaseKilled();

		// notify enemy base that its boss is dead
		if (m_eType == BOSS_AI_CONTROL)
		{
			((Enemy*)controller->GetOwner())->GetBase()->SetBossAlive(false);
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
	// if locust then attack closest target
	else if (m_eType == LOCUST_AI_CONTROL)
	{
		if  (targetAtProximity = controller->IsTargetAtProximity(m_fViewRadius))
		{
			nextState = controller->GetMachine()->GetState(FSM_ENEMY_LOCUST_ATTACK);			
			((StateLocustAttack*)nextState)->SetTarget(targetAtProximity);						
		}
	}
	// if dragonfly attack queen
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
	// if boss return boss' attack state if bee at proximity
	else if (m_eType == BOSS_AI_CONTROL)
	{
		if  (targetAtProximity = controller->IsBeeAtProximity(m_fViewRadius))
		{
			nextState = controller->GetMachine()->GetState(FSM_ENEMY_BOSS_ATTACK);			
			((StateBossAttack*)nextState)->SetTarget(targetAtProximity);						
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
