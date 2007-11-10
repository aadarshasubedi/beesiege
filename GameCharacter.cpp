/**
 * A GameCharacter. Inherits from GameObj3d
 */

#include "GameCharacter.h"
#include "GameManager.h"
#include "FSMAIControl.h"

//------------------------------------------------------------------------ 
/** 
 * Ctor
 * 
 * @param type
 */
GameCharacter::GameCharacter(ResourceManager::ResourceType type) : GameObj3d(type)	, 									
																   m_pTarget(0),
																   m_vTempTargetPos(0.0, 0.0, 0.0),
																   m_pAIControl(0)
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
	if (m_pAIControl)
	{
		NiDelete m_pAIControl;
		m_pAIControl = 0;
	}
	
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