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

	FSMAIControl* control = m_control;
	if((((FSMQueenAIControl*)m_control)->isPowerUpEmpty) || (((FSMQueenAIControl*)m_control)->isHealthFull))
	{
		//tell the user that the powerup is used up or the health is full
		//return the queen wander state
	}

	//go back to follow queen state if target enemy is dead
	else if(((FSMQueenAIControl*)m_control)->isHealthBelowZero)
	{
		//return the dead state
		//end the game here?
	}

	//return the powerup state by default

	FSMState* dummyState = NiNew FSMState();
	return dummyState;
}

void StatePowerUp::Exit()
{

}

void StatePowerUp::Init()
{

}