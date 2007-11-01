/**
 * A GameCharacter. Inherits from GameObj3d
 */

#include "GameCharacter.h"
#include "GameManager.h"

//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 * @param type
 */
GameCharacter::GameCharacter(ResourceManager::ResourceType type) : GameObj3d(type)	, 									
																   m_pTarget(0)
{
}
//------------------------------------------------------------------------ 
/** 
 * Dtor
 * 
 */
GameCharacter::~GameCharacter()
{
	m_spAgent = 0;
	
}
//------------------------------------------------------------------------ 
/** 
 * Do extra initializations
 * 
 * 
 * @return bool
 */
bool GameCharacter::DoExtraInits()
{
	// get actor
	NxActor* myactor = m_spProp->GetSnapshot()->GetActorAt(0)->GetActor();
	if (!myactor)
	{
		return false;
	}

	// set dampings
	myactor->setLinearDamping(5.0f);
	myactor->setAngularDamping(5.0f);
	m_spAgent = NiNew Agent(myactor);

	return true;
}