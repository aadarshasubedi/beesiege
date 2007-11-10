/**
 * A Bee or a queen's soldier. 
 */

#include "Bee.h"
#include "GameManager.h"
#include "Wander.h"
#include "BehaviorCombo.h"
#include "ConfigurationManager.h"
#include "ResourceManager.h"
#include "Arrival.h"
#include "Separation.h"
#include "Cohesion.h"
#include "Alignment.h"
#include "Departure.h"
#include "Agent.h"
#include <NiMaterialProperty.h>
#include "FSMBeeAIControl.h"

//------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
Bee::Bee() : GameCharacter(ResourceManager::RES_MODEL_BEE),
			 m_bAttackCommandIssued(false)
{
}
//------------------------------------------------------------------------
/** 
 * Dtor
 * 
 */
Bee::~Bee()
{
	m_spSound = 0;  
}
//------------------------------------------------------------------------
/**
* Lets the AI control know of the attack command
*/
void Bee::Attack (GameCharacterPtr target)
{
	m_bAttackCommandIssued  = true;
	m_pTarget = target;
}
//------------------------------------------------------------------------
/** 
 * Update the target the bee's controller
 * 
 * @param fTime
 */
void Bee::DoExtraUpdates(float fTime)
{
	if (m_pAIControl)
	{
		m_pAIControl->Update(fTime);
	}

	if (m_pTarget)
	{
		NxVec3 target = m_pTarget->GetAgent()->GetActor()->getGlobalPosition();
		m_spAgent->Update(target);
	}
	/*
	
	*/
	//m_spSound->Update(m_spAgent->GetActor()->getGlobalPosition()/50.0f,
	//	m_spAgent->GetActor()->getLinearVelocity()/50.0f);

}
//------------------------------------------------------------------------ 
/** 
 * Create a behavior for the bee's controller 
 * and initialize the bee's properties 
 * 
 * 
 * @return bool
 */
bool Bee::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	// add behaviors to a behavior combo
	NiTPointerList<BehaviorPtr> lBehavior;
	lBehavior.AddTail(NiNew Arrival());
	lBehavior.AddTail(NiNew Wander());
	lBehavior.AddTail(NiNew Departure());
	//lBehavior.AddTail(NiNew Separation());
	float arrivalC    = 1.0f;
	float wanderC     = 0.5f;
	float departureC  = 1.5f;
	float separationC = 2.0f;

	// add behavior coefficients
	NiTPointerList<float> lBehaviorCoef;
	lBehaviorCoef.AddTail(arrivalC);
	lBehaviorCoef.AddTail(wanderC);
	lBehaviorCoef.AddTail(departureC);
	lBehaviorCoef.AddTail(separationC);

	// set the bee's behavior
	BehaviorComboPtr behavior = NiNew BehaviorCombo(lBehavior, lBehaviorCoef);
	m_spAgent->GetController()->SetBehavior((Behavior*)behavior);

	// add the bee to the queen's soldier list
	GameManager::Get()->GetQueen()->AddSoldier(this);
	// add the bee's agent to the GameManager's agent list
	GameManager::Get()->AddAgent(m_spAgent);
	// set the default target to the queen
	m_pTarget = GameManager::Get()->GetQueen();
	m_spAgent->GetActor()->setGlobalPosition(m_pTarget->GetAgent()->GetActor()->getGlobalPosition() - 
		NxVec3(100.0, 0.0, 0.0));
	// set a small linear damping for the bee's PhysX actor
	m_spAgent->GetActor()->setLinearDamping(1.0f);

	m_pAIControl = NiNew FSMBeeAIControl(this);
	//m_spSound = 
	//ResourceManager::Get()->GetSound(ResourceManager::RES_SOUND_BEE); 
	//m_spSound->Play();


	return true;
}