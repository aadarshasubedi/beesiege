#include "State_Attack_Enemy.h"

void StateAttackEnemy::Enter()
{
	//play animation for attack
}
void StateAttackEnemy::Update(int t)
{
	
}

FSMState* StateAttackEnemy::CheckTransitions(int i)
{
	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StateAttackEnemy::Exit()
{

}

void StateAttackEnemy::Init()
{

}