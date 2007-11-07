#include "State_PowerUp.h"

void StatePowerUp::Enter()
{

}
void StatePowerUp::Update(int t)
{
	
	FSMAIControl* control = m_control;
	Queen* queen = ((FSMQueenAIControl*)m_control)->m_queen;
	GameObj* powerup = ((FSMQueenAIControl*)m_control)->m_nearestPowerUp;
	
	//Set enemy as target
	queen->SetTarget((GameCharacter*)powerup);

	//the collisions with powerup should increase the bees' health
	//that should be happening in the collision response

}

FSMState* StatePowerUp::CheckTransitions(int i)
{
	//return the current state by default
	FSMState* nextState = ((FSMQueenAIControl*)m_control)->m_queen_machine->m_currentState;

	if((((FSMQueenAIControl*)m_control)->isPowerUpEmpty) || (((FSMQueenAIControl*)m_control)->isHealthFull))
	{
		//tell the user that the powerup is used up or the health is full
		//return the queen wander state
		nextState = ((FSMQueenAIControl*)m_control)->m_queen_machine->GetState(FSM_QUEEN_WANDER);
	}

	else if(((FSMQueenAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		//end the game here?
		nextState = ((FSMQueenAIControl*)m_control)->m_queen_machine->GetState(FSM_QUEEN_DEAD);
	}

	return nextState;
}

void StatePowerUp::Exit()
{
	((FSMQueenAIControl*)m_control)->issuedPowerUpCommand = false;
}

void StatePowerUp::Init()
{

}