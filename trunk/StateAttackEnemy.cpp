#include "State_Attack_Enemy.h"
#include "FSMMachine.h"
#include "Arrival.h"
#include "GameCharacter.h"
#include <NiColor.h>

void StateAttackEnemy::Enter()
{
	m_control->m_character->GetAgent()->GetController()->SetBehavior(NiNew Arrival());
	m_control->m_character->SetEmmitance(NiColor(0.0, 0.0, 0.0));
}

void StateAttackEnemy::Update(int t)
{
	
}

FSMState* StateAttackEnemy::CheckTransitions(int i)
{
	
	//return the current state by default
	FSMState* nextState = ((FSMBeeAIControl*)m_control)->m_machine->m_currentState;
/*
	if(((FSMBeeAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		nextState = ((FSMBeeAIControl*)m_control)->m_machine->GetState(FSM_BEE_DEAD);
	}

	//go back to follow queen state if target enemy is dead
	else if(((FSMBeeAIControl*)m_control)->isTargetDead)
	{
		//return the follow queen state
		nextState = ((FSMBeeAIControl*)m_control)->m_machine->GetState(FSM_FOLLOW_QUEEN);
	}
*/	
	return nextState;
	
}

void StateAttackEnemy::Exit()
{
	//is the bee supposed to do anything special as it exits the attack state?
	// that logic would come here
	//((FSMBeeAIControl*)m_control)->issuedAttackCommand = false;
}

void StateAttackEnemy::Init()
{

}