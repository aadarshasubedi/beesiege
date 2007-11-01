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



//------------------------------------------------------------------------
/** 
 * Ctor
 * 
 */
Bee::Bee() : GameCharacter(ResourceManager::RES_MODEL_BEE)
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
 * Update the target the bee's controller
 * 
 * @param fTime
 */
void Bee::DoExtraUpdates(float fTime)
{
	if (m_pTarget)
	{
		NxVec3 target = m_pTarget->GetAgent()->GetActor()->getGlobalPosition();
		m_spAgent->Update(target);
		if (m_pTarget == (GameCharacter*)GameManager::Get()->GetQueen())
		{
			m_spAgent->GetActor()->setGlobalOrientation(m_pTarget->GetAgent()->GetActor()->getGlobalOrientation());
		}
		else
		{
			m_spAgent->LookAt(target);
		}

	}

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
	lBehavior.AddTail(NiNew Separation());
	float arrivalC    = 1.0f;
	float wanderC     = 0.3f;
	float departureC  = 1.0f;
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
	// set a small linear damping for the bee's PhysX actor
	m_spAgent->GetActor()->setLinearDamping(1.0f);

	//m_spSound = 
	//ResourceManager::Get()->GetSound(ResourceManager::RES_SOUND_BEE); 
	//m_spSound->Play();


	return true;
}