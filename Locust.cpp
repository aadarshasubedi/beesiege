/**
 * Enemy: Locust
 */

#include "Locust.h"
#include "GameManager.h"
#include "Wander.h"
#include "BehaviorCombo.h"
#include "ResourceManager.h"
#include "Agent.h"
#include "Arrival.h"
#include "Departure.h"
#include "Wander.h"
#include "BehaviorCombo.h"

//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 */
Locust::Locust() : GameCharacter(ResourceManager::RES_MODEL_LOCUST)
					
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
Locust::~Locust()
{

}
//------------------------------------------------------------------------ 
/** 
 * Does extra updates
 * 
 * @param fTime
 */
void Locust::DoExtraUpdates(float fTime)
{
	// if there is a current target follow it
	if (m_pTarget)
	{
		NxVec3 target = m_pTarget->GetAgent()->GetActor()->getGlobalPosition();
		m_spAgent->Update(target);
		m_spAgent->LookAt(target);
	}
	// else put a different target
	else
	{
		m_spAgent->Update(m_vTempTargetPos);
		m_spAgent->LookAt(GameManager::Get()->GetQueen()->GetAgent()->GetActor()->getGlobalPosition());
	}
}
//------------------------------------------------------------------------ 
/** 
 * Does extra initializations
 * 
 * 
 * @return bool
 */
bool Locust::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	// create a behavior combo
	NiTPointerList<BehaviorPtr> lBehavior;
	lBehavior.AddTail(NiNew Arrival());
	lBehavior.AddTail(NiNew Wander());

	float arrivalC    = 0.5f;
	float wanderC     = 0.5f;

	NiTPointerList<float> lBehaviorCoef;
	lBehaviorCoef.AddTail(arrivalC);
	lBehaviorCoef.AddTail(wanderC);
	//lBehaviorCoef.AddTail(separationC);

	// set the behavior
	BehaviorComboPtr behavior = NiNew BehaviorCombo(lBehavior, lBehaviorCoef);

	m_spAgent->GetController()->SetBehavior((Behavior*)behavior);
	
	return true;
}