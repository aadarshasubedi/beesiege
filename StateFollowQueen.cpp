#include "State_FollowQueen.h"
#include "Bee.h"
#include "Queen.h"
#include "FSMMachine.h"
#include "GameManager.h"

void StateFollowQueen::Enter()
{
	m_control->m_character->SetTarget(GameManager::Get()->GetQueen());
}
void StateFollowQueen::Update(int t)
{
	m_control->m_character->GetAgent()->GetActor()
		->setGlobalOrientation(GameManager::Get()->GetQueen()->GetAgent()
		->GetActor()->getGlobalOrientation());	
}

FSMState* StateFollowQueen::CheckTransitions(int i)
{
	//return the current state by default
	FSMState* nextState = ((FSMBeeAIControl*)m_control)->m_machine->m_currentState;

	if(((FSMBeeAIControl*)m_control)->issuedAttackCommand)
	{
		//return attack state
		nextState = ((FSMBeeAIControl*)m_control)->m_machine->GetState(FSM_ATTACK_ENEMY);
	}
	else if(((FSMBeeAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		nextState = ((FSMBeeAIControl*)m_control)->m_machine->GetState(FSM_BEE_DEAD);
	}

	return nextState;
}

void StateFollowQueen::Exit()
{
	//maybe we play a different sound or animation when the bee exits from this stage...i don't know
	
}

void StateFollowQueen::Init()
{

}