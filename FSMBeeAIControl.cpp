/**
* Inherits from FSMAIControl. Controls a Bee
*/

#include "FSMBeeAIControl.h"
#include "FSMMachine.h"
#include "StateBeeAttackEnemy.h"
#include "State_FollowQueen.h"
#include "Bee.h"
#include "Enemy.h"
#include "GameManager.h"
//-----------------------------------------------------------------------
/**
* Ctor
* @param The bee that needs to be controlled
*/
FSMBeeAIControl::FSMBeeAIControl(Bee* bee) : FSMAIControl((GameCharacter*)bee),
											   m_pTargetEnemy(0),
											   isHealthBelowZero(0),
											   isTargetDead(0),
											   issuedAttackCommand(0)
{
	// add states to the FSM
	StateFollowQueen* followQueen = NiNew StateFollowQueen(this);
	m_spMachine->AddState(followQueen, FSM_FOLLOW_QUEEN);
	m_spMachine->AddState(NiNew StateBeeAttackEnemy(this), FSM_ATTACK_ENEMY);
	m_spMachine->SetDefaultState(followQueen);

	// add agent to the GameManager agents list
	// so that other agents know about it when they
	// do group behaviors
	//GameManager::Get()->AddAgent(m_spAgent);

}
//-----------------------------------------------------------------------
/**
* Dtor
* 
*/
FSMBeeAIControl::~FSMBeeAIControl()
{
	m_pTargetEnemy = 0;
	// remove agent from game manager
	//GameManager::Get()->RemoveAgent(m_spAgent);
}
//-----------------------------------------------------------------------
/**
* Updates the required variables that the controller needs to function
* @param delta time
*/
void FSMBeeAIControl::UpdatePerceptions(float fTime)
{
	NIASSERT(m_pOwner);
	Bee* ownerBee = (Bee*)m_pOwner;
	issuedAttackCommand = ownerBee->WasAttackIssued();

	if (issuedAttackCommand)
	{
		m_pTargetEnemy = ownerBee->GetEnemyTarget();
	}
	else
	{
		m_pTargetEnemy = 0;
	}
}
//-----------------------------------------------------------------------
/**
* Performs extra updates if necessary
* @param delta time
*/
void FSMBeeAIControl::DoExtraUpdates(float fTime)
{
	
	
}