#include "State_Idle.h"

void StateIdle::Enter()
{

}
void StateIdle::Update(int t)
{
	FSMAIControl* control = m_control;
	//Locust* enemy = ((FSMEnemyAIControl*)m_control)->m_enemy;
	//GameObj* queen = ((FSMEnemyAIControl*)m_control)->m_queenBee;

	//Seek the queen bee
	//enemy->SetTarget((GameCharacter*)queen);
}

FSMState* StateIdle::CheckTransitions(int i)
{
	//return the current state by default
	FSMState* nextState = ((FSMEnemyAIControl*)m_control)->m_machine->m_currentState;

	if(((FSMEnemyAIControl*)m_control)->isHealthBelowZero)
	{	
		//return dead state
		nextState = ((FSMEnemyAIControl*)m_control)->m_machine->GetState(FSM_ENEMY_DEAD);
	}
	else if(((FSMEnemyAIControl*)m_control)->m_distFromQueen < 30.0) //please use appropriate threshold
	{	
		//return the attack state
		nextState = ((FSMEnemyAIControl*)m_control)->m_machine->GetState(FSM_ATTACK_BEE);
	}

	return nextState;
}

void StateIdle::Exit()
{
	//give some indication that it's attacking or dead?
}

void StateIdle::Init()
{

}