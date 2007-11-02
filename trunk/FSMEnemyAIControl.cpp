#include "FSMEnemyAIControl.h"
#include "State_Attack.h"
#include "State_Dead.h"
#include "State_Idle.h"

FSMEnemyAIControl::FSMEnemyAIControl(Locust* enemy)
{
	m_enemy = enemy;
	m_enemy_machine = NiNew FSMEnemyMachine(FSM_MACH_ENEMY);
	StateIdle* idle = NiNew StateIdle();
	m_enemy_machine->AddState(idle);
	m_enemy_machine->AddState(NiNew StateAttack());
	m_enemy_machine->AddState(NiNew StateDead());
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
	m_nearestBee = NULL; //Game.getClosestGameObj(m_bee,GameObj::OBJ_ENEMY)
	
	//bee collision determination
	m_willCollide = false;

	if(m_willCollide)
		m_safetyRadius = 30.0f;
	else
		m_safetyRadius = 15.0f;

	if(m_nearestBee)
	{
		float speed = 0; //m_enemy->m_velocity.Norm
		m_nearestBeeDist = 0; //m_nearestBee->m_position.Distance(m_enemy->m_poistion)

		float dotVel;
		NiPoint3 normDelta(0,0,0); //m_nearestBee->m_position - m_enemy->m_position;
		normDelta.Unitize(); //I am guessing this means Normalize???

		float beeSpeed = 0; //m_nearestEnemy->m_velocity.Norm()

		if(speed > beeSpeed)
			dotVel = 0; //DOT(m_enemy->UnitVectorVelocity(),normDelta);
		else
		{
			speed = beeSpeed;
			dotVel = 0; //DOT(m_nearestEnemy->UnitVectorVelocity(),normDelta);

		}
		float speedAdj = 0; //LERP(speed/AI_MAX_SPEED,0.0f,50.0f)*dotVel
		float adjSafetyRadius = 0; //m_safetyRadius + speedAdj + m_nearestEnemy->m_size

		if(m_nearestBeeDist <= adjSafetyRadius && dotVel > 0)
			m_willCollide = true;
	}

}


void FSMEnemyAIControl::Init()
{

}