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
#include <list>
#include <NiMaterialProperty.h>

#include <NiGeometry.h>

using namespace std;


//------------------------------------------------------------------------
Bee::Bee() : GameCharacter(ResourceManager::RES_MODEL_BEE)
{
}
//------------------------------------------------------------------------
Bee::~Bee()
{

}
//------------------------------------------------------------------------
void Bee::DoExtraUpdates(float fTime)
{
	m_spAgent->Update(m_vTarget);
	m_spAgent->LookAt(m_vTarget);
}
//------------------------------------------------------------------------
bool Bee::DoExtraInits()
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
	GameManager::Get()->GetQueen()->AddSoldier(this);

	return true;
}