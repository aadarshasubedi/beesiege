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
	m_pHealth = (HealthAttribute*)m_control->GetOwner()->
		GetAttribute(GameCharacter::ATTR_HEALTH);
	m_control->GetAgent()->SetTarget(m_control->GetAgent()->GetActor()->getGlobalPosition());
	// create a behavior combo
	//NiTPointerList<BehaviorPtr> lBehaviors;
	//NiTPointerList<float> lCoefficients;
	//lBehaviors.AddTail(NiNew Arrival);
	//lBehaviors.AddTail(NiNew Wander);

	//lCoefficients.AddTail(1.0f);
	//lCoefficients.AddTail(2.0f);

	//BehaviorComboPtr combo = NiNew BehaviorCombo(lBehaviors, lCoefficients);
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

	m_control->GetAgent()->LookAt(GameManager::Get()->
		GetQueen()->GetActor()->getGlobalPosition());
	
}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateEnemyWander::CheckTransitions(float fTime)
{	
	
	FSMState* nextState = m_control->GetMachine()->GetCurrentState();;
	
	if (m_pHealth)
	{
		if (m_pHealth->GetHealth() <= 0.0f)
		{
			m_control->GetOwner()->SetActive(false);
			//m_control->GetAgent()->GetController()->ToggleSpringDynamics(true);
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
