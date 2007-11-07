#include "State_Enemy_Dead.h"

void StateEnemyDead::Enter()
{

}
void StateEnemyDead::Update(int t)
{
	//free the memory for this GameCharacter
	Exit();
	
}

FSMState* StateEnemyDead::CheckTransitions(int i)
{
	//always return the dead state
	FSMState* nextState = ((FSMEnemyAIControl*)m_control)->m_enemy_machine->m_currentState;
	return nextState;
}

void StateEnemyDead::Exit()
{
	FSMAIControl* control = m_control;
	//delete ((FSMEnemyAIControl*)m_control)->m_enemy;
}

void StateEnemyDead::Init()
{

}