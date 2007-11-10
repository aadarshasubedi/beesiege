#include "FSMBeeAIControl.h"
#include "FSMMachine.h"
#include "State_Attack_Enemy.h"
#include "State_Bee_Dead.h"
#include "State_PowerUp.h"
#include "State_FollowQueen.h"
#include "Bee.h"

FSMBeeAIControl::FSMBeeAIControl(Bee* bee) : FSMAIControl((GameCharacter*)bee),
											 isHealthBelowZero(0),
											 isTargetDead(0),
											 issuedAttackCommand(0)
{
	StateFollowQueen* followQueen = NiNew StateFollowQueen(this);
	m_machine->AddState(followQueen);
	m_machine->AddState(NiNew StateAttackEnemy(this));
	m_machine->AddState(NiNew StatePowerUp(this));
	m_machine->AddState(NiNew StateBeeDead(this));
	m_machine->SetDefaultState(followQueen);
}




void FSMBeeAIControl::UpdatePerceptions(int t)
{
	
	m_TargetEnemy = m_character->GetTarget();
	//get the nearest powerUp here
	//m_nearestPowerUp = m_bee->m_TargetPowerUp

	//get the health of the bee here
	//m_health = m_bee->getHealth();
	//if(m_health <= 0.0)
	//	isHealthBelowZero = true;

	if(m_TargetEnemy)
	{
	//	float enemyHealth;
		//get target enemy health here
		//enemyHealth = m_TargetEnemy->getHealth();

	//	if(enemyHealth <= 0.0)
	//		isTargetDead = true;
	
	}
	//check if bee has been issued an attack command
	issuedAttackCommand = ((Bee*)m_character)->WasAttackCommandIssued();
	
}

void FSMBeeAIControl::Init()
{

}