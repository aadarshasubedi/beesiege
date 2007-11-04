#include "State_Attack_Enemy.h"

void StateAttackEnemy::Enter()
{
	//play animation for attack
}
void StateAttackEnemy::Update(int t)
{
	//here the bee attacks the enemy

	FSMAIControl* control = m_control;
	GameObj* enemy = ((FSMBeeAIControl*)m_control)->m_TargetEnemy;
	Bee* bee = ((FSMBeeAIControl*)m_control)->m_bee;

	//Set enemy as target
	bee->SetTarget((GameCharacter*)enemy);

	//the collisions with enemy should reduce the enemy's health
	//that should be happening in the collision response
}

FSMState* StateAttackEnemy::CheckTransitions(int i)
{
	//get the health of this bee 

	FSMAIControl* control = m_control;
	if(((FSMBeeAIControl*)m_control)->isHealthBelowZero)
	{
		//In order to return a state object we have to do as below...but i don't think that's right
		//so we may need to return integers that represent the state and the FSMMachine should take care whether
		//it is a valid transition id and then go to the next state

		/*StateDead* deadState = NiNew StateDead(control);
		return deadState;*/

		//return the dead state
	}

	//go back to follow queen state if target enemy is dead
	else if(((FSMBeeAIControl*)m_control)->isTargetDead)
	{
		//For now please consider the idle state as the "seek" state
		//return the follow queen state
	}

	
	//return the same state - attack enemy
	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StateAttackEnemy::Exit()
{
	//is the bee supposed to do anything special as it exits the attack state?
	// that logic would come here
}

void StateAttackEnemy::Init()
{

}