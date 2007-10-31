#include "GameCharacter.h"
#include "GameManager.h"

//------------------------------------------------------------------------
GameCharacter::GameCharacter(ResourceManager::ResourceType type) : GameObj3d(type)	, 									
																   m_pTarget(0)
{
}
//------------------------------------------------------------------------
GameCharacter::~GameCharacter()
{
	m_spAgent = 0;
	
}
//------------------------------------------------------------------------
bool GameCharacter::DoExtraInits()
{
	NxActor* myactor = m_spProp->GetSnapshot()->GetActorAt(0)->GetActor();
	if (!myactor)
	{
		return false;
	}

	myactor->setLinearDamping(5.0f);
	myactor->setAngularDamping(5.0f);
	m_spAgent = NiNew Agent(myactor);

	return true;
}