/**
*	A state that allows the queen to target enemies
*/
#include "StateQueenTargetEnemy.h"
#include "StateQueenSelectSoldiers.h"
#include "Bee.h"
#include "Queen.h"
#include "FSMMachine.h"
#include "GameManager.h"
#include "FSMQueenAIControl.h"
#include "ConfigurationManager.h"
#include "HealthAttribute.h"
#include "Enemy.h"
#include <NiPhysX.h>
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateQueenTargetEnemy::Enter()
{
	
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateQueenTargetEnemy::Update(float fTime)
{
	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	NIASSERT(controller);

	if (controller->issuedTargetEnemyCommand)
	{
		controller->issuedTargetEnemyCommand = false;
		TargetNextEnemy();
	}

	// if the current target is dead then deselect it
	if (m_pTargetHealth)
	{
		if (m_pTargetHealth->GetHealth() <= 0.0f)
		{
			DeselectCurrent();
		}
	}

	// if the current target move out of the queen's radius then
	// stop targeting it
	if (m_pCurrentTarget)
	{
		if (m_pCurrentTarget->GetActor())
		{
			NxVec3 targetPos = m_pCurrentTarget->GetActor()->getGlobalPosition();
			NxVec3 queenPos  = ((Queen*)controller->GetOwner())->GetActor()->getGlobalPosition();
			NxVec3 distance = targetPos - queenPos;
			
			if (distance.magnitude() > ConfigurationManager::Get()->queen_viewRadius)
			{
				DeselectCurrent();
			}
		}		
	}

}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateQueenTargetEnemy::CheckTransitions(float fTime)
{
	FSMQueenAIControl* controller = (FSMQueenAIControl*)m_control;
	NIASSERT(controller);
	FSMState* nextState = controller->GetMachine()->GetCurrentState();;
	
	if (controller->issuedSelectSoldiersCommand &&
		m_pCurrentTarget)
	{
		nextState = controller->GetMachine()->GetState(FSM_QUEEN_SELECTSOLDIERS);
	}
	else if (controller->issuedSelectGatherersCommand &&
		GameManager::Get()->GetCurrentFlowerTarget())
	{
		nextState = controller->GetMachine()->GetState(FSM_QUEEN_SELECTGATHERERS);
	}
	return nextState;
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is exited
*   
*/
void StateQueenTargetEnemy::Exit()
{
	
}
//------------------------------------------------------------------------ 
/** 
 * Targets next closest enemy
 * 
 */
void StateQueenTargetEnemy::TargetNextEnemy()
{
	const NiTPointerList<EnemyPtr>& enemies = GameManager::Get()->GetEnemies();
	
	if (enemies.IsEmpty()) 
	{
		if (m_pCurrentTarget)
		{
			DeselectCurrent();
		}
		return;
	}

	// deselect current target and current attackers
	if (m_pCurrentTarget)
	{
		if (enemies.Get(m_itCurrentTargetPosition) == m_pCurrentTarget)
		{
			DeselectCurrent();
			if (m_itCurrentTargetPosition == enemies.GetTailPos())
			{
				m_itCurrentTargetPosition = enemies.GetHeadPos();
			}
			else
			{
				m_itCurrentTargetPosition = 
					enemies.GetNextPos(m_itCurrentTargetPosition);
			}
		}
		else
		{
			DeselectCurrent();
			m_itCurrentTargetPosition = enemies.GetHeadPos();
		}
	}
	else
	{
		m_itCurrentTargetPosition = enemies.GetHeadPos();
	}

	// check if target is in radius otherwise select the next one
	while(true)
	{
		m_pCurrentTarget = enemies.Get(m_itCurrentTargetPosition);
		NxVec3 distance = m_pCurrentTarget->GetActor()->getGlobalPosition() - 
			m_control->GetAgent()->GetActor()->getGlobalPosition();
		if (distance.magnitude() <= ConfigurationManager::Get()->queen_viewRadius)
		{
			break;
		}
		else
		{
			if (m_itCurrentTargetPosition == enemies.GetTailPos())
			{
				break;
			}
			else
			{
				m_itCurrentTargetPosition = enemies.GetNextPos(
					m_itCurrentTargetPosition);
			}
		}
	}

	// select target (change emmisive color)
	if (m_pCurrentTarget)
	{
		m_pTargetHealth = (HealthAttribute*)m_pCurrentTarget->
			GetAttribute(GameCharacter::ATTR_HEALTH);
		GameManager::Get()->SetCurrentTarget(m_pCurrentTarget);
		m_pCurrentTarget->SetEmmitance(NiColor(1.0, 0.0, 0.0));
		if (!m_pCurrentTarget->GetAttackers().IsEmpty())
		{
			const NiTPointerList<GameCharacterPtr>& attackers = m_pCurrentTarget->GetAttackers();
			NiTListIterator it = attackers.GetHeadPos();
			for (int i=0; i<attackers.GetSize(); i++)
			{
				attackers.Get(it)->SetEmmitance(NiColor(0.0, 0.8, 0.0));
				if (NiIsKindOf(Bee, attackers.Get(it)))
				{
					((Bee*)(GameCharacter*)attackers.Get(it))->SetHighlighted(true);
				}
				it = attackers.GetNextPos(it);
			}
		}
	}

}
//------------------------------------------------------------------------ 
/** 
 * Deselects current target and attackers
 * 
 */
void StateQueenTargetEnemy::DeselectCurrent()
{
	if (!m_pCurrentTarget) return;
	m_pCurrentTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
	if (!m_pCurrentTarget->GetAttackers().IsEmpty())
	{
		const NiTPointerList<GameCharacterPtr>& attackers = m_pCurrentTarget->GetAttackers();
		NiTListIterator it = attackers.GetHeadPos();
		for (int i=0; i<attackers.GetSize(); i++)
		{
			if (NiIsKindOf(Bee, attackers.Get(it)))
			{
				Bee* attacker = (Bee*)(GameCharacter*)attackers.Get(it);
				if (attacker)
				{
					if (attacker->IsHighlighted())
					{
						attacker->SetEmmitance(NiColor(0.0, 0.0, 0.0));
						attacker->SetHighlighted(false);
					}
				}				
			}
			else
			{
				attackers.Get(it)->SetEmmitance(NiColor(0.0, 0.0, 0.0));
			}
			it = attackers.GetNextPos(it);
		}
	}
	m_pCurrentTarget->SetStrongAttack(false);
	m_pCurrentTarget = 0;
	GameManager::Get()->SetCurrentTarget(0);
	m_pTargetHealth = 0;
}