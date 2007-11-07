#include "State_Queen_Wander.h"
#include "Queen.h"

void StateQueenWander::Enter()
{

}
void StateQueenWander::Update(int t)
{
	
	FSMAIControl* control = m_control;
	Queen* queen = ((FSMQueenAIControl*)m_control)->m_queen;
	
	//Call the queen behavior here:
	//queen->SetTarget();

}

FSMState* StateQueenWander::CheckTransitions(int i)
{
	
	//return the current state by default
	FSMState* nextState = ((FSMQueenAIControl*)m_control)->m_queen_machine->m_currentState;

	if(((FSMQueenAIControl*)m_control)->issuedPowerUpCommand)
	{
		//return the PowerUp State
		nextState = ((FSMQueenAIControl*)m_control)->m_queen_machine->GetState(FSM_POWERUP);
	}
	else if(((FSMQueenAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		//that should end the game!
		nextState = ((FSMQueenAIControl*)m_control)->m_queen_machine->GetState(FSM_QUEEN_DEAD);
	}

	return nextState;
}

void StateQueenWander::Exit()
{

}

void StateQueenWander::Init()
{

}