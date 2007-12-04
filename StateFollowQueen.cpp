/**
*	A state that makes the owner follow the queen
*/
#include "State_FollowQueen.h"
#include "Bee.h"
#include "Queen.h"
#include "FSMMachine.h"
#include "GameManager.h"
#include "FSMBeeAIControl.h"
#include "Arrival.h"
#include "Seek.h"
#include "Departure.h"
#include "Wander.h"
#include "BehaviorCombo.h"
#include "HealthAttribute.h"
#include <NiTPointerList.h>

//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateFollowQueen::Enter()
{
	GameManager::Get()->GetQueen()->AddSoldier((Bee*)((FSMBeeAIControl*)m_control)->GetOwner());
	// set the target to the queen
	m_control->GetAgent()->SetTarget(
		GameManager::Get()->GetQueen()->GetActor());
	
	// create a behavior combo
	NiTPointerList<BehaviorPtr> lBehaviors;
	NiTPointerList<float> lCoefficients;
	lBehaviors.AddTail(NiNew Arrival);
	lBehaviors.AddTail(NiNew Departure);
	lBehaviors.AddTail(NiNew Wander);

	lCoefficients.AddTail(1.0f);
	lCoefficients.AddTail(2.0f);
	lCoefficients.AddTail(0.5f);

	BehaviorComboPtr combo = NiNew BehaviorCombo(lBehaviors, lCoefficients);

	m_control->GetAgent()->GetController()->SetBehavior((Behavior*)combo);
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateFollowQueen::Update(float fTime)
{
	m_control->GetAgent()->Update();
}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateFollowQueen::CheckTransitions(float fTime)
{
	//return the current state by default
	FSMState* nextState = m_control->GetMachine()->GetCurrentState();;

	if (IsOwnerDead())
	{
		((FSMBeeAIControl*)m_control)->PlayDyingSound();
		return nextState;
	}
	else if(((FSMBeeAIControl*)m_control)->issuedAttackCommand)
	{
		((FSMBeeAIControl*)m_control)->issuedAttackCommand = false;
		//return attack state
		nextState = ((FSMBeeAIControl*)m_control)->GetMachine()->GetState(FSM_ATTACK_ENEMY);
	}
	
	return nextState;
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is exited
*   
*/
void StateFollowQueen::Exit()
{
	
}
