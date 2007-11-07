#include "FSMEnemyAIControl.h"
#include "State_Attack_Bee.h"
#include "State_Enemy_Dead.h"
#include "State_Idle.h"

FSMEnemyAIControl::FSMEnemyAIControl(Locust* enemy)
{
	m_enemy = enemy;
	m_enemy_machine = NiNew FSMEnemyMachine(FSM_MACH_ENEMY);
	StateIdle* idle = NiNew StateIdle(this);
	m_enemy_machine->AddState(idle);
	m_enemy_machine->AddState(NiNew StateAttackBee(this));
	m_enemy_machine->AddState(NiNew StateEnemyDead(this));
	m_enemy_machine->SetDefaultState(idle);
}

void FSMEnemyAIControl::Update(int t)
{
	if(!m_enemy)
	{
		m_enemy_machine->Reset();
		return;
	}
	
	UpdatePerceptions(t);
	m_enemy_machine->UpdateMachine(t);
}

void FSMEnemyAIControl::UpdatePerceptions(int t)
{
	//We need to get the closest bee to the bee here
	//m_TargetBee = m_enemy->getNearestBee();

	//get the health of the enemy here
	//m_health = m_enemy->getHealth();
	if(m_health <= 0.0)
		isHealthBelowZero = true;

	if(m_TargetBee)
	{
		float beeHealth;
		//get target enemy health here
		//enemyHealth = m_TargetEnemy->getHealth();

		if(beeHealth <= 0.0)
			isTargetDead = true;
	
	}
	
	//determine distance from queen
	//m_distFromQueen = m_enemy->getDistanceFromQueen();

}


void FSMEnemyAIControl::Init()
{

}