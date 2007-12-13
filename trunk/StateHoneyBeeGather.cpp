/**
*	A state that makes the owner gather honey
*/
#include "StateHoneyBeeGather.h"
#include "FSMMachine.h"
#include "Arrival.h"
#include "Seek.h"
#include "GameCharacter.h"
#include <NiColor.h>
#include "FSMHoneyBeeAIControl.h"
#include "HoneyBee.h"
#include "Flower.h"
#include "GameManager.h"
#include "ConfigurationManager.h"
#include <math.h>
//----------------------------------------------------------------------
/**
*	Ctor
*/
StateHoneyBeeGather::StateHoneyBeeGather(FSMAIControl* control, int type) : 
	  FSMState(control, type), m_pTarget(0), 
	  m_fcHoneyToken(ConfigurationManager::Get()->honeyBee_gatherAmount),
	  m_fcGatherTime(ConfigurationManager::Get()->honeyBee_duration),
	  m_fGatherTimer(m_fcGatherTime), m_fGatherDelayTimer(0.0f)
{
	
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is entered
*/
void StateHoneyBeeGather::Enter()
{
	m_pTarget = m_pGameManager->GetCurrentFlowerTarget();
	if (m_pTarget)
	{
		NiPoint3 targetPos = m_pTarget->GetNode()->GetTranslate();
		m_control->GetAgent()->SetTarget(NxVec3(targetPos.x,targetPos.y,targetPos.z));
		m_control->GetAgent()->SetTarget((NxActor*)0);
		m_control->GetAgent()->GetController()->SetBehavior((Behavior*)NiNew Seek);

	}
}
//----------------------------------------------------------------------
/**
*	Updates the state
*   @param delta time
*/
void StateHoneyBeeGather::Update(float fTime)
{
	m_control->GetAgent()->Update();

	if (m_pTarget)
	{
		Gather();
	}
}
//----------------------------------------------------------------------
/**
*	Checks for transition conditions
*   @param delta time
*/
FSMState* StateHoneyBeeGather::CheckTransitions(float fTime)
{	
	FSMState* nextState = m_control->GetMachine()->GetCurrentState();
	if (IsOwnerDead())
	{
		return nextState;
	}
	else if (!m_pTarget)
	{
		nextState = m_control->GetMachine()->GetState(FSM_FOLLOW_QUEEN);
	}
	
	return nextState;
	
}
//----------------------------------------------------------------------
/**
*	Performs necessary operations when we the state is exited
*   
*/
void StateHoneyBeeGather::Exit()
{
	((HoneyBee*)m_control->GetOwner())->SetGather(0,false);
	m_pTarget = 0;
}
//----------------------------------------------------------------------
/**
*	Gathers honey
*   
*/
void StateHoneyBeeGather::Gather()
{
	if (!m_pTarget->HasHoney())
	{
		m_pTarget = 0;
		return;
	}

	NxVec3 pos = m_control->GetAgent()->GetActor()->getGlobalPosition();
	NiPoint3 targetPos = m_pTarget->GetNode()->GetTranslate();
	NxVec3 distance = NxVec3(targetPos.x, targetPos.y, targetPos.z) - pos;
	if (distance.magnitude() < 30.0f)
	{
		m_fGatherTimer -= m_pGameManager->GetDeltaTime();
		if (m_fGatherTimer <= 0.0f)
		{
			m_fGatherTimer = m_fcGatherTime;
			m_pTarget = 0;
			return;
		}

		m_fGatherDelayTimer -=  m_pGameManager->GetDeltaTime();
		if (m_fGatherDelayTimer <= 0.0f)
		{
			m_fGatherDelayTimer = 1.0f;		
			m_pTarget->DecreaseHoneyAmount(m_fcHoneyToken);
			((HoneyBee*)m_control->GetOwner())->
				IncreaseGatheredHoney(m_fcHoneyToken);			
		}
		
	}
}