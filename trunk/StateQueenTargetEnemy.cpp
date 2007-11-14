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
#include "Enemy.h"
#include <NiPhysX.h>
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateQueenTargetEnemy::Enter()
{
	if (m_pCurrentTarget)
	{
		m_pCurrentTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
		m_pCurrentTarget = 0;
	}
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

	// if the current target move out of the queen's radius then
	// stop targeting it
	if (m_pCurrentTarget)
	{
		NxVec3 distance = m_pCurrentTarget->GetActor()->getGlobalPosition() - 
			((Queen*)controller->GetOwner())->GetActor()->getGlobalPosition();
		if (distance.magnitude() > ConfigurationManager::Get()->queen_viewRadius)
		{
			m_pCurrentTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
			m_pCurrentTarget = 0;
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
	FSMState* nextState = controller->GetMachine()->m_spCurrentState;
	
	if (controller->issuedSelectSoldiersCommand &&
		m_pCurrentTarget)
	{
		nextState = controller->GetMachine()->GetState(FSM_QUEEN_SELECTSOLDIERS);
		NIASSERT(nextState);
		((StateQueenSelectSoldiers*)nextState)->SetTarget(m_pCurrentTarget);

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
		m_pCurrentTarget = 0;
		return;
	}

	if (m_pCurrentTarget)
	{
		if (enemies.Get(m_itCurrentTargetPosition))
		{
			m_pCurrentTarget->SetEmmitance(NiColor(0.0, 0.0, 0.0));
			m_pCurrentTarget = 0;
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
		m_pCurrentTarget->SetEmmitance(NiColor(1.0, 0.0, 0.0));
	}

}