#include "State_Attack_Bee.h"
#include "Bee.h"
#include "State_Dead.h"
#include "State_Idle.h"

void StateAttackBee::Enter()
{
	//play animation for attack
}
void StateAttackBee::Update(int t)
{
	/*
	//this is where the enemy attacks the bee
	
	FSMAIControl* control = m_control;
	GameObj* bee = ((FSMEnemyAIControl*)m_control)->m_TargetBee;
	Locust* enemy = ((FSMEnemyAIControl*)m_control)->m_enemy;

	//Set the closest bee as the target
	enemy->SetTarget((GameCharacter*)bee);

	//the collisions with the bee should reduce the bee's health
	//that should be happening in the collision response 
	*/
}

FSMState* StateAttackBee::CheckTransitions(int i)
{
	
	//return the current state by default
	FSMState* nextState = ((FSMEnemyAIControl*)m_control)->m_spMachine->m_currentState;

	if(((FSMEnemyAIControl*)m_control)->isHealthBelowZero)
	{	
		//return dead state
		nextState = ((FSMEnemyAIControl*)m_control)->m_spMachine->GetState(FSM_ENEMY_DEAD);
	}
	else if(((FSMEnemyAIControl*)m_control)->isTargetDead)
	{
		//For now please consider the idle state as the "seek" state of the enemy
		//return the idle state
		nextState = ((FSMEnemyAIControl*)m_control)->m_spMachine->GetState(FSM_IDLE);
	}

	//return the Attack state by default
	return nextState;
	
}

void StateAttackBee::Exit()
{
	//What does the enemy do when it exits the Attack state and before it enters the next state?
}

void StateAttackBee::Init()
{

}