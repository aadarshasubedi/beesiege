#include "State_Queen_Wander.h"

void StateQueenWander::Enter()
{

}
void StateQueenWander::Update(int t)
{
	
	FSMAIControl* control = m_control;
	Queen* queen = ((FSMBeeAIControl*)m_control)->m_queen;
	
	//Call the queen behavior here:
	//queen->SetTarget();

}

FSMState* StateQueenWander::CheckTransitions(int i)
{
	
	FSMAIControl* control = m_control;
	if(((FSMQueenAIControl*)m_control)->issuedPowerUpCommand)
	{
		//return the PowerUp State
	}

	//go back to follow queen state if target enemy is dead
	else if(((FSMBeeAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		//that should end the game!
	}

	//return the wander behavior by default

	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StateQueenWander::Exit()
{

}

void StateQueenWander::Init()
{

}