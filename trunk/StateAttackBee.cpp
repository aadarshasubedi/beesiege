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
	//this is where the enemy attacks the bee
	
	FSMAIControl* control = m_control;
	GameObj* bee = ((FSMEnemyAIControl*)m_control)->m_TargetBee;
	Locust* enemy = ((FSMEnemyAIControl*)m_control)->m_enemy;

	//Set the closest bee as the target
	enemy->SetTarget((GameCharacter*)bee);

	//the collisions with the bee should reduce the bee's health
	//that should be happening in the collision response 
}

FSMState* StateAttackBee::CheckTransitions(int i)
{
	//get the health of this enemy character
	FSMAIControl* control = m_control;
	if(((FSMEnemyAIControl*)m_control)->isHealthBelowZero)
	{
		//In order to return a state object we have to do as below...but i don't think that's right
		//so we may need to return integers that represent the state and the FSMMachine should take care whether
		//it is a valid transition id and then go to the next state

		/*StateDead* deadState = NiNew StateDead(control);
		return deadState;*/

		//return dead state
	}
	else if(((FSMEnemyAIControl*)m_control)->isTargetDead)
	{
		//For now please consider the idle state as the "seek" state of the enemy
		
		//return the idle state
	}

	//return the Attack state by default

	FSMState* dummyState = NiNew FSMState();
	return dummyState;

}

void StateAttackBee::Exit()
{
	//What does the enemy do when it exits the Attack state and before it enters the next state?
}

void StateAttackBee::Init()
{

}