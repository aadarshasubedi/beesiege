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
Locust::Locust() : GameCharacter(ResourceManager::RES_MODEL_LOCUST)
{
}
//------------------------------------------------------------------------
Locust::~Locust()
{

}
//------------------------------------------------------------------------
void Locust::DoExtraUpdates(float fTime)
{
	if (m_pTarget)
	{
		NxVec3 target = m_pTarget->GetAgent()->GetActor()->getGlobalPosition();
		m_spAgent->Update(target);
		m_spAgent->LookAt(target);
	}
	else
	{
		NxVec3 target = NxVec3(100.0, 500.0, -100.0);
		m_spAgent->Update(target);
		m_spAgent->LookAt(GameManager::Get()->GetQueen()->GetAgent()->GetActor()->getGlobalPosition());
	}
}
//------------------------------------------------------------------------
bool Locust::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	NiTPointerList<BehaviorPtr> lBehavior;
	lBehavior.AddTail(NiNew Arrival());
	lBehavior.AddTail(NiNew Wander());
	lBehavior.AddTail(NiNew Departure());
	//lBehavior.AddTail(NiNew Separation());

	float arrivalC    = 1.0f;
	float wanderC     = 0.3f;
	float departureC  = 1.0f;
	float separationC = 0.9f;

	NiTPointerList<float> lBehaviorCoef;
	lBehaviorCoef.AddTail(arrivalC);
	lBehaviorCoef.AddTail(wanderC);
	lBehaviorCoef.AddTail(departureC);
	//lBehaviorCoef.AddTail(separationC);

	BehaviorComboPtr behavior = NiNew BehaviorCombo(lBehavior, lBehaviorCoef);

	m_spAgent->GetController()->SetBehavior((Behavior*)behavior);
	GameManager::Get()->AddEnemy(this);
	//m_spTarget = GameManager::Get()->GetQueen();
	
	return true;
}