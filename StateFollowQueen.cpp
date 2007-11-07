#include "State_FollowQueen.h"
#include "Bee.h"
#include "Queen.h"

void StateFollowQueen::Enter()
{

}
void StateFollowQueen::Update(int t)
{
	//here the bees follow the queen
	
	FSMAIControl* control = m_control;
	Bee* bee = ((FSMBeeAIControl*)m_control)->m_bee;
	GameObj* queen = ((FSMBeeAIControl*)m_control)->m_queenBee; //is the bee is a global character?

	//Call the bee follow queen behavior here:
	bee->SetTarget((GameCharacter*)queen);
}

FSMState* StateFollowQueen::CheckTransitions(int i)
{
	//return the current state by default
	FSMState* nextState = ((FSMBeeAIControl*)m_control)->m_bee_machine->m_currentState;

	if(((FSMBeeAIControl*)m_control)->issuedAttackCommand)
	{
		//return attack state
		nextState = ((FSMBeeAIControl*)m_control)->m_bee_machine->GetState(FSM_ATTACK_ENEMY);
	}
	else if(((FSMBeeAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		nextState = ((FSMBeeAIControl*)m_control)->m_bee_machine->GetState(FSM_BEE_DEAD);
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