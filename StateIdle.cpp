#include "State_Idle.h"

void StateIdle::Enter()
{

}
void StateIdle::Update(int t)
{
	FSMAIControl* control = m_control;
	Locust* enemy = ((FSMEnemyAIControl*)m_control)->m_enemy;
	GameObj* queen = ((FSMEnemyAIControl*)m_control)->m_queenBee;

	//Seek the queen bee
	enemy->SetTarget((GameCharacter*)queen);
}

FSMState* StateIdle::CheckTransitions(int i)
{
	//get the health of this character
	FSMAIControl* control = m_control;
	if(((FSMEnemyAIControl*)m_control)->isHealthBelowZero)
	{
		//return dead state
	}
	else if(((FSMEnemyAIControl*)m_control)->m_distFromQueen < 30.0) //please use appropriate threshold
	{	
		//return the attack state
	}

	//return the Attack state by default

	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StateIdle::Exit()
{
	//give some indication that it's attacking or dead?
}

void StateIdle::Init()
{

}