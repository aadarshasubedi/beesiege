/**
* Inherits from FSMAIControl. Controls a HoneyBee
*/

#include "FSMHoneyBeeAIControl.h"
#include "FSMMachine.h"
#include "State_FollowQueen.h"
#include "StateHoneyBeeGather.h"
#include "HoneyBee.h"
#include <NiTPointerList.h>
#include "Queen.h"
#include "GameManager.h"
#include "ConfigurationManager.h"
//-----------------------------------------------------------------------
NiImplementRTTI(FSMHoneyBeeAIControl,FSMAIControl);
//-----------------------------------------------------------------------
/**
* Ctor
* @param The bee that needs to be controlled
*/
FSMHoneyBeeAIControl::FSMHoneyBeeAIControl(HoneyBee* bee) 
								:  FSMAIControl((GameCharacter*)bee),
								   issuedGatherCommand(false)
{
	// add states to the FSM
	StateFollowQueen* followQueen = NiNew StateFollowQueen(this);
	m_spMachine->AddState(followQueen, FSM_FOLLOW_QUEEN);
	m_spMachine->AddState(NiNew StateHoneyBeeGather(this), FSM_GATHER_HONEY);
	m_spMachine->SetDefaultState(followQueen);

}
//-----------------------------------------------------------------------
/**
* Dtor
* 
*/
FSMHoneyBeeAIControl::~FSMHoneyBeeAIControl()
{
	
}
//-----------------------------------------------------------------------
/**
* Updates the required variables that the controller needs to function
* @param delta time
*/
void FSMHoneyBeeAIControl::UpdatePerceptions(float fTime)
{
	HoneyBee* ownerBee = (HoneyBee*)m_pOwner;
	issuedGatherCommand = ownerBee->WasGatherIssued();

}
//-----------------------------------------------------------------------
/**
* Performs extra updates if necessary
* @param delta time
*/
void FSMHoneyBeeAIControl::DoExtraUpdates(float fTime)
{
	
}
