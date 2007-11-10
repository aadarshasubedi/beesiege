#include "FSMQueenAIControl.h"
#include "State_PowerUp.h"
#include "State_Queen_Dead.h"
#include "State_Queen_Wander.h"
#include "GameManager.h"
#include "FSMMachine.h"

FSMQueenAIControl::FSMQueenAIControl() : FSMAIControl(GameManager::Get()->GetQueen())
{
	StateQueenWander* wander = NiNew StateQueenWander(this);
	m_machine->AddState(wander);
	m_machine->AddState(NiNew StatePowerUp(this));
	m_machine->AddState(NiNew StateQueenDead(this));
	m_machine->SetDefaultState(wander);
}


void FSMQueenAIControl::UpdatePerceptions(int t)
{
	/*
	bool issuedPowerUpCommand;
	bool isHealthBelowZero;
	bool isHealthFull;

	bool isPowerUpEmpty;
	GameObj* m_nearestEnemy;
	GameObj* m_nearestPowerUp;
	
	//get the health of the queen here
	//m_health = m_queen->getHealth();
	if(m_health <= 0.0)
		isHealthBelowZero = true;

	if(m_health >= FULL_HEALTH)
		isHealthFull = true;

	//get nearest power up here
	//m_nearestPowerUp = m_queen->getNearestPowerUp();

	//check the powerUp capacity
	//if(m_nearestPowerUp->getCapacity() <= 0.0)
		//isPowerUpEmpty = true; 

    //check if user has issued powerup command
	//if(m_queen->issuedPowerUp)
		//issuedPowerUpCommand = true;
	*/
}


void FSMQueenAIControl::Init()
{

}