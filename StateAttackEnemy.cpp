#include "State_Attack_Enemy.h"

void StateAttackEnemy::Enter()
{
	//play animation for attack
}
void StateAttackEnemy::Update(int t)
{
	//here the bee attacks the enemy

	GameObj* enemy = ((FSMBeeAIControl*)m_control)->m_TargetEnemy;
	Bee* bee = ((FSMBeeAIControl*)m_control)->m_bee;

	//Set enemy as target
	bee->SetTarget((GameCharacter*)enemy);

	//the collisions with enemy should reduce the enemy's health
	//that should be happening in the collision response
}

FSMState* StateAttackEnemy::CheckTransitions(int i)
{
	//return the current state by default
	FSMState* nextState = ((FSMBeeAIControl*)m_control)->m_bee_machine->m_currentState;

	if(((FSMBeeAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		nextState = ((FSMBeeAIControl*)m_control)->m_bee_machine->GetState(FSM_BEE_DEAD);
	}

	//go back to follow queen state if target enemy is dead
	else if(((FSMBeeAIControl*)m_control)->isTargetDead)
	{
		//return the follow queen state
		nextState = ((FSMBeeAIControl*)m_control)->m_bee_machine->GetState(FSM_FOLLOW_QUEEN);
	}
	
	return nextState;
}

void StateAttackEnemy::Exit()
{
	//is the bee supposed to do anything special as it exits the attack state?
	// that logic would come here
	((FSMBeeAIControl*)m_control)->issuedAttackCommand = false;
}

void StateAttackEnemy::Init()
{

}