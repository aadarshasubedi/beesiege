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
#include <list>
using namespace std;

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
	m_vTarget = NxVec3(100.0, 300.0, 0.0);
	m_spAgent->Update(m_vTarget);
	
}
//------------------------------------------------------------------------
bool Locust::DoExtraInits()
{
	if (!GameCharacter::DoExtraInits())
	{
		return false;
	}

	list<BehaviorPtr> vBehavior;
	vBehavior.push_back(NiNew Arrival());
	vBehavior.push_back(NiNew Wander());
	vBehavior.push_back(NiNew Departure());

	float arrivalC    = 1.0f;
	float wanderC     = 0.3f;
	float departureC  = 1.0f;

	list<float> vBehaviorCoef;
	vBehaviorCoef.push_back(arrivalC);
	vBehaviorCoef.push_back(wanderC);
	vBehaviorCoef.push_back(departureC);

	BehaviorComboPtr behavior = NiNew BehaviorCombo("", vBehavior, vBehaviorCoef);

	m_spAgent->GetController()->SetBehavior((Behavior*)behavior);
	GameManager::Get()->AddEnemy(this);
	
	return true;
}