/**
* Inherits from FSMAIControl. Controls a Bee
*/

#include "FSMBeeAIControl.h"
#include "FSMMachine.h"
#include "StateBeeAttackEnemy.h"
#include "State_FollowQueen.h"
#include "Bee.h"
#include "Enemy.h"
#include "Sound.h"

//-----------------------------------------------------------------------
NiImplementRTTI(FSMBeeAIControl,FSMAIControl);
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

}
//-----------------------------------------------------------------------
/**
* Dtor
* 
*/
FSMBeeAIControl::~FSMBeeAIControl()
{
	m_pTargetEnemy = 0;
	
}
//-----------------------------------------------------------------------
/**
* Updates the required variables that the controller needs to function
* @param delta time
*/
void FSMBeeAIControl::UpdatePerceptions(float fTime)
{
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
//-----------------------------------------------------------------------
/**
* Plays a sound when the bee is dying
*/
void FSMBeeAIControl::PlayDyingSound()
{
	SoundPtr snd = (Sound*)GetOwner()->GetAttribute(GameCharacter::ATTR_SOUND_2);
	if (snd)
	{
		snd->Play();
	}
	
}