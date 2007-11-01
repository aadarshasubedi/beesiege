#include "FSMBeeAIControl.h"
#include "State_Attack.h"
#include "State_Dead.h"
#include "State_PowerUp.h"
#include "State_FollowQueen.h"

FSMBeeAIControl::FSMBeeAIControl(Bee* bee)
{
	m_bee = bee;
	m_bee_machine = new FSMBeeMachine(FSM_MACH_BEE);
	StateFollowQueen* followQueen = new StateFollowQueen();
	m_bee_machine->AddState(followQueen);
	m_bee_machine->AddState(new StateAttack());
	m_bee_machine->AddState(new StatePowerUp());
	m_bee_machine->AddState(new StateDead());
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
	m_nearestEnemy = NULL; //Game.getClosestGameObj(m_bee,GameObj::OBJ_ENEMY)
	m_nearestPowerUp = NULL; //Game.getClosestPowerUp(m_bee, GameObj::OBJ_POWERUP)

	//bee collision determination
	m_willCollide = false;

	if(m_willCollide)
		m_safetyRadius = 30.0f;
	else
		m_safetyRadius = 15.0f;

	if(m_nearestEnemy)
	{
		float speed = 0; //m_bee->m_velocity.Norm
		m_nearestEnemyDist = 0; //m_nearestEnemy->m_position.Distance(m_bee->m_poistion)

		float dotVel;
		NiPoint3 normDelta(0,0,0); //m_nearestEnemy->m_position - m_bee->m_position;
		normDelta.Unitize(); //I am guessing this means Normalize???

		float enemySpeed = 0; //m_nearestEnemy->m_velocity.Norm()

		if(speed > enemySpeed)
			dotVel = 0; //DOT(m_bee->UnitVectorVelocity(),normDelta);
		else
		{
			speed = enemySpeed;
			dotVel = 0; //DOT(m_nearestEnemy->UnitVectorVelocity(),normDelta);

		}
		float speedAdj = 0; //LERP(speed/AI_MAX_SPEED,0.0f,50.0f)*dotVel
		float adjSafetyRadius = 0; //m_safetyRadius + speedAdj + m_nearestEnemy->m_size

		if(m_nearestEnemyDist <= adjSafetyRadius && dotVel > 0)
			m_willCollide = true;
	}

	if(m_nearestPowerUp)
	{
		m_nearestPowerUpDist = 0; //m_nearestPowerUp->m_position.Distance(m_bee->m_position)

		if(m_nearestPowerUpDist <= POWERUP_SCAN_DIST)
		{
			m_powerUpNear = true;
		}

	}


}