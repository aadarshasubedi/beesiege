#include "FSMBeeAIControl.h"
#include "State_Attack_Enemy.h"
#include "State_Bee_Dead.h"
#include "State_PowerUp.h"
#include "State_FollowQueen.h"

FSMBeeAIControl::FSMBeeAIControl(Bee* bee)
{
	m_bee = bee;
	m_bee_machine = NiNew FSMBeeMachine(FSM_MACH_BEE);
	StateFollowQueen* followQueen = NiNew StateFollowQueen(this);
	m_bee_machine->AddState(followQueen);
	m_bee_machine->AddState(NiNew StateAttackEnemy(this));
	m_bee_machine->AddState(NiNew StatePowerUp(this));
	m_bee_machine->AddState(NiNew StateBeeDead(this));
	m_bee_machine->SetDefaultState(followQueen);
}

void FSMBeeAIControl::Update(int t)
{
	if(!m_bee)
	{
		m_bee_machine->Reset();
		return;
	}
	
	UpdatePerceptions(t);
	m_bee_machine->UpdateMachine(t);
}

void FSMBeeAIControl::UpdatePerceptions(int t)
{
	//We need to get the closest enemy to the bee here
	//m_TargetEnemy = m_bee->getNearestTarget();

	//get the nearest powerUp here
	//m_nearestPowerUp = m_bee->m_TargetPowerUp

	//get the health of the bee here
	//m_health = m_bee->getHealth();
	if(m_health <= 0.0)
		isHealthBelowZero = true;

	if(m_TargetEnemy)
	{
		float enemyHealth;
		//get target enemy health here
		//enemyHealth = m_TargetEnemy->getHealth();

		if(enemyHealth <= 0.0)
			isTargetDead = true;
	
	}
	//check if bee has been issued an attack command
	//issuedAttackCommand = m_bee->isAttackCommandIssued;

}

void FSMBeeAIControl::Init()
{

}